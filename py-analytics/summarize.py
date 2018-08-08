# Written by Aadit Trivedi and Srihari Nanniyur

from summarizer import summarize
from tkinter import *
from summarizer import summarize

email_text = open("data/DATA").read()

root = Tk()
label = Label(root, text=summarize('E-Mail', email_text))
label.pack()
root.mainloop()
