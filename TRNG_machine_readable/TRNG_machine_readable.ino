int rand_num;

void setup() {
  Serial.begin(2000000); // Open serial port with baud of 2Mbps
  while(!Serial);

  MCLK->APBCMASK.bit.TRNG_ = 1; // Enable Main Clock (MCLK) for TRNG

  TRNG->CTRLA.bit.ENABLE = 1; // Enable TRNG
  TRNG->INTENSET.bit.DATARDY = 1; // Enable TRNG interrupt when data ready
  delay(10); // Short delay to allow generation of new random number
}

void loop() {
  rand_num = TRNG->DATA.reg; // Read random number
  if (rand_num==0){ // Data register is zero by default
    Serial.println("TRNG not correctly setup!");
  }
  Serial.println(rand_num, BIN); // Output the number as binary over USB
  delayMicroseconds(200); // wait 200 microseconds to allow PC to catch up
}
