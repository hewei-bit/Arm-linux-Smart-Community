#ifndef READRFIDID_H
#define READRFIDID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <termios.h>
#include <unistd.h>
#include <strings.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define USART1 "/dev/ttySAC1"


extern void init_tty(int fd);
extern unsigned char calBCC(unsigned char* buf,int n);
extern int PiccRequest(int fd);
extern int PiccAnticoll(int fd);
int readCardId();

#ifdef __cplusplus
}
#endif
#endif // READRFIDID_H
