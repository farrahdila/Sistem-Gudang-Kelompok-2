#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iomanip>

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
    int stok = 0;
    long harga = 0;
    long harga_jual = 0;
};

struct LogTransaksi
{
    string infoLog;
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
    cout << "\nTekan ENTER untuk kembali . . . ";
    cin.ignore();
    cin.get();
}

string ambilBagian(string& teks, string pembatas)
{
    size_t pos = teks.find(pembatas);
    string hasil = "";
    if (pos != string::npos)
    {
        hasil = teks.substr(0, pos);
        teks.erase(0, pos + pembatas.length());
    }
    else
    {
        hasil = teks;
        teks = "";
    }

    if (!hasil.empty()) {
        size_t first = hasil.find_first_not_of(' ');
        size_t last = hasil.find_last_not_of(' ');
        if (first != string::npos && last != string::npos)
        {
            hasil = hasil.substr(first, (last - first + 1));
        }
    }
    return hasil;
}

void tampilkanLogRapi(LogTransaksi databaseLog[], int jumlahLog)
{
    cout << "=========================================================================================\n";
    cout << left << setw(4) << "NO"
        << "| " << setw(10) << "JENIS"
        << "| " << setw(30) << "AKTIVITAS / KETERANGAN"
        << "| " << setw(12) << "JUMLAH"
        << "| " << setw(15) << "NILAI (IDR)" << "\n";
    cout << "=========================================================================================\n";

    if (jumlahLog == 0)
    {
        cout << setw(89) << left << "                      [ Belum ada aktivitas transaksi terdaftar ]" << "\n";
    }
    else {
        for (int i = 0; i < jumlahLog; i++)
        {
            string s = databaseLog[i].infoLog;

            if (s.find("|") != string::npos)
            {
                string jenis = ambilBagian(s, "|");
                string ket = ambilBagian(s, "|");
                string qty = ambilBagian(s, "|");
                string harga = ambilBagian(s, "|");

                cout << left << setw(4) << (i + 1)
                    << "| " << setw(10) << jenis
                    << "| " << setw(30) << ket
                    << "| " << setw(12) << qty
                    << "| " << setw(15) << harga << "\n";
            }
            else
            {
                cout << left << setw(4) << (i + 1)
                    << "| " << setw(10) << "INFO"
                    << "| " << setw(71) << s << "\n";
            }
        }
    }
    cout << "=========================================================================================\n";
}

int main()
{
    Pengguna databaseAkun[10];
    int jumlahAkun = 0;

    Barang databaseBarang[30];
    int jumlahBarang = 0;

    LogTransaksi databaseLog[100];
    int jumlahLog = 0;

    databaseAkun[jumlahAkun++] = { "admin", "admin123", "ADMIN" };
    databaseAkun[jumlahAkun++] = { "staff gudang", "staff123", "STAFF" };

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
            cout << "Pilihan opsi (1-3): ";
            int opsiAwal;
            cin >> opsiAwal;

            if (opsiAwal == 1)
            {
                clearScreen();
                if (jumlahAkun == 0)
                {
                    cout << "[!] PEMBERITAHUAN [!]" << endl;
                    cout << "Belum ada akun yang terdaftar di sistem." << endl;
                    kembaliKeMenu();
                    continue;
                }

                string inputUser, inputPass;
                cout << "--- HALAMAN LOGIN ---" << endl;
                cout << "Username : "; cin.ignore(); getline(cin, inputUser);
                cout << "Password : "; getline(cin, inputPass);

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
                    cin.get();
                }
                else
                {
                    cout << "\nUsername atau Password salah!" << endl;
                    cout << "Tekan ENTER untuk mencoba lagi...";
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
                cout << "Masukkan Username Baru : "; cin.ignore(); getline(cin, newUser);
                cout << "Masukkan Password Baru : "; getline(cin, newPass);

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
			    cout << "3. Riwayat & Transaksi Barang" << endl;
                cout << "4. Log Masuk-Keluar (Real-time)" << endl;
                cout << "5. Cetak Barcode & Laporan" << endl;
                cout << "6. Kembali ke Halaman Login (Logout)" << endl;
            }
            else if (roleUserAktif == "STAFF")
            {
                cout << "1. Cari Barang / Kode SKU" << endl;
                cout << "2. Log Masuk-Keluar (Real-time)" << endl;
                cout << "3. Kembali ke Halaman Login (Logout)" << endl;
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
                    cout << "2. Pengambilan Barang oleh Vendor" << endl;
                    cout << "3. Update Data Barang" << endl;
                    cout << "4. Menampilkan Semua Stok Gudang" << endl;
                    cout << "Masukkan pilihan Anda (1-4): ";
                    cin >> pilihanSubMenu;

                    if (pilihanSubMenu == 1)
                    {
                        clearScreen();
                        if (jumlahBarang >= 30)
                        {
                            cout << "Gudang penuh, tidak bisa menambah barang lagi!" << endl;
                            kembaliKeMenu();
                            break;
                        }

                        string noLaporan, penanggungJawab;
                        time_t sekarang = time(0);
                        tm* waktu = localtime(&sekarang);

                        cout << "================================" << endl;
                        cout << "     FORM INPUT DATA BARANG     " << endl;
                        cout << "================================" << endl;
                        cout << "No. Laporan      : "; cin >> noLaporan;
                        cout << "Penanggung Jawab : "; cin.ignore(); getline(cin, penanggungJawab);

                        string tanggal = to_string(waktu->tm_mday) + "-" + to_string(waktu->tm_mon + 1) + "-" + to_string(waktu->tm_year + 1900);
                        cout << "Tanggal Akses    : " << tanggal << endl;
                        cout << "================================" << endl;

                        cout << "Masukkan Kode SKU   : "; cin >> databaseBarang[jumlahBarang].sku;
                        cout << "Masukkan Nama Barang: "; cin.ignore(); getline(cin, databaseBarang[jumlahBarang].nama);
                        cout << "Masukkan Jumlah Stok: "; cin >> databaseBarang[jumlahBarang].stok;
                        cout << "Masukkan Harga Modal: "; cin >> databaseBarang[jumlahBarang].harga;
                        
                        double persenProfit;
                        cout << "Masukkan Rencana % Keuntungan : ";
                        cin >> persenProfit;
                        databaseBarang[jumlahBarang].harga_jual = databaseBarang[jumlahBarang].harga * (1.0 + (persenProfit / 100.0));
                        cout << "-> Harga Jual Otomatis Dihitung: Rp" << databaseBarang[jumlahBarang].harga_jual << endl;

                        if (jumlahLog < 98) {
                            databaseLog[jumlahLog++].infoLog = "MASUK  |" + databaseBarang[jumlahBarang].nama + " | " + to_string(databaseBarang[jumlahBarang].stok) + " unit | Rp" + to_string(databaseBarang[jumlahBarang].harga * databaseBarang[jumlahBarang].stok);
                        }

                        jumlahBarang++;
                        cout << "\nBarang berhasil ditambahkan oleh Admin." << endl;
                        kembaliKeMenu();
                    }
                    else if (pilihanSubMenu == 2)
                    {
                        clearScreen();
                        cout << "--- [MENU 2] PENGAMBILAN BARANG OLEH VENDOR ---" << endl;
                        if (jumlahBarang == 0)
                        {
                            cout << "Stok gudang kosong, tidak ada barang yang bisa diambil." << endl;
                        }
                        else {
                            string targetSku, namaVendor;
                            int jumlahAmbil;

                            cout << "Masukkan Kode SKU Barang yang akan diambil: "; cin >> targetSku;

                            int idx = -1;
                            for (int i = 0; i < jumlahBarang; i++)
                            {
                                if (databaseBarang[i].sku == targetSku) { idx = i; break; }
                            }

                            if (idx == -1) {
                                cout << "[!] Barang dengan SKU tersebut tidak ditemukan!" << endl;
                            }
                            else {
                                cout << "Nama Barang   : " << databaseBarang[idx].nama << endl;
                                cout << "Stok Saat Ini : " << databaseBarang[idx].stok << " Unit" << endl;
                                cout << "Harga Jual    : Rp" << databaseBarang[idx].harga_jual << endl;
                                cout << "------------------------------------------" << endl;

                                cout << "Masukkan Nama Vendor    : ";
                                cin.ignore();
                                getline(cin, namaVendor);
								
								bool valid = false;
								while (!valid) {
								    if (namaVendor.empty() || namaVendor.find_first_not_of(' ') == string::npos) {
								        cout << "[!] Peringatan: Nama vendor tidak boleh kosong!\n" << endl;
								    } 
								    else {
								        bool hanyaHuruf = true;
								        for (char c : namaVendor) {
								            if (!isalpha(c) && !isspace(c)) {
								                hanyaHuruf = false;
								                break;
								            }
								        }
								
								        if (!hanyaHuruf) {
								            cout << "[!] Peringatan: Nama vendor hanya boleh mengandung huruf!\n" << endl;
								        } else {
								            valid = true;
								        }
								    }
								
								    if (!valid) {
								        cout << "Masukkan kembali Nama Vendor : ";
								        getline(cin, namaVendor);
								    }
								}
						
                                cout << "Masukkan Jumlah Diambil : "; cin >> jumlahAmbil;

                                if (jumlahAmbil > databaseBarang[idx].stok)
                                {
                                    cout << "\n[!] Gagal! Stok tidak mencukupi." << endl;
                                }
                                else if (jumlahAmbil <= 0) {
                                    cout << "\n[!] Jumlah pengambilan tidak valid." << endl;
                                }
                                else {
                                    databaseBarang[idx].stok -= jumlahAmbil;
                                    long totalHargaJual = (long)jumlahAmbil * databaseBarang[idx].harga_jual;

                                    if (jumlahLog < 100) {
                                        databaseLog[jumlahLog++].infoLog = "KELUAR | Vendor " + namaVendor + " | " + to_string(jumlahAmbil) + " unit | Rp" + to_string(totalHargaJual);
                                    }
                                    cout << "\nBerhasil! Pengambilan dicatat. Sisa stok: " << databaseBarang[idx].stok << " Unit." << endl;
                                    
                                    // LOGIKA PERUBAHAN: Batas minimum stok diganti ke 10 unit
                                    if (databaseBarang[idx].stok <= 10) {
                                        cout << "\n[PEMBERITAHUAN] Stok " << databaseBarang[idx].nama << " sekarang kritis Tersisa kurang dari 10 unit!\n";
                                    }
                                }
                            }
                        }
                        kembaliKeMenu();
                    }
                    else if (pilihanSubMenu == 3)
                    {
                        clearScreen();
                        string targetSku;
                        cout << "--- UPDATE DATA BARANG ---" << endl;
                        cout << "Masukkan Kode SKU barang yang ingin diupdate: "; cin >> targetSku;

                        bool ditemukan = false;
                        for (int i = 0; i < jumlahBarang; i++)
                        {
                            if (databaseBarang[i].sku == targetSku)
                            {
                                ditemukan = true;
                                cout << "\n[Data Lama Barang]" << endl;
                                cout << "Nama Barang : " << databaseBarang[i].nama << endl;
                                cout << "Stok Lama   : " << databaseBarang[i].stok << endl;
                                cout << "------------------------------------------" << endl;

                                string namaBaru; int stokBaru;
                                long modalBaru, jualBaru;
                                cout << "Masukkan Nama Barang Baru : "; cin.ignore(); getline(cin, namaBaru);
                                cout << "Masukkan Jumlah Stok Baru : "; cin >> stokBaru;
                                cout << "Masukkan Harga Modal Baru : "; cin >> modalBaru;
                                cout << "Masukkan Harga Jual Baru  : "; cin >> jualBaru;

                                if (jumlahLog < 100)
                                {
                                    databaseLog[jumlahLog++].infoLog = "Update Barang SKU " + targetSku + ": " + databaseBarang[i].nama + " -> " + namaBaru;
                                }
                                databaseBarang[i].nama = namaBaru;
                                databaseBarang[i].stok = stokBaru;
                                databaseBarang[i].harga = modalBaru;
                                databaseBarang[i].harga_jual = jualBaru;
                                cout << "\nData barang berhasil diperbarui!" << endl;
                                break;
                            }
                        }
                        if (!ditemukan) cout << "\nKode SKU tidak ditemukan!" << endl;
                        kembaliKeMenu();
                    }
                    else if (pilihanSubMenu == 4)
                    {
                        clearScreen();
                        cout << "--- OPSI TAMPILAN GUDANG ---\n";
                        cout << "1. Tampilkan Biasa Sesuai Urutan Input\n";
                        cout << "2. Urutkan Berdasarkan Stok Paling Sedikit\n";
                        cout << "3. Urutkan Berdasarkan Harga Jual Tertinggi\n";
                        cout << "Pilih Opsi (1-3): ";
                        int opsiTampil;
                        cin >> opsiTampil;

                        Barang tempBarang[30];
                        for(int i = 0; i < jumlahBarang; i++) tempBarang[i] = databaseBarang[i];

                        if (opsiTampil == 2) {
                            for (int i = 0; i < jumlahBarang - 1; i++) {
                                for (int j = 0; j < jumlahBarang - i - 1; j++) {
                                    if (tempBarang[j].stok > tempBarang[j + 1].stok) {
                                        swap(tempBarang[j], tempBarang[j + 1]);
                                    }
                                }
                            }
                        } 
                        else if (opsiTampil == 3) {
                            for (int i = 0; i < jumlahBarang - 1; i++) {
                                  for (int j = 0; j < jumlahBarang - i - 1; j++) {
                                      if (tempBarang[j].harga_jual < tempBarang[j + 1].harga_jual) {
                                          swap(tempBarang[j], tempBarang[j + 1]);
                                      }
                                  }
                            }
                        }

                        clearScreen();
                        cout << "===================================================================================================\n";
                        cout << left << setw(4) << "NO"
                            << "| " << setw(12) << "KODE SKU"
                            << "| " << setw(23) << "NAMA BARANG"
                            << "| " << setw(15) << "JUMLAH STOK"
                            << "| " << setw(12) << "MODAL"
                            << "| " << setw(12) << "JUAL" 
                            << "| " << setw(15) << "STATUS STOK" << "\n";
                        cout << "===================================================================================================\n";

                        if (jumlahBarang == 0)
                        {
                            cout << "\n--- Data Stok Gudang Masih Kosong ---\n";
                        }
                        else {
                            for (int i = 0; i < jumlahBarang; i++) {
                            
                                string statusStok = (tempBarang[i].stok <= 10) ? "[STOK MENIPIS]" : "Aman";
                                
                                cout << left << setw(4) << (i + 1) << "| "
                                    << setw(12) << tempBarang[i].sku << "| "
                                    << setw(23) << tempBarang[i].nama << "| "
                                    << setw(15) << (to_string(tempBarang[i].stok) + " Unit") << "| "
                                    << "Rp" << setw(10) << tempBarang[i].harga << "| "
                                    << "Rp" << setw(10) << tempBarang[i].harga_jual << "| "
                                    << setw(15) << statusStok << "\n";
                            }
                        }
                        cout << "===================================================================================================\n";
                        kembaliKeMenu();
                    }
                    break;
                }
				
				case 2:
				{
					clearScreen();
					cout << "--- [MENU 2] CARI BARANG / KODE SKU (ADMIN) ---" << endl;
					
					if (jumlahBarang == 0) {
					    cout << "[!] Belum ada data barang di gudang." << endl;
					} 
					else {
					    string cariSku;
					    cout << "Masukkan Kode SKU yang dicari: "; 
					    cin >> cariSku;
					    
					    bool found = false;
					    for (int i = 0; i < jumlahBarang; i++) {
					        if (databaseBarang[i].sku == cariSku) {
					            cout << "\n--- DATA BARANG DITEMUKAN ---" << endl;
					            cout << "Nama Barang   : " << databaseBarang[i].nama << endl;
					            cout << "Kode SKU      : " << databaseBarang[i].sku << endl;
					            cout << "Stok Saat Ini : " << databaseBarang[i].stok << " Unit ";
					            
					            // Peringatan stok untuk Admin
					            if (databaseBarang[i].stok <= 10) {
					                cout << "[!!! STOK KRITIS !!!]";
					            }
					            cout << endl;
					
					            cout << "Harga Modal   : Rp" << databaseBarang[i].harga << endl;
					            cout << "Harga Jual    : Rp" << databaseBarang[i].harga_jual << endl;
					            cout << "------------------------------" << endl;
					            
					            found = true; 
					            break;
					        }
					    }
					    
					    if (!found) {
					        cout << "[!] Barang dengan SKU " << cariSku << " tidak ditemukan." << endl;
					    }
					}
					kembaliKeMenu();
					break;
				}

                case 3:
				{
                    clearScreen();
                    cout << "--- [MENU 3] LOG RIWAYAT TRANSAKSI REAL-TIME (ADMIN) ---" << endl << endl;
                    cout << "==========================================================" << endl;
                    cout << "NO | JENIS    | KETERANGAN         | HARGA (MASUK/KELUAR)" << endl;
                    cout << "==========================================================" << endl;

                    long totalPemasukan = 0, totalPengeluaran = 0;
                    int nomor = 1;
                    for (int i = 0; i < jumlahLog; i++)

                    {
                        if (databaseLog[i].infoLog.find("Rp") != string::npos)
                        {
                            string sTemp = databaseLog[i].infoLog;
                            size_t posBaris = sTemp.find("Rp");
                            long nilai = stol(sTemp.substr(posBaris + 2));

                            cout << setw(2) << nomor++ << " | " << databaseLog[i].infoLog << endl;

                            if (sTemp.find("MASUK") != string::npos)
                            {
                                totalPengeluaran += nilai;

                            }
                            else if (sTemp.find("KELUAR") != string::npos)
                            {
                                totalPemasukan += nilai;
                            }
                        }
                    }
                    cout << "==========================================================" << endl;
                    cout << "TOTAL MODAL BARANG MASUK  : Rp" << totalPengeluaran << endl;
                    cout << "TOTAL OMSET BARANG KELUAR : Rp" << totalPemasukan << endl;
                    cout << "----------------------------------------------------------" << endl;
                    cout << "SALDO/KEUNTUNGAN BERSIH    : Rp" << (totalPemasukan - totalPengeluaran) << endl;
                    kembaliKeMenu();
                    break;
				}

                case 4:
                {
                    clearScreen();
                    cout << "--- [MENU 4] LOG RIWAYAT TRANSAKSI REAL-TIME (ADMIN) ---\n\n";
                    tampilkanLogRapi(databaseLog, jumlahLog);
                    kembaliKeMenu();
                    break;
                }

                case 5:
                {
                    clearScreen();
                    cout << "--- [MENU 5] PRINT BARCODE & LAPORAN ---" << endl;
                    if (jumlahBarang == 0)
                    {
                        cout << "[X] Gudang kosong!" << endl;
                    }
                    else {
                        string cariSku;
                        cout << "Masukkan kode SKU barang: "; cin >> cariSku;
                        bool ketemuSku = false;

                        for (int i = 0; i < jumlahBarang; i++)
                        {
                            if (databaseBarang[i].sku == cariSku)
                            {
                                ketemuSku = true;
                                cout << "\n==========================================" << endl;
                                cout << "        HASIL GENERATE BARCODE            " << endl;
                                cout << "==========================================" << endl;
                                cout << " Nama Barang : " << databaseBarang[i].nama << endl;
                                cout << " Kode SKU    : " << databaseBarang[i].sku << endl;
                                cout << " Tampilan Barcode: \n\n   ";

                                for (size_t k = 0; k < databaseBarang[i].sku.length(); k++)
                                {
                                    cout << ((databaseBarang[i].sku[k] % 2 == 0) ? "|||" : "|");
                                }
                                cout << "\n    * " << databaseBarang[i].sku << " *" << endl;

                                if (jumlahLog < 100) {
                                    databaseLog[jumlahLog++].infoLog = "Cetak Barcode SKU: " + databaseBarang[i].sku;
                                }
                                break;
                            }
                        }
                        if (!ketemuSku) cout << "\n[X] Kode SKU tidak terdaftar." << endl;
                    }
                    kembaliKeMenu();
                    break;
                }

                case 6:
                    tetapDiMenuUtama = false;
                    break;

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
                    cout << "--- [MENU 1] CARI BARANG / KODE SKU (STAFF) ---" << endl;
                    if (jumlahBarang == 0) {
                        cout << "[!] Belum ada data barang di gudang." << endl;
                    }
                    else {
                        string cariSku;
                        cout << "Masukkan Kode SKU yang dicari: "; cin >> cariSku;
                        bool found = false;
                        for (int i = 0; i < jumlahBarang; i++)
                        {
                            if (databaseBarang[i].sku == cariSku)
                            {
                                cout << "\nNama Barang   : " << databaseBarang[i].nama << endl;
                                cout << "Kode SKU      : " << databaseBarang[i].sku << endl;
                                cout << "Stok Saat Ini : " << databaseBarang[i].stok << " Unit ";
                                
                                // LOGIKA PERUBAHAN: Staff juga melihat warning jika stok <= 10
                                if (databaseBarang[i].stok <= 10) cout << "[STOK MENIPIS]";
                                cout << endl;

                                cout << "Harga Modal   : Rp" << databaseBarang[i].harga << endl;
                                cout << "Harga Jual    : Rp" << databaseBarang[i].harga_jual << endl;
                                found = true; break;
                            }
                        }
                        if (!found) cout << "[!] Barang tidak ditemukan." << endl;
                    }
                    kembaliKeMenu();
                    break;
                }
                case 2:
                    clearScreen();
                    cout << "--- [MENU 2] LOG TRANSAKSI REAL-TIME (STAFF) ---\n\n";
                    tampilkanLogRapi(databaseLog, jumlahLog);
                    kembaliKeMenu();
                    break;

                case 3:
                    tetapDiMenuUtama = false;
                    break;

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
