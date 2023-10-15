#ifndef CARSALESSTRUCTURES_H
#define CARSALESSTRUCTURES_H
//Prevents the header file from being included more than once

#include <stdio.h> //used for printf(), scanf(), and file I/O
#include <string.h> //used for strcpy() and srtlen()
#include <stdlib.h>  //used for malloc(), free() and qsort()
#include <ctype.h> //used for tolower() and isaplpha()

//useful constants
#define DISCOUNT_MULTIBUY_AMOUNT 3
#define DISCOUNT_MEMBER_PERCENTAGE 0.25f
#define DISCOUNT_MULTIBUY_PERCENTAGE 0.2f

#define NUMBER_OF_CAR_MODELS 10
#define MAX_SALES 100
#define MAX_CARS_PER_USER 10

#define DEFAULT_CAR_STOCK 10

//used to improve code semantics
#define MENU_OPTION_BUY_CARS 'a'
#define MENU_VIEW_STOCK 'b'
#define MENU_OPTION_VIEW_SALES 'c'
#define MENU_OPTION_SAVE 'd'
#define	MENU_OPTION_EXIT 'x'

#define TRUE 1
#define FALSE 0

//the ID of each sale
extern short saleID = 0;


typedef struct { //defines the term "customer" to this struct, this makes it easier to refference
	char name[100]; //users name
	unsigned short age; //users age
	short discountAplied; //if the user got a discount
	float discountPercent; //the discount in % (0.00 - 1.00)
	float discountAmount; //the value of the discount in $
	char discountReason[20]; //the reason for the discount
	int numberBought; //number of cars each user bought
	float total; //the total price for each users purchace
	int carsBought[MAX_CARS_PER_USER]; //an array storing each car that each user bought
}customer;

typedef struct {
	int id; //the ID of each car
	char model[20]; //the name of each car
	float price; //the cost of each car
	int stock; //the amount of each car remaining
	int sold; //the number of each car sold
	float revenue; //the money made from each cars sales
}car;



#endif