#pragma config(Sensor, dgtl2,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  leftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)


task display()
{
	bLCDBacklight = true;
	string mainBattery, backupBattery;

	while(true)
	{
		clearLCDLine(0);
		clearLCDLine(1);


		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V');
		displayNextLCDString(mainBattery);


		displayLCDString(1, 0, "Backup: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');
		displayNextLCDString(backupBattery);


		wait1Msec(100);
	}
}
// A program that drives forward and backward five times incresing the distance by 0,5m. Calulates distance with distens.

const int FULL_POWER = 127;

const float BASE_DIST = 563.934837727; //BASE_DIST is what it takes to go 0,5m.
//Calucation for BASE_DIST, CIRCUMFERENCE	= 2.54*4*PI = 31.9185813605, BASE_DIST = 50/CIRCUMFERENCE*360.


void reset_encoders(){
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder]  = 0;
}
void stop_motor(){
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(1000);
}
void drive(float dist,bool direction){
	int dir = (direction)?(1):(-1);
	while(dist > abs(SensorValue[rightEncoder]))
	{
		if(abs(SensorValue[rightEncoder]) == abs(SensorValue[leftEncoder])) //if both wheels are at same distence
		{
			motor[rightMotor] = 60*dir;
			motor[leftMotor]  = 60*dir;
		}
		else if(abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder])) //if right wheel is to far a head
		{
			motor[rightMotor] = 40*dir;
			motor[leftMotor]  = 60*dir;
		}
		else     //if left wheel is to far a head
		{
			motor[rightMotor] = 60*dir;
			motor[leftMotor]  = 40*dir;
		}
	}
}

task main()
{
 StartTask(display);
   for(int i=1;i<6;i++){
   reset_encoders();
 	 drive(BASE_DIST*i,true);
 	 stop_motor();
 	 reset_encoders();
 	 drive(BASE_DIST*i,false);
 	 stop_motor();
 }

}
