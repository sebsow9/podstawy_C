#include <stdio.h>
#include "map_direction.c"
#include "move_direction.c"
#include "wektor.c"


struct Car{
    enum MapDirection orientation;
    struct Vector vector;
};

int main(){

    struct Car car;
    MapDirection_toString(car.orientation);
    return 0;
}