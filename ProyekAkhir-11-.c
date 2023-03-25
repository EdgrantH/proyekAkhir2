/****************************************************************************\
| Tujuan Program     : Mencari dan membeli tiket konser						 |	
| Nama Pembuat       : 														 |
|                  1. Edgrant Henderson Suryajaya   (2206025016)			 |
|                  2. Farhan Nuzul Noufendri        (2206024442)			 |
| Tanggal pembuatan  : 24 Maret 2023										 |
| Versi Program      : 0.3													 |
\****************************************************************************/

/*
TODO: 
	Ubah beberapa barang jadi function, contohnya print error handling sama thankyou sebenarnya mirip banget
	Buat:
		data input
		setting
			read setting files
			output setting to flie
		sorting 
		searching
	prototype function
	flowchart
	pseudocode
*/

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

typedef struct{
	char namaKonser[50];
	char namaArtist[50];
	float waktuMulai;
	float durasi;
	float harga;
}Flights;

void box(char alas, char dinding, int lebar, int tinggi);
void center_print(char *output, int length);
void resetScreen(int color);
void settings(int colorPreference);
int read_settings();
void write_settings(int input);
bool read_flight_data();
void intro();
int home(int colorPreference);


enum color {BLUE, RED, GREEN, YELLOW};
// 
int main()
{
    int i, colorPreference, input = 0;
	intro();

	while(input != 4){
		colorPreference = read_settings();
		input = home(colorPreference);
		switch (input){
			case(1):
				//help
				break;
				
			case(2):
				//memilih concert
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

bool read_flight_data(){
	FILE *fptr;
	fptr = fopen("flight_data.txt", "r");

	//return false if file doesn't exist
	if (fptr == NULL) return false;
	
	
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
	resetScreen(colorPreference);
	box('=', '|', 80, 5);
	gotoxy(3,3);
	center_print ("Home", 80);
	gotoxy(1, 6);
	box('-', '|', 80, 7);
	gotoxy(3, 7);
	printf ("Pemilihan Selanjutnya");
	gotoxy(3, 8);
	printf ("1. Help");
	gotoxy(3, 9);
	printf ("2. Pick Concerts");
	gotoxy(3, 10);
	printf ("3. Settings");
	gotoxy(3, 11);
	printf ("4. Exit program");

	
	gotoxy(3, 13);
	scanf ("%d", &input);
	return input;
}
