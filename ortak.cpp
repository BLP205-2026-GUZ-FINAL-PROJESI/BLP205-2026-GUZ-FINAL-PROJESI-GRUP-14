// ============================================================================
//  ortak.cpp
//  ortak.h icinde bildirilen yardimci fonksiyonlarin tanimlari.
//  Sorumlu: 1. Ogrenci
//
//  Neden cin >> yerine getline?
//  cin >> sayi kullanildiginda kullanici harf girerse cin "hata" durumuna
//  gecer ve sonraki tum okumalar bozulur; ayrica satir sonu tamponda kalir.
//  getline ile butun satiri metin olarak alip kendimiz kontrol ediyoruz,
//  boylece hatali giriste program kilitlenmez.
// ============================================================================
#include "ortak.h"

#include <cstdlib>   // exit
#include <iostream>
#include <sstream>   // istringstream

using namespace std;

// Metnin basindaki ve sonundaki bosluk, tab ve satir sonu karakterlerini siler.
// '\r' de silinir; Windows'ta olusturulan dosyalarda satir sonu "\r\n" olur.
static string bosluklariKirp(const string& metin)
{
    const char* bosluklar = " \t\r\n";
    size_t bas = metin.find_first_not_of(bosluklar);
    if (bas == string::npos) {
        return "";  // Metin tamamen bosluktan olusuyor
    }
    size_t son = metin.find_last_not_of(bosluklar);
    return metin.substr(bas, son - bas + 1);
}

void girdiAkisiBitti()
{
    cout << "\n[!] Girdi akisi sona erdi. Bellek temizlenip programdan cikiliyor...\n";
    tumBellegiTemizle();
    exit(0);
}

int tamSayiOku(const string& mesaj)
{
    string satir;
    while (true) {
        cout << mesaj;

        // getline basarisizsa girdi akisi bitmistir (Ctrl+Z / dosya sonu)
        if (!getline(cin, satir)) {
            girdiAkisiBitti();
        }

        satir = bosluklariKirp(satir);
        if (satir.empty()) {
            cout << "[!] Bos giris yaptiniz. Lutfen bir tam sayi girin.\n";
            continue;
        }

        istringstream akis(satir);
        int deger;
        char fazlalik;

        // 1) Satirin basinda gecerli bir sayi olmali.
        //    Sayi int sinirini asarsa da okuma basarisiz olur.
        if (!(akis >> deger)) {
            cout << "[!] Gecersiz giris: \"" << satir
                 << "\". Lutfen gecerli bir tam sayi girin.\n";
            continue;
        }

        // 2) Sayidan sonra baska karakter kalmamali ("12abc", "3.5" gibi).
        if (akis >> fazlalik) {
            cout << "[!] Gecersiz giris: \"" << satir
                 << "\". Sadece tam sayi girin (harf veya ondalik olmasin).\n";
            continue;
        }

        return deger;
    }
}

int tamSayiOku(const string& mesaj, int minDeger, int maxDeger)
{
    while (true) {
        int deger = tamSayiOku(mesaj);
        if (deger >= minDeger && deger <= maxDeger) {
            return deger;
        }
        cout << "[!] Deger " << minDeger << " ile " << maxDeger
             << " arasinda olmali. Tekrar deneyin.\n";
    }
}

string metinOku(const string& mesaj)
{
    string satir;
    while (true) {
        cout << mesaj;

        if (!getline(cin, satir)) {
            girdiAkisiBitti();
        }

        satir = bosluklariKirp(satir);
        if (satir.empty()) {
            cout << "[!] Bu alan bos birakilamaz. Tekrar deneyin.\n";
            continue;
        }

        // '|' dosya formatinda alan ayiraci oldugu icin metnin icinde olamaz.
        if (satir.find('|') != string::npos) {
            cout << "[!] '|' karakteri kullanilamaz (dosya ayiraci). Tekrar deneyin.\n";
            continue;
        }

        return satir;
    }
}

void cizgiCiz(int uzunluk, char karakter)
{
    cout << string(uzunluk, karakter) << "\n";
}

void baslikYazdir(const string& baslik)
{
    cout << "\n";
    cizgiCiz(60, '=');
    cout << "  " << baslik << "\n";
    cizgiCiz(60, '=');
}
