# Verifies the existence of an email address

def veripy(SERVER, SMTP_PORT, email):
  server = smtplib.SMTP(str(SERVER), int(SMTP_PORT))
  server.connect()
  server.set_debuglevel(True)
  try:
      server.verify(email)
  except Exception:
      return False
  finally:
      server.quit()
