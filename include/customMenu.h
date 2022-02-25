
#include "vex.h"
#include "robot-config.h"

using namespace std;
using namespace vex;

//-------------------------------------------------------------------------------
//GLOBAL VARIABLES THAT WONT CHANGE
//Defining buttons for easy coding
//-------------------------------------------------------------------------------
#define btnNONE				0
#define btnUP				  1
#define btnDOWN				2
#define btnLEFT				3
#define btnRIGHT			4
#define btnA				  5
#define btnB			   	6
#define btnX				  7
#define btnY				  8
#define btnR1				  9
#define btnR2				  10
#define btnL1				  11
#define btnL2				  12


//Define delays 
#define bounceDelay			20		//Time to wait between reads to check for key bounce
#define refreshDelay		150		//Time to wait between refreshing screens

//Define usable screen space for easy coding
#define screenTextWidth		16		//Max characters you can print on one line
#define screenTextHeight	3		//Max lines of text that can show on the controller

//Define max entries in 2d array for easy coding
#define maxMenus		   	3		//Make this the same # as items in maxMenusIndex
#define maxOptions			3		//Make this the same # as items in 2D of menuDisplayIndex

//Define robot status for easy coding
#define modeDisabled		0
#define modeDriver			1
#define modeAuton	  		2
#define modeError	  		3

//Define more robot info for easy coding
#define BLUE		    		0
#define RED				    	1
#define GOALSIDE				0
#define RAMPSIDE			  1
#define SKILLS		      2
#define ARCADE			    0
#define TANK				    1
#define AUTON_COLOR			0
#define AUTON_TYPE			1
#define AUTON_DRIVE			2

//-------------------------------------------------------------------------------
//Declaring functions
//Functions to create interactable menu (dont change?)
//-------------------------------------------------------------------------------
int keyPressed();										//Filtered button inputs
int currStatus();										//Gets current robot status
void clearLine(int l_row);								//Smart row clearer
void clearScreen();										//Smart screen clearer
void print(std::string text, int row, int col);			//Prints without overwriting selector
void selector(int row);									//Prints selector
void displayMenu(int currRow, int configuration[]);		//Prints config menu
int getValues(int wantConfig);							//Returns current values of configuration[]

//Pre-built programs
void notificationHUD(std::string str);					//Prints a message on first line
void statusHUD();										//Prints current robot status on two lines
void menuCONFIG();										//Runs complete config menu


