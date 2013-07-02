

import android
import time


BT_DEVICE_ID = '00:12:10:29:21:40'


droid = android.Android()

droid.bluetoothConnect('00001101-0000-1000-8000-00805F9B34FB', BT_DEVICE_ID)
time.sleep(3)
while True:
	droid.bluetoothWrite('s')
	time.sleep(3)
	droid.bluetoothWrite('f')
	time.sleep(3)
