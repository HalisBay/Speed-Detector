# Proje Tanımı
Devrenin asıl amacı Kızılötesi-IR sensörünün kullanımı hakkında fikir sahibi olmaktır, Kızılötesi (IR) sensörü, ortamdaki kızılötesi radyasyonu ölçen ve algılayan elektronik bir cihazdır. IR sensörü yardımıyla nesnelerin saatteki hızlarını (KM/S) ölçmek mümkündür (Tabi bunun için 2 adet IR sensörüne ihtiyaç vardır, çünkü; iki sensör arasındaki hız ölçülür.) bu proje sayesinde iki IR sensörü arasından geçen nesnelerin hızlarını ölçebilir, hız sınırını aşan araç-nesneler hakkında bilgi sahibi olabiliriz

# Malzemeler ve Fiyatları. Not:Fiyat sizinde tahmin ettiğiniz üzere değişebilir.
![image](https://user-images.githubusercontent.com/77541788/131997498-ccbf4ee3-41fc-4ef4-963d-4a5a6cd256ae.png)


# Devre Şeması
![devreSeması](https://user-images.githubusercontent.com/77541788/131997302-91c681db-6839-4b21-b031-5f818e1fa64f.png)

# Genel Çalışma Prensibi
Arduino enerjilendiğinde sayaç aktifleşir ve enerjisi kesilene kadar saymaya devam eder. Ir sensörü A (ilk IR sensörü) o anda geçilen saniyeyi arduinoya iletir ve arduino bunu hafızasında tutar. Ardından Ir sensörü B (ikinci IR sensörü) den geçiş olduğu zaman oda arduinoda iletilir ve hafızaya kaydedilir. Matematiksel işlemler sonrası aracın; hızı, yolu tamamlama süresi, yola girdiği ve çıktığı zaman I2C modüllü lcd ekranda gözükür. Devre çalışıyoken mavi led sürekli yanar ancak 500 km/h hızı geçen araç, nesne vb. şeyler olursa; mavi led söner kırmızı led ve buzzer 8 kere 100 er mili saniye arayla +5 volt alır ve -5 volt alır (yanar-söner). Ardın dan lcd ekranda verileri görürüz, veriler bittikten sonra mavi led tekrar yanar. Birde yeşil led in yanma durumu vardır. Araç,nesne vb. şey iki IR sensörü arasından 500km/h hızdan düşük bir hızla geçerse mavi ledle beraber yeşil led de yanar(1 saniye) ve ardından yeşil led söner mavi led yanmaya devam eder.





