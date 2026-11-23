# Kampüs Kütüphanesi ve Öğrenci Hizmetleri Otomasyonu

> **Not:** Geliştirme aşamasında. Modüller ekip üyeleri tarafından tamamlandıkça bu belge güncellenecektir.

**Ders:** BLP 205 Veri Yapıları – Final Projesi
**Grup:** 14 (BLP205-2026-GUZ-FINAL-PROJESI-GRUP-14)
**Kurum:** Doğuş Üniversitesi MYO – Bilgisayar Programcılığı
**Dil / Standart:** C++11 (konsol uygulaması)

## Projenin Amacı

Bir kampüs kütüphanesinin temel işlerini (kitap kataloğu, duyurular, ödünç bekleme sırası, işlem geçmişi, kitap sıralama/arama ve kampüs içi rota bulma) konsol üzerinden yöneten bir otomasyon geliştirmek. Projede her iş, derste işlenen bir veri yapısı veya algoritma ile **STL konteyneri kullanmadan** kendimiz tarafından gerçekleştirilmiştir.

## Ekip

Görev dağılımı ve kişi bazlı katkılar için: [GOREV_DAGILIMI.md](GOREV_DAGILIMI.md)

## Kullanılan Veri Yapıları ve Algoritmalar

| Modül | Konu | Veri yapısı / Algoritma | Dosya |
|---|---|---|---|
| 1A | Kitap kataloğu | Çift yönlü bağlı liste (`prev` / `next`) | `modul1_kitap.*` |
| 1B | Duyuru panosu | Tek yönlü dairesel bağlı liste | `modul1_duyuru_dosya.*` |
| 1B | Kalıcı kayıt | Dosyaya yazma / okuma (`ofstream` / `ifstream`) | `modul1_duyuru_dosya.*` |
| 2 | İşlem geçmişi | Bağlı liste tabanlı yığın (LIFO) | `modul2_yigin_kuyruk.*` |
| 2 | Ödünç bekleme sırası | Bağlı liste tabanlı kuyruk (FIFO) | `modul2_yigin_kuyruk.*` |
| 3 | Kitap sıralama | Bubble Sort, Insertion Sort, Quick Sort | `modul3_siralama.*` |
| 3 | Kitap arama | Binary Search (ikili arama) | `modul3_siralama.*` |
| 4 | Kampüs rotası | Komşuluk matrisi, BFS, DFS, Dijkstra | `modul4_graf.*` |

## Dosya Yapısı

```
main.cpp                    Ana menü, örnek veriler, çıkışta bellek temizliği
ortak.h / ortak.cpp         Güvenli girdi okuma ve ortak yardımcı fonksiyonlar
modul1_kitap.*              Modül 1A – Kitap kataloğu
modul1_duyuru_dosya.*       Modül 1B – Duyuru panosu ve dosya işlemleri
modul2_yigin_kuyruk.*       Modül 2  – Yığın ve kuyruk
modul3_siralama.*           Modül 3  – Sıralama ve arama
modul4_graf.*               Modül 4  – Graf ve kampüs rotası
TEST_SENARYOLARI.md         Test tablosu
GOREV_DAGILIMI.md           Ekip görev dağılımı
ekran_goruntuleri/          Program ekran görüntüleri
```

## Derleme ve Çalıştırma

```bash
g++ -std=c++11 *.cpp -o kutuphane
./kutuphane
```

Uyarıları da görmek için:

```bash
g++ -std=c++11 -Wall -Wextra *.cpp -o kutuphane
```

## Menü Özeti

```
1. Modül 1 - Kitap Kataloğu, Duyurular, Dosya (Bağlı Listeler)
   1. Başa Kitap Ekle
   2. Sona Kitap Ekle
   3. Belirli Bir ID'den Önce Kitap Ekle
   4. ID ile Kitap Sil
   5. Kitapları Listele (Baştan Sona - next)
   6. Kitapları Listele (Sondan Başa - prev)
   7. Katalog Analizi
   8. Duyuru Panosu (Dairesel Bağlı Liste)
   9. Dosya İşlemleri (Kataloğu Yaz / Oku)
2. Modül 2 - Ödünç Sırası ve İşlem Geçmişi (Kuyruk / Yığın)
3. Modül 3 - Kitap Sıralama ve Arama Algoritmaları
4. Modül 4 - Kampüs Rota Analizi (Graf)
0. Çıkış
```

## Örnek Kullanım

_(Modüller tamamlandığında doldurulacak.)_

## Kampüs Modeli

_(5. öğrenci tarafından doldurulacak: birimler ve mesafeler tablosu.)_

## Bilinen Sınırlılıklar

- Program yalnızca konsolda çalışır; Türkçe karakter sorunu yaşanmaması için kod ve ekran mesajları ASCII karakterlerle yazılmıştır.
- Veriler program kapanınca silinir; kalıcı kayıt yalnızca Modül 1B'deki dosya işlemleriyle yapılır.
- Kitap adı, yazar gibi metin alanlarında `|` karakteri kullanılamaz (dosya ayırıcısı olduğu için).

## Testler

Test senaryoları ve sonuçları: [TEST_SENARYOLARI.md](TEST_SENARYOLARI.md)

## Ekran Görüntüleri

_(Teslimden önce `ekran_goruntuleri/` klasörüne eklenecek.)_
