/*
  # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #                                                                #
  #                 Installation :                          #
  # Arduino Uno                1.3 inch Oled display        #
  #    A5          <---------->      SDA                    #
  #    A4          <---------->      SCK                    #
  #    GND         <---------->      GND                    #
  #   3V/3V3       <---------->      VDO                    #
    ----------------------------------------------------
  # Arduino Uno              5x4 Keypad from right          #
  #     2          <---------->      R1                     #
  #     3          <---------->      R2                     #
  #     4          <---------->      R3                     #     
  #     5          <---------->      R4                     #
  #     6          <---------->      R5                     #
  #     7          <---------->      C1                     #  
  #     8          <---------->      C2                     #
  #     9          <---------->      C3                     #
  #     10         <---------->      C4                     #     
  # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
*/

//Including the libraries
#include <Keypad.h>
#include "U8glib.h"

const byte ROWS = 5; //Four rows of Keypad
const byte COLS = 4; //Four columns of Keypad

//Define the symbols on the buttons of the keypad
char Keys[ROWS][COLS] = {

  {'A', 'B', '#', '*'},
  {'1', '2', '3', 'U'},
  {'4', '5', '6', 'D'},
  {'7', '8', '9', 'C'},
  {'L', '0', 'R', 'E'}

};

//input the pins the keypad are connected to
byte rowPins[ROWS] = {2, 3, 4, 5, 6};
byte colPins[COLS] = {10, 9, 8, 7};
Keypad myKeypad = Keypad(makeKeymap(Keys), rowPins, colPins, ROWS, COLS);

//used to set up the oled display
U8GLIB_SH1106_128X64 oled(U8G_I2C_OPT_NONE);

void setup() {
  Serial.begin(9600);
  Serial.print("Started the system!");
  Serial.println(" ");

  //show an initial message on the oled upon startup
  oled.firstPage();
  do{
    oled.setFont(u8g_font_profont11);
    oled.setPrintPos(0, 10);
    oled.print("GROUP A PROJECT");
    oled.setPrintPos(0, 25);
    oled.print("A decimal-binary");
    oled.setPrintPos(0, 40);
    oled.print("and binary-decimal");
    oled.setPrintPos(0, 55);
    oled.print("conversion system.");
   }while(oled.nextPage());
}

void loop() {
  char key = myKeypad.getKey();
  if (key != NO_KEY) {
    if (key == 'A') {
      decimalToBinary();
    } else if (key == 'B') {
       binaryToDecimal();
    } else{
       Serial.print("View options to select");
       Serial.println(" ");
  
       oled.firstPage();
       homeDisplay();
    }
  }
}

void decimalToBinary(){
  Serial.print("Entered the decimal to binary conversion");
  Serial.println(" ");
  
  String decimalNum;
  long decimalNumber;
  long binaryNumber;
  String stringBinary = "";

  while(true){
    oled.firstPage();
    
    char key = myKeypad.getKey();
    if(key != NO_KEY){
      if (key == 'E'){
        //jump out of loop when left button is selected
        Serial.print("Jumped out of the dec2Bin convertion");
        Serial.println(" ");

        homeDisplay();
        
        break;
      }else if (key != 'A' and key != 'B' and key != '#' and key != '*' and key != 'L' and key != 'R' and key != 'U' and key != 'D' and key != 'C' and key != 'E') {
          decimalNum = decimalNum + String(key);
          decimalNumber = decimalNum.toInt();
          
          if (decimalNumber <= 1023) {
            //Converts Decimal to Binary
            binaryNumber = convertDecimalToBinary(decimalNumber);
            stringBinary = String(binaryNumber);

            //Prints the Binary and the Decimal numbers on the OLED Display
            do{
              oled.setPrintPos(0, 10);
              oled.print("D:");
              oled.println(decimalNumber);
              oled.setPrintPos(0, 25);
              oled.print("B:");
              oled.println(binaryNumber);
              oled.setPrintPos(0, 55);
              oled.print("Ent to Main Menu");
            }while(oled.nextPage());
          
            //Prints the Decimal number on the Serial Monitor
            Serial.print("Decimal: ");
            Serial.print(decimalNumber);
            Serial.print("      ");

            //Prints the Binary number on the Serial Monitor
            Serial.print("Binary: ");
            Serial.println(binaryNumber);
          }else {
            do{
              oled.setFont(u8g_font_profont11);
              oled.setPrintPos(0, 10);
              oled.print("Max decimal value is: ");
              oled.setPrintPos(0, 25);
              oled.print("1023");
              oled.setPrintPos(0, 55);
              oled.print("Press Esc key!!");
            }while(oled.nextPage());

            Serial.println("Max decimal value = 1023");
            delay(1000);
          }
      } else if (key == 'C') {
        //Clears the numbers
          decimalNum = "";
          decimalNumber = 0;
          
          do{
            oled.setPrintPos(0, 10);
            oled.print("D:");
            oled.println('0');
            oled.setPrintPos(0, 25);
            oled.print("B:");
            oled.println('0');
            oled.setPrintPos(0, 55);
            oled.print("Ent to Main Menu");
          }while(oled.nextPage());
      }
    }
  }
}

void binaryToDecimal() {
  Serial.print("Entered the binary to decimal conversion");
  Serial.println(" ");
  
  String binNum;
  long binNumber;
  long decNumber;
  String stringDecimal = "";

  while(true){
    oled.firstPage();
    
    char key = myKeypad.getKey();
    if(key != NO_KEY){
      if (key == 'E'){
        //jump out of loop when left button is selected
        Serial.print("Jumped out of the Binary to decimal convertion");
        Serial.println(" ");

        homeDisplay();
        
        break;
      }else if (key != 'A' and key != 'B' and key != '#' and key != '*' and key != 'L' and key != 'R' and key != 'U' and key != 'D' and key != 'C' and key != 'E') {
          binNum = binNum + String(key);
          binNumber = binNum.toInt();
          
          if (isBinary(binNumber)) {
            //Converts Decimal to Binary
            decNumber = convertBinaryToDecimal(binNumber);
            stringDecimal = decNumber;

            //Prints the Binary and the Decimal numbers on the OLED Display
            do{
              oled.setPrintPos(0, 10);
              oled.print("D:");
              oled.println(binNumber);
              oled.setPrintPos(0, 25);
              oled.print("B:");
              oled.println(decNumber);
              oled.setPrintPos(0, 55);
              oled.print("Ent to Main Menu");
            }while(oled.nextPage());
          
            //Prints the Binary Input number on the Serial Monitor
            Serial.print("Binary: ");
            Serial.print(binNumber);
            Serial.print("      ");

            //Prints the Decimal output number on the Serial Monitor
            Serial.print("Decimal: ");
            Serial.println(decNumber);
          }else {
            do{
              oled.setFont(u8g_font_profont11);
              oled.setPrintPos(0, 10);
              oled.print(binNum);
              oled.print(" is not binary");
              oled.setPrintPos(0, 55);
              oled.print("Press Esc key!!");
            }while(oled.nextPage());

            Serial.println("Max decimal value = 1023");
            delay(1000);
          }
      } else if (key == 'C') {
        //Clears the numbers
          binNum = "";
          binNumber = 0;
          
          do{
            oled.setPrintPos(0, 10);
            oled.print("B:");
            oled.println('0');
            oled.setPrintPos(0, 25);
            oled.print("D:");
            oled.println('0');
            oled.setPrintPos(0, 55);
            oled.print("Ent to Main Menu");
          }while(oled.nextPage());
      }
    }
  }
}

//This is display in home screen of oled
void homeDisplay(){
   do{
      oled.setFont(u8g_font_profont11);
      oled.setPrintPos(0, 10);
      oled.print("Select either");
      oled.setPrintPos(0, 25);
      oled.print("F1: Decimal-Binary");
      oled.setPrintPos(0, 40);
      oled.print("OR");
      oled.setPrintPos(0, 55);
      oled.print("F2: Binary-Decimal");
    }while(oled.nextPage());
}


//This function converts a Decimal number to Binary number
long convertDecimalToBinary(int number) {
  int reminder;
  String bin;

  while (number) {
    reminder = number % 2;
    number = number / 2;
    bin = String(reminder) + bin;
  }
  
  return bin.toInt();
}

bool isBinary(long number){
  String str = String(number);
  for(int i=0; i<str.length(); i++){
    if(str[i] != '1' && str[i] != '0')
      return false;
  }
  return true;
}

//This function converts a Binary number to Deciman number
int convertBinaryToDecimal(long number){
  int decimal = 0;
  int base = 1;

  while (number > 0){
      int lastDigit = number % 10;
      number = number/10;
      decimal += lastDigit*base;
      base = base*2;
  }

  return decimal;
}
