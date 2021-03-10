/*

*/

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>   // WinApi header

#ifndef GREEN
#define GREEN 10
#endif // !GREEN
#ifndef GREY
#define GREY 8
#endif // !GREY
#ifndef WHITE
#define WHITE 7
#endif // !WHITE

void tokenize(std::string& str, char delim, std::vector<std::string>& out) {
    size_t start, end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

bool isPathTemplate(std::string const path) {
    if (path.size() < 2) return false;
    return path[0] == '%' && path[path.size() - 1] == '%';
}

void validatePath(std::string path) {
    using std::cout;
    using std::endl;
    using std::string;
    using std::vector;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char* buf = nullptr;
    size_t sz = 0;
    if (_dupenv_s(&buf, &sz, path.c_str()) == 0 && buf != nullptr)
    {
        //printf("EnvVarName = %s\n", buf);
        char d = ';';
        vector<string> a;
        std::string s(buf);
        tokenize(s, d, a);
        free(buf);
        for (auto it : a) {
            if (isPathTemplate(it)) {
                SetConsoleTextAttribute(hConsole, WHITE);
                cout << it << endl;
                s =  it.substr(1, it.size() - 2);
                validatePath(s);
            }
            else {
                SetConsoleTextAttribute(hConsole, GREEN);
                cout << it << endl;
                SetConsoleTextAttribute(hConsole, WHITE);
            }
        }
    }
    else {
        cout << "EnvNotFound " << endl;
    }
}

// test function (can be omitted)
int main(int argc, char** argv) {
    if (argc == 2) {
        std::string s(argv[1]);
        validatePath(s);
    }
}



