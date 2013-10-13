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
 int servoCountMax = 50;
 int servoValue1 = 0;
 int servoValue2 = 0;
 int servoValue3 = 0;
 int servoValue4 = 0;
 int tempPot2 = 0;

void stepServo(tMotor motorPort, float t1) //move servo at given speed
{
	servoCount = 0;
	motor[motorPort] = motor[motorPort] + t1;
  wait1Msec(2);
}

void limMotor(tMotor mot1, tSensors sens1, tSensors sens2) //stop motor if limswitch pressed
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

void clawGoToPosition(tMotor first, tMotor second, tMotor third, tMotor fourth,
											int t4, int t5, int t6, int t7)
{
	motor[first] = t4;
	motor[second] = t5;
	motor[third] = t6;
	motor[fourth] = t7;
}

void moveAtAngle(tMotor motA,
								 tSensors potA,
								 int angle,
								 int speedA,
								 int pointErrorA,
								 int startPositionA,
								 float divideAngle1,
								 float divideAngle2,
								 float divideSpeed1,
								 float divideSpeed2)
{
	int z1 = startPositionA + angle*divideAngle1;
	int z2 = startPositionA + angle*divideAngle2;
	while(SensorValue[potA] > (startPositionA + angle) + pointErrorA ||  SensorValue[potA] < (startPositionA + angle) - pointErrorA)
		{
	  if(SensorValue[potA] < startPositionA + angle)
	  	{
			if(SensorValue[potA] < z1)
			{
				motor[motA] = speedA;
			}
			if(SensorValue[potA] < z1 + z2 - startPositionA &&
			 SensorValue[potA] > z1)
			{
				motor[motA] = speedA*divideSpeed1;
			}
			if(SensorValue[potA] > z1 + z2 - startPositionA)
			{
				motor[motA] = speedA*divideSpeed2;
			}
	  	}
	  if(SensorValue[potA] > startPositionA + angle)
	  	{
			if(SensorValue[potA] < angle + z2)
			{
				motor[motA] = -speedA*divideSpeed2;
			}
			if(SensorValue[potA] < angle + z1 &&
			   SensorValue[potA] > angle + z2)
			{
				motor[motA] = -speedA*divideSpeed1;
			}
			if(SensorValue[potA] > angle + z1)
			{
				motor[motA] = -speedA;
			}
	  	}
		}
	motor[motA] = 0;
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
	while(SensorValue[potP] > target + pointErrorP || SensorValue[potP] < target - pointErrorP)
	{
		if(SensorValue[potP] < target)
		{
			if(SensorValue[potP] < target - trajDiff1)
				{
					motor[motP] = speedP;
				}
			if(SensorValue[potP] > target - trajDiff1 && SensorValue[potP] < target - trajDiff2)
				{
					motor[motP] = speedP*divideSpeed1;
				}
			if(SensorValue[potP] > target - trajDiff2)
				{
					motor[motP] = speedP*divideSpeed2;
				}
		}

		if(SensorValue[potP] > target)
		{
		if(SensorValue[potP] > target + trajDiff1)
			{
				motor[motP] = -speedP;
			}
		if(SensorValue[potP] < target + trajDiff1 && SensorValue[potP] > target + trajDiff2)
			{
				motor[motP] = -speedP*divideSpeed1;
			}
		if(SensorValue[potP] < target + trajDiff2)
			{
				motor[motP] = -speedP*divideSpeed2;
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

void autonomousFcns(int Btn4, int startPos)
{
	switch(Btn4)
		{
		case 256: //8U
		servoCount = 0;
		moveAtAngle(motor1, pot2, 15, 500, 3, startPos, 0.5, 0.25, 0.75, 0.5);
		break;

		case 1024: //8D
		servoCount = 0;
		moveToPosition(motor4, pot1, 2048, 80, 3, 1024, 512, 0.7, 0.3);
		moveToPosition(motor1, pot2, 1024, 80, 3, 512, 256, 0.7, 0.3);
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

void idleElbow(int tolerance2, int tempVal)
{
	if(vexRT[Ch3] == 0)
			{
				if((SensorValue[pot2] - tempVal) > tolerance2)
			  	{
			  		motor[motor1] = -110;
			  	}
			  if((SensorValue[pot2] - tempVal) < -tolerance2)
			  	{
			  		motor[motor1] = 110;
			  	}
			  	motor[motor1] = 0;
			}
}

task main()
{
 int x = SensorValue[pot1];

 while(true)
  {
  	//prevents servos and elbow from drooping over time
  	if(servoCount == 2)
  		{
  			servoValue1 = motor[servo1];
 				servoValue2 = motor[servo2];
 				servoValue3 = motor[servo3];
 				servoValue4 = motor[servo4];
 				tempPot2 = SensorValue[pot2];
  		}

  	if(servoCount == servoCountMax)
  		{
  			idleServo (servo1, servoValue1, 2);
  			idleServo (servo2, servoValue2, 2);
  			idleServo (servo3, servoValue3, 2);
  			idleServo (servo4, servoValue4, 2);
  			idleElbow(3, tempPot2);
  			servoCount = 0;
  		}

  	 servoCount++;

  	motor[motor4] = vexRT[Ch4]; //base motor controlled by joystick ch4
  	motor[motor1] = -vexRT[Ch3]; //elbow motor controlled by joystick ch3

    //dead zones for motors
  	if(abs(vexRT[Ch3]) < 30)
  		{
  		motor[motor1] = 0;
  		}

  	if(abs(vexRT[Ch4]) < 30)
  		{
  		motor[motor4] = 0;
  		}

		limMotor(motor4, lim1, lim2);

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

   clawOpenCloseCenter(servo1, servo2, servo3, servo4, 1, BtnX);
   extendArm(motor3, 127, BtnX);
   autonomousFcns(BtnX, x);

   //joystick ch1 controls servo4
    if((vexRT[Ch1] <= -30) && (vexRT[Ch1] > -80))
		{
			stepServo(servo4, -1);
		}
		else if((vexRT[Ch1] <= -80) && (vexRT[Ch1] > -110))
		{
			stepServo(servo4, -2);
		}
		else if(vexRT[Ch1] <= -110)
		{
			stepServo(servo4, -3);
		}

		if((vexRT[Ch1] >= 30) && (vexRT[Ch1] < 80))
		{
			stepServo(servo4, 1);
		}
		else if((vexRT[Ch1] >= 80) && (vexRT[Ch1] < 110))
		{
			stepServo(servo4, 2);
		}
		else if(vexRT[Ch1] >= 110)
		{
			stepServo(servo4, 3);
		}

		//joystick ch2 controls servo3
    if((vexRT[Ch2] <= -40) && (vexRT[Ch2] > -80))
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

		if((vexRT[Ch2] >= 40) && (vexRT[Ch2] < 80))
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
