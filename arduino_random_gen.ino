
const int analogPin = 4;
long millisec,contat;
const bool fastADC=true;//http://forum.arduino.cc/index.php?topic=6549.0
const bool printPerformances=false;//Every 10Kbits,I print the time

 // defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


void setup() {
  
  Serial.begin(115200);
  //pinMode(5,INPUT);
  //analogReference(EXTERNAL);
  pinMode(A4,INPUT);

 millisec=millis();
  if(fastADC){
    // set prescale to 16
    sbi(ADCSRA,ADPS2) ;
    cbi(ADCSRA,ADPS1) ;
    cbi(ADCSRA,ADPS0) ;
  }
}

void loop() {
 
  // put your main code here, to run repeatedly:
  //Serial.print(digitalRead(5));
  //Serial.println(analogRead(analogPin));
  //while(1){
    int val1,val2;
    delayMicroseconds(3);
    val1=getInt();
    delayMicroseconds(2);
    val2=getInt();

    /*
     * Usually lower bits has an higher variancy. At the same time, I don't want to waste completly highest bits, so I've merged two nibbles using xor
     */
    val1=(val1>>4)^(val1&15);
    val2=(val2>>4)^(val2&15);

    int xo=val1^val2;//there are variation across two reads
    xo=xo&255;
    if(xo>0 && !( (val1&256)^(val2&512))){//Insteadd of completly throw away the two highest bits,I use the to flip the outcome
      int temp=val1;//a NOT over val1 would be sufficient
      val1=val2;
      val2=temp;
    }
    //if(xo){Serial.print(xo);Serial.print(" ");Serial.println(val1&15);contat++;}
    while(xo>0){//I print bits which differ across two reads
      if(xo&1){Serial.print(val1&1);/* /writeBitToBuffer(val1&1);*/ contat++;}
      xo>>=1;
      val1>>=1;
    }
   // eventuallySendBuffer();
   if(printPerformances){
      if(contat>=10000){
        Serial.println("");
        Serial.print(contat);
         Serial.print(" ");
         Serial.println(millis()-millisec);
         millisec=millis();
         contat=0;
      }
   }
    /*
    It increases a bit the noise. Is mandatory to test if this trick compromises the quality  of randomness
    */
    analogWrite(9, (contat%16)*16);
  //}
}

/*const int lenBuffer=16;
byte bufferSend[lenBuffer];
int bufferIndex=0;
void writeBitToBuffer(byte _bit){
  int offsBit=bufferIndex&7;//I get the bit position inside the byte
  int offsByte=bufferIndex>>3;//I get the byte
  bitWrite(bufferSend[offsByte],offsBit,_bit);
  bufferIndex++;
}
void eventuallySendBuffer(){
  const int threeshold=(lenBuffer-4)*8;
  if((bufferIndex>=threeshold && ((bufferIndex&7)==0))/*||(bufferIndex>=lenBuffer*8)* /){
    //Serial.write(bufferSend,bufferIndex>>3);
    Serial.print("aaaaaaaaaaaaaaaa");
    bufferIndex=0;
  }
}*/



/*inline byte getInt(){
  int val;
  do{
    val=analogRead(analogPin)>>1;
    
  }while(val>=385 ||val<=127);
  //return val;
  return val-128;
}*/

inline int getInt(){
  int val;
  do{
    val=analogRead(analogPin);
  }while(val>=1020 ||val<=3);
 // return val;
  return val-4;
}

