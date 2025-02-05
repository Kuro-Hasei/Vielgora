#ifndef CRUD_MEMBER_H
#define CRUD_MEMBER_H

#ifndef CRUD_Member_H
#define CRUD_Member_H

#include "Deklarasi.h"
#include "../Tampilan/Tampilan.h"

void inputMember(int n) {
    system("cls");
    templateUI();
    cleanKiri();

    char kodeMember[] = {"MBR"};
    int idTerakhir = 0;
    int batasKiri = 5;

    fileMember = fopen("../Database/dat/Member.dat", "ab+");
    if (fileMember == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(member.id_Member, "%*[^0-9]%d", &idTerakhir);
    }
    gotoxy(batasKiri, 2); SetColor(colorMainText);

    // Looping pembuatan id cabang
    for (int i = idTerakhir+1; i <= idTerakhir+n; i++) {
        // Generate ID otomatis
        snprintf(member.id_Member, sizeof(member.id_Member), "%s%i", kodeMember, i);

        // Menampilkan Teks Untuk Input
        SetColor(colorMainText);
        gotoxy(batasKiri, 3); printf("=MASUKKAN DATA Member===========");
        SetColor(text2);
        gotoxy(batasKiri, 5); printf("ID Member");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", member.id_Member);

        gotoxy(batasKiri, 8); printf("Nama Member");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", " ");

        gotoxy(batasKiri, 11); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 11); printf("| %-40s|", " ");

        gotoxy(batasKiri, 14); printf("Alamat");
        gotoxy(batasKiri+50, 14); printf("| %-40s|", " ");

        gotoxy(batasKiri, 17); printf("No Telepon");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", " ");

        gotoxy(batasKiri, 20); printf("Status");
        gotoxy(batasKiri+50, 20); printf("| %-40s|", "Aktif ");

        gotoxy(57, 8); getteks(member.nama, 50);

        gotoxy(57, 11); getDate(member.tglLhr);

        gotoxy(57, 14); getteks(member.alamat, 15);

        gotoxy(57, 17); getno(member.noTelp, 13);

        strcpy(member.status, "Aktif");

        fwrite(&member, sizeof(member), 1, fileMember);
    }
    fclose(fileMember);
}

void readdataMemberINJS() {
    cleanKiri();

    char id[] = "ID";
    char nama[] = "NAMA";
    char status[] = "STATUS";

    int i = 1;
    int yTeks = 6;

    fileMember = fopen("../Database/dat/Member.dat", "rb");
    if (fileMember == NULL) {
        perror("Failed to open file");
        return;
    }

    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        printTable(30, 90, 3, 38);
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(30, 4); printf(" %-8s   %-25s   %-20s \n", id, nama, status);
        gotoxy(30, yTeks);printf(" %-8s   %-25s   %-20s \n", member.id_Member, member.nama,member.status);

        if (i % 35 == 0) {
            getchar();
            cleanKiri();
            yTeks = 5; // PADA SAAT BERHENTI, KOORDINAT UNTUK MENAMPILKAN DATA KARYAWAN AKAN RESET KEMBALI KE AWAL
        }
        i++;
        yTeks++;
    }
    fclose(fileMember);
}

void readDetailMember() {
    int batasKiri = 5;
    char idMmbr[10];
    cleanKanan();

    retype:
    SetColor(colorHeadText);
    gotoxy(130, 2); printf("   %-35s", "W E L C O M E  A D M I N");
    gotoxy(130, 41); printf("%38c", ' ');
    SetColor(text2);
    gotoxy(135, 13); printf("Masukkan ID Member");
    gotoxy(135, 15); printf("[        ]");

    readdataMemberINJS();

    gotoxy(137, 15); getteks(idMmbr, 4);
    cleanKiri();

    int i = 1;
    int found = 0;
    //Membuka file dengan mode rb
    fileMember = fopen("../Database/dat/Member.dat", "rb");

    gotoxy(0, 3); SetColorBlock(3,7);
    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        if (strcmp(idMmbr, member.id_Member) == 0) {
            found = 1;
            break;
        }
        i++;
    }

    if (found == 1) {
        cleanKiri();
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

void updateMember() {
    int found;
    found = 0;
    char No[10];
    int batasKiri = 5;

    retype:
    cleanKanan();
    gotoxy(135, 5); SetColor(text2);
    gotoxy(135, 10); printf("ID Member : [      ]");
    gotoxy(149, 10); getteks(No, 4);
    /*gotoxy(115+8, 10); printf("ID Karyawan : [   ]");
    gotoxy(row+17, 15); getteks(No, 6);*/

    //Membuka file asli dengan mode rb
    fileMember = fopen("../Database/dat/Member.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempMember = fopen("../Database/Temp/MemberTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(No, member.id_Member) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&member, sizeof(member), 1, tempMember);
        }
    }

    //Proses lanjutan setelah data ditemukan
    if (found == 1) {
        cleanKiri();
        SetColor(text2);
        gotoxy(batasKiri, 3); printf("ID Member");
        gotoxy(batasKiri+50, 3); printf("| %-40s|", member.id_Member);

        gotoxy(batasKiri, 4); printf("Nama Member");
        gotoxy(batasKiri+50, 4); printf("| %-40s|", member.nama);

        gotoxy(batasKiri, 5); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 5); printf("| %-40s|", member.tglLhr);

        gotoxy(batasKiri, 6); printf("Alamat");
        gotoxy(batasKiri+50, 6); printf("| %-40s|", member.alamat);

        gotoxy(batasKiri, 7); printf("No Telepon");
        gotoxy(batasKiri+50, 7); printf("| %-40s|", member.noTelp);

        gotoxy(batasKiri, 8); printf("Status");
        gotoxy(batasKiri+50, 8); printf("| %-40s|", member.status);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColor(colorHeadText);
        gotoxy(batasKiri, 13); printf("=MASUKKAN DATA YANG BARU===========");
        SetColor(text2);
        gotoxy(batasKiri, 15); printf("ID Member");
        gotoxy(batasKiri+50, 15); printf("| %-40s|", member.id_Member);

        gotoxy(batasKiri, 17); printf("Nama Member");
        gotoxy(batasKiri+50, 17); printf("| %-40s|", " ");

        gotoxy(batasKiri, 19); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(batasKiri+50, 19); printf("| %-40s|", " ");

        gotoxy(batasKiri, 21); printf("Alamat");
        gotoxy(batasKiri+50, 21); printf("| %-40s|", " ");

        gotoxy(batasKiri, 23); printf("No Telepon");
        gotoxy(batasKiri+50, 23); printf("| %-40s|", " ");

        gotoxy(batasKiri, 25); printf("Status");
        gotoxy(batasKiri+50, 25); printf("| %-40s|", " ");

        char namTemp[50];
        gotoxy(57, 17); getteks(namTemp, 50);

        char tglTemp[12];
        gotoxy(57, 19); getDate(tglTemp);

        char alamatTemp[35];
        gotoxy(57, 21); getteks(alamatTemp, 35);

        char tlpTemp[15];
        gotoxy(57, 23); getno(tlpTemp, 13);

        char statusTemp[10];
        /*gotoxy(57, 29); getteks(statusTemp, 10);*/
        int validStatus = 0;
        while (!validStatus) {
            gotoxy(57, 25); getteks(statusTemp, 1);

            // Cek apakah Gender valid
            for (int j = 0; j < jumlahGender; j++) {
                if (strcmp(statusTemp, statusKodeK[j]) == 0) {
                    strcpy(statusTemp, statusNamaK[j]); // Mengganti kode dengan nama jabatan
                    validStatus = 1;
                    break;
                }
            }

            if (!validStatus) {
                showMessage("ATTENTION", "Status tidak valid.");
            }
        }

        if (doaction("UBAH DATA") == 1) {
            strcpy(member.id_Member, No);
            strcpy(member.nama, namTemp);
            strcpy(member.tglLhr, alamatTemp);
            strcpy(member.alamat, alamatTemp);
            strcpy(member.noTelp, tlpTemp);
            strcpy(member.status, statusTemp);
            fwrite(&member, sizeof(member), 1, tempMember);
            while (fread(&member, sizeof(member), 1, fileMember) == 1) {
                fwrite(&member, sizeof(member), 1, tempMember);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&member, sizeof(member), 1, tempMember);
            while (fread(&member, sizeof(member), 1, fileMember) == 1) {
                fwrite(&member, sizeof(member), 1, tempMember);
            }
        }
    } else {
        showMessage("ALERT!", "ID Member tidak ditemukan");
        goto retype;
    }
    fclose(fileMember);
    fclose(tempMember);
}

void deleteDataMember() {
    int found;
    found = 0;
    char idMember[10];
    int batasKiri = 5;
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    retype:
    cleanKanan();
    readdataMemberINJS();
    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 10); printf("ID Produk : [      ]");
    gotoxy(PosisiX+14, 10); getteks(idMember, 4);

    //Membuka file asli dengan mode rb
    fileMember = fopen("../Database/dat/Member.dat", "rb");
    //Membuka file temporary dengan mode wb
    tempMember = fopen("../Database/Temp/MemberTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&member, sizeof(member), 1, fileMember) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(idMember, member.id_Member) == 0) {
            cleanKiri();
            gotoxy(batasKiri, 5); printf("ID member");
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
            getchar();
            getchar();
            if (deleteData() == 1) {
                found = 1;
                showMessage("ATTENTION!!", "Data berhasil dihapus!");
                continue;
            } else {
                found = 1;
                fwrite(&member, sizeof(member), 1, tempMember);
            }
        }
            //Jika tidak maka program akan menyalin data dari file asli ke data temporary
        else {
            fwrite(&member, sizeof(member), 1, tempMember);
        }
    }
    if (found == 0) {
        showMessage("ALERT!", "ID Member tidak ditemukan");
        return;
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileMember);
    fclose(tempMember);
}

void MenuAddMember() {
    cleanKanan();
    int PosisiX = 135;

    int n;
    char man[] = "W E L C O M E  A D M I N";
    char space = " ";

    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 10); printf("Banyaknya data : [   ]");
    gotoxy(PosisiX+19, 10); getnum(&n, 1);

    inputMember(n);
    system("cls");
    frame();
}

void menuReadMember() {
    cleanKanan();
    int PosisiX = 135;
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
    gotoxy(PosisiX - 5, 40); printf("%38c", space);
    SetColor(text2);
    gotoxy(PosisiX, 35); printf("Press ENTER to next...");
    readdataMemberINJS();
    getch();
    if (lihatDetil() == 1) {
        readDetailMember();
    }
    system("cls");
    frame();
}

void menuUpdateMember() {
    //Memanggil prosedur pencarian id kota
    updateMember();
    //Membuka file asli dengan mode wb
    fileMember = fopen("../Database/dat/Member.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempMember = fopen("../Database/Temp/MemberTemp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&member, sizeof(member), 1, tempMember) == 1) {
        fwrite(&member, sizeof(member), 1, fileMember);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileMember);
    fclose(tempMember);
    system("cls");
    frame();
}

void menuDeleteMember() {
    //Memanggil prosedur pencarian id kota
    deleteDataMember();
    //Membuka file asli dengan mode wb
    fileMember = fopen("../Database/dat/Member.dat", "wb");
    //Membuka file temporary dengan mode rb
    tempMember = fopen("../Database/Temp/MemberTemp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&member, sizeof(member), 1, tempMember)==1) {
        fwrite(&member, sizeof(member), 1, fileMember);
    }
    //Menutup file asli dan file temporary setelah digunakan
    fclose(fileMember);
    fclose(tempMember);
    system("cls");
    frame();
}

void crudMember() {
    int PosisiX = 135; // Posisi menu di layar
    int PosisiY = 10;
    int jarakMenu = 2;

    int menu = 1;   // Menu aktif (posisi awal)
    int totalMenu = 5; // Total jumlah menu
    int key;

    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    system("cls");
    frame();

    do {
        // Menampilkan menu dengan indikasi pilihan aktif (>>)
        SetColor(colorHeadText);
        gotoxy(PosisiX - 5, 2); printf("   %-35s", man);
        gotoxy(PosisiX - 5, 40); printf("%38c", space);
        SetColor(text2);
        for (int i = 1; i <= totalMenu; i++) {
            if (i == menu) { // Tambahkan tanda ">>" di menu aktif
                gotoxy(PosisiX + 22, PosisiY + (i - 1) * jarakMenu); printf("<<<");
            } else {
                gotoxy(PosisiX + 22, PosisiY + (i - 1) * jarakMenu); printf("   ");
            }

            // Tampilkan menu
            gotoxy(PosisiX, PosisiY + (i - 1) * jarakMenu);
            switch (i) {
                case 1: printf("Tambah Data Member"); break;
                case 2: printf("Lihat Data Member"); break;
                case 3: printf("Ubah Data Member"); break;
                case 4: printf("Hapus Data Member"); break;
                case 5: printf("EXIT PROGRAM"); break;
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
                    MenuAddMember();
                    break;
                case 2:
                    menuReadMember();
                    break;
                case 3:
                    menuUpdateMember();
                    break;
                case 4:
                    menuDeleteMember();
                    break;
                case 5:
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

#endif
#endif //CRUD_MEMBER_H