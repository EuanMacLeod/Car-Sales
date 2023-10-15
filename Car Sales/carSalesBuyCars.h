#ifndef CARSALESBUYCARS_H
#define CARSALESBUYCARS_H

#define DISCOUNT_CARCLUB 1
#define DISCOUNT_MULTIBUY 2

//prototypes
void menu_buyCars(car* carArray, customer* customerArray);
void getCars(car* carArray, customer* customerArray, short* basket);
void showBasket(car* carArray, short basketLength, short* basket);
void getUserInfo(customer* customerArray);
void decideIfDiscountNeeded(customer* customerArray);
void menu_applyDiscountMember(customer* customerArray);
void menu_applyDiscountMultibuy(customer* customerArray);
void menu_applyDiscountNone(customer* customerArray);
void recordPurchase(car* carArray, customer* customerArray, short* basket);
void displaySaleInfo(customer* customerArray);


/*
The overarching function for allowing the user to buy cars
*/
void menu_buyCars(car* carArray, customer* customerArray) {
	short basket[MAX_CARS_PER_USER]; //array containing the ID of each car to be purchased by the user

	//sorts the array of car structs by the car ID(acending)
	qsort(carArray, NUMBER_OF_CAR_MODELS, sizeof(car), compareID);

	getCars(carArray, customerArray, basket);

	getUserInfo(customerArray);

	decideIfDiscountNeeded(customerArray);

	recordPurchase(carArray, customerArray, basket);

	displaySaleInfo(customerArray);

	saleID++; //updates sales ID ready for a new customer


	if (saveCars(carArray) && saveCustomers(customerArray)) { //saves the new customers data and also the car sales data
		printf("\nFiles Saved Successfully...\n");
	}
	else {
		printf("\nError Whilst Saving Files...\n");
	}
	return;

}

/*
takes a pointer to the 1st index of the basket array
gets the cars the user wishes to buy and saves them into the basket
*/
void getCars(car* carArray, customer* customerArray, short* basket) {
	short numberOfCarsBeingBought = 0;
	/*
	used to track the number of cars being bought, this also corresponds to the length of the basket array
	*/


	do {
		clearScreen();
		if (numberOfCarsBeingBought >= MAX_CARS_PER_USER) {
			printf("You Have Reached The Maximum Number Of Cars Allowed Per Person\n");
			break; //exit the loop
		}
		else if (numberOfCarsBeingBought > 0) {
			showBasket(carArray, numberOfCarsBeingBought, basket);
			char carSelectionMenuChoice = getCharFromConsole(
				"\nWhat Would You Like To Do?\na) Buy Another Car\nb) Remove The Last Car From Your Basket\nc) Continue To Total\n",
				"abc");
			if (carSelectionMenuChoice == 'a') {
				clearScreen();
			}
			else if (carSelectionMenuChoice == 'b') {
				numberOfCarsBeingBought--; //decriment the number of cars the user is buying
				carArray[basket[numberOfCarsBeingBought]].stock += 1; //add car being removed from the basket back in stock
				basket[numberOfCarsBeingBought] = '\0'; //set the last item in the basket to null
				continue; //restarts the loop
			}
			else if (carSelectionMenuChoice == 'c') {
				clearScreen();
				break; //exit the loop
			}

			showBasket(carArray, numberOfCarsBeingBought, basket);//displays the items in the basket
		}
		printf("\nMax %d cars per person\nYou may buy %hd more cars", MAX_CARS_PER_USER, (MAX_CARS_PER_USER - numberOfCarsBeingBought));
		printf("\nID: Car Model: Price:  Avaliable:\n");
		for (int i = 0; i < NUMBER_OF_CAR_MODELS; i++) { //displays the cars along with thier prices and how many are in stock
			printf("%d - %s -  $%.0f - %hd\n", i, carArray[i].model, (1000 * carArray[i].price), carArray[i].stock);
		}

		//sets the basket at the current index to the id of the car the user wishes to buy
		basket[numberOfCarsBeingBought] = getUnsignedShortFromConsole("\nEnter The ID of The Car You Wish To Buy: ", 0, 9);
		clearScreen();
		clearBuffer();
		if (carArray[basket[numberOfCarsBeingBought]].stock > 0) { //check if requested car model is in stock
			carArray[basket[numberOfCarsBeingBought]].stock -= 1;
			printf("%s added to your basket\n", carArray[basket[numberOfCarsBeingBought]].model);

			numberOfCarsBeingBought++;

		}
		else { //if not in stock then return to the buy menu
			clearScreen();
			printf("Sorry That Car Is Out Of Stock");
			printf("\nPress Enter To Continue...\n");
			getchar();
		}

	} while (1);

	showBasket(carArray, numberOfCarsBeingBought, basket);
	customerArray[saleID].numberBought = numberOfCarsBeingBought;


	return;

}

//displays the current car models in the basket
void showBasket(car* carArray, short basketLength, short* basket) {
	printf("Current Basket: ");
	for (int i = 0; i < basketLength; i++) { //itterate though the basket array and display the correspondsing car model
		printf("%s, ", carArray[basket[i]].model);
	}
	printf("\n");
}

//gets the users age and name then updates the customerArray
void getUserInfo(customer* customerArray) {
	getAlphabeticalStringFromConsole(customerArray[saleID].name, "\nWhat is your name?:");

	//char* customerName = getAlphabeticalStringFromConsole("\nWhat is your name?:");

	//strcpy(customerArray[saleID].name, customerName);

	customerArray[saleID].age = getUnsignedShortFromConsole("\nHow old are you?: ", 0, 100);
}

//decides if a discount is needed and calls the appropriate discount function
void decideIfDiscountNeeded(customer* customerArray) {
	float discountPercent = 0.0f;
	//records the discount infomation and returns the value of the discount
	if (getCharFromConsole("\nAre you a member of our car club? (Y/N): ", "yn") == 'y') {
		menu_applyDiscountMember(customerArray);
	}
	else if (customerArray[saleID].numberBought >= DISCOUNT_MULTIBUY_AMOUNT) {
		menu_applyDiscountMultibuy(customerArray);
	}
	else {
		menu_applyDiscountNone(customerArray);
	}


}

/*
one is called from decideIfDiscountNeeded depending on conditions
updates customer.discountAplied, customer.discountPercent and customer.discountReason
*/
void menu_applyDiscountMember(customer* customerArray) {
	clearScreen();
	customerArray[saleID].discountAplied = TRUE; //record that a discount was given
	customerArray[saleID].discountPercent = DISCOUNT_MEMBER_PERCENTAGE; //record the amount in %
	strcpy(customerArray[saleID].discountReason, "Club Member"); //records the reason for the discount
	printf("\nThank you for your continued patronage, a discount of %.0f%% has been applied, ", (100 * DISCOUNT_MEMBER_PERCENTAGE));
	return;
}
void menu_applyDiscountMultibuy(customer* customerArray) {
	clearScreen();
	customerArray[saleID].discountAplied = TRUE;
	customerArray[saleID].discountPercent = DISCOUNT_MULTIBUY_PERCENTAGE;
	strcpy(customerArray[saleID].discountReason, "Multi Buy");
	printf("\nBecause you're buying more than %d cars, a discount of %.0f%% has been applied, ", DISCOUNT_MULTIBUY_AMOUNT, (100 * DISCOUNT_MULTIBUY_PERCENTAGE));
	return;
}
void menu_applyDiscountNone(customer* customerArray) {
	clearScreen();
	customerArray[saleID].discountAplied = FALSE;
	customerArray[saleID].discountPercent = 0;
	strcpy(customerArray[saleID].discountReason, "N/A");
	printf("\nNo discount has been applied.\n");
	return;
}

/*
calculates the total price
also updates carArray.sold, carArray.revenue
and customerArray.carsBought, customerArray.total, customerArray.discountAmount
*/
void recordPurchase(car* carArray, customer* customerArray, short* basket) {
	float totalPrice = 0.0f;
	float discountMultiplier = (1.0f - customerArray[saleID].discountPercent); //calculates the multiplier for the discount

	for (int i = 0; i < customerArray[saleID].numberBought; i++) { //loop for the number of cars the user bought

		totalPrice += (discountMultiplier * carArray[basket[i]].price); //calculate the total price of the order

		carArray[basket[i]].sold += 1; //update number of each car model sold

		carArray[basket[i]].revenue += (1000 * discountMultiplier * carArray[basket[i]].price); //update the sales figures for each model

		customerArray[saleID].carsBought[i] = basket[i]; //records each idividual car purchased by each user

	}
	customerArray[saleID].total = (1000 * totalPrice);
	customerArray[saleID].discountAmount = ((customerArray[saleID].total / discountMultiplier) - customerArray[saleID].total); //records how much money the discount took off of the price
	return;
}

/*
displays to the user how many cars they've bought, the total cost
also if a discount was applied and the monetary value of that discount
*/
void displaySaleInfo(customer* customerArray) {

	if (customerArray[saleID].discountAplied) { //if the user received a discount then display how much $ they saved
		printf("you've saved $%.2f.\n", customerArray[saleID].discountAmount);
	}

	printf("\nYou've bought %hd car(s) for a total price of $%.2f.\n",
		customerArray[saleID].numberBought, customerArray[saleID].total);
	//informs user of how many cars are in thier order
	//printf("The total cost is $%.2f.\n", customerArray[saleID].total); //informs user of the price of thier order
	printf("\nMy cousin owns a mechanics shop down the road for when ... \n\nI mean if anything goes wrong, here's his number: 01632 123456\n\n"); //provides user with extended warenty options

	return;
}











#endif