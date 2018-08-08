#include "analyze.h"
#include <gtk/gtk.h>
#include "mail.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GtkWidget *window, *entry_num, *entry_flag, *btn_flag, *btn_itemize, *btn_cloud, *box;

static GtkWidget *item_window, *item_view, *item_scroller;
static GtkTextBuffer *item_buffer;

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
    item_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(item_window), "Action Items");
    gtk_window_set_default_size(GTK_WINDOW(item_window), 300, 300);

    item_buffer = gtk_text_buffer_new(NULL);
    gtk_text_buffer_set_text(item_buffer, filebuf, nbytes);
    free(filebuf);

    item_view = gtk_text_view_new_with_buffer(item_buffer);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(item_view), FALSE);
    item_scroller = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(item_scroller),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(item_scroller, 300, 300);
    gtk_container_add(GTK_CONTAINER(item_scroller), item_view);
    gtk_container_add(GTK_CONTAINER(item_window), item_scroller);
    g_signal_connect(item_window, "destroy", G_CALLBACK(gtk_main_quit),
                     NULL);
    gtk_widget_show_all(item_window);
    gtk_main();
}

void analyze_gui(void)
{
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);
    gtk_window_set_title(GTK_WINDOW(window), "E-Mail Analytics");
    entry_num = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_num), "Message Number...");
    entry_flag = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_flag), "Flag as... (1 for positive or 0 for negative)");
    btn_flag = gtk_button_new_with_label("Flag Message");
    btn_itemize = gtk_button_new_with_label("Action-Itemize!");
	btn_cloud = gtk_button_new_with_label("Word Cloud");
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_box_pack_start(GTK_BOX(box), entry_num, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(box), entry_flag, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(box), btn_itemize, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(box), btn_flag, FALSE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(box), btn_cloud, FALSE, FALSE, 1);
    gtk_container_add(GTK_CONTAINER(window), box);
    g_signal_connect(btn_flag, "clicked", G_CALLBACK(flag), NULL);
    g_signal_connect(btn_itemize, "clicked", G_CALLBACK(itemize), NULL);
	g_signal_connect(btn_cloud, "clicked", G_CALLBACK(word_cloud), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
