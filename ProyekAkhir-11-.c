/****************************************************************************\
| Tujuan Program     : Mencari dan membeli tiket konser						 |	
| Nama Pembuat       : 														 |
|                  1. Edgrant Henderson Suryajaya   (2206025016)			 |
|                  2. Farhan Nuzul Noufendri        (2206024442)			 |
| Tanggal pembuatan  : 24 Maret 2023										 |
| Versi Program      : 0.3													 |
\****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <ctype.h>

//sumber https://stackoverflow.com/questions/26423537/how-to-position-the-input-text-cursor-in-c
#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

//mengprint karakter x sebanyak y kali, dalam python ini adalah print("x"*y)
#define printdup(x, y) for(i = 0; i < y; i++) printf("%c", x); printf("\n");
//mengprint karakter x yang mengimpin kosong dengan total panjang y
#define printBorder(x, y) printf("%c", x); for(i = 0; i < y-2; i++) printf(" "); printf("%c\n", x)
#define setData(i, y, z) strcpy(Concerts[i].namaKonser, y); Concerts[i].harga = z;

typedef struct{
	char namaKonser[50];
	char namaArtist[50];
	float waktuMulai;
	float durasi;
	float harga;
}Concert;

void box(char alas, char dinding, int lebar, int tinggi);
void center_print(char *output, int length);
void resetScreen(int color);
void swap(Concert *a, Concert *b);
int partition(Concert arr[], int low, int high);
void quickSort(Concert arr[], int low, int high);
int partitionStr(Concert arr[], int low, int high);
void quickSortStr(Concert arr[], int low, int high);
void settings(int colorPreference);
int read_settings();
void write_settings(int input);
void intro();
int home(int colorPreference);
int ask_for_menu(int colorPreference, char *title, char *choice1, char *choice2, char *choice3, char *choice4);
void set_concert_data(Concert *Concerts);

enum color {BLUE, RED, GREEN, YELLOW};
// 
int main()
{
    int i, colorPreference, input = 0, concertAmmount = 4;
	bool firstLoop = true;
	Concert Concerts[50];//kalau ada waktu ini bikin dynamic memori
	intro();

	while(input != 4){
		colorPreference = read_settings();
		set_concert_data(Concerts);
		quickSortStr(Concerts, 0, concertAmmount);
		
		if (firstLoop){
			firstLoop = false;
			continue;
		}//ini ngeskip loop pertama, fungsinya agar display Concerts dapat benar, kalau gak index ke-0 akan diskip.

		input = home(colorPreference);

		switch (input){
			case(1):
				//help();
				break;
				
			case(2):
				input = ask_for_menu(colorPreference, "Ticket Display", "sort by name", "sort by price", "search name", "exit");
				switch (input){
					case (1):
						quickSortStr(Concerts, 0, concertAmmount);
						display_concert_data(colorPreference, Concerts, concertAmmount);
						break;
					
					case (2):
						quickSort(Concerts, 0, concertAmmount);
						display_concert_data(colorPreference, Concerts, concertAmmount);
						break;
					
					case (3):
						//searching
						break;
					
					case (4):
						break;
					
					default:
						resetScreen(RED);
						box('=', '|', 60, 3);
						gotoxy(3,2);
						center_print ("Inputan Salah, silahkan input ulang", 60);
						gotoxy(1,4);
						getch();
						getchar();
						break;
				}
				break;
				
			case(3):
				settings(colorPreference);
				break;
				
			case(4):
				resetScreen(GREEN);
				box('=', '|', 60, 3);
				gotoxy(3,2);
				center_print ("Terima kasih udah memakai program kita", 60);
				gotoxy(1,4);
				getch();
				break;
				
			default:
				resetScreen(RED);
				box('=', '|', 60, 3);
				gotoxy(3,2);
				center_print ("Inputan Salah, silahkan input ulang", 60);
				gotoxy(1,4);
				getch();
				getchar();
				break;
		}
	}

    return 0;
}

void box(char alas, char dinding, int lebar, int tinggi){
    int i, j;
    if(tinggi >= 3 || lebar >= 2){
        printdup(alas, lebar);
        for (int j = 0; j < tinggi - 2; j++){
            printBorder(dinding, lebar); 
        } 
        printdup(alas, lebar);
    }
}

//print text to align center
void center_print(char *output, int length){
	int strLength = strlen(output);
	int offset = (length - strLength)/2;
	int i;
	for (i = 0; i < offset; i++) {
		printf(" ");
	}
    printf("%s", output);
}

void swap(Concert *a, Concert *b) {
    Concert t = *a;
    *a = *b;
    *b = t;
}

int partition(Concert arr[], int low, int high) {
    int pivot = arr[high].harga;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].harga <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Concert arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partitionStr(Concert arr[], int low, int high) {
    char *pivot = arr[high].namaKonser;
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j].namaKonser, pivot) < 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSortStr(Concert arr[], int low, int high) {
    if (low < high) {
        int pi = partitionStr(arr, low, high);
        quickSortStr(arr, low, pi - 1);
        quickSortStr(arr, pi + 1, high);
    }
}

//menghilangkan semua text di console dan mengganti warnanya
void resetScreen(int color){
	clear();
	
	switch (color){
		case (BLUE):
			system("color 90");
			break;
		case (RED):
			system("color 4f");
			break;
		case (GREEN):
			system("color A0");
			break;
		case (YELLOW):
			system("color E0");
			break;
		default:
			system("color 07");
			break;
	}
}

int read_settings(){
	int input;
	FILE *fptr = fopen("settings.txt", "r");

	if (fptr == NULL){
		write_settings(BLUE);
		fptr = fopen("settings.txt", "r");
	}

	fscanf(fptr, "%d", &input);

	fclose(fptr);
	return input;
}

void write_settings(int input){
	FILE *fptr = fopen("settings.txt", "w+");

	if (fptr == NULL){
		resetScreen(RED);
		box('=', '|', 60, 3);
		gotoxy(3,2);
		center_print ("File tidak berhasil dibuat", 60);
		gotoxy(1,4);
		getch();
		getchar();
	}

	fprintf(fptr, "%d", input);

	fclose(fptr);
}

void settings(int colorPreference){
	int i, input;

	resetScreen(colorPreference);
	box('=', '|', 60, 3);
	gotoxy(3,2);
	center_print ("Settings", 60);
	gotoxy(1,4);

	printdup('-', 60);
	printf ("Pilih warna: \n");
	printf ("1. biru \n");
	printf ("2. merah \n");
	printf ("3. hijau \n");
	printf ("4. kuning \n");
	printdup('-', 60);
	printf ("Input: ");
	scanf ("%d", &input);

	if (input < 1 || input > 4){
		resetScreen(RED);
		box('=', '|', 60, 3);
		gotoxy(3,2);
		center_print ("Inputan Salah, silahkan input ulang", 60);
		gotoxy(1,4);
		getch();
		getchar();
	}

	write_settings(input-1);
}

void intro(){
	resetScreen(YELLOW);
	box('=', '|', 80, 5);
	gotoxy(3,3);
	center_print ("Peron Pembelian Tiket", 80);
	gotoxy(1, 6);
	center_print ("Silahkan membuat program fullscreen\n", 80);
	center_print ("pencet apapun untuk lanjut...\n", 80);
	getch();
}

int home(int colorPreference){
	int input;
	return ask_for_menu(colorPreference, "HOME", "Help", "Pick Concert", "Settings", "Exit program");
}

int ask_for_menu(int colorPreference, char *title, char *choice1, char *choice2, char *choice3, char *choice4){
	int input;
	resetScreen(colorPreference);
	box('=', '|', 80, 5);
	gotoxy(3,3);
	center_print (title, 80);
	gotoxy(1, 6);
	box('-', '|', 80, 7);
	gotoxy(3, 7);
	printf ("Pemilihan Selanjutnya");
	gotoxy(3, 8);
	printf ("1. %s", choice1);
	gotoxy(3, 9);
	printf ("2. %s", choice2);
	gotoxy(3, 10);
	printf ("3. %s", choice3);
	gotoxy(3, 11);
	printf ("4. %s", choice4);
	
	gotoxy(3, 13);
	scanf ("%d", &input);

	return input;
}

void set_concert_data(Concert *Concerts){
	setData(0, "Concert A", 9.2);
	setData(1, "Concert B", 3.5);
	setData(2, "Concert C", 12.7);
	setData(3, "Concert D", 5.8);
}

void display_concert_data(int colorPreference, Concert *Concerts, int dataAmmount){
	int i, j;

	resetScreen(colorPreference);
	box('=', '|', 60, 3);
	gotoxy(3,2);
	center_print ("Tickets", 60);
	gotoxy(1,4);

	printdup('-', 60);
	printf ("%-45s %-11s\n", "Nama Concert", "Harga");
	for (j = 0; j < dataAmmount; j++) {
		printf ("%-45s Rp.%-11.1f\n", Concerts[j].namaKonser, Concerts[j].harga);
	}
	printdup('-', 60);
	getch();
}