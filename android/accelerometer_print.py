

import android
import time
import math
from decimal import Decimal

droid = android.Android()
dt = 100 #100ms between sensings
endTime = 3000 #sample for 3000ms
timeSensed=0
droid.startSensingTimed(2,dt)# acceleration
#droid.startSensingTimed(1,dt)# orientation 
#droid.startSensingTimed(3,dt) # magnetometer
while True:
	data= droid.sensorsReadAccelerometer().result
	#print droid.sensorsReadMagnetometer().result
	#print droid.sensorsReadOrientation().result
	acc_z=(data[2])
	acc_x=(data[0])
	#print acc_z
	try:
		angle_rad= math.asin(acc_z/math.hypot(acc_x,acc_z))
		print math.degrees(angle_rad)
	except:
		print "pass"
		pass

	time.sleep(dt/1000.0)
	timeSensed+=dt
droid.stopSensing()




















