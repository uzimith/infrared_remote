/*
*/

unsigned int on[] = {2552,2680,824,860,820, 860,824,1892,852,1868,824,1896,824,1892,828, 856,828, 856,848,53728,2552,2672,828,860,824, 856,824,1896,852,1864,824,1896,824,1896,852, 828,828, 856,828,53840,2560,2672,828,856,848, 836,824,1892,824,1892,828,1892,852,1868,852, 832,848, 832,828};
unsigned int off[] = {2552,2676,852,832,824,1896,848, 832,828, 856,828,1892,824, 856,852,1868,824,1892,852,53944,2556,2676,824,860,820,1896,828, 856,828, 852,848,1872,824, 856,828,1896,824,1892,824,53844,2552,2676,852,832,824,1896,848, 836,824, 856,828,1892,824, 860,820,1896,828,1888,848};

void setup () {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
}

void send_on() {
  int datasize = sizeof(on)/sizeof(on[0]);
  
  for (int i = 0; i < datasize; ++i) {
    unsigned long len = on[i];
    unsigned long now = micros();
    
    do {
      digitalWrite(12, 1-i&1);
      delayMicroseconds(8);
      digitalWrite(12, 0);
      delayMicroseconds(7);
    } while(long(now + len - micros()) > 0);
  }
}

void send_off() {
  int datasize = sizeof(off)/sizeof(off[0]);
  
  for (int i = 0; i < datasize; ++i) {
    unsigned long len = off[i];
    unsigned long now = micros();
    
    do {
      digitalWrite(12, 1-i&1);
      delayMicroseconds(8);
      digitalWrite(12, 0);
      delayMicroseconds(7);
    } while(long(now + len - micros()) > 0);
  }
}


const int OUTPUTS = 2;
byte pin[OUTPUTS] = {13, 12};
int current;

byte currentCase = 0;

void loop()
{
  if (Serial.available() > 0) {
    current = Serial.read();
  }

  // send 2
  if(current == 50) {
    Serial.print(2);
    send_on();
    delay(1000);

  }
  // send 1
  if(current == 49) {
    Serial.print(1);
    send_off();
    delay(1000);
  }

}
