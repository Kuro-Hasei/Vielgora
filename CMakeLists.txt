cmake_minimum_required(VERSION 3.29)
project(Vielgora C)

set(CMAKE_C_STANDARD 23)

add_executable(Vielgora TokoVielgora.c
        ProgramTest.h
        cmake-build-debug/Menu_Admin.h
        Source/crud_Karyawan.h
        Source/Deklarasi.h
        Tampilan/Tampilan.h
        Tampilan/menu.h
        Source/cruid_Supplier.h
        Source/crud_Produk.h
        Source/crud_aksesoris.h
        Source/crud_Member.h
        Source/crud_Garansi.h
        Source/crud_Diskon.h
        Source/crud_Layanan.h
        Tampilan/Procedure.h
        Transaksi/Trsk_Pembelian.h
        Transaksi/Trsk_Penjualan.h
        Transaksi/Trsk_Member.h
        Transaksi/Trsk_KlaimGaransi.h)

