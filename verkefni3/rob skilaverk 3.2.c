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

//A program that drives after a spesific pattern

const int FULL_POWER = 80;
const int BASE_DIST = 564;


void reset_encoders(){
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder]  = 0;
}
void drive(int dist,bool direction){
	int dir = (direction)?(1):(-1);
	while(dist > abs(SensorValue[rightEncoder]))
	{
		if(abs(SensorValue[rightEncoder]) == abs(SensorValue[leftEncoder]))
		{
			motor[rightMotor] = 60*dir;
			motor[leftMotor]  = 60*dir;
		}
		else if(abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder]))
		{
			motor[rightMotor] = 40*dir;
			motor[leftMotor]  = 60*dir;
		}
		else
		{
			motor[rightMotor] = 60*dir;
			motor[leftMotor]  = 40*dir;
		}
	}
}

bool turn_list[] = {1,0,0,1,1,0,1,1,0,1,1,0,0,1}; //list to determen what direction it is supos to turn

void turn(int degrees10,bool counterclock){
	SensorType[in4] = sensorNone; //Clering out the sensor
  wait1Msec(1000);
  SensorType[in4] = sensorGyro; //Reconfing the sensor
  wait1Msec(2000);

  while(abs(SensorValue[in4]) < degrees10)
  {
		if (counterclock){
		motor[rightMotor] = 50;
		motor[leftMotor] = -50;
		}
		else{
		motor[rightMotor] = -50;
		motor[leftMotor] = 50;
		}
  }
  // break to stop it from drifting
  motor[rightMotor] = -5;
  motor[leftMotor] = 5;
  wait1Msec(250);
}
void stop_motor(){
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(1000);
}


task stop_button(){
while(vexRT[Btn8R] == 0)
{
}
StopAllTasks();
}

task main()
{
 StartTask(display);
 StartTask(stop_button);
 for (int i = 0;i<14;i++){
 	reset_encoders();
	drive(BASE_DIST,true);
 	stop_motor();
	turn(900,turn_list[i]);
	stop_motor();
}
reset_encoders();
drive(BASE_DIST,true);
}
