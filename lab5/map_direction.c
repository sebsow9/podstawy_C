#include <stdio.h>

enum MapDirection{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

void MapDirection_toString(enum MapDirection direction){ // wyswietla aktualny kierunek
    switch(direction){
        case NORTH:
            printf("Polnoc\n");
            break;
        case EAST:
            printf("Wschod\n");
            break;
        case SOUTH:
            printf("Poludnie\n");
            break;
        case WEST:
            printf("Zachod\n");
            break;
    }
}
enum MapDirection MapDirection_next(enum MapDirection direction){ //wyswietla nastepny kierunek
    switch(direction){
        case WEST:
            return NORTH;
        case NORTH:
            return EAST;
        case EAST:
            return SOUTH;
        case SOUTH:
            return WEST;
    }
}
enum MapDirection MapDirection_previous(enum MapDirection direction){ // wyswietla poprzedni kierunek
    switch(direction){
        case EAST:
            return NORTH;
        case SOUTH:
            return EAST;
        case WEST:
            return SOUTH;
        case NORTH:
            return WEST;
    }
}
