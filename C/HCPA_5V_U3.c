// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// HCPA_5V_U3
// This code is designed to work with the HCPA-5V-U3_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=HCPA-5V-U3_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, HCPA_5V_U3 I2C address is 0x28(40)
	ioctl(file, I2C_SLAVE, 0x28);

	// Send start command
	char config[1] = {0};
	config[0] = 0x80;
	write(file, config, 1);
	sleep(1);

	// Read 4 bytes of data
	// humidity msb, humidity lsb, cTemp msb, cTemp lsb
	char data[4] = {0};
	if(read(file, data, 4) != 4)
	{
		printf("Error : Input/output Error \n");
	}
	else
	{
	// Convert the data to 14-bits
	double humidity = (((data[0] & 0x3F) * 256) + (data[1] & 0xFF)) / 16384.0 * 100.0;
	double cTemp = ((((data[2] & 0xFF) * 256) + (data[3] & 0xFC)) / 4) / 16384.0 * 165.0 - 40.0;
	double fTemp = (cTemp * 1.8) + 32;

	// Output data to screen
	printf("Relative Humidity : %.2f \n", humidity);
	printf("Temperature in Celsius : %.2f C \n", cTemp);
	printf("Temperature in Farhenheit : %.2f F \n", fTemp);
	}
}
