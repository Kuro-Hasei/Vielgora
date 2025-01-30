#ifndef TRSK_PEMBELIAN_H
#define TRSK_PEMBELIAN_H

void transaksiPembelian() {
    system("cls");

    char idSupplier[10];
    int jumlah;
    int foundSupplier = 0, foundProduk = 0;
    int totalHarga = 0;

    fileSupplier = fopen("../Database/dat/Supplier.dat", "rb");
    if (fileSupplier == NULL) {
        perror("Failed to open Supplier.dat");
        return;
    }

    fileProduk = fopen("../Database/dat/Produk.dat", "rb");
    if (fileProduk == NULL) {
        perror("Failed to open Produk.dat");
        fclose(fileSupplier);
        return;
    }

    filePembelian = fopen("../Database/dat/Pembelian.dat", "ab+");
    if (filePembelian == NULL) {
        perror("Failed to open Pembelian.dat");
        fclose(fileSupplier);
        fclose(fileProduk);
        return;
    }

    // Input ID Supplier
    printf("Masukkan ID Supplier: ");
    scanf("%s", idSupplier);

    // Cari supplier berdasarkan ID
    while (fread(&supplier, sizeof(DTSupplier), 1, fileSupplier) == 1) {
        if (strcmp(supplier.idSpl, idSupplier) == 0) {
            foundSupplier = 1;
            break;
        }
    }

    if (!foundSupplier) {
        printf("Supplier dengan ID %s tidak ditemukan!\n", idSupplier);
        fclose(fileSupplier);
        fclose(fileProduk);
        fclose(filePembelian);
        return;
    }

    printf("\nSupplier Ditemukan:\n");
    printf("ID Supplier: %s\n", supplier.idSpl);
    printf("Nama       : %s\n", supplier.namaSpl);
    printf("Alamat     : %s\n", supplier.alamat);
    printf("No. Telp   : %s\n", supplier.noTelp);

    // Input data produk yang akan dibeli
    char idProduk[10];
    printf("\nMasukkan ID Produk yang ingin dibeli: ");
    scanf("%s", idProduk);

    // Cari produk berdasarkan ID
    while (fread(&produk, sizeof(DTProduk), 1, fileProduk) == 1) {
        if (strcmp(produk.idPrd, idProduk) == 0) {
            foundProduk = 1;
            break;
        }
    }

    if (!foundProduk) {
        printf("Produk dengan ID %s tidak ditemukan!\n", idProduk);
        fclose(fileSupplier);
        fclose(fileProduk);
        fclose(filePembelian);
        return;
    }

    printf("\nProduk Ditemukan:\n");
    printf("ID Produk   : %s\n", produk.idPrd);
    printf("Nama Produk : %s\n", produk.namaPrd);
    printf("Harga       : RP. %d\n", produk.harga);

    // Input jumlah produk yang ingin dibeli
    printf("\nMasukkan jumlah produk yang ingin dibeli: ");
    scanf("%d", &jumlah);

    totalHarga = jumlah * produk.harga;

    // Generate ID Pembelian
    snprintf(pembelian.idPembelian, sizeof(pembelian.idPembelian), "PB%d", ftell(filePembelian) / sizeof(DTPembelian) + 1);

    // Simpan data pembelian
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(pembelian.tanggalPembelian, sizeof(pembelian.tanggalPembelian), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    pembelian.totalPembelian = jumlah;
    pembelian.totalHarga = totalHarga;
    strcpy(pembelian.metodePembayaran, "Cash"); // Untuk contoh, metode pembayaran adalah cash

    fwrite(&pembelian, sizeof(DTPembelian), 1, filePembelian);

    // Cetak struk pembelian
    printf("\n\n=== STRUK PEMBELIAN ===\n");
    printf("ID Pembelian      : %s\n", pembelian.idPembelian);
    printf("Tanggal Pembelian : %s\n", pembelian.tanggalPembelian);
    printf("Supplier          : %s\n", supplier.namaSpl);
    printf("Produk            : %s\n", produk.namaPrd);
    printf("Jumlah            : %d\n", pembelian.totalPembelian);
    printf("Total Harga       : RP. %d\n", pembelian.totalHarga);
    printf("Metode Pembayaran : %s\n", pembelian.metodePembayaran);

    fclose(fileSupplier);
    fclose(fileProduk);
    fclose(filePembelian);
}

void historyTransaksi() {
    system("cls");

    printf("=== HISTORY TRANSAKSI PEMBELIAN ===\n");
    printf("ID Pembelian | Tanggal      | Total Pembelian | Total Harga  | Metode Pembayaran\n");
    printf("-------------------------------------------------------------------------\n");

    filePembelian = fopen("../Database/dat/Pembelian.dat", "rb");
    if (filePembelian == NULL) {
        perror("Failed to open Pembelian.dat");
        return;
    }

    while (fread(&pembelian, sizeof(pembelian), 1, filePembelian) == 1) {
        printf("%-13s | %-12s | %-15d | %-12d | %-16s\n",
               pembelian.idPembelian,
               pembelian.tanggalPembelian,
               pembelian.totalPembelian,
               pembelian.totalHarga,
               pembelian.metodePembayaran);
    }

    fclose(filePembelian);
    printf("\nTekan sembarang tombol untuk melanjutkan...");
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
