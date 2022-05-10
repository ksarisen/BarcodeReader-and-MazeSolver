#pragma config(StandardModel, "EV3_REMBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const int speed = 5;
task main()
{
	//move from start box in virtual world; comment out this if in physical world
	setMotorTarget(rightMotor,2*360,5*speed);
	setMotorTarget(leftMotor,2*360,5*speed);
	waitUntilMotorStop(rightMotor);
	waitUntilMotorStop(leftMotor);

	//go up to start of barcode; start up light sensor to skip initial value
	int temp=0;
	while (temp<5){
		getColorReflected(colorSensor);
		temp++;
		sleep(100);
	}
	while (getColorReflected(colorSensor)>99){
		displayCenteredBigTextLine(2, "ColorValue %d",getColorReflected(colorSensor));
		setMotorSpeed(rightMotor,5*speed);
		setMotorSpeed(leftMotor,5*speed);
	}

	//stop at start of barcode
	setMotorSpeed(rightMotor,0);
	setMotorSpeed(leftMotor,0);
	waitUntilMotorStop(rightMotor);
	waitUntilMotorStop(leftMotor);

	//flush data on file
	displayCenteredBigTextLine(2, "BARCODE READ");
	datalogFlush();
	datalogClose();
	datalogClear();

	// Argument 1: Datalog index; Argument 2: Columns; Argument 3: Append option
	bool datalogOpenSuccess = datalogOpen(0, 1, false);
	if (!datalogOpenSuccess) {
		displayCenteredBigTextLine(6, "Unable to open datalog.");
	}
	//datalog
	//Adjust motor encoder to length of barcode; Adjust speed if in RVW or physical world
	while(getMotorEncoder(leftMotor)<5400) {
		setMotorSpeed(leftMotor, 3.2*speed);
		setMotorSpeed(rightMotor, 3.2*speed);
		datalogDataGroupStart();
		datalogAddValue(1, getColorReflected(colorSensor));
		sleep(300);
		datalogDataGroupEnd();

	}
	//close the log file
	datalogClose();
}
