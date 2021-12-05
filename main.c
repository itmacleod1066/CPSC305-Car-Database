#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "car.h"

//car cars[MAX_CARS];

int main(int argc, char **argv){
    printf("%s\n", "***C Project***");  
    int initialize =  initialize_db(argv[1]);
     if(initialize == 0){
        char user[30];
        printf("Enter user name: ");
        scanf("%s", user);
        if(strcmp(user, "owner") == 0){
            int optionChoose = 1;
            
            while(optionChoose == 1){
                printf("\n");
                printf("%s\n\t", "Possible commands include:");
                printf("%s\n\t", "|add [carnum year make model miles cost]: adds a car to the database");
                printf("%s\n\t", "|list: list all the cars in database");
                printf("%s\n\t", "|delete [carnum]: delete a car in the database");
                printf("%s\n\t", "|updatecost [carnum cost]: update the cost of a vehicle in the database");
                printf("%s\n\t", "|updatemiles [carnum cost]: update the mileage of a vehicle");
                printf("%s\n\t", "|find [carnum]: print data of car from database based on what car you want to find");
                printf("%s\n\t", "|showyear [year]: print data of all cars newer than input year");
                printf("%s\n\t", "|showmake [make]: print data of all cars with inputted make");
                printf("%s\n\t", "|showcost [cost]: shows all cars less than cost");
                printf("%s\n\t", "|showcategory [category]: shows all cars that match the category");
                printf("%s\n\t", "|purchase [carnum]: purchase car");
                printf("%s\n\t", "|save: save changes to database file");
                printf("%s\n\t", "|quit: quit the program without saving changes");
                printf("%s\n", "|exit: exits program and saves changes to database");
                printf("\n");
                printf("Type a command: ");
                
                char option[20];
                scanf("%s", option);
                printf("\n");

                if(strcmp(option, "quit") == 0){
                    optionChoose = 0;
                }else if(strcmp(option, "list") == 0){
                    show_cars();
                }else if(strcmp(option, "delete") == 0){
                    int num;
                    //printf("%s", "Enter the number to delete: ");
                    scanf("%d", &num);
                    car *purchased = purchase(num);
                }else if(strcmp(option, "updatecost") == 0){
                    int carnum, cost;
                    //printf("%s", "Type the car number and cost: ");
                    scanf("%d %d", &carnum, &cost);
                    update_cost(carnum, cost);
                }else if(strcmp(option, "updatemiles") == 0){
                    int carnum, miles;
                    //printf("%s", "Type the car number and miles: ");
                    scanf("%d %d", &carnum, &miles);
                    update_miles(carnum, miles);
                }else if(strcmp(option, "add") == 0){
                    int carnum, miles, year, cost;
                    char cat[20];
                    char make[20];
                    category type;
                    //printf("%s\n", "Enter carnum, year, make, category, miles, and cost: ");
                    scanf("%d %d %s %s %d %d", &carnum, &year, make, cat, &miles, &cost);
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
                }else if(strcmp(option, "find") == 0){
                    int num;
                   // printf("Enter the carnum: ");
                    scanf("%d", &num);
                    find_car(num);
                }else if(strcmp(option, "showyear") == 0){
                    int y;
                    //printf("%s\n", "Type the year to show caws newer than that year:");
                    scanf("%d", &y);
                    car *cars[MAX_CARS];
                    int n = get_year(cars, y);
                }else if(strcmp(option, "showmake") == 0){
                    char m[20];
                    //printf("%s\n", "Print the make:");
                    scanf("%s", m);
                    car *cars[MAX_CARS];
                    int n = get_make(cars,m);
                }else if(strcmp(option, "showcost") == 0){
                    int c;
                    //printf("%s\n", "Please enter cost:");
                    scanf("%d", &c);
                    car *cars[MAX_CARS];
                    int num = get_cost(cars, c);
                }else if(strcmp(option, "showcategory") == 0){
                    char cat[20];
                    category category;
                    //printf("%s", "Type the category (sedan, suv, truck, hybrid):");
                    scanf("%s", cat);
                    if(strcmp(cat, "sedan") == 0){
                        category = 0;
                    }else if(strcmp(cat, "suv") == 0){
                        category = 1;
                    }else if(strcmp(cat, "truck") == 0){
                        category = 2;
                    }else if(strcmp(cat, "hybrid") == 0){
                        category = 3;
                    }
                    car *cars[MAX_CARS];

                    int count = get_category(cars, category);
                } 
                else if(strcmp(option, "purchase") == 0){
                    int num;
                    //printf("%s\n", "Enter the car number you wish to purcahse:");
                    scanf("%d", &num);
                    car *purchased = purchase(num);
                }
                else if(strcmp(option, "save") == 0){
                   int saving =  write_db(argv[1]);
                   if(saving == -1){
                       printf("%s", "Saving unsuccessful!\n");
                   }else{
                        printf("%s", "Saving...Done!\n");
                   }
                }else if(strcmp(option, "exit") == 0){
                    printf("%s\n", "Saving...exiting program!");
                    int saving = write_db(argv[1]);
                    optionChoose = 0;
                }
                else{
                    printf("%s\n", "Invalid command!");
                }
            }
        }else if(strcmp(user, "shopper") == 0){
            
            int option = 1;

            while(option == 1){
                printf("\n");
                printf("%s\n\t", "Possible Commands Include:");
                printf("%s\n\t", "|purchase [carnum]: Purchases car from database");
                printf("%s\n\t", "|showyear [year]: Shows the years of cars newer than inputted year");
                printf("%s\n\t", "|showmake [make]: Shows the make of all cars in the db entered");
                printf("%s\n\t", "|showcost [cost]: Shows all cars less than cost");
                printf("%s\n\t", "|showcategory [category]: Shows all cars of the inputed category");
                printf("%s\n\t", "|exit: Saves any changes and exits");
        
                char choice[20];
                printf("\n");
                printf("%s\n", "Type a command: ");
                scanf("%s", choice);
                if(strcmp(choice, "exit") == 0){
                    int saving = write_db(argv[1]);
                    if(saving == -1){
                        printf("%s", "Saving unsuccessful");
                    }else{
                        printf("\n");
                        printf("%s\n", "Saving...Exiting now");
                    }
                    option = 0;
                }else if(strcmp(choice, "purchase") == 0){
                    int num;
                    printf("\n");
                    //printf("%s\n", "Enter the car number you wish to purcahse:");
                    scanf("%d", &num);
                    car *purchased = purchase(num);
                }else if(strcmp(choice, "showyear") == 0){
                    int y;
                    printf("\n");
                    //printf("%s\n", "Type the year to show caws newer than that year:");
                    scanf("%d", &y);
                    car *cars[MAX_CARS];
                    int n = get_year(cars, y);
                }else if(strcmp(choice, "showmake") == 0){
                    char m[20];
                    //printf("%s\n", "Print the make:");
                    scanf("%s", m);
                    car *cars[MAX_CARS];
                    int n = get_make(cars,m);
                }else if(strcmp(choice, "showcost") == 0){               
                    int c;
                    //printf("%s\n", "Type the cost:");
                    scanf("%d", &c);
                    car *cars[MAX_CARS];
                    int costCount = get_cost(cars, c);
                }else if(strcmp(choice, "showcategory") == 0){
                    char cat[20];
                    category category;
                    //printf("%s\n", "Type the category (sedan, suv, truck, hybrid): ");
                    scanf("%s", cat);
                    if(strcmp(cat, "sedan") == 0){
                        category = 0;
                    }else if(strcmp(cat, "suv") == 0){
                        category = 1;
                    }else if(strcmp(cat, "truck") == 0){
                        category = 2;
                    }else if(strcmp(cat, "hybrid") == 0){
                        category = 3;
                    }

                    car *cars[MAX_CARS];
                    int count = get_category(cars, category);
                }else{
                    printf("%s\n", "Invalid Command");
                }
            }
        }else{
            printf("%s\n", "Invalid User");
        }
     }else{
         printf("%s\n", "File not found!");
     }

     return 0;
 
}

