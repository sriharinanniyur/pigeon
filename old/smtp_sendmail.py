import smtplib

# Standard responses to action items
aff = "Thank you for the reminder. Looking forward to meeting you!"
neg = "Thanks for the invite, but I will not be able to attend due to a conflict. Would any other times work?"
med = "I will get back to you as soon as possible."

# Function responsible for sending an email
def smtp_send(email_address, user_pwd, target, content):
  mail = smtplib.SMTP('smtp.gmail.com', 587)
  mail.ehlo()
  mail.starttls()
  mail.login(email_address,user_pwd)
  mail.sendmail(email_address,target, content)
  mail.close()

# Function responsible for easily sends standard response based on user's choice
def smart_reply(email_address, user_pwd, target, response_type):
  if response_type == aff:
    smtp_send(email_address, user_pwd, target, aff)
  elif response_type == neg:
    smtp_send(email_address, user_pwd, target, neg)
  elif response_type == med:
    smtp_send(email_address, user_pwd, target, med)
