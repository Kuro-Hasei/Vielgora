#ifndef CRUD_KARYAWAN_H
#define CRUD_KARYAWAN_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"

void inputKaryawan(int n) {
    system("cls");
    templateUI();
    cleanKiri();

    char kodeKaryawan[] = {"KRY"};
    int idTerakhir = 0;
    int batasKiri = 3;

    fileKaryawan = fopen("../Database/dat/Karyawan.dat", "ab+");
    if (fileKaryawan == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&karyawan, sizeof(karyawan), 1, fileKaryawan) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(karyawan.id, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColorBlock(3,7);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        memset(&karyawan, 0, sizeof(karyawan));
        // Generate ID otomatis
        snprintf(karyawan.id, sizeof(karyawan.id), "%s%i", kodeKaryawan, i);

        // Menampilkan Teks Untuk Input
        SetColorBlock(3,7);
        gotoxy(batasKiri, 3); printf("=MASUKKAN DATA KARYAWAN===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 5); printf("ID Karyawan");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", karyawan.id);

        gotoxy(batasKiri, 8); printf("Nama Karyawan");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", " ");

        gotoxy(batasKiri, 11); printf("Tanggal Lahir (DD-MM-YYYY)");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", " ");

        gotoxy(batasKiri, 14); printf("Jabatan");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", " ");

        gotoxy(batasKiri, 17); printf("No Telepon");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", " ");

        gotoxy(batasKiri, 20); printf("Alamat");
        gotoxy(batasKiri+50, 20); printf("| %-40s|", " ");

        gotoxy(batasKiri, 23); printf("Gender");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", " ");

        gotoxy(batasKiri, 26); printf("Status");
        gotoxy(batasKiri+50, 26); printf("| %-40s|", "Aktif");

        gotoxy(55, 8); getteks(karyawan.namaKry, 50);

        gotoxy(55, 11); getDate(karyawan.tglLhr);

        /*gotoxy(55, 14); getteks(karyawan.jabatan, 10);*/
        int validJabatan = 0;
        while (!validJabatan) {
            gotoxy(55, 14); getteks(karyawan.jabatan, 3);

            // Cek apakah jabatan valid
            for (int j = 0; j < jumlahJabatan; j++) {
                if (strcmp(karyawan.jabatan, jabatanKode[j]) == 0) {
                    strcpy(karyawan.jabatan, jabatanNama[j]); // Mengganti kode dengan nama jabatan
                    validJabatan = 1;
                    break;
                }
            }

            if (!validJabatan) {
                showMessage("ATTENTION", "Jabatan tidak valid.");
                gotoxy(55, 14); printf("%s", "   ");
            } else {
                gotoxy(batasKiri, 28); printf("%-70s", " "); // Hapus pesan error
            }
        }

        gotoxy(55, 17); getno(karyawan.noTLP, 13);

        gotoxy(55, 20); getteks(karyawan.alamat, 50);

        /*gotoxy(55, 23); getteks(karyawan.gender, 10);*/
        int validGender = 0;
        while (!validGender) {
            gotoxy(55, 23); getteks(karyawan.gender, 1);

            // Cek apakah Gender valid
            for (int j = 0; j < jumlahGender; j++) {
                if (strcmp(karyawan.gender, genderKode[j]) == 0) {
                    strcpy(karyawan.gender, genderNama[j]); // Mengganti kode dengan nama jabatan
                    validGender = 1;
                    break;
                }
            }

            if (!validGender) {
                showMessage("ATTENTION", "Gender tidak valid.");
                gotoxy(55, 23); printf("%s", " ");
            } else {
                gotoxy(batasKiri, 28); printf("%-70s", " "); // Hapus pesan error
            }
        }

        strcpy(karyawan.status, "Aktif");

        fwrite(&karyawan, sizeof(karyawan), 1, fileKaryawan);
    }
    fclose(fileKaryawan);
}

void readdataKaryawanINJS() {
    cleanKiri();

    char id[] = "ID";
    char nama[] = "NAMA";
    char jab[] = "JABATAN";
    char status[] = "STATUS";

    int i = 1;
    int yTeks = 4;

    fileKaryawan = fopen("../Database/dat/Karyawan.dat", "rb");
    if (fileKaryawan == NULL) {
        perror("Failed to open file");
        return;
    }

    printTable(3, 110, 1, 42);
    gotoxy(0, 3);
    SetColorBlock(3, 7);
    gotoxy(3, 2);
    printf(" %-8s   %-20s   %-15s   %-10s\n", id, nama, jab, status);

    while (fread(&karyawan, sizeof(karyawan), 1, fileKaryawan) == 1) {
        gotoxy(3, yTeks);
        printf(" %-8s   %-20s   %-20s   %-15s\n", karyawan.id, karyawan.namaKry, karyawan.jabatan, karyawan.status);

        if (i % 40 == 0) {
            printf("\n--- Press any key to continue ---\n");
            getchar(); // Wait for user input
            cleanKiri();
            yTeks = 4; // Reset yTeks after clearing screen
            gotoxy(3, 2);
            printf(" %-8s   %-20s   %-15s   %-10s\n", id, nama, jab, status);
        }
        i++;
        yTeks++;
    }
    fclose(fileKaryawan);
}

void readDetailKaryawan() {
    int batasKiri = 3;
    char idKrywn[10];
    system("cls");
    retype:

    gotoxy(115, 2); SetColorBlock(3,7); printf("   %-35s", "W E L C O M E  A D M I N");
    gotoxy(115, 41); printf("%38c", ' ');
    gotoxy(127, 5); SetColorBlock(3,7);
    gotoxy(124, 11); printf("Masukkan ID Karyawan");
    gotoxy(129, 15); printf("[        ]");

    readdataKaryawanINJS();
    frame();

    gotoxy(131, 15); getteks(idKrywn, 4);
    cleanKiri();

    int i = 1;
    int found = 0;
    //Membuka file dengan mode rb
    fileKaryawan = fopen("../Database/dat/Karyawan.dat", "rb");

    gotoxy(0, 3); SetColorBlock(3,7);
    while (fread(&karyawan, sizeof(karyawan), 1, fileKaryawan) == 1) {
        if (strcmp(idKrywn, karyawan.id) == 0) {
            found = 1;
            break;
        }
        i++;
    }

    if (found == 1) {
        cleanKiri();
        gotoxy(batasKiri, 5); printf("ID Karyawan");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", karyawan.id);

        gotoxy(batasKiri, 8); printf("Nama Karyawan");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", karyawan.namaKry);

        gotoxy(batasKiri, 11); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", karyawan.tglLhr);

        gotoxy(batasKiri, 14); printf("Jabatan");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", karyawan.jabatan);

        gotoxy(batasKiri, 17); printf("No Telepon");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", karyawan.noTLP);

        gotoxy(batasKiri, 20); printf("Alamat");
        gotoxy(batasKiri+50, 20); printf("| %-40s|", karyawan.alamat);

        gotoxy(batasKiri, 23); printf("Gender");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", karyawan.gender);

        gotoxy(batasKiri, 26); printf("Status");
        gotoxy(batasKiri+50, 26); printf("| %-40s|", karyawan.status);
    } else {
        showMessage("ALERT!", "ID Karyawan tidak ditemukan");
        gotoxy(131, 15); printf("       ");
        goto retype;
    }
    gotoxy(123, 30); printf("Press ENTER to back...");
    getchar();
    //Menutup file setelah membaca
    fclose(fileKaryawan);
    getchar();
}

void updateKaryawan() {
    int found;
    found = 0;
    char No[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    readdataKaryawanINJS();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("ID Karyawan : [      ]");
    gotoxy(115+27, 10); getteks(No, 4);
    /*gotoxy(115+8, 10); printf("ID Karyawan : [   ]");
    gotoxy(row+17, 15); getteks(No, 6);*/

    //Membuka file asli dengan mode rb
    fileKaryawan = fopen("../Database/dat/Karyawan.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempKaryawan = fopen("../Database/Temp/KaryawanTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&karyawan, sizeof(karyawan), 1, fileKaryawan) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(No, karyawan.id) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&karyawan, sizeof(karyawan), 1, tempKaryawan);
        }
    }

    //Proses lanjutan setelah data ditemukan
    if (found == 1) {
        cleanKiri();
        gotoxy(batasKiri, 3); printf("ID Karyawan");
        gotoxy(batasKiri+50, 3); printf("| %-40s|", karyawan.id);

        gotoxy(batasKiri, 4); printf("Nama Karyawan");
        gotoxy(batasKiri+50, 4); printf("| %-40s|", karyawan.namaKry);

        gotoxy(batasKiri, 5); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", karyawan.tglLhr);

        gotoxy(batasKiri, 6); printf("Jabatan");
        gotoxy(batasKiri+50, 6); printf("| %-40s|", karyawan.jabatan);

        gotoxy(batasKiri, 7); printf("No Telepon");
        gotoxy(batasKiri+50, 7); printf("| %-40s|", karyawan.noTLP);

        gotoxy(batasKiri, 8); printf("Alamat");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", karyawan.alamat);

        gotoxy(batasKiri, 9); printf("Gender");
        gotoxy(batasKiri+50, 9); printf("| %-40s|", karyawan.gender);

        gotoxy(batasKiri, 10); printf("Status");
        gotoxy(batasKiri+50, 10); printf("| %-40s|", karyawan.status);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColorBlock(3,7);
        gotoxy(batasKiri, 13); printf("=MASUKKAN DATA YANG BARU===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 15); printf("ID Karyawan");
        gotoxy(batasKiri+50, 15); printf("| %-40s|", karyawan.id);

        gotoxy(batasKiri, 17); printf("Nama Karyawan");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", " ");

        gotoxy(batasKiri, 19); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 19); printf("| %-40s|", " ");

        gotoxy(batasKiri, 21); printf("Jabatan");
        gotoxy(batasKiri+50, 21); printf("| %-40s|", " ");

        gotoxy(batasKiri, 23); printf("No Telepon");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", " ");

        gotoxy(batasKiri, 25); printf("Alamat");
        gotoxy(batasKiri+50, 25); printf("| %-40s|", " ");

        gotoxy(batasKiri, 27); printf("Gender");
        gotoxy(batasKiri+50, 27); printf("| %-40s|", " ");

        gotoxy(batasKiri, 29); printf("Status");
        gotoxy(batasKiri+50, 29); printf("| %-40s|", " ");

        char namTemp[50];
        gotoxy(57, 17); getteks(namTemp, 50);

        char tglTemp[12];
        gotoxy(57, 19); getDate(tglTemp);

        char jabTemp[10];
        /*gotoxy(57, 21); getteks(jabTemp, 20);*/
        int validJabatan = 0;
        while (!validJabatan) {
            gotoxy(57, 21); getteks(jabTemp, 3);

            // Cek apakah jabatan valid
            for (int j = 0; j < jumlahJabatan; j++) {
                if (strcmp(jabTemp, jabatanKode[j]) == 0) {
                    strcpy(jabTemp, jabatanNama[j]); // Mengganti kode dengan nama jabatan
                    validJabatan = 1;
                    break;
                }
            }

            if (!validJabatan) {

                gotoxy(batasKiri, 35); showMessage("ATTENTION", "Kode jabatan tidak valid!");
            } else {
                gotoxy(batasKiri, 35); printf("%-70s", " "); // Hapus pesan error
            }
        }

        char tlpTemp[15];
        gotoxy(57, 23); getno(tlpTemp, 13);

        char alamatTemp[50];
        gotoxy(57, 25); getteks(alamatTemp, 50);

        char sexTemp[10];
        /*gotoxy(57, 27); getteks(sexTemp, 1);*/
        int validGender = 0;
        while (!validGender) {
            gotoxy(57, 27); getteks(sexTemp, 1);

            // Cek apakah Gender valid
            for (int j = 0; j < jumlahGender; j++) {
                if (strcmp(sexTemp, genderKode[j]) == 0) {
                    strcpy(sexTemp, genderNama[j]); // Mengganti kode dengan nama jabatan
                    validGender = 1;
                    break;
                }
            }

            if (!validGender) {
                showMessage("ATTENTION", "Gender tidak valid.");
                gotoxy(57, 27); printf("%s", " ");
            }
        }

        char statusTemp[10];
        /*gotoxy(57, 29); getteks(statusTemp, 10);*/
        int validStatus = 0;
        while (!validStatus) {
            gotoxy(57, 29); getteks(statusTemp, 1);

            // Cek apakah Gender valid
            for (int j = 0; j < jumlahGender; j++) {
                if (strcmp(statusTemp, statusKodeK[j]) == 0) {
                    strcpy(statusTemp, statusNamaK[j]); // Mengganti kode dengan nama jabatan
                    validStatus = 1;
                    break;
                }
            }

            if (!validStatus) {
                showMessage("ATTENTION", "Status tidak valid.");
                gotoxy(57, 29); printf("%s", " ");
            }
        }

        if (doaction("UBAH DATA") == 1) {
            strcpy(karyawan.id, No);
            strcpy(karyawan.namaKry, namTemp);
            strcpy(karyawan.tglLhr, tglTemp);
            strcpy(karyawan.jabatan, jabTemp);
            strcpy(karyawan.noTLP, tlpTemp);
            strcpy(karyawan.alamat, alamatTemp);
            strcpy(karyawan.gender, sexTemp);
            strcpy(karyawan.status, statusTemp);
            fwrite(&karyawan, sizeof(karyawan), 1, tempKaryawan);
            while (fread(&karyawan, sizeof(karyawan), 1, fileKaryawan) == 1) {
                fwrite(&karyawan, sizeof(karyawan), 1, tempKaryawan);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&karyawan, sizeof(karyawan), 1, tempKaryawan);
            while (fread(&karyawan, sizeof(karyawan), 1, fileKaryawan) == 1) {
                fwrite(&karyawan, sizeof(karyawan), 1, tempKaryawan);
            }
        }
    } else {
        showMessage("ALERT!", "ID Karyawan tidak ditemukan");
        gotoxy(115+27, 10); printf("%s", "    ");
        goto retype;
    }
    fclose(fileKaryawan);
    fclose(tempKaryawan);
}

void deleteDataKaryawan() {
    int found;
    found = 0;
    char No[10];
    int batasKiri = 5;

    retype:
    cleanKiri();
    cleanKanan();
    readdataKaryawanINJS();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("ID Karyawan : [      ]");
    gotoxy(115+27, 10); getteks(No, 4);

    //Membuka file asli dengan mode rb
    fileKaryawan = fopen("../Database/dat/Karyawan.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempKaryawan = fopen("../Database/Temp/KaryawanTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&karyawan, sizeof(karyawan), 1, fileKaryawan) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(No, karyawan.id) == 0) {
            cleanKiri();
            gotoxy(batasKiri, 5); printf("ID Karyawan");
            gotoxy(batasKiri+50, 5); printf("| %-40s|", karyawan.id);

            gotoxy(batasKiri, 8); printf("Nama Karyawan");
            gotoxy(batasKiri+50, 8); printf("| %-40s|", karyawan.namaKry);

            gotoxy(batasKiri, 11); printf("Tanggal Lahir DD-MM-YYYY");
            gotoxy(batasKiri+50, 11); printf("| %-40s|", karyawan.tglLhr);

            gotoxy(batasKiri, 14); printf("Jabatan");
            gotoxy(batasKiri+50, 14); printf("| %-40s|", karyawan.jabatan);

            gotoxy(batasKiri, 17); printf("No Telepon");
            gotoxy(batasKiri+50, 17); printf("| %-40s|", karyawan.noTLP);

            gotoxy(batasKiri, 20); printf("Alamat");
            gotoxy(batasKiri+50, 20); printf("| %-40s|", karyawan.alamat);

            gotoxy(batasKiri, 23); printf("Gender");
            gotoxy(batasKiri+50, 23); printf("| %-40s|", karyawan.gender);

            gotoxy(batasKiri, 26); printf("Status");
            gotoxy(batasKiri+50, 26); printf("| %-40s|", karyawan.status);
            getchar();
            getchar();
            if (deleteData() == 1) {
                found = 1;
                showMessage("ATTENTION!!", "Data berhasil dihapus!");
                continue;
            } else {
                found = 1;
                fwrite(&karyawan, sizeof(karyawan), 1, tempKaryawan);
            }
        }
            //Jika tidak maka program akan menyalin data dari file asli ke data temporary
        else {
            fwrite(&karyawan, sizeof(karyawan), 1, tempKaryawan);
        }
    }
    if (found == 0) {
        showMessage("ALERT!", "ID Karyawan tidak ditemukan");
        gotoxy(115+27, 10); printf("%s", "    ");
        goto retype;
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileKaryawan);
    fclose(tempKaryawan);
}

void MenuAddKaryawan() {
    system("cls");
    frame();

    int n;
    char Admin[] = "W E L C O M E  A D M I N";
    char space = " ";
    gotoxy(115, 2); SetColorBlock(3,7); printf(" %-35s", Admin);
    gotoxy(115, 41); printf("%38c", space);
    gotoxy(115+12, 5); SetColorBlock(3,7);
    do {
        gotoxy(115+8, 10); printf("Banyaknya data : [   ]");
        gotoxy(115+27, 10); scanf("%d", &n);

        if (n == 0) {
            doaction("KELUAR");
        }
    } while (n != 0);
    inputKaryawan(n);
    system("cls");
    frame();
}

void menuReadKaryawan() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    gotoxy(115, 2); SetColorBlock(3,7); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);
    gotoxy(127, 5); SetColorBlock(3,7);
    gotoxy(123, 35); printf("Press ENTER to next...");
    readdataKaryawanINJS();
    getch();
    if (lihatDetil() == 1) {
        readDetailKaryawan();
    }
    system("cls");
    frame();
}

void menuUpdateKaryawan() {
    //Memanggil prosedur pencarian id kota
    updateKaryawan();
    //Membuka file asli dengan mode wb
    fileKaryawan = fopen("../Database/dat/Karyawan.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempKaryawan = fopen("../Database/Temp/KaryawanTemp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&karyawan, sizeof(karyawan), 1, tempKaryawan) == 1) {
        fwrite(&karyawan, sizeof(karyawan), 1, fileKaryawan);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileKaryawan);
    fclose(tempKaryawan);
    system("cls");
    frame();
}

void menuDeleteKaryawan() {
    //Memanggil prosedur pencarian id kota
    deleteDataKaryawan();
    //Membuka file asli dengan mode wb
    fileKaryawan = fopen("../Database/dat/Karyawan.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempKaryawan = fopen("../Database/Temp/KaryawanTemp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&karyawan, sizeof(karyawan), 1, tempKaryawan)==1) {
        fwrite(&karyawan, sizeof(karyawan), 1, fileKaryawan);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileKaryawan);
    fclose(tempKaryawan);
    system("cls");
    frame();
}



// CRUD Menu
void crudKaryawan() {
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
                case 1: printf("Tambah Data Karyawan"); break;
                case 2: printf("Lihat Data Karyawan"); break;
                case 3: printf("Ubah Data Karyawan"); break;
                case 4: printf("Hapus Data Karyawan"); break;
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
                    cleanKanan();
                    MenuAddKaryawan();
                    break;
                case 2:
                    menuReadKaryawan();
                    break;
                case 3:
                    cleanKanan();
                    menuUpdateKaryawan();
                    break;
                case 4:
                    cleanKanan();
                    menuDeleteKaryawan();
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

#endif //CRUD_KARYAWAN_H
