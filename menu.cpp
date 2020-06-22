#include "menu.h"

void Menu_Display(Menu* menu){
   (*menu->draw)(*menu); //display       
}
//*****************************************//
Menu* Process_Button(Menu* menu,char value){
   
      switch (value){
          case BUTTON_UP:{
              if(menu->CurIdx >= 0 && menu->CurIdx < menu->num){
                 menu->CurIdx--; 
                 if(menu->CurIdx <0)
                    menu->CurIdx =0;
                 if(menu->CurIdx < menu->StartIdx){         //menu display page control
                    menu->Cur_page = (short)(menu->CurIdx /SCREEN_SECTION); 
                    menu->StartIdx = (menu->Cur_page) * SCREEN_SECTION; 
                  }              
              } 
              break;   
           }            
          case BUTTON_DOWN:{
              if(menu->CurIdx >= 0 && menu->CurIdx < menu->num){  
                 menu->CurIdx++;
                 if(menu->CurIdx >=menu->num)
                    menu->CurIdx = menu->num-1;
                 if(menu->CurIdx >= menu->StartIdx+SCREEN_SECTION){
                    menu->Cur_page = (short)(menu->CurIdx /SCREEN_SECTION); 
                    menu->StartIdx = (menu->Cur_page) * SCREEN_SECTION; 
                  }                
                }   
                break;             
            }          
          case BUTTON_RETUTN:{
            if(menu->list[menu->CurIdx].prv !=NULL){ 
              menu = menu->list[menu->CurIdx].prv;           //return current menu 
              }
              break;
            }
          case BUTTON_ENTER:{
            if(menu->list[menu->CurIdx].type != ITEM_PARAM && 
                menu->list[menu->CurIdx].next !=NULL){       //enter sub menu 
                menu = menu->list[menu->CurIdx].next;
              }else if(menu->list[menu->CurIdx].type == ITEM_PARAM){
                bool (*action)(void*)= NULL;
                void* pMsg = NULL;
                pMsg = menu->list[menu->CurIdx].pMsg;   
                action = menu->list[menu->CurIdx].action;
                if(action != NULL) (*action)(pMsg);       //pass msg and do the callback function
              }
              break;
            }
        }
        return menu;
   }
