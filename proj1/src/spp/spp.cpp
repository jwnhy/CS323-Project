#include "spp.h"

using namespace std;
unordered_map<string, string> definitions;

void error(const char *format, const char *msg) {
    printf(format, msg);
    exit(1);
}

list<list<string>> into_lines(fstream &fin) {
    list <list<string>> tokens;
    stringstream token_stream;
    string token_line;
    string token;
    token_stream << fin.rdbuf();
    fin.close();
    while (getline(token_stream, token_line)) {
        list <string> line = list<string>();
        replace(token_line.begin(), token_line.end(), '\t' , ' ');
        stringstream line_stream(token_line);
        while(getline(line_stream, token, ' ')) {
            if(token.length() > 0)
                line.push_back(token);
        }
        tokens.push_back(line);
    }
    return tokens;
}

list<list<string>> read_definition(list<list<string>> lines) {
    for(auto & line : lines) {
        auto iter = line.begin();
        if (*iter == "#define") {
            string replacement;
            string macro = *(++iter);
            if((++iter)!=line.end())
                replacement = *iter;
            definitions[macro] = replacement;
            line.clear();
        }
    }
    lines.remove_if([](auto x) -> bool { return x.empty(); });
    return lines;
}

list<list<string>> replace_definition(list<list<string>> lines) {
    for(auto &line : lines) {
        for (auto &token : line) {
            auto iter = definitions.find(token);
            if (iter != definitions.end()) {
                string new_token = iter->second;
                token = new_token;
            }
        }
    }
    lines.remove_if([](auto x) -> bool { return x.empty(); });
    return lines;
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

int main(int argc, char *argv[]) {
    char *filepath = argv[1];
    fstream code_file(filepath);
    list<list<string>> k = into_lines(code_file);
    k = file_inclusion(k);
    k = read_definition(k);
    k = replace_definition(k);
}