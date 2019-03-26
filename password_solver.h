/*********************************
 * Filename: password_solver.h
 * Author: Jake Cirino
 * Purpose: Class that solves passwords given hashes,
 * salts and a dictionary
 *********************************/
#ifndef PWSOLVER_H
#define PWSOLVER_H

using namespace std;
#include <vector>
#include <string>
#include <unistd.h>
#include <tgmath.h>
#include <sstream>

class password_solver{

public:
    password_solver(vector<string> &salts, vector<string> &encoded, vector<string> &dictionary, int max_digits = 3){
        this->salts = salts;
        this->encoded = encoded;
        this->dictionary = dictionary;
        max_num = pow(10, max_digits)-1;
    }

    vector<string> solve_passwords(){
        //create new vector to store results
        vector<string> passwords(encoded.size());

        //loop through num of words, start of permutation
        int passes_found = 0;
        while(passes_found < encoded.size()){
            string cur_pass;
            for(int words = 1; words <= 2; words++){
                //determine number before word
                string num1_str;
                for(int num1 = -1; num1 <= max_num; num1++){
                    if(num1 != -1){
                        stringstream out;
                        out << num1;
                        num1_str = out.str();
                    }
                }

                //determine number after word
                string num2_str;
                for(int num2 = -1; num2 <= max_num; num2++){
                    if(num2 != -1){
                        stringstream out;
                        out << num2;
                        num2_str = out.str();
                    }
                }

                //loop through possible dictionary words for current word
                string this_word;
                for(int dic_val = 0; dic_val < dictionary.size(); dic_val++){
                    this_word = dictionary[dic_val];
                }
            }
        }
    }

private:
    vector<string> salts, encoded, dictionary;
    int max_num;
};

#endif