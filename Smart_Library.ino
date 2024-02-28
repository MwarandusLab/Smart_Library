#include <SPI.h>
#include <Wire.h>
#include <RFID.h>
#include <LiquidCrystal_I2C.h>

int Buzzer = 17;

int Physics_1 = 2;
int Physics_2 = 3;
int Physics_3 = 4;

int Engineering_1 = 5;
int Engineering_2 = 6;
int Engineering_3 = 7;

int Mathematics_1 = 10;
int Mathematics_2 = 11;
int Mathematics_3 = 12;

int Line_1_Red = 43;
int Line_1_Blue = 47;
int Line_1_Green = 45;

int Line_2_Red = 30;
int Line_2_Blue = 22;
int Line_2_Green = 24;

int Line_3_Red = 41;
int Line_3_Blue = 39;
int Line_3_Green = 26;

int Line_4_Green = 46;
int Line_4_Red = 17;
int Line_4_Blue = 18;  //

int Line_5_Blue = 40;
int Line_5_Red = 48;    //
int Line_5_Green = 49;  //

int Line_6_Red = 28;
int Line_6_Blue = 32;
int Line_6_Green = 23;

int Line_7_Red = 36;
int Line_7_Blue = 34;
int Line_7_Green = 38;

int Line_8_Red = 29;
int Line_8_Blue = 25;
int Line_8_Green = 27;

int Line_9_Red = 33;
int Line_9_Blue = 31;
int Line_9_Green = 42;


uint32_t tagID = 0;
#define SDA_DIO 9
#define RESET_DIO 8

enum State {
  WAIT_TAG,
  TAG_ID,
  BOOKS_BOOKED,
  LOCATION_1,
  LOCATION_2,
  LOCATION_3,
};

State currentState = WAIT_TAG;

RFID RC522(SDA_DIO, RESET_DIO);

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  SPI.begin();
  RC522.init();

  pinMode(Physics_1, INPUT);
  pinMode(Physics_2, INPUT);
  pinMode(Physics_3, INPUT);

  pinMode(Line_1_Red, OUTPUT);
  pinMode(Line_1_Blue, OUTPUT);
  pinMode(Line_1_Green, OUTPUT);

  pinMode(Line_2_Red, OUTPUT);
  pinMode(Line_2_Blue, OUTPUT);
  pinMode(Line_2_Green, OUTPUT);

  pinMode(Line_3_Red, OUTPUT);
  pinMode(Line_3_Blue, OUTPUT);
  pinMode(Line_3_Green, OUTPUT);

  pinMode(Line_4_Red, OUTPUT);
  pinMode(Line_4_Blue, OUTPUT);
  pinMode(Line_4_Green, OUTPUT);

  pinMode(Line_5_Red, OUTPUT);
  pinMode(Line_5_Blue, OUTPUT);
  pinMode(Line_5_Green, OUTPUT);

  pinMode(Line_6_Red, OUTPUT);
  pinMode(Line_6_Blue, OUTPUT);
  pinMode(Line_6_Green, OUTPUT);

  pinMode(Line_7_Red, OUTPUT);
  pinMode(Line_7_Blue, OUTPUT);
  pinMode(Line_7_Green, OUTPUT);

  pinMode(Line_8_Red, OUTPUT);
  pinMode(Line_8_Blue, OUTPUT);
  pinMode(Line_8_Green, OUTPUT);

  pinMode(Line_9_Red, OUTPUT);
  pinMode(Line_9_Blue, OUTPUT);
  pinMode(Line_9_Green, OUTPUT);


  digitalWrite(Line_1_Green, LOW);
  digitalWrite(Line_1_Red, LOW);
  digitalWrite(Line_1_Blue, LOW);

  digitalWrite(Line_2_Green, LOW);
  digitalWrite(Line_2_Red, LOW);
  digitalWrite(Line_2_Blue, LOW);

  digitalWrite(Line_3_Green, LOW);
  digitalWrite(Line_3_Red, LOW);
  digitalWrite(Line_3_Blue, LOW);

  digitalWrite(Line_4_Green, LOW);
  digitalWrite(Line_4_Red, LOW);
  digitalWrite(Line_4_Blue, LOW);  //

  digitalWrite(Line_5_Green, LOW);  //
  digitalWrite(Line_5_Red, LOW);    //
  digitalWrite(Line_5_Blue, LOW);

  digitalWrite(Line_6_Green, LOW);
  digitalWrite(Line_6_Red, LOW);
  digitalWrite(Line_6_Blue, LOW);

  digitalWrite(Line_7_Green, LOW);
  digitalWrite(Line_7_Red, LOW);
  digitalWrite(Line_7_Blue, LOW);

  digitalWrite(Line_8_Green, LOW);
  digitalWrite(Line_8_Red, LOW);
  digitalWrite(Line_8_Blue, LOW);

  digitalWrite(Line_9_Green, LOW);
  digitalWrite(Line_9_Red, LOW);
  digitalWrite(Line_9_Blue, LOW);



  pinMode(Engineering_1, INPUT);
  pinMode(Engineering_2, INPUT);
  pinMode(Engineering_3, INPUT);

  pinMode(Mathematics_1, INPUT);
  pinMode(Mathematics_2, INPUT);
  pinMode(Mathematics_3, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(7, 1);
  lcd.print("SYSTEM");
  lcd.setCursor(3, 2);
  lcd.print("INITIALIZATION");
  delay(2000);
}

void loop() {
  switch (currentState) {
    case WAIT_TAG:
      wait_tag();
      break;
    case TAG_ID:
      tag_id();
      break;
    case BOOKS_BOOKED:
      books_booked();
      break;
    case LOCATION_1:
      location_1();
      break;
    case LOCATION_2:
      location_2();
      break;
    case LOCATION_3:
      location_3();
      break;
  }
}

void wait_tag() {
  lcd.clear();
  lcd.setCursor(7, 1);
  lcd.print("PLACE");
  lcd.setCursor(2, 2);
  lcd.print("YOUR STUDENT ID");
  delay(500);
  if (RC522.isCard()) {
    RC522.readCardSerial();
    Serial.println("Card detected:");
    String tagID = "";
    for (int i = 0; i < 5; i++) {
      tagID += String(RC522.serNum[i], DEC);
    }
    Serial.println("Tag ID: " + tagID);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(tagID);
    if (tagID == "211171111163180") {
      Serial3.print("A");
      Serial.println("Data sent: A");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NAME: DERRICK KAMAU");
      lcd.setCursor(0, 1);
      lcd.print("BOOK_1: ");
      lcd.setCursor(0, 2);
      lcd.print("BOOK_2: ");
      lcd.setCursor(0, 3);
      lcd.print("BOOK_3: ");
      delay(1000);
    } else if (tagID == "147217126163151") {
      Serial3.print("B");
      Serial.println("Data sent: B");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NAME: LINAH ALMASI");
      lcd.setCursor(0, 1);
      lcd.print("BOOK_1: ");
      lcd.setCursor(0, 2);
      lcd.print("BOOK_2: ");
      lcd.setCursor(0, 3);
      lcd.print("BOOK_3: ");
      delay(1000);
    } else if (tagID == "6723420918106") {
      Serial3.print("C");
      Serial.println("Data sent: C");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NAME: KHERI KISIA");
      lcd.setCursor(0, 1);
      lcd.print("BOOK_1: ");
      lcd.setCursor(0, 2);
      lcd.print("BOOK_2: ");
      lcd.setCursor(0, 3);
      lcd.print("BOOK_3: ");
      delay(1000);
    }
    delay(2000);
    Serial.println();
    Serial.println();
  }
  delay(500);
}
void tag_id() {
}
void books_booked() {
}
void location_1() {
}
void location_2() {
}
void location_3() {
}
void kheri() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NAME: KHERI KISIA");
  lcd.setCursor(0, 1);
  lcd.print("BOOK_1: ");
  lcd.setCursor(0, 2);
  lcd.print("BOOK_2: ");
  lcd.setCursor(0, 3);
  lcd.print("BOOK_3: ");
  delay(3000);
}
void derrick() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NAME: DERRICK KAMAU");
  lcd.setCursor(0, 1);
  lcd.print("BOOK_1: ");
  lcd.setCursor(0, 2);
  lcd.print("BOOK_2: ");
  lcd.setCursor(0, 3);
  lcd.print("BOOK_3: ");
  delay(3000);
}
void linah() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NAME: LINAH ALMASI");
  lcd.setCursor(0, 1);
  lcd.print("BOOK_1: ");
  lcd.setCursor(0, 2);
  lcd.print("BOOK_2: ");
  lcd.setCursor(0, 3);
  lcd.print("BOOK_3: ");
  delay(3000);
}
void book_1_Green() {
  digitalWrite(Line_1_Green, HIGH);
  digitalWrite(Line_1_Red, LOW);
  digitalWrite(Line_1_Blue, LOW);
}
void book_1_Red() {
  digitalWrite(Line_1_Green, LOW);
  digitalWrite(Line_1_Red, HIGH);
  digitalWrite(Line_1_Blue, LOW);
}
void book_1_Blue() {
  digitalWrite(Line_1_Green, LOW);
  digitalWrite(Line_1_Red, LOW);
  digitalWrite(Line_1_Blue, HIGH);
}

void book_2_Green() {
  digitalWrite(Line_2_Green, HIGH);
  digitalWrite(Line_2_Red, LOW);
  digitalWrite(Line_2_Blue, LOW);
}
void book_2_Red() {
  digitalWrite(Line_2_Green, LOW);
  digitalWrite(Line_2_Red, HIGH);
  digitalWrite(Line_2_Blue, LOW);
}
void book_2_Blue() {
  digitalWrite(Line_2_Green, LOW);
  digitalWrite(Line_2_Red, LOW);
  digitalWrite(Line_2_Blue, HIGH);
}

void book_3_Green() {
  digitalWrite(Line_3_Green, HIGH);
  digitalWrite(Line_3_Red, LOW);
  digitalWrite(Line_3_Blue, LOW);
}
void book_3_Red() {
  digitalWrite(Line_3_Green, LOW);
  digitalWrite(Line_3_Red, HIGH);
  digitalWrite(Line_3_Blue, LOW);
}
void book_3_Blue() {
  digitalWrite(Line_3_Green, LOW);
  digitalWrite(Line_3_Red, LOW);
  digitalWrite(Line_3_Blue, HIGH);
}

void book_4_Green() {
  digitalWrite(Line_4_Green, HIGH);
  digitalWrite(Line_4_Red, LOW);
  digitalWrite(Line_4_Blue, LOW);
}
void book_4_Red() {
  digitalWrite(Line_4_Green, LOW);
  digitalWrite(Line_4_Red, HIGH);
  digitalWrite(Line_4_Blue, LOW);
}
void book_4_Blue() {
  digitalWrite(Line_4_Green, LOW);
  digitalWrite(Line_4_Red, LOW);
  digitalWrite(Line_4_Blue, HIGH);
}

void book_5_Green() {
  digitalWrite(Line_5_Green, HIGH);
  digitalWrite(Line_5_Red, LOW);
  digitalWrite(Line_5_Blue, LOW);
}
void book_5_Red() {
  digitalWrite(Line_5_Green, LOW);
  digitalWrite(Line_5_Red, HIGH);
  digitalWrite(Line_5_Blue, LOW);
}
void book_5_Blue() {
  digitalWrite(Line_5_Green, LOW);
  digitalWrite(Line_5_Red, LOW);
  digitalWrite(Line_5_Blue, HIGH);
}

void book_6_Green() {
  digitalWrite(Line_6_Green, HIGH);
  digitalWrite(Line_6_Red, LOW);
  digitalWrite(Line_6_Blue, LOW);
}
void book_6_Red() {
  digitalWrite(Line_6_Green, LOW);
  digitalWrite(Line_6_Red, HIGH);
  digitalWrite(Line_6_Blue, LOW);
}
void book_6_Blue() {
  digitalWrite(Line_6_Green, LOW);
  digitalWrite(Line_6_Red, LOW);
  digitalWrite(Line_6_Blue, HIGH);
}

void book_7_Green() {
  digitalWrite(Line_7_Green, HIGH);
  digitalWrite(Line_7_Red, LOW);
  digitalWrite(Line_7_Blue, LOW);
}
void book_7_Red() {
  digitalWrite(Line_7_Green, LOW);
  digitalWrite(Line_7_Red, HIGH);
  digitalWrite(Line_7_Blue, LOW);
}
void book_7_Blue() {
  digitalWrite(Line_7_Green, LOW);
  digitalWrite(Line_7_Red, LOW);
  digitalWrite(Line_7_Blue, HIGH);
}

void book_8_Green() {
  digitalWrite(Line_8_Green, HIGH);
  digitalWrite(Line_8_Red, LOW);
  digitalWrite(Line_8_Blue, LOW);
}
void book_8_Red() {
  digitalWrite(Line_8_Green, LOW);
  digitalWrite(Line_8_Red, HIGH);
  digitalWrite(Line_8_Blue, LOW);
}
void book_8_Blue() {
  digitalWrite(Line_8_Green, LOW);
  digitalWrite(Line_8_Red, LOW);
  digitalWrite(Line_8_Blue, HIGH);
}

void book_9_Green() {
  digitalWrite(Line_9_Green, HIGH);
  digitalWrite(Line_9_Red, LOW);
  digitalWrite(Line_9_Blue, LOW);
}
void book_9_Red() {
  digitalWrite(Line_9_Green, LOW);
  digitalWrite(Line_9_Red, HIGH);
  digitalWrite(Line_9_Blue, LOW);
}
void book_9_Blue() {
  digitalWrite(Line_9_Green, LOW);
  digitalWrite(Line_9_Red, LOW);
  digitalWrite(Line_9_Blue, HIGH);
}