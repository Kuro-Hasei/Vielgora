#ifndef TRSK_PENJUALAN_H
#define TRSK_PENJUALAN_H


void transaksiPenjualan() {
    cleanKanan();
    int PosisiX = 130;
    int batasKiri = 5;
    char idItem[10], idDiskon[10], idLayanan[10], idKaryawan[10], lastID[10], idGaransi[10], namaBarang[50];
    int jumlah, jenisPilihan;
    int foundBarang = 0, foundKaryawan = 0;
    int hargaBarang = 0, hargaLayanan = 0, totalDiskon = 0;
    int lastNumber = 0;

    readdataKaryawanINJS();
    SetColor(text2);
    gotoxy(PosisiX,10); printf("Masukkan ID Karyawan: ");
    gotoxy(PosisiX,11); printf("[      ]");
    gotoxy(PosisiX+2,11); getteks(idKaryawan, 4);
    cleanKanan();

    // Buka file karyawan dan cari ID
    fileKaryawan = fopen("../Database/dat/Karyawan.dat", "rb");
    if (fileKaryawan == NULL) {
        perror("Failed to open Karyawan.dat");
        return;
    }

    while (fread(&karyawan, sizeof(karyawan), 1, fileKaryawan) == 1) {
        if (strcmp(karyawan.id, idKaryawan) == 0) {
            foundKaryawan = 1;
            break;
        }
    }

    if (!foundKaryawan) {
        printf("Karyawan dengan ID %s tidak ditemukan!", idKaryawan);
        return;
    }
    fclose(fileKaryawan);

    cleanKiri();
    SetColor(text2);
    gotoxy(PosisiX,10); printf("Pilih jenis barang [   ]");
    gotoxy(PosisiX,11); printf("1. Produk ");
    gotoxy(PosisiX,12); printf("2. Aksesoris ");
    gotoxy(PosisiX+21,10); getnum(&jenisPilihan,1);
    cleanKanan();

    if (jenisPilihan == 1) {
        fileProduk = fopen("../Database/dat/Produk.dat", "rb");
        readdataProduk2();
        if (fileProduk == NULL) {
            perror("Failed to open Produk.dat");
            return;
        }
        fclose(fileProduk);
    } else if (jenisPilihan == 2) {
        fileAksessoris = fopen("../Database/dat/Aksesoris.dat", "rb");
        readdataAksesoris2();
        if (fileAksessoris == NULL) {
            perror("Failed to open Aksessoris.dat");
            return;
        }
        fclose(fileAksessoris);
    } else {
        printf("Pilihan tidak valid!\n");
        return;
    }

    filePenjualan = fopen("../Database/dat/Penjualan.dat", "ab+");
    if (filePenjualan == NULL) {
        perror("Failed to open Penjualan.dat");
        return;
    }

    // Cek ID terakhir transaksi
    FILE *fileCheck = fopen("../Database/dat/Penjualan.dat", "rb");
    if (fileCheck != NULL) {
        while (fread(&penjualan, sizeof(penjualan), 1, fileCheck) == 1) {
            strcpy(lastID, penjualan.idPenjualan);
        }
        fclose(fileCheck);
    }

    // Generate ID transaksi unik
    if (sscanf(lastID, "PJ%d", &lastNumber) == 1) {
        lastNumber++;
    } else {
        lastNumber = 1;
    }
    snprintf(penjualan.idPenjualan, sizeof(penjualan.idPenjualan), "PJ%d", lastNumber);

    SetColor(text2);
    gotoxy(PosisiX,10); printf("Masukkan ID Barang");
    gotoxy(PosisiX,11); printf("[      ]");
    gotoxy(PosisiX+2,11); getteks(idItem, 4);
    cleanKanan();

    if (jenisPilihan == 1) {
        fileProduk = fopen("../Database/dat/Produk.dat", "rb");
        while (fread(&produk, sizeof(produk), 1, fileProduk) == 1) {
            if (strcmp(produk.idPrd, idItem) == 0) {
                foundBarang = 1;
                hargaBarang = produk.harga;
                strcpy(namaBarang, produk.namaPrd); // Simpan nama produk
                break;
            }
        }
        fclose(fileProduk);
    } else {
        fileAksessoris = fopen("../Database/dat/Aksesoris.dat", "rb");
        while (fread(&aksessoris, sizeof(aksessoris), 1, fileAksessoris) == 1) {
            if (strcmp(aksessoris.idAks, idItem) == 0) {
                foundBarang = 2;
                hargaBarang = aksessoris.harga;
                strcpy(namaBarang, aksessoris.namaAks); // Simpan nama aksesoris
                break;
            }
        }
        fclose(fileAksessoris);
    }

    if (!foundBarang) {
        showMessage("ATTENTION","DATA TIDAK DI TEMUKAN");
        return;
    }

    SetColor(text2);
    gotoxy(PosisiX,10); printf("Masukkan jumlah barang");
    gotoxy(PosisiX,11); printf("[   ]");
    gotoxy(PosisiX+2,11); getnum(&jumlah, 1);
    cleanKanan();

    // Cek apakah ada diskon
    fileDiskon = fopen("../Database/dat/Diskon.dat", "rb");
    if (fileDiskon != NULL) {
        cleanKiri();
        readdataDiskon2();
        SetColor(text2);
        gotoxy(PosisiX,10); printf("Masukkan ID Diskon (0 = Tidak Ada)");
        gotoxy(PosisiX,11); printf("[      ]");
        gotoxy(PosisiX+2,11); getteks(idDiskon, 4);
        cleanKanan();
        fileDiskon = fopen("../Database/dat/Diskon.dat", "rb");
        if (strcmp(idDiskon, "0") != 0) {
            while (fread(&diskon, sizeof(diskon), 1, fileDiskon) == 1) {
                if (strcmp(diskon.idDsk, idDiskon) == 0) {
                    totalDiskon = (hargaBarang * jumlah * atoi(diskon.persentase)) / 100;
                    break;
                }
            }
        }
        fclose(fileDiskon);
    }

    // Cek layanan tambahan
    fileLayanan = fopen("../Database/dat/Layanan.dat", "rb");
    if (fileLayanan != NULL) {
        cleanKiri();
        readdataLayanan2();
        SetColor(text2);
        gotoxy(PosisiX,10); printf("Masukkan ID Layanan (0 = Tidak Ada)");
        gotoxy(PosisiX,11); printf("[      ]");
        gotoxy(PosisiX+2,11); getteks(idLayanan, 4);
        cleanKanan();
        fileLayanan = fopen("../Database/dat/Layanan.dat", "rb");
        if (strcmp(idLayanan, "0") != 0) {
            while (fread(&layanan, sizeof(layanan), 1, fileLayanan) == 1) {
                if (strcmp(layanan.idLyn, idLayanan) == 0) {
                    hargaLayanan = layanan.hargaLyn;
                    break;
                }
            }
        }
        fclose(fileLayanan);
    }

    // Cek Garansi
    fileGaransi = fopen("../Database/dat/Garansi.dat", "rb");
    if (fileGaransi != NULL) {
        cleanKiri();
        readdataGaransiINJS();
        SetColor(text2);
        gotoxy(PosisiX,10); printf("Masukkan ID Garansi (0 = Tidak Ada)");
        gotoxy(PosisiX,11); printf("[      ]");
        gotoxy(PosisiX+2,11); getteks(idGaransi, 4);
        cleanKanan();
        fileGaransi = fopen("../Database/dat/Garansi.dat", "rb");
        if (strcmp(idGaransi, "0") != 0) {
            while (fread(&garansi, sizeof(garansi), 1, fileGaransi) == 1) {
                if (strcmp(garansi.idGrns, idGaransi) == 0) {
                    break;
                }
            }
        }
        fclose(fileGaransi);
    }

    // Simpan transaksi
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(penjualan.tanggalPenjualan, sizeof(penjualan.tanggalPenjualan), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    strcpy(penjualan.kategori, namaBarang);
    penjualan.garansi = garansi.durasi;
    penjualan.hargaLayanan = hargaLayanan;
    penjualan.hargaSatuan = hargaBarang;
    penjualan.totalPenjualan = jumlah;
    penjualan.totalPromo = totalDiskon;
    penjualan.totalHarga = (hargaBarang * jumlah) - totalDiskon + hargaLayanan;
    strcpy(penjualan.namaKRY, karyawan.namaKry); // Gunakan nama dari database karyawan
    strcpy(penjualan.Metode, "Cash");

    char hargaSatuan[20], totalHarga[20], diskonPembelian[20], layananPengecekan[20], totalBayar[20];
    int gabunganHargaTotal = penjualan.hargaSatuan * penjualan.totalPenjualan;
    rupiah(penjualan.hargaSatuan, hargaSatuan);
    rupiah(gabunganHargaTotal, totalHarga);
    rupiah(penjualan.totalPromo, diskonPembelian);
    rupiah(penjualan.hargaLayanan, layananPengecekan);
    rupiah(penjualan.totalHarga, totalBayar);

    fwrite(&penjualan, sizeof(penjualan), 1, filePenjualan);

    // Menampilkan struk
    cleanKiri();
    gotoxy(batasKiri, 5); printf("=== [ DATA PENJUALAN ] ==============");
    gotoxy(batasKiri, 8); printf("ID Penjualan");
    gotoxy(batasKiri+50, 8); printf("| %-40s|", penjualan.idPenjualan);

    gotoxy(batasKiri, 10); printf("Tanggal Penjualan");
    gotoxy(batasKiri+50, 10); printf("| %-40s|", penjualan.tanggalPenjualan);

    gotoxy(batasKiri, 12); printf("Barang");
    gotoxy(batasKiri+50, 12); printf("| %-40s|", penjualan.kategori);

    gotoxy(batasKiri, 14); printf("Jumlah");
    gotoxy(batasKiri+50, 14); printf("| %-40d|", penjualan.totalPenjualan);

    gotoxy(batasKiri, 16); printf("Harga Satuan");
    gotoxy(batasKiri+50, 16); printf("| RP.%-37s|", hargaSatuan);

    gotoxy(batasKiri, 18); printf("Total Harga");
    gotoxy(batasKiri+50, 18); printf("| RP.%-37s|", totalHarga);

    gotoxy(batasKiri, 20); printf("Diskon (%s)", diskon.jenisDsk);
    gotoxy(batasKiri+50, 20); printf("| RP.%-37s|", diskonPembelian);

    gotoxy(batasKiri, 22); printf("Layanan (%s)", layanan.jenisLyn);
    gotoxy(batasKiri+50, 22); printf("| RP.%-37s|", layananPengecekan);

    gotoxy(batasKiri, 24); printf("Garansi (%s)", garansi.jenisGrns);
    gotoxy(batasKiri+50, 24); printf("| %d %-38s|", penjualan.garansi, "Tahun");

    gotoxy(batasKiri, 26); printf("Total Bayar");
    gotoxy(batasKiri+50, 26); printf("| RP.%-37s|", totalBayar);

    gotoxy(batasKiri, 28); printf("Karyawan");
    gotoxy(batasKiri+50, 28); printf("| %-40s|", penjualan.namaKRY);

    gotoxy(batasKiri, 30); printf("Metode Pembayaran");
    gotoxy(batasKiri+50, 30); printf("| %-40s|", penjualan.Metode);

    getchar(); getchar();
    fclose(filePenjualan);
}

void displayTransaksiPenjualan() {
    int PosisiX = 130;
    int batasKiri = 5;
    int found = 0;
    char idPenjualanCari[10];
    int yTeks = 6;
    int i = 1;
    int pilihan;

    cleanKiri();
    filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
    if (filePenjualan == NULL) {
        perror("Failed to open Penjualan.dat");
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
    }
    getchar(); getchar();
    cleanKanan();

    // MENUTUP FILE
    fclose(filePenjualan);

    // Pilihan untuk melihat detail transaksi
    cleanKanan();
    SetColor(text2);
    gotoxy(PosisiX,10); printf("Ingin Lihat Detail? (1 = iya)");
    gotoxy(PosisiX,11); printf("[   ]");
    gotoxy(PosisiX+2,11); getnum(&pilihan, 1);

    if (pilihan == 1) {
    // Buka kembali file untuk mencari transaksi yang sesuai
    filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
        cleanKanan();
        SetColor(text2);
        gotoxy(PosisiX, 10); printf("Masukkan ID Penjualan : [     ]");
        gotoxy(PosisiX+26, 10); getteks(idPenjualanCari, 4);
    if (filePenjualan == NULL) {
        perror("Failed to open Penjualan.dat");
        return;
    }

    while (fread(&penjualan, sizeof(penjualan), 1, filePenjualan) == 1) {
        if (strcmp(penjualan.idPenjualan, idPenjualanCari) == 0) {
            found = 1;
            break;
        }
    }
    fclose(filePenjualan);

    if (!found) {
        printf("Transaksi dengan ID %s tidak ditemukan!\n", idPenjualanCari);
        return;
    }

       char hargaSatuan[20], totalHarga[20], diskonPembelian[20], layananPengecekan[20], totalBayar[20];
    int gabunganHargaTotal = penjualan.hargaSatuan * penjualan.totalPenjualan;
    rupiah(penjualan.hargaSatuan, hargaSatuan);
    rupiah(gabunganHargaTotal, totalHarga);
    rupiah(penjualan.totalPromo, diskonPembelian);
    rupiah(penjualan.hargaLayanan, layananPengecekan);
    rupiah(penjualan.totalHarga, totalBayar);

    // Menampilkan struk
    cleanKiri();
    gotoxy(batasKiri, 5); printf("=== [ DATA PENJUALAN ] ==============");
    gotoxy(batasKiri, 8); printf("ID Penjualan");
    gotoxy(batasKiri+50, 8); printf("| %-40s|", penjualan.idPenjualan);

    gotoxy(batasKiri, 10); printf("Tanggal Penjualan");
    gotoxy(batasKiri+50, 10); printf("| %-40s|", penjualan.tanggalPenjualan);

    gotoxy(batasKiri, 12); printf("Barang");
    gotoxy(batasKiri+50, 12); printf("| %-40s|", penjualan.kategori);

    gotoxy(batasKiri, 14); printf("Jumlah");
    gotoxy(batasKiri+50, 14); printf("| %-40d|", penjualan.totalPenjualan);

    gotoxy(batasKiri, 16); printf("Harga Satuan");
    gotoxy(batasKiri+50, 16); printf("| RP.%-37s|", hargaSatuan);

    gotoxy(batasKiri, 18); printf("Total Harga");
    gotoxy(batasKiri+50, 18); printf("| RP.%-37s|", totalHarga);

    gotoxy(batasKiri, 20); printf("Diskon (%s)", diskon.jenisDsk);
    gotoxy(batasKiri+50, 20); printf("| RP.%-37s|", diskonPembelian);

    gotoxy(batasKiri, 22); printf("Layanan (%s)", layanan.jenisLyn);
    gotoxy(batasKiri+50, 22); printf("| RP.%-37s|", layananPengecekan);

    gotoxy(batasKiri, 24); printf("Garansi (%s)", garansi.jenisGrns);
    gotoxy(batasKiri+50, 24); printf("| %d %-38s|", penjualan.garansi, "Tahun");

    gotoxy(batasKiri, 26); printf("Total Bayar");
    gotoxy(batasKiri+50, 26); printf("| RP.%-37s|", totalBayar);

    gotoxy(batasKiri, 28); printf("Karyawan");
    gotoxy(batasKiri+50, 28); printf("| %-40s|", penjualan.namaKRY);

    gotoxy(batasKiri, 30); printf("Metode Pembayaran");
    gotoxy(batasKiri+50, 30); printf("| %-40s|", penjualan.Metode);
        getchar(); getchar();
    }
}


void TransaksiPenjualan() {
    int PosisiX = 135; // Posisi menu di layar
    int PosisiY = 10;
    int jarakMenu = 2; // Jarak antar menu

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 3; // Total jumlah menu
    int key;

    char man[] = "T R A N S A K S I  P E N J U A L A N";
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
                case 1: printf("Tambah Transaksi"); break;
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
                case 1: transaksiPenjualan();
                system("cls");
                frame();
                    break;
                case 2: displayTransaksiPenjualan();
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

#endif //TRSK_PENJUALAN_H
