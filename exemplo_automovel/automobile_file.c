/*
discente: larissa yasmim alves batista
exemplo da aula de structs e unions
*/

/*
Write I/O functions scan date, scan tank, scan auto, print date, print tank,
and print auto, and also write a driver function that repeatedly fills and displays an
auto structure variable until EOF is encountered in the input stream. Sample data:
Mercury(M) Sable(S) 99842 1 18 2001 5 30 1991 16 12.5
Mazda(Z) Navajo(N) 123961 2 20 1993 6 15 1993 19.3 16.7
*/

#include <stdio.h>

typedef enum {MANUFACTURE, PURCHASE} date_option_en;
typedef struct date_t
{
    int month, day, year;
} date_t;

typedef struct tank_t
{
    double tank_capacity, current_fuel_lvl;
} tank_t;

typedef struct auto_t
{
    char make, model;
    int odometer_read;
    date_t manufacture_date, purchase_date;
    tank_t gas_tank;
} auto_t;

date_t scan_date();
tank_t scan_tank();
auto_t scan_auto();

void print_date(int option, date_t date);
void print_tank(tank_t tank);
void print_auto(auto_t automobile);

int main()
{
    auto_t automobile;
    char choice = 'q';
    //char t = ' ';
    do
    {
        printf("Welcome to the automobile program. Type 'q' if you want to exit, otherwise type 'E'\n");
        scanf(" %c", &choice);
        /*while (scanf("%c ",&t) != EOF){
        }*/
        if (choice != 'q')
        {
            automobile = scan_auto();
            print_auto(automobile);   
        }

    } while (choice != 'q');

    return 0;
}

date_t scan_date()
{
    date_t date;
    //printf("Please write bellow the manufacture date of your car (mm/dd/yy): \n");
    scanf("%d %d %d",
        &date.month,
        &date.day,
        &date.year);
    return date;
}

tank_t scan_tank()
{
    tank_t tank;
    //printf("Please write the current state of your tank (fuel level and capacity): \n");
    scanf("%lf %lf",
        &tank.current_fuel_lvl,
        &tank.tank_capacity);
    return tank;
}


auto_t scan_auto()
{
    auto_t car;
    //printf("Please write the make of your car: \n");
    scanf(" %c",&car.make);
    //printf("Please write the model of your car: \n");
    scanf(" %c",&car.model);
    //printf("Please write the odometer read of your car: \n");
    scanf(" %d",&car.odometer_read);
    car.manufacture_date = scan_date();
    car.purchase_date = scan_date();
    car.gas_tank = scan_tank();
    return car;
}

void print_date(int option, date_t date){
    switch (option)
    {
    case MANUFACTURE:
        printf("manufacture date is %d/%d/%d\n",date.month,date.day,date.year);
        break;
    case PURCHASE:
        printf("purchase date %d/%d/%d\n",date.month,date.day,date.year);
        break;
    default:
        printf("invalid date option\n");
        break;
    }
}
void print_tank(tank_t tank){
    printf("your tank's fuel level is: %.3f out of the of capacity of: %.3f\n",tank.current_fuel_lvl, tank.tank_capacity);
}

void print_auto(auto_t car){
    printf("Your %c car (of %c make) is at: %d km/h\n",car.model,car.make, car.odometer_read);
    print_date(MANUFACTURE,car.manufacture_date);
    print_date(PURCHASE,car.purchase_date);
    print_tank(car.gas_tank);
}