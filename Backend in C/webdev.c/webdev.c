/* webdev.c */
#include "webdev.h"

bool continuation;

Request *mkrequest(int32 s) {
    return (Request *)0;
}

State *mkstate(int32 s, pid_t pid) {
    State *state;
    int16 size;

    size = sizeof(struct s_state);
    state = (State *)malloc($i size);
    if (!state)
        return (State *)0;

    zero($8 state, size);
    state->s = s;
    state->pid = pid;

    return state;
}

void syslogger(int16 priority, int8 *str) {
    openlog("webdev.c", 0, LOG_SYSLOG);
    syslog($i priority, "%s", str);
    closelog();

    return;
}

int32 setupserver(int8 *host, int16 port) {
    struct sockaddr_in sock;
    int16 n;
    int32 s;

    s = $2 socket(AF_INET, SOCK_STREAM, 0);
    assert(s > 0);

    sock.sin_family = AF_INET;
    sock.sin_port = htons($i port);
    sock.sin_addr.s_addr = inet_addr($c host);

    n = $6 bind(s, (struct sockaddr *)&sock, sizeof(sock));
    assert(!n);

    n = $6 listen(s, 50);
    assert(!n);

    return s;
}

int8 mainloop(int32 s) {
    struct sockaddr_in sock;
    int8 *str, *host;
    int8 buf[128];
    int16 port;
    int32 c;
    unsigned int size;
    State *state;
    pid_t pid;
    Request *req;

    size  = sizeof(struct sockaddr);
    c = $6 accept($i s, (struct sockaddr *)&sock,
        (unsigned int *)&size);
    
    if (c > 0); else {
        str = $8 "accept() failed";
        logwarning(str);
        sleep(1);

        return 1;
    }

    if (pid = (fork())) {
        host = todotted(sock.sin_addr.s_addr);
        port = nstoh($6 sock.sin_port);
        zero(buf, 128);

        snprintf($c buf, 127,
            "Client connected from %s:%d",
            $c host, $i port);
        log(buf);

        state = mkstate(s, pid);
        if (!state) {
            logerr($8 "Unable to create state");
            return 1;
        }
        state->ip = host;
        state->port = port;

        return 0;
    }
    else {
        req = mkrequest(s);
        if (!req) {
            close(s);
            zero(buf, 128);
            snprintf($c buf, 127,
                "Unable to parse request with ID %d",
                s);
            logerr(buf);

            exit(-1);
        }
    }
}

void usage(int8* arg) {
    fprintf(stderr, "Usage: %s <port> [host]\n",
        $c arg);
    exit(-1);

    return;
}

int main(int argc, char *argv[]) {
    int8 ret;
    int8 buf[128];
    int8 *host, *port8;
    int16 port;
    int32 s;

    if (argc < 2)
        usage($8 *argv);
    else if (argc == 2) {
        port8 = $8 argv[1];
        port = $6 atoi($c port8);
        host = $8 "0.0.0.0";
    }
    else {
        port8 = $8 argv[1];
        host = $8 argv[2];
        port = $6 atoi($c port8);
    }

    s = setupserver(host, port);
    zero(buf, 128);
    snprintf($c buf, 127,
        "Server successfully listening to %s:%d.",
        $c host, $i port);
    log(buf);

    continuation = true;
    while (continuation)
        ret = mainloop(s);
    close(s);

    return ret;
}