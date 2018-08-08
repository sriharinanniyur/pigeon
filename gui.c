// Written by Srihari Nanniyur.

#include "gui.h"
#include "mail.h"
#include "analyze.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GtkCssProvider *provider;
static GtkStyleContext *context;

static GtkWidget *window, *view, *scroller, *button_view, *button_send, *button_analyze, *entry_num, *box;
static GtkTextBuffer *buffer;

static GtkWidget *msg_window, *msg_view, *msg_scroller;
static GtkTextBuffer *msg_buffer;

static GtkWidget *send_window, *send_from_entry, *send_to_entry, *send_cc_entry, *send_content_entry, *send_btn, *send_box;

static void analyze(GtkWidget *p, gpointer data)
{
    analyze_gui();
}

static void send_message(GtkWidget *p, gpointer data)
{
    FILE *fp = fopen("SENDMESSAGE", "w");
    if (fp == NULL) return;
    fputs(gtk_entry_get_text(GTK_ENTRY(send_content_entry)), fp);
    fclose(fp);
    fp = fopen("SENDMESSAGE", "r");
    if (fp == NULL) return;
    send_mail(gtk_entry_get_text(GTK_ENTRY(send_from_entry)),
              PASSWORD, (char *)gtk_entry_get_text(GTK_ENTRY(send_to_entry)),
              (char *)gtk_entry_get_text(GTK_ENTRY(send_cc_entry)), fp);
    fclose(fp);
}

static void send_message_gui(GtkWidget *p, gpointer data)
{
    send_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(send_window), "Send Message");
    gtk_window_set_default_size(GTK_WINDOW(send_window), 300, 200);
    send_from_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(send_from_entry), "From...");
    send_to_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(send_to_entry), "To...");
    send_cc_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(send_cc_entry), "Cc...");
    send_content_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(send_content_entry), "Content...");
    send_btn = gtk_button_new_with_label("Send");
    send_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, -1);
    gtk_box_pack_start(GTK_BOX(send_box), send_from_entry, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(send_box), send_to_entry, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(send_box), send_cc_entry, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(send_box), send_content_entry, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(send_box), send_btn, FALSE, FALSE, 1);
    gtk_container_add(GTK_CONTAINER(send_window), send_box);
    g_signal_connect(send_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(send_btn, "clicked", G_CALLBACK(send_message), NULL);
    gtk_widget_show_all(send_window);
    gtk_main();

}

static void view_message_gui(GtkWidget *p, gpointer data)
{
    char *filebuf = NULL;
    long numbytes;
    FILE *fp;
    fetch_mail(USERNAME, PASSWORD, BODY,
               atoi(gtk_entry_get_text(GTK_ENTRY(entry_num))));
    if ((fp = fopen("data/DATA", "r")) == NULL)
        return;
    fseek(fp, 0L, SEEK_END);
    numbytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    if ((filebuf = (char *) calloc(numbytes, sizeof(char))) == NULL)
        return;
    fread(filebuf, sizeof(char), numbytes, fp);
    fclose(fp);
    msg_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(msg_window), "Message");
    gtk_window_set_default_size(GTK_WINDOW(msg_window), 300, 300);

    msg_buffer = gtk_text_buffer_new(NULL);
    gtk_text_buffer_set_text(msg_buffer, filebuf, numbytes);
    free(filebuf);

    msg_view = gtk_text_view_new_with_buffer(msg_buffer);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(msg_view), FALSE);
    msg_scroller = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroller),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(msg_scroller, 300, 300);
    gtk_container_add(GTK_CONTAINER(msg_scroller), msg_view);
    gtk_container_add(GTK_CONTAINER(msg_window), msg_scroller);
    g_signal_connect(msg_window, "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(msg_window);
    gtk_main();
}

void main_gui()
{
    char *filebuf = NULL;
    long numbytes;
    FILE *fp;
    fp = fopen("HEADERS", "r");
    if (fp == NULL)
        return;
    fseek(fp, 0L, SEEK_END);
    numbytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    if ((filebuf = (char *) calloc(numbytes, sizeof(char))) == NULL)
        return;
    fread(filebuf, sizeof(char), numbytes, fp);
    fclose(fp);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), USERNAME);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);

    buffer = gtk_text_buffer_new(NULL);
    gtk_text_buffer_set_text(buffer, filebuf, numbytes);
    free(filebuf);
    view = gtk_text_view_new_with_buffer(buffer);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    provider = gtk_css_provider_new();
	gtk_css_provider_load_from_data(provider,
        "textview { font : 15px serif;}", -1, NULL);
	context = gtk_widget_get_style_context(view);
	gtk_style_context_add_provider(context,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    scroller = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroller),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scroller, 300, 400);
    gtk_container_add(GTK_CONTAINER(scroller), view);

    button_view = gtk_button_new_with_label("View Message");
    button_send = gtk_button_new_with_label("Send Message");
    button_analyze = gtk_button_new_with_label("Analyze Messages");
    entry_num = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_num), "Message number...");

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, -1);
    gtk_box_pack_start(GTK_BOX(box), button_view, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(box), button_send, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(box), button_analyze, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(box), entry_num, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(box), scroller, TRUE, TRUE, 1);

    gtk_container_add(GTK_CONTAINER(window), box);
    g_signal_connect(button_view, "clicked", G_CALLBACK(view_message_gui), NULL);
    g_signal_connect(button_send, "clicked", G_CALLBACK(send_message_gui), NULL);
    g_signal_connect(button_analyze, "clicked", G_CALLBACK(analyze), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
