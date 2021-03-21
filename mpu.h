#ifndef __MPU_H_
#define __MPU_H_

#include <MPU6050_tockn.h>
#include <Wire.h>

class MPU
{
private:
	/* data */
	// MPU6050 mpu6050(Wire);
	MPU6050 mpu6050;
	// MPU6050 imu;
	int flag;
	float ax, ay, az;
	float gx, gy, gz;

public:
	MPU(/* args */ TwoWire &w);
	~MPU();

	void init();
	void update();

	float getTem();

	float getAccelX();
	float getAccelY();
	float getAccelZ();

	float getGyroX();
	float getGyroY();
	float getGyroZ();
};

#endif