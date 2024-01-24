#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

struct CodePair {
    char plain;
    string code;
};
class Morse {
public:
    //vector <char> letter;
    //vector <string> code;
    Morse(string fname){
        ifstream f(fname);

        if(f.is_open()) {
            string s;
            while (getline(f, s)) {
                istringstream iss(s);
                int i = 0;
                string word;
                while (iss >> word) {
                    CodePair p;
                    if (word.size() == 1 && word[0]!='.' && word[0]!='-') { p.plain = (word[0]); }
                    else p.code = (word);
                    code_table.push_back(p);
                }

            }
        }
        else{cout << "Didnt open";}
    };
    string encode_a_letter(char c){
        for(int i=0; i<code_table.size();i++){
            if (code_table[i].plain==c){return code_table[i].code;}
        }
        return "****";
    };
    char decode_a_letter(string codes){
        for(int i=0; i<code_table.size();i++){
            if (code_table[i].code==codes){return code_table[i].plain;}
        }
        return '*';
    };
    string encode_a_word(string w){
        string enw;
        for(int i=0;i<w.size();i++){
            char c = w[i];
            enw += encode_a_letter(c);
            if(i==w.size()-1){return enw;}
            enw += "   ";
        }
    }

    string decode_a_word(string w){
        vector <string> morses = split(w, 3);
        string enw;
        for(int i=0;i<morses.size();i++){
            enw += decode_a_letter(morses[i]);
        }
        return enw;
    }

    string decode_a_word_seq(string w){
        vector <string> splitSeq = split(w,7);
        string totsen;
        for(int i=0;i<splitSeq.size();i++){
            totsen += decode_a_word(splitSeq[i]);
            if(i==splitSeq.size()-1){return totsen;}
            totsen += " ";
        }
        return totsen;
    }

    vector<string> split(const string& s, int n_sp) {
        vector<string> result;

        size_t start = 0;
        size_t end = s.find(string(n_sp, ' '));  

        while (end != string::npos) {
            result.push_back(s.substr(start, end - start));
            start = end + n_sp;
            end = s.find(string(n_sp, ' '), start);
        }

        result.push_back(s.substr(start));

        return result;
    }

private:
    vector<CodePair> code_table;
};
//
// Created by hughf on 03/12/2023.
//
