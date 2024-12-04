#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

// color
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define BLUE "\e[0;34m"
#define RESET "\e[0m"

// size
#define garisPutus 28
#define garisPanjang 15
#define Maxnomor 15
#define panjangNama 50
#define maxCoba 3

struct User {
    char nama[panjangNama];
    char noHp[panjangNama];
    int pin;
    int saldo;
};

//global variabel
struct User tampilUser;

enum Hari {
    MINGGU = 1,
    SENIN,
    SELASA,
    RABU,
    KAMIS,
    JUMAT,
    SABTU
};

// center
void center(int offsetY, int offsetX) {
    COORD c;
    c.X = 20 + offsetX;
    c.Y = 10 + offsetY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// cek nomor HP
int cekNomorHp(char *noHp) {
    FILE *file = fopen("user.txt", "r");
    if (file == NULL) {
        printf(RED "Gagal membuka file.\n" RESET);
        return 0;
    }

    struct User cek_user;
    while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
        if (strcmp(cek_user.noHp, noHp) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// daftar
void daftar() {
    struct User user;
    user.saldo = 0;
    FILE *file;

    center(0, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    for (int i = 0; i < 18; i++) {
        center(i + 1, 0);
        printf("|");
        center(i + 1, 27);
        printf("|");
    }
    center(18, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    center(2, 5);
    printf("      Daftar     ");
    center(4, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    center(6, 2);
    printf("Masukkan Nomor Hp : ");
    center(7, 2);
    scanf("%14s", user.noHp);
    while(getchar() != '\n');
    center(8, 0);
    if (cekNomorHp(user.noHp)) {
        center(9, 2);
        printf(RED "Nomor HP sudah terdaftar." RESET);
        center(10, 2);
        printf("Segera ke halaman masuk.\n");
        center(11, 0);
        for (int i = 0; i < garisPutus; i++) {
        printf("-");
        }
        Sleep(2000);
        system("cls");
        return;
    }
    center(10, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    center(11, 2);
    printf("Masukkan nama Anda : ");
    center(12, 2);
    gets(user.nama);
    center(13, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    center(14, 2);
    printf("Masukkan PIN Anda : ");
    center(15, 2);
    scanf("%d", &user.pin);

    // menambahkan data
    file = fopen("user.txt", "a");
    if (file == NULL) {
        printf(RED "Nama Anda tidak terdaftar." RESET);
        return;
    }
    fprintf(file, "%s %s %d %d\n", user.nama, user.noHp, user.pin, user.saldo);
    fclose(file);

    center(16, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    center(17, 2);
    printf(GREEN "Berhasil terdaftar." RESET);
}


// masuk
void masuk() {
    int cek = 0;
    struct User user;
    FILE *file;
    center(-8, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    for (int i = 0; i < 26; i++) {
        center(i - 7, 0);
        printf("|");
        center(i - 7, 27);
        printf("|");
    }

    center(-6, 5);
    printf("      Masuk      ");
    center(-4, 2);
    printf("Masukkan Nomor HP Anda : ");
    center(-3, 2);
    scanf("%s", user.noHp);
    center(-2, 2);
    printf("Masukkan PIN Anda : ");
    center(-1, 2);
    scanf("%d", &user.pin);

    do {
        file = fopen("user.txt", "r");
        if (file == NULL) {
            printf("Error membuka file.\n");
            return;
        }

        struct User cek_user;
        int found = 0;

        while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
            if (strcmp(cek_user.noHp, user.noHp) == 0 && cek_user.pin == user.pin) {
                tampilUser = cek_user;
                center(0, 2);
                printf(GREEN "Segera ke halaman utama.\n" RESET, cek_user.nama);
                center(1, 0);
                for (int i = 0; i < garisPutus; i++) {
                    printf("-");
                }
                fclose(file);
                return 1;
            }
        }
        fclose(file);

        cek++;

        if (cek == 1) {
            center(0, 0);
            for (int i = 0; i < garisPutus; i++) {
                printf("-");
            }
            center(1, 2);
            printf(RED "Nomor HP atau PIN salah." RESET);
            center(2, 2);
            printf(RED "Percobaan %d dari %d" RESET, cek, maxCoba);
            center(3, 2);
            printf("Masukkan Nomor HP Anda : ");
            center(4, 2);
            scanf("%s", user.noHp);
            center(5, 2);
            printf("Masukkan PIN Anda: ");
            center(6, 2);
            scanf("%d", &user.pin);
        } else if (cek == 2) {
            center(7, 0);
            for (int i = 0; i < garisPutus; i++) {
                printf("-");
            }
            center(8, 2);
            printf(RED "Nama atau PIN salah." RESET);
            center(9, 2);
            printf(RED "Percobaan %d dari %d" RESET, cek, maxCoba);
            center(10, 2);
            printf("Masukkan Nomor HP Anda : ");
            center(11, 2);
            scanf("%s", user.noHp);
            center(12, 2);
            printf("Masukkan PIN Anda: ");
            center(13, 2);
            scanf("%d", &user.pin);
        } else if (cek == 3) {
            center(19, 0);
            for (int i = 0; i < garisPutus; i++) {
                printf("-");
            }
            center(17, 2);
            printf(RED "Anda sudah salah 3 kali." RESET);
            center(18, 2);
            printf(RED "Segera ke halaman Cari." RESET);
            Sleep(3000);
            system("cls");
            cari();
            return;
        }
    } while (cek < maxCoba);

    system("cls");
    return 0;
}

// cari
void cari() {
    struct User user;
    FILE *file;
    center(0, 0);
    for (int i = 0; i < garisPutus; i++) {
                printf("-");
    }
    center(1,0);
    for (int i = 0; i < 18; i++) {
        center(i + 1, 0);
        printf("|");
        center(i + 1, 27);
        printf("|");
    }
    center(2,2);
    printf("Masukkan Nomor Hp Anda : ");
    center(3,2);
    scanf("%s", user.noHp);
    file = fopen("user.txt", "r");

    if (file == NULL) {
        printf("Gagal membuka file.");
        return;
    }

    struct User cek_user;
    while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
        if (strcmp(cek_user.noHp, user.noHp) == 0) {
            center(5,2);
            printf(GREEN "PIN Anda adalah %d\n" RESET, cek_user.pin);
            center(6, 0);
            for (int i = 0; i < garisPutus; i++) {
                printf("-");
            }
            Sleep(3000);
            system("cls");
            masuk();
            fclose(file);
            return;
        }
    }

    fclose(file);
    center(5,2);
    printf(RED "Nomor HP tidak ditemukan.\n" RESET);
    Sleep(1000);
    system("cls");
    cari();
}


// topup
void topUp() {
    FILE *file, *tempFile;
    struct User cek_user;
    int pin, jumlahTopUp, saldoBaru = 0;
    char nomorHp[15];
    int found = 0;

    time_t t = time(NULL);
    struct tm *timeinfo = localtime(&t);
    char *hariIni;
    switch(timeinfo->tm_wday) {
        case 0: hariIni = "Minggu"; break;
        case 1: hariIni = "Senin"; break;
        case 2: hariIni = "Selasa"; break;
        case 3: hariIni = "Rabu"; break;
        case 4: hariIni = "Kamis"; break;
        case 5: hariIni = "Jumat"; break;
        case 6: hariIni = "Sabtu"; break;
    }

    system("cls");
    center(0, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    for (int i = 0; i < 16; i++) {
        center(i + 1, 0);
        printf("|");
        center(i + 1, 27);
        printf("|");
    }
    center(18, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    center(2, 5);
    printf("    Top-Up Saldo   ");

    center(4, 2);
    printf("Masukkan nomor HP Anda: ");
    center(5, 2);
    scanf("%s", nomorHp);
    if (strcmp(nomorHp, tampilUser.noHp) != 0) {
        center(7, 2);
        printf(RED "Nomor HP tidak sesuai dengan akun Anda!" RESET);
        Sleep(3000);
        system("cls");
        topUp();
        return;
    }

    center(7, 2);
    printf("Masukkan jumlah Top-Up: ");
    center(8, 2);
    scanf("%d", &jumlahTopUp);

    if (jumlahTopUp <= 0) {
        center(9, 2);
        printf(RED "Jumlah Top-Up harus lebih dari 0!" RESET);
        Sleep(3000);
        system("cls");
        topUp();
        return;
    }

    center(10, 2);
    printf("Masukkan PIN Anda: ");
    center(11, 2);
    scanf("%d", &pin);

    if (pin != tampilUser.pin) {
        center(12, 2);
        printf(RED "PIN salah!", RESET);
        center(13, 2);
        printf(RED "Top-Up dibatalkan." RESET);
        Sleep(3000);
        system("cls");
        topUp();
        return;
    }

    file = fopen("user.txt", "r");
    tempFile = fopen("temp_user.txt", "w");
    if (file == NULL || tempFile == NULL) {
        center(10, 2);
        printf(RED "Tidak dapat membuka file." RESET);
        Sleep(3000);

        return;
    }

    while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
        if (strcmp(cek_user.nama, tampilUser.nama) == 0) {
            found = 1;
            saldoBaru = cek_user.saldo + jumlahTopUp;
            cek_user.saldo = saldoBaru;
            tampilUser.saldo = saldoBaru;
            catatLaporan(cek_user.noHp, cek_user.nama, jumlahTopUp, hariIni, "Top-Up");
            center(13, 2);
            printf(GREEN "Top-Up berhasil!" RESET);
            center(14, 2);
            printf("Nomor HP : %s", nomorHp);
            center(15, 2);
            printf("Jumlah TopUp : %d", jumlahTopUp);
            center(16, 2);
            printf("Hari : %s", hariIni);


            FILE *struk = fopen("struk_topup.txt", "a");
            if (struk != NULL) {
                fprintf(struk, "Nomor HP: %s\nJumlah Top-Up: Rp.%d\nHari: %s\n\n",nomorHp, jumlahTopUp, hariIni);
                fclose(struk);
            }
        }
        fprintf(tempFile, "%s %s %d %d\n", cek_user.nama, cek_user.noHp, cek_user.pin, cek_user.saldo);
    }

    fclose(file);
    fclose(tempFile);
    remove("user.txt");
    rename("temp_user.txt", "user.txt");

    if (!found) {
        center(14, 2);
        printf(RED "Top-Up gagal! Akun tidak ditemukan." RESET);
    }

    Sleep(3000);
    system("cls");
}

// trasnfer
void transferSaldo() {
    FILE *file, *tempFile;
    struct User cek_user;
    char nomorHpTujuan[15];
    char namaTujuan[100];
    int jumlahTransfer, pin;
    char cek;
    int foundTujuan = 0, saldoBaruPengirim, saldoBaruPenerima;

    time_t t = time(NULL);
    struct tm *timeinfo = localtime(&t);
    char *hariIni;
    switch(timeinfo->tm_wday) {
        case 0: hariIni = "Minggu"; break;
        case 1: hariIni = "Senin"; break;
        case 2: hariIni = "Selasa"; break;
        case 3: hariIni = "Rabu"; break;
        case 4: hariIni = "Kamis"; break;
        case 5: hariIni = "Jumat"; break;
        case 6: hariIni = "Sabtu"; break;
    }

    system("cls");
    center(-8, 0);
    for (int i = 0; i < 32; i++) {
        printf("-");
    }
    for (int i = 0; i < 30; i++) {
        center(i - 7, 0);
        printf("||");
        center(i - 7, 30);
        printf("||");
    }
    center(-6, 3);
    printf("      Transfer Saldo      ");
    center(-5,3);
    printf("Saldo : Rp.%d\n", tampilUser.saldo);
    center(-4,3);
    printf("Masukkan nomor HP tujuan: ");
    center(-3,3);
    scanf("%s", nomorHpTujuan);

    if (strcmp(nomorHpTujuan, tampilUser.noHp) == 0) {
        center(-2, 2);
        printf(RED "Tidak bisa transfer ke nomor sendiri." RESET);
        Sleep(3000);
        return;
    }

    file = fopen("user.txt", "r");
    if (file == NULL) {
        center(-9, 2);
        printf(RED "File tidak ada" RESET);
        return;
    }

    while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
        if (strcmp(cek_user.noHp, nomorHpTujuan) == 0) {
            foundTujuan = 1;
            strcpy(namaTujuan, cek_user.nama);
            break;
        }
    }
    fclose(file);

    if (!foundTujuan) {
        center(-1, 2);
        printf(RED "Nomor tidak ditemukan" RESET);
        Sleep(3000);
        return;
    }
    center(0,3);
    printf("Masukkan jumlah transfer: ");
    center(1,3);
    scanf("%d", &jumlahTransfer);
    center(2,3);
    if (jumlahTransfer <= 0) {
        center(9,3);
        printf(RED "Jumlah transfer harus lebih dari 0!" RESET);
        Sleep(3000);
        return;
    }
    center(3,3);
    if (jumlahTransfer > tampilUser.saldo) {
        printf(RED "Saldo tidak mencukupi." RESET);
        Sleep(3000);
        return;
    }
    center(4,3);
    printf("Nama tujuan Anda : %s", namaTujuan);
    center(5,3);
    printf("Apakah sudah sesuai?(y/t): ");
    center(6,3);
    scanf("%s", &cek);
    if (cek == 't' || cek == 'T') {
        Sleep(3000);
        system("cls");
        transferSaldo();
        return;
    }

    center(7,3);
    printf("Masukkan PIN Anda: ");
    center(8,3);
    scanf("%d", &pin);
    center(9,3);
    if (pin != tampilUser.pin) {
        printf(RED "PIN salah!\n" RESET);
        printf(RED "Transfer dibatalkan." RESET);
        Sleep(3000);
        return;
    }

    file = fopen("user.txt", "r");
    tempFile = fopen("temp_user.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf(RED "Tidak dapat membuka file.\n" RESET);
        return;
    }

    while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
        if (strcmp(cek_user.noHp, nomorHpTujuan) == 0) {
            foundTujuan = 1;
            saldoBaruPenerima = cek_user.saldo + jumlahTransfer;
            cek_user.saldo = saldoBaruPenerima;
            catatLaporan(cek_user.noHp, cek_user.nama, jumlahTransfer, hariIni, "Transfer");
            center(10, 3);
            printf("Transfer berhasil!\n");
            center(11, 3);
            printf("Nama Penerima : %s", namaTujuan);
            center(12, 3);
            printf("\nNomor Penerima : %s", nomorHpTujuan);
            center(13, 3);
            printf("\nJumlah Transfer : Rp.%d", jumlahTransfer);
            center(14, 3);
            printf("\nHari : %s", hariIni);
            center(15, 3);
            FILE *struk = fopen("struk_transfer.txt", "a");
            if (struk != NULL) {
            center(14, 3);
            fprintf(struk, "Nama Penerima: %s\nNomor Penerima: %s\nJumlah Transfer: %d\nHari: %s\n", namaTujuan, nomorHpTujuan, jumlahTransfer, hariIni);
            fclose(struk);
            }
        }

        if (strcmp(cek_user.noHp, tampilUser.noHp) == 0) {
            saldoBaruPengirim = tampilUser.saldo - jumlahTransfer;
            tampilUser.saldo = saldoBaruPengirim;
            cek_user.saldo = saldoBaruPengirim;
            catatLaporan(tampilUser.noHp, tampilUser.nama, -jumlahTransfer, hariIni, "Transfer");
        }
        fprintf(tempFile, "%s %s %d %d\n", cek_user.nama, cek_user.noHp, cek_user.pin, cek_user.saldo);
    }

    fclose(file);
    fclose(tempFile);

    if (!foundTujuan) {
        printf(RED "Nomor HP tujuan tidak ditemukan.\n" RESET);
        remove("temp_user.txt");
        return;
    }

    remove("user.txt");
    rename("temp_user.txt", "user.txt");

    Sleep(3000);
    system("cls");
}

//catat laporan
void catatLaporan(const char *noHp, const char *nama, int jumlah, const char *hari, const char *jenis) {
    char namaFile[50];
    sprintf(namaFile, "laporan_%s.txt", noHp);

    FILE *file = fopen(namaFile, "a+");
    if (file == NULL) {
        printf(RED "Error: Tidak dapat membuka file laporan.\n" RESET);
        return;
    }

    time_t now;
    time(&now);
    char waktu[50];
    strcpy(waktu, ctime(&now));
    waktu[strcspn(waktu, "\n")] = 0;

    fprintf(file, "\nNama: %s\nNomor: %s\nJumlah: Rp.%d\nHari: %s\nJenis: %s\n------------------------\n",nama, noHp, jumlah, hari, jenis);
    fclose(file);
}

//tampil laporan
void tampilkanLaporan(const char *noHp) {
    char namaFile[50];
    sprintf(namaFile, "laporan_%s.txt", noHp);
    FILE *file = fopen(namaFile, "r");
    if (file == NULL) {
        printf(RED "Tidak ada laporan untuk nomor HP %s.\n" RESET, noHp);
        return;
    }

    printf(GREEN "Laporan Keuangan\n" RESET);

    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}


//edit nomorhp
void editNomorHp() {
    FILE *file, *tempFile;
    struct User cek_user;
    char nomorBaru[20];
    int found = 0;
    int duplicate = 0;

    system("cls");
    center(0, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    center(2, 5);
    printf("    Edit Nomor HP    ");
    do {
        duplicate = 0;
        center(4, 2);
        printf("Masukkan nomor baru: ");
        center(5, 2);
        scanf("%s", nomorBaru);

        file = fopen("user.txt", "r");
        if (file == NULL) {
            printf(RED "Tidak dapat membuka file.\n" RESET);
            return;
        }

        while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
            if (strcmp(cek_user.noHp, nomorBaru) == 0) {
                duplicate = 1;
                break;
            }
        }
        fclose(file);

        if (duplicate) {
            center(6, 2);
            printf(RED "Nomor sudah terdaftar." RESET);
            center(7, 2);
            printf(RED "Silakan masukkan nama lain.\n" RESET);
            Sleep(2000);
        }
    } while (duplicate);

    file = fopen("user.txt", "r");
    tempFile = fopen("temp_user.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf(RED "Tidak dapat membuka file.\n" RESET);
        return;
    }

    while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
        if (strcmp(cek_user.noHp, tampilUser.noHp) == 0) {
            found = 1;
            strcpy(cek_user.noHp, nomorBaru);
        }
        fprintf(tempFile, "%s %s %d %d\n", cek_user.nama, cek_user.noHp, cek_user.pin, cek_user.saldo);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf(RED "Akun tidak ditemukan.\n" RESET);
        remove("temp_user.txt");
        return;
    }

    remove("user.txt");
    rename("temp_user.txt", "user.txt");

    strcpy(tampilUser.noHp, nomorBaru);

    center(8, 2);
    printf(GREEN "Nomor HP berhasil diubah.\n" RESET);
    Sleep(3000);
    system("cls");
}

//edit pin
void editPin() {
    FILE *file, *tempFile;
    struct User cek_user;
    int pinBaru;
    int found = 0;

    system("cls");
    center(0, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    center(2, 5);
    printf("    Edit Pin    ");
    center(4, 2);
    printf("Masukkan pin baru: ");
    center(5, 2);
    scanf("%d", &pinBaru);

    file = fopen("user.txt", "r");
    tempFile = fopen("temp_user.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf(RED "Tidak dapat membuka file.\n" RESET);
        return;
    }

    while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
        if (strcmp(cek_user.noHp, tampilUser.noHp) == 0) {
            found = 1;
            cek_user.pin = pinBaru;
        }
        fprintf(tempFile, "%s %s %d %d\n", cek_user.nama, cek_user.noHp, cek_user.pin, cek_user.saldo);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf(RED "Akun tidak ditemukan.\n" RESET);
        remove("temp_user.txt");
        return;
    }

    remove("user.txt");
    rename("temp_user.txt", "user.txt");

    tampilUser.pin = pinBaru;

    center(7, 2);
    printf(GREEN "Pin berhasil diubah.\n" RESET);
    Sleep(3000);
    system("cls");
}

//edit nama
void editNama() {
    FILE *file, *tempFile;
    struct User cek_user;
    char namaBaru[panjangNama];
    int found = 0;
    int duplicate = 0;

    system("cls");
    center(0, 0);
    for (int i = 0; i < garisPutus; i++) {
        printf("-");
    }
    center(2, 5);
    printf("    Edit Nama    ");

    do {
        duplicate = 0;
        center(4, 2);
        printf("Masukkan nama baru: ");
        center(5, 2);
        scanf("%s", namaBaru);

        file = fopen("user.txt", "r");
        if (file == NULL) {
            printf(RED "Tidak dapat membuka file.\n" RESET);
            return;
        }

        while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
            if (strcmp(cek_user.nama, namaBaru) == 0) {
                duplicate = 1;
                break;
            }
        }
        fclose(file);

        if (duplicate) {
            center(6, 2);
            printf(RED "Nama sudah terdaftar. Silakan masukkan nama lain.\n" RESET);
            Sleep(2000);
            system("cls");
            pengaturan();
        }
    } while (duplicate);

    file = fopen("user.txt", "r");
    tempFile = fopen("temp_user.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf(RED "Tidak dapat membuka file.\n" RESET);
        return;
    }

    while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
        if (strcmp(cek_user.noHp, tampilUser .noHp) == 0) {
            found = 1;
            strcpy(cek_user.nama, namaBaru);
        }
        fprintf(tempFile, "%s %s %d %d\n", cek_user.nama, cek_user.noHp, cek_user.pin, cek_user.saldo);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf(RED "Akun tidak ditemukan.\n" RESET);
        remove("temp_user.txt");
        return;
    }

    remove("user.txt");
    rename("temp_user.txt", "user.txt");

    strcpy(tampilUser .nama, namaBaru);

    center(8, 2);
    printf(GREEN "Nama berhasil diubah.\n" RESET);
    Sleep(3000);
    system("cls");
}

//hapus akun
void hapusAkun() {
    FILE *file, *tempFile;
    struct User cek_user;
    int found = 0;

    file = fopen("user.txt", "r");
    tempFile = fopen("temp_user.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf(RED "Gagal membuka file.\n" RESET);
        return;
    }

    while (fscanf(file, "%s %s %d %d", cek_user.nama, cek_user.noHp, &cek_user.pin, &cek_user.saldo) == 4) {
        if (strcmp(cek_user.noHp, tampilUser.noHp) == 0) {
            found = 1;
            continue;
        }
        fprintf(tempFile, "%s %s %d %d\n", cek_user.nama, cek_user.noHp, cek_user.pin, cek_user.saldo);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("user.txt");
        rename("temp_user.txt", "user.txt");
        center(5, 2);
        printf(GREEN "Akun berhasil dihapus." RESET);
        Sleep(2000);
        system("cls");
        exit(0);
    } else {
        center(5, 2);
        printf(RED "Akun tidak ditemukan." RESET);
        Sleep(2000);
        system("cls");
    }
}

//pengaturan
void pengaturan() {
    int pilihan;
    do {
        system("cls");
        center(0, 0);
        for (int i = 0; i < garisPutus; i++) {
            printf("-");
        }
        center(2, 5);
        printf("    Pengaturan    ");
        center(4, 2);
        printf("Halo," BLUE "%s" RESET, tampilUser.nama[0] ? tampilUser.nama : "Trio Wallet");
        center(6,2);
        printf(GREEN "%s" RESET, tampilUser.noHp[0] ? tampilUser.noHp : "Null");
        center(8, 2);
        printf("1. Edit Nama");
        center(9, 2);
        printf("2. Edit Nomor HP");
        center(11, 2);
        printf("3. Edit Pin");
        center(12, 2);
        printf("4. Hapus Akun");
        center(13, 2);
        printf("5. Keluar");
        center(15, 2);
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                editNama();
                break;
            case 2:
                editNomorHp();
                break;
            case 3:
                editPin();
                break;
            case 4:
                hapusAkun();
                break;
            case 5:
                printf("Menuju Home..\n");
                return;
                break;
            default:
                printf("Harap Masukkan angka 1-4!.\n");
                break;
        }
    } while (pilihan != 6);
}


//utama
int main()
{
    int pilihan;
    daftar();
    Sleep(3000);
    system("cls");
    masuk();
    do{
        Sleep(2000);
        system("cls");
        printf("Halo," BLUE "%s!" RESET "\nSaldo Anda : Rp.%d\n", tampilUser.nama[0] ? tampilUser.nama : "Trio E-Wallet", tampilUser.saldo);
        printf("\nHome\n");
        printf("1. Top-Up Saldo\n");
        printf("2. Transfer Saldo\n");
        printf("3. Laporan Keuangan\n");
        printf("4. Setting\n");
        printf("5. Exit\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);
        getchar();
        switch (pilihan) {
            case 1:
                topUp();
                break;
            case 2:
                transferSaldo();
                break;
            case 3:
                tampilkanLaporan(tampilUser.noHp);
                break;
            case 4:
                pengaturan();
                break;
            case 5:
                printf("Terima kasih, %s!\n", tampilUser.nama[0] ? tampilUser.nama : "Trio Wallet");
                printf("\nSudah memakai aplikasi Trio E-Wallet\n");
                exit(0);
                break;
            default:
                printf("Harap Masukkan angka 1 - 4!.\n");
                break;
        }
        printf("Tekan enter untuk melanjutkan Home...");
        getch();
    } while (pilihan != 5);
    return 0;
}
