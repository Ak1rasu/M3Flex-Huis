#include <ArduinoJson.h>

// Pin voor de LDR en de lampjes
const int LDRPin = A0;   // Analoge pin voor de LDR
const int lampPin1 = D5;   // Digitale pin voor lamp 1
const int lampPin2 = D3;   // Digitale pin voor lamp 2

// Functie om te bepalen of het weinig licht is
bool isLowLight(int LDRValue) {
  if (LDRValue < 500) {
    return true;  // Weinig licht
  } else {
    return false;  // Veel licht
  }
}

// Functie om lampjes aan te zetten op basis van LDR-waarde
void controlLampjes(int LDRValue) {
  if (LDRValue < 500) {
    digitalWrite(lampPin1, HIGH);  // Zet lamp op D5 aan bij weinig licht
  } else {
    digitalWrite(lampPin1, LOW);   // Zet lamp op D5 uit bij veel licht
  }

  // Zet D3 aan als LDR waarde tussen 500 en 700
  if (LDRValue >= 500 && LDRValue < 700) {
    digitalWrite(lampPin2, HIGH);  // Zet lamp op D3 aan
  } else {
    digitalWrite(lampPin2, LOW);   // Zet lamp op D3 uit
  }
}

void setup() {
  Serial.begin(9600);  // Serial communicatie starten

  // Zet de pinnen voor de lampjes als OUTPUT
  pinMode(lampPin1, OUTPUT);
  pinMode(lampPin2, OUTPUT);
}

void loop() {
  // Lees de waarde van de LDR (tussen 0 en 1023)
  int LDRValue = analogRead(LDRPin);
  
  // Maak een JSON-document aan
  StaticJsonDocument<200> doc;
  doc["LDRValue"] = LDRValue;
  
  // Print het JSON-document naar de Serial Monitor
  serializeJson(doc, Serial);
  Serial.println();
  
  // Controleer of de LDR-waarde onder de 500 is
  if (LDRValue < 500) {
    // Lampjes knipperen met een willekeurige snelheid tussen 100 en 500 milliseconden
    int blinkDelay = random(100, 501); // Willekeurige vertraging tussen 100 en 500 milliseconden
    
    digitalWrite(lampPin1, HIGH);  // Zet lamp 1 aan
    digitalWrite(lampPin2, HIGH);  // Zet lamp 2 aan
    delay(blinkDelay);             // Wacht een willekeurige tijd
    digitalWrite(lampPin1, LOW);   // Zet lamp 1 uit
    digitalWrite(lampPin2, LOW);   // Zet lamp 2 uit
    delay(blinkDelay);             // Wacht weer een willekeurige tijd
  }

  // Roep de functie aan om de lampjes te controleren
  controlLampjes(LDRValue);

  // Print of het weinig licht is of niet
  if (isLowLight(LDRValue)) {
    Serial.println("Weinig licht");
  } else {
    Serial.println("Veel licht");
  }

  delay(500);  // Wacht 500 ms (1 keer per seconde)
}
