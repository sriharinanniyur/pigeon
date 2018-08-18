// Written by Srihari Nanniyur.

#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include "mail.h"
#include "gui.h"


GtkWidget *auth_window, *auth_uname_entry, *auth_pwd_entry, *auth_btn, *auth_box;
void start_program(void);
void authenticate_and_run(GtkWidget *, gpointer);

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    start_program();
    system("rm HEADERS SENDMESSAGE");
    return 0;
}

void start_program(void)
{
    auth_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(auth_window), 300, 150);
    gtk_window_set_title(GTK_WINDOW(auth_window), "Username and Password");

    auth_uname_entry = gtk_entry_new();
    auth_pwd_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(auth_pwd_entry), FALSE);
    auth_btn = gtk_button_new_with_label("Authenticate");
    auth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, -1);
    gtk_box_pack_start(GTK_BOX(auth_box), auth_uname_entry, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(auth_box), auth_pwd_entry, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(auth_box), auth_btn, FALSE, FALSE, 1);
    gtk_container_add(GTK_CONTAINER(auth_window), auth_box);
    g_signal_connect(auth_btn, "clicked", G_CALLBACK(authenticate_and_run), NULL);
    gtk_widget_show_all(auth_window);
    gtk_main();
}

void authenticate_and_run(GtkWidget *p, gpointer data)
{
    strncpy(USERNAME, gtk_entry_get_text(GTK_ENTRY(auth_uname_entry)), MAXLEN);
    strncpy(PASSWORD, gtk_entry_get_text(GTK_ENTRY(auth_pwd_entry)), MAXLEN);
    fetch_headers(USERNAME, PASSWORD);
    gtk_widget_destroy(auth_window);
    gtk_main_quit();
    main_gui();
}
