#ifndef CRUD_LAYANAN_H
#define CRUD_LAYANAN_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"

void inputLayanan();
void viewLayanan();
void changeLayanan();
void deleteLayanan();

void crudLayanan () {
    /* DECLARATION */
    int menu;

    /* ALGORITHM */
    system("cls");
    do {
    printf ("\n---- Menu Pilihan ----\n\n");
    printf ("1. Tambah data Layanan\n");
    printf ("2. Lihat data Layanan\n");
    printf ("3. Ubah data Layanan\n");
    printf ("4. Hapus data Layanan\n");
    printf ("5. EXIT PROGRAM\n");
    printf ("Pilih menu program:");
    scanf  ("%d", &menu);

        switch (menu) {
            case 1:inputLayanan(); break;
            case 2:viewLayanan(); break;
            case 3:changeLayanan(); break;
            case 4:deleteLayanan();break;
            case 5:
                printf ("\nProgram Terminated\n");
                system("cls"); break;
            default: printf ("\nInvalid Input\n");
        }
    } while (menu != 5);
    getch();
}

void inputLayanan() {
    /* DECLARATION */

    /* ALGORITHM */
    printf ("\n---- Tambah Data Layanan ----\n\n");
    fileLayanan = fopen("Layanan.dat", "ab");
    printf("ID Layanan:");
    scanf ("%s", &layanan.idLyn);
    fflush(stdin);
    while (strcmp(layanan.idLyn,"selesai")!=0) {
        printf ("Jenis Layanan :");
        gets(layanan.jenisLyn);
        fflush(stdin);
        printf (" Harga :");
        scanf ("%s", &layanan.hargaLyn);
        printf (" Status :");
        scanf ("%d", &layanan.status);
        fwrite (&layanan, sizeof(layanan), 1, fileLayanan);
        printf ("\n");
        printf ("ID Layanan:");  scanf("%s",&layanan.idLyn);  fflush(stdin);
    }
    printf("\n");
    fclose (fileLayanan);
}

void viewLayanan() {
    /* DECLARATION */

    /* ALGORITHM */
    fileLayanan = fopen("Layanan.dat", "rb");
    if (!fileLayanan) {
        printf ("File Not Found\n");
        return;
    }

    printf ("\n---- Lihat Data Layanan ----\n\n");
    while (fread(&layanan, sizeof(layanan), 1, fileLayanan)) {
        printf ("ID Layanan    :%s\n", layanan.idLyn);
        printf ("Jenis Layanan :%s\n", layanan.jenisLyn);
        printf ("Harga         :%s\n", layanan.hargaLyn);
        printf ("Status        :%d\n", layanan.status);

        printf ("\n");
    }
    fclose (fileLayanan);
}


void changeLayanan() {
    /* DECLARATION */
    Boolean found;
    char idTarget[10];

    /* ALGORITHM */
    printf ("\n---- Ubah Data Layanan ----\n\n");
    printf ("Masukkan ID Layanan:"); scanf ("%s", &idTarget);
    fileLayanan = fopen("Layanan.dat", "rb");
    tempLayanan = fopen("temp.dat", "wb");

    found = False;
    while (!found && !feof(fileLayanan)) {
        fread(&layanan, sizeof(layanan), 1, fileLayanan);
         if (strcmp(layanan.idLyn,idTarget)==0) {
            found = True;
        } else {
            fwrite(&layanan, sizeof(layanan), 1, tempLayanan);
        }
    }

    if (found) {
        printf ("Masukkan nama Jenis Layanan baru:"); scanf(" %[^\n]%*c", layanan.jenisLyn);
        printf("Harga :"); scanf ("%s", layanan.hargaLyn);
        printf ("Status :"); scanf ("%d", &layanan.status);
        fwrite(&layanan, sizeof(layanan), 1, tempLayanan);
        printf ("Data Berhasil Di Perbaharui\n");

        while (fread(&layanan, sizeof(layanan), 1, fileLayanan) == 1) {
            fread(&layanan, sizeof(layanan), 1, fileLayanan);
            fwrite(&layanan, sizeof(layanan), 1, tempLayanan);
        }
    } else {
        printf ("\nID %s Tidak Ditemukan Di Dalam File\n", idTarget);
    }
    fclose (fileLayanan);
    fclose (tempLayanan);

    tempLayanan = fopen("temp.dat", "rb");
    fileLayanan = fopen("Layanan.dat", "wb");
    while (!feof(tempLayanan)) {
        fread(&layanan, sizeof(layanan), 1, tempLayanan);
        fwrite(&layanan, sizeof(layanan), 1, fileLayanan);
    }
    fclose (tempLayanan);
    fclose (fileLayanan);

    remove ("Layanan.dat");
    rename("temp.dat", "Layanan.dat");
}


void deleteLayanan() {
    /* DECLARATION */
    Boolean found;
    char idTarget[10];

    /* ALGORITHM */
    printf ("\n---- Hapus data Layanan ----\n\n");
    printf ("Masukkan ID Layanan:"); scanf ("%s", &idTarget);
    fileLayanan = fopen("Layanan.dat", "rb");
    tempLayanan = fopen("temp.dat", "wb");
    found = False;
    while (fread(&layanan, sizeof(layanan), 1, fileLayanan)) {
        if (strcmp(layanan.idLyn,idTarget)==0) {
            found = True;
            printf ("\nData Berhasil Di Hapus\n");
        } else {
            fwrite(&layanan, sizeof(layanan), 1, tempLayanan);
        }
    }

    if (!found) {
        printf ("Data Supplier tidak di temukan\n");
    }
    fclose (fileLayanan);
    fclose (tempLayanan);

    remove ("Layanan.dat");
    rename("temp.dat", "Layanan.dat");
}


#endif //CRUD_LAYANAN_H
