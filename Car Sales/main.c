#define _CRT_SECURE_NO_WARNINGS //Used to allow scanf and other macros in Visual Studio

//contains the constants, structs and libraries used
#include "carSalesStructures.h" 

//contains the generic functions used
#include "carSalesFunctions.h"

//contains the functions for File I/O
#include "carSalesSaveLoad.h"

//contains the functions for the quick sort algorithm
#include "carSalesSort.h"

//contians the functions used for getting the car buying process
#include "carSalesBuyCars.h"

//contains the functions used for the main menu
#include "carSalesMenu.h"




void main() {
	car* carArray;
	carArray = malloc(sizeof(car) * NUMBER_OF_CAR_MODELS); //creates the array of car structs and allocates enough memory for all the cars

	customer* customerArray;
	customerArray = malloc(sizeof(customer) * MAX_SALES); //creates the array of customer structs and allocates enough memory for the maximum number of sales

	char menuSelection;

	loadCars(carArray);
	loadCustomers(customerArray);

	do {
		clearScreen();

		//Greeting and menu display
		menu_greetUser();
		menuSelection = getCharFromConsole("What would you like to do today ? \nMenu : \n a : Buy Cars\n b : View Car Stocks\n c : View Sales Data\n d : Save Data\n x : Exit Programme\n",
			"abcdx");


		clearScreen();

		switch (menuSelection) {
		case MENU_OPTION_BUY_CARS:
			menu_buyCars(carArray, customerArray);
			break;

		case MENU_VIEW_STOCK:
			menu_viewStock(carArray);
			break;

		case MENU_OPTION_VIEW_SALES: //menu check sales data
			menu_viewSales(carArray, customerArray);
			//save(carArray, customerArray);
			break;

		case MENU_OPTION_SAVE:
			if (saveCars(carArray) && saveCustomers(customerArray)) {
				printf("\nData Saved Successfully...\n");
			}
			break;

		case MENU_OPTION_EXIT:
			printf("\nThank You For Using The 100%% Reliable Used Car Sales Office.\nPlease Come Again Soon!\n\n\n");
			break;



		}
		pauseProgramme(menuSelection);

	} while (menuSelection != 'x');

	free(carArray);
	free(customerArray);
}








