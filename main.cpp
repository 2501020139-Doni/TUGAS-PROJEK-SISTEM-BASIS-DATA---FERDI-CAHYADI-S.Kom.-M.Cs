#include <iostream>
#include <stdlib.h>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>

using namespace std;

// Konfigurasi koneksi database MySQL
const string SERVER = "tcp://127.0.0.1:3306";
const string USERNAME = "root";
const string PASSWORD = "";
const string DATABASE = "db_arsip_digital";

int main()
{
    sql::Driver* driver;
    sql::Connection* con;

    // Membuat koneksi ke server MySQL dan memilih database yang digunakan
    try
    {
        driver = get_driver_instance();

        con = driver->connect(
            SERVER,
            USERNAME,
            PASSWORD
        );

        con->setSchema(DATABASE);

        cout << "==================================" << endl;
        cout << " KONEKSI DATABASE BERHASIL" << endl;
        cout << "==================================" << endl;

        int menuLogin;

        // Menyimpan informasi pengguna yang sedang login.
        // Data ini digunakan untuk pencatatan aktivitas
        // dan mengetahui hak akses pengguna.
        int idLogin;
        string namaLogin;
        string roleLogin;


        // Perulangan menu login.
        // Akan terus tampil hingga pengguna berhasil login
        // atau memilih keluar dari program.
        while (true)
        {
            cout << "\n======================================" << endl;
            cout << " SISTEM MANAJEMEN ARSIP SURAT DAN DOKUMEN" << endl;
            cout << "======================================" << endl;

            cout << "1. Login" << endl;
            cout << "2. Registrasi User" << endl;
            cout << "0. Keluar" << endl;

            cout << "Pilih : ";
            cin >> menuLogin;
            cin.ignore();

            if (menuLogin == 1)
            {
                string usernameLogin;
                string passwordLogin;

                cout << "\n========== LOGIN ==========\n";

                cout << "Username : ";
                getline(cin, usernameLogin);

                cout << "Password : ";
                getline(cin, passwordLogin);

                sql::PreparedStatement* login;
                sql::ResultSet* resLogin;

                // Menggunakan Prepared Statement agar query lebih aman
                // dari SQL Injection.
                login = con->prepareStatement(
                    "SELECT * FROM user WHERE username=? AND password=?"
                );

                login->setString(1, usernameLogin);
                login->setString(2, passwordLogin);

                resLogin = login->executeQuery();

                // Jika data ditemukan maka login berhasil,
                // jika tidak maka username atau password salah.
                if (resLogin->next())
                {
                    idLogin = resLogin->getInt("id_user");
                    namaLogin = resLogin->getString("nama");
                    roleLogin = resLogin->getString("role");

                    cout << "\nLogin Berhasil" << endl;
                    cout << "Selamat Datang " << namaLogin << endl;

                    delete resLogin;
                    delete login;

                    break;
                }
                else
                {
                    cout << "\nUsername atau Password Salah!" << endl;

                    delete resLogin;
                    delete login;
                }
            }
            else if (menuLogin == 2)
            {
                string nama;
                string username;
                string password;
                string email;

                cout << "\n===== REGISTRASI USER =====" << endl;

                cout << "Nama : ";
                getline(cin, nama);

                cout << "Username : ";
                getline(cin, username);

                cout << "Password : ";
                getline(cin, password);

                cout << "Email : ";
                getline(cin, email);

                sql::PreparedStatement* pstmt;

                // Menyimpan data user baru ke tabel user.
                // Role otomatis menjadi "User".
                pstmt = con->prepareStatement(
                    "INSERT INTO user(nama,username,password,email,role)"
                    " VALUES(?,?,?,?,?)"
                );

                pstmt->setString(1, nama);
                pstmt->setString(2, username);
                pstmt->setString(3, password);
                pstmt->setString(4, email);
                pstmt->setString(5, "User");

                pstmt->execute();

                delete pstmt;

                cout << "\nRegistrasi Berhasil." << endl;
                cout << "Silakan Login.\n";
            }
            else if (menuLogin == 0)
            {
                return 0;
            }
            else
            {
                cout << "Menu tidak tersedia." << endl;
            }
        }

        // Mencatat aktivitas login ke tabel aktivitas.
        sql::PreparedStatement* log;

        log = con->prepareStatement(
            "INSERT INTO aktivitas(id_user,aktivitas,waktu) "
            "VALUES(?, ?, NOW())"
        );

        log->setInt(1, idLogin);
        log->setString(2, "Login Sistem");

        log->execute();

        delete log;



        int pilihan;

        // Menu utama akan terus berjalan
        // sampai pengguna memilih Logout atau Keluar.
        do
        {

            cout << "\n========================================" << endl;
            cout << "SISTEM MANAJEMEN ARSIP SURAT DAN DOKUMEN" << endl;
            cout << "========================================" << endl;

            cout << "\nLOGIN\n" << endl;

            cout << "\n===== MENU USER =====" << endl;
            cout << "1. Tambah User" << endl;
            cout << "2. Tampilkan User" << endl;
            cout << "3. Edit User" << endl;
            cout << "4. Hapus User" << endl;

            cout << "\n===== MENU KATEGORI =====" << endl;
            cout << "5. Tambah Kategori" << endl;
            cout << "6. Tampilkan Kategori" << endl;
            cout << "7. Edit Kategori" << endl;
            cout << "8. Hapus Kategori" << endl;

            cout << "\n===== MENU DOKUMEN =====" << endl;
            cout << "9. Tambah Dokumen" << endl;
            cout << "10. Tampilkan Dokumen" << endl;
            cout << "11. Cari Dokumen" << endl;
            cout << "12. Edit Dokumen" << endl;
            cout << "13. Hapus Dokumen" << endl;

            cout << "\n===== MENU AKTIVITAS =====" << endl;
            cout << "14. Tampilkan Aktivitas" << endl;

            cout << "\n===== MENU LAPORAN =====" << endl;
            cout << "15. Semua Dokumen" << endl;
            cout << "16. Berdasarkan Kategori" << endl;
            cout << "17. Berdasarkan User" << endl;

            cout << "\n18. Logout" << endl;
            cout << "0. Keluar" << endl;
            cout << "Pilih Menu : ";
            cin >> pilihan;
            cin.ignore();

            // Menjalankan fitur sesuai nomor menu yang dipilih pengguna.
            switch (pilihan)
            {

            // ===== MENU TAMBAH USER =====
            case 1:
            {

                string nama;
                string username;
                string password;
                string email;
                string role;

                cout << "\n=== TAMBAH USER ===" << endl;

                cout << "Nama      : ";
                getline(cin, nama);

                cout << "Username  : ";
                getline(cin, username);

                cout << "Password  : ";
                getline(cin, password);

                cout << "Email     : ";
                getline(cin, email);

                cout << "Role      : ";
                getline(cin, role);

                sql::PreparedStatement* pstmt;

                pstmt = con->prepareStatement(
                    "INSERT INTO user "
                    "(nama,username,password,email,role) "
                    "VALUES(?,?,?,?,?)"
                );

                pstmt->setString(1, nama);
                pstmt->setString(2, username);
                pstmt->setString(3, password);
                pstmt->setString(4, email);
                pstmt->setString(5, role);

                pstmt->execute();

                sql::PreparedStatement* log;

                log = con->prepareStatement(
                    "INSERT INTO aktivitas(id_user,aktivitas,waktu) "
                    "VALUES(?, ?, NOW())"
                );

                log->setInt(1, idLogin);
                log->setString(2, "Menambahkan User");

                log->execute();

                delete log;

                cout << "\nData User Berhasil Disimpan!" << endl;

                delete pstmt;

                break;
            }

            // ===== MENU TAMPIL USER =====
            case 2:
            {
                sql::Statement* stmt;
                sql::ResultSet* res;

                stmt = con->createStatement();
                res = stmt->executeQuery("SELECT * FROM user");

                cout << "\n===== DATA USER =====\n";

                while (res->next())
                {
                    cout << "ID User : "
                        << res->getInt("id_user") << endl;

                    cout << "Nama : "
                        << res->getString("nama") << endl;

                    cout << "Username : "
                        << res->getString("username") << endl;

                    cout << "Email : "
                        << res->getString("email") << endl;

                    cout << "Role : "
                        << res->getString("role") << endl;

                    cout << "------------------------" << endl;
                }

                delete res;
                delete stmt;
            }
            break;

            // ===== MENU EDIT USER =====
            case 3:
            {
                int id;
                string nama;

                cout << "ID User : ";
                cin >> id;
                cin.ignore();

                cout << "Nama Baru : ";
                getline(cin, nama);

                sql::PreparedStatement* pstmt;

                pstmt = con->prepareStatement(
                    "UPDATE user SET nama=? WHERE id_user=?"
                );

                pstmt->setString(1, nama);
                pstmt->setInt(2, id);

                pstmt->execute();

                cout << "User berhasil diubah\n";

                delete pstmt;
            }
            break;

            // ===== MENU HAPUS USER =====
            case 4:
            {
                int id;

                cout << "ID User : ";
                cin >> id;

                sql::PreparedStatement* pstmt;

                pstmt = con->prepareStatement(
                    "DELETE FROM user WHERE id_user=?"
                );

                pstmt->setInt(1, id);

                pstmt->execute();

                cout << "User berhasil dihapus\n";

                delete pstmt;
            }
            break;

            // ===== MENU TAMBAH KATEGORI =====
            case 5:
            {

                string namaKategori;
                string keterangan;

                cout << "\n=== TAMBAH KATEGORI ===" << endl;

                cout << "Nama Kategori : ";
                getline(cin, namaKategori);

                cout << "Keterangan    : ";
                getline(cin, keterangan);

                sql::PreparedStatement* pstmt;

                pstmt = con->prepareStatement(
                    "INSERT INTO kategori "
                    "(nama_kategori,keterangan) "
                    "VALUES(?,?)"
                );

                pstmt->setString(1, namaKategori);
                pstmt->setString(2, keterangan);

                pstmt->execute();

                sql::PreparedStatement* log;

                log = con->prepareStatement(
                    "INSERT INTO aktivitas(id_user,aktivitas,waktu) "
                    "VALUES(?, ?, NOW())"
                );

                log->setInt(1, idLogin);
                log->setString(2, "Menambahkan Kategori");

                log->execute();

                delete log;

                cout << "\nKategori Berhasil Ditambahkan!" << endl;

                delete pstmt;

                break;
            }

            // ===== MENU TAMPIL KATEGORI =====
            case 6:
            {
                sql::Statement* stmt;
                sql::ResultSet* res;

                stmt = con->createStatement();

                res = stmt->executeQuery(
                    "SELECT * FROM kategori"
                );

                cout << "\n===== DATA KATEGORI =====\n" << endl;

                while (res->next())
                {
                    cout << "ID : "
                        << res->getInt("id_kategori");

                    cout << "\nKategori : "
                        << res->getString("nama_kategori");

                    cout << "\nKeterangan : "
                        << res->getString("keterangan");

                    cout << "\n---------------------\n" << endl;
                }

                delete res;
                delete stmt;
            }
            break;

            // ===== MENU EDIT KATEGORI =====
            case 7:
            {
                int id;
                string nama;
                string ket;

                cout << "ID Kategori : ";
                cin >> id;
                cin.ignore();

                cout << "Nama Baru : ";
                getline(cin, nama);

                cout << "Keterangan Baru : ";
                getline(cin, ket);

                sql::PreparedStatement* pstmt;

                pstmt = con->prepareStatement(
                    "UPDATE kategori SET nama_kategori=?, keterangan=? WHERE id_kategori=?"
                );

                pstmt->setString(1, nama);
                pstmt->setString(2, ket);
                pstmt->setInt(3, id);

                pstmt->execute();

                cout << "Kategori berhasil diubah" << endl;

                delete pstmt;
            }
            break;

            // ===== MENU HAPUS KATEGORI =====
            case 8:
            {
                int id;

                cout << "ID Kategori : ";
                cin >> id;

                sql::PreparedStatement* pstmt;

                pstmt = con->prepareStatement(
                    "DELETE FROM kategori WHERE id_kategori=?"
                );

                pstmt->setInt(1, id);

                pstmt->execute();

                cout << "Kategori berhasil dihapus" << endl;

                delete pstmt;
            }
            break;

            // ===== MENU TAMBAH DOKUMEN =====
            case 9:
            {

                string nomor;
                string judul;
                string tanggal;
                string file;
                string deskripsi;

                int idUser;
                int idKategori;

                cout << "\n=== TAMBAH DOKUMEN ===" << endl;

                sql::Statement* stmtUser;
                sql::ResultSet* resUser;

                stmtUser = con->createStatement();

                resUser = stmtUser->executeQuery(
                    "SELECT * FROM user"
                );

                cout << "\n===== DATA USER =====" << endl;

                while (resUser->next())
                {
                    cout << "ID : "
                        << resUser->getInt("id_user")
                        << " | Nama : "
                        << resUser->getString("nama")
                        << endl;
                }

                delete resUser;
                delete stmtUser;

                sql::Statement* stmtKategori;
                sql::ResultSet* resKategori;

                stmtKategori = con->createStatement();

                resKategori = stmtKategori->executeQuery(
                    "SELECT * FROM kategori"
                );

                cout << "\n===== DATA KATEGORI =====" << endl;

                while (resKategori->next())
                {
                    cout << "ID : "
                        << resKategori->getInt("id_kategori")
                        << " | "
                        << resKategori->getString("nama_kategori")
                        << endl;
                }

                delete resKategori;
                delete stmtKategori;

                cout << "Nomor Dokumen : ";
                getline(cin, nomor);

                cout << "Judul Dokumen : ";
                getline(cin, judul);

                cout << "Tanggal Upload (YYYY-MM-DD) : ";
                getline(cin, tanggal);

                cout << "Nama File : ";
                getline(cin, file);

                cout << "Deskripsi : ";
                getline(cin, deskripsi);

                cout << "ID User : ";
                cin >> idUser;

                cout << "ID Kategori : ";
                cin >> idKategori;

                cin.ignore();

                sql::PreparedStatement* pstmt;

                pstmt = con->prepareStatement(
                    "INSERT INTO dokumen "
                    "(nomor_dokumen,judul_dokumen,"
                    "tanggal_upload,file_dokumen,"
                    "deskripsi,id_user,id_kategori)"
                    "VALUES(?,?,?,?,?,?,?)"
                );

                pstmt->setString(1, nomor);
                pstmt->setString(2, judul);
                pstmt->setString(3, tanggal);
                pstmt->setString(4, file);
                pstmt->setString(5, deskripsi);
                pstmt->setInt(6, idUser);
                pstmt->setInt(7, idKategori);

                pstmt->execute();

                sql::PreparedStatement* log;

                log = con->prepareStatement(
                    "INSERT INTO aktivitas(id_user,aktivitas,waktu) "
                    "VALUES(?, ?, NOW())"
                );

                log->setInt(1, idLogin);
                log->setString(2, "Menambahkan Dokumen");

                log->execute();

                delete log;

                cout << "\nDokumen Berhasil Disimpan!" << endl;

                delete pstmt;

                break;
            }

            // ===== MENU TAMPIL DOKUMEN =====
            case 10:
            {

                sql::Statement* stmt;
                sql::ResultSet* res;

                stmt = con->createStatement();

                res = stmt->executeQuery(
                    "SELECT d.*, u.nama, k.nama_kategori "
                    "FROM dokumen d "
                    "JOIN user u ON d.id_user = u.id_user "
                    "JOIN kategori k ON d.id_kategori = k.id_kategori"
                );

                cout << "\n===== DATA DOKUMEN =====\n" << endl;

                while (res->next())
                {

                    cout << "ID Dokumen      : "
                        << res->getInt("id_dokumen")
                        << endl;

                    cout << "Nomor Dokumen   : "
                        << res->getString("nomor_dokumen")
                        << endl;

                    cout << "Judul Dokumen   : "
                        << res->getString("judul_dokumen")
                        << endl;

                    cout << "Tanggal Upload  : "
                        << res->getString("tanggal_upload")
                        << endl;

                    cout << "File Dokumen    : "
                        << res->getString("file_dokumen")
                        << endl;

                    cout << "Deskripsi       : "
                        << res->getString("deskripsi")
                        << endl;

                    cout << "Kategori        : "
                        << res->getString("nama_kategori")
                        << endl;

                    cout << "Pengunggah      : "
                        << res->getString("nama")
                        << endl;

                    cout << "--------------------------"
                        << endl;
                }

                delete res;
                delete stmt;

                break;
            }

            // ===== MENU CARI DOKUMEN =====
            case 11:
            {
                string keyword;

                cout << "Masukkan Judul Dokumen : ";
                getline(cin, keyword);

                sql::PreparedStatement* pstmt;
                sql::ResultSet* res;

                pstmt = con->prepareStatement(
                    "SELECT d.*, u.nama, k.nama_kategori "
                    "FROM dokumen d "
                    "JOIN user u ON d.id_user = u.id_user "
                    "JOIN kategori k ON d.id_kategori = k.id_kategori "
                    "WHERE d.judul_dokumen LIKE ?"
                );

                // Operator LIKE digunakan agar pencarian
                // dapat menemukan judul yang mengandung keyword.
                pstmt->setString(1, "%" + keyword + "%");

                res = pstmt->executeQuery();

                while (res->next())
                {
                    cout << "\nID : "
                        << res->getInt("id_dokumen");

                    cout << "\nJudul : "
                        << res->getString("judul_dokumen");

                    cout << "\nNomor : "
                        << res->getString("nomor_dokumen");

                    cout << "\nKategori : "
                        << res->getString("nama_kategori");

                    cout << "\nPengunggah : "
                        << res->getString("nama");

                    cout << "\nTanggal Upload : "
                        << res->getString("tanggal_upload");

                    cout << "\n-------------------" << endl;
                }

                delete res;
                delete pstmt;
            }
            break;

            // ===== MENU EDIT DOKUMEN =====
            case 12:
            {
                int id;
                string judul;

                cout << "ID Dokumen : ";
                cin >> id;
                cin.ignore();

                cout << "Judul Baru : ";
                getline(cin, judul);

                sql::PreparedStatement* pstmt;

                pstmt = con->prepareStatement(
                    "UPDATE dokumen SET judul_dokumen=? WHERE id_dokumen=?"
                );

                pstmt->setString(1, judul);
                pstmt->setInt(2, id);

                pstmt->execute();

                cout << "Dokumen berhasil diubah" << endl;

                delete pstmt;
            }
            break;

            // ===== MENU HAPUS DOKUMEN =====
            case 13:
            {
                int id;

                cout << "ID Dokumen : ";
                cin >> id;

                sql::PreparedStatement* pstmt;

                pstmt = con->prepareStatement(
                    "DELETE FROM dokumen WHERE id_dokumen=?"
                );

                pstmt->setInt(1, id);

                pstmt->execute();

                cout << "Dokumen berhasil dihapus" << endl;

                delete pstmt;
            }
            break;

            // ===== MENU TAMPIL AKTIVITAS =====
            case 14:
            {

                sql::Statement* stmt;
                sql::ResultSet* res;

                stmt = con->createStatement();

                res = stmt->executeQuery(

                    "SELECT aktivitas.id_log,"
                    "user.nama,"
                    "aktivitas.aktivitas,"
                    "aktivitas.waktu "

                    "FROM aktivitas "

                    "JOIN user "

                    "ON aktivitas.id_user=user.id_user "

                    "ORDER BY aktivitas.waktu DESC"

                );

                cout << "\n===== DATA AKTIVITAS =====" << endl << endl;

                while (res->next())
                {

                    cout << "ID Log     : " << res->getInt("id_log") << endl;

                    cout << "Nama User  : " << res->getString("nama") << endl;

                    cout << "Aktivitas  : " << res->getString("aktivitas") << endl;

                    cout << "Waktu      : " << res->getString("waktu") << endl;

                    cout << "---------------------------" << endl;

                }

                delete res;
                delete stmt;

                break;

            }

            // ===== MENU LAPORAN SEMUA DOKUMEN =====
            case 15:
            {

                sql::Statement* stmt;
                sql::ResultSet* res;

                stmt = con->createStatement();

                // Menggabungkan tiga tabel (dokumen, user, kategori)
                // agar informasi yang ditampilkan lebih lengkap.
                res = stmt->executeQuery(
                    "SELECT d.*, u.nama, k.nama_kategori "
                    "FROM dokumen d "
                    "JOIN user u ON d.id_user = u.id_user "
                    "JOIN kategori k ON d.id_kategori = k.id_kategori"
                );

                cout << "\n===== LAPORAN DOKUMEN =====\n" << endl;

                while (res->next())
                {

                    cout << "ID Dokumen      : "
                        << res->getInt("id_dokumen")
                        << endl;

                    cout << "Nomor Dokumen   : "
                        << res->getString("nomor_dokumen")
                        << endl;

                    cout << "Judul Dokumen   : "
                        << res->getString("judul_dokumen")
                        << endl;

                    cout << "Tanggal Upload  : "
                        << res->getString("tanggal_upload")
                        << endl;

                    cout << "File Dokumen    : "
                        << res->getString("file_dokumen")
                        << endl;

                    cout << "Deskripsi       : "
                        << res->getString("deskripsi")
                        << endl;

                    cout << "Kategori        : "
                        << res->getString("nama_kategori")
                        << endl;

                    cout << "Pengunggah      : "
                        << res->getString("nama")
                        << endl;

                    cout << "--------------------------"
                        << endl;
                }

                delete res;
                delete stmt;

                break;
            }

            // ===== MENU LAPORAN BERDASARKAN KATEGORI =====
            case 16:
            {
                int idKategori;

                cout << "ID Kategori : ";
                cin >> idKategori;

                sql::PreparedStatement* pstmt;
                sql::ResultSet* res;

                pstmt = con->prepareStatement(
                    "SELECT * FROM dokumen WHERE id_kategori=?"
                );

                pstmt->setInt(1, idKategori);

                res = pstmt->executeQuery();

                while (res->next())
                {
                    cout << res->getString("judul_dokumen") << endl;
                }

                delete res;
                delete pstmt;
            }
            break;

            // ===== MENU LAPORAN BERDASARKAN USER =====
            case 17:
            {
                int idUser;

                cout << "ID User : ";
                cin >> idUser;

                sql::PreparedStatement* pstmt;
                sql::ResultSet* res;

                pstmt = con->prepareStatement(
                    "SELECT * FROM dokumen WHERE id_user=?"
                );

                pstmt->setInt(1, idUser);

                res = pstmt->executeQuery();

                while (res->next())
                {
                    cout << res->getString("judul_dokumen") << endl;
                }

                delete res;
                delete pstmt;
            }
            break;

            // ===== MENU LOGOUT =====
            case 18:
            {
                cout << "\nLogout berhasil...\n";

                sql::PreparedStatement* log;

                log = con->prepareStatement(
                    "INSERT INTO aktivitas(id_user,aktivitas,waktu) "
                    "VALUES(?, ?, NOW())"
                );

                log->setInt(1, idLogin);
                log->setString(2, "Logout Sistem");
                log->execute();

                delete log;

                // Kembali ke halaman login setelah logout.
                return main();
            }



            case 0:
                cout << "\nProgram Selesai..." << endl;
                break;

            default:
                cout << "\nMenu Tidak Tersedia!" << endl;
            }

        } while (pilihan != 0);

        delete con;
    }

    // Menangani kesalahan yang berasal dari database,
    // misalnya koneksi gagal atau query error.
    catch (sql::SQLException& e)
    {
        cout << "\nERROR DATABASE!" << endl;
        cout << e.what() << endl;
    }

    system("pause");

    return 0;
}