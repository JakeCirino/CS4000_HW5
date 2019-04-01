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
#include <sstream>
#include <iostream>
#include <string.h>

class password_solver{

public:
    password_solver(vector<string> &salts, vector<string> &encoded, vector<string> &dictionary, int world_size, int world_rank, int max_digits = 3){
        this->world_size = world_size;
        this->world_rank = world_rank;
        this->salts = salts;
        this->encoded = encoded;
        this->dictionary = dictionary;
        max_num = power(10, max_digits)-1;
    }

    void solve_passwords(){
        //create new vector to store results
        vector<bool> password_found(encoded.size()); 

        for(int wordi = world_rank; wordi < dictionary.size(); wordi += world_size){
            //store word
            string word = dictionary[wordi];
            for(int num = 0; num <= max_num; num++){
                //store number
                stringstream ss;
                ss << num;
                string num_string = ss.str();

                string p1 = num_string + word,
                    p2 = word + num_string;
                hash_word(password_found, salts, encoded, p1);
                hash_word(password_found, salts, encoded, p2);
            }
        }
    }

private:
    vector<string> salts, encoded, dictionary;
    int max_num, world_size, world_rank;

    void hash_word(vector<bool> &found, vector<string> &salts, vector<string> &encoded, string &word){
        for(int i = 0; i < salts.size(); i++){
            if(!found[i]){
                string encoded_word = crypt(word.c_str(), salts[i].c_str());
                if(encoded_word.compare(encoded[i]) == 0){
                    cout << "Pass " << i+1 << " found: " << word << endl;
                    found[i] = 1;
                    //TODO communicate openmpi
                    
                    break;
                }
            }
        }
    }

    int power(int base, int exp){
        if(exp == 1)
            return base;
        else
            return base * power(base, exp-1);
    }
};

#endif
