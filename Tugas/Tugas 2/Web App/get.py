import serial
import requests
import datetime

urls = "http://127.0.0.1:5000/insert"

print("Running UNO")
now = datetime.datetime.now()
print (now.strftime('%Y-%m-%d %H:%M:%S.%f')[:-3])

#arduino = serial.Serial("/dev/ttyUSB0", timeout=1, baudrate=9600)
arduino = serial.Serial("COM2", timeout=1, baudrate=9600)
while True:
	a = arduino.readline().decode("utf-8").strip('\n').strip('\r')
	print(a)
	if(a!=''):
		temp = a.split(';')
		print(temp)
		temperature = float(temp[0])
		humidity = float(temp[1])
		pressure = float(temp[2])
		rain = temp[3]
		data = {'temperature':temperature,
			'humidity':humidity,
			'pressure':pressure,
			'rain':rain}
		res = requests.post(url = urls, data = data) 
		print(res.text)
	