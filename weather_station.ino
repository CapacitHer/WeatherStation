/*
Lucky Cat
 /\_/\  
( ^_^ ) 
 > ~ <
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 0, 1, 2, 3, 4, 5, 6, 7);

const int thermistorPin = A0;
const int photoresistorPin = A1;
const float BETA = 3950; 
const float R0 = 10000;  

void setup() {
    lcd.begin(16, 2);
    lcd.clear();
}

void loop() {
    // Scroll welcome message 
    String welcomeMessage = " Welcome to the Mini Weather Station ";
    for (int i = 0; i < welcomeMessage.length() - 15; i++) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(welcomeMessage.substring(i, i + 16));
        delay(600); // scrolling pace
    }

    // Read thermistor value
    int rawTemp = analogRead(thermistorPin);
    float resistance = (1023.0 / rawTemp - 1.0) * R0;
    float temperatureC = 1.0 / (log(resistance / R0) / BETA + 1.0 / 298.15) - 273.15;
    
    // Convert to Farenheit 
    float temperatureF = (temperatureC * 1.8) + 32;

    // Read photoresistor value
    int lightLevel = analogRead(photoresistorPin);

    // Determine light condition
    String lightCondition;
    if (lightLevel > 800) {
        lightCondition = "Sunny";
    } else if (lightLevel > 400) {
        lightCondition = "Shady";
    } else {
        lightCondition = "Dark";
    }

    // Display sensor readings for 5 seconds
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");    
    lcd.print(temperatureF);
    lcd.print(" F");

    lcd.setCursor(0, 1);
    lcd.print("Light: ");
    lcd.print(lightCondition);

    delay(5000); // Wait for 5 seconds before repeating
}