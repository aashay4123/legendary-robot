
import conf, tweepy
from boltiot import Sms, Email,Bolt
import json, time

mybolt = Bolt(conf.api_key, conf.device_id)

config = {
"consumer_key"    : conf.consumer_key,
"consumer_secret"     : conf.consumer_secret,
"access_token"        : conf.access_token,
"access_token_secret" : conf.access_token_secret
}

minimum_limit = 20 
maximum_limit = 50  
temperature_threshold = 59


sms = Sms(conf.SSID, conf.AUTH_TOKEN, conf.TO_NUMBER, conf.FROM_NUMBER)
mailer = Email(email_conf.MAILGUN_API_KEY, email_conf.SANDBOX_URL, email_conf.SENDER_EMAIL, email_conf.RECIPIENT_EMAIL)

def check_status():
	response = mybolt.isOnline()
	print (response)
	
def restart():
	response = mybolt.restart()
	print (response)
	
def ledon():	
	response = mybolt.digitalWrite('0', 'HIGH')
	print (response)
	
def ledoff():
	response = mybolt.digitalWrite('0', 'LOW')
	print (response)
	
def bright(int num):
	response = mybolt.analogWrite('0', num)
	print (response)
	

def get_api_object(cfg):
    auth =tweepy.OAuthHandler(cfg['consumer_key'],
                                  cfg['consumer_secret'])
    auth.set_access_token(cfg['access_token'],
                              cfg['access_token_secret'])
    return tweepy.API(auth)


def temp_sms(): 
	response = mybolt.analogRead('A0') 
	data = json.loads(response) 
 	print (data['value'])
  	sensor_value = int(data['value']) 
   	Temperature=(100*sensor_value)/1024
    if sensor_value > maximum_limit or sensor_value < minimum_limit:
    	print (temperature)
    	response = sms.send_sms("The Current temperature sensor value is " +str(Temperature)) 
    time.sleep(10)


def temp_email():
   	response = mybolt.analogRead('A0') 
  	data = json.loads(response) 
   	print (data['value'])
   	sensor_value = int(data['value']) 
   	Temperature=(100*sensor_value)/1024
    print (Temperature)
    if sensor_value > maximum_limit or sensor_value < minimum_limit:
       	response = mailer.send_email("Alert", "The Current temperature sensor value is " +str(Temperature))
  		print (Temperature)
    time.sleep(10)
	
def temp_tweet():
    	
   	response = mybolt.analogRead('A0')
   	data = json.loads(response)
   	print (data['value'])
   	sensor_value = int(data['value'])
   	if sensor_value > temperature_threshold:
   		print "Temperature has crossed the threshold."
   		api_object = get_api_object(config)
   		tweet = "Temperature has crossed the threshold."
   		status = api_object.update_status(status=tweet)
   	time.sleep(10)
   