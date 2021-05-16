#include "parser.h"
#include <stdlib.h>

void interactive(){
    char line [BUFSIZE] = {0};
    for (;;)
    {
        memset(line, 0, BUFSIZE);
        printf(">>> ");
        fgets(line, BUFSIZE, stdin);
        if(parser(line)) break;
    };
    return;
};

void outputToFile(const char* cmds_file,
                  const char* output){
    REDIRECT_STDOUT_BEGIN(output)
    FILE *inFPtr = fopen(cmds_file, "r");
    if (inFPtr == NULL) exit(EXIT_FAILURE);
    int exitFlag = 0;
    char * buf = NULL;
    size_t len = 0;
    ssize_t read;
    while (-1!=(read =  getline(&buf, &len, inFPtr) ))
    {
        exitFlag = parser(buf);
        memset(buf, 0, sizeof buf);
        if(exitFlag) break;
    }
    if(buf) free(buf);
    fclose(inFPtr);
    FLUSH_STDOUT
    REDIRECT_STDOUT_END
    return;
};


int main(int argc, char const *argv[])
{
    if (argc==1) {
        interactive();
    } else if (argc==3 &&
               strcmp(argv[1],"-f")==0)
    {
       outputToFile(argv[2], "ouput.txt");
    } else {
        printf("Usage:\t[Interactive Mode] %s\n", argv[0]);
        printf("\t[File Mode] %s -f <filename>\n", argv[0]);
    }
    return 0;
}
