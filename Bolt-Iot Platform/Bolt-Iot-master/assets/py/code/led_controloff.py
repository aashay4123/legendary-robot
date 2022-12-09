api_key = "92c94f06-a681-4ef4-9bff-f4c024fba905"
device_id  = "BOLT6094955"
mybolt = Bolt(api_key, device_id)
response = mybolt.digitalWrite('0', 'LOW')
print(response)