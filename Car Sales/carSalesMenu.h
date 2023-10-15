#ifndef CARSALESMENU_H
#define CARSALESMENU_H

//greets the users
//void menu_greetUser();

/*
displays the cars id, model, its price, and how many are in stock
calls bsort beforehand to sort by stock remaining decending
*/
//void menu_viewStock(car* carArray);

/*
displays all sales and customer infomation
calls bsort to sort by revenue decending
*/
//void menu_viewSales(car* carArray, customer* customerArray);


void menu_greetUser() { //greets the users and provides them with the programmes main menu
	printf("Welcome to the 100%% reliable used car sales office!\n\n");
}

void menu_viewStock(car* carArray) {

	//sorts the car array by stock remaining(decending)
	qsort(carArray, NUMBER_OF_CAR_MODELS, sizeof(car), compareStock);

	printf("\nID: Car Model: Price:  Avaliable:\n"); //displays the cars id, model, its price, and how many are in stock in the order determined by the quick sort
	for (int i = 0; i < NUMBER_OF_CAR_MODELS; i++) {
		printf("%d - %s -  $%.0f - %d\n",
			carArray[i].id,
			carArray[i].model,
			(1000 * carArray[i].price),
			carArray[i].stock);
	}
}

void menu_viewSales(car* carArray, customer* customerArray) {

	printf("\nCustomer Sales Details:");
	for (int i = 0; i < saleID; i++) {

		//displays the sale ID, how many cars were bought, how much revenue each model has made, the customers name and age, if a discount was given and how much that discount was
		printf("\n\nSales ID: %d"
			"\n   Cars Bought:		%d"
			"\n   Sale Amount:		$%.2f"
			"\n   Customer Name:	%s"
			"\n   Customer Age:	%d"
			"\n   Discount Given:	%d"
			"\n   Reason For Discount:	%s"
			"\n   Discount Percent:	%%%.2f"
			"\n   Discount Value:	$%.2f\n",
			i,
			customerArray[i].numberBought,
			customerArray[i].total,
			customerArray[i].name,
			customerArray[i].age,
			customerArray[i].discountAplied,
			customerArray[i].discountReason,
			(100 * customerArray[i].discountPercent),
			customerArray[i].discountAmount);


		printf("   Model of car(s) bought: "); //displays what cars each individual bought
		for (int j = 0; j < customerArray[i].numberBought; j++) {
			printf("%s, ", carArray[customerArray[i].carsBought[j]].model);
		}
		printf("\n\n");
		for (int l = 0; l < 40; l++) {
			printf("*");
		}
	}


	//sorts the car data by revenue(decending)
	qsort(carArray, NUMBER_OF_CAR_MODELS, sizeof(car), compareRevenue);

	printf("\n\nCar Sales Details:\n");
	printf("\nCar Model:  Number Sold: Revenue:\n");
	for (int i = 0; i < NUMBER_OF_CAR_MODELS; i++) { //itterates though and displays the car model, how many have been sold and the revenue of each model
		printf("%s    -    %d     -    $%.2f\n",
			carArray[i].model,
			carArray[i].sold,
			carArray[i].revenue
			);
	}
	printf("\n");
}



#endif