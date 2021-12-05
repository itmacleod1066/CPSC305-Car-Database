#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "car.h"

car *db[MAX_CARS];
int num_cars = 0;

//Read filename into database. Returns 0 on success and -1 on errot
int initialize_db(char *filename){
     FILE *fin = fopen(filename, "r");
     if(fin == NULL){
         return -1;
     }else{
         int carnum, year, miles, cost;
         char cat[20];
         //category cateogry
         char make[20];
         //int i = 0;
         while(fscanf(fin, "%d %d %s %s %d %d", &carnum, &year, make, cat, &miles, &cost) != EOF){
            // car car = {carnum, year, make, category, miles, cost};
             //fprintf(stdout, "carnum: %d year: %d make: %s, category: %s, miles %d, cost: %d\n", carnum, year, make, category, miles, cost);
            category type;
            if(strcmp(cat, "sedan") == 0){
                type = 0;
            }else if(strcmp(cat, "suv") == 0){
                type = 1;
            }else if(strcmp(cat, "truck") == 0){
                type = 2;
            }else{
                type = 3;
            }
             add_car(carnum, year, make, type, miles, cost);
             //print_car(db[num_cars]);
             //num_cars++;
             //printf("%s\n","Reading in the following car into the db");
             //print_car(db[num_cars]);
             //num_cars++;
         }             
         //printf("There are %d cars in db", i);
         fclose(fin);
         
         return 0;
     }
}

//Write db to filename. Returns 0 on success and -1 on error
int write_db(char *filename){
    FILE *fout = fopen(filename, "w");
    if(fout == NULL){
        return -1;
    }
    for(int i = 0; i < num_cars; i++){
        car *c = db[i];
        char cat[20];
        if(c->category == 0){
            strcpy(cat, "sedan");
        }else if(c->category == 1){
            strcpy(cat, "suv");
        }else if(c->category == 2){
            strcpy(cat, "truck");
        }else{
            strcpy(cat, "hybrid");
        }
        fprintf(fout, "%d %d %s %s %d %d\n", c->carnum, c->year, c->make, cat, c->miles, c->cost);
    }
    fclose(fout);
    return 0;
}


//method that prints the cars in the database
void show_cars(){ 
    for(int i = 0; i < num_cars; i++){
        car *c = db[i];
        print_car(c);
    }
}

//displays c on stdout
void print_car(car *c){
    char cat[20];
    if(c->category == 0){
        strcpy(cat, "sedan");
    }else if(c->category == 1){
        strcpy(cat, "suv");
    }else if(c->category == 2){
        strcpy(cat, "truck");
    }else{
        strcpy(cat, "hybrid");
    }
    printf("Number: %d Year: %d Make: %s Category %s Miles %d Cost %d\n", c->carnum, c->year,  c->make, cat, c->miles, c->cost);
}

//returns car* with carnum in db. Returns NULL if carnum is not in db
car *find_car(int carnum){
    car *c;
    for(int i = 0; i < num_cars; i++){
        if(db[i]->carnum == carnum){
            print_car(db[i]);
            return db[i];
        }
    }
    printf("%s", "Car is not in the database!\n");
    return NULL;
}

//Adds a new car to db. Returns car* of the car added. Returns 0 if carnum is already in the db
car *add_car(int num, int year, char *make, category category, int mileage, int cost){

    car *c = malloc(sizeof(car));
    
    c->carnum = num;
    c->year = year;
    strcpy(c->make, make);
    c->category = category;
    c->miles = mileage;
    c->cost = cost;
    
    
    //check to see if car is in the database or not
    for(int i = 0; i < num_cars; i++){
        if(db[i]->carnum == c->carnum){
            printf("Car number %d is already in the database!\n", c->carnum);
            return 0;
        }
    }
    
    db[num_cars] = c;
    num_cars++;

    return c;
}

//Updates cost of carnum in db. Returns car* with carnum. Returns NULL if carnum is not in db
car *update_cost(int carnum, int cost){
    if(cost >= 0){
        int found = 0;
        for(int i = 0; i < num_cars; i++){
            if(db[i]->carnum == carnum){
                db[i]->cost = cost;
                return db[i];
            }
        }
        if(found == 0){
            printf("%s", "Invalid carnum!\n");
            return NULL;
        }
    }else{
        printf("%s", "Invalid cost! Must be positive\n");
        return NULL;
    }

    return NULL;
}

//Updates miles of carnum in db. Returns car* with carnum. Returns NULL if carnum is not in db
car *update_miles(int carnum, int miles){
    if(miles > 0){
        int found = 0;
        for(int i = 0; i < num_cars; i++){
            if(db[i]->carnum == carnum){
                db[i]->miles = miles;
                return db[i];
            }
        }
        if(found == 0){
            printf("%s", "Invalid carnum\n");
        }
    }else{
        printf("%s", "Invalid mileage! Must be positive\n");
        return NULL;
    }

    return NULL;
}

//Get methods here//

//Fills in cars with an array of car pointers for all cars in db with year > year
int get_year(car **cars, int year){
    int count = 0; 
    printf("\n");
    printf("%s\n", "Cars that match query...");
    for(int i = 0; i < num_cars; i++){
        if(db[i]->year > year){
           // print_car(db[i]);
            cars[count] = db[i];
            print_car(cars[count]);
            count++;
            //print_car(cars[i]);
        }
    }

    if(count == 0){
        printf("%s\n", "No cars newer than year!");
    }
    printf("Count is %d\n", count);
    return count;
}

//Fills in cars with an array of car pointers for all cars in db with cost < cost
int get_cost(car **cars, int cost){
    int count = 0;
    printf("\n");
    printf("%s\n", "Cars that match query...");
    for(int i = 0; i < num_cars; i++){
        if(db[i]->cost < cost){
            // print_car(db[i]);
            //print_car(cars[count]);
            cars[count] = db[i];
            print_car(cars[count]);
            count++;
            //print_car(cars[i]);
        }
    }
   
    if(count == 0){
        printf("%s\n", "No cars less than cost!");
    }
    printf("Count is %d", count); 
    return count;
}

//Fills in cars with an array of car pointers for all cars in db with category == c
int get_category(car **cars, category c){
    int count = 0;
    printf("\n");
    printf("%s\n", "Cars that match query...");
    for(int i = 0; i < num_cars; i++){
        if(db[i]->category == c){
            cars[count] = db[i];
            print_car(cars[count]);
            count++;
            //print_car(cars[i]);
        }
    }

    if(count == 0){
        printf("%s\n", "No cars match of category!");
    }

    return count;
}

//Fills in cars with an array of car pointers for all cars in db where the string in  make
//matches the string in the car entry
int get_make(car **cars, char *make){
    int count = 0;
    printf("\n");
    printf("%s\n", "Cars that match query...");
    for(int i = 0; i < num_cars; i++){
        if(strcmp(db[i]->make, make) == 0){
            cars[count] = db[i];
            count++;
            print_car(cars[i]);
        }
    }

    if(count == 0){
        printf("%s\n", "No cars of make!");
    }

    return count;
}

//Purhcase carnum. Removes the car from db. Returns car* with carnum. Returns NULL
//if carnum is not in db
car *purchase(int carnum){
    for(int i = 0; i < num_cars; i++){
        if(db[i]->carnum == carnum){
            car *c = db[i];
            printf("Taking carnum %d off the lot!\n", carnum);
            //new code
            for(int j = i; j < num_cars; j++){
                db[j] = db[j + 1];
            }
            num_cars--;
            //

            //deleteCar(db[i]->carnum);
            return c;
        }
    }

    printf("%s\n", "Invalid carnum!\n");
    return NULL;
}
/**
void deleteCar(int carnum){
    int found = 0;
    for(int i = 0; i < num_cars; i++){
        if(db[i]->carnum == carnum){
            printf("%s\n", "Car deleted!");
            for(int j = i; j < num_cars; j++){
                db[j] = db[j + 1];
            }

            num_cars--;
            found = 1;
        }
    }

    //show_cars();
    if(found == 0){
        printf("%s", "Invalid car num!\n");
    }
}
*/
