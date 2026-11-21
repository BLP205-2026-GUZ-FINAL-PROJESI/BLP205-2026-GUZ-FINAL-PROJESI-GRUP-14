# Test Senaryoları

Her test programı çalıştırarak uygulanır. **Gerçekleşen** sütununa ne olduğu, **Durum** sütununa `Geçti` / `Kaldı`, **Test eden** sütununa testi yapan kişinin adı yazılır.

Derleme: `g++ -std=c++11 *.cpp -o kutuphane` → Çalıştırma: `./kutuphane`

## Genel (Ana Menü ve Girdi Kontrolü)

| No | Senaryo | Girdi | Beklenen | Gerçekleşen | Durum | Test eden |
|---|---|---|---|---|---|---|
| G1 | Program açılışı | – | Örnek veriler yüklenir, ana menü görünür | | | |
| G2 | Geçersiz menü seçimi | Ana menü: `7` | "Geçersiz seçim" uyarısı, menü tekrar gelir | | | |
| G3 | Harf girişi | Ana menü: `abc` | "Geçersiz giriş" uyarısı, tekrar sorar | | | |
| G4 | Boş giriş | Ana menü: Enter | "Boş giriş" uyarısı, tekrar sorar | | | |
| G5 | Sayı + harf | Ana menü: `1abc` | "Sadece tam sayı girin" uyarısı | | | |
| G6 | Çıkışta bellek temizliği | Ana menü: `0` | Her modül için silinen düğüm sayısı yazılır | | | |

## Modül 1A – Kitap Kataloğu (Çift Yönlü Bağlı Liste)

| No | Senaryo | Girdi | Beklenen | Gerçekleşen | Durum | Test eden |
|---|---|---|---|---|---|---|
| 1A-1 | İleri listeleme | `1` → `5` | 7 örnek kitap baştan sona listelenir | | | |
| 1A-2 | Geri listeleme | `1` → `6` | 7 kitap ters sırada listelenir | | | |
| 1A-3 | Başa ekleme | `1` → `1` → ID `200`, ad, yazar, `300` | Kitap listenin başında görünür | | | |
| 1A-4 | Sona ekleme | `1` → `2` → ID `201` ... | Kitap listenin sonunda görünür | | | |
| 1A-5 | Hedef ID öncesine ekleme | `1` → `3` → hedef `103` → ID `202` ... | Kitap 103'ün hemen önünde görünür | | | |
| 1A-6 | Olmayan hedef ID | `1` → `3` → hedef `999` | "Bulunamadı" mesajı, ekleme yapılmaz | | | |
| 1A-7 | Aynı ID ile ekleme | `1` → `2` → ID `101` | "Bu ID zaten var" uyarısı | | | |
| 1A-8 | İlk düğümü silme | `1` → `4` → ilk kitabın ID'si | Silinir, ileri/geri listeleme doğru | | | |
| 1A-9 | Ortadaki düğümü silme | `1` → `4` → `103` | Silinir, ileri/geri listeleme doğru | | | |
| 1A-10 | Son düğümü silme | `1` → `4` → son kitabın ID'si | Silinir, geri listeleme yeni sondan başlar | | | |
| 1A-11 | Olmayan ID silme | `1` → `4` → `999` | "Bulunamadı" mesajı | | | |
| 1A-12 | Katalog analizi | `1` → `7` → eşik `500` | Toplam, ortalama, en az/en çok, eşiği aşanlar doğru | | | |
| 1A-13 | Boş katalog | Tüm kitapları sil → `5`, `6`, `7` | "Katalog boş" mesajı | | | |
| 1A-14 | `\|` karakteri | Kitap adı: `A\|B` | "'\|' kullanılamaz" uyarısı | | | |
| 1A-15 | Geçersiz sayfa sayısı | Sayfa: `-5` veya `0` | Aralık uyarısı, tekrar sorar | | | |

## Modül 1B – Duyuru Panosu ve Dosya İşlemleri

| No | Senaryo | Girdi | Beklenen | Gerçekleşen | Durum | Test eden |
|---|---|---|---|---|---|---|
| 1B-1 | Duyuruları listeleme | `1` → `8` → `2` | Örnek duyurular bir tam tur listelenir, "Başlangıç düğümüne geri dönüldü" yazar | | | |
| 1B-2 | Duyuru ekleme | `1` → `8` → `1` → metin | Duyuru sona eklenir, numara otomatik artar | | | |
| 1B-3 | Kataloğu dosyaya yazma | `1` → `9` → `1` | `katalog.txt` oluşur, yazılan kayıt sayısı gösterilir | | | |
| 1B-4 | Dosyadan okuma | `1` → `9` → `2` | Kayıtlar tablo hâlinde gösterilir | | | |
| 1B-5 | Yaz ve geri oku | `1` → `9` → `3` | Yazılan ve okunan kayıt sayısı aynı | | | |
| 1B-6 | Bozuk satır | `katalog.txt`'ye eksik alanlı satır ekle → `2` | Bozuk satır atlanır, uyarı verilir | | | |
| 1B-7 | Dosya yok | `katalog.txt`'yi sil → `2` | "Dosya bulunamadı" mesajı | | | |

## Modül 2 – Yığın ve Kuyruk

| No | Senaryo | Girdi | Beklenen | Gerçekleşen | Durum | Test eden |
|---|---|---|---|---|---|---|
| 2-1 | Kuyruğa öğrenci ekleme | `2` → `1` → no, ad, kitap | Öğrenci sıranın sonuna eklenir | | | |
| 2-2 | Kuyruğu listeleme | `2` → `3` | Öğrenciler FIFO sırasıyla, sıra numarasıyla listelenir | | | |
| 2-3 | Dequeue | `2` → `2` | Baştaki öğrenciye "kitap verildi" mesajı, kayıt silinir | | | |
| 2-4 | Boş kuyrukta Dequeue | Kuyruğu boşalt → `2` | "Kuyruk boş" mesajı | | | |
| 2-5 | Aynı öğrenci no | Kuyrukta olan no ile ekleme | Uyarı verilir | | | |
| 2-6 | Negatif öğrenci no | No: `-3` | Uyarı verilir | | | |
| 2-7 | İşlem geçmişi | Modül 1'de kitap ekle → `2` → `4` | Eklenen kitap yığının en üstünde | | | |
| 2-8 | Peek | `2` → `5` | En son işlem gösterilir, yığından çıkmaz | | | |
| 2-9 | Pop | `2` → `6` | En son işlem çıkarılır ve gösterilir | | | |
| 2-10 | Boş yığında Pop/Peek | Yığını boşalt → `5`, `6` | "Yığın boş" mesajı | | | |

## Modül 3 – Sıralama ve Arama

| No | Senaryo | Girdi | Beklenen | Gerçekleşen | Durum | Test eden |
|---|---|---|---|---|---|---|
| 3-1 | Bubble vs Insertion | `3` → `1` | Orijinal sıra, iki sıralama sonucu ve karşılaştırma tablosu | | | |
| 3-2 | Quick Sort | `3` → `2` | Kitaplar ID'ye göre sıralı, sayaçlar gösterilir | | | |
| 3-3 | Binary Search (var) | `3` → `2` → `105` | Adımlar ve "bulundu" mesajı | | | |
| 3-4 | Binary Search (yok) | `3` → `2` → `999` | Adımlar ve "bulunamadı" mesajı | | | |
| 3-5 | Boş katalog | Tüm kitapları sil → `3` → `1`, `2` | "Katalog boş" mesajı | | | |
| 3-6 | Tek kitap | Tek kitap bırak → `3` → `1` | Anlaşılır mesaj | | | |

## Modül 4 – Graf ve Kampüs Rotası

| No | Senaryo | Girdi | Beklenen | Gerçekleşen | Durum | Test eden |
|---|---|---|---|---|---|---|
| 4-1 | Komşuluk matrisi | `4` → `1` | Simetrik matris başlıklı tablo hâlinde | | | |
| 4-2 | BFS | `4` → `2` → `0` | Ziyaret sırası "A -> B -> C" biçiminde | | | |
| 4-3 | DFS | `4` → `3` → `0` | Ziyaret sırası "A -> B -> C" biçiminde | | | |
| 4-4 | Dijkstra | `4` → `4` → `0` → `5` | En kısa mesafe ve rota | | | |
| 4-5 | Başlangıç = hedef | `4` → `4` → `2` → `2` | Uygun mesaj | | | |
| 4-6 | Geçersiz birim no | `4` → `2` → `99` | "Geçersiz bina numarası" | | | |
