import requests
import subprocess
import time
from bs4 import BeautifulSoup

web_server = requests.get("http://192.168.0.104/humidity")

while True:
	if web_server.text < 40:
		subprocess.call(["/var/www/rfoutlet/RFSource/codesend", "5332236", "-l", "194", "-p", "0"])

	elif web_server.text > 55:
		subprocess.call(["/var/www/rfoutlet/RFSource/codesend", "5332227", "-l", "194", "-p", "0"])

	else:
		print "Dehumidfier is working."
		time.sleep(30)



