#pragma config(Sensor, dgtl6,  sonarSensor,         sensorSONAR_cm)
#pragma config(Sensor, in3,    lightSensor,         sensorReflection)
#pragma config(Motor,  port3,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           leftMotor,     tmotorNormal, openLoop)


// A Program that drives the robot forward and turns away from obstical as long it is bright

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
task light()
{
	wait1Msec(2000);

	while(SensorValue(lightSensor) < 400) //While light is brighter than 400
	{
	}
StopAllTasks();
}

task stop_button(){
while(vexRT[Btn8R] == 0)
{
}
StopAllTasks();
}
task main()
{
	wait1Msec(2000);
	StartTask(display);
	StartTask(stop_button);
	StartTask(light);
	while (true == true){
	if(SensorValue(sonarSensor) > 50  || SensorValue(sonarSensor) == -1) //if sonar is more than 50cm
	{
		motor[rightMotor] = 63;
		motor[leftMotor]  = 63;
	}
	else{

	motor[rightMotor] = 50;
	motor[leftMotor] = -50;


	}
}
}
