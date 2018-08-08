// Written by Srihari Nanniyur.

#include "mail.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <curl/curl.h>

char USERNAME[MAXLEN];
char PASSWORD[MAXLEN];

int fetch_mail(char *username, char *password, int section, int num)
{
    CURL *curl;
    FILE *stream;
    CURLcode res = CURLE_OK;
    char url[MAXLEN];
    sprintf(url, "%s%.5d%s", "imaps://imap.gmail.com:993/INBOX/;UID=", num,
        (section ? "/;SECTION=1" : "/;SECTION=HEADER.FIELDS%20(DATE%20FROM%20TO%20SUBJECT)"));
    if ((stream = fopen((section ? "data/DATA" : "HEADERS"), (section ? "w" : "a+"))) == NULL)
        return 0;
    fprintf(stream, "message %d\n", num);
    printf("processing message %d\n", num);
    if (curl = curl_easy_init()) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_URL, url);
#ifdef SKIP_PEER_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
#ifdef SKIP_HOSTNAME_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "No additional mail found: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
    fclose(stream);
    return (int) res;
}

void fetch_headers(char *username, char *password)
{
    int i;
    for (i = 1; fetch_mail(username, password, HEADER, i) == CURLE_OK; i++)
        ;
    system("dos2unix HEADERS");
}

int send_mail(const char *username, const char *password,
               const char *to, const char *cc, FILE *fp)
{
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;

    if (curl = curl_easy_init()) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_URL, "smtp.gmail.com:587");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
#ifdef SKIP_PEER_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
#ifdef SKIP_HOSTMAKE_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_VERIFYHOST, 0L);
#endif
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, username);
        recipients = curl_slist_append(recipients, to);
        recipients = curl_slist_append(recipients, cc);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_READDATA, fp);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        if ((res = curl_easy_perform(curl)) != CURLE_OK)
            fprintf(stderr, "Unable to send mail: %s\n",
                    curl_easy_strerror(res));
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
    return (int) res;
}
