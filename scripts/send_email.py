import smtplib
import os
import sys
from email.mime.text import MIMEText

# Load credentials from environment variables
EMAIL = os.getenv("ALERT_EMAIL")
PASSWORD = os.getenv("ALERT_PASSWORD")
RECIPIENT = os.getenv("ALERT_RECIPIENT")

def send_email(subject, body, recipient):
    if not EMAIL or not PASSWORD or not recipient:
        print("❌ ERROR: Missing email credentials or recipient.")
        print("Set ALERT_EMAIL, ALERT_PASSWORD, and ALERT_RECIPIENT environment variables.")
        sys.exit(1)

    try:
        # Create the email message
        msg = MIMEText(body)
        msg["Subject"] = subject
        msg["From"] = EMAIL
        msg["To"] = recipient

        # Connect to Gmail SMTP with SSL
        with smtplib.SMTP_SSL("smtp.gmail.com", 465) as server:
            server.login(EMAIL, PASSWORD)
            server.sendmail(EMAIL, recipient, msg.as_string())

        print(f"✅ Email sent successfully to {recipient}!")

    except smtplib.SMTPAuthenticationError:
        print("❌ Authentication failed: Check your Gmail App Password.")
    except Exception as e:
        print(f"❌ Failed to send email: {e}")

if __name__ == "__main__":
    # Subject and body for urgent task notification
    subject = "URGENT: Task Due Soon"
    body = "🚨 Urgent Task Alert: Check your assignment tracker."

    # Use environment variable recipient by default
    recipient = RECIPIENT or "receiver@example.com"

    send_email(subject, body, recipient)
