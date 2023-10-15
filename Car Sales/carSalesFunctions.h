#ifndef CARSALESFUNCTIONS_H
#define CARSALESFUNCTIONS_H
//prevents the header file from being included more than once


#define	MENU_OPTION_EXIT 'x'
#include <stdio.h> //used for printf, scanf, and file I/O
#include <string.h> //used for strcpy() and srtlen()
#include <stdlib.h>  //used for malloc() and free()
#include <ctype.h> //used for tolower() and isaplpha()

//function prototypes
void clearScreen();
void clearBuffer();
char getCharFromConsole(char message[201], char allowedCharacters[]);
unsigned short getUnsignedShortFromConsole(char message[201], unsigned short lowerBound, unsigned short upperBound);
void getAlphabeticalStringFromConsole(char* userInput, char message[201]);
void pauseProgramme(char menuSelection);




//clears the console (windows only)
void clearScreen() {
	system("cls"); //clears the terminal of all text
}


//clears the input buffer
void clearBuffer() {
	while (getchar() != '\n'); //empties the input buffer
}


/*
Takes a message to be displayed, a string of allowed characters
loops until user enters an allowed character
returns the character
*/
char getCharFromConsole(char message[201], char allowedCharacters[]) { 
	char userInput;

	printf(message); //prompts the user for an input with the given message
	do {
		scanf("\n%c", &userInput); //accepts an input from the command line
		userInput = tolower(userInput); //converts the inputed character to lower case, this is to make the programme more user friendsly e.g Y and y will both be valid inputs
		clearBuffer();

		for (int i = 0; i < (strlen(allowedCharacters)); i++) { //checks if the inputted character is present in the allowedCharacters array
			if (userInput == allowedCharacters[i]) {
				return userInput;
			}
		}
		printf("\nValid Input Not Entered, Please Try Again...\n"); //informs the user of the incorrect input and allows them to enter another charcter
	} while (1);
}



/*
Takes a message to be displayed, an upper and lower bound
loops until user enter a value between the upper and lower bounds (inclusive)
returns the value entered
*/
unsigned short getUnsignedShortFromConsole(char message[201], unsigned short lowerBound, unsigned short upperBound) {
	// will be used to store the captured number
	unsigned short userInput;


	do {
		printf(message); // prompt user using the value of the given message
		//scanf("%hd", &userInput);
		if (scanf("%hd", &userInput) == 1) { //check if the users input matches the short data type
			if (userInput < lowerBound || userInput > upperBound) { //check the users input is within the specified bounds
				printf("\nNumber Entered Is Not Within The Acceptable Range, Please Try Again.");
				clearBuffer();
				continue; //restarts the start of the loop
			}
			else { //exit the while loop
				//break;
				return userInput; //return the value, this also exits the while loop
			}
		}
		else {
			printf("\nValid Number Not Entered, Please Try Again."); //infrom the user of the incorrect input
			clearBuffer();
		}
	} while (1); //indefinate loop
}


/*
Takes a message to be displayed
loops until the user enters a string that only contains alphabetical characters
returns pointer to 1st index of a string
*/
void getAlphabeticalStringFromConsole(char* userInput, char message[201]) {

	/*
	Used to get a string from the user and test if it contains number or special characters

	special characters need to be removed as they can interfere with the rest of the programme
	(mainly comma's interfering with the save and load process)
	*/

	short isAllowed;
	//char userInput[100];
	printf("%s", message);
	do {
		isAllowed = 1;
		scanf("\n%[^\n]s", userInput);
		for (int i = 0; i < (strlen(userInput)); i++) {
			if (isalpha(userInput[i])) {
				continue;
			}
			else if (userInput[i] == '\0') {
				break;
			}
			else {
				isAllowed = 0;
				break;
			}

		}

		if (isAllowed == 1) {
			return;
		}
		printf("Valid Input Not Entered, Please Try Again...\n");
	} while (1);
}



//pauses the programme until a newline is entered
void pauseProgramme(char menuSelection) {
	if (menuSelection == MENU_OPTION_EXIT) {
		printf("Press Enter to Exit...");
		exit(0); //closes the programme with the code 0 (no issues)
	}
	else {
		printf("Press Enter to return to the menu...");
	}

	getchar();
}








#endif