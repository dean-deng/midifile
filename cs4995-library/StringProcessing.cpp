#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "StringProcessing.hpp"

using std::vector;
using std::string;

namespace smf {

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

// assumes valid input
vector<string> tokenizeChordstr(string str) {
    // Token containing '/' means we're dealing with a chord
    // split using / as a delimiter
    if (str.find('/') != string::npos) {
        return tokenize(str, '/');
    }

    vector<string> tokens;
    unsigned int start = 0, end = 1;
    // Create new token for every BasePitch ('A' - 'G').
    while (end < str.size()){
        while (!(isBasePitch(str[end])) && end < str.size() ) {
            end++;
        }
        tokens.push_back(str.substr(start, end - start));
        start = end;
        end++;
    }
    if (start < str.size()) {
        tokens.push_back(str.substr(start));
    }
    return tokens;
}

vector<Note> parseNotes(string s) {
    vector<Note> result;

    vector<string> tokens = tokenize(s, ' ');
    if (tokens.size() == 0) {
        return result;
    }

    // reserve space >= the amount needed
    result.reserve(tokens.size());

    float noteLength = DEFAULT_LENGTH;
    auto it = tokens.begin();
    while (it < tokens.end()) {
        string tok = *it;
        Note note{noteLength};

        if (tok[tok.length() - 1] == '(') {
            // Start specifying note length
            int subdivision = std::stoi(tok.substr(0, tok.length() - 1));
            noteLength = WHOLE_LENGTH / subdivision;
            ++it;
        } else if (tok.compare(")") == 0) {
            // Stop specifying note length
            noteLength = DEFAULT_LENGTH;
            ++it;
        } else {
            if (it->compare(REST) != 0) {
                // Construct a Note using vector of pitches
                vector<string> pitchTokens = tokenizeChordstr(tok);
                for (auto& pitchToken: pitchTokens) {
                    note << Pitch{pitchToken};
                }
            }
            while(++it < tokens.end() && it->compare(EXTEND) == 0) {
                note.setLength(note.getLength() + noteLength);
            }
            result.push_back(note);
        }
    }

    return result;
}

} // namespace smf
