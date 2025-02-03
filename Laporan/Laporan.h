#ifndef LAPORAN_H
#define LAPORAN_H

void detailPenjualan();

void laporanTransaksiPenjualan() {
    int PosisiX = 135;
    int PosisiY = 10;
    int jarakMenu = 2; // Jarak antar menu
    int batasKiri = 5;

    int menu = 1;
    int totalMenu = 3;
    int key;

    int bulan, tahun;
    int found = 0;
    char idPenjualanCari[10];

    char man[] = "L A P O R A N   P E N J U A L A N";
    char space = ' ';

    int i = 1;
    int yTeks = 6;

    cleanKanan();
    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        SetColor(colorHeadText);
        gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
        gotoxy(PosisiX - 5, 40); printf("%38c", space);
        SetColor(text2);

        for (i = 1; i <= totalMenu; i++) {
            if (i == menu) {
                gotoxy(PosisiX + 23, PosisiY + (i - 1) * jarakMenu); printf("<<<");
            } else {
                gotoxy(PosisiX + 23, PosisiY + (i - 1) * jarakMenu); printf("   ");
            }
            gotoxy(PosisiX, PosisiY + (i - 1) * jarakMenu);
            switch (i) {
                case 1: printf("Sorting Bulan & Tahun"); break;
                case 2: printf("Sorting Tahun"); break;
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
                SetColor(colorHeadText);
                gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
                gotoxy(PosisiX - 5, 40); printf("%38c", space);
                SetColor(text2);
                gotoxy(135,15);printf("Masukkan Tahun (YYYY): ");
                gotoxy(135,16);printf("[    ]");
                gotoxy(136,16);getnum(&tahun, 4);
                if (menu == 1) {
                    gotoxy(135,15);printf("Masukkan Bulan (1-12): ");
                    gotoxy(135,16);printf("[    ]");
                    gotoxy(137,16);getnum(&bulan, 2);
                }
                cleanKiri();

                filePenjualan = fopen("../Database/dat/Penjualan.dat", "rb");
                if (filePenjualan == NULL) {
                    perror("Failed to open Penjualan.dat");
                    return;
                }

                fileProduk = fopen("../Database/dat/Produk.dat", "rb");
                if (fileProduk == NULL) {
                    perror("Failed to open Penjualan.dat");
                    return;
                }

                fileAksessoris = fopen("../Database/dat/Aksesoris.dat", "rb");
                if (fileAksessoris == NULL) {
                    perror("Failed to open Penjualan.dat");
                    return;
                }

                // Tambahkan variabel untuk menyimpan total keseluruhan
                int totalKeseluruhan = 0;

                // MENAMPILKAN KE LAYAR ISI DARI FILE
                while (fread(&penjualan, sizeof(penjualan), 1, filePenjualan) == 1) {
                    printTable(20, 100, 3, 35);
                    gotoxy(0, 6); SetColor(colorScText);
                    gotoxy(20, 4); printf(" %-10s %-30s %-15s %-15s\n", "ID", "Barang", "Jumlah", "Total");
                    char total[20];
                    rupiah(penjualan.totalHarga, total);
                    int transBulan, transTahun;
                    sscanf(penjualan.tanggalPenjualan, "%*d-%d-%d", &transBulan, &transTahun);

                    if ((menu == 1 && transBulan == bulan && transTahun == tahun) || (menu == 2 && transTahun == tahun)) {
                        found = 1;
                        gotoxy(20, yTeks);
                        printf(" %-10s %-30s %-15d RP.%-12s\n",
                               penjualan.idPenjualan, penjualan.kategori, penjualan.totalPenjualan, total);

                        // Tambahkan total harga ke total keseluruhan
                        totalKeseluruhan += penjualan.totalHarga;
                    }

                    if (i % 35 == 0) {
                        getchar();
                        cleanKiri();
                    }
                    i++;
                    yTeks++;
                }

                // Jika ada transaksi yang ditampilkan, tampilkan total keseluruhan
                if (found) {
                    char totalFinal[20];
                    rupiah(totalKeseluruhan, totalFinal);
                    gotoxy(20, 37);
                    printf("TOTAL PENJUALAN: RP.%-12s\n", totalFinal);
                }

                getchar(); getchar();
                cleanKanan();

                // MENUTUP FILE
                fclose(filePenjualan);
                fclose(fileProduk);
                fclose(fileAksessoris);

                if (!found) {
                    showMessage("ATTENTION", "Tidak ada transaksi pada periode tersebut.");
                }

            } else if (menu == 3) {
                system("cls");
                frame();
                return;
            }
        }
    } while (1);
}

#endif //LAPORAN_H
