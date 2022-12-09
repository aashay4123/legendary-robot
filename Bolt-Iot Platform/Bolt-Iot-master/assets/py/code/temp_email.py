import email_conf
from boltiot import Email, Bolt
import json, time

minimum_limit = 20 #the minimum threshold of light value 
maximum_limit = 50 #the maximum threshold of light value 


mybolt = Bolt(email_conf.API_KEY, email_conf.DEVICE_ID)
mailer = Email(email_conf.MAILGUN_API_KEY, email_conf.SANDBOX_URL, email_conf.SENDER_EMAIL, email_conf.RECIPIENT_EMAIL)


while True: 
    response = mybolt.analogRead('A0') 
    data = json.loads(response) 
    print (data['value'])
    try: 
        sensor_value = int(data['value']) 
        Temperature=(100*sensor_value)/1024
        
        if sensor_value > maximum_limit or sensor_value < minimum_limit:
            print (Temperature)
            mail="The Current temperature sensor value is " +str(Temperature)
            response = mailer.send_email("Alert", mail)
    except Exception as e: 
        print ("Error",e)
    time.sleep(10)