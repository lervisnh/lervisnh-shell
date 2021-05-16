#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_parser.h"
#include "common_base.h"

#define _GUN_SOURCE

int count_token (char* str, const char* delim)
{
	int len = strlen (str);
	if (str == NULL || len<1) {
		printf ("Empty string\n");
		return 0;
	}
	
	int n_token = 0;
	int delim_len = strlen(delim);
	for (size_t i = 0; i < len; i++) {
		for (size_t j = 0; j < delim_len; j++) {
			if (str[i]==delim[j]) {
				n_token++;
				break;
			}
		}
	}
	return n_token+1;
}

command_line str_filler (char* str, const char* delim)
{
	
	if (str[strlen(str)-1]=='\n') {
		str[strlen(str)-1] = '\0';
	}
	command_line command;
	
	int num_token = count_token(str, delim);
	SAFE_MALLOC(command.command_list, char*, num_token);
	char* rest = str;
	int valid_token_num=0;
	for (int i = 0; i < num_token; i++) {
		char* token = strtok_r(rest, delim, &rest);
		if (NULL != token) {
			SAFE_MALLOC(command.command_list[i], char, strlen(token) + 1);
			strcpy(command.command_list[i], token);
			valid_token_num++;
		} else {
			command.command_list[i] = NULL;
		}
	}
	command.num_token = valid_token_num;
	return command;
}


void free_command_line(command_line* command) {
	for (int i = 0; i<command->num_token; i++) {
		SAFE_FREE(command->command_list[i]);
	}
	SAFE_FREE(command->command_list);
}
