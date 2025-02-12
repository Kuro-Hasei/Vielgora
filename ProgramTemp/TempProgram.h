#ifndef TEMPPROGRAM_H
#define TEMPPROGRAM_H

void insertEMP()
{
    // DEKLARASI VARIABLE LOKAL PADA PROSEDUR YANG AKAN DIGUNAKAN
    char kodekaryawan[] = {"KRY"};
    int idterakhir = 0;
    char *jbArray[] = {"Teknisi", "Teknisi", "Teknisi", "Admin", "Kasir", "Manager", "Kasir", "Admin", "Admin", "Teknisi",
                       "Admin", "Admin", "Kasir", "Teknisi", "Teknisi", "Teknisi", "Manager", "Manager", "Manager", "Admin",
                       "Admin", "Admin", "Admin", "Kasir", "Kasir"};
    char names[][50] = {
            "Aji Shiori",
            "Simon Simamora",
            "Basri Hamid",
            "Imron Amelia",
            "Arief Suwarno",
            "Mardi Nasir",
            "Imam Hadi",
            "Febri Sukaesih",
            "Heru Karim",
            "Hendi Supriyanto",
            "Ahmad Umar",
            "Erik Irawan",
            "Ayi Anam",
            "Ardi Ayu",
            "Febri Latifah",
            "Edi Yani",
            "Dadang Anggraini",
            "Sulaeman Syahputra",
            "Al Suryana",
            "Gatot Cahyono",
            "Mariana Astutik",
            "Riska Rohimah",
            "Dg Siagian",
            "Yuyun Agustina",
            "Ramlah Syah"
    };
    char *dates[] = {
            "15-07-1990",
            "12-03-1985",
            "28-04-1998",
            "19-09-1982",
            "11-10-1995",
            "02-07-1987",
            "22-08-1992",
            "14-05-1984",
            "30-10-1988",
            "03-05-1993",
            "18-06-1999",
            "01-12-1986",
            "24-09-1991",
            "11-08-1983",
            "20-04-1996",
            "07-01-1989",
            "12-09-1994",
            "25-02-1981",
            "17-05-1997",
            "10-11-1984",
            "29-03-1990",
            "08-06-1995",
            "19-11-1987",
            "06-03-1992",
            "16-09-1983"
    };
    char *lokasi[] = {
            "Sawah Besar, Jakarta",
            "Genteng, Surabaya",
            "Pontianak Barat, Pontianak",
            "Grogol, Semarang",
            "Tanah Abang, Jakarta",
            "Koto Tangah, Padang",
            "Tanjung Priok, Jakarta",
            "Ciputat, Tangerang",
            "Banyumanik, Semarang",
            "Banjarmasin Utara, Banjarmasin",
            "Sukolilo, Surabaya",
            "Mangga Besar, Jakarta",
            "Banyuwangi, Banyuwangi",
            "Medan Baru, Medan",
            "Percut Sei Tuan, Medan",
            "Cengkareng, Jakarta",
            "Nanggalo, Padang",
            "Sidorejo, Salatiga",
            "Kramat Jati, Jakarta",
            "Tanjung Priok, Jakarta",
            "Kotabaru, Yogyakarta",
            "Cirebon, Cirebon",
            "Ngaliyan, Semarang",
            "Pulo Gadung, Jakarta",
            "Wonokromo, Surabaya"
    };
    char *numbers[] = {"081234567890","082198765432","085211223344","087755667788","089612345678","081387654321","082222334455","085366778899","087899887766","089754321098","081443216789","082334567891","085123456789","087955678890","089811223345","081567890123","082476543210","085690876543","087634125678","089977665544"};

    fileKaryawan = fopen("../Database/dat/Karyawan.dat", "wb");
    if (fileKaryawan == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&karyawan, sizeof(karyawan), 1, fileKaryawan) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(karyawan.id, "%*[^0-9]%d", &idterakhir);
    }

    int x = 0;
    // LOOPING PEMBUATAN ID CABANG SESUAI INPUTAN USER
    for (int i = idterakhir+1; i <= idterakhir+20; i++) {
        // GENERATE ID CABANG OTOMATIS DENGAN MENGGABUNGKAN STRING DAN INTEGER
        snprintf(karyawan.id, sizeof(karyawan.id), "%s%i", kodekaryawan, i); // ini untuk menggabungkan 2 variable

        strcpy(karyawan.jabatan, jbArray[x]);

        strcpy(karyawan.namaKry, names[x]); // INPUT NAMA KARYAWAN

        strcpy(karyawan.tglLhr, dates[x]); // INPUT TGL LAHIR KARYAAWAN

        strcpy(karyawan.noTLP, numbers[x]); // INPUT NO TELEPON

        strcpy(karyawan.alamat, lokasi[x]); // INPUT ALAMAT KARYAWAN

        strcpy(karyawan.gender, "Laki-Laki"); // INPUT GENDER KARYAWAN

        strcpy(karyawan.status, "Aktif"); // INPUT STATUS KARYAWAN

        // MENYIMPAN SEMUA HASIL INPUTAN KE FILE
        fwrite(&karyawan, sizeof(karyawan), 1, fileKaryawan);
        x++;
    }
    fclose(fileKaryawan); //MENUTUP FILE SETELAH DIGUNAKAN
}

void insertProduk()
{
    // DEKLARASI VARIABLE LOKAL PADA PROSEDUR YANG AKAN DIGUNAKAN
    char kodekaryawan[] = {"PRD"};
    int idterakhir = 0;
    char *jbArray[] = {
        "Komputer","Laptop","Komputer","Laptop","Laptop","Komputer","Komputer","Laptop","Komputer","Laptop","Laptop","Komputer","Komputer","Laptop","Komputer","Laptop","Laptop","Komputer","Laptop","Komputer"
    };
    char names[][50] = {
        "Dell OptiPlex 7090", "Asus ROG Strix G15", "HP EliteDesk 800 G6","Lenovo Legion 5 Pro", "Acer Predator Helios 300", "IBM ThinkCentre M75q", "Apple Mac Pro M2 Ultra", "MSI Stealth 16 Studio", "Fujitsu Esprimo D7011", "Samsung Galaxy Book3 Pro", "Toshiba Dynabook Tecra A50", "Cisco UCS C220 M6", "Sony Vaio Z Desktop", "Huawei MateBook X Pro", "Panasonic Toughbook FZ-55", "Xiaomi Redmi G 2023", "Razer Blade 15 Advanced", "Gateway DX4885", "LG Gram 17Z90Q", "Compaq Presario CQ5000"
    };
    char *dates[] = {
        "9", "9", "9", "3", "3", "9", "3", "3", "5", "4", "2", "7", "1", "2", "1", "6", "8", "7", "5", "9"
    };
    char *numbers[] = {
        "15500000","24300000","18750000","27200000","22800000","12900000","29500000","26400000","14700000","19600000","13200000","28900000","17500000","21100000","25300000","16800000","23900000","11400000","20700000","10900000"
    };

    fileProduk = fopen("../Database/dat/Produk.dat", "ab+");
    if (fileProduk == NULL) {
        perror("Failed to open file");
        return;
    }

    // Membaca file untuk mendapatkan id terakhir
    while (fread(&produk, sizeof(produk), 1, fileProduk) == 1) {
        // Membaca bagian integer lalu di simpan pada variabel idTerakhir
        sscanf(produk.idPrd, "%*[^0-9]%d", &idterakhir);
    }

    int x = 0;
    // LOOPING PEMBUATAN ID CABANG SESUAI INPUTAN USER
    for (int i = idterakhir+1; i <= idterakhir+20; i++) {
        // GENERATE ID CABANG OTOMATIS DENGAN MENGGABUNGKAN STRING DAN INTEGER
        snprintf(produk.idPrd, sizeof(produk.idPrd), "%s%i", kodekaryawan, i); // ini untuk menggabungkan 2 variable

        strcpy(produk.jenisPrd, jbArray[x]);

        strcpy(produk.namaPrd, names[x]); // INPUT NAMA KARYAWAN

        strcpy(produk.quantity, dates[x]); // INPUT TGL LAHIR KARYAAWAN

        strcpy(produk.harga, numbers[x]); // INPUT NO TELEPON

        // MENYIMPAN SEMUA HASIL INPUTAN KE FILE
        fwrite(&produk, sizeof(produk), 1, fileProduk);
        x++;
    }
    fclose(fileProduk); //MENUTUP FILE SETELAH DIGUNAKAN
}

#endif //TEMPPROGRAM_H
