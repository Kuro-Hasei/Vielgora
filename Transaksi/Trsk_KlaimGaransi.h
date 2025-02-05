#ifndef TRSK_KLAIMGARANSI_H
#define TRSK_KLAIMGARANSI_H

// MAAF KAK UNTUK TRANSAKSI KLAIM GARANSI TIDAK SELESAI DENGAN SEPENUHNYA DI KARENAKAN SAYA BERNIAT
// UNTUK MERUBAH DATANYA AGAR DAPAT LEBIH MASUK DENGAN KODINGAN YANG LAIN
// SEKALI LAGI SAYA MINTA MAAF

void inputKlaimGaransi() {
    system("cls");
    templateUI();
    int lastNumber = 0;
    char lastID[10];

    fileKlaimGaransi = fopen("../Database/dat/KlaimGaransi.dat", "ab+");
    if (fileKlaimGaransi == NULL) {
        perror("Gagal membuka file KlaimGaransi.dat");
        return;
    }

    // Cek ID terakhir transaksi
    FILE *fileCheck = fopen("../Database/dat/KlaimGaransi.dat", "rb");
    if (fileCheck != NULL) {
        while (fread(&klaimGaransi, sizeof(klaimGaransi), 1, fileCheck) == 1) {
            strcpy(lastID, klaimGaransi.idKlaimGaransi);
        }
        fclose(fileCheck);
    }

    // Generate ID transaksi unik
    if (sscanf(lastID, "KG%d", &lastNumber) == 1) {
        lastNumber++;
    } else {
        lastNumber = 1;
    }
    snprintf(klaimGaransi.idKlaimGaransi, sizeof(klaimGaransi.idKlaimGaransi), "KG%d", lastNumber);

    // Input tanggal klaim garansi
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(klaimGaransi.tanggalKlaimGaransi, sizeof(klaimGaransi.tanggalKlaimGaransi), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Input deskripsi masalah
    SetColor(text2);
    gotoxy(5,5);printf("Masukkan deskripsi masalah: ");
    getchar(); // Membersihkan buffer
    gotoxy(5,6); fgets(klaimGaransi.deskripsiMasalah, sizeof(klaimGaransi.deskripsiMasalah), stdin);
    klaimGaransi.deskripsiMasalah[strcspn(klaimGaransi.deskripsiMasalah, "\n")] = 0; // Menghapus newline

    // Simpan data ke file
    fwrite(&klaimGaransi, sizeof(klaimGaransi), 1, fileKlaimGaransi);
    fclose(fileKlaimGaransi);

    cleanKiri();
    SetColor(colorHeadText);
    gotoxy(5,5); printf("Data klaim garansi berhasil disimpan!");
    SetColor(text2);
    gotoxy(5,7); printf("ID Klaim Garansi    : %s", klaimGaransi.idKlaimGaransi);
    gotoxy(5,9); printf("Tanggal Klaim Garansi: %s", klaimGaransi.tanggalKlaimGaransi);
    gotoxy(5,11); printf("Deskripsi Masalah   : %s", klaimGaransi.deskripsiMasalah);
    getchar();
}

void lihatKlaimGaransi() {
    int yTeks = 6;
    int i = 1;

    fileKlaimGaransi = fopen("../Database/dat/KlaimGaransi.dat", "rb");
    if (fileKlaimGaransi == NULL) {
        perror("Gagal membuka file KlaimGaransi.dat");
        return;
    }

    cleanKiri();
    while (fread(&klaimGaransi, sizeof(klaimGaransi), 1, fileKlaimGaransi) == 1) {
        printTable(10, 110, 3, 35);
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(20, 4); printf(" %-15s %-15s %-50s\n", "ID", "Tanggal", "Keluhan");
        gotoxy(20, yTeks); printf(" %-15s %-15s %-50s\n", klaimGaransi.idKlaimGaransi, klaimGaransi.tanggalKlaimGaransi, klaimGaransi.deskripsiMasalah);
        if (i % 35 == 0) {
            getchar();
            cleanKiri();
        }
        i++;
        yTeks++;
    }
    getchar(); getchar();
    cleanKanan();
    fclose(fileKlaimGaransi);
}

void CrudKlaimGaransi() {
    int PosisiX = 135; // Posisi menu di layar
    int PosisiY = 10;
    int jarakMenu = 2; // Jarak antar menu

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 3; // Total jumlah menu
    int key;

    char man[] = "K L A I M  G A R A N S I";
    char space = ' ';

    cleanKanan();
    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        SetColor(colorHeadText);
        gotoxy(PosisiX - 5, 2); printf(" %-37s", man);
        gotoxy(PosisiX - 5, 40); printf("%38c", space);
        SetColor(text2);

        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) { // Tambahkan tanda "<<<" di menu aktif
                gotoxy(PosisiX + 22, PosisiY + (i - 1) * jarakMenu); printf("<<<");
            } else {
                gotoxy(PosisiX + 22, PosisiY + (i - 1) * jarakMenu); printf("   ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + (i - 1) * jarakMenu);
            switch (i) {
                case 1: printf("Klaim Garansi"); break;
                case 2: printf("Lihat Data"); break;
                case 3: printf("Exit"); break;
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
                case 1: inputKlaimGaransi();
                system("cls");
                frame();
                    break;
                case 2: lihatKlaimGaransi();
                system("cls");
                frame();
                    break;
                case 3:
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

#endif //TRSK_KLAIMGARANSI_H
