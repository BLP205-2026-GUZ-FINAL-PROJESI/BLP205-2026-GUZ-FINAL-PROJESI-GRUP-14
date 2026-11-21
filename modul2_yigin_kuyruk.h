// ============================================================================
//  modul2_yigin_kuyruk.h
//  Modul 2: Islem gecmisi (BAGLI LISTE TABANLI YIGIN) ve
//           odunc bekleme sirasi (BAGLI LISTE TABANLI KUYRUK)
//  Sorumlu: 3. Ogrenci
//
//  NOT: Bu 4 fonksiyonun imzasi sabittir, degistirmeyin.
//       main.cpp ve modul1_kitap.cpp bu fonksiyonlari cagiriyor.
// ============================================================================
#ifndef MODUL2_YIGIN_KUYRUK_H
#define MODUL2_YIGIN_KUYRUK_H

#include <string>

void modul2OrnekVeriYukle();   // Acilista ornek islem ve ogrenciler
void modul2Menu();             // Ana menu -> 2
void modul2Temizle();          // Cikista yigin ve kuyrugu delete eder

// Yapilan bir islemi islem gecmisi yiginina ekler (push).
// Modul 1'de kitap eklenince / silinince cagrilir.
void islemKaydet(const std::string& aciklama);

#endif // MODUL2_YIGIN_KUYRUK_H
