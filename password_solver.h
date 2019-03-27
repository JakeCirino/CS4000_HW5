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

class password_solver{

public:
    password_solver(vector<string> &salts, vector<string> &encoded, vector<string> &dictionary, int max_digits = 3){
        this->salts = salts;
        this->encoded = encoded;
        this->dictionary = dictionary;
        max_num = power(10, max_digits)-1;
    }

    void solve_passwords(){
        //create new vector to store results
        vector<string> passwords(encoded.size());
        int dic_size = dictionary.size();

        //loop through number
        for(int num = -1; num <= max_num; num++){
            //first word
            for(int word1i = 0; word1i < dic_size; word1i++){
                string word1 = dictionary[word1i];
                //second word, no second word at -1
                for(int word2i = -1; word2i < dic_size; word2i++){
                    string word2 = "";
                    //get number position, 0 = before first, 1 = after first, 2 = after second
                    int pos_max = 2;
                    if(word2i == -1)
                        pos_max = 1;
                    else
                        word2 = dictionary[word2i];
                    //determine pass with/without num
                    if(num != -1){
                        //determine number position
                        for(int num_pos = 0; num_pos <= pos_max; num_pos++){
                            //complete pass
                            string pass;

                            //convert number to string
                            string num_string;
                            stringstream ss;
                            ss << num;
                            num_string = ss.str();

                            if(num_pos == 0)
                                pass += num_string;

                            pass += word1;

                            if(num_pos == 1)
                                pass += num_string;

                            pass += word2;

                            if(num_pos == 2)
                                pass += num_string;

                            //TODO do shit
                            cout << pass << endl;
                        }
                    }else{
                        //there is no number, combine the words
                        string pass = word1 + word2;

                        //TODO do shit
                        cout << pass << endl;
                    }
                }
            }
        }
    }

private:
    vector<string> salts, encoded, dictionary;
    int max_num;

    int power(int base, int exp){
        if(exp == 1)
            return base;
        else
            return base * power(base, exp-1);
    }
};

#endif
