#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "menu.h"
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//test callback function 
void pfun(void){
    Serial.println(F("This is label_1 fun!"));
  }
  
// define mutil_level_menu  
Menu main_m;
Menu sec_m;
Menu thd_m;

MenuItem main_list[4]={
  {10,10,MAIN_MENU,"label_1",NULL,NULL,NULL,&sec_m},
  {10,30,MAIN_MENU,"label_2",NULL,NULL,NULL,&thd_m},
  {10,50,MAIN_MENU,"label_3",NULL,NULL,NULL,&sec_m},
  {10,10,MAIN_MENU,"label_4",NULL,NULL,NULL,&sec_m}
  };
MenuItem sec_list[3]={  
  {10,10,SUB_MENU,"label_1.1",NULL,NULL,&main_m,NULL},
  {10,30,ITEM_PARAM,"label_1.2",NULL,pfun,&main_m,NULL},
  {10,50,ITEM_PARAM,"label_1.3",NULL,NULL,&main_m,NULL}
  };
MenuItem thd_list[3]={ 
  {10,10,SUB_MENU,"label_3.1",NULL,NULL,&main_m,NULL},
  {10,30,ITEM_PARAM,"label_3.2",NULL,NULL,&main_m,NULL},
  {10,50,ITEM_PARAM,"label_3.3",NULL,NULL,&main_m,NULL}
  }; 
    
Menu* Cur_menu = &main_m;  // define cur_menu pointer

//******************************//
//init menu 
//******************************//  
void menuSetup(){
  main_m ={4,PAGE_NUM(4),0,INIT_IDX,INIT_IDX,main_list,DrawMenu};
  sec_m  ={3,PAGE_NUM(3),0,INIT_IDX,INIT_IDX,sec_list,DrawMenu};
  thd_m  ={3,PAGE_NUM(3),0,INIT_IDX,INIT_IDX,thd_list,DrawMenu};  
  }  

//*******************************//  
//draw menu function which can be modified by user
//******************************//
void drawchar(MenuItem* mItem,bool cr) {
  display.setTextSize(2);      // Normal 1:1 pixel scale  
  if(true == cr){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }else{
    display.setTextColor(SSD1306_WHITE); // Draw white text     
    } 
  display.setCursor(mItem->x, mItem->y);     // Start at top-left corner
  display.println((mItem->label));
}
bool DrawMenu(Menu& menu){ 
  short num = min(menu.StartIdx+SCREEN_SECTION,menu.num);
  for(short i=menu.StartIdx;i < num ;i++){
    if(menu.CurIdx == i){
        drawchar(&(menu.list[i]),true);
      }else{
        drawchar(&(menu.list[i]),false);
      }   
    } 
   display.setTextSize(1);      // Normal 1:1 pixel scale  
   display.setTextColor(SSD1306_WHITE); // Draw white text 
   display.setCursor(SCREEN_WIDTH-20,0);     // Start at top-right corner   
   static char page[4] = {"0/0\0"};
   page[0]= menu.Cur_page+1+'0';
   page[2] = menu.page+'0';
   display.print(page); 
  return true;
  }
//******************************//   
  
void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();  
  menuSetup();
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
}

void loop() {
  // only for simple test 
  short value8 = digitalRead(8); //up
  short value9 = digitalRead(9); // down
  short value10 = digitalRead(10);//left
  short value11 = digitalRead(11);//right
  char key =0;
  if(LOW == value8){
     delay(500);
     if(LOW == value8){      
        key =0x01;
      }
  }
  if(LOW == value9){
      delay(500);
      if(LOW == value9){            
         key =0x02;
    }
  }      
  if(LOW == value10){
     delay(500);
     if(LOW == value10){  
        key =0x04;
     }
  }   
  if(LOW == value11){
    delay(500);
    if(LOW == value11){ 
      key =0x08;
    } 
  } 
   Cur_menu = Process_Button(Cur_menu,key);
   display.clearDisplay();
   Menu_Display(Cur_menu);
   display.display();
  
}
