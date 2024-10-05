#define IR_1 3
#define IR_2 4
#define LED_R_1 5
#define LED_G_1 6
#define LED_R_2 7
#define LED_G_2 8
void setup() {
Serial.begin(115200);
// Initialize pins for IR Sensors
  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  // Initialize pins for LEDs
  pinMode(LED_R_1, OUTPUT);
  pinMode(LED_R_2, OUTPUT);
  pinMode(LED_G_1, OUTPUT);
  pinMode(LED_G_2, OUTPUT);

  // Turn off LEDs at start
  digitalWrite(LED_R_1, LOW);
  digitalWrite(LED_R_2, LOW);
  digitalWrite(LED_G_1, HIGH);
  digitalWrite(LED_G_2, HIGH);

}

void loop() {
   int IR_1_Value = digitalRead(IR_1);
  int IR_2_Value = digitalRead(IR_2);

  // Check if a vehicle is detected on one side and control LEDs accordingly
  if (IR_1_Value == 0) {
    // Vehicle detected on side 1, turn on LED 2 (stop light for side 2)
    digitalWrite(LED_R_2, HIGH);
    digitalWrite(LED_G_2, LOW);
    delay(3000);
    
  } else {
    // No vehicle detected on side 1, turn off LED 2
    digitalWrite(LED_R_2, LOW);
    digitalWrite(LED_G_2, HIGH);
    
  }

  if (IR_2_Value == 0) {
    // Vehicle detected on side 2, turn on LED 1 (stop light for side 1)
    digitalWrite(LED_R_1, HIGH);
    digitalWrite(LED_G_1, LOW);
     delay(3000);
    
  } else {
    // No vehicle detected on side 2, turn off LED 1
    digitalWrite(LED_R_1, LOW);
    digitalWrite(LED_G_1, HIGH);
   
  }

  


}
