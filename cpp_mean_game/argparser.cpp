//
// Created by Dima on 07.12.2019.
//

#include "argparser.h"
#include <iostream>
#include <sstream>

Config set_field(std::string arg, Config config, bool mess = true){
    std::stringstream ss;
    config->successful = true;

    if(arg.rfind("-L", 0) == 0){
        int L;
        ss << arg.substr(2, arg.size());
        if(ss >> L){
            config->L = L;
        } else {
            config->successful = false;
            std::cerr << "Expected integer, got " << arg << std::endl;
        }
    }else if(arg.rfind("-NSteps", 0) == 0){
        int NSteps;
        ss << arg.substr(7, arg.size());
        if(ss >> NSteps){
            config->total_steps = NSteps;
        } else {
            config->successful = false;
            std::cerr << "Expected integer, got " << arg << std::endl;
        }
    }else if(arg.rfind("-NDrop", 0) == 0){
        int NDrop;
        ss << arg.substr(6, arg.size());
        if(ss >> NDrop){
            config->drop_steps = NDrop;
        } else {
            config->successful = false;
            std::cerr << "Expected integer, got " << arg << std::endl;
        }
    }else if(arg.rfind("-NFields", 0) == 0){
        int NFields;
        ss << arg.substr(8, arg.size());
        if(ss >> NFields){
            config->fields_number = NFields;
        } else {
            config->successful = false;
            std::cerr << "Expected integer, got " << arg << std::endl;
        }
    }else if(arg.rfind("-h", 0) == 0){
        config->help = true;
        config->successful = false;

    }else if (mess){
        config->successful=false;
        std::cerr << "Unknown parameter " << arg << std::endl;
    } else {
        config->successful=false;
    }
    return config;
}

void help_message(std::string prog_name){
    std::cout <<  "Usage: " << prog_name << " [OPTIONS] output_file" << std::endl;
    std::cout << "Options: " << std::endl;
    std::cout << "\t-L{integer} - Size of the field\n\t-NSteps - Number of steps" << std::endl;
    std::cout << "\t-NDrop - number of steps, which would be dropped from output file" << std::endl;
    std::cout << "\t-NFields - number of fields in directory 'fields/' in form 'field_{L}_{n}.npy'" << std::endl;
}

std::string err_message(std::string prog_name){
    std::cerr << "Wrong usage: " << prog_name << " [OPTIONS] output_file" << std::endl;
    std::cerr << "-h will help you" << std::endl;
}

Config get_config(int argc, char* argv[]){
    Config config = new pConfig;
    config->total_steps = 16000;
    config->drop_steps = 8000;
    config->L = 400;
    config->fields_number = 40;
    config->successful = true;
    config->fields_directory = "fields";
    config->help = false;

    if(argc == 1){
        err_message(argv[0]);
        config->successful = false;
        return config;
    }else if(argc == 2){
        set_field(argv[1], config);
        if(config->help){
            help_message(argv[0]);
            config->successful = false;
            return config;
        } else if(config->successful) {
            err_message(argv[0]);
            config->successful = false;
            return config;
        } else {
            config->output_file = argv[1];
        }
    }else{
        for(int i = 1; i < argc; i++){

            set_field(argv[i], config, !(i == argc-1)   );

            if(config->help){
                help_message(argv[0]);
                config->successful = false;
                break;
            } else if (!config->successful && i == argc - 1){
                config->successful = true;
                config->output_file = argv[i];
            } else if (config->successful && i == argc - 1){
                err_message(argv[0]);
                config->successful = false;
            } else if (!config->successful){
                break;
            }
        }
    }

    return config;
}