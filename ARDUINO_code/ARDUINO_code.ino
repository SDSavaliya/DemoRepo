#include <SPI.h>
#include <Servo.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
Servo s1;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
void setup() 
{
  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  s1.attach(3);
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  //Servo s1;

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  analogWrite(3,00);
  if (content.substring(1) == "C5 C8 56 73") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("You are authorized to enter.");
    Serial.println();
    //analogWrite(3,360);
    s1.write(90);
    delay(1000);
    analogWrite(3,0);
 
  }
  else   {
    Serial.println(" You are not authorized person");
    delay(3000);
    
  }
} 
