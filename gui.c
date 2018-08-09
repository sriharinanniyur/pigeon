// Written by Srihari Nanniyur.

#include "gui.h"
#include "mail.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GtkCssProvider *provider;
static GtkStyleContext *context;

static GtkWidget *window, *view, *scroller, *button_view, *button_send, *entry_num, *btn_box, *view_box, *box;
static GtkTextBuffer *buffer;

static GtkWidget *msg_view, *msg_scroller;
static GtkTextBuffer *msg_buffer;

static GtkWidget *send_frame, *send_from_entry, *send_to_entry, *send_cc_entry, *send_content_entry, *send_box;

static GtkWidget *entry_flag, *btn_flag, *btn_itemize, *btn_summarize, *btn_cloud;

static GtkWidget *item_view, *item_scroller;
static GtkTextBuffer *item_buffer;

static void summarize(GtkWidget *p, gpointer data)
{   
    fetch_mail(USERNAME, PASSWORD, BODY, atoi(gtk_entry_get_text(GTK_ENTRY(entry_num))));
    system("python3 py-analytics/summarize.py");
}

static void word_cloud(GtkWidget *p, gpointer data)
{   
    fetch_mail(USERNAME, PASSWORD, BODY, atoi(gtk_entry_get_text(GTK_ENTRY(entry_num))));
    system("python3 py-analytics/word_cloud.py");
}

static void flag(GtkWidget *p, gpointer data)
{   
    int c;
    FILE *fin; 
    FILE *fout = fopen((atoi(gtk_entry_get_text(GTK_ENTRY(entry_flag))) ? "training/POSITIVES" : "training/NEGATIVES"), "a+");
    fetch_mail(USERNAME, PASSWORD, BODY, atoi(gtk_entry_get_text(GTK_ENTRY(entry_num))));
    fin = fopen("data/DATA", "r");
    if (fin == NULL || fout == NULL) return;
    while ((c = getc(fin)) != EOF) putc(c, fout);
    fclose(fin);
    fclose(fout);
}

static void itemize(GtkWidget *p, gpointer data)
{
    FILE *fp;
    char *filebuf;
    long nbytes;
    fetch_mail(USERNAME, PASSWORD, BODY, atoi(gtk_entry_get_text(GTK_ENTRY(entry_num))));
    system("sbcl --script main.lisp");
    if ((fp = fopen("data/RESULTS", "r")) == NULL) return;
    fseek(fp, 0L, SEEK_END);
    nbytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    if ((filebuf = (char *) calloc(nbytes, sizeof(char))) == NULL) return;
    fread(filebuf, sizeof(char), nbytes, fp);
    fclose(fp);
    gtk_text_buffer_set_text(item_buffer, filebuf, nbytes);
    free(filebuf);
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

static void view_message(GtkWidget *p, gpointer data)
{
    char *filebuf = NULL;
    long numbytes;
    FILE *fp;
    fetch_mail(USERNAME, PASSWORD, BODY, atoi(gtk_entry_get_text(GTK_ENTRY(entry_num))));
    if ((fp = fopen("data/DATA", "r")) == NULL)
        return;
    fseek(fp, 0L, SEEK_END);
    numbytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    if ((filebuf = (char *) calloc(numbytes, sizeof(char))) == NULL)
        return;
    fread(filebuf, sizeof(char), numbytes, fp);
    fclose(fp);
    gtk_text_buffer_set_text(msg_buffer, filebuf, numbytes);
    free(filebuf);
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
    gtk_window_set_default_size(GTK_WINDOW(window), 1500, 700);

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
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroller), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scroller, 200, 400);
    gtk_container_add(GTK_CONTAINER(scroller), view);

    msg_buffer = gtk_text_buffer_new(NULL);
    msg_view = gtk_text_view_new_with_buffer(msg_buffer);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(msg_view), FALSE);
    msg_scroller = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroller), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(msg_scroller, 200, 400);
    gtk_container_add(GTK_CONTAINER(msg_scroller), msg_view);

    item_buffer = gtk_text_buffer_new(NULL);
    item_view = gtk_text_view_new_with_buffer(item_buffer);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(item_view), FALSE);
    item_scroller = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(item_scroller),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(item_scroller, 200, 400);
    gtk_container_add(GTK_CONTAINER(item_scroller), item_view);

    button_view = gtk_button_new_with_label("View Message");
    entry_num = gtk_entry_new();
    entry_flag = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_num), "Message number...");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_flag), "Flag as... (1 for positive or 0 for negative)");
    btn_flag = gtk_button_new_with_label("Flag Message");
    btn_itemize = gtk_button_new_with_label("Action-Itemize");
    btn_summarize = gtk_button_new_with_label("Summarize");
    btn_cloud = gtk_button_new_with_label("Word Cloud");

    btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(btn_box), button_view, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(btn_box), btn_flag, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(btn_box), btn_itemize, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(btn_box), btn_summarize, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(btn_box), btn_cloud, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(btn_box), entry_num, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(btn_box), entry_flag, FALSE, FALSE, 1);

    view_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(view_box), scroller, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(view_box), msg_scroller, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(view_box), item_scroller, TRUE, TRUE, 1);

    send_from_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(send_from_entry), "From...");
    send_to_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(send_to_entry), "To...");
    send_cc_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(send_cc_entry), "Cc...");
    send_content_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(send_content_entry), "Content...");
    button_send = gtk_button_new_with_label("Send Message");
    send_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, -1);
    gtk_box_pack_start(GTK_BOX(send_box), send_from_entry, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(send_box), send_to_entry, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(send_box), send_cc_entry, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(send_box), send_content_entry, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(send_box), button_send, FALSE, FALSE, 1);
    send_frame = gtk_frame_new("Send Message");
    gtk_container_add(GTK_CONTAINER(send_frame), send_box);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(box), btn_box, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(box), view_box, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(box), send_frame, FALSE, FALSE, 1);

    gtk_container_add(GTK_CONTAINER(window), box);
    g_signal_connect(button_view, "clicked", G_CALLBACK(view_message), NULL);
    g_signal_connect(btn_flag, "clicked", G_CALLBACK(flag), NULL);
    g_signal_connect(button_send, "clicked", G_CALLBACK(send_message), NULL);
    g_signal_connect(btn_itemize, "clicked", G_CALLBACK(itemize), NULL);
    g_signal_connect(btn_summarize, "clicked", G_CALLBACK(summarize), NULL);
    g_signal_connect(btn_cloud, "clicked", G_CALLBACK(word_cloud), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
