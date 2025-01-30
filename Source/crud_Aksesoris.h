#ifndef CRUD_AKSESORIS_H
#define CRUD_AKSESORIS_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"

void inputAksessoris();
void viewAksessoris();
void changeAksessoris();
void deleteAksessoris();

void crudAksessoris () {
    /* DECLARATION */
    int menu;

    /* ALGORITHM */
    system("cls");
    do {
    printf ("\n---- Menu Pilihan ----\n\n");
    printf ("1. Tambah data Aksessoris\n");
    printf ("2. Lihat data Aksessoris\n");
    printf ("3. Ubah data Aksessoris\n");
    printf ("4. Hapus data Aksessoris\n");
    printf ("5. EXIT PROGRAM\n");
    printf ("Pilih menu program:");
    scanf  ("%d", &menu);

        switch (menu) {
            case 1:inputAksessoris(); break;
            case 2:viewAksessoris(); break;
            case 3:changeAksessoris(); break;
            case 4:deleteAksessoris();break;
            case 5:
                printf ("\nProgram Terminated\n");
                system("cls"); break;
            default: printf ("\nInvalid Input\n");
        }
    } while (menu != 5);
    getch();
}

void inputAksessoris() {
    /* DECLARATION */

    /* ALGORITHM */
    printf ("\n---- Tambah Data Aksessoris ----\n\n");
    fileAksessoris = fopen("Aksessoris.dat", "ab");
    printf("ID Aksessoris:");
    scanf ("%s", &aksessoris.idAks);
    fflush(stdin);
    while (strcmp(aksessoris.idAks,"selesai")!=0) {
        printf ("Nama Aksessoris :");
        gets(aksessoris.namaAks);
        fflush(stdin);
        printf (" Harga :");
        scanf ("%s", &aksessoris.harga);
        printf (" Status :");
        scanf ("%d", &aksessoris.status);
        fwrite (&aksessoris, sizeof(aksessoris), 1, fileAksessoris);
        printf ("\n");
        printf ("ID Aksessoris:");  scanf("%s",&aksessoris.idAks);  fflush(stdin);
    }
    printf("\n");
    fclose (fileAksessoris);
}

void viewAksessoris() {
    /* DECLARATION */

    /* ALGORITHM */
    fileAksessoris = fopen("Aksessoris.dat", "rb");
    if (!fileAksessoris) {
        printf ("File Not Found\n");
        return;
    }

    printf ("\n---- Lihat Data Aksessoris ----\n\n");
    while (fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris)) {
        printf ("ID Aksessoris     :%s\n", aksessoris.idAks);
        printf ("Nama Aksessoris   :%s\n", aksessoris.namaAks);
        printf ("Harga             :%s\n", aksessoris.harga);
        printf ("Status            :%d\n", aksessoris.status);

        printf ("\n");
    }
    fclose (fileAksessoris);
}


void changeAksessoris() {
    /* DECLARATION */
    Boolean found;
    char idTarget[10];

    /* ALGORITHM */
    printf ("\n---- Ubah Data Aksessoris ----\n\n");
    printf ("Masukkan ID Aksessoris:"); scanf ("%s", &idTarget);
    fileAksessoris = fopen("Aksessoris.dat", "rb");
    tempAksessoris = fopen("temp.dat", "wb");

    found = False;
    while (!found && !feof(fileAksessoris)) {
        fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris);
         if (strcmp(aksessoris.idAks,idTarget)==0) {
            found = True;
        } else {
            fwrite(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
        }
    }

    if (found) {
        printf ("Masukkan nama Aksessoris baru:"); scanf(" %[^\n]%*c", aksessoris.namaAks);
        printf("Harga:"); scanf ("%s", aksessoris.harga);
        fwrite(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
        printf ("Data Berhasil Di Perbaharui\n");

        while (fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris) == 1) {
            fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris);
            fwrite(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
        }
    } else {
        printf ("\nID %s Tidak Ditemukan Di Dalam File\n", idTarget);
    }
    fclose (fileAksessoris);
    fclose (tempAksessoris);

    tempAksessoris = fopen("temp.dat", "rb");
    fileAksessoris = fopen("Aksessoris.dat", "wb");
    while (!feof(tempAksessoris)) {
        fread(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
        fwrite(&aksessoris, sizeof(aksessoris), 1, fileAksessoris);
    }
    fclose (tempAksessoris);
    fclose (fileAksessoris);

    remove ("Aksessoris.dat");
    rename("temp.dat", "Aksessoris.dat");
}

void deleteAksessoris() {
    /* DECLARATION */
    Boolean found;
    char idTarget[10];

    /* ALGORITHM */
    printf ("\n---- Hapus data Aksessoris ----\n\n");
    printf ("Masukkan ID Aksessoris:"); scanf ("%s", &idTarget);
    fileAksessoris = fopen("Aksessoris.dat", "rb");
    tempAksessoris = fopen("temp.dat", "wb");
    found = False;
    while (fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris)) {
        if (strcmp(aksessoris.idAks,idTarget)==0) {
            found = True;
            printf ("\nData Berhasil Di Hapus\n");
        } else {
            fwrite(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
        }
    }

    if (!found) {
        printf ("Data Aksessoris tidak di temukan\n");
    }
    fclose (fileAksessoris);
    fclose (tempAksessoris);

    remove ("Aksessoris.dat");
    rename("temp.dat", "Aksessoris.dat");
}

#endif //CRUD_AKSESORIS_H
