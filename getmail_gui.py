import imaplib
import email
import html2text
import tkinter as tk
from tkinter import END

def getmail_gui():
    root = tk.Tk()
    host_label = tk.Label(root, text="Mail Server")
    host_label.grid(row=0, column=0)
    address_label = tk.Label(root, text="Email Address")
    address_label.grid(row=1, column=0)
    password_label = tk.Label(root, text="Password")
    password_label.grid(row=2, column=0)
    host_entry = tk.Entry(root)
    host_entry.grid(row=0, column=1)
    address_entry = tk.Entry(root)
    address_entry.grid(row=1, column=1)
    password_entry = tk.Entry(root, show="•")
    password_entry.grid(row=2, column=1)

    def getmail():
        M = imaplib.IMAP4_SSL(host_entry.get())
        M.login(address_entry.get(), password_entry.get())
        rv, data = M.select('INBOX')
        if rv == 'OK':
            rv, data = M.search(None, 'ALL')
            if rv != 'OK':
                raise Exception(rv)
            for n in data[0].split():
                rv, data = M.fetch(n, '(RFC822)')
                if rv != 'OK':
                    raise Exception(rv)
                with open('email/' + n.decode('utf-8') + '.eml', 'a+') as fout:
                    for part in email.message_from_string(data[0][1].decode('utf-8')).walk():
                            try:
                                fout.write(html2text.html2text(part.get_payload(decode=True).decode('utf-8')))
                            except:
                                continue
        else:
            raise Exception(rv)
        M.close()
        M.logout()
        root.destroy()

    submit_btn = tk.Button(root, text="Submit", command=getmail)
    submit_btn.grid(row=3, column=0)
    root.mainloop()
getmail_gui()
