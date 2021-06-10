//設定各接腳

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
#define P 0
#define A2 110
#define B2 123
#define C3 131
#define C3s 139
#define D3 147
#define D3s 156
#define E3 165
#define F3 175
#define F3s 185
#define G3 196
#define G3s 208
#define A3 220
#define A3s 233
#define B3 247
#define C4 262
#define D4 294
#define E4 330
int m[4][32]={
  { C3,E3,G3,C4,G3,E3,C3,
  D3,F3s,A3,D4,A3,F3s,D3,
   E3,G3s,B3,E4,B3,G3s,E3},
  {
   C3,C3,C3,E3,G3,G3,E3,
  G3,G3,A3,B3,C4,C4,G3,
  C4,C4,A3,G3,E3,A3,G3,
  E3,D3,C3,D3,E3,G3,A3,G3,E3,D3,C3
  },
    
  { C3,E3,G3,E3,C3},
    
    { G3,E3,D3,G3,E3,D3,P,B3,A3,G3,G3,A3}
    
    
 
    
};
int t[4][32]={
  { 
   1,1,1,1,1,1,2,
   1,1,1,2,1,1,2,
   1,1,1,1,1,1,2},
  {
  2,2,4,1,2,2,4,
  2,2,4,1,2,2,4,
  2,2,4,1,2,2,4,
  1,1,2,1,1,2,1,1,2,2,4
  
  },
    
    { 
   2,2,2,2,2},
    
      
    { 
   2,1,1,2,1,1,1,2,1,1,1,2}
    

 
};



byte colDataMatrix[8] = {
   B11111110,
   B11111101,
   B11111011,
   B11110111,
   B11101111,
   B11011111,
   B10111111,
   B01111111
}; //掃描
int L=0 ;//Which picture
byte rowDataMatrix[4][8] = {
  { B00000000,
   B01111111,
   B01000001,
   B01011101,
   B01010101,
   B01000101,
   B01111101,
   B00000001
  },
  {
   B11111111,
   B10000000,
   B10111110,
   B10100010,
   B10101010,
   B10111010,
   B10000010,
   B11111110
   
  },
  { B00000000,
   B01111110,
   B01000010,
   B01011010,
   B01011010,
   B01000010,
   B01111110,
   B00000000
   
  },
    
  { 
  B11111111,
   B10000001,
   B10111101,
   B10100101,
   B10100101,
   B10111101,
   B10000001,
   B11111111
  }
}; //圖案
int bs1=0,ps1=0;

void cp(){
 bs1=digitalRead(2);
if(L>=4)L=0;

if(bs1==0&&ps1==1){
    L++;
     ps1=0;
  }
 if(bs1==1){
     ps1=1;
  }
}


int S=0,bs2=0,ps2=0;


 int td=0,i=-1;
long ntime=0,ptime=0,pb=0;
void  check(){
ntime=millis();
  if(ntime-ptime>=pb){
   i++;
    if(i>=32){
    i=-1;
      pb=100;
      ptime=millis();
    }
    else{
     td=(100*t[S][i])+1;
      tone(13,m[S][i],td);
      pb=td*1.3;
     ptime=millis();
    }
  }
}  
void cm(){
bs2=digitalRead(4);
if(S>=4)S=0;

if(bs2==0&&ps2==1){
    S++;
  i=-1;
     ps2=0;
  }
 if(bs2==1){
     ps2=1;
  }

}
void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

}

void loop() {
  
  
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, rowDataMatrix[L][i]);
    digitalWrite(latchPin,HIGH);
    check();
    cp();
    cm();
    delay(1);
  }

}