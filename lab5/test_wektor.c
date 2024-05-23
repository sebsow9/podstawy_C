#include <assert.h>
#include "wektor.c"

int main(){
    struct Vector vector1 = {0, 0};
    struct Vector vector2 = {0, 0};

    assert(Vector_equals(vector1, vector2));
    printf("Wektory sa sobie rowne\n\n");

    vector1.x++;
    vector1.y++;

    assert(Vector_follows(vector1, vector2));
    printf("Wektor 1 ma wieksze wspolrzedne niz wektor 2, badz sa rowne\n\n");

    assert(Vector_precedes(vector2, vector1));
    printf("Wektor 2 ma mniejsze wspolrzedne niz wektor 1, badz sa rowne\n\n");
    return 0;
}