#ifndef TRSK_PEMBELIAN_H
#define TRSK_PEMBELIAN_H

void transaksiPembelian() {
    cleanKanan();
    int PosisiX = 130;
    int batasKiri = 5;

    char idSupplier[10], lastID[10], idItem[10], namaBarang[10];
    int jumlah, jenisPilihan;
    int foundSupplier = 0, foundBarang = 0, hargaBarang = 0, lastNumber = 0;;

    readdataSupplierALL();
    SetColor(text2);
    gotoxy(PosisiX,10); printf("Masukkan ID Supplier: ");
    gotoxy(PosisiX,11); printf("[      ]");
    gotoxy(PosisiX+2,11); getteks(idSupplier, 4);
    cleanKanan();

    // Buka file karyawan dan cari ID
    fileSupplier= fopen("../Database/dat/Supplier.dat", "rb");
    if (fileSupplier == NULL) {
        perror("Failed to open Supplier.dat");
        return;
    }

    while (fread(&supplier, sizeof(supplier), 1, fileSupplier) == 1) {
        if (strcmp(supplier.idSpl, idSupplier) == 0) {
            foundSupplier = 1;
            break;
        }
    }

    if (!foundSupplier) {
        showMessage("ATTENTION", "ID TIDAK DI TEMUKAN");
        return;
    }
    fclose(fileSupplier);

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

    filePembelian = fopen("../Database/dat/Pembelian.dat", "ab+");
    if (filePembelian == NULL) {
        perror("Failed to open Pembelian.dat");
        return;
    }

    // Cek ID terakhir transaksi
    FILE *fileCheck = fopen("../Database/dat/Pembelian.dat", "rb");
    if (fileCheck != NULL) {
        while (fread(&pembelian, sizeof(pembelian), 1, fileCheck) == 1) {
            strcpy(lastID, pembelian.idPembelian);
        }
        fclose(fileCheck);
    }

    // Generate ID transaksi unik
    if (sscanf(lastID, "PB%d", &lastNumber) == 1) {
        lastNumber++;
    } else {
        lastNumber = 1;
    }
    snprintf(pembelian.idPembelian, sizeof(pembelian.idPembelian), "PB%d", lastNumber);

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

    // Simpan data pembelian
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(pembelian.tanggalPembelian, sizeof(pembelian.tanggalPembelian), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    strcpy(pembelian.kategori, namaBarang);
    strcpy(pembelian.idSupplier, supplier.idSpl);
    pembelian.hargaSatuan = hargaBarang;
    pembelian.totalPembelian = jumlah;
    pembelian.totalHarga = hargaBarang * jumlah;
    strcpy(pembelian.metodePembayaran, "Cash");

    char hargaSatuan[20], totalHarga[20];
    int gabunganHargaTotal = pembelian.hargaSatuan * pembelian.totalPembelian;
    rupiah(pembelian.hargaSatuan, hargaSatuan);
    rupiah(gabunganHargaTotal, totalHarga);

    fwrite(&pembelian, sizeof(pembelian), 1, filePembelian);

    // Menampilkan struk
    cleanKiri();
    gotoxy(batasKiri, 5); printf("=== [ DATA PEMBELIAN ] ==============");
    gotoxy(batasKiri, 8); printf("ID Pembelian");
    gotoxy(batasKiri+50, 8); printf("| %-40s|", pembelian.idPembelian);

    gotoxy(batasKiri, 10); printf("Tanggal Pembelian");
    gotoxy(batasKiri+50, 10); printf("| %-40s|", pembelian.tanggalPembelian);

    gotoxy(batasKiri, 12); printf("Supplier");
    gotoxy(batasKiri+50, 12); printf("| %-40s|", pembelian.idSupplier);

    gotoxy(batasKiri, 14); printf("Barang");
    gotoxy(batasKiri+50, 14); printf("| %-40s|", pembelian.kategori);

    gotoxy(batasKiri, 16); printf("Jumlah Barang");
    gotoxy(batasKiri+50, 16); printf("| %-40d|", pembelian.totalPembelian);

    gotoxy(batasKiri, 18); printf("Harga Satuan");
    gotoxy(batasKiri+50, 18); printf("| RP.%-37s|", hargaSatuan);

    gotoxy(batasKiri, 20); printf("Total Harga");
    gotoxy(batasKiri+50, 20); printf("| RP.%-37s|", totalHarga);

    gotoxy(batasKiri, 22); printf("Metode Pembayaran");
    gotoxy(batasKiri+50, 22); printf("| %-40s|", pembelian.metodePembayaran);

    getchar(); getchar();
    fclose(filePenjualan);
}

void historyTransaksi() {
    int PosisiX = 130;
    int batasKiri = 5;
    int found = 0;
    char idPenjualanCari[10];
    int yTeks = 6;
    int i = 1;
    int pilihan;

    cleanKiri();
    filePembelian = fopen("../Database/dat/Pembelian.dat", "rb");
    if (filePembelian == NULL) {
        perror("Failed to open Pembelian.dat");
        return;
    }
                // MENAMPILKAN KE LAYAR ISI DARI FILE
    while (fread(&pembelian, sizeof(pembelian), 1, filePembelian) == 1) {
        printTable(20, 100, 3, 35);
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(20, 4); printf(" %-10s %-10s %-30s %-15s %-15s\n", "ID", "Supplier", "Barang", "Jumlah", "Total");
        char total[20];
        rupiah(pembelian.totalHarga, total);
        gotoxy(20, yTeks); printf(" %-10s %-10s %-30s %-15d RP.%-12s\n",
                            pembelian.idPembelian, pembelian.idSupplier, pembelian.kategori, pembelian.totalPembelian, total);
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
    fclose(filePembelian);

    // Pilihan untuk melihat detail transaksi
    cleanKanan();
    SetColor(text2);
    gotoxy(PosisiX,10); printf("Ingin Lihat Detail? (1 = iya)");
    gotoxy(PosisiX,11); printf("[   ]");
    gotoxy(PosisiX+2,11); getnum(&pilihan, 1);

    if (pilihan == 1) {
    // Buka kembali file untuk mencari transaksi yang sesuai
    filePembelian = fopen("../Database/dat/Pembelian.dat", "rb");
        cleanKanan();
        SetColor(text2);
        gotoxy(PosisiX, 10); printf("Masukkan ID Pembelian : [     ]");
        gotoxy(PosisiX+26, 10); getteks(idPenjualanCari, 4);
    if (filePembelian == NULL) {
        perror("Failed to open Pembelian.dat");
        return;
    }

    while (fread(&pembelian, sizeof(pembelian), 1, filePembelian) == 1) {
        if (strcmp(pembelian.idPembelian, idPenjualanCari) == 0) {
            found = 1;
            break;
        }
    }
    fclose(filePembelian);

    if (!found) {
        showMessage("ATTENTION", "TRANSAKSI TIDAK DI TEMUKAN");
        return;
    }

        char hargaSatuan[20], totalHarga[20];
        int gabunganHargaTotal = pembelian.hargaSatuan * pembelian.totalPembelian;
        rupiah(pembelian.hargaSatuan, hargaSatuan);
        rupiah(gabunganHargaTotal, totalHarga);

        fwrite(&pembelian, sizeof(pembelian), 1, filePembelian);

        // Menampilkan struk
        cleanKiri();
        gotoxy(batasKiri, 5); printf("=== [ DATA PEMBELIAN ] ==============");
        gotoxy(batasKiri, 8); printf("ID Pembelian");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", pembelian.idPembelian);

        gotoxy(batasKiri, 10); printf("Tanggal Pembelian");
        gotoxy(batasKiri+50, 10); printf("| %-40s|", pembelian.tanggalPembelian);

        gotoxy(batasKiri, 12); printf("Supplier");
        gotoxy(batasKiri+50, 12); printf("| %-40s|", pembelian.idSupplier);

        gotoxy(batasKiri, 14); printf("Barang");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", pembelian.kategori);

        gotoxy(batasKiri, 16); printf("Jumlah Barang");
        gotoxy(batasKiri+50, 16); printf("| %-40d|", pembelian.totalPembelian);

        gotoxy(batasKiri, 18); printf("Harga Satuan");
        gotoxy(batasKiri+50, 18); printf("| RP.%-37s|", hargaSatuan);

        gotoxy(batasKiri, 20); printf("Total Harga");
        gotoxy(batasKiri+50, 20); printf("| RP.%-37s|", totalHarga);

        gotoxy(batasKiri, 22); printf("Metode Pembayaran");
        gotoxy(batasKiri+50, 22); printf("| %-40s|", pembelian.metodePembayaran);

        getchar(); getchar();
        fclose(filePenjualan);
    }
}


void CrudTransaksiPembelian() {
    int PosisiX = 135; // Posisi menu di layar
    int PosisiY = 10;
    int jarakMenu = 2; // Jarak antar menu

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 3; // Total jumlah menu
    int key;

    char man[] = "T R A N S A K S I  P E M B E L I A N";
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
                case 1: transaksiPembelian();
                system("cls");
                frame();
                    break;
                case 2: historyTransaksi();
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

#endif //TRSK_PEMBELIAN_H
