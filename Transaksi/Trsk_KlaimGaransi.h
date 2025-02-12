#ifndef TRSK_KLAIMGARANSI_H
#define TRSK_KLAIMGARANSI_H


void inputKlaimGaransi() {
    cleanKanan();
    cleanKiri();
    int PosisiX = 130;
    int batasKiri = 5;
    char lastID[10], idPenjualan[10];
    int lastNumber = 0, i = 1, yTeks = 6;
    int foundPenjualan = 0;

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

    filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
    if (filePenjualan == NULL) {
        perror("Gagal membuka file Penjualan.dat");
        return;
    }

    // MENAMPILKAN KE LAYAR ISI DARI FILE
    while (fread(&penjualan, sizeof(penjualan), 1, filePenjualan) == 1) {
        printTable(20, 100, 3, 35);
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(20, 4); printf(" %-10s %-30s %-15s %-15s\n", "ID", "Barang", "Jumlah", "Total");
        char total[20];
        rupiah(penjualan.totalHarga, total);
        gotoxy(20, yTeks); printf(" %-10s %-30s %-15d RP.%-12s\n",
                            penjualan.idPenjualan, penjualan.kategori, penjualan.totalPenjualan, total);
        if (i % 35 == 0) {
            getchar();
            cleanKiri();
        }
        i++;
        yTeks++;
    } getchar();
    cleanKanan();

    // MENUTUP FILE
    fclose(filePenjualan);

    SetColor(text2);
    gotoxy(PosisiX,10); printf("Masukkan ID Penjualan: ");
    gotoxy(PosisiX,11); printf("[       ]");
    gotoxy(PosisiX+2,11); getteks(idPenjualan, 5);

    filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
    // Mencari ID Penjualan
    while (fread(&penjualan, sizeof(penjualan), 1, filePenjualan) == 1) {
        if (strcmp(penjualan.idPenjualan, idPenjualan) == 0) {
            strcpy(klaimGaransi.namaProduk, penjualan.kategori);
            foundPenjualan = 1;
            break;
        }
    } fclose(filePenjualan);

    if (!foundPenjualan) {
        showMessage("ATTENTION", "ID PENJUALAN TIDAK DITEMUKAN");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(klaimGaransi.tanggalKlaimGaransi, sizeof(klaimGaransi.tanggalKlaimGaransi), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Input tanggal klaim garansi
    time_t sekarang;
    time(&sekarang);

    // Parsing tanggal penjualan dari string ke struct tm
    struct tm expire = {0};

    // Debugging: pastikan string tanggal tidak kosong
    if (strlen(penjualan.tanggalPenjualan) == 0) {
        showMessage("ERROR", "Tanggal Penjualan Kosong!");
        return;
    }

    // Parsing tanggal
    int parsed = sscanf(penjualan.tanggalPenjualan, "%d-%d-%d", &expire.tm_mday, &expire.tm_mon, &expire.tm_year);
    if (parsed != 3) {
        showMessage("ERROR", "Format tanggal penjualan salah");
        return;
    }

    // Sesuaikan format struct tm
    expire.tm_year -= 1900; // Tahun dihitung sejak 1900
    expire.tm_mon -= 1;     // Bulan dimulai dari 0
    expire.tm_hour = 0;
    expire.tm_min = 0;
    expire.tm_sec = 0;

    // Validasi rentang nilai
    if (expire.tm_year < 70 || expire.tm_year > 200) {
        showMessage("ERROR", "Tahun tidak valid");
        return;
    }
    if (expire.tm_mon < 0 || expire.tm_mon > 11) {
        showMessage("ERROR", "Bulan tidak valid");
        return;
    }
    if (expire.tm_mday < 1 || expire.tm_mday > 31) {
        showMessage("ERROR", "Hari tidak valid");
        return;
    }

    // Tambahkan durasi garansi dalam bulan
    expire.tm_mon += penjualan.garansi;
    while (expire.tm_mon >= 12) {
        expire.tm_mon -= 12;
        expire.tm_year += 1;
    }

    // Konversi ke time_t
    time_t kadaluarsa = mktime(&expire);
    if (kadaluarsa == -1) {
        showMessage("ERROR", "Gagal menghitung waktu kadaluarsa");
        return;
    }

    // Tampilkan hasil debugging
    /*gotoxy(PosisiX,10); printf("Sekarang: %s", ctime(&sekarang));
    gotoxy(PosisiX,11); printf("Kadaluarsa: %s", ctime(&kadaluarsa));*/

    // Cek apakah garansi masih berlaku
    if (sekarang <= kadaluarsa) {
        strcpy(klaimGaransi.status, "Diterima");
    } else {
        strcpy(klaimGaransi.status, "Ditolak");
    }

    fwrite(&klaimGaransi, sizeof(klaimGaransi), 1, fileKlaimGaransi);

    // Menampilkan struk
    cleanKiri();
    SetColor(colorHeadText);
    gotoxy(batasKiri, 7); printf("=== [ DATA KLAIM GARANSI ] ==============");
    SetColor(text2);
    gotoxy(batasKiri, 10); printf("ID Klaim Garansi");
    gotoxy(batasKiri+50, 10); printf("| %-40s|", klaimGaransi.idKlaimGaransi);

    gotoxy(batasKiri, 12); printf("Nama Barang");
    gotoxy(batasKiri+50, 12); printf("| %-40s|", klaimGaransi.namaProduk);

    gotoxy(batasKiri, 14); printf("Tanggal Klaim");
    gotoxy(batasKiri+50, 14); printf("| %-40s|", klaimGaransi.tanggalKlaimGaransi);

    gotoxy(batasKiri, 16); printf("Status");
    gotoxy(batasKiri+50, 16); printf("| %-40s|", klaimGaransi.status);
    getchar(); getchar();

    fclose(fileKlaimGaransi);
}

void lihatKlaimGaransi() {
    int PosisiX = 130;
    int batasKiri = 5;
    int found = 0;
    char idPenjualanCari[10];
    int yTeks = 0;
    int i = 1;
    int pilihan;

    fileKlaimGaransi = fopen("../Database/dat/KlaimGaransi.dat", "rb");
    if (fileKlaimGaransi == NULL) {
        perror("Gagal membuka file KlaimGaransi.dat");
        return;
    }

    cleanKiri();
    yTeks = 6;
    while (fread(&klaimGaransi, sizeof(klaimGaransi), 1, fileKlaimGaransi) == 1) {
        printTable(20, 100, 3, 35);
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(20, 4); printf(" %-10s %-30s %-25s %-15s\n", "ID", "NAMA", "TANGGAL KLAIM", "STATUS");
        gotoxy(20, yTeks); printf(" %-10s %-30s %-25s %-15s\n", klaimGaransi.idKlaimGaransi, klaimGaransi.namaProduk, klaimGaransi.tanggalKlaimGaransi, klaimGaransi.status);
        if (i % 30 == 0) {
            getchar();
            cleanKiri();
            yTeks = 6;
        }
        i++;
        yTeks++;
    }getchar();
    cleanKanan();
    fclose(fileKlaimGaransi);

    cleanKanan();
    SetColor(text2);
    gotoxy(PosisiX,10); printf("Ingin Lihat Detail? (1 = iya)");
    gotoxy(PosisiX,11); printf("[   ]");
    gotoxy(PosisiX+2,11); getnum(&pilihan, 1);

    if (pilihan == 1) {
        // Buka kembali file untuk mencari transaksi yang sesuai
        fileKlaimGaransi = fopen("../Database/dat/KlaimGaransi.dat", "rb");
        cleanKanan();
        SetColor(text2);
        gotoxy(PosisiX, 10); printf("Masukkan ID Transaksi : [      ]");
        gotoxy(PosisiX+26, 10); getteks(idPenjualanCari, 5);
        if (fileKlaimGaransi == NULL) {
            perror("Failed to open KlaimGaransi.dat");
            return;
        }
    }

    while (fread(&klaimGaransi, sizeof(klaimGaransi), 1, fileKlaimGaransi) == 1) {
        if (strcmp(klaimGaransi.idKlaimGaransi, idPenjualanCari) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fileKlaimGaransi);

    if (!found) {
        showMessage("ATTENTION", "ID Klaim Garansi Tidak DItemukan");
        return;
    }

    // Menampilkan struk
    cleanKiri();
    SetColor(colorHeadText);
    gotoxy(batasKiri, 7); printf("=== [ DATA KLAIM GARANSI ] ==============");
    SetColor(text2);
    gotoxy(batasKiri, 10); printf("ID Klaim Garansi");
    gotoxy(batasKiri+50, 10); printf("| %-40s|", klaimGaransi.idKlaimGaransi);

    gotoxy(batasKiri, 12); printf("Nama Barang");
    gotoxy(batasKiri+50, 12); printf("| %-40s|", klaimGaransi.namaProduk);

    gotoxy(batasKiri, 14); printf("Tanggal Klaim");
    gotoxy(batasKiri+50, 14); printf("| %-40s|", klaimGaransi.tanggalKlaimGaransi);

    gotoxy(batasKiri, 16); printf("Status");
    gotoxy(batasKiri+50, 16); printf("| %-40s|", klaimGaransi.status);
    getchar(); getchar();

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
