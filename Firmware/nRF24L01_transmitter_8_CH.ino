// 8 Channel Transmitter & Trim buttons
// V0.2 Auto ack on, retries on, throttle reset to zero, failsafe to 500 ms, channel 120

  #include <SPI.h>
  #include <nRF24L01.h>
  #include <RF24.h>
  #include <EEPROM.h>
    
  const uint64_t pipeOut = 0xABCDABCD71LL;        // Must be the same as in the receiver 
  RF24 radio(9, 10);                      // Select CE and CSN pins
  
 #define trimbut_1 1                      // Trim button 1 / Pin D1
 #define trimbut_2 2                      // Trim button 2 / Pin D2
 #define trimbut_3 3                      // Trim button 3 / Pin D3
 #define trimbut_4 4                      // Trim button 4 / Pin D4
 #define trimbut_5 5                      // Trim button 5 / Pin D5
 #define trimbut_6 6                      // Trim button 6 / Pin D6
 
 int tvalue1 = EEPROM.read(1) * 4;        // Reading trim values from Eprom
 int tvalue2 = EEPROM.read(3) * 4;        
 int tvalue3 = EEPROM.read(5) * 4;        

  struct Signal {
  byte throttle;
  byte pitch;
  byte roll;
  byte yaw;
  byte aux1;
  byte aux2;
  byte aux3;
  byte aux4;  
};

  Signal data;
  void ResetData() 
{
  // Signal lost position
  data.throttle = 0; // from 512 to 0, now on 10kpot                   
  data.pitch = 127;
  data.roll = 127;
  data.yaw = 127;
  data.aux1 = 0;                         
  data.aux2 = 0;
  data.aux3 = 0;
  data.aux4 = 0;
}
  void setup()
{
  // Configure the NRF24 module
  
  radio.begin();
  radio.openWritingPipe(pipeOut);
  radio.setChannel(120);
  radio.setAutoAck(true);
  radio.setRetries(0,1);
  radio.setDataRate(RF24_250KBPS);       // The lowest data rate value for more stable communication
  radio.setPALevel(RF24_PA_MAX);         // Output power is set for maximum 
  radio.stopListening();                 // Start the radio comunication for Transmitter
  ResetData();
 
  pinMode(trimbut_1, INPUT_PULLUP); 
  pinMode(trimbut_2, INPUT_PULLUP);
  pinMode(trimbut_3, INPUT_PULLUP); 
  pinMode(trimbut_4, INPUT_PULLUP);
  pinMode(trimbut_5, INPUT_PULLUP); 
  pinMode(trimbut_6, INPUT_PULLUP);

  tvalue1= EEPROM.read(1) * 4;
  tvalue2= EEPROM.read(3) * 4;
  tvalue3= EEPROM.read(5) * 4;
}

// Joystick center and borders
  int Border_Map(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if ( val < middle )
  val = map(val, lower, middle, 0, 128);
  else
  val = map(val, middle, upper, 128, 255);
  return ( reverse ? 255 - val : val );
}
  void loop()
{

// Trims and Limiting trim values

  if(digitalRead(trimbut_1)==LOW and tvalue1 < 630) {
    tvalue1=tvalue1-15;
    EEPROM.write(1,tvalue1/4); 
    delay (130);
  }   
  if(digitalRead(trimbut_2)==LOW and tvalue1 > 280){
    tvalue1=tvalue1+15;
    EEPROM.write(1,tvalue1/4);
    delay (130);
  }
 
  if(digitalRead(trimbut_3)==LOW and tvalue2 < 630) { //3
    tvalue2=tvalue2-15;
    EEPROM.write(3,tvalue2/4);
    delay (130);
  }   
  if(digitalRead(trimbut_4)==LOW and tvalue2 > 280){ //4
    tvalue2=tvalue2+15;
    EEPROM.write(3,tvalue2/4);
    delay (130);
  }  
    
  if(digitalRead(trimbut_5)==LOW and tvalue3 < 630) { //5
     tvalue3=tvalue3+15;
     EEPROM.write(5,tvalue3/4);
     delay (130);
  }   
  if(digitalRead(trimbut_6)==LOW and tvalue3 > 280){  //6
    tvalue3=tvalue3-15;
    EEPROM.write(5,tvalue3/4);
    delay (130);
  }
  
// Control Stick Calibration for channels 
// "true" or "false" for signal direction
// Pin to control assignments:
// A0(pin 14)~ Lpot, A1(pin 15)~ Rpot, A3(pin 17) ~ JoyL l-r, A4(pin 18)~ JoyL u-d, A6(pin 20)~ JoyR l-r, A7(pin 21)~ JoyR u-d, pin 7~ switchR, pin 8~ switchL 

  data.roll = Border_Map( analogRead(A3), 0, tvalue1, 1023, true );    //   JoyL l-r, Tvalue for buttons
  data.pitch = Border_Map( analogRead(A7), 0, tvalue3, 1023, true );   //   JoyR u-d, Tvalue for buttons
  data.throttle = Border_Map( analogRead(A0), 0, 512, 1023, true );    //   Lpot, For Single side ESC, "(A4), 0, 256, 512, true"  for joy
  //data.throttle = Border_Map( analogRead(A4),0, 512, 1023, false );  //   JoyL u-d, For Bidirectional ESC (boats or cars or reversed thrust airplane), A4 for joy
  data.yaw = Border_Map( analogRead(A6), 0, tvalue2, 1023, true );     //   JoyR l-r, Tvalue for buttons
  data.aux1 = Border_Map( analogRead(A4), 0, 512, 1023, true );        //   JoyL u-d     
  data.aux2 = Border_Map( analogRead(A1), 0, 512, 1023, true );        //   Rpot      
  data.aux3 = digitalRead(7);                                          //   switchR
  data.aux4 = digitalRead(8);                                          //   switchL
  radio.write(&data, sizeof(Signal)); 
}
