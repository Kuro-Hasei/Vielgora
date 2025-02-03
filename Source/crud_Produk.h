#ifndef CRUD_PRODUK_H
#define CRUD_PRODUK_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"
#include "../Tampilan/Procedure.h"

void inputProduk1(int n) {
    system("cls");
    templateUI();

    char kodeProduk[] = {"PRD"};
    int idTerakhir = 0;
    int batasKiri = 5;

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
    gotoxy(batasKiri, 2); SetColor(colorMainText);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        memset(&produk, 0, sizeof(produk));
        // Generate ID otomatis
        snprintf(produk.idPrd, sizeof(produk.idPrd), "%s%i", kodeProduk, i);

        // Menampilkan Teks Untuk Input
        SetColor(text2);
        gotoxy(batasKiri, 3); printf("=== [ MASUKKAN DATA PRODUK ] ===========");
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

        gotoxy(57, 8); getteks(produk.jenisPrd, 15);

        gotoxy(57, 11); getteks(produk.namaPrd, 50);

        getRp(&produk.harga, 5, 9, 61, 14);

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
    int yTeks = 6;

    fileProduk = fopen("../Database/dat/Produk.dat", "rb");
    if (fileProduk == NULL) {
        perror("Failed to open file");
        return;
    }

    //MENAMPILKAN KE LAYAR ISI DARI FILE
    while (fread(&produk, sizeof(produk), 1, fileProduk) == 1) {
        printTable(10, 100, 3, 38);
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(10, 4);printf("  %-10s  %-15s  %-25s  %-20s  %-20s", id, jenis, nama, harga, status );
        char hargaPrd[20];
        rupiah(produk.harga, hargaPrd);
        gotoxy(10, yTeks); printf("  %-10s  %-15s  %-25s  RP. %-16s  %-20s", produk.idPrd, produk.jenisPrd, produk.namaPrd, hargaPrd, produk.status );
        if (i % 35 == 0) {
            getchar();
            cleanKiri();
            yTeks = 5; // PADA SAAT BERHENTI, KOORDINAT UNTUK MENAMPILKAN DATA KARYAWAN AKAN RESET KEMBALI KE AWAL
        }
        i++;
        yTeks++;
    }
    //MENUTUP FILE
    fclose(fileProduk);
}

void updateProduk() {
    int found;
    found = 0;
    char idProduk[10];
    int batasKiri = 5;
    char hargaPrd[20];

    retype:
    cleanKanan();
    readdataProduk2();
    gotoxy(135, 5); SetColor(text2);
    gotoxy(135, 10); printf("ID Produk : [      ]");
    gotoxy(149, 10); getteks(idProduk, 4);
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
        SetColor(text2);
        gotoxy(batasKiri, 3); printf("ID Karyawan");
        gotoxy(batasKiri+50, 3); printf("| %-40s|", produk.idPrd);

        gotoxy(batasKiri, 4); printf("Jenis Produk");
        gotoxy(batasKiri+50, 4); printf("| %-40s|", produk.jenisPrd);

        gotoxy(batasKiri, 5); printf("Nama Produk");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", produk.namaPrd);

        gotoxy(batasKiri, 6); printf("Harga Produk");
        rupiah(produk.harga, hargaPrd);
        gotoxy(batasKiri+50, 6); printf("| RP.%-37s|", hargaPrd);

        gotoxy(batasKiri, 7); printf("Status Produk");
        gotoxy(batasKiri+50, 7); printf("| %-40s|", produk.status);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColor(colorHeadText);
        gotoxy(batasKiri, 13); printf("=== [ MASUKKAN DATA YANG BARU ] ===========");
        SetColor(text2);
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
        getRp(&hargaTemp, 5, 9, 61, 21);

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
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    retype:
    cleanKanan();
    readdataProduk2();
    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 10); printf("ID Produk : [      ]");
    gotoxy(PosisiX+14, 10); getteks(idProduk, 4);

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
        return;
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileProduk);
    fclose(tempProduk);
}

void menuAddProduk() {
    cleanKanan();
    int PosisiX = 135;

    int n;
    char man[] = "W E L C O M E  A D M I N";
    char space = " ";

    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 10); printf("Banyaknya data : [   ]");
    gotoxy(PosisiX+19, 10); getnum(&n, 1);

    inputProduk1(n);
    system("cls");
    frame();
}

void menuReadProduk() {
    cleanKanan();
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 35); printf("Press ENTER to next...");
    readdataProduk2();
    getch();
    /* BUAT LIAT DETAIL JIKA DI PERLUKAN */
    /*if (lihatDetil() == 1) {
        readdataProduk2();
    }*/
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
    int PosisiX = 135; // Posisi menu di layar
    int PosisiY = 10;
    int jarakMenu = 2;

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 5; // Total jumlah menu
    int key;

    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    system("cls");
    frame();

    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        SetColor(colorHeadText);
        gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
        gotoxy(PosisiX - 5, 40); printf("%38c", space);
        SetColor(text2);

        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) { // Tambahkan tanda ">>" di menu aktif
                gotoxy(PosisiX + 22, PosisiY + (i - 1) * jarakMenu); printf("<<<");
            } else {
                gotoxy(PosisiX + 22, PosisiY + (i - 1) * jarakMenu); printf("   ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + (i - 1) * jarakMenu);
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
