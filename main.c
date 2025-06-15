/*
* Rejestr Samochodów
 * ------------------
 * Program umożliwia:
 *   1) Dodawanie nowego samochodu do rejestru (plik tekstowy)
 *   2) Odczyt danych samochodu na podstawie numeru rejestracyjnego
 *   3) Aktualizację przebiegu wybranego auta
 *   4) Wyczyszczenie całego rejestru
 *
 * Format wiersza w pliku `samochody.txt`:
 *  <Lp.> <Marka> <Rocznik> <NrRej> <Przebieg>
 *  np.: 1 Toyota 2015 KR12345 120000
 *
 * Każda funkcja posiada szczegółowy opis poniżej.
 */

#include <stdio.h>
#include <string.h>

/* ------------------------------------------------------------
 *  Pomocnicza funkcja zliczająca pojazdy zapisane w pliku.
 *  Zwraca:
 *    - liczb jeżeli sukces,
 *    - 1 gdy pliku nie da się otworzyć (wartość odróżniająca od 0).
 * ------------------------------------------------------------ */

int QuantityOfVehicle() {
    int NumberOfVehicle;    // liczba porządkowa pojazdow
    char Brand[100];        // marka pojazdu
    int Year;               // rocznik
    char RegNumb[100];      // numer rejestracyjny
    int Mileage;            // przebieg w km
    int counter = 0;

    FILE *fptr = NULL;
    fptr = fopen("samochody.txt", "r");
    if (fptr == NULL) {
        printf("Cos poszlo nie tak\n");
        return 1;
    }
    while (fscanf(fptr, "%d %s %d %s %d", &NumberOfVehicle, Brand, &Year, RegNumb, &Mileage) == 5) {
        counter++;
    }
    fclose(fptr);
    return counter;
}

/* ------------------------------------------------------------
 *  Wyswietla menu glowne programu.
 * ------------------------------------------------------------ */

void menu(void) {
    printf("\n\tRejestr Samochodow\n");
    printf("\n1. Wprowadz nowy samochod\n");
    printf("\n2. Odczytaj dane samochodu\n");
    printf("\n3. Zaaktualizuj przebieg samochodu\n");
    printf("\n4. Wyczysc rejestr samochodow\n");
    printf("\n0. Koniec programu\n");
}

/* ------------------------------------------------------------
 *  Zapisuje nowy samochód do pliku.
 *  Argumenty:
 *    NumberOfVehicle – kolejny numer porządkowy (size z main()).
 *  Zwraca 0 – sukces.
 * ------------------------------------------------------------ */

int enterVehicle(int NumberOfVehicle) {
    char Brand[100];
    int Year;
    char RegNumb[100];
    int Mileage;

    // Pobranie danych od uzytkownika

    printf("\nWprowadz marke:");
    scanf("%s", Brand);

    printf("\nWprowadz rocznik:");
    scanf("%d", &Year);

    printf("\nWprowadz numer rejestracyjny (bez spacji):");
    scanf("%s", RegNumb);

    printf("\nWprowadz przebieg:");
    scanf("%d", &Mileage);

    // Potwierdzenie wprowadzonych danych

    printf("\n Wprowadziles samochod:\n");
    printf("Marka:\t\t\t%s\n", Brand);
    printf("Rocznik:\t\t%d\n", Year);
    printf("Numer Rejestracyjny:\t%s \n", RegNumb);
    printf("Przebieg:\t\t%dkm \n\n", Mileage);

    // Dopisanie danych do pliku

    FILE *fptr = NULL;
    fptr = fopen("samochody.txt", "a");
    if (fptr == NULL) {
        printf("Cos poszlo nie tak\n");
    }
    fprintf(fptr, "%d \t %s %d %s %d \n", NumberOfVehicle, Brand, Year, RegNumb, Mileage);
    printf("Dane pojazdu zostaly zapisane\n");
    fclose(fptr);


    return 0;
}

/* ------------------------------------------------------------
 *  Odczytuje dane konkretnego samochodu na podstawie numeru
 *  rejestracyjnego podanego przez użytkownika.
 *  Zwraca 0 – sukces.
 * ------------------------------------------------------------ */

int CheckVehicle() {
    int NumberOfVehicle;
    char Brand[100], RegNumb[100], EnterRegNumb[100];
    int Year;
    int Mileage;
    int found = 0;
    int counter = 0;
    int NewMileage = 0;

    printf("\nWprowadz numer rejestracyjny samochodu do odczytu:\n");
    scanf("%s", EnterRegNumb);

    FILE *fptr = NULL;
    fptr = fopen("samochody.txt", "r");
    if (fptr == NULL) {
        return 1;
    }
    while (fscanf(fptr, "%d %s %d %s %d", &NumberOfVehicle, Brand, &Year, RegNumb, &Mileage) == 5) {
        if (strcmp(RegNumb, EnterRegNumb) == 0) {

            // Znaleziono pojazd - wypisz dane

            printf("\n Twoj samochod:\n");
            printf("Marka:\t\t\t%s\n", Brand);
            printf("Rocznik:\t\t%d\n", Year);
            printf("Numer Rejestracyjny:\t%s \n", RegNumb);
            printf("Pzebieg:\t\t%dkm \n\n", Mileage);
            found = 1;
            break;
        }
    }
    fclose(fptr);

    if (!found) {
        printf("\nNie ma takiego pojazdu w rejestrze\n");
    }
    return 0;
}

/* ------------------------------------------------------------
 *  Aktualizuje przebieg wybranego samochodu.
 *  Zwraca 0 – sukces, 1 – gdy pojazdu nie znaleziono lub błąd.
 * ------------------------------------------------------------ */

int ChangeMileage() {
    int NumberOfVehicle[100];
    char Brand[100][20], RegNumb[100][20], EnterRegNumb[100];
    int Year[20];
    int Mileage[20];
    int found = 0;
    int counter = 0;

    printf("\nWprowadz numer rejestracyjny samochodu do aktualizacji przebiegu:\n");
    scanf("%s", EnterRegNumb);

    FILE *fptr = NULL;
    fptr = fopen("samochody.txt", "r");
    if (fptr == NULL) {
        printf("Cos poszlo nie tak\n");
        return 1;
    }
    while (fscanf(fptr, "%d %s %d %s %d",
                  &NumberOfVehicle[counter],
                  Brand[counter],
                  &Year[counter],
                  RegNumb[counter],
                  &Mileage[counter]) == 5) {
        counter++;
    }
    fclose(fptr);

    for (int i = 0; i < counter; i++) {
        if (strcmp(RegNumb[i], EnterRegNumb) == 0) {
            printf("\nZnaleziono pojazd: %s %s przebieg: %dkm\n", Brand[i], RegNumb[i], Mileage[i]);
            printf("\nPodaj nowy przebieg:\n");
            scanf("%d", &Mileage[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nNie znaleziono pojazdu o podanym numerze rejestracyjnym");
        return 1;
    }

    fptr = fopen("samochody.txt", "w");
    if (fptr == NULL) {
        printf("Cos poszlo nie tak\n");
        return 1;
    }

    for (int i = 0; i < counter; i++) {
        fprintf(fptr, "%d %s %d %s %d\n", NumberOfVehicle[i], Brand[i], Year[i], RegNumb[i], Mileage[i]);
    }

    fclose(fptr);
    printf("\nPrzebieg zostal zaakatualizowany\n");
    return 0;
}

/* ------------------------------------------------------------
 *  Czysci rejestr samochodów po potwierdzeniu uzytkownika.
 *  Argumenty:
 *    - wskaznik na zmienna przechowującą liczbe pojazdów (NumberOfVehicle),
 *      która zostaje zresetowana do zera po wyczyszczeniu.
 *  Zwraca 0 – sukces, 1 – błąd .
 * ------------------------------------------------------------ */

int ClearList(int *NumberOfVehicle) {
    char decision[100];
    printf("\nCzy jestes tego pewien?\n");
    scanf("%s", decision);
    if (strcasecmp(decision, "nie") == 0) {
        // uzytkownik anulowal czyszczenie
        printf("\nWybrano NIE - wracam do menu\n");
    } else if (strcasecmp(decision, "tak") == 0) {
        // Czyszczenie pliku (nadpisanie pustej zawartosci)
        FILE *fptr = NULL;
        fptr = fopen("samochody.txt", "w");
        if (fptr == NULL) {
            printf("\nCos poszlo nie tak\n");
            return 1;
        }
        fclose(fptr);

        printf("\nWybrano TAK - rejestr wyczyszczony\n");
        *NumberOfVehicle = 0; // zresetuj licznik pojazdow
    } else {
        printf("\nNiepoprawna odpowiedz\n");
    }


    return 0;
}

/*------------------------------------------------------------
 *  Funkcja główna programu – zarządza interfejsem użytkownika.
 *  Obsługuje wybór opcji z menu i wywołuje odpowiednie funkcje.
 * ------------------------------------------------------------ */

int main() {
    int option;                         // zmienna do wyboru opcji menu
    int size = QuantityOfVehicle();     // Poczatkowa liczba pojazdow


    do {
        menu();                         // wyswietl menu

        scanf("%d", &option);

        switch (option) {
            case 0:
                break;

            case 1:
                // Dodanie nowego pojazdu, jeśli limit nie został przekroczony
                if (size >= 20) {
                    printf("\nLiczba pojazdow w rejestrze jest za duza\n");
                } else {
                    size++;
                    enterVehicle(size);
                }
                break;
            case 2:
                // Odczyt danych pojazdu
                CheckVehicle();
                break;

            case 3:
                // Aktualizacja przebiegu
                ChangeMileage();
                break;

            case 4:
                // Czyszczenie rejestru
                ClearList(&size);
                break;

            default:
                printf("\nWybierz poprawny program!\n");
        }
    } while (option != 0);

    printf("\t\n KONIEC PROGRAMU! \n");


    return 0;
}
