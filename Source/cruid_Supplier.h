#ifndef CRUID_SUPPLIER_H
#define CRUID_SUPPLIER_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"

void inputSupplier(int n) {
    system("cls");
    templateUI();

    char kodeSupplier[] = {"SPL"};
    int idTerakhir = 0;
    int batasKiri = 5;

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
    gotoxy(batasKiri, 2); SetColor(colorMainText);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        // Generate ID otomatis
        snprintf(supplier.idSpl, sizeof(supplier.idSpl), "%s%i", kodeSupplier, i);

        // Menampilkan Teks Untuk Input
        SetColor(text2);
        gotoxy(batasKiri, 3); printf("=MASUKKAN DATA SUPPLIER===========");
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

        gotoxy(57, 8); getteks(supplier.namaSpl, 50);
        gotoxy(57, 11); getteks(supplier.alamat, 50);
        gotoxy(57, 14); getno(supplier.noTelp, 13);
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
    int yTeks = 6;

    FILE *fileSupplier = fopen("../Database/dat/Supplier.dat", "rb");
    if (fileSupplier == NULL) {
        perror("Failed to open file");
        return;
    }


    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        printTable(10, 105, 3, 38);
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(10, 4);printf(" %-8s   %-20s   %-25s   %-15s   %10s\n", id, nama, alamat, noTelpn, status);
        gotoxy(10,yTeks); printf(" %-8s   %-20s   %-25s   %-15s   %10s\n", supplier.idSpl, supplier.namaSpl, supplier.alamat, supplier.noTelp, supplier.status);

        if (i % 35 == 0) {
            getchar();
            cleanKiri();
            yTeks = 5; // PADA SAAT BERHENTI, KOORDINAT UNTUK MENAMPILKAN DATA KARYAWAN AKAN RESET KEMBALI KE AWAL
        }
        i++;
        yTeks++;
    }
    fclose(fileSupplier);
}


void readDetailSupplier() {
    int batasKiri = 3;
    char idSplr[10];
    cleanKanan();
    cleanKiri();
    retype:

    SetColor(colorHeadText);
    gotoxy(130, 2); printf("   %-35s", "W E L C O M E  A D M I N");
    gotoxy(130, 41); printf("%38c", ' ');
    gotoxy(130, 5); SetColor(text2);
    gotoxy(135, 13); printf("Masukkan ID Supplier");
    gotoxy(135, 15); printf("[        ]");

    readdataSupplierALL();

    gotoxy(137, 15); getteks(idSplr, 4);
    cleanKiri();

    int i = 1;
    int found = 0;
    //Membuka file dengan mode rb
    fileSupplier = fopen("../Database/dat/Supplier.dat", "rb");

    gotoxy(0, 3); SetColor(colorMainText);
    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        if (strcmp(idSplr, supplier.idSpl) == 0) {
            found = 1;
            break;
        }
        i++;
    }

    if (found == 1) {
        cleanKiri();
        SetColor(text2);
        gotoxy(batasKiri, 5); printf("ID Supplier");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", supplier.idSpl);

        gotoxy(batasKiri, 8); printf("Nama Supplier");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", supplier.namaSpl);

        gotoxy(batasKiri, 11); printf("Alamat");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", supplier.alamat);

        gotoxy(batasKiri, 14); printf("No Telepon");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", supplier.noTelp);

        gotoxy(batasKiri, 17); printf("Status");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", karyawan.status);
    } else {
        showMessage("ALERT!", "ID Supplier tidak ditemukan");
        goto retype;
    }
    gotoxy(135, 30); printf("Press ENTER to back...");
    getchar();
    //Menutup file setelah membaca
    fclose(fileSupplier);
    getchar();
}

void updateSupplier() {
    int found;
    found = 0;
    char idSupplier[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    readdataSupplierALL();
    gotoxy(135, 5); SetColor(text2);
    gotoxy(135, 10); printf("ID Supplier : [      ]");
    gotoxy(149, 10); getteks(idSupplier, 4);

    //Membuka file asli dengan mode rb
    fileSupplier = fopen("../Database/dat/Supplier.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempSupplier = fopen("../Database/Temp/SupplierTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idSupplier, supplier.idSpl) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&supplier, sizeof(supplier), 1, tempSupplier);
        }
    }

    //Proses lanjutan setelah data ditemukan
    if (found == 1) {
        cleanKiri();
        SetColor(text2);
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
        SetColor(colorHeadText);
        gotoxy(batasKiri, 13); printf("=MASUKKAN DATA YANG BARU===========");
        SetColor(text2);
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
            strcpy(supplier.idSpl, idSupplier);
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
        goto retype;
    }
    fclose(fileSupplier);
    fclose(tempSupplier);
}

void deleteDataSupplier() {
    int found;
    found = 0;
    char idSupplier[10];
    int batasKiri = 5;
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    retype:
    cleanKanan();
    readdataSupplierALL();
    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 10); printf("ID Supplier : [      ]");
    gotoxy(PosisiX+16, 10); getteks(idSupplier, 4);
    //Membuka file asli dengan mode rb
    fileSupplier = fopen("../Database/dat/Supplier.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempSupplier = fopen("../Database/Temp/SupplierTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idSupplier, supplier.idSpl) == 0) {
            cleanKiri();
            gotoxy(batasKiri, 5); printf("ID Supplier");
            gotoxy(batasKiri+50, 5); printf("| %-40s|", supplier.idSpl);

            gotoxy(batasKiri, 8); printf("Nama Supplier");
            gotoxy(batasKiri+50, 8); printf("| %-40s|", supplier.namaSpl);

            gotoxy(batasKiri, 11); printf("Alamat");
            gotoxy(batasKiri+50, 11); printf("| %-40s|", supplier.alamat);

            gotoxy(batasKiri, 14); printf("No Telepon");
            gotoxy(batasKiri+50, 14); printf("| %-40d|", supplier.noTelp);

            gotoxy(batasKiri, 17); printf("Status");
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
        goto retype;
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileSupplier);
    fclose(tempSupplier);
}

void MenuAddSupplier() {
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

    inputSupplier(n);
    system("cls");
    frame();
}

void menuReadSupplier() {
    cleanKanan();
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 35); printf("Press ENTER to next...");
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
    fileSupplier = fopen("../Database/dat/Supplier.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempSupplier = fopen("../Database/Temp/SupplierTemp.dat", "rb");

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
    fileSupplier = fopen("../Database/dat/Supplier.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempSupplier = fopen("../Database/Temp/SupplierTemp.dat", "rb");

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