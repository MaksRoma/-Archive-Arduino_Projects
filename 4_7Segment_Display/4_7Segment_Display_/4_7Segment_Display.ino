// conversion table
/*
        =====
       ||   ||
       ||===|| = 7 Segment decoder (1 of 4 display)
       ||   ||
        =====
          |
Looks something like below
          |
          |
         \ /
          A
        F   B
          G
        E   C
          D
P.S. '0' means not usable bit
0   1   1   1   1   1   1   1
    G   F   E   D   C   B   A
    
1 = 6     ( 0000 0110 )
2 = 91    ( 0101 1011 )
3 = 79    ( 0100 1111 )
4 = 102   ( 0110 0110 )
5 = 109   ( 0110 1101 )
6 = 125   ( 0111 1101 )
7 = 7     ( 0000 0111 )
8 = 127   ( 0111 1111 )
9 = 111   ( 0110 1111 )
0 = 63    ( 0011 1111 )



*/
struct RAM{
   uint8_t SEGM4;
   uint8_t SEGM3;
   uint8_t SEGM2;
   uint8_t SEGM1;
};

const uint8_t Array_Of_Numbers[10] = {   63, 6,  91, 79, 102,  109,  125,  7,  127,  111   };
uint32_t fixed_Time = millis();  
RAM vram = {  127,  63, 79, 91  };

void printBuffer();
RAM setBuffer(int number);
//void Adequate_Delay(int milliTime,void(*Function_Pointer)(RAM));

void setup() {              
  DDRB = DDRB | 0xF;  
  DDRD = 0xFF;
  PORTD = 0x00;
  PORTB &= 0x0;
}

void loop() 
{ 
  printBuffer();
  if( millis() > fixed_Time + 1000  )
  setBuffer(1234);

  if( millis() > fixed_Time + 2000  )
  setBuffer(5678);

  if( millis() > fixed_Time + 3000  )
  setBuffer(9012);

  if( millis() > fixed_Time + 3000  )
  fixed_Time = millis();
}

void printBuffer()
{
    PORTD = vram.SEGM1;
    delay(1);
    PORTD = 0x00;
    PORTB &= 0x0;
    PORTB ^= 0x2;
    
    PORTD = vram.SEGM2;
    delay(1);
    PORTD = 0x00;
    PORTB &= 0x0;
    PORTB ^= 0x4;
    
    PORTD = vram.SEGM3;
    delay(1);
    PORTD = 0x00;
    PORTB &= 0x0;
    PORTB ^= 0x8;
    
    PORTD = vram.SEGM4;
    delay(1);
    PORTD = 0x00;
    PORTB &= 0x0;
    PORTB ^= 0x1;
 }

RAM setBuffer(int number)
{
  vram.SEGM1 =  Array_Of_Numbers[number % 10];
  vram.SEGM2 =  Array_Of_Numbers[(number % 100) / 10];
  vram.SEGM3 =  Array_Of_Numbers[(number % 1000) / 100];
  vram.SEGM4 =  Array_Of_Numbers[number / 1000];
  
  return vram;
}
