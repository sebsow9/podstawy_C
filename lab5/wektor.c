#include <stdio.h>
#include <stdbool.h>

#define min(a,b) ((a < b) ? a : b)
#define max(a,b) ((a > b) ? a : b)

struct Vector {
    int x;
    int y;
};

void Vector_toString(struct Vector vector){ /*Zwraca aktualne wartosci x,y przekazanej struktury vector */
    printf("(%d, %d)\n\n", vector.x, vector.y);
}

bool Vector_precedes(struct Vector vector1, struct Vector vector2){ // sprawdza czy vector 1 ma obydwie mniejsze lub rowne wartosci
    return ((vector1.x <= vector2.x) && (vector1.y <= vector2.y));
}

bool Vector_follows(struct Vector vector1, struct Vector vector2){ //sprawdzwa czy vector 1 ma obydwie wieksze lub rowne wartosci
    return ((vector1.x >= vector2.x) && (vector1.y >= vector2.y));
}

struct Vector Vector_add(struct Vector vector1, struct Vector vector2){ //dodaje poszczegolne skladowe i zwraca strukture Vector
    struct Vector vector3 = {vector1.x + vector2.x, vector1.y + vector2.y};
    return vector3;
}

struct Vector Vector_subtract(struct Vector vector1, struct Vector vector2){ //odejmuje poszczegolne skladowe i zwraca strukture Vector
    struct Vector vector3 = {vector1.x - vector2.x, vector1.y - vector2.y};
    return vector3;
}

struct Vector Vector_upperRight(struct Vector vector1, struct Vector vector2){ //zwraca wieksze wartosci poszczegolnych wektorow
    struct Vector vector3 = {max(vector1.x, vector2.x), max(vector1.y, vector2.y)};
    return vector3;
}

struct Vector Vector_lowerLeft(struct Vector vector1, struct Vector vector2){ //zwraca wieksze wartosci poszczegolnych wektorow
    struct Vector vector3 = {min(vector1.x, vector2.x), min(vector1.y, vector2.y)};
    return vector3;
}

struct Vector Vector_opposite(struct Vector vector){ //zwraca wektory obrocony o 180 stopni
    struct Vector vector_modified = {-vector.x, -vector.y};
    return vector_modified;
}

bool Vector_equals(struct Vector vector1, struct Vector vector2){ //sprawdza czy wektory sa sobie rowne
    return ((vector1.x == vector2.x) && (vector1.y == vector2.y));
}


