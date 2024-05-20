#include <SPI.h>
#include <Wire.h>
#include <RFID.h>
#include <LiquidCrystal_I2C.h>

int Buzzer = 17;
int k = 0;
int j = 0;
int l = 0;
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

int Tracker_1 = 0;
int Tracker_2 = 0;
int Tracker_3 = 0;
int Tracker_4 = 0;
int Tracker_5 = 0;
int Tracker_6 = 0;
int Tracker_7 = 0;
int Tracker_8 = 0;
int Tracker_9 = 0;

uint32_t tagID = 0;
#define SDA_DIO 9
#define RESET_DIO 8

enum State {
  IDLE,
  WAIT_TAG,
  TAG_ID,
  BOOK_1,
  BOOK_2,
  BOOK_3,
  READ_DATA,
  READ_DATA_1,
  READ_DATA_2,
  CHECK_BOOK
};

State currentState = WAIT_TAG;

RFID RC522(SDA_DIO, RESET_DIO);

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  SPI.begin();
  RC522.init();

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
  digitalWrite(Line_6_Blue, HIGH);

  digitalWrite(Line_7_Green, LOW);
  digitalWrite(Line_7_Red, LOW);
  digitalWrite(Line_7_Blue, LOW);

  digitalWrite(Line_8_Green, LOW);
  digitalWrite(Line_8_Red, LOW);
  digitalWrite(Line_8_Blue, LOW);

  digitalWrite(Line_9_Green, LOW);
  digitalWrite(Line_9_Red, LOW);
  digitalWrite(Line_9_Blue, LOW);


  pinMode(Physics_1, INPUT);
  pinMode(Physics_2, INPUT);
  pinMode(Physics_3, INPUT);

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
  check_book_status();
  switch (currentState) {
    case WAIT_TAG:
      wait_tag();
      break;
    case IDLE:
      idle();
      break;
    case TAG_ID:
      tag_id();
      break;
    case READ_DATA:
      ReadData();
      break;
    case READ_DATA_1:
      ReadData_1();
      break;
    case READ_DATA_2:
      ReadData_2();
      break;
    case CHECK_BOOK:
      check_book();
      break;
  }
}
String mergeData(String data) {
  String mergedData = "";

  int physicsIndex = data.indexOf("Physics: ");
  int engineeringIndex = data.indexOf("Engineering: ");
  int mathematicsIndex = data.indexOf("Mathematics: ");

  if (physicsIndex != -1 && engineeringIndex != -1 && mathematicsIndex != -1) {
    String physicsData = data.substring(physicsIndex + 9, physicsIndex + 14);
    String engineeringData = data.substring(engineeringIndex + 13, engineeringIndex + 18);
    String mathematicsData = data.substring(mathematicsIndex + 13, mathematicsIndex + 18);

    mergedData = physicsData + engineeringData + mathematicsData;
  }

  return mergedData;
}
void check_book() {
  if (digitalRead(Line_1_Green) == HIGH) {
    if (digitalRead(Physics_1) == LOW) {
      tunoff_book1_A();
    } else {
      digitalWrite(Line_1_Green, HIGH);
      delay(1000);
    }
  }
  if (digitalRead(Line_2_Green) == HIGH) {
    if (digitalRead(Physics_2) == LOW) {
      tunoff_book1_B();
    } else {
      digitalWrite(Line_1_Green, HIGH);
      digitalWrite(Line_2_Green, HIGH);
      delay(1000);
    }
  }
  if (digitalRead(Line_3_Green) == HIGH) {
    if (digitalRead(Physics_3) == LOW) {
      tunoff_book1_C();
    } else {
      digitalWrite(Line_1_Green, HIGH);
      digitalWrite(Line_2_Green, HIGH);
      digitalWrite(Line_3_Green, HIGH);
      delay(1000);
    }
  }
  if (digitalRead(Line_4_Red) == HIGH) {
    if (digitalRead(Engineering_1) == LOW) {
      tunoff_book2_A();
    } else {
      digitalWrite(Line_1_Red, HIGH);
      digitalWrite(Line_2_Red, HIGH);
      digitalWrite(Line_3_Red, HIGH);
      digitalWrite(Line_4_Red, HIGH);
      delay(1000);
    }
  }
  if (digitalRead(Line_5_Red) == HIGH) {
    if (digitalRead(Engineering_2) == LOW) {
      tunoff_book2_B();
    } else {
      digitalWrite(Line_1_Red, HIGH);
      digitalWrite(Line_2_Red, HIGH);
      digitalWrite(Line_3_Red, HIGH);
      digitalWrite(Line_4_Red, HIGH);
      digitalWrite(Line_5_Red, HIGH);
      delay(1000);
    }
  }
  if (digitalRead(Line_6_Red) == HIGH) {
    if (digitalRead(Engineering_3) == LOW) {
      tunoff_book2_C();
    } else {
      digitalWrite(Line_1_Red, HIGH);
      digitalWrite(Line_2_Red, HIGH);
      digitalWrite(Line_3_Red, HIGH);
      digitalWrite(Line_4_Red, HIGH);
      digitalWrite(Line_5_Red, HIGH);
      digitalWrite(Line_6_Red, HIGH);
      delay(1000);
    }
  }
  if (digitalRead(Line_7_Blue) == HIGH) {
    if (digitalRead(Mathematics_1) == LOW) {
      tunoff_book3_A();
    } else {
      digitalWrite(Line_1_Blue, HIGH);
      digitalWrite(Line_2_Blue, HIGH);
      digitalWrite(Line_3_Blue, HIGH);
      digitalWrite(Line_4_Blue, HIGH);
      digitalWrite(Line_5_Blue, HIGH);
      digitalWrite(Line_6_Blue, HIGH);
      digitalWrite(Line_7_Blue, HIGH);
      delay(1000);
    }
  }
  if (digitalRead(Line_8_Blue) == HIGH) {
    if (digitalRead(Mathematics_2) == LOW) {
      tunoff_book3_B();
    } else {
      digitalWrite(Line_1_Blue, HIGH);
      digitalWrite(Line_2_Blue, HIGH);
      digitalWrite(Line_3_Blue, HIGH);
      digitalWrite(Line_4_Blue, HIGH);
      digitalWrite(Line_5_Blue, HIGH);
      digitalWrite(Line_6_Blue, HIGH);
      digitalWrite(Line_7_Blue, HIGH);
      digitalWrite(Line_8_Blue, HIGH);
      delay(1000);
    }
  }
  if (digitalRead(Line_9_Blue) == HIGH) {
    if (digitalRead(Mathematics_3) == LOW) {
      tunoff_book3_C();
    } else {
      digitalWrite(Line_1_Blue, HIGH);
      digitalWrite(Line_2_Blue, HIGH);
      digitalWrite(Line_3_Blue, HIGH);
      digitalWrite(Line_4_Blue, HIGH);
      digitalWrite(Line_5_Blue, HIGH);
      digitalWrite(Line_6_Blue, HIGH);
      digitalWrite(Line_7_Blue, HIGH);
      digitalWrite(Line_8_Blue, HIGH);
      digitalWrite(Line_9_Blue, HIGH);
      delay(1000);
    }
  }
  if ((digitalRead(Line_1_Green) == HIGH) && (digitalRead(Line_2_Green) == HIGH) && (digitalRead(Line_3_Green) == HIGH) && (digitalRead(Line_4_Red) == HIGH) && (digitalRead(Line_5_Red) == HIGH) && (digitalRead(Line_6_Red) == HIGH) && (digitalRead(Line_7_Blue) == HIGH) && (digitalRead(Line_8_Blue) == HIGH) && (digitalRead(Line_9_Blue) == HIGH)) {
    currentState = IDLE;
  }
}
void tunoff_book1_A() {
  digitalWrite(Line_1_Green, LOW);
}
void tunoff_book1_B() {
  digitalWrite(Line_1_Green, LOW);
  digitalWrite(Line_2_Green, LOW);
}
void tunoff_book1_C() {
  digitalWrite(Line_1_Green, LOW);
  digitalWrite(Line_2_Green, LOW);
  digitalWrite(Line_3_Green, LOW);
}
void tunoff_book2_A() {
  digitalWrite(Line_1_Red, LOW);
  digitalWrite(Line_2_Red, LOW);
  digitalWrite(Line_3_Red, LOW);
  digitalWrite(Line_4_Red, LOW);
}
void tunoff_book2_B() {
  digitalWrite(Line_1_Red, LOW);
  digitalWrite(Line_2_Red, LOW);
  digitalWrite(Line_3_Red, LOW);
  digitalWrite(Line_4_Red, LOW);
  digitalWrite(Line_5_Red, LOW);
}
void tunoff_book2_C() {
  digitalWrite(Line_1_Red, LOW);
  digitalWrite(Line_2_Red, LOW);
  digitalWrite(Line_3_Red, LOW);
  digitalWrite(Line_4_Red, LOW);
  digitalWrite(Line_5_Red, LOW);
  digitalWrite(Line_6_Red, LOW);
}
void tunoff_book3_A() {
  digitalWrite(Line_1_Blue, LOW);
  digitalWrite(Line_2_Blue, LOW);
  digitalWrite(Line_3_Blue, LOW);
  digitalWrite(Line_4_Blue, LOW);
  digitalWrite(Line_5_Blue, LOW);
  digitalWrite(Line_6_Blue, LOW);
  digitalWrite(Line_7_Blue, LOW);
}
void tunoff_book3_B() {
  digitalWrite(Line_1_Blue, LOW);
  digitalWrite(Line_2_Blue, LOW);
  digitalWrite(Line_3_Blue, LOW);
  digitalWrite(Line_4_Blue, LOW);
  digitalWrite(Line_5_Blue, LOW);
  digitalWrite(Line_6_Blue, LOW);
  digitalWrite(Line_7_Blue, LOW);
  digitalWrite(Line_8_Blue, LOW);
}
void tunoff_book3_C() {
  digitalWrite(Line_1_Blue, LOW);
  digitalWrite(Line_2_Blue, LOW);
  digitalWrite(Line_3_Blue, LOW);
  digitalWrite(Line_4_Blue, LOW);
  digitalWrite(Line_5_Blue, LOW);
  digitalWrite(Line_6_Blue, LOW);
  digitalWrite(Line_7_Blue, LOW);
  digitalWrite(Line_8_Blue, LOW);
  digitalWrite(Line_9_Blue, LOW);
}
void idle() {
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
  digitalWrite(Line_6_Blue, HIGH);

  digitalWrite(Line_7_Green, LOW);
  digitalWrite(Line_7_Red, LOW);
  digitalWrite(Line_7_Blue, LOW);

  digitalWrite(Line_8_Green, LOW);
  digitalWrite(Line_8_Red, LOW);
  digitalWrite(Line_8_Blue, LOW);

  digitalWrite(Line_9_Green, LOW);
  digitalWrite(Line_9_Red, LOW);
  digitalWrite(Line_9_Blue, LOW);

  currentState = WAIT_TAG;
}
void ReadData() {
  if (Serial3.available()) {
    String receivedData = Serial3.readStringUntil('\n');
    Serial.println(receivedData);

    // Merge data into a single string
    String mergedData = mergeData(receivedData);
    Serial.println("Merged Data: " + mergedData);

    // Find the indices of the first three occurrences of '1'
    findFirstThreeOnes_1(mergedData);
  }
}
void ReadData_1() {
  if (Serial3.available()) {
    String receivedData = Serial3.readStringUntil('\n');
    Serial.println(receivedData);

    // Merge data into a single string
    String mergedData = mergeData(receivedData);
    Serial.println("Merged Data: " + mergedData);

    // Find the indices of the first three occurrences of '1'
    findFirstThreeOnes_1(mergedData);
  }
}
void ReadData_2() {
  if (Serial3.available()) {
    String receivedData = Serial3.readStringUntil('\n');
    Serial.println(receivedData);

    // Merge data into a single string
    String mergedData = mergeData(receivedData);
    Serial.println("Merged Data: " + mergedData);

    // Find the indices of the first three occurrences of '1'
    findFirstThreeOnes_2(mergedData);
  }
}
void findFirstThreeOnes_1(String data) {
  int count = 0;
  for (k = 0; k < data.length(); k++) {
    if (data.charAt(k) == '1') {
      Serial.print("Index of '1' #");
      Serial.print(count + 1);
      Serial.print(": ");
      Serial.println(k);
      if (k == 0) {
        physics_1();
      }
      if (k == 1) {
        physics_2();
      }
      if (k == 2) {
        physics_2();
      }
      // if (k == 5) {
      //   engineering_1();
      // }
      // if (k == 6) {
      //   engineering_2();
      // }
      // if (k == 7) {
      //   engineering_3();
      // }
      // if (k == 10) {
      //   mathematics_1();
      // }
      // if (k == 11) {
      //   mathematics_2();
      // }
      // if (k == 12) {
      //   mathematics_3();
      // }
      count++;
      if (count == 3) break;
      lcd.clear();
      lcd.setCursor(7, 1);
      lcd.print("FOLLOW");
      lcd.setCursor(6, 2);
      lcd.print("THE LEDs");
      delay(2000);
      currentState = CHECK_BOOK;
    }
  }

  if (count < 3) {
    Serial.println("Less than 3 occurrences of '1' found.");
  }
}
void findFirstThreeOnes_2(String data) {
  int count = 0;
  for (j = 0; j < data.length(); j++) {
    if (data.charAt(j) == '1') {
      Serial.print("Index of '1' #");
      Serial.print(count + 1);
      Serial.print(": ");
      Serial.println(j);
      if (j == 0) {
        physics_1();
      }
      if (j == 1) {
        physics_2();
      }
      if (j == 2) {
        physics_2();
      }
      // if (j == 5) {
      //   engineering_1();
      // }
      // if (j == 6) {
      //   engineering_2();
      // }
      // if (j == 7) {
      //   engineering_3();
      // }
      // if (j == 10) {
      //   mathematics_1();
      // }
      // if (j == 11) {
      //   mathematics_2();
      // }
      // if (j == 12) {
      //   mathematics_3();
      // }
      count++;
      if (count == 3) break;
      lcd.clear();
      lcd.setCursor(7, 1);
      lcd.print("FOLLOW");
      lcd.setCursor(6, 2);
      lcd.print("THE LEDs");
      delay(2000);
      currentState = CHECK_BOOK;
    }
  }

  if (count < 3) {
    Serial.println("Less than 3 occurrences of '1' found.");
  }
}
void findFirstThreeOnes_3(String data) {
  int count = 0;
  for (l = 0; l < data.length(); l++) {
    if (data.charAt(l) == '1') {
      Serial.print("Index of '1' #");
      Serial.print(count + 1);
      Serial.print(": ");
      Serial.println(l);
      if (l == 0) {
        physics_1();
      }
      if (l == 1) {
        physics_2();
      }
      if (l == 2) {
        physics_2();
      }
      // if (l == 5) {
      //   engineering_1();
      // }
      // if (l == 6) {
      //   engineering_2();
      // }
      // if (l == 7) {
      //   engineering_3();
      // }
      // if (l == 10) {
      //   mathematics_1();
      // }
      // if (l == 11) {
      //   mathematics_2();
      // }
      // if (l == 12) {
      //   mathematics_3();
      // }
      count++;
      if (count == 3) break;
      lcd.clear();
      lcd.setCursor(7, 1);
      lcd.print("FOLLOW");
      lcd.setCursor(6, 2);
      lcd.print("THE LEDs");
      delay(2000);
      currentState = CHECK_BOOK;
    }
  }

  if (count < 3) {
    Serial.println("Less than 3 occurrences of '1' found.");
  }
}
void check_book_status() {
  if (digitalRead(Physics_1) == HIGH) {
    //Serial.println("Physics_1 is Available");
    Tracker_1 = 1;
  } else if (digitalRead(Physics_1) == LOW) {
    //Serial.println("Physics_1 is Not Available");
    Tracker_1 = 0;
  }
  if (digitalRead(Physics_2) == HIGH) {
    //Serial.println("Physics_2 is Available");
    Tracker_2 = 1;
  } else if (digitalRead(Physics_2) == LOW) {
    //Serial.println("Physics_2 is Not Available");
    Tracker_2 = 0;
  }
  if (digitalRead(Physics_3) == HIGH) {
    //Serial.println("Physics_3 is Available");
    Tracker_3 = 1;
  } else if (digitalRead(Physics_3) == LOW) {
    //Serial.println("Physics_3 is Not Available");
    Tracker_3 = 0;
  }
  if (digitalRead(Engineering_1) == HIGH) {
    //Serial.println("Engineering_1 is Available");
    Tracker_4 = 1;
  } else if (digitalRead(Engineering_1) == LOW) {
    //Serial.println("Engineering_1 is Not Available");
    Tracker_4 = 0;
  }
  if (digitalRead(Engineering_2) == HIGH) {
    //Serial.println("Engineering_2 is Available");
    Tracker_5 = 1;
  } else if (digitalRead(Engineering_2) == LOW) {
    //Serial.println("Engineering_2 is Not Available");
    Tracker_5 = 0;
  }
  if (digitalRead(Engineering_3) == HIGH) {
    //Serial.println("Engineering_3 is Available");
    Tracker_6 = 1;
  } else if (digitalRead(Engineering_3) == LOW) {
    //Serial.println("Engineering_3 is Not Available");
    Tracker_6 = 0;
  }
  if (digitalRead(Mathematics_1) == HIGH) {
    //Serial.println("Mathematics_1 is Available");
    Tracker_7 = 1;
  } else if (digitalRead(Mathematics_1) == LOW) {
    //Serial.println("Mathematics_1 is Not Available");
    Tracker_7 = 0;
  }
  if (digitalRead(Mathematics_2) == HIGH) {
    //Serial.println("Mathematics_2 is Available");
    Tracker_8 = 1;
  } else if (digitalRead(Mathematics_2) == LOW) {
    //Serial.println("Mathematics_2 is Not Available");
    Tracker_8 = 0;
  }
  if (digitalRead(Mathematics_3) == HIGH) {
    //Serial.println("Mathematics_3 is Available");
    Tracker_9 = 1;
  } else if (digitalRead(Mathematics_3) == LOW) {
    //Serial.println("Mathematics_3 is Not Available");
    Tracker_9 = 0;
  }
  Serial3.print("Tracker _1: ");
  Serial3.println(Tracker_1);
  Serial3.print("Tracker _2: ");
  Serial3.println(Tracker_2);
  Serial3.print("Tracker _3: ");
  Serial3.println(Tracker_3);
  Serial3.print("Tracker _4: ");
  Serial3.println(Tracker_4);
  Serial3.print("Tracker _5: ");
  Serial3.println(Tracker_5);
  Serial3.print("Tracker _6: ");
  Serial3.println(Tracker_6);
  Serial3.print("Tracker _7: ");
  Serial3.println(Tracker_7);
  Serial3.print("Tracker _8: ");
  Serial3.println(Tracker_8);
  Serial3.print("Tracker _9: ");
  Serial3.println(Tracker_9);
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
    // lcd.clear();
    // lcd.setCursor(0, 1);
    // lcd.print(tagID);
    if (tagID == "211171111163180") {
      Serial3.print("A");
      Serial.println("Data sent: A");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NAME: DERRICK KAMAU");
      lcd.setCursor(0, 1);
      lcd.print("ADM: BTCES/2020/74429");
      delay(5000);
      currentState = READ_DATA_2;
    } else if (tagID == "147217126163151") {
      Serial3.print("B");
      Serial.println("Data sent: B");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NAME: LINAH ALMASI");
      lcd.setCursor(0, 1);
      lcd.print("ADM: BTCES/2020/67428");
      delay(5000);
      currentState = READ_DATA_1;
    } else if (tagID == "14717421426241") {
      Serial3.print("C");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NAME: KHERI KISIA");
      lcd.setCursor(0, 1);
      lcd.print("ADM: BTCES/2020/97824");
      delay(5000);
      currentState = READ_DATA;
      Serial.println("Data sent: C");
      delay(3000);
    }
    delay(500);
  }
}
void physics_1() {
  book_1_Green();
}
void physics_2() {
  book_1_Green();
  book_2_Green();
}
void physics_3() {
  book_1_Green();
  book_2_Green();
  book_3_Green();
}
void engineering_1() {
  book_1_Red();
  book_2_Red();
  book_3_Red();
  book_4_Red();
}
void engineering_2() {
  book_1_Red();
  book_2_Red();
  book_3_Red();
  book_4_Red();
  book_5_Red();
}
void engineering_3() {
  book_1_Red();
  book_2_Red();
  book_3_Red();
  book_4_Red();
  book_5_Red();
  book_6_Red();
}
void mathematics_1() {
  book_1_Blue();
  book_2_Blue();
  book_3_Blue();
  book_4_Blue();
  book_5_Blue();
  book_6_Blue();
  book_7_Blue();
}
void mathematics_2() {
  book_1_Blue();
  book_2_Blue();
  book_3_Blue();
  book_4_Blue();
  book_5_Blue();
  book_6_Blue();
  book_7_Blue();
  book_8_Blue();
}
void mathematics_3() {
  book_1_Blue();
  book_2_Blue();
  book_3_Blue();
  book_4_Blue();
  book_5_Blue();
  book_6_Blue();
  book_7_Blue();
  book_8_Blue();
  book_9_Blue();
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