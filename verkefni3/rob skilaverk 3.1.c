#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)
#pragma config(Motor,  port4,           armMotor,      tmotorNormal, openLoop)
#pragma config(Motor,  port5,           kloMotor,      tmotorNormal, openLoop)


// Program that using the controler for controling the robot

task main()
{
  while(1 == 1)
  {
    //Driving Motor Control
    motor[leftMotor] = vexRT[Ch3] / 2;
    motor[rightMotor] = vexRT[Ch2] / 2;

    //Arm Control
    if(vexRT[Btn6U] == 1)
    {
      motor[armMotor] = -40;
    }
    else if(vexRT[Btn6D] == 1)
    {
      motor[armMotor] = 40;
    }
    else
    {
      motor[armMotor] = 0;
    }
    //Klo control
    if(vexRT[Btn5U] == 1)
    {
      motor[kloMotor] = -40;
    }
    else if(vexRT[Btn5D] == 1)
    {
      motor[kloMotor] = 40;
    }
    else
    {
      motor[kloMotor] = 0;
    }
  }
}
