# The Summarizer 2 (2018) -- Written by Aadit Trivedi and Srihari Nanniyur

from summarizer import summarize
from tkinter import *
from summarizer import summarize

email_text = open("data/DATA").read()

root = Tk()

sumnum_lab1 = Label(root, text="Summarize mail into ")
sumnum_entry = Entry(root)
sumnum_lab1 = Label(root, text=" number of lines")
sumnum_lab1.grid(row=0, column=0)
sumnum_entry.grid(row=0, column=1)
sumnum_lab2.grid(row=0, column=2)
summarize_button = Button(root, text="Summarize", command=displayTheSum)
summarize_button.grid(row=1, column=0)

def displayTheSum():
  sumnum = sumnum_entry.get()
  label = Label(root, text=summarize('E-Mail', email_text, sumnum))
  label.grid(row=2, column=0)

root.mainloop()
