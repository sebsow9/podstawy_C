#include "car.c"
#include <stdio.h>
#include <assert.h>


int main(){
    
    struct Car Auto = car(0);
    struct Vector vector1 = {0,0};
    struct Vector vector2 = {0,1};
    struct Vector vector3 = {1,1};
    
    
    assert(Auto.orientation == NORTH);
    assert(Car_isAt(Auto, vector1));
    printf("Dobra inicjalizacja\n\n");

    Car_move(&Auto, FORWARD, 4, 4);
    assert(Car_isAt(Auto, vector2));
    printf("Dobrze poruszylismy auto\n\n");

    Car_move(&Auto, LEFT, 4, 4);
    assert(Auto.orientation == WEST);
    printf("Dobrze obrocilismy Auto\n\n");

    Car_move(&Auto, FORWARD, 4, 4);
    assert(Auto.orientation == EAST);
    assert(Car_isAt(Auto,vector3));
    printf("Udalo sie obrocic Auto jak chcialo wyjechac\n\n");



}