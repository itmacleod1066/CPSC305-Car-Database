#define MAX_CARS 100
#define MAX_MAKE_CHARS 32

//Category of car
typedef enum { sedan, suv, truck, hybrid } category;

/*
 *Car structure. Each car has a number, year make, category
 miles, and cost
 */
typedef struct{
    int carnum;
    int year;
    char make[MAX_MAKE_CHARS];
    category category;
    int miles;
    int cost;
}car;

//Function prototypes
int initialize_db(char *filename);
int write_db(char *filename);
void show_cars();
void print_car(car *c);
car *find_car(int carnum);
car *add_car(int carnum, int year, char *make, category category, int miles, int cost);
car *update_cost(int carnum, int cost);
car *update_miles(int carnum, int miles);
int get_year(car **cars, int year);
int get_cost(car **cars, int cost);
int get_category(car **cars, category c);
int get_make(car **cars, char *make);
car *purchase(int carnum);
//void deleteCar(int carnum);


