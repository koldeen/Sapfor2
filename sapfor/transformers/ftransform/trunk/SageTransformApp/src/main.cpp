#include <iostream>
#include <sstream>
#include <ctime>
#include <fstream>
#include <LoopCombine.h>
#include <SageTransformException.hpp>
#include <SignalHandling.hpp>

//own includes
#include "SageTransformLib.hpp"
#include "SageUtils.hpp"
#include "Log.hpp"
#include "LaunchOptions.hpp"

using std::cout;
using std::endl;
using std::string;
using namespace SageTransform;
using SageUtils::getLastLoopStatement;
using SageUtils::decodeStmtVariant;

void printStatements(const char *projectFileName) {
    Log::info(string("Print info for Sage++ project ") + projectFileName);
    errno = 0;
    FILE *f = fopen(projectFileName, "r");
    if (errno != 0 || f == 0) {
        Log::info(string("Open failed for project file ") + projectFileName);
        cout << strerror(errno) << endl;
    } else {
        Log::info(string("Open success for project file ") + projectFileName);
    }
    Log::info("Reading project...");
    SgProject *project = new SgProject(projectFileName);
    Log::info("OK");
    SgFile *file;
    SgStatement *stmt;
    int stmtCount = -1;
    for (int i = 0; i < project->numberOfFiles(); i++) {
        file = &(project->file(i));
        stmt = file->firstStatement();
        while (stmt != NULL) {
            stmtCount++;
            //Log::debug(string("Stmt ") + stmtCount + " variant=" + stmt->variant() + " " + decodeStmtVariant(stmt->variant()));
            switch (stmt->variant()) {
                case FOR_NODE:
                    //Log::debug(string(" has ") + stmt->numberOfChildrenList1() + " child stmts");
                default:
                    if (stmt->comments()) {
                        Log::debug(string() + stmt->comments());
                    }
                    break;
            }
            if (stmt->controlParent() != NULL) {
                Log::debug(string() + "  controlParent type " + decodeStmtVariant(stmt->controlParent()->variant()));
            }
            cout << endl;
            stmt = stmt->lexNext();
        }
    }
    //Log::debug(string("Found ") + stmtCount + " statements");
    Log::debug("Print ends");
}

extern "C" int out_free_form; //sage built-in
void reprintSageProject(SgFile *file) {
    out_free_form = 1;
    FILE *outputFile = fopen("trans.f90", "w");
    file->unparse(outputFile);
    fclose(outputFile);
}

vector<string> readFortranSourceLines(const char *fileName) {
    vector<string> result;
    result.push_back("<file start>");
    std::ifstream infile(fileName);
    std::string line;
    while (std::getline(infile, line)) {
        result.push_back(line);
    }
    return result;
}

void transform(SgFile *file) {
    const char *fortranSourceName = file->filept->filename;
    vector<string> lines = readFortranSourceLines(fortranSourceName);
    //pipeline
    //1. get dependency graph from DependencyGraphGetter (currently from comments)
    //2.? check if StatementsSplitter can split
    //3 = 2.False.? check if StatementReshuffler can reshuffle
    //4 = 3.True. StatementReshuffler switches order of statements. Goto 2.
    //5 = 3.False. nothing can be done - continue to next loop
    //6 = 2.True. StatementSplitter makes groups for resulting loops
    //7 = LoopTransformSplitter splits loop

    StatementOrderTransform stmtOrderTransform;
    LoopTransformTighten loopTransformTighten;
    SgStatement *stmt, *next;
    SgForStmt *outerLoop, *innermostLoop;
    stmt = file->firstStatement();
    try {
        while (stmt != NULL) {
            next = stmt->lexNext();
            size_t lineNumber = (size_t) stmt->lineNumber();
            cout << "at line " << lineNumber;
            if (lineNumber < lines.size()) {
                cout << ":" << lines[lineNumber];
            } else {
                cout << " <source not available>";
            }
            cout << endl;
            char *comment = stmt->comments();
            if (comment) cout << "stmt comment: " << comment << endl;

            if ((outerLoop = isSgForStmt(stmt))) {
                //care for order of transformations, they possibly affect each other
                if (loopTransformTighten.hasTightenComment(outerLoop)) {
                    int initialTightness = loopTransformTighten.getTightness(outerLoop);
                    int canTightTo = loopTransformTighten.canTighten(outerLoop);
                    cout << "tightening loop at line:" << outerLoop->lineNumber()
                         << " from depth=" << initialTightness << " to depth=" << canTightTo << std::endl;
                    if (loopTransformTighten.tighten(outerLoop, canTightTo)) {
                        cout << "tightening successful" << std::endl;
                        loopTransformTighten.removeComment(outerLoop);
                    }
                } else if (LoopTransformBreak::hasValidBreakComment(outerLoop)) {
                    next = getLastLoopStatement(outerLoop)->lexNext();
                    vector<vector<uint>> breakSchema = LoopTransformBreak::getFullBreakSchema(outerLoop);
                    LoopTransformBreak::breakLoop(outerLoop, SageUtils::getInnermostForStmt(outerLoop), breakSchema);
                } else if (LoopTransformMerge::getMergeGroupNumber(outerLoop) >= 0) {
                    cout << "trying to merge loops starting at line:" << outerLoop->lineNumber() << std::endl;
                    next = LoopTransformMerge::merge(outerLoop);
                } else if (DependencyInfoGetter::hasDependencyInfo(outerLoop)) {
                    cout << "trying to split loop at line:" << outerLoop->lineNumber() << std::endl;
                    next = getLastLoopStatement(outerLoop)->lexNext();
                    innermostLoop = SageUtils::getInnermostForStmt(outerLoop);
                    stmtOrderTransform.transformLoop(outerLoop, innermostLoop);
                } else if (LoopCombine::hasComment(outerLoop)) {
                    cout << "Applying LoopCombine" << std::endl;
                    LoopCombine transformation;
                    next = transformation.apply(outerLoop);
                    cout << "Applied LoopCombine" << std::endl;
                    //removed automatically
                    //transformation.removeComment(outerLoop);
                    cout << "Removed LoopCombine comment (auto)" << std::endl;
                }
            } else if (isSgInputOutputStmt(stmt) && WriteDearray::hasIOArrayComment(stmt)) {
                //currently dearray in write
                //result not used now
                vector<SgSymbol *> createdScalars = WriteDearray::removeArrayAccess(stmt);
            }

            stmt = next;
        }
    } catch (SageTransformException &e) {
        cout << e.toString();
    } catch (const char *charE) {
        cout << "Exception during transform: " << charE << endl;
    } catch (std::string strE) {
        cout << "Exception during transform: " << strE << endl;
    } catch (...) {
        cout << "Exception during transform: <no message>" << endl;
    }
    reprintSageProject(file);
}

void redirectCout(const char *logFileName) {
    /* from stackoverflow
       http://stackoverflow.com/questions/10150468/how-to-redirect-cin-and-cout-to-files
     */
    /*
    std::ifstream in("in.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    std::ofstream out("out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    std::string word;
    std::cin >> word;           //input from the file in.txt
    std::cout << word << "  ";  //output to the file out.txt

    f(); //call function


    std::cin.rdbuf(cinbuf);   //reset to standard input again
    std::cout.rdbuf(coutbuf); //reset to standard output again

    std::cin >> word;   //input from the standard input
    std::cout << word;  //output to the standard input
    */
}

void backUpPreviousLog(const std::string fileName) {
    FILE *fin = fopen(fileName.c_str(), "r");
    if (fin) {
        fclose(fin);

        std::time_t t = std::time(nullptr);   // get time now
        std::tm *now = std::localtime(&t);
        std::stringstream sstm;
        sstm << fileName
             << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday
             << "." << now->tm_hour << '-' << now->tm_min << '-' << now->tm_sec
             << ".backup";
        string newFileName = sstm.str();

        rename(fileName.c_str(), newFileName.c_str());
    }
}

int main(int argc, const char **argv) {
    SignalHandling signalHandling; //we need to instantiate it to ensure it is linked actually.
    const char *fileName = "dvm.proj";
    const string logFileName = "SageTransform.log";
    backUpPreviousLog(logFileName);
    LaunchOptions launchOptions = LaunchOptions::fromArgs(argc, argv);
    std::ofstream logFileStream(logFileName);
    std::streambuf *coutbuf;
    const bool silent = launchOptions.isSilent();
    if (silent) {
        coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(logFileStream.rdbuf()); //redirect std::cout to out.txt!
    }
    Log::LogLevel logLevel = Log::LogLevel::DEBUG;
    Log::setLogLevel(logLevel);
    Log::setLogOutputStream(&logFileStream);

    if (launchOptions.hasProjectFile()) {
        fileName = launchOptions.getProjectFile();
    } else {
        cout << "Project argument missing" << endl;
        cout << "using " << fileName << endl;
    }
    printStatements(fileName);

    cout << "SageTranform fortran : " << fileName << endl;

    SgProject *project = new SgProject(fileName);
    SgFile *file = &project->file(0);

    transform(file);
    //char c;
    //std::cin >> c;
    if (silent) {
        std::cout.flush();
        std::cout.rdbuf(coutbuf); //restore old buff
    }
    return 0;
}

/*
SgProject* project = new SgProject(projectFileName);
	SgFile * file;
	SgStatement * stmt, * next;
	for (int i = 0; i < project->numberOfFiles(); i++) {
		file = &(project->file(i));
		stmt = file->firstStatement();
		while (stmt != NULL) {			
			next = stmt->lexNext();
			switch (stmt->variant()) {
			case FOR_NODE:
				next = LoopSplitter::findLastLoopStatement(stmt)->lexNext();
				cout << "loop comment: " << stmt->comments();
				if (strncmp(stmt->comments(), "!PRG pass", 9)) {
					cout << "loop found" << endl;					
					vector<vector<int>> splitSchema = DependencyGraphBuilder::getValidSplit(stmt);
					cout << "split schema [";
					for (unsigned int ii = 0; ii < splitSchema.size(); ii++) {
						cout << "[";
						for (unsigned int iii = 0; iii < splitSchema.at(ii).size(); iii++) {
							cout << splitSchema.at(ii).at(iii) << ", ";
						}
						cout << '\b'<<'\b';
						cout << "], ";
					}
					cout << '\b'<<'\b';
					cout << "]" << endl;
					LoopSplitter::split(stmt, splitSchema);					
				}
				break;
			default: break;
			}
			stmt = next;
		}		
	}
	reprintSageProject(file);
	exit(0);
*/
