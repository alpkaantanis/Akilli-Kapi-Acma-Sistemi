#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <MFRC522.h>

 LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2); 
 MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)
 Servo myservo;
 int angle=0;
 String tagUID = "0D 2E 5F 4B"; // String to store UID of tag. Change it with your tag's UID
 char d;
 int pos;
 void setup() {
 lcd.init();
 lcd.backlight();
 myservo.attach(8);
 SPI.begin(); // Init SPI bus
 mfrc522.PCD_Init(); // Init MFRC522
 lcd.clear();
 }
 void loop() {
 lcd.setCursor(0, 0);
 lcd.print("RFID KAPI KILIDI");
 delay(1000);
 lcd.setCursor(0, 1);
 lcd.print(" KARTINI GOSTER ");
 
 // Look for new cards
 if ( ! mfrc522.PICC_IsNewCardPresent()) {
 return;
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
 return;
 }
 //Reading from the card
 String tag = "";
 for (byte i = 0; i < mfrc522.uid.size; i++)
 {
 tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
 tag.concat(String(mfrc522.uid.uidByte[i], HEX));
 }
 tag.toUpperCase();
 
 //Checking the card
 if (tag.substring(1) == tagUID) //change here the UID of the card/cards that you want to give access
 {
 // If UID of tag is matched.
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("ERISIM IZNI");
 lcd.setCursor(0, 1);
 lcd.print("KAPI ACILDI");
 myservo.write(150);
 //digitalWrite(greenLed, HIGH);
 delay(3000);
 //digitalWrite(greenLed, LOW);
 myservo.write(80);
 lcd.clear();
 }
 
 else
 {
 // If UID of tag is not matched.
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("TANIMSIZ KART");
 lcd.setCursor(0, 1);
 lcd.print("GIRIS REDDEDILDI");
 delay(3000);
 lcd.clear();

  if(Serial.available())
{
  d=Serial.read();
}
if(d=='a')
{
  Serial.print(d);
  delay(300);
  for(pos=0;pos<=80;pos+=5)
   { myservo.write(pos);
   delay(20);
   }
   delay(5000);
   for(pos=80;pos>=0;pos-=5)
   { 
   myservo.write(pos);
   delay(20);
   }
   }
   d="";

 }
 }
