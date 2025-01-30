#ifndef CRUID_SUPPLIER_H
#define CRUID_SUPPLIER_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"

/*void inputSupplier(int n) {
    system("cls");
    templateUI();
    cleanKiri();

    char kodeSupplier[] = {"SPL"};
    int idTerakhir = 0;
    int batasKiri = 3;

    fileSupplier = fopen("../Database/dat/Supplier.dat", "ab+");
    if (fileSupplier == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(supplier.id, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColorBlock(3,7);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        // Generate ID otomatis
        snprintf(supplier.id, sizeof(supplier.id), "%s%i", kodeSupplier, i);

        // Menampilkan Teks Untuk Input
        SetColorBlock(3,7);
        gotoxy(batasKiri, 3); printf("=MASUKKAN DATA SUPPLIER===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 5); printf("ID Supplier");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", supplier.id);

        gotoxy(batasKiri, 8); printf("Nama Supplier");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", " ");

        gotoxy(batasKiri, 11); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", " ");

        gotoxy(batasKiri, 17); printf("No Telepon");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", " ");

        gotoxy(batasKiri, 20); printf("Alamat");
        gotoxy(batasKiri+50, 20); printf("| %-40s|", " ");

        gotoxy(batasKiri, 26); printf("Status");
        gotoxy(batasKiri+50, 26); printf("| %-40s|", "Aktif");

        gotoxy(57, 8); getteks(supplier.namaSpl, 50);

        gotoxy(57, 17); getteks(supplier.noTelp, 20);

        gotoxy(57, 20); getteks(supplier.alamat, 50);

        strcpy(supplier.status, "Aktif");

        fwrite(&supplier, sizeof(supplier), 1, fileSupplier);
    }
    fclose(fileSupplier);
}

void readdataSupplierALL() {
    cleanKiri();

    char id[] = "ID";
    char nama[] = "NAMA";
    char alamat[] = "ALAMAT";
    char noTelpn[] = "NO TELP";
        char status[] = "STATUS";

    int i = 1;
    int yTeks = 4;

    fileSupplier = fopen("../Database/dat/Supplier.dat", "rb");
    if (fileSupplier == NULL) {
        perror("Failed to open file");
        return;
    }

    printTable(3, 110, 1, 42);
    gotoxy(0, 3);
    SetColorBlock(3, 7);
    gotoxy(3, 2);
    printf(" %-8s   %-20s   %-15s   %-10s   %10s\n", id, nama, alamat, noTelpn, status);

    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        gotoxy(3, yTeks);
        printf(" %-8s   %-20s   %-15s   %-10s   %10s\n", supplier.id, supplier.namaSpl, supplier.alamat, supplier.noTelp, supplier.status);

        if (i % 40 == 0) {
            printf("\n--- Press any key to continue ---\n");
            getchar(); // Wait for user input
            cleanKiri();
            yTeks = 4; // Reset yTeks after clearing screen
            gotoxy(3, 2);
            printf(" %-8s   %-20s   %-15s   %-10s   %10s\n", id, nama, alamat, noTelpn, status);
        }
        i++;
        yTeks++;
    }

    fclose(fileKaryawan);
}

void CrudSupplier() {
    int PosisiX = 115; // Posisi menu di layar
    int PosisiY = 10;

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 5; // Total jumlah menu
    int key;
    int n;

    do {
        cleanKanan();
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
                case 1: printf("Tambah Data Supplier"); break;
                case 2: printf("Lihat Data Supplier"); break;
                case 3: printf("Ubah Data Supplier"); break;
                case 4: printf("Hapus Data Supplier"); break;
                case 5: printf("EXIT PROGRAM"); break;
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
                    AdminMenuTambah(); break;
                case 2:
                    readdataSupplierALL(); break;
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
}*/

/*void inputSupplier();
void viewSupplier();
void changeSuppplier();
void deleteSupplier();

void crudSupplier () {
    /* DECLARATION #1#
    int menu;

    /* ALGORITHM #1#
    system("cls");
    do {
    printf ("\n---- Menu Pilihan ----\n\n");
    printf ("1. Tambah data Supplier\n");
    printf ("2. Lihat data Supplier\n");
    printf ("3. Ubah data Supplier\n");
    printf ("4. Hapus data Supplier\n");
    printf ("5. EXIT PROGRAM\n");
    printf ("Pilih menu program:");
    scanf  ("%d", &menu);

        switch (menu) {
            case 1:inputSupplier(); break;
            case 2:viewSupplier(); break;
            case 3:changeSuppplier(); break;
            case 4:deleteSupplier();break;
            case 5:
                printf ("\nProgram Terminated\n");
                system("cls"); break;
            default: printf ("\nInvalid Input\n");
        }
    } while (menu != 5);
    getch();
}

void inputSupplier() {
    /* DECLARATION #1#

    /* ALGORITHM #1#
    printf ("\n---- Tambah Data Supplier ----\n\n");
    fileSupplier = fopen("Supplier.dat", "ab");
    printf("ID Supplier:");
    scanf ("%s", &supplier.idSpl);
    fflush(stdin);
    while (strcmp(supplier.idSpl,"selesai")!=0) {
        printf ("Nama Supplier :");
        gets(supplier.namaSpl);
        fflush(stdin);
        printf (" Alamat :");
        gets(supplier.alamat);
        fflush(stdin);
        printf (" No Telpon :");
        scanf ("%d", &supplier.noTelp);
        printf (" Status :");
        scanf ("%d", &supplier.status);
        fwrite (&supplier, sizeof(supplier), 1, fileSupplier);
        printf ("\n");
        printf ("ID Supplier:");  scanf("%s",&supplier.idSpl);  fflush(stdin);
    }
    printf("\n");
    fclose (fileSupplier);
}

void viewSupplier() {
    /* DECLARATION #1#

    /* ALGORITHM #1#
    fileSupplier = fopen("Supplier.dat", "rb");
    if (!fileSupplier) {
        printf ("File Not Found\n");
        return;
    }

    printf ("\n---- Lihat Data Supplier ----\n\n");
    while (fread(&supplier, sizeof(supplier), 1, fileSupplier)) {
        printf ("ID Supplier   :%s\n", supplier.idSpl);
        printf ("Nama Supplier :%s\n", supplier.namaSpl);
        printf ("Alamat        :%s\n", supplier.alamat);
        printf ("No Telpon     :%d\n", supplier.noTelp);
        printf ("Status        :%d\n", supplier.status);

        printf ("\n");
    }
    fclose (fileSupplier);
}


void changeSuppplier() {
    /* DECLARATION #1#
    Boolean found;
    char idTarget[10];

    /* ALGORITHM #1#
    printf ("\n---- Ubah Data Supplier ----\n\n");
    printf ("Masukkan ID Supplier:"); scanf ("%s", &idTarget);
    fileSupplier = fopen("Supplier.dat", "rb");
    tempSupplier = fopen("temp.dat", "wb");

    found = False;
    while (!found && !feof(fileSupplier)) {
        fread(&supplier, sizeof(supplier), 1, fileSupplier);
         if (strcmp(supplier.idSpl,idTarget)==0) {
            found = True;
        } else {
            fwrite(&supplier, sizeof(supplier), 1, tempSupplier);
        }
    }

    if (found) {
        printf ("Masukkan nama Supplier baru:"); scanf(" %[^\n]%*c", supplier.namaSpl);
        printf("Alamat :"); scanf ("%[^\n]%*c", supplier.alamat);
        printf (" No Telpon :"); scanf ("%d", &supplier.noTelp);
        printf ("Status :"); scanf ("%d", &supplier.status);
        fwrite(&supplier, sizeof(supplier), 1, tempSupplier);
        printf ("Data Berhasil Di Perbaharui\n");

        while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
            fread(&supplier, sizeof(supplier), 1, fileSupplier);
            fwrite(&supplier, sizeof(supplier), 1, tempSupplier);
        }
    } else {
        printf ("\nID %d Tidak Ditemukan Di Dalam File\n", idTarget);
    }
    fclose (fileSupplier);
    fclose (tempSupplier);

    tempSupplier = fopen("temp.dat", "rb");
    fileSupplier = fopen("Supplier.dat", "wb");
    while (!feof(tempSupplier)) {
        fread(&supplier, sizeof(supplier), 1, tempSupplier);
        fwrite(&supplier, sizeof(supplier), 1, fileSupplier);
    }
    fclose (tempSupplier);
    fclose (fileSupplier);

    remove ("Supplier.dat");
    rename("temp.dat", "Supplier.dat");
}


void deleteSupplier() {
    /* DECLARATION #1#
    Boolean found;
    char idTarget[10];

    /* ALGORITHM #1#
    printf ("\n---- Hapus data kendaraan ----\n\n");
    printf ("Masukkan ID Supplier:"); scanf ("%s", &idTarget);
    fileSupplier = fopen("Supplier.dat", "rb");
    tempSupplier = fopen("temp.dat", "wb");
    found = False;
    while (fread(&supplier, sizeof(supplier), 1, fileSupplier)) {
        if (strcmp(supplier.idSpl,idTarget)==0) {
            found = True;
            printf ("\nData Berhasil Di Hapus\n");
        } else {
            fwrite(&supplier, sizeof(supplier), 1, tempSupplier);
        }
    }

    if (!found) {
        printf ("Data Supplier tidak di temukan\n");
    }
    fclose (fileSupplier);
    fclose (tempSupplier);

    remove ("Supplier.dat");
    rename("temp.dat", "Supplier.dat");
}*/

void inputSupplier(int n) {
    system("cls");
    templateUI();
    cleanKiri();

    char kodeSupplier[] = {"SPL"};
    int idTerakhir = 0;
    int batasKiri = 3;

    fileSupplier = fopen("../Database/dat/Supplier.dat", "ab+");
    if (fileSupplier == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(supplier.idSpl, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColorBlock(3,7);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        // Generate ID otomatis
        snprintf(supplier.idSpl, sizeof(supplier.idSpl), "%s%i", kodeSupplier, i);

        // Menampilkan Teks Untuk Input
        SetColorBlock(3,7);
        gotoxy(batasKiri, 3); printf("=MASUKKAN DATA SUPPLIER===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 5); printf("ID Supplier");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", supplier.idSpl);


        gotoxy(batasKiri, 8); printf("Nama Supplier");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", " ");

        gotoxy(batasKiri, 11); printf("Alamat");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", " ");

        gotoxy(batasKiri, 14); printf("No Telepon");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", " ");

        gotoxy(batasKiri, 17); printf("Status");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", "Aktif");

        gotoxy(55, 8); getteks(supplier.namaSpl, 50);
        gotoxy(55, 11); getteks(supplier.alamat, 50);
        gotoxy(55, 14); getno(supplier.noTelp, 13);
        strcpy(supplier.status, "Aktif");

        fwrite(&supplier, sizeof(supplier), 1, fileSupplier);
    }
    fclose(fileSupplier);
}

void readdataSupplierALL() {
    cleanKiri();

    char id[] = "ID";
    char nama[] = "NAMA";
    char alamat[] = "ALAMAT";
    char noTelpn[] = "NO TELP";
    char status[] = "STATUS";

    int i = 1;
    int yTeks = 4;

    FILE *fileSupplier = fopen("../Database/dat/Supplier.dat", "rb");
    if (fileSupplier == NULL) {
        perror("Failed to open file");
        return;
    }

    printTable(3, 110, 1, 42);
    gotoxy(0, 3);
    SetColorBlock(3, 7);
    gotoxy(3, 2);
    printf(" %-8s   %-20s   %-20s   %-15s   %10s\n", id, nama, alamat, noTelpn, status);

    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        gotoxy(3, yTeks);
        printf(" %-8s   %-20s   %-20s   %-15s   %10s\n", supplier.idSpl, supplier.namaSpl, supplier.alamat, supplier.noTelp, supplier.status);

        if (i % 40 == 0) {
            printf("\n--- Press any key to continue ---\n");
            getchar(); // Wait for user input
            cleanKiri();
            yTeks = 4; // Reset yTeks after clearing screen
            gotoxy(3, 2);
            printf(" %-8s   %-20s   %-20s   %-15s   %10s\n", id, nama, alamat, noTelpn, status);
        }
        i++;
        yTeks++;
    }

    fclose(fileKaryawan);
}


void readDetailSupplier() {
    int batasKiri = 3;
    char idSplr[10];
    system("cls");
    retype:

    gotoxy(115, 2); SetColorBlock(3,7); printf("   %-35s", "W E L C O M E  A D M I N");
    gotoxy(115, 41); printf("%38c", ' ');
    gotoxy(127, 5); SetColorBlock(3,7);
    gotoxy(124, 11); printf("Masukkan ID Supplier");
    gotoxy(129, 15); printf("[        ]");

    readdataSupplierALL();
    frame();

    gotoxy(131, 15); getteks(idSplr, 4);
    cleanKiri();

    int i = 1;
    int found = 0;
    //Membuka file dengan mode rb
    fileSupplier = fopen("../Database/dat/Supplier.dat", "rb");

    gotoxy(0, 3); SetColorBlock(3,7);
    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        if (strcmp(idSplr, supplier.idSpl) == 0) {
            found = 1;
            break;
        }
        i++;
    }

    if (found == 1) {
        cleanKiri();
        gotoxy(batasKiri, 5); printf("ID Supplier");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", supplier.idSpl);

        gotoxy(batasKiri, 8); printf("Nama Supplier");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", supplier.namaSpl);

        gotoxy(batasKiri, 11); printf("Alamat");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", supplier.alamat);

        gotoxy(batasKiri, 14); printf("No Telepon");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", supplier.noTelp);

        gotoxy(batasKiri, 26); printf("Status");
        gotoxy(batasKiri+50, 26); printf("| %-40s|", karyawan.status);
    } else {
        showMessage("ALERT!", "ID Supplier tidak ditemukan");
        gotoxy(131, 15); printf("       ");
        goto retype;
    }
    gotoxy(123, 30); printf("Press ENTER to back...");
    getchar();
    //Menutup file setelah membaca
    fclose(fileSupplier);
    getchar();
}

void updateSupplier() {
    int found;
    found = 0;
    char No[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    readdataSupplierALL();
    gotoxy(115+8, 10); printf("ID Supplier : [   ]");
    gotoxy(row+17, 15); getteks(No, 6);

    //Membuka file asli dengan mode rb
    fileSupplier = fopen("../Database/dat/Supplier.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempSupplier = fopen("../Database/Temp/SupplierTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(No, supplier.idSpl) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&supplier, sizeof(supplier), 1, tempSupplier);
        }
    }

    //Proses lanjutan setelah data ditemukan
    if (found == 1) {
        cleanKiri();
        gotoxy(batasKiri, 3); printf("ID Supplier");
        gotoxy(batasKiri+50, 3); printf("| %-40s|", supplier.idSpl);

        gotoxy(batasKiri, 4); printf("Nama Supplier");
        gotoxy(batasKiri+50, 4); printf("| %-40s|", supplier.namaSpl);

        gotoxy(batasKiri, 5); printf("Alamat");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", supplier.alamat);

        gotoxy(batasKiri, 6); printf("No Telepon");
        gotoxy(batasKiri+50, 6); printf("| %-40d|", supplier.noTelp);

        gotoxy(batasKiri, 7); printf("Status");
        gotoxy(batasKiri+50, 7); printf("| %-40s|", supplier.status);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColorBlock(3,7);
        gotoxy(batasKiri, 13); printf("=MASUKKAN DATA YANG BARU===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 15); printf("ID Supplier");
        gotoxy(batasKiri+50, 15); printf("| %-40s|", supplier.idSpl);

        gotoxy(batasKiri, 17); printf("Nama Supplier");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", " ");

        gotoxy(batasKiri, 19); printf("Alamat");
        gotoxy(batasKiri+50, 19); printf("| %-40s|", " ");

        gotoxy(batasKiri, 21); printf("No Telepon");
        gotoxy(batasKiri+50, 21); printf("| %-40s|", " ");

        gotoxy(batasKiri, 23); printf("Status");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", " ");

        char namTemp[50];
        gotoxy(57, 17); getteks(namTemp, 50);

        char alamatTemp[10];
        gotoxy(57, 19); getteks(alamatTemp, 50);

        char tlpTemp[15];
        gotoxy(57, 21); getno(tlpTemp, 13);

        char statusTemp[10];
        gotoxy(57, 23); getteks(statusTemp, 10);

        fwrite(&supplier, sizeof(supplier), 1, tempSupplier);

        if (doaction("UBAH DATA") == 1) {
            strcpy(supplier.idSpl, No);
            strcpy(supplier.namaSpl, namTemp);
            strcpy(supplier.noTelp, tlpTemp);
            strcpy(supplier.alamat, alamatTemp);
            strcpy(supplier.status, statusTemp);
            fwrite(&supplier, sizeof(supplier), 1, fileSupplier);
            while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
                fwrite(&supplier, sizeof(supplier), 1, tempSupplier);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&supplier, sizeof(supplier), 1, tempSupplier);
            while (fread(&supplier, sizeof(supplier), 1, tempSupplier) == 1) {
                fwrite(&supplier, sizeof(supplier), 1, tempSupplier);
            }
        }
    } else {
        showMessage("ALERT!", "ID Supplier tidak ditemukan");
        gotoxy(row + 17, 15); printf("       ");
        goto retype;
    }
    fclose(fileSupplier);
    fclose(tempSupplier);
}

void deleteDataSupplier() {
    int found;
    found = 0;
    char No[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    readdataSupplierALL();
    gotoxy(115+8, 10); printf("ID Supplier : [   ]");
    gotoxy(row+17, 15); getteks(No, 6);

    //Membuka file asli dengan mode rb
    fileSupplier = fopen("../Database/dat/Supplier.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempSupplier = fopen("../Database/Temp/SupplierTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(No, supplier.idSpl) == 0) {
            cleanKiri();
            gotoxy(batasKiri, 5); printf("ID Supplier");
            gotoxy(batasKiri+50, 5); printf("| %-40s|", supplier.idSpl);

            gotoxy(batasKiri, 8); printf("Nama Supplier");
            gotoxy(batasKiri+50, 8); printf("| %-40s|", supplier.namaSpl);

            gotoxy(batasKiri, 11); printf("Alamat");
            gotoxy(batasKiri+50, 11); printf("| %-40s|", supplier.alamat);

            gotoxy(batasKiri, 14); printf("No Telepon");
            gotoxy(batasKiri+50, 14); printf("| %-40d|", supplier.noTelp);

            gotoxy(batasKiri, 14); printf("Status");
            gotoxy(batasKiri+50, 17); printf("| %-40s|", supplier.status);

            getchar();
            getchar();
            if (deleteData() == 1) {
                found = 1;
                showMessage("ATTENTION!!", "Data berhasil dihapus!");
                return;
            } else {
                found = 1;
                fwrite(&supplier, sizeof(supplier), 1, tempSupplier);
            }
        }
            //Jika tidak maka program akan menyalin data dari file asli ke data temporary
        else {
            fwrite(&supplier, sizeof(supplier), 1, tempSupplier);
        }
    }
    if (found == 0) {
        showMessage("ALERT!", "ID Supplier tidak ditemukan");
        gotoxy(row + 17, 15); printf("       ");
        goto retype;
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileSupplier);
    fclose(tempSupplier);
}

void MenuAddSupplier() {
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

    inputSupplier(n);
    system("cls");
    frame();
}

void menuReadSupplier() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    gotoxy(115, 2); SetColorBlock(3,7); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);
    gotoxy(127, 5); SetColorBlock(3,7);
    gotoxy(123, 35); printf("Press ENTER to next...");
    readdataSupplierALL();
    getch();
    if (lihatDetil() == 1) {
        readDetailSupplier();
    }
    system("cls");
    frame();
}

void menuUpdateSupplier() {
    //Memanggil prosedur pencarian id kota
    updateSupplier();
    //Membuka file asli dengan mode wb
    fileKaryawan = fopen("../Database/dat/Supplier.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempKaryawan = fopen("../Database/Temp/SupplierTemp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&supplier, sizeof(supplier), 1, tempSupplier)==1) {
        fwrite(&supplier, sizeof(supplier), 1, fileSupplier);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileSupplier);
    fclose(tempSupplier);
    system("cls");
    frame();
}

void menuDeleteSupplier() {
    //Memanggil prosedur pencarian id kota
    deleteDataSupplier();
    //Membuka file asli dengan mode wb
    fileKaryawan = fopen("../Database/dat/Supplier.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempKaryawan = fopen("../Database/Temp/SupplierTemp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&supplier, sizeof(supplier), 1, tempSupplier)==1) {
        fwrite(&supplier, sizeof(supplier), 1, fileSupplier);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileSupplier);
    fclose(tempSupplier);
    system("cls");
    frame();
}

void crudSupplier() {
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
                case 1: printf("Tambah Data Supplier"); break;
                case 2: printf("Lihat Data Supplier"); break;
                case 3: printf("Ubah Data Supplier"); break;
                case 4: printf("Hapus Data Supplier"); break;
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
                    MenuAddSupplier(); break;
                case 2:
                    menuReadSupplier(); break;
                case 3:
                    menuUpdateSupplier(); break;
                case 4:
                    menuDeleteSupplier(); break;
                case 5:
                    system("cls");
                    frame();
                    return;
                default:
                    gotoxy(PosisiX, PosisiY + totalMenu + 2);
                    printf("Input tidak valid. Silakan coba lagi.\n");
            }
        }
    } while (1);
}

#endif //CRUID_SUPPLIER_H
