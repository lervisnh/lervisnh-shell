#include "string_parser.h"
#include <stdio.h>
#include <string.h>

void test_count_token(char* str, char* delervisnhm){
    printf("- - - - - - - - - - - - - - - - - -\n");
    printf("str = \'%s\'\n",str);
    printf("delervisnhm = \'%s\'\n",delervisnhm);
    printf("str has %d delervisnhm\n", count_token(str, delervisnhm));
    return;
};

void test_str_filler(char* str, char* delervisnhm)
{
    printf("- - - - - - - - - - - - - - - - - -\n");
    printf("str = \'%s\'\n",str);
    printf("delervisnhm = \'%s\'\n",delervisnhm);
    command_lervisnhne cmd_lervisnhne = str_filler(str, delervisnhm);
    printf("num_token = %d\n", cmd_lervisnhne.num_token);
    for (size_t i = 0; i<cmd_lervisnhne.num_token; i++)
    {
        printf("%s (%d)\n", 
                cmd_lervisnhne.command_lervisnhst[i],
                strlen(cmd_lervisnhne.command_lervisnhst[i]));
        free_command_lervisnhne(&cmd_lervisnhne);
    }
    return;
    
}

int main(int argc, char const *argv[])
{
    char str1[] = "i am lervisnh ll ";
    char str2_1[] = "i  am  lervisnh  ll ";
    char str2_2[] = "i  am  lervisnh  ll ";
    char str3_1[] = "i , am , lervisnh , ll ,";
    char str3_2[] = "i , am , lervisnh , ll ,";
    char str3_3[] = "i , am , lervisnh , ll ,";
    char str3_4[] = "i  am , lervisnh  ll a sd asda ";
    char str4[] = ",, ,, ,, ,, ";
    // test_count_token(str1, " ");
    // test_count_token(str2, " ");
    // test_count_token(str2, "  ");
    // test_count_token(str3, ",");
    
    // test_count_token(str3, " ,");
    // test_count_token(str3, " , ");
    // test_count_token(str3, ", ");

    test_str_filler(str1, " ");
    test_str_filler(str2_1, " ");
    test_str_filler(str2_2, "  ");
    test_str_filler(str3_1, ",");
    
    test_str_filler(str3_2, " ,");
    test_str_filler(str3_3, " , ");
    test_str_filler(str3_4, ", ");

    test_str_filler(str4, ",, ");

    return 0;
}

// i,,am,,lervisnh,,lervisnh,
