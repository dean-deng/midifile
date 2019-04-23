#ifndef STRING_PROCESSING_HPP_
#define STRING_PROCESSING_HPP_

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using std::vector;
using std::string;

vector<string> tokenize(string str, char delimiter) {
    vector<string> tokens;
    std::stringstream stream(str);
    string intermediate;
    while(getline(stream, intermediate, delimiter)) {
        if (intermediate.length() > 0) {
            tokens.push_back(intermediate);
        }
    }
    return tokens;
}

// returns true if c is one of
// {'A','B','C','D','E','F','G'}
bool is_note_char(char& c){
    return (c >= 'A' && c <= 'G');
}

bool is_note_number(char& c) {
  return (c >= '0' && c <= '9');
}

// assumes valid input
// creates new token every time it encounters one of
// {'A','B','C','D','E','F','G'}
vector<string> tokenize_chordstr(string str) {
    vector<string> tokens;
    unsigned int start = 0, end = 1;

    while (end < str.size()){
        while (!(is_note_char(str[end])) && end < str.size() ) {
            end++;
        }
        tokens.push_back(str.substr(start, end - start));
        start = end;
        end++;
    }

    tokens.push_back(str.substr(start));
    return tokens;
}
#endif