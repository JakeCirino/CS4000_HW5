/*********************************
 * Filename: main.cc
 * Author: Jake Cirino
 * Purpose: Entrypoint for program to run
 *********************************/
using namespace std;
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
//#include <mpi.h> TODO implement parallel
#include <unistd.h>
#include "password_solver.h"

/**
 * Max int digits in password
 */
const int max_digits = 3;
vector<string> encoded_passwords, salts, dictionary;

/**
 * Loads strings from a file into a vector
 */
vector<string> load_strings(string &filename){
    vector<string> vec;
    ifstream file(filename.c_str());
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

    vector<string> encoded_passwords = load_strings(enc_filename);
    vector<string> salts = load_strings(salts_filename);
    vector<string> dictionary = load_strings(words_filename);

    password_solver solver(salts, encoded_passwords, dictionary);
    solver.solve_passwords();

    return 1;
}