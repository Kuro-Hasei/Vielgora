#ifndef menu_h
#define menu_h
#include <windows.h>
#include "Tampilan.h"
#include "../Source/Deklarasi.h"
#include <conio.h>

#include "../Source/crud_Karyawan.h"
#include "../Source/crud_Aksesoris.h"
#include "../Source/crud_Diskon.h"
#include "../Source/crud_Garansi.h"
#include "../Source/crud_Layanan.h"
#include "../Source/crud_Member.h"
#include "../Source/crud_Produk.h"
#include "../Source/cruid_Supplier.h"
#include "../Transaksi/Trsk_Penjualan.h"
#include "../Transaksi/Trsk_Member.h"
#include "../Transaksi/Trsk_Pembelian.h"
#include "../Transaksi/Trsk_KlaimGaransi.h"


void mainPage() {
    SetColorBlock(3,7);
    Sleep(50);
    PrintFile("../TXT/Vielgora.txt", 60, 12);
    printASCII(201, 0,0);
    printASCII(187, maxWidht,0);
    for (int i = 1; i < maxWidht; i++) {
        printASCII(205, i, 0);
        printASCII(205, maxWidht-i, maxHeight);
        //        Sleep(1);
    }
    printASCII(200, 0,maxHeight);
    printASCII(188, maxWidht,maxHeight);
    for (int j = 1; j < maxHeight; j++) {
        printASCII(186, maxWidht, j);
        printASCII(186, 0, maxHeight-j);
        Sleep(30);
    }

    SetColorBlock(3,7);
    gotoxy(70, 40); printf("Press any key to next...");
    getch();
    system("cls");
}

void menuadmin() {
    int PosisiX = 115; // Posisi menu di layar
    int PosisiY = 10;

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 9; // Total jumlah menu
    int key;

    cleanKanan();
    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        gotoxy(PosisiX, PosisiY - 2); printf("---- Menu Pilihan ----\n");
        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) { // Tambahkan tanda ">>" di menu aktif
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("<<<");
            } else {
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("   ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + i - 1);
            switch (i) {
                case 1: printf("CRUD Karyawan"); break;
                case 2: printf("CRUD Produk"); break;
                case 3: printf("CRUD Aksesoris"); break;
                case 4: printf("CRUD Member"); break;
                case 5: printf("CRUD Supplier"); break;
                case 6: printf("CRUD Layanan"); break;
                case 7: printf("CRUD Garansi"); break;
                case 8: printf("CRUD Diskon"); break;
                case 9: printf("Exit"); break;
            }
        }

        // Membaca input keyboard
        key = getch();
        if (key == 224) { // Input arrow key di Windows
            key = getch();
            if (key == 72 && menu > 1) { // Arrow UP
                menu--;
            } else if (key == 80 && menu < totalMenu) { // Arrow DOWN
                menu++;
            }
        } else if (key == 13) { // Tombol Enter
            switch (menu) {
                case 1:
                    crudKaryawan(); break;
                case 2:
                    crudProduk(); break;
                case 3:
                    crudAksessoris(); break;
                case 4:
                    crudMember(); break;
                case 5:
                    crudSupplier(); break;
                case 6:
                    crudLayanan(); break;
                case 7:
                    crudGaransi(); break;
                case 8:
                    crudDiskon(); break;
                case 9:
                    gotoxy(PosisiX, PosisiY + totalMenu + 2);
                    printf("Program Terminated.\n");
                    return;
                default:
                    gotoxy(PosisiX, PosisiY + totalMenu + 2);
                    printf("Input tidak valid. Silakan coba lagi.\n");
            }
        }
    } while (1);
}

void menukasir() {
    int PosisiX = 115; // Posisi menu di layar
    int PosisiY = 10;

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 5; // Total jumlah menu
    int key;

    cleanKanan();
    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        gotoxy(PosisiX, PosisiY - 2); printf("---- Menu Pilihan ----\n");
        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) { // Tambahkan tanda ">>" di menu aktif
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("<<<");
            } else {
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("   ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + i - 1);
            switch (i) {
                case 1: printf("Transaksi Penjualan"); break;
                case 2: printf("Transaksi Pembelian"); break;
                case 3: printf("Transaksi Member"); break;
                case 4: printf("Transaksi Garansi"); break;
                case 5: printf("Exit"); break;
            }
        }

        // Membaca input keyboard
        key = getch();
        if (key == 224) { // Input arrow key di Windows
            key = getch();
            if (key == 72 && menu > 1) { // Arrow UP
                menu--;
            } else if (key == 80 && menu < totalMenu) { // Arrow DOWN
                menu++;
            }
        } else if (key == 13) { // Tombol Enter
            switch (menu) {
                case 1: CrudTransaksiPenjualan();
                    break;
                case 2: CrudTransaksiPembelian();
                    break;
                case 3: crudTrsMember();
                    break;
                case 4: CrudKlaimGaransi();
                    break;
                case 5:
                    gotoxy(PosisiX, PosisiY + totalMenu + 2);
                    printf("Program Terminated.\n");
                    return;
                default:
                    gotoxy(PosisiX, PosisiY + totalMenu + 2);
                    printf("Input tidak valid. Silakan coba lagi.\n");
            }
        }
    } while (1);
}

void menumanager() {
    int PosisiX = 115; // Posisi menu di layar
    int PosisiY = 10;

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 5; // Total jumlah menu
    int key;

    cleanKanan();
    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        gotoxy(PosisiX, PosisiY - 2); printf("---- Menu Pilihan ----\n");
        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) { // Tambahkan tanda ">>" di menu aktif
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("<<<");
            } else {
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("   ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + i - 1);
            switch (i) {
                case 1: printf("Laporan Penjualan"); break;
                case 2: printf("Laporan Pembelian"); break;
                case 3: printf("Laporan Member"); break;
                case 4: printf("Laporan Garansi"); break;
                case 5: printf("Exit"); break;
            }
        }

        // Membaca input keyboard
        key = getch();
        if (key == 224) { // Input arrow key di Windows
            key = getch();
            if (key == 72 && menu > 1) { // Arrow UP
                menu--;
            } else if (key == 80 && menu < totalMenu) { // Arrow DOWN
                menu++;
            }
        } else if (key == 13) { // Tombol Enter
            switch (menu) {
                case 1: break;
                case 2: break;
                case 3: break;
                case 4: break;
                case 5:
                    gotoxy(PosisiX, PosisiY + totalMenu + 2);
                printf("Program Terminated.\n");
                return;
                default:
                    gotoxy(PosisiX, PosisiY + totalMenu + 2);
                printf("Input tidak valid. Silakan coba lagi.\n");
            }
        }
    } while (1);
}

void login(int width, int height) {
    char inputUsername[50];
    char inputPassword[50];
    int loginAttempts = 3;

    while (loginAttempts > 0) {
        system("cls"); // Membersihkan layar
        frame();  // Menggambar border
        printKotak(23,4,130-1,10-2);

        int PosisiX = 130; // Menyesuaikan posisi teks di tengah
        int PosisiY = 10;

        gotoxy(PosisiX, PosisiY - 2); printf("===== LOGIN MENU =====");
        gotoxy(PosisiX, PosisiY);     printf("Username: ");
        gotoxy(PosisiX, PosisiY + 1); printf("Password: ");

        // Input username
        gotoxy(PosisiX + 10, PosisiY);
        scanf("%s", inputUsername);

        // Input password
        gotoxy(PosisiX + 10, PosisiY + 1);
        passwordPrivasi(inputPassword);

        // Verifikasi
        if (strcmp(inputUsername, usrnmAdmin) == 0 && strcmp(inputPassword, pwdAdmin) == 0) {
            showMessage("ATTENTION!", "Selamat Datang Admin!");
            menuadmin();
        } else if (strcmp(inputUsername, usrnmManager) == 0 && strcmp(inputPassword, pwdManager) == 0) {
            showMessage("ATTENTION!", "Selamat Datang Manager!");
            menumanager();
        } else if (strcmp(inputUsername, usrnmKasir) == 0 && strcmp(inputPassword, pwdKasir) == 0) {
            showMessage("ATTENTION!", "Selamat Datang Kasir!");
            menukasir();
        } else {
            loginAttempts--;
            gotoxy(PosisiX, PosisiY + 3);
            printf("Username atau password salah. %d percobaan tersisa.\n", loginAttempts);
            gotoxy(PosisiX, PosisiY + 5);
            printf("Tekan Enter untuk mencoba lagi...");
            getchar(); // Menunggu input sebelum mengulang
            getchar();
        }
    }

    gotoxy(width / 2 - 20, height - 3);
    printf("Anda telah kehabisan percobaan login. Program akan keluar.");
    getchar(); // Menunggu input sebelum keluar
    exit(0);
}


void apk() {
    mainPage();
    login(maxWidht, maxHeight);
}

#endif//menu_h