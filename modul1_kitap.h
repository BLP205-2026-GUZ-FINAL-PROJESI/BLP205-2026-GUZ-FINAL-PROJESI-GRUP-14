// ============================================================================
//  modul1_kitap.h
//  Modul 1A: Kitap katalogu - CIFT YONLU BAGLI LISTE
//  Sorumlu: 1. Ogrenci
//
//  Her dugum bir kitabi tutar ve iki isaretcisi vardir:
//    prev -> bir onceki dugum (ilk dugumde nullptr)
//    next -> bir sonraki dugum (son dugumde nullptr)
//  Listenin basi (bas) ve sonu (son) isaretcileri modul icinde tutulur.
// ============================================================================
#ifndef MODUL1_KITAP_H
#define MODUL1_KITAP_H

#include <string>

// Bir kitabin bilgileri
struct Kitap {
    int id;
    std::string ad;
    std::string yazar;
    int sayfaSayisi;
};

// Cift yonlu bagli liste dugumu
struct KitapDugum {
    Kitap veri;
    KitapDugum* prev;   // onceki dugum
    KitapDugum* next;   // sonraki dugum
};

// --- main.cpp tarafindan kullanilan fonksiyonlar ---
void modul1OrnekVeriYukle();   // 7 ornek kitap ekler
void modul1Menu();             // Modul 1 alt menusu
void modul1Temizle();          // Tum dugumleri delete eder

// --- Diger modullerin kullanabilecegi fonksiyonlar ---
// Listenin ilk dugumunu dondurur (bos ise nullptr). Sadece okuma amaclidir;
// listeyi degistirmek icin Modul 1 menusu kullanilmalidir.
KitapDugum* katalogBasi();

// Listedeki kitap sayisini dondurur.
int katalogBoyutu();

// Kitap tablosunun baslik satirini yazar (ID, Ad, Yazar, Sayfa).
void kitapTabloBasligiYazdir();

// Tek bir kitabi tablo satiri olarak yazar.
void kitapYazdir(const Kitap& kitap);

#endif // MODUL1_KITAP_H
