#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include "mail.h"
#include "gui.h"

void get_uname_pwd(void);

int main(int argc, char **argv)
{
    get_uname_pwd();
    fetch_headers(USERNAME, PASSWORD);
    gtk_init(&argc, &argv);
    main_gui();
    system("rm HEADERS MESSAGE SENDMESSAGE TEXT");
    return 0;
}

void get_uname_pwd(void)
{
    char username[MAXLEN], *password;
    printf("username: ");
    fgets(username, MAXLEN, stdin);
    username[strlen(username)] = '\0';
    strcpy(USERNAME, username);
    password = getpass("password: ");
    strncpy(PASSWORD, password, MAXLEN);
    free(password);
}
