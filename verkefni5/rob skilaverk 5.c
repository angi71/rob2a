#pragma config(Sensor, in5,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in6,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in7,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop, reversed)


// Program that follows after a white line on the floor

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

task stop_button(){
while(vexRT[Btn8R] == 0)
{
}
StopAllTasks();
}
//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	task display();
	task stop_button();
  wait1Msec(2000);

  int threshold = 2500;
  int leftThreshold = 2650;

  while(true)
  {

    if(SensorValue(lineFollowerRIGHT) < threshold)
    {

      motor[leftMotor]  = 40;
      motor[rightMotor] = 0;
    }

    if(SensorValue(lineFollowerCENTER) < threshold)
    {

      motor[leftMotor]  = 40;
      motor[rightMotor] = 40;
    }

    if(SensorValue(lineFollowerLEFT) < leftThreshold)
    {

      motor[leftMotor]  = 0;
      motor[rightMotor] = 40;
    }
  }
}
