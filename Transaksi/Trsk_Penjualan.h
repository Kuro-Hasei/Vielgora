#ifndef TRSK_PENJUALAN_H
#define TRSK_PENJUALAN_H
#include <stdio.h>
#include <stdlib.h>

#include "../Source/Deklarasi.h"

/*==================== FUNCTION IMPLEMENTATIONS ====================*/

void transaksiPenjualan() {
    system("cls");
    char idProduk[10];
    int jumlah;
    int foundProduk = 0;

    fileProduk = fopen("../Database/dat/Produk.dat", "rb");
    if (fileProduk == NULL) {
        perror("Failed to open Produk.dat");
        return;
    }

    filePenjualan = fopen("../Database/dat/Penjualan.dat", "ab+");
    if (filePenjualan == NULL) {
        perror("Failed to open Penjualan.dat");
        fclose(fileProduk);
        return;
    }

    printf("Masukkan ID Produk yang ingin dijual: ");
    scanf("%s", idProduk);

    while (fread(&produk, sizeof(DTProduk), 1, fileProduk) == 1) {
        if (strcmp(produk.idPrd, idProduk) == 0) {
            foundProduk = 1;
            break;
        }
    }

    if (!foundProduk) {
        printf("Produk dengan ID %s tidak ditemukan!\n", idProduk);
        fclose(fileProduk);
        fclose(filePenjualan);
        return;
    }

    printf("\nProduk Ditemukan:\n");
    printf("ID Produk   : %s\n", produk.idPrd);
    printf("Nama Produk : %s\n", produk.namaPrd);
    printf("Harga       : RP. %d\n", produk.harga);

    printf("\nMasukkan jumlah produk yang terjual: ");
    scanf("%d", &jumlah);

    snprintf(penjualan.idPenjualan, sizeof(penjualan.idPenjualan), "PJ%d", ftell(filePenjualan) / sizeof(DTPenjualan) + 1);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(penjualan.tanggalPenjualan, sizeof(penjualan.tanggalPenjualan), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    penjualan.jenisTerjual = 1; // Contoh: 1 jenis produk terjual
    penjualan.totalPenjualan = jumlah;
    penjualan.totalPromo = 0; // Contoh: Tidak ada promo
    penjualan.totalHarga = jumlah * produk.harga;
    strcpy(penjualan.namaKRY, "Karyawan A"); // Contoh nama karyawan
    strcpy(penjualan.Metode, "Cash"); // Contoh metode pembayaran

    fwrite(&penjualan, sizeof(DTPenjualan), 1, filePenjualan);

    printf("\n\n=== STRUK PENJUALAN ===\n");
    printf("ID Penjualan      : %s\n", penjualan.idPenjualan);
    printf("Tanggal Penjualan : %s\n", penjualan.tanggalPenjualan);
    printf("Produk            : %s\n", produk.namaPrd);
    printf("Jumlah            : %d\n", penjualan.totalPenjualan);
    printf("Total Harga       : RP. %d\n", penjualan.totalHarga);
    printf("Karyawan          : %s\n", penjualan.namaKRY);
    printf("Metode Pembayaran : %s\n", penjualan.Metode);

    fclose(fileProduk);
    fclose(filePenjualan);
}

void displayTransaksiPenjualan() {
    system("cls");
    int yTeks = 4;

    filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
    if (filePenjualan == NULL) {
        perror("Failed to open Penjualan.dat");
        return;
    }

    printf("%-10s %-15s %-15s %-15s %-15s %-15s %-15s\n", "ID", "Tanggal", "Jenis", "Total", "Promo", "Harga", "Metode");

    while (fread(&penjualan, sizeof(DTPenjualan), 1, filePenjualan) == 1) {
        printf("%-10s %-15s %-15d %-15d %-15d %-15d %-15s\n",
               penjualan.idPenjualan, penjualan.tanggalPenjualan, penjualan.jenisTerjual, penjualan.totalPenjualan,
               penjualan.totalPromo, penjualan.totalHarga, penjualan.Metode);
        yTeks++;
    }

    fclose(filePenjualan);
}

void CrudTransaksiPenjualan() {
    int pilihan;

    do {
        system("cls");
        printf("Menu Penjualan Barang\n");
        printf("1. Transaksi Penjualan\n");
        printf("2. Display Penjualan\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                transaksiPenjualan();
            break;
            case 2:
                displayTransaksiPenjualan();
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

#endif //TRSK_PENJUALAN_H
