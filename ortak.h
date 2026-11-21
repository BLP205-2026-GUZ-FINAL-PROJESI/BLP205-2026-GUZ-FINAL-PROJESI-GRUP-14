// ============================================================================
//  ortak.h
//  Tum modullerin kullandigi ortak yardimci fonksiyonlar.
//  - Guvenli kullanici girdisi (tamSayiOku, metinOku)
//  - Ekran duzeni (cizgiCiz, baslikYazdir)
//  - Girdi akisi biterse (Ctrl+Z / Ctrl+D) bellegi temizleyip cikma
//  Sorumlu: 1. Ogrenci
// ============================================================================
#ifndef ORTAK_H
#define ORTAK_H

#include <string>

// Kullanicidan tam sayi okur. Harf, bos giris veya "12abc" gibi
// girislerde uyari verip tekrar sorar.
int tamSayiOku(const std::string& mesaj);

// Kullanicidan [minDeger, maxDeger] araliginda tam sayi okur.
// Aralik disindaki degerlerde uyari verip tekrar sorar.
int tamSayiOku(const std::string& mesaj, int minDeger, int maxDeger);

// Kullanicidan bos olmayan bir metin okur. Bastaki/sondaki bosluklari siler.
// '|' karakterine izin vermez, cunku dosyaya yazarken alan ayiraci olarak
// '|' kullaniliyor (ornek: 101|Ad|Yazar|250).
std::string metinOku(const std::string& mesaj);

// Ekrana ayni karakterden olusan bir cizgi cizer.
void cizgiCiz(int uzunluk = 60, char karakter = '-');

// Ekrana cizgiler arasinda bir baslik yazar.
void baslikYazdir(const std::string& baslik);

// Girdi akisi bittiginde (EOF) cagrilir: mesaj verir, tum bellegi
// temizler ve programi sonlandirir. Geri donmez.
[[noreturn]] void girdiAkisiBitti();

// Tum modullerin bellegini temizler. Tanimi main.cpp icindedir.
// Hem normal cikista hem de girdiAkisiBitti() icinde cagrilir.
void tumBellegiTemizle();

#endif // ORTAK_H
