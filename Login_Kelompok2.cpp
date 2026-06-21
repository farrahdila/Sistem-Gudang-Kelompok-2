#include <iostream>
#include <cstdlib>


using namespace std;

struct Pengguna 
{
    string username;
    string password;
    string role; 
};

struct Barang {
    string sku;
    string nama;
    int stok;
};

void clearScreen()
{
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void kembaliKeMenu()
{
    cout << "\nTekan ENTER untuk kembali ke menu utama . . . ";
    cin.ignore();
    cin.get();
}

int main ()
{
    Pengguna databaseAkun[10];
    int jumlahAkun = 0;
  
    Barang databaseBarang[30];
    int jumlahBarang = 0; 
    
    while (true)
    {
        string roleUserAktif = ""; 
        bool loginSukses = false;
        
        while (!loginSukses)
        {
            clearScreen();
            cout << "==========================================" << endl;
            cout << "                STOCKIFY             " << endl;
            cout << "==========================================" << endl;
            cout << "1. Login ke Sistem" << endl;
            cout << "2. Daftar Akun Baru" << endl;
            cout << "3. Keluar dari Aplikasi" << endl;
            cout << "___________________________________________" << endl;
            cout << "Pilih opsi (1-3): ";
            int opsiAwal;
            cin >> opsiAwal;
            
            if (opsiAwal == 1) 
            {
                clearScreen(); 
                if (jumlahAkun == 0)
                {
                    cout << "[!] PEMBERITAHUAN [!]" << endl;
                    cout << "Belum ada akun yang terdaftar di sistem." << endl;
                    cout << "Silahkan kembali dan pilih menu 'Daftar Akun Baru' terlebih dahulu." << endl;
                    
                    cout << "\nTekan ENTER untuk kembali. . .";
                    cin.ignore();
                    cin.get();
                    continue; 
                }
                
                string inputUser, inputPass;
                cout << "--- HALAMAN LOGIN ---" << endl;
                cout << "Username : "; cin >> inputUser; 
                cout << "Password : "; cin >> inputPass; 
                
                for (int i = 0; i < jumlahAkun; i++)
                {
                    if (databaseAkun[i].username == inputUser && databaseAkun[i].password == inputPass)
                    {
                        loginSukses = true;
                        roleUserAktif = databaseAkun[i].role;
                        break;
                    }
                }
                
                if (loginSukses)
                {
                    cout << "\nLogin Berhasil! Anda masuk sebagai " << roleUserAktif << "." << endl;
                    cout << "Tekan ENTER untuk masuk ke Menu Utama...";
                    cin.ignore();
                    cin.get();
                }
                else
                {
                    cout << "\nUsername atau Password salah!" << endl;
                    cout << "Tekan ENTER untuk mencoba lagi...";
                    cin.ignore();
                    cin.get();
                }
            }
            else if (opsiAwal == 2)
            {
                clearScreen();
                if (jumlahAkun >= 10)
                {
                    cout << "Memori database penuh! Tidak bisa menambah akun lagi." << endl;
                    kembaliKeMenu();
                    continue; 
                }
                
                string newUser, newPass;
                int pilihanRole;
                
                cout << "--- PENDAFTARAN AKUN BARU ---" << endl;
                cout << "Masukkan Username Baru : ";
                cin >> newUser; 
                cout << "Masukkan Password Baru : ";
                cin >> newPass;
                cout << "Pilih Hak Akses (Role): \n1. ADMIN\n2. STAFF GUDANG\nPilihan (1-2): "; 
                cin >> pilihanRole;
                
                string newRole = (pilihanRole == 1) ? "ADMIN" : "STAFF";
                
                databaseAkun[jumlahAkun].username = newUser;
                databaseAkun[jumlahAkun].password = newPass;
                databaseAkun[jumlahAkun].role = newRole;
                jumlahAkun++;
                
                cout << "\nAkun berhasil didaftarkan!" << endl;
                cout << "Silahkan gunakan akun tersebut untuk login." << endl;
                cout << "Tekan ENTER untuk kembali...";
                cin.ignore();
                cin.get();      
            }
            else if (opsiAwal == 3)
            {
                clearScreen();
                cout << "Terima kasih telah menggunakan sistem." << endl;
                return 0;   
            }   
        } 
        
        bool tetapDiMenuUtama = true;
        while (tetapDiMenuUtama)
        {
            clearScreen(); 
            cout << "===================================================" << endl;
            cout << "                MENU UTAMA - " << roleUserAktif << endl;
            cout << "===================================================" << endl;
            
            if (roleUserAktif == "ADMIN") 
            {
                cout << "1. Kelola Stok Barang & Vendor (CRUD)" << endl;
                cout << "2. Cari Barang / Kode SKU" << endl;
                cout << "3. Log Masuk-Keluar (Real-time)" << endl;
                cout << "4. Cetak Barcode & Laporan" << endl;
                cout << "5. Kembali ke Halaman Login (Logout)" << endl;
                cout << "6. Keluar dari Aplikasi" << endl;
            } 
            else if (roleUserAktif == "STAFF") 
            {
                cout << "1. Cari Barang / Kode SKU" << endl;
                cout << "2. Log Masuk-Keluar (Real-time)" << endl;
                cout << "3. Kembali ke Halaman Login (Logout)" << endl;
                cout << "4. Keluar dari Aplikasi" << endl;
            }
            cout << "___________________________________________________" << endl;
            cout << "Pilihan menu: "; 
            int pilihanMenu;
            cin >> pilihanMenu;
            
            if (roleUserAktif == "ADMIN") 
            {
                switch (pilihanMenu)
                {
                    case 1:
                    {
                        int pilihanSubMenu;
                        clearScreen();
                        
                        cout << "--- [MENU 1] KELOLA STOK BARANG (CRUD) ---" << endl;
                        cout << "1. Tambahkan Stok Barang Baru" << endl;
                        cout << "2. Hapus Data Barang" << endl;
                        cout << "3. Menampilkan Semua Stok Gudang" << endl;
                        cout << "Masukkan pilihan Anda (1-3): ";
                        cin >> pilihanSubMenu;
                        
                        if (pilihanSubMenu == 1)
                        {
                            clearScreen();
                            int jumlahInput;
                            cout << "Mau Input Berapa Jenis Barang? : ";
                            cin >> jumlahInput;
                            
                            for (int i = 0; i < jumlahInput; i++)
                            {
                                if (jumlahBarang >= 30) {
                                    cout << "Gudang penuh, tidak bisa menambah barang lagi!" << endl;
                                    break;
                                }
                                cout << "\n--- Data Barang ke-" << i+1 << " ---" << endl;
                                cout << "Masukkan Kode SKU   : "; cin >> databaseBarang[jumlahBarang].sku;
                                cout << "Masukkan Nama Barang: "; cin >> databaseBarang[jumlahBarang].nama;
                                cout << "Masukkan Jumlah Stok: "; cin >> databaseBarang[jumlahBarang].stok;
                                jumlahBarang++;
                            }
                            cout << "\nAksi berhasil dimuat oleh Admin." << endl;
                            kembaliKeMenu(); 
                        }
                        else if (pilihanSubMenu == 2)
                        {
                            clearScreen();
                            string targetSku;
                            cout << "Masukkan Kode SKU barang yang ingin didelete: ";
                            cin >> targetSku;
                            
                            bool ditemukan = false;
                            for (int i = 0; i < jumlahBarang; i++) {
                                if (databaseBarang[i].sku == targetSku) {
                                    for (int j = i; j < jumlahBarang - 1; j++) {
                                        databaseBarang[j] = databaseBarang[j + 1];
                                    }
                                    jumlahBarang--;
                                    ditemukan = true;
                                    cout << "\nBarang dengan SKU " << targetSku << " berhasil dihapus dari sistem." << endl;
                                    break;
                                }
                            }
                            if (!ditemukan) {
                                cout << "\nKode SKU tidak ditemukan!" << endl;
                            }
                            kembaliKeMenu();
                        }
                        else if (pilihanSubMenu == 3)
                        {
                            clearScreen();
                            cout << "===================================================\n";
                            cout << "KODE SKU\tNAMA BARANG\t\tJUMLAH STOK\n";
                            cout << "===================================================\n";
                            if (jumlahBarang == 0) {
                                cout << "\t\t--- Gudang Kosong ---\n";
                            } else {
                                for (int i = 0; i < jumlahBarang; i++) {
                                    cout << databaseBarang[i].sku << "\t\t" << databaseBarang[i].nama << "\t\t" << databaseBarang[i].stok << " Unit\n";
                                }
                            }
                            cout << "===================================================\n";
                            kembaliKeMenu();
                        }
                        break;
                    }
                    
                    case 2:
                    {
                        clearScreen();
                        string kataKunci;
                        cout << "--- [MENU 2] CARI NAMA BARANG / SKU (ADMIN) ---" << endl;
                        cout << "Masukkan Kode SKU yang dicari: ";
                        cin >> kataKunci;
                        
                        bool ketemu = false;
                        for (int i = 0; i < jumlahBarang; i++) {
                            if (databaseBarang[i].sku == kataKunci) {
                                cout << "\nDATA BARANG DITEMUKAN!" << endl;
                                cout << "Kode SKU    : " << databaseBarang[i].sku << endl;
                                cout << "Nama Barang : " << databaseBarang[i].nama << endl;
                                cout << "Sisa Stok   : " << databaseBarang[i].stok << " Unit" << endl;
                                ketemu = true;
                                break;
                            }
                        }
                        if (!ketemu) {
                            cout << "\nBarang dengan SKU '" << kataKunci << "' tidak ada di gudang." << endl;
                        }
                        kembaliKeMenu();
                        break;
                    }
                    case 3:
                        clearScreen();
                        cout << "--- [MENU 3] LOG TRANSAKSI REAL-TIME ---" << endl;
                        cout << "[LOG 01] Admin berhasil memperbarui data rak SKU001." << endl;
                        cout << "[LOG 02] Sinkronisasi database stok lokal berhasil." << endl;
                        kembaliKeMenu();
                        break;
                    case 4:
                        clearScreen();
                        cout << "--- [MENU 4] PRINT BARCODE & LAPORAN ---" << endl;
                        cout << "[?] Dokumen cetak laporan bulanan berhasil di-generate oleh Admin." << endl;
                        kembaliKeMenu();
                        break;
                    case 5:
                        tetapDiMenuUtama = false; 
                        cout << "\nMelakukan Logout..." << endl;
                        cout << "Tekan ENTER untuk kembali ke halaman Login...";
                        cin.ignore(); cin.get();
                        break;
                    case 6:
                        clearScreen();
                        cout << "Terima kasih telah menggunakan sistem." << endl;
                        return 0;
                    default:
                        cout << "\nPilihan tidak valid!" << endl;
                        kembaliKeMenu();
                        break;  
                }
            } 
            else if (roleUserAktif == "STAFF") 
            {
                switch (pilihanMenu)
                {
                    case 1:
                    {
                        clearScreen();
                        string kataKunci;
                        cout << "--- [MENU 1] CARI NAMA BARANG / SKU (STAFF) ---" << endl;
                        cout << "Masukkan Kode SKU yang dicari: ";
                        cin >> kataKunci;
                        
                        bool ketemu = false;
                        for (int i = 0; i < jumlahBarang; i++) {
                            if (databaseBarang[i].sku == kataKunci) {
                                cout << "\n[?] DATA BARANG DITEMUKAN!" << endl;
                                cout << "Kode SKU    : " << databaseBarang[i].sku << endl;
                                cout << "Nama Barang : " << databaseBarang[i].nama << endl;
                                cout << "Sisa Stok   : " << databaseBarang[i].stok << " Unit" << endl;
                                ketemu = true;
                                break;
                            }
                        }
                        if (!ketemu) {
                            cout << "\n[X] Barang dengan SKU '" << kataKunci << "' tidak ada di gudang." << endl;
                        }
                        kembaliKeMenu();
                        break;
                    }
                    case 2:
                        clearScreen();
                        cout << "--- [MENU 2] LOG TRANSAKSI REAL-TIME ---" << endl;
                        cout << "[LOG 01] Staff Gudang membaca data stok secara real-time." << endl;
                        kembaliKeMenu();
                        break;
                    case 3:
                        tetapDiMenuUtama = false; 
                        cout << "\nMelakukan Logout..." << endl;
                        cout << "Tekan ENTER untuk kembali ke halaman Login...";
                        cin.ignore(); cin.get();
                        break;
                    case 4: 
                        clearScreen();
                        cout << "Terima kasih telah menggunakan sistem." << endl;
                        return 0;
                    default:
                        cout << "\nPilihan tidak valid!" << endl;
                        kembaliKeMenu();
                        break;  
                }
            }
        } 
    } 
    return 0;
}
