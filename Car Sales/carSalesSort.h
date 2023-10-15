#ifndef CARSALESSORT_H
#define CARSALESSORT_H

#define SORT_BY_CAR_ID 0
#define SORT_BY_STOCK 1
#define SORT_BY_REVENUE 2

//prototypes
int compareStock(const void* a, const void* b);
int compareRevenue(const void* a, const void* b);
int compareID(const void* a, const void* b);

/*
used for qsort,
returns a negative value if A is larger than B
0 if they are equal
and a posetive value if B is larger than A
*/
int compareStock(const void* a, const void* b) {
	car* carA = (car*)a;
	car* carB = (car*)b;

	return (carB->stock - carA->stock);
}
int compareRevenue(const void* a, const void* b) {
	car* carA = (car*)a;
	car* carB = (car*)b;
	if (carB->revenue > carA->revenue) {
		return 1;
	}
	if (carB->revenue < carA->revenue) {
		return -1;
	}
	if (carB->revenue == carA->revenue) {
		return 0;
	}
}

/*
same as above but inverted
*/
int compareID(const void* a, const void* b) {
	car* carA = (car*)a;
	car* carB = (car*)b;

	return (carA->id - carB->id);
}


#endif