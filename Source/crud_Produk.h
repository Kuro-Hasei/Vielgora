#ifndef CRUD_PRODUK_H
#define CRUD_PRODUK_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"
#include "../Tampilan/Procedure.h"

void inputProduk1(int n) {
    system("cls");
    templateUI();
    cleanKiri();

    char kodeProduk[] = {"PRD"};
    int idTerakhir = 0;
    int batasKiri = 3;

    fileProduk = fopen("../Database/dat/Produk.dat", "ab+");
    if (fileProduk == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&produk, sizeof(produk), 1, fileProduk) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(produk.idPrd, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColorBlock(3,7);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        memset(&produk, 0, sizeof(produk));
        // Generate ID otomatis
        snprintf(produk.idPrd, sizeof(produk.idPrd), "%s%i", kodeProduk, i);

        // Menampilkan Teks Untuk Input
        SetColorBlock(3,7);
        gotoxy(batasKiri, 3); printf("=MASUKKAN DATA PRODUK===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 5); printf("ID Produk");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", produk.idPrd);

        gotoxy(batasKiri, 8); printf("Jenis Produk");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", " ");

        gotoxy(batasKiri, 11); printf("Nama Produk");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", " ");

        gotoxy(batasKiri, 14); printf("Harga Produk");
        gotoxy(batasKiri+50, 14); printf("| RP.%-37s|", " ");

        gotoxy(batasKiri, 17); printf("status Produk");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", "Tersedia");

        gotoxy(55, 8); getteks(produk.jenisPrd, 15);

        gotoxy(55, 11); getteks(produk.namaPrd, 50);

        getRp(&produk.harga, 5, 9, 59, 14);

        strcpy(produk.status, "Tersedia");

        fwrite(&produk, sizeof(produk), 1, fileProduk);
    }
    fclose(fileProduk);
}

void readdataProduk2() {
    cleanKiri();

    char id[] = "ID";
    char jenis[] = "JENIS";
    char nama[] = "NAMA";
    char harga[] = "HARGA";
    char status[] = "STATUS";

    int i = 1;
    int yTeks = 4;

    fileProduk = fopen("../Database/dat/Produk.dat", "rb");
    if (fileProduk == NULL) {
        perror("Failed to open file");
        return;
    }

    //MENAMPILKAN KE LAYAR ISI DARI FILE
    while (fread(&produk, sizeof(produk), 1, fileProduk) == 1) {
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(10, 4);printf("  %-10s  %-15s  %-25s  %-15s  %-20s", id, jenis, nama, harga, status );
        char hargaPrd[20];
        rupiah(produk.harga, hargaPrd);
        gotoxy(10, 6); printf("  %-10s  %-15s  %-25s  RP. %-11s  %-20s", produk.idPrd, produk.jenisPrd, produk.namaPrd, hargaPrd, produk.status );
        if (i % 35 == 0) {
            getchar();
            cleanKiri();
            yTeks = 6; // PADA SAAT BERHENTI, KOORDINAT UNTUK MENAMPILKAN DATA KARYAWAN AKAN RESET KEMBALI KE AWAL
        }
        i++;
        yTeks++;
    }
    printTable(10, 100, 3, 38);
    //MENUTUP FILE
    fclose(fileProduk);
}

void updateProduk() {
    int found;
    found = 0;
    char idProduk[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    readdataProduk2();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("ID Produk : [      ]");
    gotoxy(115+22, 10); getteks(idProduk, 4);
    /*gotoxy(115+8, 10); printf("ID Karyawan : [   ]");
    gotoxy(row+17, 15); getteks(No, 6);*/

    //Membuka file asli dengan mode rb
    fileProduk = fopen("../Database/dat/Produk.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempProduk = fopen("../Database/Temp/Temp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&produk, sizeof(produk), 1, fileProduk) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idProduk, produk.idPrd) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&produk, sizeof(produk), 1, tempProduk);
        }
    }

    //Proses lanjutan setelah data ditemukan
    if (found == 1) {
        cleanKiri();
        gotoxy(batasKiri, 3); printf("ID Karyawan");
        gotoxy(batasKiri+50, 3); printf("| %-40s|", produk.idPrd);

        gotoxy(batasKiri, 4); printf("Jenis Produk");
        gotoxy(batasKiri+50, 4); printf("| %-40s|", produk.jenisPrd);

        gotoxy(batasKiri, 5); printf("Nama Produk");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", produk.namaPrd);

        gotoxy(batasKiri, 6); printf("Harga Produk");
        gotoxy(batasKiri+50, 6); printf("| RP. %-36d|", produk.harga);

        gotoxy(batasKiri, 7); printf("Status Produk");
        gotoxy(batasKiri+50, 7); printf("| %-40s|", produk.status);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColorBlock(3,7);
        gotoxy(batasKiri, 13); printf("=== [ MASUKKAN DATA YANG BARU ] ===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 15); printf("ID Produk");
        gotoxy(batasKiri+50, 15); printf("| %-40s|", produk.idPrd);

        gotoxy(batasKiri, 17); printf("Jenis Produk");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", produk.jenisPrd);

        gotoxy(batasKiri, 19); printf("Nama Produk");
        gotoxy(batasKiri+50, 19); printf("| %-40s|", produk.namaPrd);

        gotoxy(batasKiri, 21); printf("Harga Produk");
        gotoxy(batasKiri+50, 21); printf("| RP. %-36s|", " ");

        gotoxy(batasKiri, 23); printf("Stats Produk");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", " ");

        int hargaTemp;
        gotoxy(61, 21); getnum(&hargaTemp, 9);

        char statusTemp[15];
        gotoxy(57, 23); getteks(statusTemp, 15);

        if (doaction("UBAH DATA") == 1) {
            strcpy(produk.idPrd, idProduk);
            produk.harga = hargaTemp;
            strcpy(produk.status, statusTemp);

            fwrite(&produk, sizeof(produk), 1, tempProduk);
            while (fread(&produk, sizeof(produk), 1, fileProduk) == 1) {
                fwrite(&produk, sizeof(produk), 1, tempProduk);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&produk, sizeof(produk), 1, tempProduk);
            while (fread(&produk, sizeof(produk), 1, fileProduk) == 1) {
                fwrite(&produk, sizeof(produk), 1, tempProduk);
            }
        }
    } else {
        showMessage("ALERT!", "ID Produk tidak ditemukan");
        gotoxy(115+22, 10); printf("%s", "    ");
        goto retype;
    }
    fclose(fileProduk);
    fclose(tempProduk);
}

void deleteDataProduk() {
    int found;
    found = 0;
    char idProduk[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    readdataProduk2();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("ID Produk : [      ]");
    gotoxy(115+22, 10); getteks(idProduk, 4);

    //Membuka file asli dengan mode rb
    fileProduk = fopen("../Database/dat/Produk.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempProduk = fopen("../Database/Temp/Temp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&produk, sizeof(produk), 1, fileProduk) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idProduk, produk.idPrd) == 0) {
            cleanKiri();
            gotoxy(batasKiri, 5); printf("ID Produk");
            gotoxy(batasKiri+50, 5); printf("| %-40s|", produk.idPrd);

            gotoxy(batasKiri, 8); printf("Jenis Produk");
            gotoxy(batasKiri+50, 8); printf("| %-40s|", produk.jenisPrd);

            gotoxy(batasKiri, 11); printf("Nama Produk");
            gotoxy(batasKiri+50, 11); printf("| %-40s|", produk.namaPrd);

            gotoxy(batasKiri, 14); printf("Harga Produk");
            gotoxy(batasKiri+50, 14); printf("| RP. %-36d|", produk.harga);

            gotoxy(batasKiri, 17); printf("status Produk");
            gotoxy(batasKiri+50, 17); printf("| %-40s|", produk.status);
            getchar();
            getchar();
            if (deleteData() == 1) {
                found = 1;
                showMessage("ATTENTION!!", "Data berhasil dihapus!");
                continue;
            } else {
                found = 1;
                fwrite(&produk, sizeof(produk), 1, tempProduk);
            }
        }
            //Jika tidak maka program akan menyalin data dari file asli ke data temporary
        else {
            fwrite(&produk, sizeof(produk), 1, tempProduk);
        }
    }
    if (found == 0) {
        showMessage("ALERT!", "ID Karyawan tidak ditemukan");
        gotoxy(115+22, 10); printf("%s", "    ");
        goto retype;
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileProduk);
    fclose(tempProduk);
}

void menuAddProduk() {
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

    inputProduk1(n);
    system("cls");
    frame();
}

void menuReadProduk() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(text2);
    gotoxy(115, 2); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);
    gotoxy(120, 35); printf("Press ENTER to next...");
    readdataProduk2();
    getch();
    system("cls");
    frame();
}

void menuUpdateProduk() {
    //Memanggil prosedur pencarian id kota
    updateProduk();
    //Membuka file asli dengan mode wb
    fileProduk = fopen("../Database/dat/Produk.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempProduk = fopen("../Database/Temp/Temp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&produk, sizeof(produk), 1, tempProduk) == 1) {
        fwrite(&produk, sizeof(produk), 1, fileProduk);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileProduk);
    fclose(tempProduk);
    system("cls");
    frame();
}

void menuDeleteProduk() {
    //Memanggil prosedur pencarian id kota
    deleteDataProduk();
    //Membuka file asli dengan mode wb
    fileProduk = fopen("../Database/dat/Produk.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempProduk = fopen("../Database/Temp/Temp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&produk, sizeof(produk), 1, tempProduk)==1) {
        fwrite(&produk, sizeof(produk), 1, fileProduk);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileProduk);
    fclose(tempProduk);
    system("cls");
    frame();
}



// CRUD Menu
void crudProduk() {
    int PosisiX = 120; // Posisi menu di layar
    int PosisiY = 10;

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 5; // Total jumlah menu
    int key;

    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    system("cls");
    frame();

    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        SetColor(text2);
        gotoxy(115, 3); printf("   %-35s", man);
        gotoxy(115, 41); printf("%38c", space);
        SetColor(colorMainText);

        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) { // Tambahkan tanda ">>" di menu aktif
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("<<<");
            } else {
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("   ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + i - 1);
            switch (i) {
                case 1: printf("Tambah Data Produk"); break;
                case 2: printf("Lihat Data Produk"); break;
                case 3: printf("Ubah Data Produk"); break;
                case 4: printf("Hapus Data Produk"); break;
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
                    menuAddProduk();
                    break;
                case 2:
                    menuReadProduk();
                    break;
                case 3:
                    menuUpdateProduk();
                    break;
                case 4:
                    menuDeleteProduk();
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


#endif //CRUD_PRODUK_H
