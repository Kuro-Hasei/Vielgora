#ifndef CRUD_GARANSI_H
#define CRUD_GARANSI_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"

/*void inputGaransi();
void viewGaransi();
void changeGaransi();
void deleteGaransi();

void crudGaransi () {
    /* DECLARATION #1#
    int menu;

    /* ALGORITHM #1#
    system("cls");
    do {
    printf ("\n---- Menu Garansi ----\n\n");
    printf ("1. Tambah data Garansi\n");
    printf ("2. Lihat data Garansi\n");
    printf ("3. Ubah data Garansi\n");
    printf ("4. Hapus data Garansi\n");
    printf ("5. EXIT PROGRAM\n");
    printf ("Pilih menu program:");
    scanf  ("%d", &menu);

        switch (menu) {
            case 1:inputGaransi(); break;
            case 2:viewGaransi(); break;
            case 3:changeGaransi(); break;
            case 4:deleteGaransi();break;
            case 5:
                printf ("\nProgram Terminated\n");
                system("cls"); break;
            default: printf ("\nInvalid Input\n");
        }
    } while (menu != 5);
    getch();
}

void inputGaransi() {
    /* DECLARATION #1#

    /* ALGORITHM #1#
    printf ("\n---- Tambah Data Garansi ----\n\n");
    fileGaransi = fopen("Garansi.dat", "ab");
    printf("ID Garansi:");
    scanf ("%s", &garansi.idGrns);
    fflush(stdin);
    while (strcmp(garansi.idGrns,"selesai")!=0) {
        printf ("Jenis Garansi :");
        gets(garansi.jenisGrns);
        fflush(stdin);
        printf (" Durasi :");
        gets(garansi.durasi);
        fflush(stdin);
        printf (" Ketentuan :");
        gets(garansi.ketentuan);
        fflush(stdin);
        printf (" Status :");
        scanf ("%d", &garansi.status);
        fwrite (&garansi, sizeof(garansi), 1, fileGaransi);
        printf ("\n");
        printf ("ID Garansi:");  scanf("%s",&garansi.idGrns);  fflush(stdin);
    }
    printf("\n");
    fclose (fileGaransi);
}

void viewGaransi() {
    /* DECLARATION #1#

    /* ALGORITHM #1#
    fileGaransi = fopen("Garansi.dat", "rb");
    if (!fileGaransi) {
        printf ("File Not Found\n");
        return;
    }

    printf ("\n---- Lihat Data Garansi ----\n\n");
    while (fread(&garansi, sizeof(garansi), 1, fileGaransi)) {
        printf ("ID Garansi        :%s\n", garansi.idGrns);
        printf ("Jenis Garansi     :%s\n", garansi.jenisGrns);
        printf ("Durasi            :%s\n", garansi.durasi);
        printf("Ketentuan          :%s\n", garansi.ketentuan);
        printf ("Status            :%d\n", garansi.status);

        printf ("\n");
    }
    fclose (fileGaransi);
}


void changeGaransi() {
    /* DECLARATION #1#
    Boolean found;
    char idTarget[10];

    /* ALGORITHM #1#
    printf ("\n---- Ubah Data Garansi ----\n\n");
    printf ("Masukkan ID Garansi:"); scanf ("%s", &idTarget);
    fileGaransi = fopen("Garansi.dat", "rb");
    tempGaransi = fopen("temp.dat", "wb");

    found = False;
    while (!found && !feof(fileGaransi)) {
        fread(&garansi, sizeof(garansi), 1, fileGaransi);
         if (strcmp(garansi.idGrns,idTarget)==0) {
            found = True;
        } else {
            fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
        }
    }

    if (found) {
        printf ("Masukkan Jenis Garansi baru:"); scanf(" %[^\n]%*c", garansi.jenisGrns);
        printf("Durasi:"); scanf ("%[^\n]%*c", garansi.durasi);
        printf("ketentuan:"); scanf ("%[^\n]%*c", garansi.ketentuan);
        fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
        printf ("Data Berhasil Di Perbaharui\n");

        while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
            fread(&garansi, sizeof(garansi), 1, fileGaransi);
            fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
        }
    } else {
        printf ("\nID %s Tidak Ditemukan Di Dalam File\n", idTarget);
    }
    fclose (fileGaransi);
    fclose (tempGaransi);

    tempGaransi = fopen("temp.dat", "rb");
    fileGaransi = fopen("Garansi.dat", "wb");
    while (!feof(tempGaransi)) {
        fread(&garansi, sizeof(garansi), 1, tempGaransi);
        fwrite(&garansi, sizeof(garansi), 1, fileGaransi);
    }
    fclose (tempGaransi);
    fclose (fileGaransi);

    remove ("Garansi.dat");
    rename("temp.dat", "Garansi.dat");
}

void deleteGaransi() {
    /* DECLARATION #1#
    Boolean found;
    char idTarget[10];

    /* ALGORITHM #1#
    printf ("\n---- Hapus data Garansi ----\n\n");
    printf ("Masukkan ID Garansi:"); scanf ("%s", &idTarget);
    fileGaransi = fopen("Garansi.dat", "rb");
    tempGaransi = fopen("temp.dat", "wb");
    found = False;
    while (fread(&garansi, sizeof(garansi), 1, fileGaransi)) {
        if (strcmp(garansi.idGrns,idTarget)==0) {
            found = True;
            printf ("\nData Berhasil Di Hapus\n");
        } else {
            fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
        }
    }

    if (!found) {
        printf ("Data Garansi tidak di temukan\n");
    }
    fclose (fileGaransi);
    fclose (tempGaransi);

    remove ("Garansi.dat");
    rename("temp.dat", "Garansi.dat");
}*/

void inputGaransi(int n) {
    system("cls");
    templateUI();
    cleanKiri();

    char kodeGaransi[] = {"GRNS"};
    int idTerakhir = 0;
    int batasKiri = 3;

    fileGaransi = fopen("../Database/dat/Garansi.dat", "ab+");
    if (fileGaransi == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(garansi.idGrns, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColorBlock(3,7);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        // Generate ID otomatis
        snprintf(garansi.idGrns, sizeof(garansi.idGrns), "%s%i", kodeGaransi, i);

        // Menampilkan Teks Untuk Input
        SetColorBlock(3,7);
        gotoxy(batasKiri, 3); printf("=== [ MASUKKAN DATA GARANSI ] ===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 5); printf("ID Garansi");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", garansi.idGrns);

        gotoxy(batasKiri, 8); printf("Jenis Garansi");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", " ");

        gotoxy(batasKiri, 11); printf("Durasi");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", " ");

        gotoxy(batasKiri, 14); printf("Ketentuan");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", " ");

        gotoxy(batasKiri, 17); printf("Status");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", "Aktif");

        gotoxy(55, 8); getteks(garansi.jenisGrns, 50);

        gotoxy(55, 11); getteks(garansi.durasi, 50);

        gotoxy(55, 14); getteks(garansi.ketentuan, 50);

        strcpy(garansi.status, "Aktif");

        fwrite(&garansi, sizeof(garansi), 1, fileGaransi);
    }
    fclose(fileGaransi);
}

void readdataGaransiINJS() {
    cleanKiri();

    char id[] = "ID";
    char jenis[] = "JENIS";
    char durasi[] = "DURASI";
    char ketentuan[] = "KETENTUAN";
    char status[] = "STATUS";

    int i = 1;
    int yTeks = 4;

    fileGaransi = fopen("../Database/dat/Garansi.dat", "rb");
    if (fileGaransi == NULL) {
        perror("Failed to open file");
        return;
    }

    printTable(3, 110, 1, 42);
    gotoxy(0, 3);
    SetColorBlock(3, 7);
    gotoxy(3, 2);
    printf(" %-8s   %-20s   %-15s   %15s   %-10s\n", id, jenis, durasi, ketentuan, status);

    while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
        gotoxy(3, yTeks);
        printf(" %-8s   %-20s   %-15s  %15s  %-10s\n", garansi.idGrns, garansi.jenisGrns, garansi.durasi, garansi.ketentuan,  garansi.status);

        if (i % 40 == 0) {
            printf("\n--- Press any key to continue ---\n");
            getchar(); // Wait for user input
            cleanKiri();
            yTeks = 4; // Reset yTeks after clearing screen
            gotoxy(3, 2);
            printf(" %-8s   %-20s   %-15s  %15s  %-10s\n", garansi.idGrns, garansi.jenisGrns, garansi.durasi, garansi.ketentuan,  garansi.status);
        }
        i++;
        yTeks++;
    }

    fclose(fileGaransi);
}

void readDetailGaransi() {
    int batasKiri = 3;
    char idGrns[10];
    system("cls");
    retype:

    gotoxy(115, 2); SetColorBlock(3,7); printf("   %-35s", "W E L C O M E  A D M I N");
    gotoxy(115, 41); printf("%38c", ' ');
    gotoxy(127, 5); SetColorBlock(3,7);
    gotoxy(124, 11); printf("Masukkan ID Garansi");
    gotoxy(129, 15); printf("[        ]");

    readdataGaransiINJS();
    frame();

    gotoxy(131, 15); getteks(idGrns, 6);
    cleanKiri();

    int i = 1;
    int found = 0;
    //Membuka file dengan mode rb
    fileGaransi = fopen("../Database/dat/Garansi.dat", "rb");

    gotoxy(0, 3); SetColorBlock(3,7);
    while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
        if (strcmp(idGrns, garansi.idGrns) == 0) {
            found = 1;
            break;
        }
        i++;
    }

    if (found == 1) {
        cleanKiri();
        gotoxy(batasKiri, 5); printf("ID Garansi");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", garansi.idGrns);

        gotoxy(batasKiri, 8); printf("Nama garansi");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", garansi.jenisGrns);

        gotoxy(batasKiri, 11); printf("Durasi");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", garansi.durasi);

        gotoxy(batasKiri, 14); printf("Ketentuan");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", garansi.ketentuan);

        gotoxy(batasKiri, 17); printf("Status");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", garansi.status);
    } else {
        showMessage("ALERT!", "ID Garansi tidak ditemukan");
        gotoxy(131, 15); printf("       ");
        goto retype;
    }
    gotoxy(123, 30); printf("Press ENTER to back...");
    getchar();
    //Menutup file setelah membaca
    fclose(fileGaransi);
    getchar();
}

void updateGaransi() {
    int found;
    found = 0;
    char No[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("ID Garansi : [   ]");
    gotoxy(row+17, 15); getteks(No, 6);

    //Membuka file asli dengan mode rb
    fileGaransi = fopen("../Database/dat/Garansi.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempGaransi = fopen("../Database/Temp/GaransiTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(No, garansi.idGrns) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
        }
    }

    //Proses lanjutan setelah data ditemukan
    if (found == 1) {
        cleanKiri();
        gotoxy(batasKiri, 3); printf("ID Garansi");
        gotoxy(batasKiri+50, 3); printf("| %-40s|", garansi.idGrns);

        gotoxy(batasKiri, 4); printf("Nama Garansi");
        gotoxy(batasKiri+50, 4); printf("| %-40s|", garansi.jenisGrns);

        gotoxy(batasKiri, 5); printf("Durasi");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", garansi.durasi);

        gotoxy(batasKiri, 6); printf("Ketentuan");
        gotoxy(batasKiri+50, 6); printf("| %-40s|", garansi.ketentuan);

        gotoxy(batasKiri, 7); printf("Status");
        gotoxy(batasKiri+50, 7); printf("| %-40s|", garansi.status);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColorBlock(3,7);
        gotoxy(batasKiri, 13); printf("=MASUKKAN DATA YANG BARU===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 15); printf("ID Garansi");
        gotoxy(batasKiri+50, 15); printf("| %-40s|", garansi.idGrns);

        gotoxy(batasKiri, 17); printf("Jenis Garansi");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", " ");

        gotoxy(batasKiri, 19); printf("Durasi");
        gotoxy(batasKiri+50, 19); printf("| %-40s|", " ");

        gotoxy(batasKiri, 21); printf("Ketentuan");
        gotoxy(batasKiri+50, 21); printf("| %-40s|", " ");

        gotoxy(batasKiri, 23); printf("Status");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", " ");

        char namTemp[50];
        gotoxy(57, 17); getteks(namTemp, 50);

        char durasiTemp[10];
        gotoxy(57, 19); getteks(durasiTemp, 50);

        char ketentuanTemp[10];
            gotoxy(57, 21); getteks(ketentuanTemp, 35);

        char statusTemp[10];
        gotoxy(57, 23); getteks(statusTemp, 10);

        if (doaction("UBAH DATA") == 1) {
            strcpy(garansi.idGrns, No);
            strcpy(garansi.jenisGrns, namTemp);
            strcpy(garansi.durasi, durasiTemp);
            strcpy(garansi.ketentuan, ketentuanTemp);
            strcpy(garansi.status, statusTemp);
            fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
            while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
                fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
            while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
                fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
            }
        }

    } else {
        showMessage("ALERT!", "ID Garansi tidak ditemukan");
        gotoxy(row + 17, 15); printf("       ");
        goto retype;
    }
    fclose(fileGaransi);
    fclose(tempGaransi);
}

void deleteDataGaransi() {
    int found;
    found = 0;
    char No[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("ID Garansi : [   ]");
    gotoxy(row+17, 15); getteks(No, 6);

    //Membuka file asli dengan mode rb
    fileGaransi = fopen("../Database/dat/Garansi.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempGaransi = fopen("../Database/Temp/GaransiTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(No, garansi.idGrns) == 0) {
            cleanKiri();
            gotoxy(batasKiri, 5); printf("ID Garansi");
            gotoxy(batasKiri+50, 5); printf("| %-40s|", garansi.idGrns);

            gotoxy(batasKiri, 8); printf("Nama Garansi");
            gotoxy(batasKiri+50, 8); printf("| %-40s|", garansi.jenisGrns);

            gotoxy(batasKiri, 11); printf("Durasi");
            gotoxy(batasKiri+50, 11); printf("| %-40s|", garansi.durasi);

            gotoxy(batasKiri, 14); printf("Ketentuan");
            gotoxy(batasKiri+50, 14); printf("| %-40s|", garansi.ketentuan);

            gotoxy(batasKiri, 17); printf("Status");
            gotoxy(batasKiri+50, 17); printf("| %-40s|", garansi.status);
            getchar();
            getchar();
            if (deleteData() == 1) {
                found = 1;
                showMessage("ATTENTION!!", "Data berhasil dihapus!");
                continue;
            } else {
                found = 1;
                fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
            }
        }
            //Jika tidak maka program akan menyalin data dari file asli ke data temporary
        else {
            fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
        }
    }
    if (found == 0) {
        showMessage("ALERT!", "ID Garansi tidak ditemukan");
        gotoxy(row + 17, 15); printf("       ");
        goto retype;
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileGaransi);
    fclose(tempGaransi);
}

void MenuAddGaransi() {
    system("cls");
    frame();

    int n;
    char Admin[] = "W E L C O M E  A D M I N";
    char space = " ";
    gotoxy(115, 2); SetColorBlock(3,7);printf(" %-35s", Admin);
    gotoxy(115, 41); printf("%38c", space);
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("Banyaknya data : [   ]");
    gotoxy(115+27, 10); getnum(&n, 1);

    inputGaransi(n);
    system("cls");
    frame();
}

void menuReadGaransi() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    gotoxy(115, 2); SetColorBlock(3,7); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);
    gotoxy(127, 5); SetColorBlock(3,7);
    gotoxy(123, 35); printf("Press ENTER to next...");
    readdataGaransiINJS();
    getch();
    if (lihatDetil() == 1) {
        readDetailGaransi();
    }
}

void menuUpdateGaransi() {
    //Memanggil prosedur pencarian id kota
    updateGaransi();
    //Membuka file asli dengan mode wb
    fileGaransi = fopen("../Database/dat/Garansi.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempGaransi = fopen("../Database/Temp/GaransiTemp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&garansi, sizeof(garansi), 1, tempGaransi) == 1) {
        fwrite(&garansi, sizeof(garansi), 1, fileGaransi);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileGaransi);
    fclose(tempGaransi);
}

void menuDeleteGaransi() {
    //Memanggil prosedur pencarian id kota
    deleteDataGaransi();
    //Membuka file asli dengan mode wb
    fileGaransi = fopen("../Database/dat/Garansi.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempGaransi = fopen("../Database/Temp/GaransiTemp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&garansi, sizeof(garansi), 1, tempGaransi)==1) {
        fwrite(&garansi, sizeof(garansi), 1, fileGaransi);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileGaransi);
    fclose(tempGaransi);
}

void crudGaransi() {
    int PosisiX = 115; // Posisi menu di layar
    int PosisiY = 10;

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 5; // Total jumlah menu
    int key;

    do {
        system("cls");
        frame();

        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        gotoxy(PosisiX, PosisiY - 2); printf("---- Menu Pilihan ----\n");
        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) { // Tambahkan tanda ">>" di menu aktif
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("<<<");
            } else {
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("  ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + i - 1);
            switch (i) {
                case 1: printf("Tambah Data Garansi"); break;
                case 2: printf("Lihat Data Garansi"); break;
                case 3: printf("Ubah Data Garansi"); break;
                case 4: printf("Hapus Data Garansi"); break;
                case 5: printf("EXIT PROGRAM"); break;
                default: break;
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
                    cleanKanan();
                    MenuAddGaransi(); break;
                case 2:
                    menuReadGaransi(); break;
                case 3:
                    cleanKanan();
                    menuUpdateGaransi(); break;
                case 4:
                    menuDeleteGaransi(); break;
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

#endif //CRUD_GARANSI_H
