// kelompok 6: 123250009, 123250014, 123250027
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

struct Ijasah {
    long noIjasah;
    char jenisIjasah[30];
    char namaSekolah[50];
};

Ijasah dataIjasah[100];
int jumlahData = 0;
string namaFile = ""; 

// Fungsi buat ngecek riwayat file teks yang pernah dibuat user
void cekfile() {
    bool fileada = false;
    string fileMendaftar;
    cout << "Daftar File yang Ada : " << endl;
    cout << "--------------------" << endl;

    ifstream fileDaftar("daftarfile.txt");
    if (!fileDaftar.is_open()) {
        cout << "(Belum ada riwayat file yang disimpan)" << endl;
        cout << "--------------------" << endl;
        return;
    } else {
        while (getline(fileDaftar, fileMendaftar)) {
            if (!fileMendaftar.empty()) {
                cout << "- " << fileMendaftar << endl;
                fileada = true;
            }
        }
    }
    if (!fileada) {
        cout << "(Belum ada riwayat file yang disimpan)" << endl;
    }
    cout << "--------------------" << endl;
    fileDaftar.close();
}

// Catat nama file baru ke daftarfile.txt kalau belum ada di list
void catatKeDaftarFile(string fileBaru) {
    bool ada = false;
    string fileCek;
    
    ifstream cek("daftarfile.txt");
    while (getline(cek, fileCek)) {
        if (fileCek == fileBaru) {
            ada = true;
            break;
        }
    }
    cek.close();

    if (!ada) {
        ofstream tambahfile("daftarfile.txt", ios::app);
        tambahfile << fileBaru << endl;
        tambahfile.close();
    }
}

// Ambil data dari file target terus dipindahin ke array struct di memori
bool muatDataDariFile(string namaFileTarget) {
    ifstream file(namaFileTarget);
    if (!file.is_open()) {
        return false;
    }

    jumlahData = 0;
    long no;
    char jenisIjasah[30];
    char namaSekolah[50];

    while (file >> no) {
        file.ignore(); // Lewatin karakter '|' setelah nomor ijazah
        file.getline(jenisIjasah, 30, '|');
        file.getline(namaSekolah, 50);

        dataIjasah[jumlahData].noIjasah = no;
        strcpy(dataIjasah[jumlahData].jenisIjasah, jenisIjasah);
        strcpy(dataIjasah[jumlahData].namaSekolah, namaSekolah);
        jumlahData++;
    }
    file.close();
    return true;
}

// Tulis ulang semua isi array dataIjasah yang aktif ke file .txt
void simpanData() {
    ofstream file(namaFile);
    for (int i = 0; i < jumlahData; i++) {
        file << dataIjasah[i].noIjasah << "|";
        file << dataIjasah[i].jenisIjasah << "|";
        file << dataIjasah[i].namaSekolah << endl;
    }
    file.close();
}

void inputData() {
    int jum;
    
    cekfile();
    cout << "\n--- INPUT DATA ---" << endl;
    cout << "Masukkan Nama File Target (cth: Ijasah.txt): ";
    cin >> namaFile;

    cout << "Jumlah Data yang akan di-Input: "; 
    cin >> jum;

    // Load data lama dulu biar ga ketimpa pas di-save ulang nanti
    muatDataDariFile(namaFile);

    if (jumlahData + jum > 100) {
        cout << "Jumlah data melebihi kapasitas array!" << endl;
        return;
    }

    for (int i = 0; i < jum; i++) {
        cout << "\nData Yang Ke - " << i + 1 << endl;
        cout << "No Ijasah      : "; 
        cin >> dataIjasah[jumlahData].noIjasah;
        cin.ignore(); // Bersihin sisa enter dari cin>> sebelum masuk ke cin.getline()

        cout << "Jenis Ijasah   : "; 
        cin.getline(dataIjasah[jumlahData].jenisIjasah, 30);

        cout << "Nama Sekolah   : "; 
        cin.getline(dataIjasah[jumlahData].namaSekolah, 50);
        jumlahData++;
    }

    simpanData();
    catatKeDaftarFile(namaFile);
    
    cout << "\nData Berhasil Ditambahkan ke " << namaFile << "!" << endl;
}

void tampilData() {
    string fileDicari;

    cout << "\n--- TAMPIL DATA ---\n" << endl;
    cekfile();

    cout << "Nama File yang akan ditampilkan: "; 
    cin >> fileDicari;

    if (!muatDataDariFile(fileDicari)) {
        cout << "File tidak ditemukan atau belum dibuat!" << endl;
        return;
    }

    namaFile = fileDicari; 

    cout << "\n--- DATA DARI FILE: " << namaFile << " ---" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(4) << "No";
    cout << "| " << setw(15) << "No Ijasah";
    cout << "| " << setw(15) << "Jenis Ijasah";
    cout << "| " << setw(25) << "Nama Sekolah" << " |" << endl;
    cout << "---------------------------------------------------------------------------" << endl;

    for (int i = 0; i < jumlahData; i++) {
        cout << "| " << left << setw(4) << i + 1;
        cout << "| " << setw(15) << dataIjasah[i].noIjasah;
        cout << "| " << setw(15) << dataIjasah[i].jenisIjasah;
        cout << "| " << setw(25) << dataIjasah[i].namaSekolah << " |" << endl;
    }
    cout << "---------------------------------------------------------------------------" << endl;
}

void sequentialSearch() {
    long cari;
    int ketemu = -1;
    cout << "\nMasukkan No Ijasah yang dicari (Sequential): ";
    cin >> cari;

    for (int i = 0; i < jumlahData; i++) {
        if (dataIjasah[i].noIjasah == cari) {
            ketemu = i;
            break;
        }
    }

    if (ketemu != -1) {
        cout << "\nData ditemukan!" << endl;
        cout << "No Ijasah      : " << dataIjasah[ketemu].noIjasah << endl;
        cout << "Jenis Ijasah   : " << dataIjasah[ketemu].jenisIjasah << endl;
        cout << "Nama Sekolah   : " << dataIjasah[ketemu].namaSekolah << endl;
    } else {
        cout << "\nData tidak ditemukan." << endl;
    }
}

void binarySearch() {
    // Sort array-nya dulu pake bubble sort karena binary search wajib urut
    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if (dataIjasah[j].noIjasah > dataIjasah[j+1].noIjasah) {
                swap(dataIjasah[j], dataIjasah[j+1]);
            }
        }
    }

    long cari;
    cout << "\nMasukkan No Ijasah yang dicari (Binary): ";
    cin >> cari;

    int low = 0, high = jumlahData - 1, ketemu = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (dataIjasah[mid].noIjasah == cari) {
            ketemu = mid;
            break;
        } else if (dataIjasah[mid].noIjasah < cari) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (ketemu != -1) {
        cout << "\nData ditemukan!" << endl;
        cout << "No Ijasah      : " << dataIjasah[ketemu].noIjasah << endl;
        cout << "Jenis Ijasah   : " << dataIjasah[ketemu].jenisIjasah << endl;
        cout << "Nama Sekolah   : " << dataIjasah[ketemu].namaSekolah << endl;
    } else {
        cout << "\nData tidak ditemukan." << endl;
    }
}

void searching() {
    string fileTarget;
    
    cout << "--- MENU SEARCHING ---" << endl;
    cekfile();
    cout << "Pilih Nama File Sumber Data: ";
    cin >> fileTarget;

    if (!muatDataDariFile(fileTarget)) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }
    namaFile = fileTarget;

    int menuCari;
    cout << "\nALGORITMA SEARCHING :" << endl;
    cout << "1. SEQUENTIAL SEARCH" << endl;
    cout << "2. BINARY SEARCH" << endl;
    cout << "3. Kembali" << endl;
    cout << "Pilih : ";
    cin >> menuCari;

    switch (menuCari) {
        case 1: sequentialSearch(); break;
        case 2: binarySearch(); break;
        default: return;
    }
}

void bubbleSort() {
    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if (dataIjasah[j].noIjasah > dataIjasah[j+1].noIjasah) swap(dataIjasah[j], dataIjasah[j+1]);
        }
    }
}

void selectionSort() {
    for (int i = 0; i < jumlahData - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < jumlahData; j++) {
            if (dataIjasah[j].noIjasah < dataIjasah[minIdx].noIjasah) minIdx = j;
        }
        swap(dataIjasah[i], dataIjasah[minIdx]);
    }
}

void insertionSort() {
    for (int i = 1; i < jumlahData; i++) {
        Ijasah key = dataIjasah[i];
        int j = i - 1;
        while (j >= 0 && dataIjasah[j].noIjasah > key.noIjasah) {
            dataIjasah[j + 1] = dataIjasah[j];
            j--;
        }
        dataIjasah[j + 1] = key;
    }
}

void shellSort() {
    for (int gap = jumlahData / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < jumlahData; i++) {
            Ijasah temp = dataIjasah[i];
            int j;
            for (j = i; j >= gap && dataIjasah[j - gap].noIjasah > temp.noIjasah; j -= gap) {
                dataIjasah[j] = dataIjasah[j - gap];
            }
            dataIjasah[j] = temp;
        }
    }
}

int partition(int low, int high) {
    long pivot = dataIjasah[high].noIjasah;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (dataIjasah[j].noIjasah < pivot) {
            i++;
            swap(dataIjasah[i], dataIjasah[j]);
        }
    }
    swap(dataIjasah[i + 1], dataIjasah[high]);
    return (i + 1);
}

void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void merge(int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    Ijasah* L = new Ijasah[n1];
    Ijasah* R = new Ijasah[n2];
    for (int i = 0; i < n1; i++) L[i] = dataIjasah[l + i];
    for (int j = 0; j < n2; j++) R[j] = dataIjasah[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].noIjasah <= R[j].noIjasah) { dataIjasah[k] = L[i]; i++; }
        else { dataIjasah[k] = R[j]; j++; }
        k++;
    }
    while (i < n1) { dataIjasah[k] = L[i]; i++; k++; }
    while (j < n2) { dataIjasah[k] = R[j]; j++; k++; }
    delete[] L; delete[] R;
}

void mergeSort(int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

void sorting() {
    int pil;
    cout << "MENU SORTING :" << endl;
    cout << "1. BUBBLE SORT" << endl;
    cout << "2. SELECTION SORT" << endl;
    cout << "3. INSERTION SORT" << endl;
    cout << "4. SHELL SORT" << endl;
    cout << "5. QUICK SORT" << endl;
    cout << "6. MERGE SORT" << endl;
    cout << "7. Kembali ke MENU UTAMA" << endl;
    cout << "Pilih : ";
    cin >> pil;

    if (pil == 7 || pil < 1 || pil > 7) return;

    cekfile();
    cout << "Pilih Nama File yang ingin di-Sorting: ";
    string fileTarget;
    cin >> fileTarget;

    if (!muatDataDariFile(fileTarget)) {
        cout << "File tidak ditemukan atau data kosong!" << endl;
        return;
    }
    namaFile = fileTarget;

    cout << "\nData Awal Sebelum Sorting:" << endl;
    for(int i=0; i<jumlahData; i++) {
        cout << "- " << dataIjasah[i].noIjasah << " | " << dataIjasah[i].jenisIjasah << " | " << dataIjasah[i].namaSekolah << endl;
    }

    switch (pil) {
        case 1: bubbleSort(); break;
        case 2: selectionSort(); break;
        case 3: insertionSort(); break;
        case 4: shellSort(); break;
        case 5: quickSort(0, jumlahData - 1); break;
        case 6: mergeSort(0, jumlahData - 1); break;
    }

    cout << "\nData berhasil diurutkan (Ascending)!" << endl;
    simpanData(); // Tulis balik hasil urutan baru ke file
    
    for(int i=0; i<jumlahData; i++) {
        cout << "  " << dataIjasah[i].noIjasah << " | " << dataIjasah[i].jenisIjasah << " | " << dataIjasah[i].namaSekolah << endl;
    }
}

// Bagi rata jumlah baris data ke beberapa file baru
void splitBerdasarkanKategori(int jumlahFile) {
    int dataPerFile = jumlahData / jumlahFile;
    int sisaData = jumlahData % jumlahFile;
    int indeksData = 0;

    for (int i = 1; i <= jumlahFile; i++) {
        string namaFileBaru = "Split_Kategori_part" + to_string(i) + ".txt";
        ofstream fileBaru(namaFileBaru);

        int batas = dataPerFile + (i == jumlahFile ? sisaData : 0);
        cout << "Membuat berkas " << namaFileBaru << " (" << batas << " data)..." << endl;

        for (int j = 0; j < batas; j++) {
            if (indeksData < jumlahData) {
                fileBaru << dataIjasah[indeksData].noIjasah << "|";
                fileBaru << dataIjasah[indeksData].jenisIjasah << "|";
                fileBaru << dataIjasah[indeksData].namaSekolah << endl;
                indeksData++;
            }
        }
        fileBaru.close();
        catatKeDaftarFile(namaFileBaru); 
    }
    cout << "\nSukses memisahkan file!" << endl;
}

// Pisahin data ke file baru berdasarkan batasan angka noIjasah yang di-input user
void splitBerdasarkanRentang(int jumlahFile) {
    bubbleSort(); // Di-sort dulu biar datanya berurutan pas dipisah

    for (int i = 1; i <= jumlahFile; i++) {
        long batasBawah, batasAtas;
        cout << "\n[File Bagian Ke-" << i << "]" << endl;
        cout << "Batas Bawah No Ijasah (Mulai dari): "; cin >> batasBawah;
        cout << "Batas Atas No Ijasah  (Sampai):     "; cin >> batasAtas;

        string namaFileBaru = "Split_Rentang_part" + to_string(i) + ".txt";
        ofstream fileBaru(namaFileBaru);
        int hitung = 0;

        for (int j = 0; j < jumlahData; j++) {
            if (dataIjasah[j].noIjasah >= batasBawah && dataIjasah[j].noIjasah <= batasAtas) {
                fileBaru << dataIjasah[j].noIjasah << "|";
                fileBaru << dataIjasah[j].jenisIjasah << "|";
                fileBaru << dataIjasah[j].namaSekolah << endl;
                hitung++;
            }
        }
        fileBaru.close();
        catatKeDaftarFile(namaFileBaru);
        cout << "-> Tersimpan " << hitung << " data ke dalam " << namaFileBaru << endl;
    }
}

void splitting() {
    string fileSumber;
    cout << "--- OPERASI SPLITTING ---" << endl;
    cekfile();
    cout << "Pilih Nama File yang ingin di-Split: ";
    cin >> fileSumber;

    if (!muatDataDariFile(fileSumber)) {
        cout << "File sumber tidak ditemukan atau kosong!" << endl;
        return;
    }
    namaFile = fileSumber;

    int jumlahFile, kriteria;
    cout << "Mau dibagi menjadi berapa file? : "; cin >> jumlahFile;
    if (jumlahFile <= 0) return;

    cout << "\nKriteria Pembagian Berkas:" << endl;
    cout << "1. Kategori (Bagi Rata)" << endl;
    cout << "2. Rentang Urutan No Ijasah" << endl;
    cout << "Pilih Metode: "; cin >> kriteria;

    if (kriteria == 1) splitBerdasarkanKategori(jumlahFile);
    else if (kriteria == 2) splitBerdasarkanRentang(jumlahFile);
    else cout << "Metode tidak valid!" << endl;
}

void operasiFile() {
    int pilih;
    cout << "\n===== MENU OPERASI FILE =====" << endl;
    cout << "1. Splitting" << endl;
    cout << "2. Kembali" << endl;
    cout << "Pilih: "; cin >> pilih;

    if (pilih == 1) splitting();
}

int main() {
    int pilihan;
    char ulang;

    do {
        cout << "=== PROGRAM MANAJEMEN DATA IJASAH ===" << endl;
        cout << "1. INPUT DATA" << endl;
        cout << "2. TAMPIL DATA" << endl;
        cout << "3. SEARCHING" << endl;
        cout << "4. SORTING" << endl;
        cout << "5. OPERASI DATA" << endl;
        cout << "6. EXIT" << endl; 
        cout << "PILIH : "; cin >> pilihan;
        
        switch (pilihan) {
            case 1: inputData(); break; 
            case 2: tampilData(); break;
            case 3: searching(); break;
            case 4: sorting(); break;
            case 5: operasiFile(); break;
            case 6: 
                cout << "\nAnda Keluar dari Program! Terima kasih." << endl;
                return 0;
            default:
                cout << "Pilihan Anda Tidak Valid" << endl;
        }

        cout << "\nKembali ke Menu Utama? (y/n) : "; 
        cin >> ulang;

    } while (ulang == 'y' || ulang == 'Y');

    return 0;
}