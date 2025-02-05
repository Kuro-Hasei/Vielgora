#ifndef TAMPILAN_H
#define TAMPILAN_H
#include <Windows.h>

int maxWidht = 173;
int maxHeight = 42;

const int colorMainText = 4;
const int colorHeadText = 160;
const int colorScText = 11;
const int colorThdText = 112;
const int text2 = 10;

void SetColorBlock(int foreground, int background)
{
    int color = foreground + (background << 4);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void SetColor(unsigned short color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleOutput,color);
}

void gotoxy(int x, int y) {
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void PrintFile(char file[100], int x, int y)
{
    FILE *Text;
    char Data[100];
    if((Text=fopen(file, "r")) == NULL)
    {
        system("cls");
    }
    while(fgets(Data, 100, Text))
    {
        gotoxy(x, y);
        printf("%s", Data);
        y++;
    }
    fclose(Text);
}

void showMessage(const char *title, const char *message) {
    MessageBox(NULL, message, title, MB_OK | MB_ICONINFORMATION);
}

void fullscreen() {
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void cleanKanan() {
    char space = ' ';
    for (int i = 1; i <= 41; i++) {
        gotoxy(126, i);
        printf("%-46c", space);
    }
}

void cleanKiri() {
    char space = ' ';
    for (int i = 1; i < 41; i++) {
        gotoxy(1, i);
        printf("%-124c", space);
    }
}

void printASCII(int code, int x, int y) {
    gotoxy(x, y); printf("%c", code);
}

void setConsoleFont(int fontSizeX, int fontSizeY, const wchar_t* fontName) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    // Mendapatkan informasi font saat ini
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

    // Mengganti ukuran font
    fontInfo.dwFontSize.X = fontSizeX;
    fontInfo.dwFontSize.Y = fontSizeY;

    // Mengganti nama font
    wcscpy(fontInfo.FaceName, fontName);

    // Mengganti bentuk font
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

void gettodayDate(char dateNow[]) {
    // Mendapatkan waktu saat ini
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    // Format tanggal sebagai string DD/MM/YYYY
    sprintf(dateNow, "%02d-%02d-%d", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
}

void frame() {
    char dateNow[11];

    SetColor(colorMainText);
    PrintFile("../TXT/Monitor.txt", 26, 5);
    PrintFile("../TXT/Vielgora.txt", 37, 12);
    SetColor(text2);
    gettodayDate(dateNow);
    gotoxy(56,25); printf("%s", dateNow);

    SetColor(colorMainText);
    printASCII(200, 0,maxHeight);
    printASCII(201, 0,0);
    printASCII(187, maxWidht,0);
    printASCII(188, maxWidht,maxHeight);
    for (int i = 1; i < maxWidht; i++) {
        printASCII(205, i, 0);
    }
    for (int i = 1; i < maxWidht; i++) {
        printASCII(205, i, maxHeight);
    }
    for (int i = 1; i < maxHeight; i++) {
        printASCII(186, 125, i);
        printASCII(186, 0, i);
        printASCII(186, maxWidht, i);
    }
    printASCII(203, 125, 0);
    printASCII(202, 125, maxHeight);
}

void templateUI() {
    SetColor(colorMainText);

    printASCII(200, 0,maxHeight);
    printASCII(201, 0,0);
    printASCII(187, maxWidht,0);
    printASCII(188, maxWidht,maxHeight);
    for (int i = 1; i < maxWidht; i++) {
        printASCII(205, i, 0);
    }
    for (int i = 1; i < maxWidht; i++) {
        printASCII(205, i, maxHeight);
    }
    for (int i = 1; i < maxHeight; i++) {
        printASCII(186, 0, i);
        printASCII(186, maxWidht, i);
    }
}

void printKotak(int lebar, int tinggi, int x, int y) {
    SetColorBlock(4,0);
    int j = 0;
    for (int i = x; i < x + lebar +1; i++) {
        printASCII(196, i, y - 1);
        printASCII(196, i, y + 1);
        printASCII(196, i, y + tinggi);
        j++;
    }
    int k = 0;
    for (int i = y; i < y + tinggi; i++) {
        printASCII(179, x, i);
        printASCII(179, x + lebar, i);
        k++;
    }
    printASCII(191, x + lebar, y-1);
    printASCII(218, x, y-1);
    printASCII(217, x+lebar, y+tinggi);
    printASCII(192, x, y+tinggi);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// Deklarasi prosedur untuk menampilkan kursor
void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

/*-------------------------------------Mematikan scrollbar CMD----------------------------------------*/
void disableScrollBar() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Mendapatkan informasi tentang jendela console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);

    // Menyusun atribut baru untuk mengunci scrollbar
    csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y;

    // Menyetel ukuran jendela console
    SetConsoleScreenBufferSize(hOut, csbi.dwSize);

    // Menonaktifkan scrollbar
    SetConsoleMode(hOut, ENABLE_EXTENDED_FLAGS);
}

void loading() {
    int x;
    SetColor(colorMainText);
    gotoxy(73, 36);
    printf("L O A D I N G . . . ");         //Loading

    SetColor(text2);
    for (x = 71; x <= 101; x++) {           //atas
        gotoxy(x, 35);
        printf("%c", 196);
    }
    for (x = 71; x <= 101; x++) {           //bawah
        gotoxy(x, 37);
        printf("%c", 196);
    }
    for (x = 71; x <= 101; x++) {           //isi
        Sleep(100);
        gotoxy(x, 36);
        printf("%c", 219);
    }
    SetColor(colorMainText);
    gotoxy(71, 36);
    system("pause");
    system("cls");
}

int row = 112;
int keluar() {
    SetColor(3);;
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

    gotoxy(67, 19);
    printf("YAKIN MAU KELUAR?");
    gotoxy(75, 21); printf("YES");
    gotoxy(75, 23); printf("NO");

    int pil = 1;
    int banyakMenu = 2;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(10);
                printASCII(174, row -32, 21 + (i - 1) * 2);
                printASCII(174, row -31, 21 + (i - 1) * 2);
                printASCII(174, row -30, 21 + (i - 1) * 2);
            } else {
                SetColor(0);
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
                system("cls");
            return pil;
        }
    }
}

#endif //TAMPILAN_H