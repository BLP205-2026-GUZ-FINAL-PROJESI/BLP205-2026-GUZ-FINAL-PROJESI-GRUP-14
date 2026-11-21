// ============================================================================
//  modul1_kitap.cpp
//  Modul 1A: Kitap katalogu - CIFT YONLU BAGLI LISTE
//  Sorumlu: 1. Ogrenci
//
//  Yapilan islemler ve zaman karmasikliklari (n = kitap sayisi):
//    Basa ekle ............................ O(1)  (bas isaretcisi var)
//    Sona ekle ............................ O(1)  (son isaretcisi var)
//    Hedef ID oncesine ekle ............... O(n)  (once hedef aranir)
//    ID ile sil ........................... O(n)  (once dugum aranir)
//    Ileri / geri listeleme ............... O(n)
//    Katalog analizi ...................... O(n)
//    Bellek temizleme ..................... O(n)
// ============================================================================
#include "modul1_kitap.h"
#include "modul1_duyuru_dosya.h"   // duyuruMenu(), dosyaIslemleriMenu()  (2. ogrenci)
#include "modul2_yigin_kuyruk.h"   // islemKaydet()                       (3. ogrenci)
#include "ortak.h"

#include <iomanip>   // setw, fixed, setprecision
#include <iostream>
#include <sstream>   // ostringstream
#include <string>

using namespace std;

// ----------------------------------------------------------------------------
//  Modul icindeki gizli degiskenler (static: sadece bu dosyadan erisilir)
// ----------------------------------------------------------------------------
static KitapDugum* bas = nullptr;   // listenin ilk dugumu
static KitapDugum* son = nullptr;   // listenin son dugumu
static int kitapSayisi = 0;         // listedeki dugum sayisi

// Kullanicidan alinacak degerlerin sinirlari
static const int MAKS_ID = 999999;
static const int MAKS_SAYFA = 100000;

// ============================================================================
//  YARDIMCI FONKSIYONLAR
// ============================================================================

// Uzun metinleri tablo sutununa sigacak sekilde kisaltir ("..." ekler).
static string kisalt(const string& metin, size_t enFazla)
{
    if (metin.size() <= enFazla) {
        return metin;
    }
    return metin.substr(0, enFazla - 3) + "...";
}

// Verilen ID'ye sahip dugumu bastan baslayarak arar. O(n)
// Bulamazsa nullptr dondurur.
static KitapDugum* idIleBul(int id)
{
    KitapDugum* gezici = bas;
    while (gezici != nullptr) {
        if (gezici->veri.id == id) {
            return gezici;
        }
        gezici = gezici->next;
    }
    return nullptr;
}

// Yeni bir dugum olusturur (new). prev ve next baslangicta nullptr'dir.
static KitapDugum* yeniDugum(const Kitap& kitap)
{
    KitapDugum* dugum = new KitapDugum;
    dugum->veri = kitap;
    dugum->prev = nullptr;
    dugum->next = nullptr;
    return dugum;
}

// ============================================================================
//  BAGLI LISTE TEMEL ISLEMLERI
//  (Bu fonksiyonlar islemKaydet cagirmaz; kayit menu fonksiyonlarinda yapilir.
//   Boylece acilistaki ornek veriler islem gecmisine yazilmaz.)
// ============================================================================

// Listenin basina ekler. O(1)
static void basaEkle(const Kitap& kitap)
{
    KitapDugum* dugum = yeniDugum(kitap);

    if (bas == nullptr) {
        // Liste bos: yeni dugum hem ilk hem son dugumdur
        bas = dugum;
        son = dugum;
    } else {
        dugum->next = bas;   // yeni dugum -> eski ilk dugum
        bas->prev = dugum;   // eski ilk dugum <- yeni dugum
        bas = dugum;         // artik ilk dugum yeni dugum
    }
    kitapSayisi++;
}

// Listenin sonuna ekler. O(1)
static void sonaEkle(const Kitap& kitap)
{
    KitapDugum* dugum = yeniDugum(kitap);

    if (son == nullptr) {
        // Liste bos
        bas = dugum;
        son = dugum;
    } else {
        dugum->prev = son;   // yeni dugum <- eski son dugum
        son->next = dugum;   // eski son dugum -> yeni dugum
        son = dugum;         // artik son dugum yeni dugum
    }
    kitapSayisi++;
}

// hedefId'ye sahip dugumun ONCESINE ekler. O(n)
// Hedef bulunamazsa false dondurur.
static bool hedefOncesineEkle(int hedefId, const Kitap& kitap)
{
    KitapDugum* hedef = idIleBul(hedefId);
    if (hedef == nullptr) {
        return false;
    }

    // Hedef ilk dugumse bu islem basa eklemeyle aynidir
    if (hedef == bas) {
        basaEkle(kitap);
        return true;
    }

    // Ortaya ekleme:  onceki <-> hedef   =>   onceki <-> yeni <-> hedef
    KitapDugum* onceki = hedef->prev;
    KitapDugum* dugum = yeniDugum(kitap);

    dugum->prev = onceki;   // yeni <- onceki
    dugum->next = hedef;    // yeni -> hedef
    onceki->next = dugum;   // onceki -> yeni
    hedef->prev = dugum;    // hedef <- yeni

    kitapSayisi++;
    return true;
}

// ID'si verilen dugumu siler. O(n)
// Silinen kitabin bilgisi 'silinen' parametresine yazilir.
// Bulunamazsa false dondurur.
static bool idIleSil(int id, Kitap& silinen)
{
    KitapDugum* dugum = idIleBul(id);
    if (dugum == nullptr) {
        return false;
    }

    // 1) Onceki dugumun next'ini guncelle
    if (dugum->prev != nullptr) {
        dugum->prev->next = dugum->next;   // orta veya son dugum
    } else {
        bas = dugum->next;                 // ilk dugum siliniyor: bas kayar
    }

    // 2) Sonraki dugumun prev'ini guncelle
    if (dugum->next != nullptr) {
        dugum->next->prev = dugum->prev;   // ilk veya orta dugum
    } else {
        son = dugum->prev;                 // son dugum siliniyor: son kayar
    }

    // Tek dugum varsa yukaridaki iki adimdan sonra bas = son = nullptr olur.

    silinen = dugum->veri;
    delete dugum;
    kitapSayisi--;
    return true;
}

// ============================================================================
//  DISA ACIK FONKSIYONLAR (diger moduller kullanir)
// ============================================================================

KitapDugum* katalogBasi()
{
    return bas;
}

int katalogBoyutu()
{
    return kitapSayisi;
}

void kitapTabloBasligiYazdir()
{
    cout << left
         << setw(8) << "ID"
         << setw(32) << "Kitap Adi"
         << setw(24) << "Yazar"
         << right << setw(8) << "Sayfa" << "\n";
    cizgiCiz(72);
}

void kitapYazdir(const Kitap& kitap)
{
    cout << left
         << setw(8) << kitap.id
         << setw(32) << kisalt(kitap.ad, 30)
         << setw(24) << kisalt(kitap.yazar, 22)
         << right << setw(8) << kitap.sayfaSayisi << "\n";
}

// ============================================================================
//  LISTELEME VE ANALIZ
// ============================================================================

// Bastan sona, next isaretcisi ile gezerek listeler. O(n)
static void ileriListele()
{
    baslikYazdir("KATALOG (Bastan Sona - next ile)");
    if (bas == nullptr) {
        cout << "[!] Katalog bos. Listelenecek kitap yok.\n";
        return;
    }

    kitapTabloBasligiYazdir();
    KitapDugum* gezici = bas;
    while (gezici != nullptr) {
        kitapYazdir(gezici->veri);
        gezici = gezici->next;
    }
    cizgiCiz(72);
    cout << "Toplam " << kitapSayisi << " kitap listelendi.\n";
}

// Sondan basa, prev isaretcisi ile gezerek listeler. O(n)
// Cift yonlu listenin tek yonlu listeye gore avantaji budur.
static void geriListele()
{
    baslikYazdir("KATALOG (Sondan Basa - prev ile)");
    if (son == nullptr) {
        cout << "[!] Katalog bos. Listelenecek kitap yok.\n";
        return;
    }

    kitapTabloBasligiYazdir();
    KitapDugum* gezici = son;
    while (gezici != nullptr) {
        kitapYazdir(gezici->veri);
        gezici = gezici->prev;
    }
    cizgiCiz(72);
    cout << "Toplam " << kitapSayisi << " kitap listelendi.\n";
}

// Toplam, ortalama, en az / en cok sayfali kitap ve esigi asanlar. O(n)
static void katalogAnalizi()
{
    baslikYazdir("KATALOG ANALIZI");
    if (bas == nullptr) {
        cout << "[!] Katalog bos. Analiz yapilamaz.\n";
        return;
    }

    // Tek gezinmede toplam, en az ve en cok sayfali kitabi bul
    long long toplamSayfa = 0;
    KitapDugum* enAz = bas;
    KitapDugum* enCok = bas;

    KitapDugum* gezici = bas;
    while (gezici != nullptr) {
        toplamSayfa += gezici->veri.sayfaSayisi;
        if (gezici->veri.sayfaSayisi < enAz->veri.sayfaSayisi) {
            enAz = gezici;
        }
        if (gezici->veri.sayfaSayisi > enCok->veri.sayfaSayisi) {
            enCok = gezici;
        }
        gezici = gezici->next;
    }

    double ortalama = static_cast<double>(toplamSayfa) / kitapSayisi;

    cout << "Toplam kitap sayisi   : " << kitapSayisi << "\n";
    cout << "Toplam sayfa sayisi   : " << toplamSayfa << "\n";
    // fixed/setprecision cout uzerinde kalici oldugu icin ayri bir akista
    // bicimlendiriyoruz; boylece diger modullerin ciktilari etkilenmez.
    ostringstream ortalamaMetni;
    ortalamaMetni << fixed << setprecision(2) << ortalama;
    cout << "Ortalama sayfa sayisi : " << ortalamaMetni.str() << "\n";
    cout << "En az sayfali kitap   : " << enAz->veri.ad << " (" << enAz->veri.sayfaSayisi << " sayfa)\n";
    cout << "En cok sayfali kitap  : " << enCok->veri.ad << " (" << enCok->veri.sayfaSayisi << " sayfa)\n";

    // Esik degerini asan kitaplar
    cout << "\n";
    int esik = tamSayiOku("Esik sayfa sayisi girin (bu degerden fazla olanlar listelenir): ", 0, MAKS_SAYFA);

    int asanSayisi = 0;
    gezici = bas;
    while (gezici != nullptr) {
        if (gezici->veri.sayfaSayisi > esik) {
            if (asanSayisi == 0) {
                cout << "\n" << esik << " sayfadan fazla olan kitaplar:\n";
                kitapTabloBasligiYazdir();
            }
            kitapYazdir(gezici->veri);
            asanSayisi++;
        }
        gezici = gezici->next;
    }

    if (asanSayisi == 0) {
        cout << "[!] " << esik << " sayfadan fazla olan kitap yok.\n";
    } else {
        cizgiCiz(72);
        cout << "Esigi asan kitap sayisi: " << asanSayisi << "\n";
    }
}

// ============================================================================
//  MENU ISLEMLERI (kullanici ile etkilesim + islem gecmisine kayit)
// ============================================================================

// Kullanicidan yeni kitap bilgilerini okur.
// ID zaten varsa uyari verir ve false dondurur.
static bool yeniKitapOku(Kitap& kitap)
{
    kitap.id = tamSayiOku("Kitap ID (1-999999): ", 1, MAKS_ID);
    if (idIleBul(kitap.id) != nullptr) {
        cout << "[!] " << kitap.id << " ID'li bir kitap zaten var. Farkli bir ID secin.\n";
        return false;
    }
    kitap.ad = metinOku("Kitap adi: ");
    kitap.yazar = metinOku("Yazar: ");
    kitap.sayfaSayisi = tamSayiOku("Sayfa sayisi (1-100000): ", 1, MAKS_SAYFA);
    return true;
}

static void menuBasaEkle()
{
    baslikYazdir("BASA KITAP EKLE");
    Kitap kitap;
    if (!yeniKitapOku(kitap)) {
        return;
    }
    basaEkle(kitap);
    cout << "[+] \"" << kitap.ad << "\" katalogun basina eklendi.\n";
    islemKaydet("Kitap eklendi (basa): ID " + to_string(kitap.id) + " - " + kitap.ad);
}

static void menuSonaEkle()
{
    baslikYazdir("SONA KITAP EKLE");
    Kitap kitap;
    if (!yeniKitapOku(kitap)) {
        return;
    }
    sonaEkle(kitap);
    cout << "[+] \"" << kitap.ad << "\" katalogun sonuna eklendi.\n";
    islemKaydet("Kitap eklendi (sona): ID " + to_string(kitap.id) + " - " + kitap.ad);
}

static void menuHedefOncesineEkle()
{
    baslikYazdir("BELIRLI ID'DEN ONCE KITAP EKLE");
    if (bas == nullptr) {
        cout << "[!] Katalog bos, hedef alinacak kitap yok. Basa veya sona ekleme kullanin.\n";
        return;
    }

    // Once hedefi kontrol ediyoruz; yoksa kullaniciya bosuna bilgi girdirmeyelim.
    int hedefId = tamSayiOku("Hangi ID'den once eklensin? ");
    if (idIleBul(hedefId) == nullptr) {
        cout << "[!] " << hedefId << " ID'li kitap bulunamadi. Ekleme yapilmadi.\n";
        return;
    }

    Kitap kitap;
    if (!yeniKitapOku(kitap)) {
        return;
    }
    hedefOncesineEkle(hedefId, kitap);
    cout << "[+] \"" << kitap.ad << "\" ID " << hedefId << " olan kitabin onune eklendi.\n";
    islemKaydet("Kitap eklendi (ID " + to_string(hedefId) + " oncesine): ID "
                + to_string(kitap.id) + " - " + kitap.ad);
}

static void menuSil()
{
    baslikYazdir("ID ILE KITAP SIL");
    if (bas == nullptr) {
        cout << "[!] Katalog bos. Silinecek kitap yok.\n";
        return;
    }

    int id = tamSayiOku("Silinecek kitabin ID'si: ");
    Kitap silinen;
    if (!idIleSil(id, silinen)) {
        cout << "[!] " << id << " ID'li kitap bulunamadi. Silme yapilmadi.\n";
        return;
    }
    cout << "[OK] \"" << silinen.ad << "\" katalogdan silindi. Kalan kitap: " << kitapSayisi << "\n";
    islemKaydet("Kitap silindi: ID " + to_string(silinen.id) + " - " + silinen.ad);
}

// ============================================================================
//  main.cpp TARAFINDAN CAGRILANLAR
// ============================================================================

void modul1OrnekVeriYukle()
{
    // ID'ler bilerek karisik sirada: Modul 3'teki siralama algoritmalari
    // anlamli bir sonuc gostersin.
    Kitap ornekler[] = {
        {104, "Algoritmalara Giris",          "Thomas H. Cormen",    1312},
        {101, "Veri Yapilari ve Algoritmalar", "Rifat Colkesen",      420},
        {107, "Kurk Mantolu Madonna",         "Sabahattin Ali",      160},
        {103, "Temiz Kod",                    "Robert C. Martin",    464},
        {106, "Suc ve Ceza",                  "Fyodor Dostoyevski",  687},
        {102, "C++ Programlama Dili",         "Bjarne Stroustrup",   1368},
        {105, "Simyaci",                      "Paulo Coelho",        188}
    };
    int adet = sizeof(ornekler) / sizeof(ornekler[0]);

    for (int i = 0; i < adet; i++) {
        sonaEkle(ornekler[i]);
    }
}

void modul1Temizle()
{
    int silinen = 0;
    KitapDugum* gezici = bas;
    while (gezici != nullptr) {
        KitapDugum* sonraki = gezici->next;   // silmeden once sonrakini sakla
        delete gezici;
        gezici = sonraki;
        silinen++;
    }
    bas = nullptr;
    son = nullptr;
    kitapSayisi = 0;
    cout << "[OK] Modul 1A - Kitap katalogu: " << silinen << " dugum silindi (delete).\n";
}

void modul1Menu()
{
    while (true) {
        baslikYazdir("MODUL 1 - KITAP KATALOGU (Cift Yonlu Bagli Liste)");
        cout << "  1. Basa Kitap Ekle\n"
             << "  2. Sona Kitap Ekle\n"
             << "  3. Belirli Bir ID'den Once Kitap Ekle\n"
             << "  4. ID ile Kitap Sil\n"
             << "  5. Kitaplari Listele (Bastan Sona - next)\n"
             << "  6. Kitaplari Listele (Sondan Basa - prev)\n"
             << "  7. Katalog Analizi\n"
             << "  8. Duyuru Panosu (Dairesel Bagli Liste)\n"
             << "  9. Dosya Islemleri (Katalogu Yaz / Oku)\n"
             << "  0. Ana Menuye Don\n";
        cizgiCiz();
        cout << "Katalogdaki kitap sayisi: " << kitapSayisi << "\n";

        int secim = tamSayiOku("Seciminiz: ");
        switch (secim) {
            case 1: menuBasaEkle();          break;
            case 2: menuSonaEkle();          break;
            case 3: menuHedefOncesineEkle(); break;
            case 4: menuSil();               break;
            case 5: ileriListele();          break;
            case 6: geriListele();           break;
            case 7: katalogAnalizi();        break;
            case 8: duyuruMenu();            break;   // 2. ogrenci
            case 9: dosyaIslemleriMenu();    break;   // 2. ogrenci
            case 0: return;
            default:
                cout << "[!] Gecersiz secim: " << secim << ". Lutfen 0-9 arasinda bir deger girin.\n";
        }
    }
}
