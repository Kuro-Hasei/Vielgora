#ifndef PROGRAMTEST_H
#define PROGRAMTEST_H

/*
void inputKaryawan(int n) {
    system("cls");
    templateUI();
    cleanKiri();

    char kodeKaryawan[] = {"KRY"};
    int idTerakhir = 0;
    int batasKiri = 3;

    fileKaryawan = fopen("../Database/dat/Karyawan.dat", "ab+");

    while (fread(&karyawan, sizeof(karyawan), 1, fileKaryawan) == 1) {
        scanf(karyawan.id, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColorBlock(3,7);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        // Generate ID otomatis
        snprintf(karyawan.id, sizeof(karyawan.id), "%s%i", kodeKaryawan, i);

        // Menampilkan Teks Untuk Input
        SetColorBlock(3,7);
        gotoxy(batasKiri, 3); printf("=MASUKKAN DATA KARYAWAN===========");
        SetColorBlock(3,7);
        gotoxy(batasKiri, 5); printf("ID Karyawan");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", karyawan.id);

        gotoxy(batasKiri, 8); printf("Nama Karyawan");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", " ");

        gotoxy(batasKiri, 11); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", " ");

        gotoxy(batasKiri, 14); printf("Jabatan");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", " ");

        gotoxy(batasKiri, 17); printf("No Telepon");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", " ");

        gotoxy(batasKiri, 20); printf("Alamat");
        gotoxy(batasKiri+50, 20); printf("| %-40s|", " ");

        gotoxy(batasKiri, 23); printf("Gender");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", " ");

        gotoxy(batasKiri, 26); printf("Status");
        gotoxy(batasKiri+50, 26); printf("| %-40s|", "Aktif");

        gotoxy(57, 8); getteks(karyawan.namaKry, 50);

        gotoxy(57, 11); getDate(karyawan.tglLhr);

        gotoxy(57, 14); getteks(karyawan.jabatan, 20);

        gotoxy(57, 17); getteks(karyawan.noTLP, 20);

        gotoxy(57, 20); getteks(karyawan.alamat, 50);

        gotoxy(57, 23); getteks(karyawan.gender, 1);

        strcpy(karyawan.status, "Aktif");

        fwrite(&karyawan, sizeof(karyawan), 1, fileKaryawan);
    }
    fclose(fileKaryawan);
}

void MenuAddKaryawan() {
    system("cls");
    frame();

    int n;
    char Admin[] = "W E L C O M E  A D M I N";
    char space = " ";
    gotoxy(115, 2); SetColorBlock(3,7);printf(" %-35s", Admin);
    gotoxy(115, 41); printf("%38c", space);
    gotoxy(115+12, 5); SetColorBlock(3,7);
    gotoxy(115+8, 10); printf("Benyakan data : [  ]");
    gotoxy(115+25, 10); getnum(&n, 2);

    inputKaryawan(n);
    system("cls");
    frame();
}
*/

#endif //PROGRAMTEST_H
