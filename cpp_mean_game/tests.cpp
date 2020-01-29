//
// Created by Dima on 07.12.2019.
//
#include <iostream>
#include "argparser.h"

int main(int argc, char* argv[]) {
    Config config = get_config(argc, argv);
    if(config->successful){
        std::cout << config->L << std::endl;
        std::cout << config->total_steps << std::endl;
        std::cout << config->drop_steps << std::endl;
        std::cout << config->fields_number << std::endl;
        std::cout << config->fields_directory << std::endl;
        std::cout << config->output_file << std::endl;
        std::cout << config->successful << std::endl;
    }
    delete config;
}