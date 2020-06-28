#include <Adafruit_NeoPixel.h>
#define Pixel_num 150 // number of NeoPixels
#define Pixel_pin 11  // output pin for led strip
#define Voice_pin A0  // input pin for sound sensor

Adafruit_NeoPixel strip(Pixel_num, Pixel_pin, NEO_GRB+NEO_KHZ800);

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
    
}

static int var=0;
static int var1=170;
uint32_t pink_neon=strip.Color(64,0,64);
uint32_t green_neon=strip.Color(0,250,120);
uint32_t dark_cyan=strip.Color(240,240,245);
unsigned long preTime=0;
unsigned long currentTime=0;
const int time_wait=10;

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
  if(currentTime-preTime>=time_wait)
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
  
  if(currentTime-preTime>=time_wait*4)
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
  if(currentTime-preTime>=time_wait)
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
        if(currentTime-preTime>=time_wait)
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
  
void loop() {
  // test led strip
  currentTime=millis();
  SnakeRunUpdated();          // uncomment to play
  //Show1();                    // uncomment to play
  //Show2();                    // uncomment to play
  
}
