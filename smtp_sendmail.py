import smtplib

def smtp_send(email_address, user_pwd, target, content):
  mail = smtplib.SMTP('smtp.gmail.com', 587)
  mail.ehlo()
  mail.starttls()
  mail.login(email_address,user_pwd)
  mail.sendmail(email_address,target, content)
  mail.close()
