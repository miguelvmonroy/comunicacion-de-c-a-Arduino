//This code snippet will help you to read data from arduino

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SerialPort.h"

using namespace std;

/*Portname must contain these backslashes, and remember to
replace the following com port*/
char *port_name = "\\\\.\\COM5";

//String for incoming data
char incomingData[MAX_DATA_LENGTH];

//String for getting the output from arduino
char output[MAX_DATA_LENGTH];

void writeArduino();
void readArduino();

int main()
{
	writeArduino();
	//readArduino();
	return 0;
}


void readArduino()
{
	SerialPort arduino(port_name);
  	if (arduino.isConnected()) cout << "Connection Established" << endl;
  	else cout << "ERROR, check port name";
  
  	while (arduino.isConnected()){
    	//Check if data has been read or not
    	int read_result = arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);
    	//prints out data
    	puts(incomingData);
    	//wait a bit
    	Sleep(10);
  	}
}


//Escribir ON para encender el LED u OFF para apagarlo
void writeArduino()
{
	SerialPort arduino(port_name);
	if (arduino.isConnected()) cout << "Connection Established" << endl;
	else cout << "ERROR, check port name";
	
	while (arduino.isConnected()){
		cout << "Escribe ON/OFF: \n";
		std::string input_string;
		//Getting input
		getline(cin, input_string);
		//Creating a c string
		char *c_string = new char[input_string.size() + 1];
		//copying the std::string to c string
		std::copy(input_string.begin(), input_string.end(), c_string);
		//Adding the delimiter
		c_string[input_string.size()] = '\n';
		//Writing string to arduino
		arduino.writeSerialPort(c_string, MAX_DATA_LENGTH);
		//Getting reply from arduino
		arduino.readSerialPort(output, MAX_DATA_LENGTH);
		//printing the output
		puts(output);
		//freeing c_string memory
		delete[] c_string;
	}
}
