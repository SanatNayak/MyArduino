#include <Keypad.h>
#include <LiquidCrystal_I2C.h>



#define buzzer 10
#define output 11
#define Password_Lenght 10 // Give enough room for six chars + NULL char

int pos = 0;    // variable to store the servo position

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "7430*6192";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
bool door = true;

byte rowPins[ROWS] = {2,3,4,5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad

void setup()
{
digitalWrite(output,HIGH);
pinMode(buzzer,OUTPUT);
pinMode(output,OUTPUT);
lcd.init();
lcd.backlight();
lcd.begin(16, 2);
  lcd.print("    Wellcome");
  lcd.setCursor(0, 1);
  lcd.print("Smart Door Lock");
  delay(2000);
  lcd.clear();

}

void loop()
{
  if (door == 0)
  {
    customKey = customKeypad.getKey();

    if (customKey == '#')

    {
      lcd.clear();
digitalWrite(output,HIGH);  
lcd.print("Door is close");
      delay(2000);
      door = 1;
    }
  }

  else Open();
}

void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}
void Open()
{
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");
  
  customKey = customKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    lcd.setCursor(data_count, 1); // move cursor to show each new char
    lcd.print(Data[data_count]); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
    if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
    {
      lcd.clear();
digitalWrite(output,LOW);     
lcd.print("Door is Open");
      door = 0;
    }
    else
    {
      lcd.clear();
      lcd.print("Wrong Password");
      delay(1000);
      door = 1;
      digitalWrite(buzzer,HIGH);
      delay(800);
      digitalWrite(buzzer,LOW);
      delay(800);
      digitalWrite(buzzer,HIGH);
      delay(800);
      digitalWrite(buzzer,LOW);
      delay(800);
      digitalWrite(buzzer,HIGH);
      delay(800);
      digitalWrite(buzzer,LOW);
      delay(800);
    }
    clearData();
  }
  \\Create By Sanat
}
