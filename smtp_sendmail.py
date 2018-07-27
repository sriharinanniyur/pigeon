import smtplib

mail = smtplib.SMTP('smtp.gmail.com', 587)
mail.ehlo()
mail.starttls()

email_address = input(print("Gmail address: "))
user_pwd = input(print("Password: "))
target = input(print("To: "))
content = input(print("Content: "))


mail.login(email_address,user_pwd)
mail.sendmail(email_address,target, content)
mail.close()
