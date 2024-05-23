#include <stdio.h>
#include <stdbool.h>
#include "map_direction.c"
#include "move_direction.c"
#include "wektor.c"


struct Car{
    enum MapDirection orientation;
    struct Vector vector;
};

struct Car car(){
    struct Car car_filled = {NORTH, (0,0)}; //funkcja pomocnicza do wywolywania struktury
    return car_filled;
}

void Car_toString(struct Car car){ // wyswietlanie pozycji auta
    printf("Polozenie Auta to: ");
    MapDirection_toString(car.orientation);
    Vector_toString(car.vector);
}

bool Car_isAt(struct Car car, struct Vector vector){ // sprawdzamy czy auto jest dokladnie na tej pozycji
    return ((car.vector.x == vector.x) && (car.vector.y == vector.y));
}

void Car_move(struct Car *car, enum MoveDirection direction){
    struct Vector border1 = {0, 0}; // granice naszego obszaru
    struct Vector border2 = {4, 4};
    switch(direction){ //sprawdzamy w jakim kieurnku chcemy poruszyc auto
        case RIGHT:
            car->orientation = MapDirection_next(car->orientation);
            break;
        case LEFT:
            car->orientation = MapDirection_previous(car->orientation);
            break;
        case FORWARD:
            switch(car->orientation){ //sprawdzamy w jakim kierunku ma ruszyc auto jezeli jedziemy do przodu
                case NORTH:
                    struct Vector vectoraddFN = {0, 1};
                    if (!Vector_precedes(Vector_add(car->vector, vectoraddFN), border2)){ // sprawdzamy czy obie wspolrzedne sa mniejsza niz (4,4)
                        car->orientation = MapDirection_next(car->orientation);
                        car->orientation = MapDirection_next(car->orientation);
                        vectoraddFN = Vector_opposite(vectoraddFN);
                    } 
                    car->vector = Vector_add(car->vector, vectoraddFN);
                    //Vector_toString(car->vector);
                    //MapDirection_toString(car->orientation);
                    break;
                    
                case SOUTH:
                    struct Vector vectoraddFS = {0, -1};

                    if (!Vector_follows(Vector_add(car->vector, vectoraddFS), border1)){ // sprawdzamy czy obie wspolrzedne sa wieksze niz (0,0)
                        car->orientation = MapDirection_next(car->orientation);
                        car->orientation = MapDirection_next(car->orientation);
                        vectoraddFS = Vector_opposite(vectoraddFS);
                    } 
                    car->vector = Vector_add(car->vector, vectoraddFS);
                    break;
                    
                case WEST:
                    struct Vector vectoraddFW = {-1, 0};
                    if (!Vector_follows(Vector_add(car->vector, vectoraddFW), border1)){ // sprawdzamy czy obie wspolrzedne sa wieksze niz (0,0)
                        car->orientation = MapDirection_next(car->orientation);
                        car->orientation = MapDirection_next(car->orientation);
                        vectoraddFW = Vector_opposite(vectoraddFW);
                    } 
                    car->vector = Vector_add(car->vector, vectoraddFW);
                    break;
                    
                case EAST:
                    struct Vector vectoraddFE = {1, 0};
                    if (!Vector_precedes(Vector_add(car->vector, vectoraddFE), border2)){ // sprawdzamy czy obie wspolrzedne sa mniejsza niz (4,4)
                        car->orientation = MapDirection_next(car->orientation);
                        car->orientation = MapDirection_next(car->orientation);
                        vectoraddFE = Vector_opposite(vectoraddFE);
                    } 
                    car->vector = Vector_add(car->vector, vectoraddFE);
                    break;
                    
            }
        break;
        case BACKWARD:
            switch(car->orientation){ //sprawdzamy w jakim kierunku ma ruszyc auto jezeli jedziemy do przodu
                case SOUTH:
                    struct Vector vectoraddSB = {0, 1};
                    if (!Vector_precedes(Vector_add(car->vector, vectoraddSB), border2)){ // sprawdzamy czy obie wspolrzedne sa mniejsza niz (4,4)
                        car->orientation = MapDirection_next(car->orientation);
                        car->orientation = MapDirection_next(car->orientation);
                        vectoraddSB = Vector_opposite(vectoraddSB);
                    } 
                    car->vector = Vector_add(car->vector, vectoraddSB);
                    break;
                    
                case NORTH:
                    struct Vector vectoraddBN = {0, -1};

                    if (!Vector_follows(Vector_add(car->vector, vectoraddBN), border1)){ // sprawdzamy czy obie wspolrzedne sa wieksze niz (0,0)
                        car->orientation = MapDirection_next(car->orientation);
                        car->orientation = MapDirection_next(car->orientation);
                        vectoraddBN = Vector_opposite(vectoraddBN);
                    } 
                    car->vector = Vector_add(car->vector, vectoraddBN);
                    break;
                    
                case EAST:
                    struct Vector vectoraddBE = {-1, 0};
                    if (!Vector_follows(Vector_add(car->vector, vectoraddBE), border1)){ // sprawdzamy czy obie wspolrzedne sa wieksze niz (0,0)
                        car->orientation = MapDirection_next(car->orientation);
                        car->orientation = MapDirection_next(car->orientation);
                        vectoraddBE = Vector_opposite(vectoraddBE);
                    } 
                    car->vector = Vector_add(car->vector, vectoraddBE);
                    break;
                    
                case WEST:
                    struct Vector vectoraddBW = {1, 0};
                    if (!Vector_precedes(Vector_add(car->vector, vectoraddBW), border2)){ // sprawdzamy czy obie wspolrzedne sa mniejsza niz (4,4)
                        car->orientation = MapDirection_next(car->orientation);
                        car->orientation = MapDirection_next(car->orientation);
                        vectoraddBW = Vector_opposite(vectoraddBW);
                    } 
                    car->vector = Vector_add(car->vector, vectoraddBW);
                    break;
                    
            }
        break;

    }
}