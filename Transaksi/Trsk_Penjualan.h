#ifndef TRSK_PENJUALAN_H
#define TRSK_PENJUALAN_H

#include "../Source/Deklarasi.h"

void transaksiPenjualan() {
    system("cls");
    char idItem[10], idDiskon[10], idLayanan[10], idKaryawan[10], lastID[10];
    int jumlah, jenisPilihan;
    int foundItem = 0, foundDiskon = 0, foundLayanan = 0, foundKaryawan = 0;
    int hargaBarang = 0, hargaLayanan = 0, totalDiskon = 0;
    int lastNumber = 0;

    printf("Masukkan ID Karyawan yang melakukan transaksi: ");
    scanf("%s", idKaryawan);

    // Buka file karyawan dan cari ID
    fileKaryawan = fopen("../Database/dat/Karyawan.dat", "rb");
    if (fileKaryawan == NULL) {
        perror("Failed to open Karyawan.dat");
        return;
    }

    while (fread(&karyawan, sizeof(DTKaryawan), 1, fileKaryawan) == 1) {
        if (strcmp(karyawan.id, idKaryawan) == 0) {
            foundKaryawan = 1;
            break;
        }
    }
    fclose(fileKaryawan);

    if (!foundKaryawan) {
        printf("Karyawan dengan ID %s tidak ditemukan!\n", idKaryawan);
        return;
    }

    printf("Pilih jenis barang yang ingin dijual:\n");
    printf("1. Produk\n");
    printf("2. Aksesoris\n");
    printf("Pilihan: ");
    scanf("%d", &jenisPilihan);

    if (jenisPilihan == 1) {
        fileProduk = fopen("../Database/dat/Produk.dat", "rb");
        if (fileProduk == NULL) {
            perror("Failed to open Produk.dat");
            return;
        }
    } else if (jenisPilihan == 2) {
        fileAksessoris = fopen("../Database/dat/Aksesoris.dat", "rb");
        if (fileAksessoris == NULL) {
            perror("Failed to open Aksessoris.dat");
            return;
        }
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
        while (fread(&penjualan, sizeof(DTPenjualan), 1, fileCheck) == 1) {
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

    printf("Masukkan ID barang yang ingin dijual: ");
    scanf("%s", idItem);

    if (jenisPilihan == 1) {
        while (fread(&produk, sizeof(DTProduk), 1, fileProduk) == 1) {
            if (strcmp(produk.idPrd, idItem) == 0) {
                foundItem = 1;
                hargaBarang = produk.harga;
                break;
            }
        }
    } else {
        while (fread(&aksessoris, sizeof(DTAksessoris), 1, fileAksessoris) == 1) {
            if (strcmp(aksessoris.idAks, idItem) == 0) {
                foundItem = 2;
                hargaBarang = aksessoris.harga;
                break;
            }
        }
    }

    if (!foundItem) {
        printf("Barang dengan ID %s tidak ditemukan!\n", idItem);
        return;
    }

    printf("\nMasukkan jumlah barang yang terjual: ");
    scanf("%d", &jumlah);

    // Cek apakah ada diskon
    fileDiskon = fopen("../Database/dat/Diskon.dat", "rb");
    if (fileDiskon != NULL) {
        printf("Masukkan ID Diskon (jika ada, jika tidak ketik '0'): ");
        scanf("%s", idDiskon);
        if (strcmp(idDiskon, "0") != 0) {
            while (fread(&diskon, sizeof(DTDiskon), 1, fileDiskon) == 1) {
                if (strcmp(diskon.idDsk, idDiskon) == 0) {
                    foundDiskon = 1;
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
        printf("Masukkan ID Layanan (jika ada, jika tidak ketik '0'): ");
        scanf("%s", idLayanan);
        if (strcmp(idLayanan, "0") != 0) {
            while (fread(&layanan, sizeof(DTLayanan), 1, fileLayanan) == 1) {
                if (strcmp(layanan.idLyn, idLayanan) == 0) {
                    foundLayanan = 1;
                    hargaLayanan = layanan.hargaLyn;
                    break;
                }
            }
        }
        fclose(fileLayanan);
    }

    // Simpan transaksi
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(penjualan.tanggalPenjualan, sizeof(penjualan.tanggalPenjualan), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    penjualan.kategori = jenisPilihan;
    penjualan.totalPenjualan = jumlah;
    penjualan.totalPromo = totalDiskon;
    penjualan.totalHarga = (hargaBarang * jumlah) - totalDiskon + hargaLayanan;
    strcpy(penjualan.namaKRY, karyawan.namaKry); // Gunakan nama dari database karyawan
    strcpy(penjualan.Metode, "Cash");

    fwrite(&penjualan, sizeof(DTPenjualan), 1, filePenjualan);

    // Menampilkan struk
    printf("\n\n=== STRUK PENJUALAN ===\n");
    printf("ID Penjualan      : %s\n", penjualan.idPenjualan);
    printf("Tanggal Penjualan : %s\n", penjualan.tanggalPenjualan);
    printf("Barang            : %s\n", foundItem == 1 ? produk.namaPrd : aksessoris.namaAks);
    printf("Jumlah            : %d\n", penjualan.totalPenjualan);
    printf("Harga Satuan      : RP. %d\n", hargaBarang);
    printf("Total Harga       : RP. %d\n", hargaBarang * jumlah);
    if (foundDiskon) {
        printf("Diskon (%s)  : RP. %d\n", diskon.jenisDsk, totalDiskon);
    }
    if (foundLayanan) {
        printf("Layanan (%s)  : RP. %d\n", layanan.jenisLyn, hargaLayanan);
    }
    printf("Total Bayar       : RP. %d\n", penjualan.totalHarga);
    printf("Karyawan          : %s\n", penjualan.namaKRY);
    printf("Metode Pembayaran : %s\n", penjualan.Metode);

    fclose(filePenjualan);
    if (jenisPilihan == 1) fclose(fileProduk);
    else fclose(fileAksessoris);
}

void displayTransaksiPenjualan() {
    system("cls");
    int found = 0;
    char idPenjualanCari[10];

    filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
    if (filePenjualan == NULL) {
        perror("Failed to open Penjualan.dat");
        return;
    }

    printf("\n================================= DAFTAR TRANSAKSI =================================\n");
    printf("%-10s %-15s %-15s %-15s %-15s %-15s %-15s\n", "ID", "Tanggal", "Jenis", "Total", "Promo", "Harga", "Metode");

    while (fread(&penjualan, sizeof(DTPenjualan), 1, filePenjualan) == 1) {
        printf("%-10s %-15s %-15d %-15d %-15d %-15d %-15s\n",
               penjualan.idPenjualan, penjualan.tanggalPenjualan, penjualan.kategori, penjualan.totalPenjualan,
               penjualan.totalPromo, penjualan.totalHarga, penjualan.Metode);
    }

    fclose(filePenjualan);

    // Pilihan untuk melihat detail transaksi
    char pilihan;
    printf("\nApakah Anda ingin melihat detail transaksi? (y/n): ");
    scanf(" %c", &pilihan);

    if (pilihan == 'y' || pilihan == 'Y') {
        printf("Masukkan ID Penjualan yang ingin dilihat: ");
        scanf("%s", idPenjualanCari);

        // Buka kembali file untuk mencari transaksi yang sesuai
        filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
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

        // Tampilkan detail transaksi
        printf("\n\n=== STRUK PENJUALAN ===\n");
        printf("ID Penjualan      : %s\n", penjualan.idPenjualan);
        printf("Tanggal Penjualan : %s\n", penjualan.tanggalPenjualan);
        printf("Barang            : %s\n", penjualan.kategori == 1 ? produk.namaPrd : aksessoris.namaAks);
        printf("Jumlah            : %d\n", penjualan.totalPenjualan);
        printf("Total Harga       : RP. %d\n", penjualan.totalHarga + penjualan.totalPromo);
        if (penjualan.totalPromo > 0) {
            printf("Diskon            : -RP. %d\n", penjualan.totalPromo);
        }
        printf("Total Bayar       : RP. %d\n", penjualan.totalHarga);
        printf("Karyawan          : %s\n", penjualan.namaKRY);
        printf("Metode Pembayaran : %s\n", penjualan.Metode);
    }
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
