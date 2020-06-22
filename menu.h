#ifndef _MENU_H
#define _MENU_H
#endif
#include <Arduino.h>

#define SCREEN_SECTION 3        // per screem item numbers
#define PAGE_NUM(num)  ((short)((num)%SCREEN_SECTION >0 ? \    //calculate page counts
                        ((num)/SCREEN_SECTION +1) :\
                        ((num)/SCREEN_SECTION) <0 ? 1 :\
                        ((num)/SCREEN_SECTION)))
#define BUTTON_UP      0x01
#define BUTTON_DOWN    0x02
#define BUTTON_RETUTN  0x04
#define BUTTON_ENTER   0x08

//**************************************// 
#define INIT_IDX    0
#define MAIN_MENU   0
#define SUB_MENU    1
#define ITEM_PARAM  2
#define ITEM_BITMAP 3


typedef struct Menu Menu;
typedef struct MenuItem;


typedef struct MenuItem{
  short x; //item x axis
  short y; //item y axis
  short type; //item type
  char* label; // item label such as "music"
  void* pMsg;  // msg poniter
  bool (*action)(void*); //callback function
  struct Menu* prv;  //prev menu pointer
  struct Menu* next; //next menu pointer
 }MenuItem;

typedef struct Menu{
    short num; // contain item nums
    short page; // 
    short Cur_page;
    short CurIdx; //cur item
    short StartIdx;
    struct MenuItem* list; //item list   
    bool (*draw)(struct Menu&); // draw menu function    
  }Menu;


void Menu_Display(Menu* menu);
Menu* Process_Button(Menu* menu,char value);
