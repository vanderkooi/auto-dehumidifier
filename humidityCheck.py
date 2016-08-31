# This code is meant to be used with cron tabs in your terminal to check the dehumidifier at certain time intervals.
# To set up a cron tab, use "crontab -e" to edit your crontabs.
# If you want to activate this every 10 mins, use */10 * * * * python /your/path/for/this/script

import requests
import subprocess
import time
import ast
import sys

def programCall():
	# setting up the range of values for the dehumidifier
	if humidity_level <= 45: # turn off dehumidifier if below this number
		subprocess.call(["your/path/to/codesend", "offRFCode", "-l", "yourPulse", "-p", "0"])

	elif humidity_level >= 54: # turn on dehumidifier if above this number
		subprocess.call(["your/path/to/codesend", "onRFCode", "-l", "yourPulse", "-p", "0"])

	else:
		print "Dehumidfier is working." 

try:
	web_server = requests.get("http://yourESPWebServerName")
	humidity_level = ast.literal_eval(web_server.text)
	programCall()

except requests.exceptions.Timeout:
	for i in range(0, 100):
		while True:
			try:
				web_server = requests.get("http://yourESPWebServerName")
				programCall()
			except Exception:
				time.sleep(10)
				continue

except requests.exceptions.TooManyRedirects:
	print "URL was not valid."

except requests.exceptions.ConnectionError:
	print "Could not connect, address wasn't known. Please edit this script."





