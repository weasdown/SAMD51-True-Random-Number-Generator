void setup() {
  Serial.begin(115200);
  while(!Serial);
  
  Serial.print("Current TRNG DATA: ");
  Serial.println(TRNG->DATA.reg);

  MCLK->APBCMASK.bit.TRNG_ = 1; // Enable Main Clock (MCLK) for TRNG

  TRNG_enable();

  TRNG_interrupt_enable();
  
  Serial.println(""); // Add a blank line in serial monitor for clarity of reading

  TRNG_print();

  delay(10);

  TRNG_print();


  MCLK->APBCMASK.bit.TRNG_ = 0; // Disable Main Clock (MCLK) for TRNG
  Serial.println(""); // Add a blank line in serial monitor for clarity of reading
  Serial.println("TRNG clock disabled");
  Serial.println(""); // Add a blank line in serial monitor for clarity of reading

  TRNG_print();

  delay(100);

  TRNG_print();
}

void loop() {

}

void TRNG_enable(){
  Serial.println("Setting CTRLA ENABLE");
  TRNG->CTRLA.bit.ENABLE = 1;
  Serial.print("CTRLA ENABLE: ");
  Serial.println(TRNG->CTRLA.bit.ENABLE);
}

void TRNG_interrupt_enable(){
  Serial.println("Enabling TRNG DATARDY interrupt");
  TRNG->INTENSET.bit.DATARDY = 1;
  Serial.print("INTENSET DATARDY: ");
  Serial.println(TRNG->INTENSET.bit.DATARDY);
}

void TRNG_print(){
  Serial.print("TRNG DATA new: ");
  int rand_num = TRNG->DATA.reg;
  if (rand_num==0){
    Serial.println("TRNG not correctly setup!");
  }
  Serial.println(rand_num, HEX);
}
