// include the library code:
#include <LiquidCrystal.h>

float temp;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // change reference to internal for temp sensor
  analogReference(INTERNAL);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temperature:");
}

void loop() {
  temp = (1.1 * analogRead(A0) * 100.0) / 1024;
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  String units = " C";
  String output = temp + units;
  lcd.print(output);
  
  delay(1000);
}

