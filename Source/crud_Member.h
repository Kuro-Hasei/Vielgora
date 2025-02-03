#ifndef CRUD_MEMBER_H
#define CRUD_MEMBER_H

#ifndef CRUD_Member_H
#define CRUD_Member_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"

/*void inputMember();
void viewMember();
void changeMember();
void deleteMember();
void crudMember();*/

/*void inputMember() {
    cleanKiri();
    SetColorBlock(1,7);
    fileMember = fopen(FILE_NAME, "ab");
    if (fileMember == NULL) {
        printf("Gagal membuka file untuk menambahkan data Member.\n");
        return;
    }
    gotoxy(3,3); printf("Masukkan ID Member: "); scanf("%s", &member.id_Member);
    gotoxy(3,4); printf("Masukkan Nama Member: "); getteks(member.nama,50); // Membaca string dengan spasi
    gotoxy(3,5); printf("Masukkan Tanggal Lahir (YYYY-MM-DD):"); getDate(member.tglLhr);
    gotoxy(3,6); printf("Masukkan Alamat: "); getteks(member.alamat,50);
    gotoxy(3,7); printf("Status:"); printf("Aktif");

    member.status = 1;


    fwrite(&member, sizeof(member), 1, fileMember); // Tambahkan data ke file
    fclose(fileMember);
    printf("Data member berhasil ditambahkan!\n");
}

// Lihat Data Karyawan
void viewMember() {
    system("cls");
    templateUI();
    cleanKanan();

    // Awal lokasi tabel
    int startX = 3;   // Posisi awal kolom
    int startY = 3;   // Posisi awal baris
    int currentY = startY; // Posisi baris saat ini
    SetColorBlock(1,7);

    // Header tabel
    gotoxy(startX, currentY);
    printf("+----+------------------+------------+----------------------+--------------------+------------------+----------------+---------+");
    currentY++;
    gotoxy(startX, currentY);
    printf("| ID Member | Nama Member        | Tgl Lahir   | Alamat          | Status  |");
    currentY++;
    gotoxy(startX, currentY);
    printf("+----+------------------+------------+----------------------+--------------------+------------------+----------------+---------+");
    currentY++;

    // Membaca data dari file
    FILE *file = fopen(FILE_NAME, "rb"); // Buka dengan mode baca biner
    if (file == NULL) {
        gotoxy(startX, currentY);
        printf("Gagal membuka file untuk membaca data Member. File mungkin belum ada.");
        return;
    }

    // Iterasi data dalam file
    while (fread(&member, sizeof(member), 1, file) == 1) {
        gotoxy(startX, currentY);
        printf("| %-9s | %-18s | %-11s | %-16s| %-6s  |",
               member.id_Member,
               member.nama,
               member.tglLhr,
               member.alamat,
               member.status == 1 ? "Aktif" : "Nonaktif");
        currentY++;
    }

    // Baris akhir tabel
    gotoxy(startX, currentY);
    printf("+----+------------------+------------+----------------------+--------------------+------------------+----------------+---------+");
    currentY++;

    // Tunggu sebelum keluar
    gotoxy(startX, currentY);
    printf("Tekan tombol apa saja untuk kembali...");
    getchar(); // Menunggu input
    getchar();

    fclose(file);
}

void changeMember() {
    system("cls");
    frame();
    cleanKiri();
    gotoxy(3,2);

    fileMember = fopen(FILE_NAME, "rb+"); // Buka dengan mode baca-tulis biner
    if (fileMember == NULL) {
        printf("Gagal membuka file untuk mengubah data.\n");
        return;
    }

    char id[10], found = 0;
    printf("Masukkan ID Member yang ingin diubah: ");
    scanf("%s", &id);

    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        if (strcpy(member.id_Member, id)) {
            found = 1;
            gotoxy(3,3);printf("Data lama akan diubah.\n");
            gotoxy(3,4);printf("Masukkan Nama baru: "); scanf(" %[^\n]", member.nama);
            gotoxy(3,5);printf("Masukkan Tanggal Lahir baru (YYYY-MM-DD): "); getDate(member.tglLhr);
            gotoxy(3,8);printf("Masukkan Alamat baru: "); scanf(" %[^\n]", member.alamat);
            gotoxy(3,10);printf("Masukkan Status baru (1 untuk Aktif, 0 untuk Nonaktif): "); scanf("%d", &member.status);

            fseek(fileMember, -sizeof(DTMember), SEEK_CUR);
            fwrite(&member, sizeof(DTMember), 1, fileMember);
            printf("Data Member berhasil diubah!\n");
            break;
        }
    }

    if (!found) {
        printf("ID Member tidak ditemukan.\n");
    }
    fclose(fileMember);
}

void deleteMember() {
    system("cls");
    frame();
    gotoxy(3,3);

    fileMember = fopen(FILE_NAME, "rb");
    if (fileMember == NULL) {
        printf("Gagal membuka file untuk menghapus data.\n");
        return;
    }

    tempMember = fopen("Temp.dat", "wb");
    if (tempMember == NULL) {
        printf("Gagal membuat file sementara.\n");
        fclose(fileMember);
        return;
    }

    char id[10], found = 0;
    printf("Masukkan ID Member yang ingin dihapus: ");
    scanf("%s", &id);

    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        if (strcpy(member.id_Member, id)) {
            found = 1;
        } else {
            fwrite(&member, sizeof(member), 1, tempMember);
        }
    }

    fclose(fileMember);
    fclose(tempMember);

    if (found) {
        remove(FILE_NAME);
        rename("Temp.dat", FILE_NAME);
        printf("Data Member berhasil dihapus.\n");
    } else {
        remove("Temp.dat");
        printf("ID Member tidak ditemukan.\n");
    }
}

void crudMember() {
    int PosisiX = 115;
    int PosisiY = 10;

    int menu = 1;
    int totalMenu = 5;
    int key;

    do {
        system("cls");
        frame();


        gotoxy(PosisiX, PosisiY - 2); printf("---- Menu Pilihan ----\n");
        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) {
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("<<");
            } else {
                gotoxy(PosisiX + 22, PosisiY + i - 1); printf("  ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + i - 1);
            switch (i) {
                case 1: printf("Tambah Data Member"); break;
                case 2: printf("Lihat Data Member"); break;
                case 3: printf("Ubah Data Member"); break;
                case 4: printf("Hapus Data Member"); break;
                case 5: printf("EXIT PROGRAM"); break;
            }
        }


        key = getch();
        if (key == 224) {
            key = getch();
            if (key == 72 && menu > 1) {
                menu--;
            } else if (key == 80 && menu < totalMenu) {
                menu++;
            }
        } else if (key == 13) {
            switch (menu) {
                case 1: inputMember(); break;
                case 2: viewMember(); break;
                case 3: changeMember(); break;
                case 4: deleteMember(); break;
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

void inputMember(int n) {
    system("cls");
    templateUI();
    cleanKiri();

    char kodeMember[] = {"MBR"};
    int idTerakhir = 0;
    int batasKiri = 3;

    fileMember = fopen("../Database/dat/Member.dat", "ab+");
    if (fileMember == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(member.id_Member, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColorBlock(3,7);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        // Generate ID otomatis
        snprintf(member.id_Member, sizeof(member.id_Member), "%s%i", kodeMember, i);

        // Menampilkan Teks Untuk Input
        SetColorBlock(3,7);
        gotoxy(batasKiri, 3); printf("=MASUKKAN DATA Member===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 5); printf("ID Member");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", member.id_Member);

        gotoxy(batasKiri, 8); printf("Nama Member");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", " ");

        gotoxy(batasKiri, 11); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", " ");

        gotoxy(batasKiri, 14); printf("Alamat");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", " ");

        gotoxy(batasKiri, 17); printf("No Telepon");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", " ");

        gotoxy(batasKiri, 20); printf("Riwayat Pembelian");
        gotoxy(batasKiri+50, 20); printf("| %-40s|", " ");

        gotoxy(batasKiri, 23); printf("Status");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", "Aktif ");

        gotoxy(55, 8); getteks(member.nama, 50);

        gotoxy(55, 11); getDate(member.tglLhr);

        gotoxy(55, 14); getteks(member.alamat, 15);

        gotoxy(55, 17); getno(member.noTelp, 13);

        gotoxy(55, 20); getteks(member.RP, 20);

        strcpy(member.status, "Aktif");

        fwrite(&member, sizeof(member), 1, fileMember);
    }
    fclose(fileMember);
}

void readdataMemberINJS() {
    cleanKiri();

    char id[] = "ID";
    char nama[] = "NAMA";
    char status[] = "STATUS";

    int i = 1;
    int yTeks = 4;

    fileMember = fopen("../Database/dat/Member.dat", "rb");
    if (fileMember == NULL) {
        perror("Failed to open file");
        return;
    }

    printTable(3, 110, 1, 42);
    gotoxy(0, 3);
    SetColor(colorScText);
    gotoxy(3, 2);
    printf(" %-8s   %-25s   %-20s \n", id, nama, status);

    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        gotoxy(3, yTeks);
        printf(" %-8s   %-25s   %-20s \n", member.id_Member, member.nama,member.status);

        if (i % 40 == 0) {
            printf("\n--- Press any key to continue ---\n");
            getchar(); // Wait for user input
            cleanKiri();
            yTeks = 4; // Reset yTeks after clearing screen
            gotoxy(3, 2);
            printf(" %-8s   %-25s   %-20s \n", member.id_Member, member.nama,member.status);
        }
        i++;
        yTeks++;
    }
    fclose(fileMember);
}

void readDetailMember() {
    int batasKiri = 3;
    char idMmbr[10];
    cleanKanan();

    retype:
    SetColor(colorHeadText);
    gotoxy(130, 2); printf("   %-35s", "W E L C O M E  A D M I N");
    gotoxy(130, 41); printf("%38c", ' ');
    SetColor(text2);
    gotoxy(135, 13); printf("Masukkan ID Member");
    gotoxy(135, 15); printf("[        ]");

    readdataMemberINJS();

    gotoxy(137, 15); getteks(idMmbr, 4);
    cleanKiri();

    int i = 1;
    int found = 0;
    //Membuka file dengan mode rb
    fileMember = fopen("../Database/dat/Member.dat", "rb");

    gotoxy(0, 3); SetColorBlock(3,7);
    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        if (strcmp(idMmbr, member.id_Member) == 0) {
            found = 1;
            break;
        }
        i++;
    }

    if (found == 1) {
        cleanKiri();
        gotoxy(batasKiri, 5); printf("ID Member");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", member.id_Member);

        gotoxy(batasKiri, 8); printf("Nama Member");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", member.nama);

        gotoxy(batasKiri, 11); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", member.tglLhr);

        gotoxy(batasKiri, 14); printf("Alamat");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", member.alamat);

        gotoxy(batasKiri, 17); printf("No Telepon");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", member.noTelp);

        gotoxy(batasKiri, 20); printf("Riwayat Pembelian");
        gotoxy(batasKiri+50, 20); printf("| %-40s|", member.RP);

        gotoxy(batasKiri, 23); printf("Status");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", member.status);
    } else {
        showMessage("ALERT!", "ID Member tidak ditemukan");
        gotoxy(131, 15); printf("       ");
        goto retype;
    }
    gotoxy(123, 30); printf("Press ENTER to back...");
    getchar();
    //Menutup file setelah membaca
    fclose(fileMember);
    getchar();
}

void updateMember() {
    int found;
    found = 0;
    char No[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("ID Member : [      ]");
    gotoxy(115+27, 10); getteks(No, 4);
    /*gotoxy(115+8, 10); printf("ID Karyawan : [   ]");
    gotoxy(row+17, 15); getteks(No, 6);*/

    //Membuka file asli dengan mode rb
    fileMember = fopen("../Database/dat/Member.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempMember = fopen("../Database/Temp/MemberTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(No, member.id_Member) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&member, sizeof(member), 1, tempMember);
        }
    }

    //Proses lanjutan setelah data ditemukan
    if (found == 1) {
        cleanKiri();
        gotoxy(batasKiri, 3); printf("ID Member");
        gotoxy(batasKiri+50, 3); printf("| %-40s|", member.id_Member);

        gotoxy(batasKiri, 4); printf("Nama Member");
        gotoxy(batasKiri+50, 4); printf("| %-40s|", member.nama);

        gotoxy(batasKiri, 5); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", member.tglLhr);

        gotoxy(batasKiri, 6); printf("Alamat");
        gotoxy(batasKiri+50, 6); printf("| %-40s|", member.alamat);

        gotoxy(batasKiri, 7); printf("No Telepon");
        gotoxy(batasKiri+50, 7); printf("| %-40s|", member.noTelp);

        gotoxy(batasKiri, 8); printf("Riwayat Pembelian");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", member.RP);

        gotoxy(batasKiri, 9); printf("Status");
        gotoxy(batasKiri+50, 9); printf("| %-40s|", member.status);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColorBlock(3,7);
        gotoxy(batasKiri, 13); printf("=MASUKKAN DATA YANG BARU===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 15); printf("ID Member");
        gotoxy(batasKiri+50, 15); printf("| %-40s|", member.id_Member);

        gotoxy(batasKiri, 17); printf("Nama Member");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", " ");

        gotoxy(batasKiri, 19); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 19); printf("| %-40s|", " ");

        gotoxy(batasKiri, 21); printf("Alamat");
        gotoxy(batasKiri+50, 21); printf("| %-40s|", " ");

        gotoxy(batasKiri, 23); printf("No Telepon");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", " ");

        gotoxy(batasKiri, 25); printf("Riwayat Pembelian");
        gotoxy(batasKiri+50, 25); printf("| %-40s|", " ");

        gotoxy(batasKiri, 27); printf("Status");
        gotoxy(batasKiri+50, 27); printf("| %-40s|", " ");

        char namTemp[50];
        gotoxy(57, 17); getteks(namTemp, 50);

        char tglTemp[12];
        gotoxy(57, 19); getDate(tglTemp);

        char alamatTemp[35];
        gotoxy(57, 21); getteks(alamatTemp, 35);


        char tlpTemp[15];
        gotoxy(57, 23); getno(tlpTemp, 13);

        char RpTemp[35];
        gotoxy(57, 25); getteks(RpTemp, 35);

        char statusTemp[10];
        gotoxy(57, 29); getteks(statusTemp, 10);
        int validStatus = 0;
        while (!validStatus) {
            gotoxy(57, 27); getteks(statusTemp, 1);

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
            strcpy(member.id_Member, No);
            strcpy(member.nama, namTemp);
            strcpy(member.tglLhr, tglTemp);
            strcpy(member.alamat, alamatTemp);
            strcpy(member.noTelp, tlpTemp);
            strcpy(member.RP, RpTemp);
            strcpy(member.status, statusTemp);
            fwrite(&member, sizeof(member), 1, tempMember);
            while (fread(&member, sizeof(member), 1, fileMember) == 1) {
                fwrite(&member, sizeof(member), 1, tempMember);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&member, sizeof(member), 1, tempMember);
            while (fread(&member, sizeof(member), 1, fileMember) == 1) {
                fwrite(&member, sizeof(member), 1, tempMember);
            }
        }
    } else {
        showMessage("ALERT!", "ID Member tidak ditemukan");
        gotoxy(115+27, 10); printf("%s", "    ");
        goto retype;
    }
    fclose(fileMember);
    fclose(tempMember);
}

void deleteDataMember() {
    int found;
    found = 0;
    char No[10];
    int batasKiri = 5;

    retype:
    cleanKiri();
    cleanKanan();
    readdataMemberINJS();
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("ID Member : [      ]");
    gotoxy(115+27, 10); getteks(No, 4);

    //Membuka file asli dengan mode rb
    fileMember = fopen("../Database/dat/Member.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempMember = fopen("../Database/Temp/MemberTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(No, member.id_Member) == 0) {
            cleanKiri();
            gotoxy(batasKiri, 5); printf("ID member");
            gotoxy(batasKiri+50, 5); printf("| %-40s|", member.id_Member);

            gotoxy(batasKiri, 8); printf("Nama Member");
            gotoxy(batasKiri+50, 8); printf("| %-40s|", member.nama);

            gotoxy(batasKiri, 11); printf("Tanggal Lahir DD-MM-YYYY");
            gotoxy(batasKiri+50, 11); printf("| %-40s|", member.tglLhr);

            gotoxy(batasKiri, 14); printf("Alamat");
            gotoxy(batasKiri+50, 14); printf("| %-40s|", member.alamat);

            gotoxy(batasKiri, 17); printf("No Telepon");
            gotoxy(batasKiri+50, 17); printf("| %-40s|", member.noTelp);

            gotoxy(batasKiri, 17); printf("Riwayat Pembelian");
            gotoxy(batasKiri+50, 20); printf("| %-40s|", member.RP);

            gotoxy(batasKiri, 20); printf("Status");
            gotoxy(batasKiri+50, 23); printf("| %-40s|", member.status);
            getchar();
            getchar();
            if (deleteData() == 1) {
                found = 1;
                showMessage("ATTENTION!!", "Data berhasil dihapus!");
                continue;
            } else {
                found = 1;
                fwrite(&member, sizeof(member), 1, tempMember);
            }
        }
            //Jika tidak maka program akan menyalin data dari file asli ke data temporary
        else {
            fwrite(&member, sizeof(member), 1, tempMember);
        }
    }
    if (found == 0) {
        showMessage("ALERT!", "ID Member tidak ditemukan");
        gotoxy(115+27, 10); printf("%s", "    ");
        goto retype;
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileMember);
    fclose(tempMember);
}

void MenuAddMember() {
    system("cls");
    frame();

    int n;
    char Admin[] = "W E L C O M E  A D M I N";
    char space = " ";
    gotoxy(115, 2); SetColorBlock(3,7);printf(" %-35s", Admin);
    gotoxy(115, 41); printf("%38c", space);
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("Banyaknya data : [   ]");
    gotoxy(115+27, 10); scanf("%d", &n);

    inputMember(n);
}

void menuReadMember() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    gotoxy(115, 2); SetColorBlock(3,7); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);
    gotoxy(127, 5); SetColorBlock(3,7);
    gotoxy(123, 35); printf("Press ENTER to next...");
    readdataMemberINJS();
    getch();
    if (lihatDetil() == 1) {
        readDetailMember();
    }
}

void menuUpdateMember() {
    //Memanggil prosedur pencarian id kota
    updateMember();
    //Membuka file asli dengan mode wb
    fileMember = fopen("../Database/dat/Member.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempMember = fopen("../Database/Temp/MemberTemp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&member, sizeof(member), 1, tempMember) == 1) {
        fwrite(&member, sizeof(member), 1, fileMember);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileMember);
    fclose(tempMember);
}

void menuDeleteMember() {
    //Memanggil prosedur pencarian id kota
    deleteDataMember();
    //Membuka file asli dengan mode wb
    fileMember = fopen("../Database/dat/Member.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempMember = fopen("../Database/Temp/MemberTemp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&member, sizeof(member), 1, tempMember)==1) {
        fwrite(&member, sizeof(member), 1, fileMember);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileMember);
    fclose(tempMember);
}

void crudMember() {
    int PosisiX = 115; // Posisi menu di layar
    int PosisiY = 10;

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 5; // Total jumlah menu
    int key;

    do {
        system("cls");
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
                case 1: printf("Tambah Data Member"); break;
                case 2: printf("Lihat Data Member"); break;
                case 3: printf("Ubah Data Member"); break;
                case 4: printf("Hapus Data Member"); break;
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
                    MenuAddMember();
                    break;
                case 2:
                    menuReadMember();
                    break;
                case 3:
                    cleanKanan();
                    menuUpdateMember();
                    break;
                case 4:
                    menuDeleteMember();
                    break;
                case 5:
                    gotoxy(PosisiX, PosisiY + totalMenu + 2);
                    return;
                default:
                    gotoxy(PosisiX, PosisiY + totalMenu + 2);
                    printf("Input tidak valid. Silakan coba lagi.\n");
            }
        }
    } while (1);
}

#endif
#endif //CRUD_MEMBER_H
