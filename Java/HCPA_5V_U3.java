// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// HCPA_5V_U3
// This code is designed to work with the HCPA-5V-U3_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=HCPA-5V-U3_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class HCPA
{
	public static void main(String args[]) throws Exception
	{
		// Create I2CBus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, HCPA_5V_U3 I2C address is 0x28(40)
		I2CDevice device = bus.getDevice(0x28);
		
		// Send start command
		device.write((byte)0x80);
		Thread.sleep(500);
		
		// Read 4 bytes of data
		// humidity msb, humidity lsb, cTemp msb, cTemp lsb
		byte[] data = new byte[4];
		device.read(data, 0, 4);

		// Convert the data to 14-bits
		double humidity = (((data[0] & 0x3F) * 256) + (data[1] & 0xFF)) / 16384.0 * 100.0;
		double cTemp = ((((data[2] & 0xFF) * 256) + (data[3] & 0xFC)) / 4) / 16384.0 * 165.0 - 40.0;
		double fTemp = (cTemp * 1.8) + 32;
		
		// Output data to screen
		System.out.printf("Relative Humidity : %.2f %% %n", humidity);
		System.out.printf("Temperature in Celsius : %.2f C %n", cTemp);
		System.out.printf("Temperature in Farhenheit : %.2f F %n", fTemp);
		}
}