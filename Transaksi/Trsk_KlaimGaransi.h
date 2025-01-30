#ifndef TRSK_KLAIMGARANSI_H
#define TRSK_KLAIMGARANSI_H

#include <stdio.h>
#include <stdlib.h>

#include "Trsk_Penjualan.h"
#include "../Source/Deklarasi.h"

void inputKlaimGaransi() {
    fileKlaimGaransi = fopen("../Database/dat/KlaimGaransi.dat", "ab+");
    if (fileKlaimGaransi == NULL) {
        perror("Gagal membuka file KlaimGaransi.dat");
        return;
    }

    // Generate ID Klaim Garansi
    snprintf(klaimGaransi.idKlaimGaransi, sizeof(klaimGaransi.idKlaimGaransi), "KG%d", (int)(ftell(fileKlaimGaransi) / sizeof(DTKlaimGaransi) + 1));

    // Input tanggal klaim garansi
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(klaimGaransi.tanggalKlaimGaransi, sizeof(klaimGaransi.tanggalKlaimGaransi), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Input deskripsi masalah
    printf("Masukkan deskripsi masalah: ");
    getchar(); // Membersihkan buffer
    fgets(klaimGaransi.deskripsiMasalah, sizeof(klaimGaransi.deskripsiMasalah), stdin);
    klaimGaransi.deskripsiMasalah[strcspn(klaimGaransi.deskripsiMasalah, "\n")] = 0; // Menghapus newline

    // Simpan data ke file
    fwrite(&klaimGaransi, sizeof(DTKlaimGaransi), 1, fileKlaimGaransi);
    fclose(fileKlaimGaransi);

    printf("\nData klaim garansi berhasil disimpan!\n");
    printf("ID Klaim Garansi    : %s\n", klaimGaransi.idKlaimGaransi);
    printf("Tanggal Klaim Garansi: %s\n", klaimGaransi.tanggalKlaimGaransi);
    printf("Deskripsi Masalah   : %s\n", klaimGaransi.deskripsiMasalah);
}

void lihatKlaimGaransi() {
    fileKlaimGaransi = fopen("../Database/dat/KlaimGaransi.dat", "rb");
    if (fileKlaimGaransi == NULL) {
        perror("Gagal membuka file KlaimGaransi.dat");
        return;
    }

    printf("\n=== DATA KLAIM GARANSI ===\n");
    printf("%-15s %-15s %-100s\n", "ID Klaim", "Tanggal", "Deskripsi Masalah");
    printf("-------------------------------------------------------------------------------------\n");

    while (fread(&klaimGaransi, sizeof(DTKlaimGaransi), 1, fileKlaimGaransi) == 1) {
        printf("%-15s %-15s %-100s\n", klaimGaransi.idKlaimGaransi, klaimGaransi.tanggalKlaimGaransi, klaimGaransi.deskripsiMasalah);
    }

    fclose(fileKlaimGaransi);
}

void CrudKlaimGaransi() {
    int pilihan;

    do {
        system("cls");
        printf("Menu Klaim Garansi\n");
        printf("1. Klaim Garansi\n");
        printf("2. Lihat Data\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                inputKlaimGaransi();
            break;
            case 2:
                lihatKlaimGaransi();
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

#endif //TRSK_KLAIMGARANSI_H
