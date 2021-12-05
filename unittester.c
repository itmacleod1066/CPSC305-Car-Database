#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "car.h"

void my_print_car(car *c) {
  char category[25];
  if (c->category == sedan)
    strcpy(category, "sedan");
  else if (c->category == suv)
    strcpy(category, "suv");
  else if (c->category == truck)
    strcpy(category, "truck");
  else
    strcpy(category, "hybrid");
  printf("%d %d %s %s %d %d\n", c->carnum, c->year, c->make, category, c->miles, c->cost);
}


void my_show_cars(car **db, int num_cars) {
  for (int i = 0; i < num_cars; i++) {
    char category[25];
    car *p = db[i];
    if (p->category == sedan)
      strcpy(category, "sedan");
    else if (p->category == suv)
      strcpy(category, "suv");
    else if (p->category == truck)
      strcpy(category, "truck");
    else
      strcpy(category, "hybrid");
    printf("%d %d %s %s %d %d\n", p->carnum, p->year, p->make, category, p->miles, p->cost);
  }


}

int equalcars(car *c1, car *c2) {
    if (c1->carnum == c2->carnum && c1->year == c2->year && strcmp(c1->make, c2->make) == 0 &&
        c1->category == c2->category && c1->miles == c2->miles && c1->cost == c2->cost)
        return 1;
    else
        return 0;
}

car expecteddb[] = { 
    {123, 2010, "Ford", sedan, 70000, 4000}, 
    {124, 2014, "Toyota", suv, 20000, 15000}, 
    {125, 2019, "Honda", hybrid, 10000, 25000}, 
    {126, 2020, "Toyota", truck, 5000, 30000}, 
    {127, 2006, "Porsche", suv, 5000, 13000}, 
};

car expectedfind = {123, 2010, "Ford", sedan, 70000, 4000};

car expectedgetyear[] = {
    {124, 2014, "Toyota", suv, 20000, 15000},
    {125, 2019, "Honda", hybrid, 10000, 25000},
    {126, 2020, "Toyota", truck, 5000, 30000},
};

car expectedgetcat[] = {
    {124, 2014, "Toyota", suv, 20000, 15000},
    {127, 2006, "Porsche", suv, 5000, 13000},
};

car expectedgetcost[] = {
    {123, 2010, "Ford", sedan, 70000, 4000}, 
    {124, 2014, "Toyota", suv, 20000, 15000}, 
    {127, 2006, "Porsche", suv, 5000, 13000},
    
};

car expectedupdatecost = {127, 2006, "Porsche", suv, 5000, 33333};

car expectedupdatemiles = {127, 2006, "Porsche", suv, 22222, 33333};

car expectedpurchase = {123, 2010, "Ford", sedan, 70000, 4000};

car expectedpurchasedb[] = { 
    {124, 2014, "Toyota", suv, 20000, 15000}, 
    {125, 2019, "Honda", hybrid, 10000, 25000}, 
    {126, 2020, "Toyota", truck, 5000, 30000}, 
    {127, 2006, "Porsche", suv, 22222, 33333}, 
};

car expectedaddcar = {999, 2021, "Tesla", truck, 1, 100000};

car expectedaddcardb[] = { 
    {124, 2014, "Toyota", suv, 20000, 15000}, 
    {125, 2019, "Honda", hybrid, 10000, 25000}, 
    {126, 2020, "Toyota", truck, 5000, 30000}, 
    {127, 2006, "Porsche", suv, 22222, 33333}, 
    {999, 2021, "Tesla", truck, 1, 100000},
};



extern car *db[];
extern int num_cars;
car *cars[MAX_CARS];

int main(int argc, char **argv) {
// Test initialize_db
    printf("Test initialize_db()\n");
    if (initialize_db("cars.txt") < 0) {
        perror("perror");
        exit(1);
    }
    int goodinitdb = 1;
    for (int i = 0; i < 5; i++)
        if (!equalcars(db[i], &expecteddb[i])) {
            goodinitdb = 0;
            break;
        }
    if (goodinitdb)
        printf("initialize_db passed.\n");
    else
        printf("initialize_db failed.\n");
    printf("Cars in DB after initialize_db()\n");
    my_show_cars(db, 5);

// Test find_car
    printf("\nTest find_car(123)\n");
    car *c = find_car(123);
    int goodfindcar = 1;
    if (equalcars(c, &expectedfind))
        printf("find_car(123) passed.\n");
    else {
        printf("find_car(123) failed.\n");
        goodfindcar = 0;
    }
    printf("find_car(123) results:\n");
    my_print_car(c);

// Test get_year
    printf("\nTest get_year(cars, 2010)\n");
    int goodgetyear = 1;
    int n = get_year(cars, 2010);
    if (n != 3)
        printf("get_year(cars, 2010) failed - did not find 3 cars.\n");
    else {
        printf("%s\n", "Got here");
        for (int i = 0; i < n; i++){
            printf("%d\n", i);
            if (!equalcars(cars[i], &expectedgetyear[i])) {
                goodgetyear = 0;
                break;
            }
        }
        if (goodgetyear)
            printf("get_year(cars, 210) passed.\n");
        else
            printf("get_year(cars, 210) failed.\n");
    }
    printf("\nget_year(cars, 2010) results: %d cars\n", n);
    my_show_cars(cars, n);

// Test get_category
    printf("\nTest get_category(cars, suv)\n");
    n = get_category(cars, suv);
    int goodgetcat = 1;
    if (n != 2)
        printf("get_cateory(cars, suv) failed - did not find 2 cars.\n");
    else {
        for (int i = 0; i < n; i++)
            if (!equalcars(cars[i], &expectedgetcat[i])) {
                goodgetcat = 0;
                break;
            }
        if (goodgetcat)
            printf("get_cateory(cars, suv) passed.\n");
        else
            printf("get_cateory(cars, suv) failed.\n");
    }
    printf("\nget_cat(cars, suv) results: %d cars\n", n);
    my_show_cars(cars, n);

// Test get_cost
    printf("\nTest get_cost(cars, 17000)\n");
    n = get_cost(cars, 17000);
    int goodgetcost = 1;
    if (n != 3)
        printf("get_cost(cars, 17000) failed - did not find 3 cars.\n");
    else {
        for (int i = 0; i < n; i++)
            if (!equalcars(cars[i], &expectedgetcost[i])) {
                goodgetcost = 0;
                break;
            }
        if (goodgetcost)
            printf("get_cost(cars, 17000) passed.\n");
        else
            printf("get_cost(cars, 17000) failed.\n");
    }
    printf("\nget_cost(cars, 17000) results: %d cars\n", n);
    my_show_cars(cars, n);

// Test update_cost by updating the cost of Car 127 (Porsche) to be 33333
// Then call get_cost(cars, 17000) again - should return 2 cars
    printf("\nTest update_cost(cars, 33333)\n");
    c = update_cost(127, 33333); // update cost on Porsche
    //c = find_car(127);      // find porsche
    int goodupdatecost = 1;
    if (equalcars(c, &expectedupdatecost))
        printf("update_cost(127, 33333) passed.\n");
    else {
        printf("update_cost(127, 33333) failed.\n");
        goodupdatecost = 0;
    }
    printf("update_cost(127, 33333) results:\n");
    my_print_car(c);         // print porsche with new cost
// Test get_cost again - same call as before, but there are only 2 cars < 17000
    printf("\nTest get_cost(cars, 17000) - take 2\n");
    n = get_cost(cars, 17000);
    int goodgetcost2 = 1;
    if (n != 2)
        printf("get_cost(cars, 17000) - take 2 failed - did not find 2 cars.\n");
    else {
        for (int i = 0; i < n; i++)
            if (!equalcars(cars[i], &expectedgetcost[i])) {
                goodgetcost2 = 0;
                break;
            }
        if (goodgetcost2)
            printf("get_cost(cars, 17000) - take 2 passed.\n");
        else
            printf("get_cost(cars, 17000) - take 2 failed.\n");
    }
    printf("\nget_cost(cars, 17000) - take 2 results: %d cars\n", n);
    my_show_cars(cars, n);

// Test update_miles
    printf("\nTest update_miles(cars, 22222)\n");
    c = update_miles(127, 22222); // update miles on Porsche
    //c = find_car(127);      // find porsche
    int goodupdatemiles = 1;
    if (equalcars(c, &expectedupdatemiles))
        printf("update_miles(127, 22222) passed.\n");
    else {
        printf("update_miles(127, 22222) failed.\n");
        goodupdatemiles = 0;
    }
    printf("update_miles(127, 22222) results:\n");
    my_print_car(c);         // print porsche with new cost

// Test purchase
    printf("\nTest purchase(123)\n");
    c = purchase(123);
    int goodpurchase = 1;
    if (equalcars(c, &expectedpurchase))
        printf("purchase(123) passed.\n");
    else {
        printf("purchase(123) failed.\n");
        goodpurchase = 0;
    }
    printf("purchase(123) results:\n");
    my_print_car(c);

// Check db after purchase
    int goodpurchasedb = 1;
    for (int i = 0; i < 4; i++)
        if (!equalcars(db[i], &expectedpurchasedb[i])) {
            goodpurchasedb = 0;
            break;
        }
    if (goodpurchasedb)
        printf("db after purchase passed.\n");
    else
        printf("db after purchase failed.\n");
    printf("Cars in DB after purchase(123)\n");
    my_show_cars(db, 4);

// Test add_car
    printf("\nTest add_car(999, 2021, Tesla, truck, 1, 100000)\n");
    c = add_car(999, 2021, "Tesla", truck, 1, 100000);
    int goodaddcar = 1;
    if (equalcars(c, &expectedaddcar))
        printf("add_car(999, 2021, \"Tesla\", truck, 1, 100000) passed.\n");
    else {
        printf("add_car(999, 2021, \"Tesla\", truck, 1, 100000) failed.\n");
        goodaddcar = 0;
    }
    printf("add_car(999, 2021, \"Tesla\", truck, 1, 100000) results:\n");
    my_print_car(c);

    int goodaddcar2 = 1;
    if (num_cars != 5)
        printf("db after add_car failed - db after add_car does not have 5 cars");
    else {
        for (int i = 0; i < n; i++)
            if (!equalcars(db[i], &expectedaddcardb[i])) {
                goodaddcar2 = 0;
                break;
            }
        if (goodaddcar2)
            printf("db after add_car passed\n");
        else
            printf("db after add_car failed\n");
    }
    printf("\nTest add_car results:\n");
    my_show_cars(db, 5);
/* Decided to do this via script
    write_db("cars_test.txt");
    printf("\nmore cars_test.txt after write_db()\n");
    system("more cars_test.txt");
 */   
    printf("\n\nUnit Testing Summary\n");
    printf("initialize_db test: %s\n", goodinitdb ? "passed" : "failed");
    printf("find_car test: %s\n", goodfindcar ? "passed" : "failed");
    printf("get_year test: %s\n", goodgetyear ? "passed" : "failed");
    printf("get_category test: %s\n", goodgetcat ? "passed" : "failed");
    printf("get_cost test: %s\n", goodgetcost ? "passed" : "failed");
    printf("update_cost test: %s\n", goodupdatecost ? "passed" : "failed");
    printf("get_cost 2 test: %s\n", goodgetcost2 ? "passed" : "failed");
    printf("update_miles test: %s\n", goodupdatemiles ? "passed" : "failed");
    printf("purchase test: %s\n", goodpurchase ? "passed" : "failed");
    printf("purchase db test: %s\n", goodpurchasedb ? "passed" : "failed");
    printf("add_car test: %s\n", goodaddcar ? "passed" : "failed");
    printf("add_car db test: %s\n", goodaddcar2 ? "passed" : "failed");
}
