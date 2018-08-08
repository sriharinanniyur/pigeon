// Written by Srihari Nanniyur.

#ifndef __mail_h__
#define __mail_h__
#include <stdio.h>

#define HEADER 0
#define BODY   1

#define MAXLEN 200

extern char USERNAME[MAXLEN];
extern char PASSWORD[MAXLEN];

/* fetch_mail() - display contents of an IMAP mail request. */
/* Parameters: username, password, section of message(HEADER or BODY), message num */
int fetch_mail(char *, char *, int, int);

/* fetch_headers() - wrapper over fetch_mail() that writes mail headers to file HEADERS. */
void fetch_headers(char *, char *);

/* send_mail() - SMTP mail sending function. */
/* Parameters: username, password, dest. address, CC string, FILE pointer to read message from */
int send_mail(const char *, const char *, const char *, const char *, FILE *);

#endif
