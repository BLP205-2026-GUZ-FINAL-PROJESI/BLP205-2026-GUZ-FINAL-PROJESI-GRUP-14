// ============================================================================
//  BLP 205 Veri Yapilari - Final Projesi
//  Kampus Kutuphanesi ve Ogrenci Hizmetleri Otomasyonu
//
//  main.cpp: Ana menu, acilista ornek verilerin yuklenmesi ve cikista
//            tum modullerin belleginin temizlenmesi.
//  Sorumlu: 1. Ogrenci
//
//  Derleme : g++ -std=c++11 *.cpp -o kutuphane
//  Calistir: ./kutuphane
// ============================================================================
#include "modul1_duyuru_dosya.h"   // Modul 1B - 2. ogrenci
#include "modul1_kitap.h"          // Modul 1A - 1. ogrenci
#include "modul2_yigin_kuyruk.h"   // Modul 2  - 3. ogrenci
#include "modul3_siralama.h"       // Modul 3  - 4. ogrenci
#include "modul4_graf.h"           // Modul 4  - 5. ogrenci
#include "ortak.h"

#include <iostream>

using namespace std;

// Tum modullerin ornek verilerini yukler.
// Modul 2 once yuklenir; boylece islem gecmisi yigini diger modullerden
// once hazir olur.
static void ornekVerileriYukle()
{
    modul2OrnekVeriYukle();
    modul1OrnekVeriYukle();
    duyuruOrnekVeriYukle();
    modul4OrnekVeriYukle();
}

// Tum modullerin new ile ayirdigi bellegi delete eder.
// Hem normal cikista hem de girdi akisi bittiginde (ortak.cpp) cagrilir.
// 'temizlendi' bayragi sayesinde iki kez cagrilsa bile bellek bir kez silinir.
void tumBellegiTemizle()
{
    static bool temizlendi = false;
    if (temizlendi) {
        return;
    }
    temizlendi = true;

    cout << "\n--- Bellek temizleniyor ---\n";
    modul1Temizle();       // Modul 1A: cift yonlu bagli liste
    duyurulariTemizle();   // Modul 1B: dairesel bagli liste
    modul2Temizle();       // Modul 2 : yigin ve kuyruk
    modul4Temizle();       // Modul 4 : graf
    // Modul 3'un kalici verisi yok; gecici diziler islem sonunda delete[] ediliyor.
    cout << "--- Bellek temizligi tamamlandi ---\n";
}

static void anaMenuyuYazdir()
{
    baslikYazdir("KAMPUS KUTUPHANESI VE OGRENCI HIZMETLERI OTOMASYONU");
    cout << "  1. Modul 1 - Kitap Katalogu, Duyurular, Dosya (Bagli Listeler)\n"
         << "  2. Modul 2 - Odunc Sirasi ve Islem Gecmisi (Kuyruk / Yigin)\n"
         << "  3. Modul 3 - Kitap Siralama ve Arama Algoritmalari\n"
         << "  4. Modul 4 - Kampus Rota Analizi (Graf)\n"
         << "  0. Cikis\n";
    cizgiCiz();
}

int main()
{
    ornekVerileriYukle();
    cout << "[OK] Ornek veriler yuklendi.\n";

    while (true) {
        anaMenuyuYazdir();
        int secim = tamSayiOku("Seciminiz: ");

        switch (secim) {
            case 1: modul1Menu(); break;
            case 2: modul2Menu(); break;
            case 3: modul3Menu(); break;
            case 4: modul4Menu(); break;
            case 0:
                tumBellegiTemizle();
                cout << "Programdan cikiliyor. Iyi gunler!\n";
                return 0;
            default:
                cout << "[!] Gecersiz secim: " << secim << ". Lutfen 0-4 arasinda bir deger girin.\n";
        }
    }
}
