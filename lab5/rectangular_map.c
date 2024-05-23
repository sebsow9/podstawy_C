#include "car.c"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_SIZE 10

struct Rectangular_Map{ //tworzymy strukture mapu z wektorem ktoy bedzie nam sluzyl za top R corner
    struct Vector upper_border;
    struct Car arr[10];
};


enum MapDirection change_text(char znak){ // robimy funkcje mapujaca znaki na enum map_direction
    switch (znak){
    case 'f':
        return FORWARD;
        break;
    case 'b':
        return BACKWARD;
        break;
    case 'l':
        return LEFT;
        break;
    case 'r':
        return RIGHT;
        break;
    }

}


bool check_for_car(struct Car car, struct Car arr[], int number_of_cars){ // funkcja sprawdzajaca czy na miejscu na ktore chcemy sie poryszuc nie ma juz auta
    for(int x = 0; x<number_of_cars; x++){
        if ((Car_isAt(car, arr[x].vector)) && (car.index != arr[x].index)){
            return true;
        }
    }
    return false;
}

void run_tests(){
    struct Rectangular_Map test_map;
    struct Car test_car = car(1);
    struct Car test_car2 = car(2);
    struct Vector test_vector = {1,1};
    test_map.arr[0] = test_car;
    test_map.arr[1] = test_car2;

    Car_move(&test_car, FORWARD, 3, 3);
    Car_move(&test_car, RIGHT, 3, 3);
    Car_move(&test_car, FORWARD, 3, 3);
    assert(Vector_equals(test_car.vector, test_vector)); //poruszilsmy samochodem 1 w prawo i 1 w gore i sprawdzamy czy jest rowne
    printf("Poprawnie poruszamy samochodem\n\n");

    Car_move(&test_car2, FORWARD, 3, 3);
    Car_move(&test_car2, RIGHT, 3, 3);
    Car_move(&test_car2, FORWARD, 3, 3);
    assert(check_for_car(test_map.arr[1], test_map.arr, 2));
    assert(check_for_car(test_map.arr[0], test_map.arr, 2)); //poruszylismy 2 samochodem w ten sam sposob i sprawdzamy czy funkcja sprawdzajaca kolizje wyswietli TRUE
    printf("Poprawnie wykrywamy kolizje aut\n\n");

    enum MapDirection tab[4];
    tab[0] = change_text('f');
    assert(tab[0] == FORWARD);
    tab[1] = change_text('b');
    assert(tab[1] == BACKWARD);
    tab[2] = change_text('l');
    assert(tab[2] == LEFT);
    tab[3] = change_text('r');
    assert(tab[3] == RIGHT);
    printf("Poprawnie zamieniamy tekst na zmienne typu enum MapDirection\n\n");


}

int main(int argc, char *argv[]){
    
    if (argc>1 &&strcmp(argv[1], "test") == 0){ //sprawdzamy czy zostala podana zmienna test, jezeli tak to uruchamiamy testy
        run_tests();
    }
    else{

        struct Rectangular_Map map;
        printf("Podaj rozmiary mapy w formacie liczba, enter, liczba, enter\n\n");
        int N, M, i, j, g, number_of_cars;
        int flag;
        char buffer[128];
        enum MoveDirection direction[128];
        scanf("%d", &N);
        scanf("%d", &M);
        while(getchar() != '\n'){} //czyscimy bufor

        printf("Podaj ilosc aut, maksymalnie 10: ");
        scanf("%d", &number_of_cars);
        while(getchar() != '\n'){} //czyscimy bufor
        struct Vector subvec = {0,1};
        
        switch (number_of_cars){ //tworzymy ilosc aut
        case 10:
            struct Car car10 = car(10);
            map.arr[9] = car10;
            
        case 9:
            struct Car car9 = car(9);
            map.arr[8] = car9;
            
        case 8:
            struct Car car8 = car(8);
            map.arr[7] = car8;
            
        case 7:
            struct Car car7 = car(7);
            map.arr[6] = car7;
            
        case 6:
            struct Car car6 = car(6);
            map.arr[5] = car6;
            
        case 5:
            struct Car car5 = car(5);
            map.arr[4] = car5;
            
        case 4:
            struct Car car4 = car(4);
            map.arr[3] = car4;
            
        case 3:
            struct Car car3 = car(3);
            map.arr[2] = car3;
            
            
        case 2:
            struct Car car2 = car(2);
            map.arr[1] = car2;
            
            
        case 1:
            struct Car car1 = car(1);
            map.arr[0] = car1;
        
        }
        
        while (true){
            printf("Podaj sekwencje: \n");
            fgets(buffer, 128, stdin); //pobieramy cala linie
            i = 0;
            j = 0;
            flag = 0;
            if(buffer[0] == 'Q'){
                break;
            }
            while (true){
                
                if(buffer[i] == '\n') break;
                if(buffer[i] == ' '){
                    j++;
                }
                else{
                    direction[j] = change_text(buffer[i]); //zmieniamy te linie na enum i kierunek
                }
                i++;
            }
            g=0;
            
            while(flag != 1){
                
                for(int l = 0; l<number_of_cars; l++){
                    
                    if(l+g*number_of_cars >j){ //sprawdzamy czy nie wyjdziemy poza indeks
                        flag = 1;
                        break;
                    }
                    Car_move(&map.arr[l], direction[l + g*number_of_cars], N, M);
                    
                    while(check_for_car(map.arr[l], map.arr, number_of_cars)){ //sprawdzamy kolizje, jezeli jest to obracamy o 180 stopni i jedziemy, az auto znajdzie sie na pozycji bez auta
                        printf("Could not move car: %d\n", l);
                        MapDirection_next(direction[l + g*number_of_cars]);
                        MapDirection_next(direction[l + g*number_of_cars]);
                        Car_move(&map.arr[l], direction[l + g*number_of_cars], N, M);
                    }
                    
                }
                g++;
                
            }
            printf("Pozycje Aut: \n"); //wyswietlanie pozycji aut
                for(int p =0; p<number_of_cars; p++){
                    printf("Polozenia auta numer: %d to ", p+1);
                    Vector_toString(map.arr[p].vector);
                }
        }    
    }
    return 0;    
}
