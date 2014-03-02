/*
dht11 test
*/
 
int DHT11PIN = 7;
uint8_t bits[5]={0,0,0,0,0};
#define TIMEOUT 10000


int LedPin=2;


void setup ()
{
  Serial.begin(9600);
  pinMode( DHT11PIN,OUTPUT);
  pinMode( LedPin,OUTPUT);
}
void loop()
{
  int iRet =  dht11_read(DHT11PIN);
  if (iRet==0){
    Serial.print("RH:");
    Serial.print(bits[0]);
    Serial.print("  TMP:");
    Serial.println(bits[2]);
  }else{
     Serial.print("Error:");
     Serial.println(iRet);
  }
  
  pm25_read();
  delay(1000);
}

// return values:  
//  0 : OK  
// -1 : checksum error 
// -2 : timeout  
int dht11_read(uint8_t pin)  
{  
    // INIT BUFFERVAR TO RECEIVE DATA  
    uint8_t cnt = 7;  
    uint8_t idx = 0;  
  
    // EMPTY BUFFER  
    for (int i=0; i< 5; i++) bits[i] = 0;  
  
    // REQUEST SAMPLE  
    pinMode(pin, OUTPUT);  
    digitalWrite(pin, LOW);  
    delay(20);  
    digitalWrite(pin, HIGH);  
    delayMicroseconds(40);  
    pinMode(pin, INPUT);  
  
    // GET ACKNOWLEDGE or TIMEOUT  
    unsigned int loopCnt = TIMEOUT;  
    while(digitalRead(pin) == LOW)  
        if (loopCnt-- == 0) return -2;  
  
    loopCnt = TIMEOUT;  
    while(digitalRead(pin) == HIGH)  
        if (loopCnt-- == 0) return -2;  
  
    // READ THE OUTPUT - 40 BITS => 5 BYTES  
    for (int i=0; i<40; i++)  
    {  
        loopCnt = TIMEOUT;  
        while(digitalRead(pin) == LOW)  
            if (loopCnt-- == 0) return -2;  
  
        unsigned long t = micros();  
  
        loopCnt = TIMEOUT;  
        while(digitalRead(pin) == HIGH)  
            if (loopCnt-- == 0) return -2;  
  
        if ((micros() - t) > 40) bits[idx] |= (1 << cnt);  
        if (cnt == 0)   // next byte?  
        {  
            cnt = 7;     
            idx++;        
        }  
        else cnt--;  
    }
    
  
    // TEST CHECKSUM  
    uint8_t sum = bits[0] + bits[2]; // bits[1] && bits[3] both 0  
    if (bits[4] != sum) return -1; 
    
    return 0;  
} 

void pm25_read(){
  digitalWrite(LedPin,LOW); // power on the LED
  delayMicroseconds(280);
  int dustVal=analogRead(0); // read the dust value
  delayMicroseconds(40);
  digitalWrite(LedPin,HIGH); // turn the LED off
  delayMicroseconds(9680);
  Serial.print("PM25:");
  Serial.println(dustVal);
}
