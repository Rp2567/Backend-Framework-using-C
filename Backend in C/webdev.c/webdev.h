/* webdev.h */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <syslog.h>
#include "birchutils.h"

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

enum e_method {
    GET = 1,
    POST = 2
};
typedef enum e_method Method;

/* Temporary! */
typedef bool Header;
typedef bool Cookie;

struct s_request {
    Method method; // GET, PUT, HEAD ..
    int8 *path; // /index.html
    Header *headers;
    Cookie *cookies;
};
typedef struct s_request Request;

struct s_state {
    int32 s;
    pid_t pid;

    int8 *ip;
    int16 port;
    Request *req;
};
typedef struct s_state State;

#define $c (char *)
#define $8 (int8 *)
#define $6 (int16)
#define $2 (int32)
#define $4 (int64)
#define $i (int)

#define log(x)          syslogger(LOG_INFO, x)
#define logwarning(x)   syslogger(LOG_WARNING, x)
#define logerr(x)       syslogger(LOG_ERR, x)

Request *mkrequest(int32);
State *mkstate(int32,pid_t);
void syslogger(int16,int8*);
int32 setupserver(int8*,int16);
int8 mainloop(int32);
void usage(int8*);
int main(int,char**);






