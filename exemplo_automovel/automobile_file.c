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
    int input_status = 0;
    printf("Welcome to the automobile program.\n");

    do
    {
        if (input_status != -1)
        {
            automobile = scan_auto(&input_status);
            print_auto(automobile); 
        }

    } while (input_status != -1);
    
    return 0;
}

date_t scan_date(int* input_status_p)
{
    date_t date;
    if(scanf("%d %d %d",
        &date.month,
        &date.day,
        &date.year) != 3){
            *input_status_p = -1;
        }
    return date;
}

tank_t scan_tank(int* input_status_p)
{
    tank_t tank;
    if(scanf("%lf %lf",
        &tank.current_fuel_lvl,
        &tank.tank_capacity) != 2){
            *input_status_p = -1;
    }
    return tank;
}


auto_t scan_auto(int* input_status_p)
{
    auto_t car;
    if(scanf(" %c  %c  %d",&car.make,&car.model, &car.odometer_read) ==  -1){
        *input_status_p = -1;
    }
    car.manufacture_date = scan_date(input_status_p);
    car.purchase_date = scan_date(input_status_p);
    car.gas_tank = scan_tank(input_status_p);
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
