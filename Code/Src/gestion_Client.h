#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>


#define BUFFERSIZE 300


int flag_Client;


void catchCtrlC();

void stop(int sig);

void viderBuffer();

void printMenuClient(void);



