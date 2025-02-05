#ifndef TRSK_MEMBER_H
#define TRSK_MEMBER_H

#include "../Source/Deklarasi.h"
#include "../Tampilan/Tampilan.h"

void inputTrsMember(int n) {
    system("cls");
    templateUI();

    char kodeTrsMember[] = {"TRSMBR"};
    char kodeMember[] = {"MBR"};
    int idTerakhir = 0;
    int batasKiri = 5;

    fileTrskMember = fopen("../Database/dat/trskMember.dat", "ab+");
    if (fileTrskMember == NULL) {
        perror("Failed to open file");
        return;
    }

    fileMember = fopen("../Database/dat/Member.dat", "ab+");
    if (fileMember == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&trskMember, sizeof(trskMember), 1, fileTrskMember) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(trskMember.idTransaksiMember, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColorBlock(3,7);

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(member.id_Member, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColorBlock(3,7);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        // Generate ID otomatis
        snprintf(trskMember.idTransaksiMember, sizeof(trskMember.idTransaksiMember), "%s%i", kodeTrsMember, i);

        // Generate ID otomatis
        snprintf(member.id_Member, sizeof(member.id_Member), "%s%i", kodeMember, i);

        // Menampilkan Teks Untuk Input
        SetColor(colorHeadText);
        gotoxy(batasKiri, 3); printf("=== [ MASUKKAN DATA MEMBER ] ===========");
        SetColor(text2);
        gotoxy(batasKiri, 5); printf("ID Transaksi Member");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", trskMember.idTransaksiMember);

        gotoxy(batasKiri, 8); printf("ID Member");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", member.id_Member);

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        snprintf(trskMember.tanggalAktivitas, sizeof(trskMember.tanggalAktivitas), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

        gotoxy(batasKiri, 11); printf("Tanggal Pembuatan");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", trskMember.tanggalAktivitas);

        gotoxy(batasKiri, 14); printf("Total Pembayaran");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", "RP. 100.000 ");

        gotoxy(batasKiri, 17); printf("Metode Pembayaran");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", "Cash");

        strcpy(trskMember.totalPembayaran, "RP. 100.000");

        strcpy(trskMember.metodePembayaran, "Cash");

        fwrite(&trskMember, sizeof(trskMember), 1, fileTrskMember);
        getchar(); getchar();
    }
    fclose(fileTrskMember);
    fclose(fileMember);
}

void readdataTrsMemberINJS() {
    cleanKiri();

    char id[] = "ID TRANSAKSI";
    char idM[] = "ID MEMBER";
    char harga[] = "HARGA TOTAL";
    char metode[] = "METODE PEMBAYARAN";
    char tanggal[] = "TANGGAL AKTIVASI";

    int i = 1;
    int yTeks = 6;

    fileTrskMember = fopen("../Database/dat/trskMember.dat", "rb");
    if (fileTrskMember == NULL) {
        perror("Failed to open file");
        return;
    }

    fileMember = fopen("../Database/dat/Member.dat", "rb");
    if (fileMember == NULL) {
        perror("Failed to open file");
        return;
    }


    while ((fread(&trskMember, sizeof(trskMember), 1, fileTrskMember) == 1) && fread(&member, sizeof(member), 1, fileMember)) {
        printTable(15, 110, 3, 38);
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(15, 4); printf(" %-15s  %-15s  %-20s %-20s  %-15s\n", id, idM, harga, metode, tanggal);
        gotoxy(15, yTeks); printf(" %-15s  %-15s  %-20s %-20s  %-15s\n",
                             trskMember.idTransaksiMember, member.id_Member, trskMember.totalPembayaran, trskMember.metodePembayaran, trskMember.tanggalAktivitas);

        if (i % 35 == 0) {
            getchar(); // Wait for user input
            cleanKiri();
            yTeks = 5; // Reset yTeks after clearing screen
        }
        i++;
        yTeks++;
    }
    fclose(fileTrskMember);
    fclose(fileMember);
}

void readDetailTrsMember() {
    int PosisiX = 135;
    int batasKiri = 3;
    char idMmbr[10];
    cleanKiri();
    cleanKanan();

    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    retype:
    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 13); printf("Masukkan ID Member");
    gotoxy(PosisiX, 15); printf("[        ]");

    readdataTrsMemberINJS();

    gotoxy(PosisiX+2, 15); getteks(idMmbr, 4);
    cleanKiri();

    int i = 1;
    int found = 0;
    //Membuka file dengan mode rb
    fileMember = fopen("../Database/dat/Member.dat", "rb");

    gotoxy(0, 3); SetColor(colorMainText);
    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        if (strcmp(idMmbr, member.id_Member) == 0) {
            found = 1;
            break;
        }
        i++;
    }

    if (found == 1) {
        cleanKiri();
        SetColor(text2);
        gotoxy(batasKiri, 5); printf("ID Member");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", member.id_Member);

        gotoxy(batasKiri, 8); printf("Nama Member");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", member.nama);

        gotoxy(batasKiri, 11); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", member.tglLhr);

        gotoxy(batasKiri, 14); printf("Alamat");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", member.alamat);

        gotoxy(batasKiri, 17); printf("No Telepon");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", member.noTelp);

        gotoxy(batasKiri, 20); printf("Status");
        gotoxy(batasKiri+50, 20); printf("| %-40s|", member.status);
    } else {
        showMessage("ALERT!", "ID Member tidak ditemukan");
        goto retype;
    }
    gotoxy(135, 30); printf("Press ENTER to back...");
    getchar();
    //Menutup file setelah membaca
    fclose(fileMember);
    getchar();
}

void MenuAddTrsMember() {
    system("cls");
    frame();

    int n, posisiX = 135;

    gotoxy(posisiX, 5); SetColor(text2);
    gotoxy(posisiX, 10); printf("Banyaknya data : [   ]");
    gotoxy(posisiX+19, 10); getnum(&n,1);

    inputTrsMember(n);
    inputMember(n);
    system("cls");
    frame();
}

void menuReadTrsMember() {
    int posisiX = 135;

    gotoxy(posisiX, 5); SetColor(text2);
    gotoxy(posisiX, 35); printf("Press ENTER to next...");
    readdataTrsMemberINJS();
    getch();
    if (lihatDetil() == 1) {
        readDetailTrsMember();
    }
    system("cls");
    frame();
}

void crudTrsMember() {
    int PosisiX = 135; // Posisi menu di layar
    int PosisiY = 10;
    int jarakMenu = 2;


    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 3; // Total jumlah menu
    int key;

    char man[] = "P E M B U A T A N  M E M B E R";
    char space = ' ';

    system("cls"); frame();
    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        SetColor(colorHeadText);
        gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
        gotoxy(PosisiX - 5, 40); printf("%38c", space);
        SetColor(text2);
        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) { // Tambahkan tanda ">>" di menu aktif
                gotoxy(PosisiX + 20, PosisiY + (i - 1) * jarakMenu); printf("<<<");
            } else {
                gotoxy(PosisiX + 20, PosisiY + (i - 1) * jarakMenu); printf("   ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + (i - 1) * jarakMenu);
            switch (i) {
                case 1: printf("Tambah Data Member"); break;
                case 2: printf("Lihat Data Member"); break;
                case 3: printf("Exit"); break;
                default: break;
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
                case 1:
                    cleanKanan();
                    MenuAddTrsMember();
                    break;
                case 2:
                    menuReadTrsMember();
                    break;
                case 3:
                    system("cls"); frame();
                    return;
                default:
                    gotoxy(PosisiX, PosisiY + totalMenu + 2);
                    printf("Input tidak valid. Silakan coba lagi.\n");
            }
        }
    } while (1);
}

#endif //TRSK_MEMBER_H
