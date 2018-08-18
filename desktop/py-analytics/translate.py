# Written by Aadit Trivedi and Srihari Nanniyur.
import goslate
from tkinter import *
# ------------------------------------------------------------------#
# Translates provided text into provided language
# Dependencies: goslate
# ------------------------------------------------------------------#

root = Tk()
entry = Entry(root)
lab = Label(root, text="Two-letter language code")
entry.grid(row=0, column=0)
lab.grid(row=0, column=1)

def translate_into_lang():
        _slate_ = goslate.Goslate()
        result = _slate_.translate(open('data/DATA', 'r').read(), entry.get())
        label = Label(root, text=result)
        label.grid(row=2, column=0)

button = Button(root, text="Translate", command=translate_into_lang)
button.grid(row=1, column=0)

root.mainloop()
