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
#include <mpi.h>
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
    //init mpi
    MPI_Init(&argc, &argv);

    //get number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    //get rank of process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    //output number of threads for reference
    if(world_rank == 0)
        cout << world_size << " threads initialized" << endl;
    cout << world_rank << endl;

    //load files
    string enc_filename = "enc_passwords",
        salts_filename = "salts",
        words_filename = "words";
    if(argc == 4){
        enc_filename = argv[1];
        salts_filename = argv[2];
        words_filename = argv[3];
    }

    //load data
    vector<string> encoded_passwords = load_strings(enc_filename);
    vector<string> salts = load_strings(salts_filename);
    vector<string> dictionary = load_strings(words_filename);

    //solve passwords
    password_solver solver(salts, encoded_passwords, dictionary, world_size, world_rank);
    string output = solver.solve_passwords();

    if(world_rank == 0){
        //this thread receives from other threads
        cout << output;
        for(int i = 0; i < world_size; i++){
            MPI_Recv(&output, 1, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            cout << output;
        }
    }else{
        //send to thread 0
        MPI_Send(output.c_str(), 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    //finalize mpi
    MPI_Finalize();

    return 0;
}