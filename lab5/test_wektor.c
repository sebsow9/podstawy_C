#include <assert.h>
#include "wektor.c"





int main(){
    struct Vector vector1 = {0, 0};
    struct Vector vector2 = {0, 0};
    struct Vector vector3 = {1, 1};
    struct Vector vector4 = {-1, -1};

    assert(Vector_equals(vector1, vector2));
    printf("Wektory sa sobie rowne\n\n");

    vector1.x++;
    vector1.y++;

    assert(Vector_follows(vector1, vector2));
    printf("Wektor 1 ma wieksze wspolrzedne niz wektor 2, badz sa rowne\n\n");

    assert(Vector_precedes(vector2, vector1));
    printf("Wektor 2 ma mniejsze wspolrzedne niz wektor 1, badz sa rowne\n\n");

    assert(Vector_equals(Vector_add(vector1, vector2), vector3));
    printf("Dodawanie jest poprawne\n\n");

    assert(Vector_equals(Vector_subtract(vector2, vector1), vector4));
    printf("Odejmowanie jest poprawne\n\n");

    assert(Vector_equals(Vector_upperRight(vector3, vector4), vector3));
    printf("Wektor (1,1) jest wiekszy niz (-1,-1)\n\n");

    assert(Vector_equals(Vector_lowerLeft(vector3, vector4), vector4));
    printf("Wektor (1,1) jest mniejszy niz (-1,-1)\n\n");

    assert(Vector_equals(Vector_opposite(vector3), vector4));
    printf("Poprawnie odwrocilismy wektor\n\n");






    return 0;
}