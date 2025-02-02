#ifndef LAPORAN_H
#define LAPORAN_H

void detailPenjualan();

/*void laporanTransaksiPenjualan() {
    int PosisiX = 135;
    int PosisiY = 10;
    int jarakMenu = 2; // Jarak antar menu

    int menu = 1;
    int totalMenu = 3;
    int key;

    int bulan, tahun;
    int found = 0;

    char man[] = "L A P O R A N   P E N J U A L A N";
    char space = ' ';

    int i = 1;
    int yTeks = 4;

    cleanKanan();
    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        SetColor(colorHeadText);
        gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
        gotoxy(PosisiX - 5, 40); printf("%38c", space);
        SetColor(text2);

        for (i = 1; i <= totalMenu; i++) {
            if (i == menu) {
                gotoxy(PosisiX + 30, PosisiY + (i - 1) * jarakMenu); printf("<<<");
            } else {
                gotoxy(PosisiX + 30, PosisiY + (i - 1) * jarakMenu); printf("   ");
            }
            gotoxy(PosisiX, PosisiY + (i - 1) * jarakMenu);
            switch (i) {
                case 1: printf("Berdasarkan Bulan dan Tahun"); break;
                case 2: printf("Berdasarkan Tahun"); break;
                case 3: printf("Exit"); break;
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
            if (menu == 1 || menu == 2) {
                cleanKanan();
                gotoxy(135,25);printf("Masukkan Tahun (YYYY): ");
                gotoxy(135,26);scanf("%d", &tahun);
                if (menu == 1) {
                    gotoxy(135,25);printf("Masukkan Bulan (1-12): ");
                    gotoxy(135,26);scanf("%d", &bulan);
                }
                cleanKiri();

                filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
                if (filePenjualan == NULL) {
                    perror("Failed to open Penjualan.dat");
                    return;
                }

                //MENAMPILKAN KE LAYAR ISI DARI FILE
                while (fread(&penjualan, sizeof(penjualan), 1, filePenjualan) == 1) {
                    gotoxy(0, 6); SetColor(colorScText);
                    gotoxy(10, 4); printf(" %-10s %-15s %-15s %-15s %-15s %-15s %-15s\n", "ID", "Tanggal", "Jenis", "Total", "Promo", "Harga", "Metode");
                    char hargaPrd[20];
                    /*rupiah(produk.harga, hargaPrd);#1#
                    int transBulan, transTahun;
                    sscanf(penjualan.tanggalPenjualan, "%*d-%d-%d", &transBulan, &transTahun);
                    if ((menu == 1 && transBulan == bulan && transTahun == tahun) || (menu == 2 && transTahun == tahun)) {
                        found = 1;
                        gotoxy(10, 6); printf(" %-10s %-15s %-15d %-15d %-15d %-15d %-15s\n",
                               penjualan.idPenjualan, penjualan.tanggalPenjualan, penjualan.kategori,
                               penjualan.totalPenjualan, penjualan.totalPromo, penjualan.totalHarga, penjualan.Metode);
                    }
                    if (i % 35 == 0) {
                        getchar();
                        cleanKiri();
                        yTeks = 6;
                    }
                    i++;
                    yTeks++;
                }
                printTable(10, 110, 3, 38);
                getchar();
                //MENUTUP FILE
                fclose(fileProduk);
                if (!found) {
                    showMessage("ATTENTION", "Tidak ada transaksi pada periode tersebut.");
                }
            } else if (menu == 3) {
                return;
            }
        }
    } while (1);
}

void detailPenjualan() {
    int found = 0;
    char idPenjualanCari[10];
    // Pilihan untuk melihat detail transaksi
    char pilihann;
    printf("\nApakah Anda ingin melihat detail transaksi? (y/n): ");
    scanf(" %c", &pilihann);

    if (pilihann == 'y' || pilihann == 'Y') {
        printf("Masukkan ID Penjualan yang ingin dilihat: ");
        scanf("%s", idPenjualanCari);

        // Buka kembali file untuk mencari transaksi yang sesuai
        filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
        if (filePenjualan == NULL) {
            perror("Failed to open Penjualan.dat");
            return;
        }

        fileProduk = fopen("../Database/dat/Produk.dat", "rb");
        if (fileProduk == NULL) {
            perror("Failed to open Produk.dat");
            return;
        }

        while (fread(&penjualan, sizeof(penjualan), 1, filePenjualan) == 1) {
            if (strcmp(penjualan.idPenjualan, idPenjualanCari) == 0) {
                found = 1;
                break;
            }
        }

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
    fclose(filePenjualan);
    fclose(fileProduk);
}*/

void laporanTransaksiPenjualan() {
    int PosisiX = 5, PosisiY = 4;
    int menu = 1;
    int totalMenu = 3;
    int key;
    int bulan, tahun;
    int found = 0;

    system("cls");
    cleanKanan();

    do {
        gotoxy(PosisiX, PosisiY - 2); printf("=------> Laporan Transaksi Penjualan <------=");
        gotoxy(PosisiX, PosisiY + totalMenu + 2); printf("=--------------------------------------------=");

        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) {
                gotoxy(PosisiX + 30, PosisiY + i - 1); printf("<<<");
            } else {
                gotoxy(PosisiX + 30, PosisiY + i - 1); printf("   ");
            }
            gotoxy(PosisiX, PosisiY + i - 1);
            switch (i) {
                case 1: printf("Filter Berdasarkan Bulan dan Tahun"); break;
                case 2: printf("Filter Berdasarkan Tahun Saja"); break;
                case 3: printf("Exit"); break;
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
            if (menu == 1 || menu == 2) {
                cleanKiri();
                printf("Masukkan Tahun (YYYY): ");
                scanf("%d", &tahun);
                if (menu == 1) {
                    printf("Masukkan Bulan (1-12): ");
                    scanf("%d", &bulan);
                }

                filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
                if (filePenjualan == NULL) {
                    perror("Failed to open Penjualan.dat");
                    return;
                }

                printf("\n================================= LAPORAN TRANSAKSI =================================\n");
                printf("%-10s %-15s %-15s %-15s %-15s %-15s %-15s\n", "ID", "Tanggal", "Jenis", "Total", "Promo", "Harga", "Metode");

                while (fread(&penjualan, sizeof(penjualan), 1, filePenjualan) == 1) {
                    int transBulan, transTahun;
                    sscanf(penjualan.tanggalPenjualan, "%*d-%d-%d", &transBulan, &transTahun);
                    if ((menu == 1 && transBulan == bulan && transTahun == tahun) || (menu == 2 && transTahun == tahun)) {
                        found = 1;
                        printf("%-10s %-15s %-15d %-15d %-15d %-15d %-15s\n",
                               penjualan.idPenjualan, penjualan.tanggalPenjualan, penjualan.kategori,
                               penjualan.totalPenjualan, penjualan.totalPromo, penjualan.totalHarga, penjualan.Metode);
                    }
                }
                fclose(filePenjualan);
                if (!found) {
                    showMessage("ATTENTION", "Tidak ada transaksi pada periode tersebut.");
                }
            } else if (menu == 3) {
                return;
            }
        }
    } while (1);
}

void detailPenjualan() {
    int found = 0;
    char idPenjualanCari[10];
    // Pilihan untuk melihat detail transaksi
    char pilihann;
    printf("\nApakah Anda ingin melihat detail transaksi? (y/n): ");
    scanf(" %c", &pilihann);

    if (pilihann == 'y' || pilihann == 'Y') {
        printf("Masukkan ID Penjualan yang ingin dilihat: ");
        scanf("%s", idPenjualanCari);

        // Buka kembali file untuk mencari transaksi yang sesuai
        filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
        if (filePenjualan == NULL) {
            perror("Failed to open Penjualan.dat");
            return;
        }

        fileProduk = fopen("../Database/dat/Produk.dat", "rb");
        if (fileProduk == NULL) {
            perror("Failed to open Produk.dat");
            return;
        }

        while (fread(&penjualan, sizeof(penjualan), 1, filePenjualan) == 1) {
            if (strcmp(penjualan.idPenjualan, idPenjualanCari) == 0) {
                found = 1;
                break;
            }
        }

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
    fclose(filePenjualan);
    fclose(fileProduk);
}

#endif //LAPORAN_H
