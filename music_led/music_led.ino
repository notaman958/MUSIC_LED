#include <Adafruit_NeoPixel.h>
#define Pixel_num 150 // number of NeoPixels
#define Pixel_pin 11  // output pin for led strip
#define Voice_pin A0  // input pin for sound sensor


// declare the led strip object
Adafruit_NeoPixel strip(Pixel_num, Pixel_pin, NEO_GRB+NEO_KHZ800);
// this project uses WS2812
void setup() {
        Serial.begin(9600);
        strip.begin();                                    // Init Neopixel strip object
        Serial.println("WELCOME TO MUSIC LED LIVESHOW!");
        Serial.println("Let's start");
        /************SET LED OFF*********************/
        for(int i=0;i<strip.numPixels();i++)
        {
          strip.setPixelColor(i,0,0,0);                   // initially off
        }
        strip.show();
        /************SET INPUT PIN SENSOR************/
        DDRC = B11110 ;                                   //init sensor pin set A0 to input pin
    
      }

////////////////////////Analog to Digital////////////////////////////
int AD_conversion(byte ch)
{
  DIDR0=B11111111;                    //Configure input pin mode
  ADMUX=B01000000 | ch;               //Choose reference voltage and input channel => ref voltage 5V and input channel =ch
  ADCSRA=B11000111;                   //Start conversion
  while((ADCSRA & B01000000)!=0);     //..
  return ADC;                         // return converted value
}
///////////////////////End of AD conversion///////////////////////////

uint32_t pink_neon=strip.Color(64,0,64);
uint32_t green_neon=strip.Color(0,250,120);
uint32_t dark_cyan=strip.Color(240,240,245);
int INC=204;                          // divide 1023 into 5 levels
uint32_t color=pink_neon;             // set start color
unsigned long preTime=0;              // timer
unsigned long currentTime=0;          // timer
const int time_wait=50;               // in ms
int base=5;                           // set the base there are 3 bases 
int preVal=0;                         // hold previous value of remainder 
int count=0;
//////////////////////////////MAIN FUCNTION/////////////////////////////////
  void DJPlay()
{ 
    int here;                           // here to keep the bar moving when beat is high
    int plus;
    int DigitalSensorVal=AD_conversion(PINC);
    Serial.println(DigitalSensorVal);
    int times=DigitalSensorVal/INC;     // the higher the quotien the higher the beat;
    int rem=DigitalSensorVal%INC;       //remainder
    Serial.println(base);

    if(preVal!=0)
  {
      if(preVal<DigitalSensorVal)
        {
          count++;
          if(count==2)
          {
            if(base!=15)                  // reach highest base and stop and wait for drop beat
            base+=5;  
            count=0;         
          }
         
        }
      else
        {
          if(base!=5)                   // reach lowest base and stop and wait for high beat
          base-=5;
         
        }
  }
    if(times==0&&rem<102)
  {
      plus=0;
  }
    else if(times==0&&rem>=102)
  {
      plus=5;                               // adjust this if your led is shorter
  }
    else if(times==1&&rem<102)
  {
      plus=10;                              // adjust this if your led is shorter
  }
    else if(times==1&&rem>=102)
  {
      plus=15;                              // adjust this if your led is shorter
  }
    else if(times==2&&rem<102)
  {
      plus=20;                              // adjust this if your led is shorter
  }
    else if(times==2&&rem>=102)
  {
      plus=25;                              // adjust this if your led is shorter
  }
    else if(times==3&&rem<102)
  {
      plus=30;                              // adjust this if your led is shorter
  }
   else if(times==3&&rem>=102)
  {
      plus=35;                              // adjust this if your led is shorter
  }
  else if(times==4&&rem<102)
  {
      plus=40;                              // adjust this if your led is shorter
  }
  else if(times==4&&rem>=102)
  {
      plus=45;                              // adjust this if your led is shorter
  }
        here=Pixel_num-1-base;                                               // get the beat feels
        strip.fill(strip.ColorHSV(color),here,base);                        // Set pixel 'c' to value 'color'

        for(int i=here;i>=here-times*plus;i--)                               // run from the back to front
      {                                                                        
          strip.setPixelColor(i,strip.ColorHSV(color)) ;          
      }
        strip.show();      
      preVal=DigitalSensorVal;
      if(currentTime-preTime>=time_wait)
      {         
          preTime=currentTime;
          strip.clear();
          color+=(times*66536/plus);
      }
  
      
}
//////////////////////////////END OF MAIN FUCNTION/////////////////////////////////

void loop() {
  // test led strip
  currentTime=millis();
  DJPlay();
  
}
