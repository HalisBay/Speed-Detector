//Kütüphanelerimizi çağırıyoruz
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
//lcd ye bağlı I2c modülü ne "lcd" ismini verdik
LiquidCrystal_I2C lcd(0x27, 16, 2);
int yLed = 2; //2 nolu pine yeşil ledimizi takıyoruz
int mLed = 3; //3 nolu pine mavi ledimizi takıyoruz
int kLed = 4; //4 nolu pine kırmızı ledimizi takıyoruz
int bzzr = 8; // 8nolu pine buzzer imizi takıyoruz
float irPinA = 11; // 11 nolu pine IR sensörümüzü takıyoruz
float irPinB = 12; //// 12 nolu pine diğer IR sensörümüzü takıyoruz
/*************************************************************************/
//devremizde bize yardım edecek tanımlamaları yapıyoruz
float irValA;
float irValB;
float fark;
float hiz;
float t1; 
float t2;
unsigned long girisSn = 0;
unsigned long cikisSn = 0;
float yol = 500; // alına yol olarak 500 metre verdik

void configLCD()
{
  //lcd ayarlarını yapıyoruz ; giriş ekranında karşılaştığımız ekran burası
  lcd.setCursor(0, 0);
  lcd.print("Hiz olcer");
  lcd.setCursor(0, 1);
  lcd.print("iyi yolculuklar");
}

void setup()
{
  //Giriş ve çıkışları belirtiyoruz
  pinMode(irPinA, INPUT);
  pinMode(irPinB, INPUT);
  pinMode(mLed, OUTPUT);
  pinMode(yLed, OUTPUT);
  pinMode(kLed, OUTPUT);
  pinMode(bzzr, OUTPUT);

  //seri portumuzu açıyoruz (bilgisayara bağlı iken bilgisayar üzerindenden de değerleri görebilmek için)
  Serial.begin(9600);
  
  lcd.init(); //lcdyi başlatıyoruz
  lcd.backlight();//lcdmizin arka planındaki ışığı açıyoruz
  configLCD();
}

void loop()
{
  digitalWrite(mLed, HIGH);/*sistemin çalışır durumda olduğunu belirtmek için mavi ledi, 
  sürekli yakıyoruz.Ancak Hız aşımı olduğunda bu led bir miktar sönecek*/
  irValA = digitalRead(irPinA);//IR sensörümüzün ilk değerini 11 nolu pinden alıyoruz,(yola giriş) 
  irValB = digitalRead(irPinB);//IR sensörümüzün ikinci değerini 12 nolu pinden alıyoruz(yol bitişi)
  if (irValA == LOW) 
  {
    girisSn = millis(); // Giriş süresini alıp hafızada saklıyoruz.
  }
  if (irValB == LOW) 
  {
    cikisSn = millis(); // çıkış süresini alıp hafızada saklıyoruz
    fark = cikisSn - girisSn; // giriş-çıkış arasındaki farkı buluyoruz buda bizim ne kadar süre yol aldığımızı veriyor
    fark = fark / 1000;/* fark bize milisaniye cinsinden veriliyor. 
    ör:3565 ms olsun. biz bunu bine bölerek 3,565 sn olduğunu hafızaya kaydedip adına "fark" diyoruz. 
    */
    hiz = yol / fark; // hız=yol/zaman formülü
    
  //Seri ekranda;giriş-çıkış saniyeleri, giriş ve çıkış saniyeleri arasındaki süre(yolda harcanan süre),ve hızımızı yazdırıyoruz
    Serial.print("giris : ");
    Serial.println(girisSn);
    Serial.print("cikis : ");
    Serial.println(cikisSn);
    Serial.print("fark : ");
    Serial.println(fark);
    Serial.print("hiz : ");
    Serial.println(hiz);

    /*hız; 500km/h in üstünde ise, mavi led ve yeşil ledi söndürüyoruz.
    kırmızı led ve buzzeri 8 kere 100er ms aralıklarla çalıştırıyoruz*/
    if (hiz > 500) {
        digitalWrite(mLed, LOW);
        digitalWrite(yLed, LOW);
      for (int i = 0; i < 8; i++) {
        digitalWrite(kLed, HIGH);
        digitalWrite(bzzr, HIGH);
        delay(100);
        digitalWrite(kLed, LOW);
        digitalWrite(bzzr, LOW);
        delay(100);
      }
    }
    
    /*eğer hız 500 km/h in altında ise yeşil led yanıyor.
    Herhangi bir sorun olmadığı için (hız aşımı olmadığı için) mavi ledde yanmaya devam ediyor*/
    else {
      
      digitalWrite(yLed, HIGH);
      delay(1000);
      digitalWrite(yLed, LOW);
      
      
    }

  //değerleri LCD ekrana yazdırma komutları
  lcd.clear(); // lcd yi temizliyoruz
  t1 = girisSn / 1000; // t1 = giriş süresi /1000
  t2 = cikisSn / 1000; // t2 = çıkış süresi /1000
  lcd.setCursor(0, 0); /* lcd miz 16x2 lik, 16 sütun ve 2 satır. sayımlar proğramlamada 0,1,2,3... diye gider. 0. satır 0.sütündan
  itibaren yazdırıyoruz*/
  lcd.print("giris: ");
  lcd.print(t1);
  /*1. satır 0.sütündan itibaren yazdırıyoruz*/
  lcd.setCursor(0, 1);
  lcd.print("cikis: ");
  lcd.print(t2);
  delay(3000); // 3sn bu ekranda bekle
  lcd.clear(); // lcd yi temizle
  lcd.setCursor(0, 0);
  lcd.print("sure: ");
  lcd.print(fark);
  lcd.print("sn");
  lcd.setCursor(0, 1);
  lcd.print("hiz: ");
  lcd.print(hiz);
  lcd.print(" km/h");
  delay(3000);
  lcd.clear();
  configLCD();// tekrardan lcd nin giriş ekranındaki gibi gözükmesi için bunu yapıyoruz.
  }
  }
