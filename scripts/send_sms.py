from twilio.rest import Client
import os

# Load Twilio credentials from environment
ACCOUNT_SID = os.getenv("TWILIO_SID")
AUTH_TOKEN = os.getenv("TWILIO_TOKEN")
FROM_NUMBER = os.getenv("TWILIO_FROM")
TO_NUMBER = os.getenv("TWILIO_TO")

client = Client(ACCOUNT_SID, AUTH_TOKEN)

def send_sms(body):
    message = client.messages.create(
        body=body,
        from_=FROM_NUMBER,
        to=TO_NUMBER
    )
    print("✅ SMS sent! SID:", message.sid)

if __name__ == "__main__":
    send_sms("🚨 Urgent Task Alert: Check your assignment tracker.")
