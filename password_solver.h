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
#include <mpi.h>

class password_solver{

public:
    password_solver(vector<string> &salts, vector<string> &encoded, vector<string> &dictionary, int world_size, int world_rank, int max_digits = 3){
        this->world_size = world_size;
        this->world_rank = world_rank;
        this->salts = salts;
        this->encoded = encoded;
        this->dictionary = dictionary;
        max_passwords = salts.size();
        max_num = power(10, max_digits)-1;
    }

    void solve_passwords(){
        //create new vector to store results
        vector<bool> password_found(encoded.size()); 
        //vector<string> perms;

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

                //receive coms
                //receive_communications(password_found);
            }
        }
    }

private:
    vector<string> salts, encoded, dictionary;
    int max_num, world_size, world_rank, max_passwords;

    /**
     * Hashes and compares a word for a permutation
     */
    void hash_word(vector<bool> &found, vector<string> &salts, vector<string> &encoded, string &word){
        for(int i = 0; i < salts.size(); i++){
            if(!found[i]){
                string encoded_word = crypt(word.c_str(), salts[i].c_str());
                if(encoded_word.compare(encoded[i]) == 0){
                    cout << "Pass " << i+1 << " found: " << word << endl;
                    found[i] = 1;
                    //communicate_found(i);
                    
                    break;
                }
            }
        }
    }

    /**
     * Communicates a word has been found with other threads
     */
    void communicate_found(int found){
        for(int i = 0; i < world_size; i++){
            if(i != world_rank) //only send to threads != this thread
                MPI_Send(&found, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    /**
     * Receives comms from other threads determining whether or not a pw has been found
     */
    void receive_communications(vector<bool> &found){
        for(int i = 0; i < world_size; i++){
            if(i != world_rank){
                int num = -1;

                MPI_Recv(&num, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                cout << num << endl;
                if(num != -1){
                    found[num] = 1;
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
