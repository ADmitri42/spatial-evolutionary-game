//
// Created by Dima on 07.12.2019.
//
#pragma once


#ifndef CPP_MEAN_GAME_ARGPARSER_H
#define CPP_MEAN_GAME_ARGPARSER_H
#include <string>

typedef struct {
    int total_steps;
    int drop_steps;
    int L;
    int fields_number;
    std::string output_file;
    std::string fields_directory;
    bool successful;
    bool help;
} pConfig;

typedef pConfig* Config;

Config get_config(int argc, char* argv[]);

#endif //CPP_MEAN_GAME_ARGPARSER_H
