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
// A program that drives forward and backward five times incresing the distance by 0,5m. Calulate distance with time.

const int FULL_POWER = 127;
const int BASE_TIME = 470;  //The time it takes for the robot to go 0,5 meters
int i;

void drive(bool direction,int time){
	int dir = (direction)?(1):(-1);    //Decied what direction it shoud go
	motor[rightMotor] = FULL_POWER*dir;
	motor[leftMotor]  = FULL_POWER*dir;
	wait1Msec(BASE_TIME);
}

task main()
{
	StartTask (display);
	for(i = 1; i < 6; ++i){
		drive(true,BASE_TIME*i);
		wait1Msec(100);
		drive(false,BASE_TIME*i);
		wait1Msec(100);
	}


}
