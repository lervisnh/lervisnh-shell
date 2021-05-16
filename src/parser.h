#pragma once

#ifndef _parser_h
#define _parser_h

#include "common_base.h"
#include "string_parser.h"
#include "command.h"
#include <string.h>
#include <stdio.h>

enum CMD {
    INVALID=-1, EXIT,
    LS, PWD, MKDIR, CD, CP, MV, RM, CAT
};

int cmd_status(char* cmd){
    if(strcmp(cmd, "ls")==0 || strcmp(cmd, "ls\n")==0 ){
        return LS;
    }
    else if(strcmp(cmd, "pwd")==0 || strcmp(cmd, "pwd\n")==0 ){
        return PWD;
    }
    else if(strcmp(cmd, "cd")==0 || strcmp(cmd, "cd\n")==0 ){
        return CD;
    }
    else if(strcmp(cmd, "mkdir")==0 || strcmp(cmd, "mkdir\n")==0 ){
        return MKDIR;
    }
    else if(strcmp(cmd, "cp")==0 || strcmp(cmd, "cp\n")==0 ){
        return CP;
    }
    else if(strcmp(cmd, "mv")==0 || strcmp(cmd, "mv\n")==0 ){
        return MV;
    }
    else if(strcmp(cmd, "rm")==0 || strcmp(cmd, "rm\n")==0 ){
        return RM;
    }
    else if(strcmp(cmd, "cat")==0 || strcmp(cmd, "cat\n")==0 ){
        return CAT;
    }
    else if(strcmp(cmd, "exit")==0 || strcmp(cmd, "exit\n")==0 ){
        return EXIT;
    } else {
        return INVALID;
    }
};

int parser_help(command_line* cmd, int* continue_parser){
    int exitFlag = 0;
    if(cmd->num_token==0) return exitFlag;
    switch (cmd_status(cmd->command_list[0])) {
    case INVALID:
        printf("Error! Unrecognized command: %s\n", cmd->command_list[0]);
        break;
    case EXIT:
        printf("Exit lervisnh-shell. Bye ~\n");
        exitFlag = 1;
        break;
    case LS:
        if(cmd->num_token==1){
            listDir();
        } else { // cmd->num_token >= 2
            if(cmd_status(cmd->command_list[1])==LS){
                printf("Error! Incorrect syntax. No control code found\n");
                (*continue_parser) = 0;
            } else {
                printf("Error! Unsupported parameters for command: ls\n");
            }
        }
        break;
    case PWD:
        if(cmd->num_token==1){
            showCurrentDir();
        } else {
            printf("Error! Unsupported parameters for command: pwd\n");
        }
        break;
    case MKDIR:
        if(cmd->num_token>1){
            for (size_t i = 1; i < cmd->num_token; i++) {
                makeDir(cmd->command_list[i]);
            }
        } else {
            printf("mkdir usage: mkdir <name>\n");
        }
        break;
    case CD:
        if(cmd->num_token>1){
            changeDir(cmd->command_list[1]);
        } else {
            printf("cd usage: cd <directory>\n");
        }
        break;
    case CP:
        if(cmd->num_token>2){
            for (size_t i = 1; i < cmd->num_token-1; i++) {
                copyFile(cmd->command_list[i], 
                         cmd->command_list[cmd->num_token-1]);
            }
        } else {
            printf("cp usage: cp <src> <dst>\n");
        }
        break;
    case MV:
        if(cmd->num_token>2){
            for (size_t i = 1; i < cmd->num_token-1; i++) {
                moveFile(cmd->command_list[i], 
                         cmd->command_list[cmd->num_token-1]);
            }
        } else {
            printf("mv usage: mv <src> <dst>\n");
        }
        break;
    case RM:
        if(cmd->num_token>1){
            for (size_t i = 1; i < cmd->num_token; i++) {
                deleteFile(cmd->command_list[i]);
            }
        } else {
            printf("rm usage: rm <filename>\n");
        }
        break;
    case CAT:
        if(cmd->num_token>1){
            for (size_t i = 1; i < cmd->num_token; i++) {
                displayFile(cmd->command_list[i]);
            }
        } else {
            printf("cat usage: cat <filename>\n");
        }
        break;
    }
    return exitFlag;
};

int parser(char* line){
    int exitFlag = 0;
    int continue_parser = 1;
    command_line multi_cmds = str_filler(line, ";");
    for (size_t i = 0; i < multi_cmds.num_token; i++) {
        command_line one_cmd = str_filler(multi_cmds.command_list[i], " ");
        exitFlag = parser_help(&one_cmd, &continue_parser);
        free_command_line(&one_cmd);
        if(exitFlag || 0==continue_parser) break;
    }
    free_command_line(&multi_cmds);
    return exitFlag;
};

#endif // _parser_h