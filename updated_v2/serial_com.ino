#include <Adafruit_NeoPixel.h>
#define Pixel_num 150 // number of NeoPixels
#define Pixel_pin 11  // output pin for led strip
#define Voice_pin A0  // input pin for sound sensor


char terminator='\n';
char equal=':';
char delimiter=';';

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
uint32_t white=strip.Color(255,255,255);
int INC=205;                          // divide 1023 into 5 levels
uint32_t color=pink_neon;             // set start color
unsigned long preTime=0;              // timer
unsigned long currentTime=0;          // timer
const int time_wait=50;               // in ms
const int time_wait_2=10;               // in ms
int base=1;                           // set the base there are 3 bases 
int preVal=0;                         // hold previous value of remainder 
int preHere=0;
int here;                           // here to keep the bar moving when beat is high
int plus;
static int var=0;
static int var1=170;
//////////////////////////////MAIN FUCNTION/////////////////////////////////
  void DJPlay()
{ 
    int DigitalSensorVal=AD_conversion(PINC);
    Serial.println(DigitalSensorVal);
    int times=DigitalSensorVal/INC;     // the higher the quotien the higher the beat;
    int rem=DigitalSensorVal%INC;       //remainder
    Serial.println(base);

    if(preVal!=0)
  {
      if(preVal<DigitalSensorVal&&DigitalSensorVal-preVal>=3)
        {
         
            if(base!=15)                  // reach highest base and stop and wait for drop beat
              base+=5;
            
         
        }
      else if(preVal>DigitalSensorVal&&preVal-DigitalSensorVal>=3)
        {
          if(base!=1)                   // reach lowest base and stop and wait for high beat
          base-=5;
          else
          base=1;
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
    else if(times==3)
  {
      plus=30;                              // adjust this if your led is shorter
  }
   else if(times==4&&rem<102)
  {
      plus=34;                              // adjust this if your led is shorter
  }
  else if(times==4&&rem>=102)
  {
      plus=38;                              // adjust this if your led is shorter
  }
        here=Pixel_num-1-base;                                               // get the beat feels
        strip.fill(strip.ColorHSV(color),here,base);                        // Set pixel 'c' to value 'color'
      int fin=here-times*plus;
      if(fin<0)
      fin=0;
        for(int i=here+1;i>=fin;i--)                               // run from the back to front
      {                                                                        
          strip.setPixelColor(i,strip.ColorHSV(color)) ;          
      }
      
        strip.show();
      preTime=currentTime;
      while(currentTime-preTime<=time_wait*2)
      {
         // hold still alittle
         currentTime=millis();
         Serial.println("Im clear");
      }
      /*if(preHere==0)
        preHere=here;
      else if(preHere<here)
      {
        
          preHere=here;
      }
      else if(preHere>here)
      {
        preHere=here;
      }*/
      preVal=DigitalSensorVal;
      if(currentTime-preTime>=time_wait)
      {         
          preTime=currentTime;
          strip.clear();
          color+=(times*66536/plus);
      }
  
      
}

// sub function
void snakeRun_forward(uint32_t color, int v)
{
    for(int a=v;a<=v+20;a++)
        {
          strip.setPixelColor(a,color);  
        }  
        strip.show();          
}

void snakeRun_backward(uint32_t color, int v)
{
  for(int i=v;i>=v-20;i--)
  {
    strip.setPixelColor(i,color);
  }
  strip.show();
}
void FireWork(uint32_t color, int middle_point, int times)
{
  for(int i=0;i<times*10-4;i++)
  {
       strip.setPixelColor(middle_point+i,color);
       strip.setPixelColor(middle_point,dark_cyan);
       strip.setPixelColor(middle_point-i,color);
  }
    
    strip.show();
  
}

void rainbow(int pixel_start)
{
  //for(long color=0;color<65536;color+=256)
  //{
  long color=0;
    for(int i=pixel_start;i>=pixel_start-20;i--)
    {
      uint32_t pixelHue=color+(i*66536/20);
      strip.setPixelColor(i,strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    color+=256;
    if(color==65536)
    color=0;
  //}
}
///******************End of sub function********************///
///**************Call Show 1 or Show 2 or SnakeRunUpdated to play**************///
void Show1()
{
  if(currentTime-preTime>=time_wait_2)
  {
        preTime=currentTime;
      rainbow(var1);
    //snakeRun_forward(pink_neon,var);
    //FireWork(green_neon,114,var1);
    var1--;
    //var1++;
    strip.clear();
    if(var1<=0)
    {
        var1=170;
    }
  }
}

void Show2()
{
  
  if(currentTime-preTime>=time_wait_2)
  {
    FireWork(green_neon,114,var1);
    var1++;
    strip.clear();
    if(var1==5)
    var1=0;
  }
}

void SnakeRunUpdated()
{
  if(currentTime-preTime>=time_wait_2)
  {
        preTime=currentTime;
    snakeRun_forward(pink_neon,var);
    var++;
    strip.clear();
    if(var>=170)
    {
      while(var>=0)
      {
        currentTime=millis();
        if(currentTime-preTime>=time_wait_2)
        {
          preTime=currentTime;
          snakeRun_backward(green_neon,var);
          var--;
          strip.clear();
        }
      }
    }
  }
}
  int getCommand(String cmd)
{
  Serial.println(cmd);
  String temp_title, temp_value;
  if(cmd.length()!=0)
  {
    int len=cmd.length();
    int index=cmd.indexOf(equal);
    if(index>-1)
    {
      for(int i=0;i<index;i++)
      {
          temp_title+=cmd[i];
      }
      if(index!=len-1)
      {

         for(int j=index+1;j<len;j++)
         {
          temp_value+=cmd[j];
         }
      Serial.println(temp_value);
      }
    }
    if(temp_value=="ON")
      return 1; // led white
    else if(temp_value=="OFF")
      return 0;
    else if(temp_value=="MUSIC")
      return 2;
    else if(temp_value=="SNAKE")
      return 3;

  }
}
//////////////////////////////END OF MAIN FUCNTION/////////////////////////////////
int option=-1;
void loop() {
  // test led strip
      currentTime=millis();
  if(Serial.available()>0)
  {
    String cmd=Serial.readStringUntil(delimiter);
    option=getCommand(cmd);
    Serial.println(option);

   
  }
    //Serial.println(option);
   switch(option)
    {
      case 0:
        strip.clear();
        strip.show();
        break;
      case 1:
        strip.clear();
        strip.fill(white,here,150);                        // Set pixel 'c' to value 'color'
        strip.show();
        break;
      case 2:
        DJPlay();
        break;
      case 3:
        SnakeRunUpdated();
        break;
    }
  
}
