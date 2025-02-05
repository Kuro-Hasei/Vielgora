#ifndef CRUD_AKSESORIS_H
#define CRUD_AKSESORIS_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"

void inputAksesoris1(int n) {
    system("cls");
    templateUI();

    char kodeAksesoris[] = {"AKS"};
    int idTerakhir = 0;
    int batasKiri = 5;

    fileAksessoris = fopen("../Database/dat/Aksesoris.dat", "ab+");
    if (fileAksessoris == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(aksessoris.idAks, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColor(colorMainText);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        memset(&aksessoris, 0, sizeof(aksessoris));
        // Generate ID otomatis
        snprintf(aksessoris.idAks, sizeof(aksessoris.idAks), "%s%i", kodeAksesoris, i);

        // Menampilkan Teks Untuk Input
        SetColor(colorHeadText);
        gotoxy(batasKiri, 3); printf("=== [ MASUKKAN DATA PRODUK ] ===========");
        SetColor(text2);
        gotoxy(batasKiri, 5); printf("ID Aksesoris");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", aksessoris.idAks);

        gotoxy(batasKiri, 8); printf("Jenis Aksesoris");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", " ");

        gotoxy(batasKiri, 11); printf("Nama Aksesoris");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", " ");

        gotoxy(batasKiri, 14); printf("Harga Aksesoris");
        gotoxy(batasKiri+50, 14); printf("| RP.  %-35s|", " ");

        gotoxy(batasKiri, 17); printf("Jumlah Aksesoris");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", " ");

        gotoxy(57, 8); getteks(aksessoris.jenisAks, 15);

        gotoxy(57, 11); getteks(aksessoris.namaAks, 50);

        getRp(&aksessoris.harga, 5, 9, 61, 14);

        gotoxy(57, 17); getnum(&aksessoris.quantity, 2);

        fwrite(&aksessoris, sizeof(aksessoris), 1, fileAksessoris);
    }
    fclose(fileAksessoris);
}

void readdataAksesoris2() {
    cleanKiri();

    char id[] = "ID";
    char jenis[] = "JENIS";
    char nama[] = "NAMA";
    char harga[] = "HARGA";
    char qt[] = "QUANTITY";

    int i = 1;
    int yTeks = 6;

    fileAksessoris = fopen("../Database/dat/Aksesoris.dat", "rb");
    if (fileAksessoris == NULL) {
        perror("Failed to open file");
        return;
    }

    while (fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris) == 1) {
        printTable(10, 110, 3, 38);
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(10, 4);printf(" %-8s   %-15s   %-30s   %-22s   %-10s\n", id, jenis, nama, harga, qt);
        char hargaAks[20];
        rupiah(aksessoris.harga, hargaAks);
        gotoxy(10, yTeks);printf(" %-8s   %-15s   %-30s   RP. %-18s   %-10d\n", aksessoris.idAks, aksessoris.jenisAks, aksessoris.namaAks, hargaAks, aksessoris.quantity);
        if (i % 35 == 0) {
            getchar();
            cleanKiri();
            yTeks = 5; // PADA SAAT BERHENTI, KOORDINAT UNTUK MENAMPILKAN DATA KARYAWAN AKAN RESET KEMBALI KE AWAL
        }
        i++;
        yTeks++;
    }
    fclose(fileAksessoris);
}

void updateAksesoris() {
    int found;
    found = 0;
    char idAksesoris[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    readdataAksesoris2();
    gotoxy(135, 5); SetColor(text2);
    gotoxy(135, 10); printf("ID Aksessoris : [      ]");
    gotoxy(153, 10); getteks(idAksesoris, 4);
    /*gotoxy(115+8, 10); printf("ID Karyawan : [   ]");
    gotoxy(row+17, 15); getteks(No, 6);*/

    //Membuka file asli dengan mode rb
    fileAksessoris = fopen("../Database/dat/Aksesoris.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempAksessoris = fopen("../Database/Temp/Temp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idAksesoris, aksessoris.idAks) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
        }
    }
    char hargaAks[20];
    rupiah(aksessoris.harga, hargaAks);

    //Proses lanjutan setelah data ditemukan
    if (found == 1) {
        cleanKiri();
        SetColor(text2);
        gotoxy(batasKiri, 3); printf("ID Aksesoris");
        gotoxy(batasKiri+50, 3); printf("| %-40s|", aksessoris.idAks);

        gotoxy(batasKiri, 4); printf("Jenis Aksesoris");
        gotoxy(batasKiri+50, 4); printf("| %-40s|", aksessoris.jenisAks);

        gotoxy(batasKiri, 5); printf("Nama Aksesoris");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", aksessoris.namaAks);

        gotoxy(batasKiri, 6); printf("Harga Aksesoris");
        gotoxy(batasKiri+50, 6); printf("| RP. %-36s|", hargaAks);

        gotoxy(batasKiri, 7); printf("Jumlah Aksesoris");
        gotoxy(batasKiri+50, 7); printf("| %-40d|", aksessoris.quantity);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColor(colorHeadText);
        gotoxy(batasKiri, 13); printf("=== [ MASUKKAN DATA YANG BARU ] ===========");
        SetColor(text2);
        gotoxy(batasKiri, 15); printf("ID Aksesoris");
        gotoxy(batasKiri+50, 15); printf("| %-40s|", aksessoris.idAks);

        gotoxy(batasKiri, 17); printf("Jenis Aksesoris");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", aksessoris.jenisAks);

        gotoxy(batasKiri, 19); printf("Nama Aksesoris");
        gotoxy(batasKiri+50, 19); printf("| %-40s|", aksessoris.namaAks);

        gotoxy(batasKiri, 21); printf("Harga Aksesoris");
        gotoxy(batasKiri+50, 21); printf("| RP. %-36s|", " ");

        gotoxy(batasKiri, 23); printf("Jumlah Aksesoris");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", " ");

        int hargaTemp;
        getRp(&hargaTemp, 5, 9, 61, 21);

        int qt;
        gotoxy(57, 23); getnum(&qt, 2);

        if (doaction("UBAH DATA") == 1) {
            strcpy(aksessoris.idAks, idAksesoris);
            aksessoris.harga = hargaTemp;
            aksessoris.quantity = qt;

            fwrite(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
            while (fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris) == 1) {
                fwrite(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
            while (fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris) == 1) {
                fwrite(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
            }
        }
    } else {
        showMessage("ALERT!", "ID Aksesoris tidak ditemukan");
        goto retype;
    }
    fclose(fileAksessoris);
    fclose(tempAksessoris);
}

void deleteDataAksessoris() {
    int found;
    found = 0;
    char idAksesoris[10];
    int batasKiri = 5;
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    retype:
    cleanKanan();
    readdataAksesoris2();
    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 10); printf("ID Aksessoris : [      ]");
    gotoxy(PosisiX+18, 10); getteks(idAksesoris, 4);

    char hargaAks[20];
    rupiah(aksessoris.harga, hargaAks);

    //Membuka file asli dengan mode rb
    fileAksessoris = fopen("../Database/dat/Aksesoris.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempAksessoris = fopen("../Database/Temp/Temp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idAksesoris, aksessoris.idAks) == 0) {
            cleanKiri();
            gotoxy(batasKiri, 5); printf("ID Aksesoris");
            gotoxy(batasKiri+50, 5); printf("| %-40s|", aksessoris.idAks);

            gotoxy(batasKiri, 8); printf("Jenis Aksesoris");
            gotoxy(batasKiri+50, 8); printf("| %-40s|", aksessoris.jenisAks);

            gotoxy(batasKiri, 11); printf("Nama Aksesoris");
            gotoxy(batasKiri+50, 11); printf("| %-40s|", aksessoris.namaAks);

            gotoxy(batasKiri, 14); printf("Harga Aksesoris");
            gotoxy(batasKiri+50, 14); printf("| RP. %-36s|", hargaAks);

            gotoxy(batasKiri, 17); printf("Status Aksesoris");
            gotoxy(batasKiri+50, 17); printf("| %-40d|", aksessoris.quantity);
            getchar();getchar();

            if (deleteData() == 1) {
                found = 1;
                showMessage("ATTENTION!!", "Data berhasil dihapus!");
                continue;
            } else {
                found = 1;
                fwrite(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
            }
        }
            //Jika tidak maka program akan menyalin data dari file asli ke data temporary
        else {
            fwrite(&aksessoris, sizeof(aksessoris), 1, tempAksessoris);
        }
    }
    if (found == 0) {
        showMessage("ALERT!", "ID Aksesoris tidak ditemukan");
        goto retype;
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileAksessoris);
    fclose(tempAksessoris);
}

void menuAddAksesoris() {
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

    inputAksesoris1(n);
    system("cls");
    frame();
}

void menuReadAksesoris() {
    cleanKanan();
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 35); printf("Press ENTER to next...");
    readdataAksesoris2();
    getch();
    /*if (lihatDetil() == 1) {
        readDetailKaryawan();
    }*/
    system("cls");
    frame();
}

void menuUpdateAksesoris() {
    //Memanggil prosedur pencarian id kota
    updateAksesoris();
    //Membuka file asli dengan mode wb
    fileAksessoris = fopen("../Database/dat/Aksesoris.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempAksessoris = fopen("../Database/Temp/Temp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&aksessoris, sizeof(aksessoris), 1, tempAksessoris) == 1) {
        fwrite(&aksessoris, sizeof(aksessoris), 1, fileAksessoris);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileAksessoris);
    fclose(tempAksessoris);
    system("cls");
    frame();
}

void menuDeleteAksesoris() {
    //Memanggil prosedur pencarian id kota
    deleteDataAksessoris();
    //Membuka file asli dengan mode wb
    fileAksessoris = fopen("../Database/dat/Aksesoris.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempAksessoris = fopen("../Database/Temp/Temp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&aksessoris, sizeof(aksessoris), 1, tempAksessoris)==1) {
        fwrite(&aksessoris, sizeof(aksessoris), 1, fileAksessoris);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileAksessoris);
    fclose(tempAksessoris);
    system("cls");
    frame();
}



// CRUD Menu
void crudAksesoris() {
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
                case 1: printf("Tambah Data Aksesoris"); break;
                case 2: printf("Lihat Data Aksesoris"); break;
                case 3: printf("Ubah Data Aksesoris"); break;
                case 4: printf("Hapus Data Aksesoris"); break;
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
                    menuAddAksesoris();
                    break;
                case 2:
                    menuReadAksesoris();
                    break;
                case 3:
                    menuUpdateAksesoris();
                    break;
                case 4:
                    menuDeleteAksesoris();
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

#endif //CRUD_AKSESORIS_H