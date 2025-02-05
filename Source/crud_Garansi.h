#ifndef CRUD_GARANSI_H
#define CRUD_GARANSI_H

#include "crud_Member.h"
#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"

void inputGaransi(int n) {
    system("cls");
    templateUI();

    char kodeGaransi[] = {"GRS"};
    int idTerakhir = 0;
    int batasKiri = 5;

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
    gotoxy(batasKiri, 2); SetColor(colorMainText);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        // Generate ID otomatis
        snprintf(garansi.idGrns, sizeof(garansi.idGrns), "%s%i", kodeGaransi, i);

        // Menampilkan Teks Untuk Input
        SetColor(text2);
        gotoxy(batasKiri, 3); printf("=== [ MASUKKAN DATA GARANSI ] ===========");
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

        gotoxy(57, 8); getteks(garansi.jenisGrns, 50);

        gotoxy(57, 11); getnum(&garansi.durasi, 1);

        gotoxy(57, 14); getteks(garansi.ketentuan, 50);

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
    int yTeks = 6;

    fileGaransi = fopen("../Database/dat/Garansi.dat", "rb");
    if (fileGaransi == NULL) {
        perror("Failed to open file");
        return;
    }

    while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
        printTable(20, 95, 3, 38);
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(20, 4);printf(" %-8s  %-20s  %-15s  %-10s\n", id, jenis, durasi, status);
        gotoxy(20, yTeks);printf(" %-8s  %-20s  %-15d  %-10s\n", garansi.idGrns, garansi.jenisGrns, garansi.durasi, garansi.status);

        if (i % 35 == 0) {
            getchar();
            cleanKiri();
            yTeks = 5; // PADA SAAT BERHENTI, KOORDINAT UNTUK MENAMPILKAN DATA KARYAWAN AKAN RESET KEMBALI KE AWAL
        }
        i++;
        yTeks++;
    }

    fclose(fileGaransi);
}

void readDetailGaransi() {
    int batasKiri = 3;
    char idGrns[10];
    cleanKanan();
    cleanKiri();
    retype:

    SetColor(colorHeadText);
    gotoxy(130, 2); printf("   %-35s", "W E L C O M E  A D M I N");
    gotoxy(130, 41); printf("%38c", ' ');
    gotoxy(130, 5); SetColor(text2);
    gotoxy(135, 13); printf("Masukkan ID Garansi");
    gotoxy(135, 15); printf("[        ]");

    readdataGaransiINJS();

    gotoxy(137, 15); getteks(idGrns, 6);
    cleanKiri();

    int i = 1;
    int found = 0;
    //Membuka file dengan mode rb
    fileGaransi = fopen("../Database/dat/Garansi.dat", "rb");

    gotoxy(0, 3); SetColor(colorMainText);
    while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
        if (strcmp(idGrns, garansi.idGrns) == 0) {
            found = 1;
            break;
        }
        i++;
    }

    if (found == 1) {
        cleanKiri();
        SetColor(text2);
        gotoxy(batasKiri, 5); printf("ID Garansi");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", garansi.idGrns);

        gotoxy(batasKiri, 8); printf("Nama garansi");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", garansi.jenisGrns);

        gotoxy(batasKiri, 11); printf("Durasi");
        gotoxy(batasKiri+50, 11); printf("| %-40d|", garansi.durasi);

        gotoxy(batasKiri, 14); printf("Ketentuan");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", garansi.ketentuan);

        gotoxy(batasKiri, 17); printf("Status");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", garansi.status);
    } else {
        showMessage("ALERT!", "ID Garansi tidak ditemukan");
        goto retype;
    }
    gotoxy(135, 30); printf("Press ENTER to back...");
    getchar();
    //Menutup file setelah membaca
    fclose(fileGaransi);
    getchar();
}

void updateGaransi() {
    int found;
    found = 0;
    char idGaransi[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    readdataGaransiINJS();
    gotoxy(135, 5); SetColor(text2);
    gotoxy(135, 10); printf("ID Produk : [      ]");
    gotoxy(149, 10); getteks(idGaransi, 4);

    //Membuka file asli dengan mode rb
    fileGaransi = fopen("../Database/dat/Garansi.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempGaransi = fopen("../Database/Temp/GaransiTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idGaransi, garansi.idGrns) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&garansi, sizeof(garansi), 1, tempGaransi);
        }
    }

    //Proses lanjutan setelah data ditemukan
    if (found == 1) {
        cleanKiri();
        SetColor(text2);
        gotoxy(batasKiri, 3); printf("ID Garansi");
        gotoxy(batasKiri+50, 3); printf("| %-40s|", garansi.idGrns);

        gotoxy(batasKiri, 4); printf("Nama Garansi");
        gotoxy(batasKiri+50, 4); printf("| %-40s|", garansi.jenisGrns);

        gotoxy(batasKiri, 5); printf("Durasi");
        gotoxy(batasKiri+50, 5); printf("| %-40d|", garansi.durasi);

        gotoxy(batasKiri, 6); printf("Ketentuan");
        gotoxy(batasKiri+50, 6); printf("| %-40s|", garansi.ketentuan);

        gotoxy(batasKiri, 7); printf("Status");
        gotoxy(batasKiri+50, 7); printf("| %-40s|", garansi.status);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColor(colorHeadText);
        gotoxy(batasKiri, 13); printf("=== [ MASUKKAN DATA YANG BARU ] ===========");
        SetColor(text2);
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

        int durasiTemp = 0;
        gotoxy(57, 19); getnum(&durasiTemp, 2);

        char ketentuanTemp[10];
            gotoxy(57, 21); getteks(ketentuanTemp, 35);

        char statusTemp[10];
        gotoxy(57, 23); getteks(statusTemp, 10);

        if (doaction("UBAH DATA") == 1) {
            strcpy(garansi.idGrns, idGaransi);
            strcpy(garansi.jenisGrns, namTemp);
            garansi.durasi = durasiTemp;
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
        goto retype;
    }
    fclose(fileGaransi);
    fclose(tempGaransi);
}

void deleteDataGaransi() {
    int found;
    found = 0;
    char idGaransi[10];
    int batasKiri = 5;
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    retype:
    cleanKanan();
    cleanKiri();
    readdataGaransiINJS();
    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 10); printf("ID Garansi : [      ]");
    gotoxy(PosisiX+15, 10); getteks(idGaransi, 4);

    //Membuka file asli dengan mode rb
    fileGaransi = fopen("../Database/dat/Garansi.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempGaransi = fopen("../Database/Temp/GaransiTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idGaransi, garansi.idGrns) == 0) {
            cleanKiri();
            gotoxy(batasKiri, 5); printf("ID Garansi");
            gotoxy(batasKiri+50, 5); printf("| %-40s|", garansi.idGrns);

            gotoxy(batasKiri, 8); printf("Nama Garansi");
            gotoxy(batasKiri+50, 8); printf("| %-40s|", garansi.jenisGrns);

            gotoxy(batasKiri, 11); printf("Durasi");
            gotoxy(batasKiri+50, 11); printf("| %-40d|", garansi.durasi);

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

    inputGaransi(n);
    system("cls");
    frame();
}

void menuReadGaransi() {
    cleanKanan();
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 35); printf("Press ENTER to next...");
    readdataGaransiINJS();
    getch();
    if (lihatDetil() == 1) {
        readDetailGaransi();
    }
    system("cls");
    frame();
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
    system("cls");
    frame();
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
    system("cls");
    frame();
}

void crudGaransi() {
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

#endif //CRUD_GARANSI_H