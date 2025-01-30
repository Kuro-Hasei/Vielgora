#ifndef CRUD_DISKON_H
#define CRUD_DISKON_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"

void inputDiskon1(int n) {
    system("cls");
    templateUI();
    cleanKiri();

    char kodeDiskon[] = {"DSK"};
    int idTerakhir = 0;
    int batasKiri = 3;

    fileDiskon = fopen("../Database/dat/Diskon.dat", "ab+");
    if (fileDiskon == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&diskon, sizeof(diskon), 1, fileDiskon) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(diskon.idDsk, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColorBlock(3,7);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        memset(&diskon, 0, sizeof(diskon));
        // Generate ID otomatis
        snprintf(diskon.idDsk, sizeof(diskon.idDsk), "%s%i", kodeDiskon, i);

        // Menampilkan Teks Untuk Input
        SetColorBlock(3,7);
        gotoxy(batasKiri, 3); printf("=== [ MASUKKAN DATA PRODUK ] ===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 5); printf("ID Diskon");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", diskon.idDsk);

        gotoxy(batasKiri, 8); printf("Jenis Diskon");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", " ");

        gotoxy(batasKiri, 11); printf("Persentase");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", " ");

        gotoxy(batasKiri, 14); printf("Batas Point");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", " ");

        gotoxy(55, 8); getteks(diskon.jenisDsk, 20);

        gotoxy(55, 11); getteks(diskon.persentase, 10);

        gotoxy(55, 14); getnum(&diskon.batasPoin, 5);

        fwrite(&diskon, sizeof(diskon), 1, fileDiskon);
    }
    fclose(fileDiskon);
}

void readdataDiskon2() {
    cleanKiri();

    char id[] = "ID";
    char jenis[] = "JENIS";
    char persentase[] = "PERSENTASE";
    char batasPoin[] = "BATAS POIN";
    int i = 1;
    int yTeks = 4;

    fileDiskon = fopen("../Database/dat/Diskon.dat", "rb");
    if (fileDiskon == NULL) {
        perror("Failed to open file");
        return;
    }

    printTable(3, 110, 1, 42);
    gotoxy(0, 3);
    SetColorBlock(3, 7);
    gotoxy(3, 2);
    printf(" %-10s   %-20s   %-30s   %-20s\n", id, jenis, persentase, batasPoin);

    while (fread(&diskon, sizeof(diskon), 1, fileDiskon) == 1) {
        gotoxy(3, yTeks);
        printf(" %-10s   %-20s   %-30s   %-20d\n", diskon.idDsk, diskon.jenisDsk, diskon.persentase, diskon.batasPoin);
        if (i % 40 == 0) {
            printf("\n--- Press any key to continue ---\n");
            getchar(); // Wait for user input
            cleanKiri();
            yTeks = 4; // Reset yTeks after clearing screen
            gotoxy(3, 2);
            printf(" %-10s   %-20s   %-30s   %-20s\n", id, jenis, persentase, batasPoin);
        }
        i++;
        yTeks++;
    }
    fclose(fileDiskon);
}

void updateDiskon() {
    int found;
    found = 0;
    char idDiskon[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    readdataDiskon2();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("ID Produk : [      ]");
    gotoxy(115+22, 10); getteks(idDiskon, 4);
    /*gotoxy(115+8, 10); printf("ID Karyawan : [   ]");
    gotoxy(row+17, 15); getteks(No, 6);*/

    //Membuka file asli dengan mode rb
    fileDiskon = fopen("../Database/dat/Diskon.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempDiskon = fopen("../Database/Temp/Temp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&diskon, sizeof(diskon), 1, fileDiskon) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idDiskon, diskon.idDsk) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&diskon, sizeof(diskon), 1, tempDiskon);
        }
    }

    //Proses lanjutan setelah data ditemukan
    if (found == 1) {
        cleanKiri();
        gotoxy(batasKiri, 3); printf("ID Diskon");
        gotoxy(batasKiri+50, 3); printf("| %-40s|", diskon.idDsk);

        gotoxy(batasKiri, 4); printf("Jenis Diskon");
        gotoxy(batasKiri+50, 4); printf("| %-40s|", diskon.jenisDsk);

        gotoxy(batasKiri, 5); printf("Persentase");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", diskon.persentase);

        gotoxy(batasKiri, 6); printf("Batas Point");
        gotoxy(batasKiri+50, 6); printf("| %-40d|", diskon.batasPoin);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColorBlock(3,7);
        gotoxy(batasKiri, 13); printf("=== [ MASUKKAN DATA YANG BARU ] ===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 15); printf("ID Diskon");
        gotoxy(batasKiri+50, 15); printf("| %-40s|", diskon.idDsk);

        gotoxy(batasKiri, 18); printf("Jenis Diskon");
        gotoxy(batasKiri+50, 18); printf("| %-40s|", diskon.jenisDsk);

        gotoxy(batasKiri, 21); printf("Persentase");
        gotoxy(batasKiri+50, 21); printf("| %-40s|", " ");

        gotoxy(batasKiri, 24); printf("Batas Point");
        gotoxy(batasKiri+50, 24); printf("| %-40s|", " ");

        char persentase[10];
        gotoxy(57, 21); getteks(persentase, 10);

        int batasPoint;
        gotoxy(57, 24); getnum(&batasPoint, 5);

        if (doaction("UBAH DATA") == 1) {
            strcpy(diskon.idDsk, idDiskon);
            strcpy(diskon.persentase, persentase);
            diskon.batasPoin = batasPoint;

            fwrite(&diskon, sizeof(diskon), 1, tempDiskon);
            while (fread(&diskon, sizeof(diskon), 1, fileDiskon) == 1) {
                fwrite(&diskon, sizeof(diskon), 1, tempDiskon);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&diskon, sizeof(diskon), 1, tempDiskon);
            while (fread(&diskon, sizeof(diskon), 1, fileDiskon) == 1) {
                fwrite(&diskon, sizeof(diskon), 1, tempDiskon);
            }
        }
    } else {
        showMessage("ALERT!", "ID Diskon tidak ditemukan");
        gotoxy(115+22, 10); printf("%s", "    ");
        goto retype;
    }
    fclose(fileDiskon);
    fclose(tempDiskon);
}

void deleteDataDiskon() {
    int found;
    found = 0;
    char idDiskon[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    readdataDiskon2();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("ID Diskon : [      ]");
    gotoxy(115+22, 10); getteks(idDiskon, 4);

    //Membuka file asli dengan mode rb
    fileDiskon = fopen("../Database/dat/Diskon.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempDiskon = fopen("../Database/Temp/Temp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&diskon, sizeof(diskon), 1, fileDiskon) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idDiskon, diskon.idDsk) == 0) {
            cleanKiri();
            gotoxy(batasKiri, 5); printf("ID Diskon");
            gotoxy(batasKiri+50, 5); printf("| %-40s|", diskon.idDsk);

            gotoxy(batasKiri, 8); printf("Jenis Diskon");
            gotoxy(batasKiri+50, 8); printf("| %-40s|", diskon.jenisDsk);

            gotoxy(batasKiri, 11); printf("Persentase");
            gotoxy(batasKiri+50, 11); printf("| %-40s|", diskon.persentase);

            gotoxy(batasKiri, 14); printf("Batas Point");
            gotoxy(batasKiri+50, 14); printf("| %-40d|", diskon.batasPoin);
            getchar(); getchar();

            if (deleteData() == 1) {
                found = 1;
                showMessage("ATTENTION!!", "Data berhasil dihapus!");
                continue;
            } else {
                found = 1;
                fwrite(&diskon, sizeof(diskon), 1, tempDiskon);
            }
        }
            //Jika tidak maka program akan menyalin data dari file asli ke data temporary
        else {
            fwrite(&diskon, sizeof(diskon), 1, tempDiskon);
        }
    }
    if (found == 0) {
        showMessage("ALERT!", "ID Diskon tidak ditemukan");
        gotoxy(115+22, 10); printf("%s", "    ");
        goto retype;
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileDiskon);
    fclose(tempDiskon);
}

void menuAddDiskon() {
    system("cls");
    frame();

    int n;
    char Admin[] = "W E L C O M E  A D M I N";
    char space = " ";
    gotoxy(115, 2); SetColorBlock(3,7); printf(" %-35s", Admin);
    gotoxy(115, 41); printf("%38c", space);
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("Banyaknya data : [   ]");
    gotoxy(115+27, 10); scanf("%d", &n);

    inputDiskon1(n);
    system("cls");
    frame();
}

void menuReadDiskon() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    gotoxy(115, 2); SetColorBlock(3,7); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);
    gotoxy(127, 5); SetColorBlock(3,7);
    gotoxy(123, 35); printf("Press ENTER to next...");
    readdataDiskon2();
    getch();
    /*if (lihatDetil() == 1) {
        readDetailKaryawan();
    }*/
    system("cls");
    frame();
}

void menuUpdateDiskon() {
    //Memanggil prosedur pencarian id kota
    updateDiskon();
    //Membuka file asli dengan mode wb
    fileDiskon = fopen("../Database/dat/Diskon.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempDiskon = fopen("../Database/Temp/Temp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&diskon, sizeof(diskon), 1, tempDiskon) == 1) {
        fwrite(&diskon, sizeof(diskon), 1, fileDiskon);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileDiskon);
    fclose(tempDiskon);
    system("cls");
    frame();
}

void menuDeleteDiskon() {
    //Memanggil prosedur pencarian id kota
    deleteDataDiskon();
    //Membuka file asli dengan mode wb
    fileDiskon = fopen("../Database/dat/Diskon.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempDiskon = fopen("../Database/Temp/Temp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&diskon, sizeof(diskon), 1, tempDiskon)==1) {
        fwrite(&diskon, sizeof(diskon), 1, fileDiskon);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileDiskon);
    fclose(tempDiskon);
    system("cls");
    frame();
}

// CRUD Menu
void crudDiskon() {
    int PosisiX = 115; // Posisi menu di layar
    int PosisiY = 10;

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 5; // Total jumlah menu
    int key;

    system("cls");
    frame();

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
                case 1: printf("Tambah Data Diskon"); break;
                case 2: printf("Lihat Data Diskon"); break;
                case 3: printf("Ubah Data Diskon"); break;
                case 4: printf("Hapus Data Diskon"); break;
                case 5: printf("EXIT PROGRAM"); break;
                default: return;
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
                    menuAddDiskon();
                    break;
                case 2:
                    menuReadDiskon();
                    break;
                case 3:
                    menuUpdateDiskon();
                    break;
                case 4:
                    menuDeleteDiskon();
                    break;
                case 5:
                    system("cls");
                    frame();
                    return;
                default:
                    showMessage("ERROR", "Pilihan tidak valid.");
            }
        }
    } while (1);
}

#endif //CRUD_DISKON_H
