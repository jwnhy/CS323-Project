#include "spp.h"

using namespace std;
unordered_map<string, string> definitions;

void error(const char *format, const char *msg) {
    printf(format, msg);
    exit(1);
}

list<list<string>> into_lines(istream &fin) {
    list <list<string>> tokens;
    stringstream token_stream;
    string token_line;
    string token;
    token_stream << fin.rdbuf();
    while (getline(token_stream, token_line)) {
        if(token_line.empty())
            continue;
        list <string> line = list<string>();
        replace(token_line.begin(), token_line.end(), '\t' , ' ');
        stringstream line_stream(token_line);
        while(getline(line_stream, token, ' ')) {
            if(token.length() > 0)
                line.push_back(token);
        }
        tokens.push_back(line);
    }
    tokens.remove_if([](auto x) -> bool { return x.empty(); });
    return tokens;
}

list<list<string>> file_inclusion(list<list<string>> lines) {
    for(auto line = lines.begin(); line != lines.end(); line++) {
        string token = (*line).front();
        if (token == "#include") {
            (*line).pop_front();
            string filename = (*line).front();
            (*line).pop_front();
            if(filename.front() != '"' || filename.back() != '"')
                error("illegal inclusion file format, %s", filename.c_str());
            else {
                filename = filename.substr(1, filename.length()-2);
                fstream including(filename);
                list<list<string>> including_tokens = file_inclusion(into_lines(including));
                auto next_line = ++line;
                line--;
                lines.splice(next_line, including_tokens);
            }
            (*line).clear();
        }
    }
    lines.remove_if([](auto x) -> bool { return x.empty(); });
    return lines;
}
string to_str(list<list<string>> lines) {
    string res;
    for (auto line: lines) {
        for (auto word: line) {
            res = res + word + " ";
        }
        res += "\n";
    }
    return res;
}