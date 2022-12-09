import sms_conf
from boltiot import Sms, Bolt
import json, time

minimum_limit = 20 
maximum_limit = 50  


mybolt = Bolt(sms_conf.API_KEY, sms_conf.DEVICE_ID)
sms = Sms(sms_conf.SSID, sms_conf.AUTH_TOKEN, sms_conf.TO_NUMBER, sms_conf.FROM_NUMBER)


while True: 
    response = mybolt.analogRead('A0') 
    data = json.loads(response) 
    print (data['value'])
    try: 
        sensor_value = int(data['value']) 
        Temperature=(100*sensor_value)/1024
        print (sensor_value)
        if sensor_value > maximum_limit or sensor_value < minimum_limit:
            response = sms.send_sms("The Current temperature sensor value is " +str(Temperature)) 
    except Exception as e: 
        print ("Error",e)
    time.sleep(10)

