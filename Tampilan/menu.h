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
#include "../Laporan/Laporan.h"


void mainPage() {
    SetColor(colorMainText);
    Sleep(50);
    PrintFile("../TXT/Vielgora.txt", 62, 12);
    PrintFile("../TXT/Pojok kiri.txt", 2, 1);
    PrintFile("../TXT/Pojok kanan.txt", 165, 1);
    PrintFile("../TXT/Pojok bawahKna.txt", 165, 38);
    PrintFile("../TXT/Pojok bawahKri.txt", 2, 38);
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
        /*Sleep(30);*/
    }

    SetColor(text2);
    loading();
    system("cls");
}

void menuadmin() {
    int PosisiX = 135; // Posisi menu di layar
    int PosisiY = 10;
    int jarakMenu = 2; // Jarak antar menu (bisa disesuaikan)

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 9; // Total jumlah menu
    int key;

    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    cleanKanan();
    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        SetColor(colorHeadText);
        gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
        gotoxy(PosisiX - 5, 40); printf("%38c", space);
        SetColor(text2);

        for (int i = 1; i <= totalMenu; i++) {
            int posisiYMenu = PosisiY + (i - 1) * jarakMenu;
            if (i == menu) { // Tambahkan tanda "<<<" di menu aktif
                gotoxy(PosisiX + 22, posisiYMenu); printf("<<<");
            } else {
                gotoxy(PosisiX + 22, posisiYMenu); printf("   ");
            }

            // Tampilkan menu
            gotoxy(PosisiX + 3, posisiYMenu);
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
                    crudAksesoris(); break;
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
                    gotoxy(PosisiX, PosisiY + totalMenu * jarakMenu + 2);
                    printf("Program Terminated.\n");
                    return;
                default:
                    gotoxy(PosisiX, PosisiY + totalMenu * jarakMenu + 2);
                    printf("Input tidak valid. Silakan coba lagi.\n");
            }
        }
    } while (1);
}


void menukasir() {
    int PosisiX = 135; // Posisi menu di layar
    int PosisiY = 10;
    int jarakMenu = 2; // Jarak antar menu

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 5; // Total jumlah menu
    int key;

    char man[] = "W E L C O M E  K A S I R";
    char space = ' ';

    cleanKanan();
    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        SetColor(colorHeadText);
        gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
        gotoxy(PosisiX - 5, 40); printf("%38c", space);
        SetColor(text2);

        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) { // Tambahkan tanda "<<<" di menu aktif
                gotoxy(PosisiX + 22, PosisiY + (i - 1) * jarakMenu); printf("<<<");
            } else {
                gotoxy(PosisiX + 22, PosisiY + (i - 1) * jarakMenu); printf("   ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + (i - 1) * jarakMenu);
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
                case 1: TransaksiPenjualan();
                    break;
                case 2: CrudTransaksiPembelian();
                    break;
                case 3: crudTrsMember();
                    break;
                case 4: CrudKlaimGaransi();
                    break;
                case 5:
                    gotoxy(PosisiX, PosisiY + totalMenu * jarakMenu + 2);
                    printf("Program Terminated.\n");
                    return;
                default:
                    gotoxy(PosisiX, PosisiY + totalMenu * jarakMenu + 2);
                    printf("Input tidak valid. Silakan coba lagi.\n");
            }
        }
    } while (1);
}

void menumanager() {
    int PosisiX = 135; // Posisi menu di layar
    int PosisiY = 10;
    int jarakMenu = 2; // Jarak antar menu

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 5; // Total jumlah menu
    int key;

    char man[] = "W E L C O M E  M A N A G E R";
    char space = ' ';

    cleanKanan();
    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        SetColor(colorHeadText);
        gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
        gotoxy(PosisiX - 5, 40); printf("%38c", space);
        SetColor(text2);

        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) { // Tambahkan tanda "<<<" di menu aktif
                gotoxy(PosisiX + 22, PosisiY + (i - 1) * jarakMenu); printf("<<<");
            } else {
                gotoxy(PosisiX + 22, PosisiY + (i - 1) * jarakMenu); printf("   ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + (i - 1) * jarakMenu);
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
                case 1:
                    laporanTransaksiPenjualan();
                    break;
                case 2:
                    laporanTransaksiPembelian();
                    break;
                case 3:
                    laporanMember();
                    break;
                case 4:
                    laporanGaransi();
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

void login(int width, int height) {
    char inputUsername[50];
    char inputPassword[50];
    int loginAttempts = 3;

    while (loginAttempts > 0) {
        system("cls"); // Membersihkan layar
        frame();  // Menggambar border
        printKotak(23,4,137,8);

        int PosisiX = 139; // Menyesuaikan posisi teks di tengah
        int PosisiY = 10;

        SetColor(text2);
        gotoxy(PosisiX, PosisiY - 2); printf("====== LOGIN ======");
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
            showMessage("ATTENTION", "Username Atau Password Salah");
            getchar(); // Menunggu input sebelum mengulang
        }
    }

    showMessage("Program Terminated", "Program Terminated");
    exit(0);
}


void apk() {
    mainPage();
    login(maxWidht, maxHeight);
}

#endif//menu_h