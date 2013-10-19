#pragma config(Sensor, in2,    pot1,           sensorPotentiometer)
#pragma config(Sensor, in3,    pot2,           sensorPotentiometer)
#pragma config(Sensor, dgtl2,  lim1,           sensorTouch)
#pragma config(Sensor, dgtl3,  lim2,           sensorTouch)
#pragma config(Motor,  port2,           motor1,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           motor2,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           servo1,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           servo2,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           motor3,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           motor4,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           servo3,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port9,           servo4,        tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

 int BtnX;
 int servoCount;
 int servoCountMax = 1000;
 int servoValue1 = 0;
 int servoValue2 = 0;
 int servoValue3 = 0;
 int servoValue4 = 0;
 int tempPot2 = 0;
 int servoSpeedCounter = 0;
 int boolAllowDeploy = 0;

void stepServo(tMotor motorPort, int t1) //move servo at given speed
{
	servoCount = 0;
	if(servoSpeedCounter - floor(servoSpeedCounter/10)*10 == 0)
		{
			motor[motorPort] = motor[motorPort] + t1;
		}
  if(motor[servo1] > 110)
  	{
  		motor[motorPort] = 110;
  	}
  if(motor[servo2] < -100)
  	{
  		motor[motorPort] = -100;
  	}
}

void limBase(tMotor mot1, tSensors sens1, tSensors sens2) //stop motor if limswitch pressed
{
	if(SensorValue[sens1] == 1 && vexRT[Ch4] > 0)
		{
		motor[mot1] = 0;
		}
	if(SensorValue[sens2] == 1 && vexRT[Ch4] < 0)
		{
		motor[mot1] = 0;
		}
}

void moveToPosition(tMotor motP,
										tSensors potP,
										int target,
										int speedP,
										int pointErrorP,
										int trajDiff1,
										int trajDiff2,
										float divideSpeed1,
										float divideSpeed2)
{
	while(SensorValue[potP] > target + pointErrorP || SensorValue[potP] < target - pointErrorP &&
		    vexRT[Ch3] < 10 && vexRT[Ch3] > -10)
	{
		if(SensorValue[potP] < target)
		{
			if(SensorValue[potP] < target - trajDiff1)
				{
					motor[motP] = -speedP;
				}
			if(SensorValue[potP] > target - trajDiff1 && SensorValue[potP] < target - trajDiff2)
				{
					motor[motP] = -speedP*divideSpeed1;
				}
			if(SensorValue[potP] > target - trajDiff2)
				{
					motor[motP] = -speedP*divideSpeed2;
				}
		}

		if(SensorValue[potP] > target)
		{
		if(SensorValue[potP] > target + trajDiff1)
			{
				motor[motP] = speedP;
			}
		if(SensorValue[potP] < target + trajDiff1 && SensorValue[potP] > target + trajDiff2)
			{
				motor[motP] = speedP*divideSpeed1;
			}
		if(SensorValue[potP] < target + trajDiff2)
			{
				motor[motP] = speedP*divideSpeed2;
			}
		}
		}
	motor[motP] = 0;
}

void clawOpenCloseCenter(tMotor leftFinger,
									 			 tMotor rightFinger,
									 			 tMotor servoUpDown,
									 			 tMotor servoLeftRight,
									 			 int speedB,
									 			 int Btn2)
{
	switch(Btn2)
		{
		case 1: //5U
		stepServo(leftFinger, speedB);
   	break;

   	case 2: //5D
   	stepServo(leftFinger, -speedB);
   	break;

   	case 64: //6U
   	stepServo(rightFinger, -speedB);
    break;

    case 65: //5U && 6U
    stepServo(leftFinger, speedB);
    stepServo(rightFinger, -speedB);
    break;

    case 66: //5D && 6U
    stepServo(leftFinger, -speedB);
    stepServo(rightFinger, -speedB);
    break;

    case 128: //6D
    stepServo(rightFinger, speedB);
    break;

    case 129: //5U && 6D
    stepServo(leftFinger, speedB);
    stepServo(rightFinger, speedB);
    break;

    case 130: //5D && 6D
    stepServo(leftFinger, -speedB);
    stepServo(rightFinger, speedB);
    break;

    case 3840: //all 5 && all 6
    motor[servoUpDown] = 0;
    motor[servoLeftRight] = 0;
    break;

    default:
   	wait1Msec(3);
		}
}

void extendArm(tMotor igusMotor,
							 int speedI,
							 int Btn3)
{
	switch(Btn3)
		{
		case 4: //7U
		motor[igusMotor] = speedI;
		break;

		case 16: //7D
		motor[igusMotor] = -speedI;
		break;

		default:
		motor[igusMotor] = 0;
		}
}

void autonomousFcns(int Btn4)
{
	switch(Btn4)
		{
		case 1024: //8D pick up dowels
		servoCount = 0;
		moveToPosition(motor1, pot2, 3500, 120, 3, 512, 256, 0.8, 0.5);
		motor[servo1] = 60;
		motor[servo2] = -60;
		motor[servo3] = -127;
		motor[servo4] = -127;
		break;

		case 256: //8U pick up circuitboard pieces
		servoCount = 0;
		moveToPosition(motor1, pot2, 4000, 120, 3, 512, 256, 0.8, 0.5);
		motor[servo3] = -98;
		motor[servo4] = -127;
		break;

		case 512: //base until hit limswitch
	  while(vexRT[Ch4] < 20 && vexRT[Ch4] > -20 && SensorValue[lim1] == 0 && SensorValue[lim2] == 0)
	  	{
	  	motor[motor4] = 80;
	  	}
		break;

		case 2048: //base until hit limswitch
		while(vexRT[Ch4] < 20 && vexRT[Ch4] > -20 && SensorValue[lim1] == 0 && SensorValue[lim2] == 0)
	  	{
	  	motor[motor4] = -80;
	  	}
		break;
		}
}

void idleServo(tMotor servoMotor, int servoValue, int tolerance)
{
	if((motor[servoMotor] - servoValue > tolerance)||(motor[servoMotor] - servoValue < -tolerance))
		{
		motor[servoMotor] = servoValue;
		}
}

task main()
{

 while(boolAllowDeploy == 0)
   {
      wait1Msec(10);
      if(vexRT[Btn7L] == 1)
      	{
      	//motor[motor3] = 60;
      	boolAllowDeploy = 1;
      	}
   }
if(boolAllowDeploy == 1){
 while(true)
  {
  	//prevents servos from drooping over time
  	if(servoCount == 2)
  		{
  			servoValue1 = motor[servo1];
 				servoValue2 = motor[servo2];
 				servoValue3 = motor[servo3];
 				servoValue4 = motor[servo4];
  		}

  	if(servoCount >= servoCountMax/8)
  		{
  			idleServo (servo1, servoValue1, 2);
  			idleServo (servo2, servoValue2, 2);
  			idleServo (servo3, servoValue3, 2);
  		  idleServo (servo4, servoValue4, 2);
  		}

  	if(servoCount == servoCountMax)
  		{
  			servoCount = 0;
  		}

  	servoCount++; //variable for idle control of servo
  	servoSpeedCounter++; //variable for servo speed control

  	motor[motor4] = vexRT[Ch4]; //base motor controlled by joystick ch4
  	motor[motor1] = -vexRT[Ch3];

  	tempPot2 = SensorValue[pot2]; //store value of potentiometer
  	if(tempPot2 > 2000 && tempPot2 < 3300 && vexRT[Ch3] < 30 && vexRT [Ch3] > -30)
  		{
  			motor[motor1] = 50;
  		}

  	limBase(motor4, lim1, lim2); //limit switch controls for base

    //dead zones for motors
  	if(abs(vexRT[Ch4]) < 30)
  		{
  		motor[motor4] = 0;
  		}

		BtnX = 0;
   //assign values to buttons to change value of BtnX
   if (vexRT[Btn5U] == 1){
     BtnX = BtnX + 1;}

   if (vexRT[Btn5D] == 1){
     BtnX = BtnX + 2;}

   if (vexRT[Btn7U] == 1){
     BtnX = BtnX + 4;}

   if (vexRT[Btn7L] == 1){
     BtnX = BtnX + 8;}

   if (vexRT[Btn7D] == 1){
     BtnX = BtnX + 16;}

   if (vexRT[Btn7R] == 1){
     BtnX = BtnX + 32;}

   if (vexRT[Btn6U] == 1){
     BtnX = BtnX + 64;}

   if (vexRT[Btn6D] == 1){
     BtnX = BtnX + 128;}

   if (vexRT[Btn8U] == 1){
     BtnX = BtnX + 256;}

   if (vexRT[Btn8L] == 1){
     BtnX = BtnX + 512;}

   if (vexRT[Btn8D] == 1){
     BtnX = BtnX + 1024;}

   if (vexRT[Btn8R] == 1){
     BtnX = BtnX + 2048;}

   if ((vexRT[Btn7D] == 0)&&(vexRT[Btn7U] == 0)&&(vexRT[Btn7L] == 0)&&(vexRT[Btn7R] == 0)
     &&(vexRT[Btn8D] == 0)&&(vexRT[Btn8U] == 0)&&(vexRT[Btn8L] == 0)&&(vexRT[Btn8R] == 0)
     &&(vexRT[Btn5U] == 0)&&(vexRT[Btn5D] == 0)&&(vexRT[Btn6U] == 0)&&(vexRT[Btn6D] == 0)){
     BtnX = 0;}

   clawOpenCloseCenter(servo1, servo2, servo3, servo4, 1, BtnX); //claw control
   extendArm(motor3, 127, BtnX); //igus arm control
   autonomousFcns(BtnX); //autonomous

   //joystick ch1 controls servo4
    if((vexRT[Ch1] <= -30) && (vexRT[Ch1] > -80))
		{
			stepServo(servo4, -2);
		}
		else if((vexRT[Ch1] <= -80) && (vexRT[Ch1] > -110))
		{
			stepServo(servo4, -4);
		}
		else if(vexRT[Ch1] <= -110)
		{
			stepServo(servo4, -6);
		}
		if((vexRT[Ch1] >= 30) && (vexRT[Ch1] < 80))
		{
			stepServo(servo4, 2);
		}
		else if((vexRT[Ch1] >= 80) && (vexRT[Ch1] < 110))
		{
			stepServo(servo4, 4);
		}
		else if(vexRT[Ch1] >= 110)
		{
			stepServo(servo4, 6);
		}

		//joystick ch2 controls servo3
    if((vexRT[Ch2] <= -30) && (vexRT[Ch2] > -80))
		{
			stepServo(servo3, -1);
		}
		if((vexRT[Ch2] <= -80) && (vexRT[Ch2] > -110))
		{
			stepServo(servo3, -2);
		}
		if(vexRT[Ch2] <= -110)
		{
			stepServo(servo3, -3);
		}
		if((vexRT[Ch2] >= 30) && (vexRT[Ch2] < 80))
		{
			stepServo(servo3, 1);
		}
		if((vexRT[Ch2] >= 80) && (vexRT[Ch2] < 110))
		{
			stepServo(servo3, 2);
		}
		if(vexRT[Ch2] >= 110)
		{
			stepServo(servo3, 3);
		}
	}
}
}
