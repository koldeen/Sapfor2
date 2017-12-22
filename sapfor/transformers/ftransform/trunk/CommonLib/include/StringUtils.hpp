#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace SageTransform {

    namespace StringUtils {

        bool startsWith(string const &str, string const &prefix);

        bool endsWith(string const &str, string const &ending);

        vector<string> &split(const string &s, char delim, vector<string> &elems);

        vector<string> split(const string &s, char delim);

        string unsplit(const vector<string> &v, char delim);

        vector<string> tokenize(const string &s, char delim);

        vector<string> tokenizeRespectParenthesis(const string &s, char delim);

        void inplaceCutElement(char *cstring, char splitDelim, int removedIndex);

        void removeLineStartingWith(char *lines, const string &prefix);

        // trim from left
        inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v") {
            s.erase(0, s.find_first_not_of(t));
            return s;
        }

        // trim from right
        inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v") {
            s.erase(s.find_last_not_of(t) + 1);
            return s;
        }

        // trim from left & right
        inline std::string& trim(std::string& s, const char* t) {
            return ltrim(rtrim(s, t), t);
        }

        // trim from left & right
        inline std::string& trim(std::string& s) {
            return trim(s, " \t\n\r\f\v");
        }
    }
}
#endif //STRING_UTILS_HPP

