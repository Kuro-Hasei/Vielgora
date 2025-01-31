#ifndef TRSK_PEMBELIAN_H
#define TRSK_PEMBELIAN_H

void transaksiPembelian() {
    system("cls");

    char idSupplier[10], idProduk[10], idAksesoris[10];
    int jumlah, jumlahAks, pilihan;
    int foundSupplier = 0, foundProduk = 0, foundAksesoris = 0;
    float totalHargaAksessoris = 0;
    float totalHargaProduk = 0;

    int PosisiX = 10, PosisiY = 5;

    // Membuka file Supplier
    fileSupplier = fopen("../Database/dat/Supplier.dat", "rb");
    if (fileSupplier == NULL) {
        perror("Failed to open Supplier.dat");
        return;
    }

    // Membuka file Produk
    fileProduk = fopen("../Database/dat/Produk.dat", "rb");
    if (fileProduk == NULL) {
        perror("Failed to open Produk.dat");
        fclose(fileSupplier);
        return;
    }

    // Membuka file Aksesoris
    fileAksessoris = fopen("../Database/dat/Aksesoris.dat", "rb");
    if (fileAksessoris == NULL) {
        perror("Failed to open Aksesoris.dat");
        fclose(fileSupplier);
        fclose(fileProduk);
        return;
    }

    // Membuka file Pembelian
    filePembelian = fopen("../Database/dat/Pembelian.dat", "ab+");
    if (filePembelian == NULL) {
        perror("Failed to open Pembelian.dat");
        fclose(fileSupplier);
        fclose(fileProduk);
        fclose(fileAksessoris);
        return;
    }

    // Pilihan menu sebelum menginput produk
    gotoxy(PosisiX, PosisiY); printf("Pilih jenis transaksi:");
    gotoxy(PosisiX, PosisiY + 2); printf("1. Penjualan Produk");
    gotoxy(PosisiX, PosisiY + 3); printf("2. Penjualan Aksesoris");
    gotoxy(PosisiX, PosisiY + 5); printf("Masukkan pilihan (1/2): ");
    gotoxy(PosisiX + 25, PosisiY + 5); scanf("%d", &pilihan);

    // Input ID Supplier
    gotoxy(PosisiX, PosisiY + 7); printf("Masukkan ID Supplier: ");
    gotoxy(PosisiX + 30, PosisiY + 7); scanf("%s", idSupplier);

    // Cari supplier berdasarkan ID
    while (fread(&supplier, sizeof(DTSupplier), 1, fileSupplier) == 1) {
        if (strcmp(supplier.idSpl, idSupplier) == 0) {
            foundSupplier = 1;
            break;
        }
    }

    if (!foundSupplier) {
        gotoxy(PosisiX, PosisiY + 9); printf("Supplier dengan ID %s tidak ditemukan!\n", idSupplier);
        fclose(fileSupplier);
        fclose(fileProduk);
        fclose(fileAksessoris);
        fclose(filePembelian);
        return;
    }

    // Menampilkan data supplier
    gotoxy(PosisiX, PosisiY + 9); printf("=== Data Supplier ===");
    gotoxy(PosisiX, PosisiY + 11); printf("ID Supplier : %s", supplier.idSpl);
    gotoxy(PosisiX, PosisiY + 12); printf("Nama        : %s", supplier.namaSpl);
    gotoxy(PosisiX, PosisiY + 13); printf("Alamat      : %s", supplier.alamat);
    gotoxy(PosisiX, PosisiY + 14); printf("No. Telp    : %s", supplier.noTelp);

    if (pilihan == 1) {
        // Input data produk yang akan dibeli
        gotoxy(PosisiX, PosisiY + 16); printf("Masukkan ID Produk yang ingin dibeli: ");
        gotoxy(PosisiX + 40, PosisiY + 16); scanf("%s", idProduk);

        // Cari produk berdasarkan ID
        while (fread(&produk, sizeof(DTProduk), 1, fileProduk) == 1) {
            if (strcmp(produk.idPrd, idProduk) == 0) {
                foundProduk = 1;
                break;
            }
        }

        if (!foundProduk) {
            gotoxy(PosisiX, PosisiY + 18); printf("Produk dengan ID %s tidak ditemukan!\n", idProduk);
            fclose(fileSupplier);
            fclose(fileProduk);
            fclose(fileAksessoris);
            fclose(filePembelian);
            return;
        }

        // Menampilkan data produk
        gotoxy(PosisiX, PosisiY + 18); printf("=== Data Produk ===");
        gotoxy(PosisiX, PosisiY + 20); printf("ID Produk   : %s", produk.idPrd);
        gotoxy(PosisiX, PosisiY + 21); printf("Nama Produk : %s", produk.namaPrd);
        gotoxy(PosisiX, PosisiY + 22); printf("Harga       : RP.%d", produk.harga);

        // Input jumlah produk
        gotoxy(PosisiX, PosisiY + 24); printf("Masukkan jumlah produk yang ingin dibeli: ");
        gotoxy(PosisiX + 45, PosisiY + 24); scanf("%d", &jumlah);

        totalHargaProduk = jumlah * produk.harga;
    } else if (pilihan == 2) {
        // Input data aksesoris yang akan dibeli
        gotoxy(PosisiX, PosisiY + 16); printf("Masukkan ID Aksesoris yang ingin dibeli: ");
        gotoxy(PosisiX + 45, PosisiY + 16); scanf("%s", idAksesoris);

        // Cari aksesoris berdasarkan ID
        while (fread(&aksessoris, sizeof(DTAksessoris), 1, fileAksessoris) == 1) {
            if (strcmp(aksessoris.idAks, idAksesoris) == 0 && strcmp(aksessoris.status, "Tersedia") == 0) {
                foundAksesoris = 1;
                break;
            }
        }

        if (!foundAksesoris) {
            gotoxy(PosisiX, PosisiY + 18); printf("Aksesoris tidak ditemukan atau tidak tersedia.");
            fclose(fileSupplier);
            fclose(fileProduk);
            fclose(fileAksessoris);
            fclose(filePembelian);
            return;
        }

        // Menampilkan data aksesoris
        gotoxy(PosisiX, PosisiY + 18); printf("=== Data Aksesoris ===");
        gotoxy(PosisiX, PosisiY + 20); printf("ID Aksesoris  : %s", aksessoris.idAks);
        gotoxy(PosisiX, PosisiY + 21); printf("Nama Aksesoris: %s", aksessoris.namaAks);
        gotoxy(PosisiX, PosisiY + 22); printf("Harga         : RP. %d", aksessoris.harga);

        // Input jumlah aksesoris
        gotoxy(PosisiX, PosisiY + 24); printf("Masukkan jumlah aksesoris yang ingin dibeli: ");
        gotoxy(PosisiX + 50, PosisiY + 24); scanf("%d", &jumlahAks);

        totalHargaAksessoris = jumlahAks * aksessoris.harga;
    }

    // Generate ID Pembelian
    snprintf(pembelian.idPembelian, sizeof(pembelian.idPembelian), "PB%d", ftell(filePembelian) / sizeof(DTPembelian) + 1);

    // Simpan data pembelian
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(pembelian.tanggalPembelian, sizeof(pembelian.tanggalPembelian), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    pembelian.totalPembelian = (pilihan == 1) ? jumlah : jumlahAks;
    pembelian.totalHarga = totalHargaProduk + totalHargaAksessoris;
    strcpy(pembelian.metodePembayaran, "Cash");

    fwrite(&pembelian, sizeof(DTPembelian), 1, filePembelian);

    gotoxy(PosisiX, PosisiY + 27); printf("Pembelian berhasil dicatat.");

    PosisiX = 40, PosisiY = 10; // Posisi awal cetak struk pembelian

    gotoxy(PosisiX, PosisiY);     printf("=== STRUK PEMBELIAN ===");
    gotoxy(PosisiX, PosisiY + 2); printf("ID Pembelian      : %s", pembelian.idPembelian);
    gotoxy(PosisiX, PosisiY + 3); printf("Tanggal Pembelian : %s", pembelian.tanggalPembelian);
    gotoxy(PosisiX, PosisiY + 4); printf("Supplier          : %s", supplier.namaSpl);
    gotoxy(PosisiX, PosisiY + 4); printf("Produk            : %s", produk.namaPrd);
    gotoxy(PosisiX, PosisiY + 5); printf("Jumlah Barang     : %d", pembelian.totalPembelian);
    gotoxy(PosisiX, PosisiY + 6); printf("Total Harga       : RP. %d", pembelian.totalHarga);
    gotoxy(PosisiX, PosisiY + 7); printf("Metode Pembayaran : %s", pembelian.metodePembayaran);

    fclose(fileSupplier);
    fclose(fileProduk);
    fclose(filePembelian);
}

void historyTransaksi() {
    system("cls");

    int PosisiX = 5, PosisiY = 3; // Posisi awal tampilan history transaksi

    gotoxy(PosisiX, PosisiY);     printf("=== HISTORY TRANSAKSI PEMBELIAN ===");
    gotoxy(PosisiX, PosisiY + 2); printf("ID Pembelian | Tanggal      | Nama Supplier      | Total Pembelian | Total Harga    | Metode Pembayaran");
    gotoxy(PosisiX, PosisiY + 3); printf("--------------------------------------------------------------------------------------------------------");

    filePembelian = fopen("../Database/dat/Pembelian.dat", "rb");
    if (filePembelian == NULL) {
        perror("Failed to open Pembelian.dat");
        return;
    }

    int row = PosisiY + 5; // Posisi awal data transaksi
    while (fread(&pembelian, sizeof(DTPembelian), 1, filePembelian) == 1) {
        gotoxy(PosisiX, row);
        printf("%-13s | %-12s | %-18s | %-15d | RP.%-10d | %-16s",
               pembelian.idPembelian,
               pembelian.tanggalPembelian,
                supplier.namaSpl,   // Langsung panggil nama supplier dari struct pembelian
               pembelian.totalPembelian,
               pembelian.totalHarga,
               pembelian.metodePembayaran);
        row++; // Pindah ke baris berikutnya
    }

    fclose(filePembelian);

    gotoxy(PosisiX, row + 2);
    printf("Tekan sembarang tombol untuk melanjutkan...");
    getchar();
}


void CrudTransaksiPembelian() {
    int pilihan;

    do {
        system("cls");
        printf("Menu Pembelian Barang\n");
        printf("1. Transaksi Pembelian\n");
        printf("2. History Pembelian\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                transaksiPembelian();
                break;
            case 2:
                historyTransaksi();
                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }

        if (pilihan != 0) {
            printf("\nTekan sembarang tombol untuk melanjutkan...");
            getchar(); getchar(); // Untuk menunggu input sebelum kembali ke menu
        }

    } while (pilihan != 0);
}

#endif //TRSK_PEMBELIAN_H
