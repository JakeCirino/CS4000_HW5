/*********************************
 * Filename: main.cc
 * Author: Jake Cirino
 * Purpose: Entrypoint for program to run
 *********************************/
#include <string>
#include <vector>
#include <ifstream>
#include <unistd.h>
using namespace std;

vector<string> encoded_passwords, salts, dictionary;

/**
 * Loads strings from a file into a vector
 */
vector<string> load_strings(string &filename){
    vector<string> vec;
    ifstream file(filename);
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            vec.push_back(line);
        }
        file.close();
    }
    return vec;
}

int main(int argc, char *argv[]){
    //load files
    string enc_filename = "enc_passwords",
        salts_filename = "salts",
        words_filename = "words";
    if(argc == 4){
        enc_filename = argv[1];
        salts_filename = argv[2];
        words_filename = argv[3];
    }

    encoded_passwords = load_strings(enc_filename);
    salts = load_strings(salts_filename);
    dictionary = load_string(words_filename);
    return 1;
}