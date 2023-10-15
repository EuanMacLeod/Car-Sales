#ifndef CARSALESSAVELOAD_H
#define CARSALESSAVELOAD_H

/*
CSV Format Reference
	car.csv:
		ID, Model, Price, Stock, Sold, Revenue


	customer.csv:
		Name, Age, DiscountAplied, DiscountPercent, DiscountAmount, DiscountReason, NumberBought, total
		CarsBought[0],CarsBought[1], ... CarsBought[n] //(n = NumberBought)

*/

//prototypes
short saveCars(car* carArray);
short saveCustomers(customer* customerArray);
void loadCars(car* carArray);
void loadCustomers(customer* customerArray);
void setCarValues(car* carArray);




short saveCars(car* carArray) {
	FILE* file; //pointer used to refference the file
	file = fopen("car.csv", "w"); //open the car.csv (or create one if there isn't one already) in write mode

	if (file == NULL) { //if the file isnt found after trying to create one then return an error
		printf("\nError Opening Car File During Save\n");
		return 0;
	}

	for (int i = 0; i < NUMBER_OF_CAR_MODELS; i++) { //loop for the number of car models
		fprintf(file, "%d,%s,%.2f,%d,%d,%f\n", //write the values stored in carArray[i] seperated by commas
			carArray[i].id,
			carArray[i].model,
			carArray[i].price,
			carArray[i].stock,
			carArray[i].sold,
			carArray[i].revenue);

		if (ferror(file)) {
			printf("\nError During Car File Write\n");
			return 0;
		}
	}

	fclose(file); //closes the car.csv
	//printf("\nCar Data Successfully Saved\n");
	return 1;
}

short saveCustomers(customer* customerArray) {
	FILE* file;
	file = fopen("customer.csv", "w"); //opens customer.csv in write mode

	if (file == NULL) {
		printf("\nError Opening Customer File During Save\n");
		return 0;
	}

	for (int i = 0; i < saleID; i++) { //loop for the number of sales conducted
		fprintf(file, "%s,%hd,%hd,%f,%f,%s,%d,%f\n",
			customerArray[i].name,
			customerArray[i].age,
			customerArray[i].discountAplied,
			customerArray[i].discountPercent,
			customerArray[i].discountAmount,
			customerArray[i].discountReason,
			customerArray[i].numberBought,
			customerArray[i].total);

		/*
		customerArray.carsBought is an array of int's and as such is formatted on a sepperate row with
		1 value per column for as many columns as need, after each line containing the other data

		customerArray.numberBought tracks the number of cars bought by a given customer
		and this corresponds to the number of columns needed to contain the .carsBought data
		*/

		for (int j = 0; j < customerArray[i].numberBought; j++) { //
			fprintf(file, "%d,", customerArray[i].carsBought[j]);

		}
		fprintf(file, "\n");

		if (ferror(file)) {
			printf("\nError During Customer File Write\n");
			return 0;
		}
	}

	fclose(file); //closes the customer.csv
	//printf("\nCustomer Data Successfully Saved\n");
	return 1;
}

void loadCars(car* carArray) {
	//pointer used to reference the loaded file
	FILE* file;


	//opens the car.csv in read mode
	file = fopen("car.csv", "r");


	//if the file cannot be opened then exit
	if (file == NULL)
	{
		char ignore = getCharFromConsole("Error opening car.csv (File Missing).\nWould you like to create a new file using the default values?(Y/N):",
			"yn");
		if (ignore == 'y') {
			setCarValues(carArray);
			saveCars(carArray);
			return;
		}
		else {
			exit(1);
		}
	}


	int read = 0; //used to track the number of values read per line
	int records = 0; //tracks the total number of lines read

	do
	{

		/*
		reads the given line then stores the values read into the appropriate car struct array
		*/


		read = fscanf(file,


			"%d,%19[^,],%f,%d,%d,%f\n", //%19[^,] will read for 19 characters or up until a comma, as it is a string a \0 null terminator will be placed on the end
			&carArray[records].id,
			&carArray[records].model,
			&carArray[records].price,
			&carArray[records].stock,
			&carArray[records].sold,
			&carArray[records].revenue);



		if (read == 6) records++; //we expect to read 6 values, if so then we can continue to the next line

		if (read != 6 && !feof(file))//if 6 values are not read and it isnt the end of the file then an error has occured
		{
			printf("read = %d", read);
			printf("car.csv formatted incorrectly.\n"); //inform the user and exit the programme with an error status
			exit(1);
		}


		if (ferror(file))
		{
			printf("Error whilst reading car.csv.\n");
			exit(1);
		}

	} while (!feof(file)); //continues until the end of the file is reached


	fclose(file);//close the car file
	printf("\ncar.csv read successfully\n");
}

void loadCustomers(customer* customerArray) {
	FILE* file;
	file = fopen("customer.csv", "r"); //opens the customer file in read mode

	if (file == NULL)
	{
		char ignore = getCharFromConsole("Error opening customer.csv (File Missing).\nWould you like to continue anyway?(Y/N):",
			"yn");
		if (ignore == 'y') {
			saveCustomers(customerArray);
			return;
		}
		else {
			exit(1);
		}
	}

	int read = 0;
	int records = 0;

	do
	{
		//read all the infomation on one line and store it into the appropriate customer array
		read = fscanf(file,


			"\n%99[^,],%hd,%hd,%f,%f,%19[^,],%d,%f\n",
			&customerArray[records].name,
			&customerArray[records].age,
			&customerArray[records].discountAplied,
			&customerArray[records].discountPercent,
			&customerArray[records].discountAmount,
			&customerArray[records].discountReason,
			&customerArray[records].numberBought,
			&customerArray[records].total);

		/*
		customerArray.carsBought is a 2d array of int's and is formatted with
		1 value per line for as many lines as need, after each line containing the other data

		customerArray.numberBought tracks the number of cars bought for a given customer
		and this corresponds to the number of lines needed to contain the .carsBought data
		*/

		//fscanf(file, "\n");
		for (int i = 0; i < customerArray[records].numberBought; i++) {
			fscanf(file, "%d,", &customerArray[records].carsBought[i]);
		}


		if (read == 8) records++; //we expect to read 8 values (.carsBought are not counted), if so then then continue to the next line of the csv

		if (read != 8 && !feof(file))//if we did not read 8 values and the file hasn't ended then exit with an error status
		{
			//printf("read = %d", read);
			printf("customer.csv Formatted Incorrectly.\n");
			exit(1);
		}


		if (ferror(file))
		{
			printf("Error whilst reading customer.csv.\n");
			exit(1);
		}

	} while (!feof(file)); //loop until the end of the file is reached


	saleID = records; //sets the saleID equal to the number of customer records that were read

	fclose(file); //closes the customer file
	printf("\ncustomer.csv read successfully\n");
}

/*
called by loadCars if no car.csv is found and if user accetps
sets all car values to default
*/
void setCarValues(car* carArray) {
	carArray[0].id = 0;
	strcpy(carArray[0].model, "Model A");
	//carArray[0].model = "Model A";
	carArray[0].price = 1.0f;
	carArray[0].stock = DEFAULT_CAR_STOCK;
	carArray[0].sold = 0;
	carArray[0].revenue = 0.0f;

	carArray[1].id = 1;
	strcpy(carArray[1].model, "Model B");
	carArray[1].price = 2.0f;
	carArray[1].stock = DEFAULT_CAR_STOCK;
	carArray[1].sold = 0;
	carArray[1].revenue = 0.0f;

	carArray[2].id = 2;
	strcpy(carArray[2].model, "Model C");
	carArray[2].price = 3.0f;
	carArray[2].stock = DEFAULT_CAR_STOCK;
	carArray[2].sold = 0;
	carArray[2].revenue = 0.0f;

	carArray[3].id = 3;
	strcpy(carArray[3].model, "Model D");
	carArray[3].price = 4.0f;
	carArray[3].stock = DEFAULT_CAR_STOCK;
	carArray[3].sold = 0;
	carArray[3].revenue = 0.0f;

	carArray[4].id = 4;
	strcpy(carArray[4].model, "Model E");
	carArray[4].price = 5.0f;
	carArray[4].stock = DEFAULT_CAR_STOCK;
	carArray[4].sold = 0;
	carArray[4].revenue = 0.0f;

	carArray[5].id = 5;
	strcpy(carArray[5].model, "Model F");
	carArray[5].price = 6.0f;
	carArray[5].stock = DEFAULT_CAR_STOCK;
	carArray[5].sold = 0;
	carArray[5].revenue = 0.0f;

	carArray[6].id = 6;
	strcpy(carArray[6].model, "Model G");
	carArray[6].price = 7.0f;
	carArray[6].stock = DEFAULT_CAR_STOCK;
	carArray[6].sold = 0;
	carArray[6].revenue = 0.0f;

	carArray[7].id = 7;
	strcpy(carArray[7].model, "Model H");
	carArray[7].price = 8.0f;
	carArray[7].stock = DEFAULT_CAR_STOCK;
	carArray[7].sold = 0;
	carArray[7].revenue = 0.0f;

	carArray[8].id = 8;
	strcpy(carArray[8].model, "Model I");
	carArray[8].price = 9.0f;
	carArray[8].stock = DEFAULT_CAR_STOCK;
	carArray[8].sold = 0;
	carArray[8].revenue = 0.0f;

	carArray[9].id = 9;
	strcpy(carArray[9].model, "Model J");
	carArray[9].price = 9.99f;
	carArray[9].stock = DEFAULT_CAR_STOCK;
	carArray[9].sold = 0;
	carArray[9].revenue = 0.0f;
}







#endif