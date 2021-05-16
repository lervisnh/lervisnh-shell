#pragma once

#ifndef __common_base_h
#define __common_base_h

#define BUFSIZE 0x10000

#define REDIRECT_STDOUT_BEGIN(target) \
        FILE* fr=freopen(target, "w", stdout);\
        // if(NULL!=fr) \
        //     printf("Redirect stdout to %s\n", target); \
        // else \
        //     printf("Error : redirect stdout to %s faield\n", target); 
#define FLUSH_STDOUT fflush(stdout);
#define REDIRECT_STDOUT_END freopen("/dev/tty", "w", stdout); //fclose(stdout);

#define SAFE_MALLOC(ptr, type, num) \
        ptr = (type*)malloc((sizeof(type)*(num)));\
        if (NULL == ptr){ \
            printf("Error : SAFE_MALLOC failed\n"); \
            exit(EXIT_FAILURE); \
        } else { \
            memset((void*)ptr, 0, (sizeof(type)*(num)));  \
        }
#define SAFE_FREE(ptr)\
        if (NULL!=ptr) { \
            free(ptr); \
        }

#endif // __common_base_h