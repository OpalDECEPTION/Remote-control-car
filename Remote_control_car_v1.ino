#include <RH_RF69.h>

#define RF69_FREQ 915.0

#define RFM69_RST 2
#define RFM69_INT 3
#define RFM69_CS 4
#define BUTTON_A 5
#define BUTTON_B 6
#define BUTTON_C 7
#define BUTTON_D 8

RH_RF69 rf69(RFM69_CS, RFM69_INT);

int16_t packetnum = 0; 

void setup() {
  Serial.begin(115200);


  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);

  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    while (1)
      ;
  }
  Serial.println("RFM69 radio init OK!");
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  rf69.setTxPower(20, true);  

  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  rf69.setEncryptionKey(key);

  Serial.print("RFM69 radio @");
  Serial.print((int)RF69_FREQ);
  Serial.println(" MHz");
}

void loop() {

  int F = digitalRead(5);
  int B = digitalRead(6);
  int CW = digitalRead(7);
  int CCW = digitalRead(8);

  if ((F == 1) or (B == 1) or (CW == 1) or (CCW == 1)) {
    Serial.println("Button pressed!");

    char radiopacket[20] = "  ";
    if (F == 1) radiopacket[1] = 'F';
    if (B == 1) radiopacket[1] = 'B';
    if (CW == 1) radiopacket[1] = 'R';
    if (CCW == 1) radiopacket[1] = 'L';

    Serial.print("Sending ");
    Serial.println(radiopacket);

    rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
    rf69.waitPacketSent();

  } else {

    char radiopacket[20] = "  ";
    radiopacket[1] = 'X';

    rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
    rf69.waitPacketSent();
  }
}
