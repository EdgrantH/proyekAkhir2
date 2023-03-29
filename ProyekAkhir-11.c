/****************************************************************************\
| Tujuan Program     : Mencari dan membeli tiket konser						 |	
| Nama Pembuat       : 														 |
|                  1. Edgrant Henderson Suryajaya   (2206025016)			 |
|                  2. Farhan Nuzul Noufendri        (2206024442)			 |
| Tanggal pembuatan  : 24 Maret 2023										 |
| Versi Program      : 1.0													 |
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
#define setData(i, y, z, a) strcpy(Concerts[i].namaKonser, y); Concerts[i].harga = z; strcpy(Concerts[i].namaArtist, a);

typedef struct{
	char namaKonser[50];
	char namaArtist[50];
	float harga;
	char hasil[50];
}Concert;

enum color {BLUE, RED, GREEN, YELLOW};

void box(char alas, char dinding, int lebar, int tinggi);
void center_print(char *output, int length);
void resetScreen(int color);
void swap(Concert *a, Concert *b);
int partition(Concert arr[], int low, int high);
void quickSort(Concert arr[], int low, int high);
int partitionStr(Concert arr[], int low, int high);
void quickSortStr(Concert arr[], int low, int high);
int linear_search(Concert *str, int n, char* search, char result[][50]);
int linear_search_2(Concert *str, int n, char* search, char result[][50]);
void settings(int colorPreference);
int read_settings();
void write_settings(int input);
void intro();
int home(int colorPreference);
int ask_for_menu(int colorPreference, char *title, char *choice1, char *choice2, char *choice3, char *choice4);
void set_concert_data(Concert *Concerts);
void display_concert_data(int colorPreference, Concert *Concerts, int dataAmmount);
void display_search(int colorPreference, Concert *Concerts, int dataAmmount, char result[][50]);
void display_search_2(int colorPreference, Concert *Concerts, int dataAmmount, char result[][50]);
void help();
void display_error();
int display_concert_ask_input(int colorPreference, Concert *Concerts, int dataAmmount);
void beli_tiket(int colorPreference, Concert *Concerts, int concertAmmount);
void display_history(int colorPreference);
void display_ticket_list(int colorPreference, Concert *Concerts, int concertAmmount);
void display_searching(int colorPreference, Concert *Concerts, int concertAmmount);

int main(){
    int i, colorPreference, input = 0, concertAmmount = 10;
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
				clear();
				help();
				break;

			case(2):
				input = ask_for_menu(colorPreference, "Ticket Display", "Ticket List", "Search the Ticket", "Buy Ticket", "Buy History");
				switch (input){
					case (1):
						display_ticket_list(colorPreference, Concerts, concertAmmount);
						break;
					case (2):
						display_searching(colorPreference, Concerts, concertAmmount);
						break;

					case(3):
						beli_tiket(colorPreference, Concerts, concertAmmount);
						break;

					case(4):
						display_history(colorPreference);
						break;
					default:
						display_error();
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
				display_error();
				break;
		}
	}

    return 0;
}

void box(char alas, char dinding, int lebar, int tinggi){
    int i, j;
    if(tinggi >= 3 || lebar >= 2){
        printdup(alas, lebar);
        for (j = 0; j < tinggi - 2; j++){
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
	int j;
    int pivot = arr[high].harga;
    int i = (low - 1);
    for (j = low; j <= high - 1; j++) {
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
	int j;
    char *pivot = arr[high].namaKonser;
    int i = low - 1;
    for (j = low; j <= high - 1; j++) {
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

int linear_search(Concert *str, int n, char* search, char result[][50]){
	int i, j = 0;
	for (i = 0; i < n; i++){
		if (strstr(str[i].namaKonser, search) != 0){
			strcpy(result[j], str[i].namaKonser);
			j++;
		}
	}
	return j;
}

int linear_search_2(Concert *str, int n, char* search, char result[][50]){
	int i, j = 0;
	for (i = 0; i < n; i++){
		if (strstr(str[i].namaArtist, search) != 0){
			strcpy(result[j], str[i].namaArtist);
			j++;
		}
	}
	return j;
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
		display_error();
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
		display_error();
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
	return ask_for_menu(colorPreference, "HOME", "Help", "Pick Concert", "Colour Settings", "Exit program");
}

int ask_for_menu(int colorPreference, char *title, char *choice1, char *choice2, char *choice3, char *choice4){
	int input;
	resetScreen(colorPreference);
	box('=', '|', 80, 5);
	gotoxy(3,3);
	center_print (title, 80);
	gotoxy(1, 6);

	if (choice4 == 0 && choice3 != 0){
		box('=', '|', 80, 6);
	}
	else if(choice4 == 0 && choice4 == 0 ) {
		box('=', '|', 80, 5);
	}
	else {
		box('=', '|', 80, 7);
	}

	gotoxy(3, 7);
	printf ("Pemilihan Selanjutnya");
	gotoxy(3, 8);
	printf ("1. %s", choice1);
	gotoxy(3, 9);
	printf ("2. %s", choice2);


	if (choice4 != 0 && choice3 !=0){
	gotoxy(3, 10);
	printf ("3. %s", choice3);	
	gotoxy(3, 11);
	printf ("4. %s", choice4);
	gotoxy(0, 13);
	}
	else if (choice4 == 0 && choice3 != 0){
	gotoxy(3, 10);
	printf ("3. %s", choice3);
	gotoxy(0, 13);
	}
	else
	gotoxy(0,11);
	
	scanf ("%d", &input);

	return input;
}

void set_concert_data(Concert *Concerts){
	setData(0, "Concert A", 9.2, "J");
	setData(1, "Concert B", 3.5, "I");
	setData(2, "Concert C", 12.7, "H");
	setData(3, "Concert D", 3.8, "G");
	setData(4, "Concert E", 9.8, "F");
	setData(5, "Concert F", 4.7, "E");
	setData(6, "Concert G", 15.6, "D");
	setData(7, "Concert H", 17.4, "C");
	setData(8, "Concert I", 3.2, "B");
	setData(9, "Concert J", 12.1, "A");
}

void display_concert_data(int colorPreference, Concert *Concerts, int dataAmmount){
	int i, j;

	resetScreen(colorPreference);
	box('=', '|', 60, 3);
	gotoxy(3,2);
	center_print ("Tickets", 60);
	gotoxy(1,4);

	printdup('-', 60);
	printf ("%-15s %-15s %-11s\n", "Nama Concert", "Artis", "Harga");
	for (j = 0; j < dataAmmount; j++) {
		printf ("%-15s %-15s Rp.%-11.1f\n", Concerts[j].namaKonser, Concerts[j].namaArtist, Concerts[j].harga);
	}
	printdup('-', 60);
}

void display_search(int colorPreference, Concert *Concerts, int dataAmmount, char result[][50]){
	int i, j;
	char hasil_akhir [10][50];
	box('=', '|', 60, 3);
	gotoxy(3,2);
	center_print ("Search Artis", 60);
	gotoxy(1,4);

	printdup('-', 60);

	for (i = 0; i < dataAmmount; i++) {
		for (j = 0; j < 10; j++){
			if(strcmp (result[i], Concerts[j].namaKonser) == 0){
				strcpy(hasil_akhir[j], Concerts[j].namaKonser);
			}
		}
	}

	printf ("%-15s %-15s %-15s\n", "Nama Concert", "Artis", "Harga");

	for (i = 0; i < dataAmmount; i++){
		if (strcmp(hasil_akhir[i], Concerts[i].namaKonser) == 0){
			printf ("%-15s %-15s Rp.%-11.1f\n", Concerts[i].namaKonser, Concerts[i].namaArtist, Concerts[i].harga);
		}
	}
	printdup('-', 60);
	getch();
}

void display_search_2(int colorPreference, Concert *Concerts, int dataAmmount, char result[][50]){
	int i, j;
	char hasil_akhir [10][50];
	box('=', '|', 60, 3);
	gotoxy(3,2);
	center_print ("Search Artis", 60);
	gotoxy(1,4);

	printdup('-', 60);

	for (i = 0; i < dataAmmount; i++) {
		for (j = 0; j < 10; j++){
			if(strcmp (result[i], Concerts[j].namaArtist) == 0){
				strcpy(hasil_akhir[j], Concerts[j].namaArtist);
			}
		}
	}

	printf ("%-15s %-15s %-15s\n", "Nama Concert", "Artis", "Harga");

	for (i = 0; i < dataAmmount; i++){
		if (strcmp(hasil_akhir[i], Concerts[i].namaArtist) == 0){
			printf ("%-15s %-15s Rp.%-11.1f\n", Concerts[i].namaKonser, Concerts[i].namaArtist, Concerts[i].harga);
		}
	}
	printdup('-', 60);
	getch();
}

void help(){
	int i;

	box('=', '|', 60, 3);
	gotoxy(3,2);
	center_print ("Help", 60);
	gotoxy(1,4);
	printdup('-', 60);

	printf (
		"| Mengenai Kuis.\n|\n"
		"| Kuis ini merupakan  Tugas Pertengahan Pemrogramab Lanjut"
		"\n| dengan dosen Pak Budi. Judul dari program ini adalah"
		"\n| Program Pemesanan Tiket Konser. Tujuan dibuatnya"
		"\n| program ini untuk melihat sejauh mana kami dapat"
		"\n| memahami materi 1/2 semester Pemrograman Lanjut"
		"\n| dan untuk mengasah kemampuan kami.\n|"
		
		"\n| List mahasiswa yang mengerjakan program kuis ini : \n"
		
		"| 1. Edgrant Henderson Suryajaya,    NPM : 2206025016 \n"
		"| 2. Farhan Nuzul Noufendri,         NPM : 2206024442 \n"
		
		"|\n| Tekan apapun untuk melanjutkan! \n");
	getch();
	clear();

	box('=', '|', 60, 3);
	gotoxy(3,2);
	center_print ("Help", 60);
	gotoxy(1,4);
	printdup('-', 60);

	printf (
		"| Terdapat beberapa opsi pada halaman Home :\n|\n"
		"| A. Help\n"
			"|\t Help berfungsi sebagai petunjuk mengenai . \n|\n"
		"| B. Pick Concertt\n"
			"|\t Main (Menambah peserta) sebagai opsi untuk melihat list \n"
			"|\t tiket, mencari tiket, memesan tiket, dan melihat riwayat \n"
			"|\t pemesanan tiket.\n|\n"
		"| C. Colour Settings\n"
			"|\t Colour Settings berfungsi untuk mengubah latar tampilan.\n|\n"
		"| D. Exit\n"
			"|\t Exit berfungsi untuk kembali ke layar home. \n"
		"| \n"
		"| tekan apapun untuk kembali ke home\n");
	getch();
}


void display_error(){
	resetScreen(RED);
	box('=', '|', 60, 3);
	gotoxy(3,2);
	center_print ("Inputan Salah, silahkan input ulang", 60);
	gotoxy(1,4);
	getch();
	getchar();
}

int display_concert_ask_input(int colorPreference, Concert *Concerts, int dataAmmount){
	int i, j, output;

	resetScreen(colorPreference);
	box('=', '|', 60, 3);
	gotoxy(3,2);
	center_print ("Tickets", 60);
	gotoxy(1,4);

	printdup('-', 60);
	printf ("%2s %-15s %-12s %-11s\n","No.", "Nama Concert", "Artis", "Harga");
	for (j = 0; j < dataAmmount; j++) {
		printf ("%3d %-15s %-12s Rp.%-11.1f\n", j+1, Concerts[j].namaKonser, Concerts[j].namaArtist, Concerts[j].harga);
	}
	printdup('-', 60);
	
	printf ("Ingin beli nomor berapa (ketik 0 untuk cancel): ");
	scanf ("%d", &output);
	return output;
}

void beli_tiket(int colorPreference, Concert *Concerts, int concertAmmount){
	FILE *fptr;
	int beliTiket;
	int input = ask_for_menu(colorPreference, "Ticket", "List", "Sort by Concert Name", "Sort by Price", 0);
	switch (input){
		case (1):
		break;

		case (2):
			quickSortStr(Concerts, 0, concertAmmount);
			break;

		case (3):
			quickSort(Concerts, 0, concertAmmount);
			break;

		default:
			display_error();
			break;
	}		
	
	beliTiket = display_concert_ask_input(colorPreference, Concerts, concertAmmount);

	fptr = fopen("concert_data.txt", "a");
	if (beliTiket != 0){
		fprintf(fptr, "%s\n", Concerts[beliTiket - 1].namaKonser);
	}
	fclose(fptr);
}

void display_history(int colorPreference){
	resetScreen(colorPreference);
	box('=', '|', 80, 5);
	gotoxy(3,3);
	center_print ("Buy History", 80);
	gotoxy(1, 6);

	FILE *fptr;
   	char s;
   	fptr = fopen("concert_data.txt", "r");
   	while((s = fgetc(fptr)) != EOF) {
   	   printf("%c", s);
   	}
   	getch();
	fclose(fptr);
}

void display_ticket_list(int colorPreference, Concert *Concerts, int concertAmmount){
	int input = ask_for_menu(colorPreference, "Ticket", "List", "Sort by Concert Name", "Sort by Price", 0);
	switch (input){
		case (1):
		break;

		case (2):
			quickSortStr(Concerts, 0, concertAmmount);
			break;

		case (3):
			quickSort(Concerts, 0, concertAmmount);
			break;

		default:
			display_error();
			break;
	}		

	display_concert_data(colorPreference, Concerts, concertAmmount);
	getch();
}

void display_searching(int colorPreference, Concert *Concerts, int concertAmmount){
	int input = ask_for_menu(colorPreference, "Ticket", "Search by Concert Name", "Search by Artist Name", 0, 0);
	int i;
	switch (input){
		case (1):
			clear();
			box('=', '|', 60, 3);
			gotoxy(3,2);
			center_print ("Tickets", 60);
			gotoxy(1,4);
			printdup('-', 60);

			char search_word[100];
			char result[10][50];

			printf("Masukkan kata kunci : ");
			scanf(" %[^\n]s", search_word);

			clear();

			int num = linear_search(Concerts, 10, search_word, result);
			display_search(colorPreference, Concerts, concertAmmount, result);

			printf("Konser yang ditemukan :\n");
			for (i = 0; i < num; i++){
				printf("%s\n", result[i]);
			}

		break;

		case (2):
			clear();
			box('=', '|', 60, 3);
			gotoxy(3,2);
			center_print ("Tickets", 60);
			gotoxy(1,4);
			printdup('-', 60);

			search_word[100];
			result[10][50];

			printf("Masukkan kata kunci : ");
			scanf(" %[^\n]s", search_word);

			clear();

			num = linear_search_2(Concerts, 10, search_word, result);
			display_search_2(colorPreference, Concerts, concertAmmount, result);

			printf("Konser yang ditemukan :\n");
			for (i = 0; i < num; i++){
				printf("%s\n", result[i]);
			}
		break;

		default:
			display_error();
			break;
	}			
}



 