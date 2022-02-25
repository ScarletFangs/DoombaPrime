#include "vex.h"
#include "robot-config.h"
#include "customMenu.h"

using namespace std;
using namespace vex;

competition competition1;

//-------------------------------------------------------------------------------
//DECLARING ARRAYS TO BE USED
//Changable Array depending on uses (CHECK BUTTONS)
//-------------------------------------------------------------------------------

bool isCursorOn = false;

string robotStatus[4]{
  "Robot Disabled",
  "Driver Control",
  "Auton Control",
  "MODE ERROR"
};

int maxMenuIndex[maxMenus]{
  2,
  3,
  2,
};

int configuration[maxMenus]{      //default options (first one going down line)
  0,
  0,
  0,
};

string menuTypes[maxMenus]{
  "Color: ",
  "Aim: ",
  "Drive: "
};

string menuOptions[maxMenus][maxOptions]{
  {"Blue", "Red", ""},
  {"GOAl:SAFE", "GOAL:RAMP", "Skills"},
  {"Arcade", "Tank", ""}
};

//-------------------------------------------------------------------------------
//Function definitions
//Functions to create interactable menu (dont change?)
//-------------------------------------------------------------------------------

//return value for button pressed (refer to .h)
int keyPressedRaw(){
	if (controller1.ButtonUp.pressing() == true)
	{
		return btnUP;
	}
	if (controller1.ButtonDown.pressing() == true)
	{
		return btnDOWN;
	}
	if (controller1.ButtonLeft.pressing() == true)
	{
		return btnLEFT;
	}
	if (controller1.ButtonRight.pressing() == true)
	{
		return btnRIGHT;
	}
	if (controller1.ButtonA.pressing() == true)
	{
		return btnA;
	}
	if (controller1.ButtonB.pressing() == true)
	{
		return btnB;
	}
	if (controller1.ButtonX.pressing() == true)
	{
		return btnX;
	}
	if (controller1.ButtonY.pressing() == true)
	{
		return btnY;
	}
	if (controller1.ButtonR1.pressing() == true)
	{
		return btnR1;
	}
	if (controller1.ButtonR2.pressing() == true)
	{
		return btnR2;
	}
	if (controller1.ButtonL1.pressing() == true)
	{
		return btnL1;
	}
	if (controller1.ButtonL2.pressing() == true)
	{
		return btnL2;
	}
	else
	{
		return btnNONE;
	}
}

//returns clean values(no bounce)
int keyPressed(){
	int noBounceKey = keyPressedRaw();
	vex::task::sleep(bounceDelay);
	if (noBounceKey == keyPressedRaw())
	{
		return noBounceKey;
	}
	else
	{
		return btnNONE;
	}
}

//current status of robot
int currStatus(){
	int status;
	if (competition1.isEnabled()) //If robot is enabled, check what mode/period the match is in
	{
		if (competition1.isAutonomous()) {
			status = modeAuton; //Robot is in Autonomous mode
		}
		else if (competition1.isDriverControl()) {
			status = modeDriver; //Robot is in Driver Control mode
		}
		else
		{
			status = modeError; //ERROR MODE 
		}
	}
	else
	{
		status = modeDisabled; //Robot is Disabled
	}
	return status;
}

//clear line
void clearLine(int l_row){ //select what row to clear but not selector if isCursorOn = true
	if (isCursorOn == true)
	{
		controller1.Screen.setCursor(l_row + 1, 2);	//Prevent overwrite of selector GUI
		controller1.Screen.print("               "); //15 spaces (1 less than screenTextWidth)
	}
	else
	{
		controller1.Screen.clearLine();	//If isCursorOn = false, wipe line with system clearLine
	}
}

//clear screen
void clearScreen(){ //clears everything but not selector if isCursorOn = true
	if (isCursorOn == true)
	{
		for (int row = 0; row < screenTextHeight; row++) //loops rows
		{
			clearLine(row);
		}
	}
	else
	{
		controller1.Screen.clearScreen();	//If isCursorOn = false, wipe line with system clearScreen
	}

}

//print
void print(std::string text, int row, int col){ //pass text, row, and col
	//NOTE: Does not call clearScreen, only clears current line
	clearLine(row);
	if (isCursorOn == true)
	{
		controller1.Screen.setCursor(row + 1, col + 2); //Col + 2: Prevent overwrite of selector GUI
	}
	else
	{
		controller1.Screen.setCursor(row + 1, col + 1); //Col + 1: Start from beginning
	}
	controller1.Screen.print(text.c_str()); //Future GUI will scroll text
}

//select (pass 0, 1, 2 to select what row)
void selector(int row){ //pass which row you want the selector to be
	isCursorOn = true;
	for (int i = 1; i <= screenTextHeight; i++) //clears just the selector GUI
	{
		controller1.Screen.setCursor(i, 1);
		controller1.Screen.print("|");
	}

	//reminder of row == row mod / 3 
	int showCursor = (row % screenTextHeight) + 1;
	controller1.Screen.setCursor(showCursor, 1);
	controller1.Screen.print(">");
}

//display actual menu (up to 3)
void displayMenu(int currRow, int configuration[]){ //pass wanted selector row 
	string temp;
	selector(currRow); //Display selector
	for (int i = 0; i < screenTextHeight; i++)
	{
		temp = menuTypes[i] + menuOptions[i][configuration[i]];
		print(temp, i, 0); //Display menu line i
	}
}

//get values
int getValues(int wantConfig){
	if (wantConfig > maxMenus)
	{
		return NULL;
	}
	else
	{
		return configuration[wantConfig];
	}
}


/*------------------------------------------------------------------------------------------------------
[STABLE] notificationHUD > Pre-built notification display. For use with status
------------------------------------------------------------------------------------------------------*/
void notificationHUD(std::string str){
	//notificationHUD v2019.5.14.16.10
	//Displays text on line 1 to notify drivers. 
	//Does not disappear unless overwritten.

	//Clears top row and prints user string
	clearLine(0);
	print(str, 0, 0);
}

/*------------------------------------------------------------------------------------------------------
[STABLE] statusHUD > Pre-built Heads Up Display (HUD) of current robot status
------------------------------------------------------------------------------------------------------*/
void statusHUD(){ //v2 needs no overloading values
	//statusHUD v2019.5.14.16.10
	//Displays current robot status and selected options on row 2 and 3 respectively.
	//Needs to be in loop or else it won't refresh (future versions should self-refresh)

	std::string temp;
	//Display current robot status
	print(robotStatus[currStatus()], 1, 0); //Show current robot status on line 2
	//Display previously selected options
	temp = menuOptions[0][configuration[0]] + " " + menuOptions[1][configuration[1]] + " " + menuOptions[2][configuration[2]]; //Color + space + Row + space + Drive
	print(temp, 2, 0); //Show Color + Row on line 3 
}

/*------------------------------------------------------------------------------------------------------
[STABLE] menuCONFIG > Pre-built complete config menu
------------------------------------------------------------------------------------------------------*/
void menuCONFIG() {
	//menuCONFIG v2019.3.14.15.20
	//Use D-pad to move the cursor around the menu to select settings.
	//It automatically saves the settings as you change between options (left/right buttons).
	//Press A button to exit menu.
	//Planned upgrades are seperate threads to manage display and button presses

	isCursorOn = true;
	int currCursorMenu = 0;		//Goes up and down of array
	int currCursorOptions = 0;	//Goes left and right of array

	bool isAutonSelectScreen = true;
	while (isAutonSelectScreen == true)
	{
		displayMenu(currCursorMenu, configuration);	//Refreshes the screen with all the elements

		bool isValidButton = false;
		while (isValidButton == false) //Only updates screen if button was pressed
		{
			switch (keyPressed())
			{
			case(btnUP):				//If up button pressed
				isValidButton = true;
				currCursorMenu--;		//Go up the array

				//Get new values from configuration
				currCursorMenu = (currCursorMenu + maxMenus) % maxMenus; //currCursorMenu % the amount of items in 1D array
				currCursorOptions = configuration[currCursorMenu];
				break;
			case(btnDOWN):				//If down button pressed
				isValidButton = true;
				currCursorMenu++;		//Go down the array

				//Get new values from configuration
				currCursorMenu = (currCursorMenu + maxMenus) % maxMenus; //currCursorMenu % the amount of items in 1D array
				currCursorOptions = configuration[currCursorMenu];
				break;
			case(btnLEFT):				//If left button pressed
				isValidButton = true;
				currCursorOptions--;	//Shift left of array

				//Update values back into configuration
				currCursorOptions = (currCursorOptions + maxMenuIndex[currCursorMenu]) % maxMenuIndex[currCursorMenu]; //currCursorOptions % the amount of options in 1D array
				configuration[currCursorMenu] = currCursorOptions; //Assign current menu(row) option(col) to configuration array
				break;
			case(btnRIGHT):				//If right button pressed
				isValidButton = true;
				currCursorOptions++;	//Shift right of array

				//Update values back into configuration
				currCursorOptions = (currCursorOptions + maxMenuIndex[currCursorMenu]) % maxMenuIndex[currCursorMenu]; //currCursorOptions % the amount of options in 1D array
				configuration[currCursorMenu] = currCursorOptions; //Assign current menu(row) option(col) to configuration array
				break;
			case(btnA):					//Select auton and exit
				isValidButton = true;
				isAutonSelectScreen = false;
				isCursorOn = false;
				break;
			default:
				break;
			}
		}
	}
}