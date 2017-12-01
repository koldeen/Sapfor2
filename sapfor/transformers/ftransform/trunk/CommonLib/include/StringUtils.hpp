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
    }
}
#endif //STRING_UTILS_HPP

