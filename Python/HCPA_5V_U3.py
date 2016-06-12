# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# HCPA_5V_U3
# This code is designed to work with the HCPA-5V-U3_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Temperature?sku=HCPA-5V-U3_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# HCPA_5V_U3 address, 0x28(40)
# Send start command, 0x80(128)
bus.write_byte(0x28, 0x80)

time.sleep(0.5)

# HCPA_5V_U3 address, 0x28(40)
# Read data back, 4 bytes
# humidity msb, humidity lsb, cTemp msb, cTemp lsb
data = bus.read_i2c_block_data(0x28, 4)

# Convert the data to 14-bits
humidity = (((data[0] & 0x3F) * 256) + data[1]) / 16384.0 * 100.0
cTemp = (((data[2] * 256) + (data[3] & 0xFC)) / 4) / 16384.0 * 165.0 - 40.0
fTemp = (cTemp * 1.8) + 32

# Output data to screen
print "Relative Humidity : %.2f %%RH" %humidity
print "Temperature in Celsius : %.2f C" %cTemp
print "Temperature in Fahrenheit : %.2f F" %fTemp
