#include <stdio.h>
#include <stdlib.h>


FILE *fptr;

//#define SIZE  10

//void printArray(int array[]) {  // Wyswietlanie tablicy
//    printf("\n\n WYSWIETLAM TABLICE: \n");
//    for (int i = 0; i < SIZE; i++) {
//        printf("%d \n", array[i]);
//    }
//}

void printArray(int *array, int size) {
    // Wyswietlanie tablicy przy pomocy wskaznikow
    for (int i = 0; i < size; ++i) {
        printf("array[%d] = %d\n", i, array[i]);
        printf("*(%p) = %d \n\n", array + i, *(array + i));
    }
}

void menu(void) {
    // Wyswietlenie manu wyboru programu
    printf("\n WYBIERZ PROGRAM Z MENU \n\n");
    printf("0. Zakoncz program \n");
    printf("1. Wprowadzanie danych tabeli \n");
    printf("2. Wyswietl tabele \n");
    printf("3. Zmien ilosc danych w tabeli \n");
    printf("4. Suma wartosci \n");
    printf("5. Srednia wartosc \n");
    printf("6. Minimalna wartosc \n");
    printf("7. Maxymalna wartosc \n");
    printf("8. Zapisz dane do pliku \n");
    printf("9. Odczytaj dane z pliku \n");
}

int calculateSum(int *array, int size) {
    // Obliczanie sumy
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += *(array + i);
    }
    return sum;
}

int calculateAvergae(int *array, int size) {
    // Obliczanie sredniej
    float average = 0;
    float sum = calculateSum(array, size);
    average = sum / size;

    return average;
}

int calculateMinimum(int *array, int size) {
    // Znajdywanie najmniejszej wartosci
    int minimum = *array;
    for (int i = 0; i < size; ++i) {
        if (*(array + i) < minimum) {
            minimum = *(array + i);
        }
    }
    return minimum;
}

int calculateMaximum(int *array, int size) {
    // Znajdywanie najwiekszej wartosci
    int maximum = *array;
    for (int i = 0; i < size; ++i) {
        if (*(array + i) > maximum) {
            maximum = *(array + i);
        }
    }
    return maximum;
}

int saveArrayToFile(int *array, int size) {
    FILE *fptr = NULL;
    fptr = fopen("dane.txt", "w");
    if (fptr == NULL) {
        return 1;
    }
    for (int i = 0; i < size; ++i) {
        fprintf(fptr, "%d\n ", array[i]);
    }
    fclose(fptr);

    return 0;
}

int readArrayFromFile(int *array, int size) {
    FILE *fptr = NULL, *fptr2 = NULL;
    fptr = fopen("dane.txt", "r");
    if (fptr == NULL) {
        return 1;
    }
    for (int i = 0; i < size; ++i) {
        fscanf(fptr, "%d\n ", &array[i]);
    }
    fclose(fptr);

    return 0;
}


int main() {
    int SIZE = 10;
    int array[SIZE];
    int option = 0;
    int errorCode = 0;


    do {
        // Wykonywanie wybranych programow do momentu wyboru 0
        menu();

        scanf("%d", &option);
        //        printf("%d", option);  //Wyswietlanie wartosci option

        switch (option) {
            case 0:
                break;

            case 1:
                printf("Wprowadz swoja tablice:\n");
                for (int i = 0; i < SIZE; ++i) {
                    printf("%d = ", i + 1);
                    scanf("%d", &array[i]);
                }
                break;

            case 2:
                printArray(array, SIZE);
                break;

            case 3:
                printf("Wprowadz ilosc danych:\n");
                scanf("%d", &SIZE);
                break;

            case 4:
                printf("Suma wartosci:\n");
                printf("%d", calculateSum(array, SIZE));
                break;

            case 5:
                printf("Srednia wartosci:\n");
                printf("%d", calculateAvergae(array, SIZE));
                break;

            case 6:
                printf("Minimalna wartosc:\n");
                printf("%d", calculateMinimum(array, SIZE));
                break;

            case 7:
                printf("Maksymalna wartosc:\n");
                printf("%d", calculateMaximum(array, SIZE));
                break;

            case 8:
                printf("Zapisywanie danych do pliku\n");
                errorCode = saveArrayToFile(array, SIZE);
                if (errorCode != 1) {
                    printf("Dane zapisane do pliku\n");
                } else {
                    printf("Cos poszlo nie tak\n");
                }
            break;

            case 9:
                printf("Odczytywanie danych z pliku\n");
            errorCode = readArrayFromFile(array, SIZE);
            if (errorCode != 1) {
                printf("Dane odczytane z pliku\n");
            } else {
                printf("Cos poszlo nie tak\n");
            }
            break;

            default:
                printf("\n Wybierz poprawny program!\n");
        }
    } while (option != 0);

    printf("\n\n KONIEC PROGRAMU \n\n");

    return 0;
}
