from boltiot import Bolt
import json, time
import requests

mybolt = Bolt(conf.api_key, conf.device_id)
selling_price = 232
bitcoin = '72f69dab400275285efa4ba252cf0ac8c72c1cc1ad6dc4aae69bbb66847f6bab'
def get_bitcoin_price():
	URL = "https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=USD,INR&api_key=" + bitcoin # REPLACE WITH CORRECT URL
	response = requests.request("GET", URL)
	response = json.loads(response.text)
	current_price = response["USD"]
	return current_price

while true:

	current_price = get_bitcoin_price() 
	if (current_price > selling_price ):
		print("current_price is greater than selling_price")
		response = mybolt.digitalWrite('0','HIGH')
		print(response)

	time.sleep(30)