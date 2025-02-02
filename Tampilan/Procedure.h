#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>

/*==================== FUNCTION BUTTONS ====================*/
#define ENTER 13
#define TAB 9
#define BCKSPC 8
#define ESC 27

/*==================== ARROW BUTTONS ====================*/
#define UP_KEY 72
#define DWN_KEY 80
#define RGHT_KEY 77
#define LEFT_KEY 75

#define STATIC_NUMB 18
#define STATIC_NUMB_LOGIN 62

int lihatDetil() {
    SetColorBlock(3,7);
    for (int j = 15; j < 25; j++) {
        for (int i = 50; i < 105; i++) {
            printASCII(244, i, j);
        }
    }
    SetColor(7);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    gotoxy(67, 19); printf("LIHAT DETAIL DATA?");
    gotoxy(75, 21); printf("YES");
    gotoxy(75, 23); printf("NO");

    int pil = 1;
    int banyakMenu = 2;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColorBlock(3,7);
                printASCII(174, row -32, 21 + (i - 1) * 2);
                printASCII(174, row -31, 21 + (i - 1) * 2);
                printASCII(174, row -30, 21 + (i - 1) * 2);
            } else {
                SetColorBlock(3,7);
                gotoxy(row -32, 21 + (i - 1) * 2);
                printf("   ");
            }
        }

        char ch = getch();
        switch (ch) {
            case 72:  // Panah atas
                if (pil > 1) {
                    pil--;
                }
            break;
            case 80:  // Panah bawah
                if (pil < banyakMenu) {
                    pil++;
                }
            break;
            case 13:  // Tombol Enter
                return pil;
        }
    }
}

int deleteData() {
    SetColorBlock(3,7);
    for (int j = 15; j < 25; j++) {
        for (int i = 50; i < 105; i++) {
            printASCII(244, i, j);
        }
    }
    SetColorBlock(3,7);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    gotoxy(67, 19);
    printf("YAKIN HAPUS INI?");
    gotoxy(75, 21); printf("YES");
    gotoxy(75, 23); printf("NO");

    int pil = 1;
    int banyakMenu = 2;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColorBlock(3,7);
                printASCII(174, row -32, 21 + (i - 1) * 2);
                printASCII(174, row -31, 21 + (i - 1) * 2);
                printASCII(174, row -30, 21 + (i - 1) * 2);
            } else {
                SetColorBlock(3,7);
                gotoxy(row -32, 21 + (i - 1) * 2);
                printf("   ");
            }
        }

        char ch = getch();
        switch (ch) {
            case 72:  // Panah atas
                if (pil > 1) {
                    pil--;
                }
            break;
            case 80:  // Panah bawah
                if (pil < banyakMenu) {
                    pil++;
                }
            break;
            case 13:  // Tombol Enter
                cleanKiri();
            return pil;
        }
    }
}

int doaction(char text[]) {
    //    cleanKiri();
    //    templateUI2();
    SetColorBlock(4,7);
    for (int j = 15; j < 25; j++) {
        for (int i = 50; i < 105; i++) {
            printASCII(244, i, j);
        }
    }
    SetColorBlock(2,7);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    gotoxy(68, 19); printf("YAKIN MAU %s?", text);
    gotoxy(72, 21); printf("YES");
    gotoxy(72, 23); printf("NO");

    int pil = 1;
    int banyakMenu = 2;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColorBlock(3,7);
                printASCII(174, 82, 21 + (i - 1) * 2);
                printASCII(174, 83, 21 + (i - 1) * 2);
                printASCII(174, 84, 21 + (i - 1) * 2);
            } else {
                SetColorBlock(3,7);
                gotoxy(82, 21 + (i - 1) * 2);
                printf("   ");
            }
        }

        char ch = getch();
        switch (ch) {
            case 72:  // Panah atas
                if (pil > 1) {
                    pil--;
                }
            break;
            case 80:  // Panah bawah
                if (pil < banyakMenu) {
                    pil++;
                }
            break;
            case 13:  // Tombol Enter
                cleanKiri();
            return pil;
        }
    }
}

void passwordPrivasi (char pwd[50]) {
    int i;
    char ch;
    while (1) {
        ch = getch();
        if (ch == ENTER || ch == TAB) {
            pwd [i] = '\0';
            break;
        } else if (ch == BCKSPC) {
            if(i>0) {
                i--;
                printf("\b \b");
            }
        } else {
            pwd[i++] = ch;
            printf("* \b");
        }
    }
}

void printTable(int btsKiri, int btsKanan, int atas, int bawah) {
    SetColor(5);
    for (int i = btsKiri; i < btsKanan; i++) {
        printASCII(205, i, atas);
        printASCII(205, i, atas+2);
        printASCII(196, i, bawah);
    }
    SetColor(3);
}

// Fungsi untuk menghapus karakter terakhir di konsol
void deleteLastCharacters(int count) {
    for (int i = 0; i < count; i++) {
        printf("\b \b");
    }
}

// Fungsi untuk memvalidasi tanggal
int validateDate(int day, int month, int year) {
    if (day <= 0 || day > 31 || month <= 0 || month > 12 || year <= 0) {
        return 0;
    }
    if (month == 2) { // Februari, cek tahun kabisat
        int isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if ((isLeapYear && day > 29) || (!isLeapYear && day > 28)) {
            return 0;
        }
    }
    // Bulan dengan maksimal 30 hari
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return 0;
    }
    if (year < 1900 || year > 2100) { // batas tahun
        return 0; // Tahun tidak valid
    }
    return 1;
}

void getDate(char *date) {
    char strcurrent;
    int n = 0; // Panjang string input
    int valid = 0; // Status validitas tanggal

    do {
        strcurrent = getch();

        if (strcurrent == '\b' && n > 0) { // Backspace
            deleteLastCharacters(1);
            date[--n] = '\0';
        } else if (isdigit(strcurrent)) { // Jika input adalah digit
            if (n < 10) {
                printf("%c", strcurrent);
                date[n++] = strcurrent;

                if (n == 2 || n == 5) { // Tambahkan pemisah '-'
                    printf("-");
                    date[n++] = '-';
                }
            }
        }
    } while (strcurrent != 13); // Berhenti saat Enter ditekan

    // Tambahkan null-terminator
    date[n] = '\0';

    // Validasi format string
    if (strlen(date) != 10 || date[2] != '-' || date[5] != '-') {
        showMessage("ALERT!", "FORMAT TANGGAL TIDAK VALID!");
        deleteLastCharacters(n);
        getDate(date); // Meminta input ulang
        return;
    }

    // Parse tanggal
    int day, month, year;
    sscanf(date, "%2d-%2d-%4d", &day, &month, &year);

    // Validasi tanggal
    valid = validateDate(day, month, year);
    if (!valid) {
        showMessage("ALERT!", "TANGGAL TIDAK VALID!");
        deleteLastCharacters(n);
        getDate(date); // Meminta input ulang
    }
}


void getinputmin(char input[], int min, int max, int type){
    char strcurrent;
    int i,n,x,m;
    n = 0;
    x=0;
    do
    {
        strcurrent = getch();

        if(strcurrent == '\b' && n != 0) //backspace
        {
            printf("\b \b");
            input[n]='\0';
            n--;
        }
        //else if(current >= 32 && current <= 122){
        else if(isprint(strcurrent)){ //karakter yang bisa di print
            if(n == max) {
                continue;
            }
            else{
                if(type == 3){ //isdigit = hanya angka
                    if(isdigit(strcurrent)) {
                        printf("%c", strcurrent);
                        input[n]=strcurrent;
                        n++;
                    }
                    else printf("\a");
                }
                else if(type == 2){ //isalpha = alpabet dan spasi co : nama
                    if(isalpha(strcurrent) || strcurrent == ' ') {
                        printf("%c", strcurrent);
                        input[n]=strcurrent;
                        n++;
                    }
                    else printf("\a");
                }
                else {
                    if(type == 1) // password //0= bebas
                    {
                        if(strcurrent==35||x>0)
                        {
                            if(strcurrent==35)
                            {
                                x=x+1;
                                for(m=0;m<n;m++)
                                {
                                    printf("\b \b");
                                }
                                for(m=0;m<n;m++)
                                {
                                    printf("%c",input[m]);
                                }

                            }
                            else if(strcurrent==64)
                            {
                                x=0;
                                for(m=0;m<n;m++)
                                {
                                    printf("\b \b");
                                }
                                for(m=0;m<n;m++)
                                {
                                    printf("*");
                                }
                            }
                            else
                            {
                                printf("%c", strcurrent);
                                input[n]=strcurrent;
                                n++;
                            }
                        }
                        else
                        {
                            printf("*");
                            input[n]=strcurrent;
                            n++;
                        }
                    }
                    else
                    {
                        printf("%c", strcurrent);
                        input[n]=strcurrent;
                        n++;
                    }
                }
            }
        }
        else if(strcurrent == 13)
        {
            if(n < min) {
                printf("\a");
                strcurrent = 0;
            }
            else input[n]='\0';
        }
        //else if(current == 27) end();
    }
    while(strcurrent != 13);
}

void getinput(char input[], int max, int type){
    getinputmin(input, 1, max, type);
}

void getteks(char input[], int max){
    getinput(input, max, 0);
}

void getalfabet(char input[], int max){
    getinput(input, max, 2);
}

void getnum(int *dest, int max){
    char input[max];
    getinput(input, max, 3);
    *dest = atoi(input);
    if (*dest < 0 || *dest > 9999999999999) { // Contoh validasi rentang angka
        printf("\nAngka tidak valid, coba lagi.\n");
        getnum(dest, max); // Meminta input ulang
    }
}

void getno(char input[], int max){
    getinput(input, max, 3); // Biarkan dalam bentuk string
}

void rupiah(int number, char output[])
{
    // menampilkan Bentuk Rupiah
    if(number < 1000) sprintf(output, "%d", number);
    else if(number < 1000000) sprintf(output, "%d.%03d", number/1000, number%1000);
    else if(number < 1000000000) sprintf(output, "%d.%03d.%03d", number/1000000, (number%1000000)/1000, number%1000);
    else sprintf(output, "%d.%03d.%03d.%03d", number/1000000000, (number%1000000000)/1000, (number%1000000)/1000, number%1000);
}

void getRp(int *nilai, int min, int max, int x, int y)
{
    char input[225];
    char inpkey;
    int i, n, m;
    n = 0;

    do
    {
        inpkey = getch();
        if(inpkey == '\b' && n != 0)
        {
            n--;
            input[n] = '\0';

            m = n % 3;
            if((n - m) % 3 == 0 || n == m){
                printf("\b \b");
                printf("\b \b");
            }else{
                printf("\b \b");
            }
            gotoxy(x,y);
            for(i = 0; i < n; i++){
                if((i + 1) == m || (i + 1 - m) % 3 == 0){
                    printf("%c", input[i]);
                    if(i != (n - 1)){
                        printf(".");
                    }
                }else {
                    printf("%c", input[i]);
                }
            }
        }else if (isprint(inpkey)){
            if(n == max){
                continue;
            }else {
                if (isdigit(inpkey)){
                    gotoxy(x,y);
                    input[n]=inpkey;
                    n++;
                    m = n % 3;
                    for(i = 0; i < n; i++){
                        if((i+1) == m || (i+1-m) % 3 == 0){
                            printf("%c", input[i]);
                            if(i != (n-1)){
                                printf(".");
                            }
                        }else {
                            printf("%c", input[i]);
                        }
                    }
                }
                else printf("\a");
            }
        }
        else if(inpkey == 13)
        {
            if(n < min){
                printf("\a");
                inpkey = 0;
            }
            else input[n]='\0';
        }
    }
    while(inpkey != 13);

    *nilai = atoi(input);
}

#endif //PROCEDURE_H
