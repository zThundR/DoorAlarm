#Libraries
import RPi.GPIO as GPIO
import time
import mysql.connector
import time

#GPIO Mode
GPIO.setmode(GPIO.BCM)

#PIN
GPIO_TRIGGER = 18
GPIO_ECHO = 24

#SETTAGGIO PIN
GPIO.setup(GPIO_TRIGGER, GPIO.OUT)
GPIO.setup(GPIO_ECHO, GPIO.IN)

def distance():
	#TRIGPIN su ALTO (17)
	GPIO.output(GPIO_TRIGGER, True)
	time.sleep(0.00001)
	GPIO.output(GPIO_TRIGGER, False)

	StartTime = time.time()
	StopTime = time.time()

	while GPIO.input(GPIO_ECHO) == 0:
		StartTime = time.time()

	while GPIO.input(GPIO_ECHO) == 1:
		StopTime = time.time()

	TimeElasped = StopTime - StartTime
	distance = ((TimeElasped * 34300) / 2)
	return distance


def salva_db(stringa_query):
	db = mysql.connector.connect(host="localhost", user="root", password="itis", database="allarme_porta")
	cursore = db.cursor()
	cursore.execute(stringa_query)
	db.commit()

if __name__ == '__main__':
	while True:
		try:
			secondo = time.time()
			cmlock = 0
			cnt = 0
			while cnt < 10:
				if time.time() > (secondo + cnt):
					dist = distance()
					if cnt == 0:
						cmlock = dist
						print ("Oggetto uscito dal range")
					if (dist > cmlock - 5) and (dist < cmlock + 5):
						cnt += 1
						print ("Oggetto rilevato nel range (" + str(cnt) + " volta)")
					else:
						break
			if cnt >= 10:
				print ("Rilevato Oggetto!")
				startQuery = "INSERT INTO allarme_porta (data, motivazione) VALUES ('"
				dataQuery = time.strftime('%Y/%m/%d/%H/%M/%S')
				startQuery += dataQuery + "', '"
				motivazioneQuery = "Rilevato Movimento."
				startQuery += motivazioneQuery + "')"
				salva_db(startQuery)

		except KeyboardInterrupt:
			print("")
			print("")
			print("Programma Interrotto.")
			GPIO.cleanup()
