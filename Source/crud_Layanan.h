#ifndef CRUD_LAYANAN_H
#define CRUD_LAYANAN_H

#include "Deklarasi.h"
#include "../Tampilan/Procedure.h"
#include "../Tampilan/Tampilan.h"

void inputLayanan1(int n) {
    system("cls");
    templateUI();
    cleanKiri();

    char kodeLayanan[] = {"LYN"};
    int idTerakhir = 0;
    int batasKiri = 5;

    fileLayanan = fopen("../Database/dat/Layanan.dat", "ab+");
    if (fileLayanan == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&layanan, sizeof(layanan), 1, fileLayanan) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(layanan.idLyn, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColor(colorMainText);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        memset(&layanan, 0, sizeof(layanan));
        // Generate ID otomatis
        snprintf(layanan.idLyn, sizeof(layanan.idLyn), "%s%i", kodeLayanan, i);

        // Menampilkan Teks Untuk Input
        SetColor(colorHeadText);
        gotoxy(batasKiri, 3); printf("=== [ MASUKKAN DATA LAYANAN ] ===========");
        SetColor(text2);
        gotoxy(batasKiri, 5); printf("ID Layanan");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", layanan.idLyn);

        gotoxy(batasKiri, 8); printf("Jenis Layanan");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", " ");

        gotoxy(batasKiri, 11); printf("Harga Layanan");
        gotoxy(batasKiri+50, 11); printf("| RP.%-37s|", " ");

        gotoxy(batasKiri, 14); printf("Status Layanan");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", " ");

        gotoxy(57, 8); getteks(layanan.jenisLyn, 20);

        getRp(&layanan.hargaLyn, 5, 9, 60, 11);

        gotoxy(57, 14); getteks(layanan.status, 15);

        fwrite(&layanan, sizeof(layanan), 1, fileLayanan);
    }
    fclose(fileLayanan);
}

void readdataLayanan2() {
    cleanKiri();

    char id[] = "ID";
    char jenis[] = "JENIS";
    char harga[] = "HARGA";
    char status[] = "STATUS";
    int i = 1;
    int yTeks = 6;

    fileLayanan = fopen("../Database/dat/Layanan.dat", "rb");
    if (fileLayanan == NULL) {
        perror("Failed to open file");
        return;
    }


    while (fread(&layanan, sizeof(layanan), 1, fileLayanan) == 1) {
        printTable(10, 100, 3, 38);
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(10, 4);printf(" %-10s   %-25s   %-20s   %-20s\n", id, jenis, harga, status);
        char hargaLayan[20];
        rupiah(layanan.hargaLyn, hargaLayan);
        gotoxy(10, yTeks);printf(" %-10s   %-25s   RP.%-17s   %-20s\n", layanan.idLyn, layanan.jenisLyn, hargaLayan, layanan.status);
        if (i % 35 == 0) {
            getchar(); // Wait for user input
            cleanKiri();
            yTeks = 5; // Reset yTeks after clearing screen
        }
        i++;
        yTeks++;
    }
    fclose(fileLayanan);
}

void updateLayanan() {
    int found;
    found = 0;
    char idLayanan[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    readdataLayanan2();
    gotoxy(135, 5); SetColor(text2);
    gotoxy(135, 10); printf("ID Layanan : [      ]");
    gotoxy(150, 10); getteks(idLayanan, 4);
    /*gotoxy(115+8, 10); printf("ID Karyawan : [   ]");
    gotoxy(row+17, 15); getteks(No, 6);*/

    //Membuka file asli dengan mode rb
    fileLayanan = fopen("../Database/dat/Layanan.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempLayanan = fopen("../Database/Temp/Temp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&layanan, sizeof(layanan), 1, fileLayanan) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idLayanan, layanan.idLyn) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&layanan, sizeof(layanan), 1, tempLayanan);
        }
    }

    char hargaLayan[20];
    rupiah(layanan.hargaLyn, hargaLayan);

    //Proses lanjutan setelah data ditemukan
    if (found == 1) {
        cleanKiri();
        gotoxy(batasKiri, 3); printf("ID Layanan");
        gotoxy(batasKiri+50, 3); printf("| %-40s|", layanan.idLyn);

        gotoxy(batasKiri, 4); printf("Jenis Layanan");
        gotoxy(batasKiri+50, 4); printf("| %-40s|", layanan.jenisLyn);

        gotoxy(batasKiri, 5); printf("Harga Layanan");
        gotoxy(batasKiri+50, 5); printf("| RP.%-37s|", hargaLayan);

        gotoxy(batasKiri, 6); printf("Status Layanan");
        gotoxy(batasKiri+50, 6); printf("| %-40s|", layanan.status);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColor(colorHeadText);
        gotoxy(batasKiri, 13); printf("=== [ MASUKKAN DATA YANG BARU ] ===========");
        SetColor(text2);
        gotoxy(batasKiri, 15); printf("ID Layanan");
        gotoxy(batasKiri+50, 15); printf("| %-40s|", layanan.idLyn);

        gotoxy(batasKiri, 18); printf("Jenis Layanan");
        gotoxy(batasKiri+50, 18); printf("| %-40s|", layanan.jenisLyn);

        gotoxy(batasKiri, 21); printf("Harga Layanan");
        gotoxy(batasKiri+50, 21); printf("| RP.%-37s|", " ");

        gotoxy(batasKiri, 24); printf("Status Layanan");
        gotoxy(batasKiri+50, 24); printf("| %-40s|", " ");

        int harga;
        getRp(&harga, 5, 9, 60, 21);

        char status[15];
        gotoxy(57, 24); getteks(status, 15);

        if (doaction("UBAH DATA") == 1) {
            strcpy(layanan.idLyn, idLayanan);
            layanan.hargaLyn = harga;
            strcpy(layanan.status, status);

            fwrite(&layanan, sizeof(layanan), 1, tempLayanan);
            while (fread(&layanan, sizeof(layanan), 1, fileLayanan) == 1) {
                fwrite(&layanan, sizeof(layanan), 1, tempLayanan);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&layanan, sizeof(layanan), 1, tempLayanan);
            while (fread(&layanan, sizeof(layanan), 1, fileLayanan) == 1) {
                fwrite(&layanan, sizeof(layanan), 1, tempLayanan);
            }
        }
    } else {
        showMessage("ALERT!", "ID Layanan tidak ditemukan");
        gotoxy(115+22, 10); printf("%s", "    ");
        goto retype;
    }
    fclose(fileLayanan);
    fclose(tempLayanan);
}

void deleteDataLayanan() {
    int found;
    found = 0;
    char idLayanan[10];
    int batasKiri = 5;
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    retype:
    cleanKanan();
    readdataLayanan2();
    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 10); printf("ID Layanan : [      ]");
    gotoxy(PosisiX+15, 10); getteks(idLayanan, 4);

    //Membuka file asli dengan mode rb
    fileLayanan = fopen("../Database/dat/Layanan.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempLayanan = fopen("../Database/Temp/Temp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&layanan, sizeof(layanan), 1, fileLayanan) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idLayanan, layanan.idLyn) == 0) {
            cleanKiri();
            SetColor(text2);
            gotoxy(batasKiri, 5); printf("ID Layanan");
            gotoxy(batasKiri+50, 5); printf("| %-40s|", layanan.idLyn);

            gotoxy(batasKiri, 8); printf("Jenis Layanan");
            gotoxy(batasKiri+50, 8); printf("| %-40s|", layanan.jenisLyn);

            gotoxy(batasKiri, 11); printf("Harga Layanan");
            gotoxy(batasKiri+50, 11); printf("| RP. %-36d|", layanan.hargaLyn);

            gotoxy(batasKiri, 14); printf("Status Layanan");
            gotoxy(batasKiri+50, 14); printf("| %-40s|", layanan.status);
            getchar(); getchar();

            if (deleteData() == 1) {
                found = 1;
                showMessage("ATTENTION!!", "Data berhasil dihapus!");
                continue;
            } else {
                found = 1;
                fwrite(&layanan, sizeof(layanan), 1, tempLayanan);
            }
        }
            //Jika tidak maka program akan menyalin data dari file asli ke data temporary
        else {
            fwrite(&layanan, sizeof(layanan), 1, tempLayanan);
        }
    }
    if (found == 0) {
        showMessage("ALERT!", "ID Diskon tidak ditemukan");
        gotoxy(115+22, 10); printf("%s", "    ");
        goto retype;
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileLayanan);
    fclose(tempLayanan);
}

void menuAddLayanan() {
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

    inputLayanan1(n);
    system("cls");
    frame();
}

void menuReadLayanan() {
    cleanKanan();
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 35); printf("Press ENTER to next...");
    readdataLayanan2();
    getch();
    /*if (lihatDetil() == 1) {
        readDetailKaryawan();
    }*/
    system("cls");
    frame();
}

void menuUpdateLayanan() {
    //Memanggil prosedur pencarian id kota
    updateLayanan();
    //Membuka file asli dengan mode wb
    fileLayanan = fopen("../Database/dat/Layanan.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempLayanan = fopen("../Database/Temp/Temp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&layanan, sizeof(layanan), 1, tempLayanan) == 1) {
        fwrite(&layanan, sizeof(layanan), 1, fileLayanan);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileLayanan);
    fclose(tempLayanan);
    system("cls");
    frame();
}

void menuDeleteLayanan() {
    //Memanggil prosedur pencarian id kota
    deleteDataLayanan();
    //Membuka file asli dengan mode wb
    fileLayanan = fopen("../Database/dat/Layanan.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempLayanan = fopen("../Database/Temp/Temp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&layanan, sizeof(layanan), 1, tempLayanan)==1) {
        fwrite(&layanan, sizeof(layanan), 1, fileLayanan);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileLayanan);
    fclose(tempLayanan);
    system("cls");
    frame();
}

// CRUD Menu
void crudLayanan() {
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
                case 1: printf("Tambah Data Layanan"); break;
                case 2: printf("Lihat Data Layanan"); break;
                case 3: printf("Ubah Data Layanan"); break;
                case 4: printf("Hapus Data Layanan"); break;
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
                    menuAddLayanan();
                    break;
                case 2:
                    menuReadLayanan();
                    break;
                case 3:
                    menuUpdateLayanan();
                    break;
                case 4:
                    menuDeleteLayanan();
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

#endif //CRUD_LAYANAN_H