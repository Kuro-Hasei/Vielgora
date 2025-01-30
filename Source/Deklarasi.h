#ifndef DEKLARASI_H
#define DEKLARASI_H

#include <stdio.h>

/*==================== FUNCTION BUTTONS ====================*/
#define ENTER 13
#define TAB 9
#define BCKSPC 8
#define ESC 27

/*==================== ARROW BUTTONS ====================*/
#define UP_KEY 72
#define DWN_KEY 80
#define RGHT_KEY 77
#define LEFT_KEY 75

#define STATIC_NUMB 18
#define STATIC_NUMB_LOGIN 62

typedef enum {True = 1, False = 0} Boolean;
FILE *temp;

/*========== Account Jabatan ==========*/
// ADMIN
char usrnmAdmin[] = "admin";
char pwdAdmin[]= "admin";
// MANAGER
char usrnmManager[]= "manager";
char pwdManager[]= "manager";
// TEKNISI
char usrnmTeknisi[]= "teknisi";
char pwdTeknisi[]= "teknisi";
// KASIR
char usrnmKasir[]= "kasir";
char pwdKasir[]= "kasir";

/*==================== DATA KARYAWAN ====================*/
typedef struct {
    char id[10];
    char namaKry[50];
    char tglLhr[12];
    char jabatan[20];
    char noTLP[15];
    char alamat[50];
    char gender[10];
    char status[15];
} DTKaryawan;
DTKaryawan karyawan;
FILE *fileKaryawan;
FILE *tempKaryawan;

// Daftar kode jabatan
char *jabatanKode[] = {"JB1", "JB2", "JB3", "JB4"};
char *jabatanNama[] = {"Manager", "Admin", "Teknisi", "Kasir"};
int jumlahJabatan = 4;

// Daftar kode status
char *statusKodeK[] = {"1", "0"};
char *statusNamaK[] = {"Aktif", "Tidak Aktif"};
int jumlahStatus = 2;

// Daftar kode gender
char *genderKode[] = {"L", "P"};
char *genderNama[] = {"Laki-Laki", "Perempuan"};
int jumlahGender = 2;

/*==================== DATA MEMBER ====================*/
typedef struct {
    char id_Member[10];
    char nama [50];
    char tglLhr[12];
    char alamat[50];
    char RP[20];
    char noTelp[15];
    char status[10];
}DTMember;
DTMember member;
FILE *fileMember;
FILE *tempMember;

/*==================== DATA SUPPLIER ====================*/
typedef struct {
    char idSpl[10];
    char namaSpl[50];
    char alamat[50];
    char noTelp[15];
    char status[10];
} DTSupplier;
DTSupplier supplier;
FILE *fileSupplier;
FILE *tempSupplier;

/*==================== DATA AKSESSORIS ====================*/
typedef struct {
    char idAks[10];
    char namaAks[50];
    char harga[20];
    int status;
} DTAksessoris;
DTAksessoris aksessoris;
FILE *fileAksessoris;
FILE *tempAksessoris;

/*==================== DATA PRODUK ====================*/
typedef struct {
    char idPrd[10];
    char jenisPrd[10];
    char namaPrd[50];
    int harga;
    char status[15];
} DTProduk;
DTProduk produk;
FILE *fileProduk;
FILE *tempProduk;

// Daftar kode status
char *statusKodeP[] = {"1", "0"};
char *statusNamaP[] = {"Tersedia", "Tidak Tersedia"};
int jumlahStatusP = 2;

/*==================== DATA LAYANAN ====================*/
typedef struct {
    char idLyn[10];
    char jenisLyn[20];
    char hargaLyn[20];
    char status[15];
} DTLayanan;
DTLayanan layanan;
FILE *fileLayanan;
FILE *tempLayanan;

/*==================== DATA GARANSI ====================*/
typedef struct {
    char idGrns[10];
    char jenisGrns[20];
    char durasi[30];
    char ketentuan[50];
    char status[10];
} DTGaransi;
DTGaransi garansi;
FILE *fileGaransi;
FILE *tempGaransi;

/*==================== DATA DISKON ====================*/
typedef struct {
    char idDsk[10];
    char jenisDsk[20];
    char persentase[10];
    int batasPoin;
} DTDiskon;
DTDiskon diskon;
FILE *fileDiskon;
FILE *tempDiskon;

/*==================== TRANSAKSI PEMBELIAN ====================*/
typedef struct {
    char idPembelian[10];
    char tanggalPembelian[15];
    int totalPembelian;
    int totalHarga;
    char metodePembayaran[10];
} DTPembelian;
DTPembelian pembelian;
FILE *filePembelian;
FILE *tempPembelian;

/*==================== TRANSAKSI PENJUALAN ====================*/
typedef struct {
    char idPenjualan[10];
    char tanggalPenjualan[15];
    int jenisTerjual;
    int totalPenjualan;
    int totalPromo;
    int totalHarga;
    char namaKRY[50];
    char Metode [20];
} DTPenjualan;
DTPenjualan penjualan;
FILE *filePenjualan;
FILE *tempPenjualan;

/*==================== TRANSAKSI GARANSI ====================*/
typedef struct {
    char idKlaimGaransi[10];
    char tanggalKlaimGaransi[15];
    char deskripsiMasalah[100];
} DTKlaimGaransi;
DTKlaimGaransi klaimGaransi;
FILE *fileKlaimGaransi;
FILE *tempKlaimGaransi;

/*==================== TRANSAKSI MEMBER ====================*/
typedef struct {
    char idTransaksiMember[10];
    char tanggalAktivitas[15];
    char totalPembayaran[15];
    char metodePembayaran[20];
} DTTrskMember;
DTTrskMember trskMember;
FILE *fileTrskMember;
FILE *tempTrskMember;


#endif //DEKLARASI_H