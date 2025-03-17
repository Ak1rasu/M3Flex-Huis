void setup() { 
// Set pin D3 on the NodeMCU as an 
// output pin so it can send voltages 
pinMode (D6, OUTPUT); 
} 
void loop() { 
// set a voltage on D3 
digitalWrite(D6, HIGH); 
// wait a second 
delay(1000); 
// remove voltage from D3 
digitalWrite(D6, LOW); 
// wait 2 seconds 
delay (2000); 
}
