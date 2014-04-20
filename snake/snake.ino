/*********************************************************************/
/* ARDUINO SNAKE by Tom Krcha (@tomkrcha) and Lee Brimelow (@leebrimelow) */
/* 2014 */

// renders on 96x96 Adafruit sharp memory display
// https://www.adafruit.com/products/1393

#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>

Adafruit_SharpMem display(SCK, MOSI, SS);

#define BLACK 0
#define WHITE 1

// display width and height
#define SW 96
#define SH 96
// generate food within the field with inset padding
#define PADDING 20
// snake size 2px
#define W 2
// constants for movement
#define TOP 0
#define BOTTOM 1
#define LEFT 2
#define RIGHT 3
// maximum length of snake
#define MAXLEN 50
// current/start length of snake
int length = 5;

int direction;
int currentx;
int currenty;
int lastx;
int lasty;
int foodx;
int foody;
int posx[MAXLEN];
int posy[MAXLEN];
int n;

// button pins
const int butLEFT = 8;     
const int butRIGHT = 7;

void setup(void) 
{
  
  display.begin();
  display.clearDisplay();

  direction = LEFT;

  currentx = 50;
  currenty = 50;
   
  genFood();
  
  lastx = 50;
  lasty = 50;
   
  for(int i=0;i<MAXLEN;i++){
     posx[i] = 0;
     posy[i] = 0;
  }

  n = 0;

  pinMode(butLEFT, INPUT_PULLUP);     
  pinMode(butRIGHT, INPUT_PULLUP);     

}

void refreshDisplay(void){
  // ********** direction **********
  int dirx = 0;
  int diry = 0;
  
  switch(direction){
    case LEFT:
       dirx = W;
       diry = 0;
       break; 
       
    case RIGHT:
       dirx = -W;
       diry = 0;
    
       break;
       
    case TOP:
       dirx = 0;
       diry = W;
    
       break;
       
    case BOTTOM:
       dirx = 0;
       diry = -W;
    
       break;
  }
  
  // ********** current position **********
  
  currentx += dirx;
  currenty += diry;
  
  if(currentx>=SW){
    currentx = 0;
  }else if(currentx<=0){
    currentx = SW;
  }
  
  if(currenty>=SH){
    currenty = 0;
  } else if(currenty<=0){
    currenty = SH;
  }
  
  display.fillRect(currentx, currenty, W, W, BLACK);

  // ********** food **********
  
  display.fillRect(foodx, foody, W, W, BLACK);

  if(currentx == foodx && currenty == foody){
      genFood();
      length+=1;
  }
  
  if(n==length){
    n = 0;
  }
  
  posx[n] = currentx;
  posy[n] = currenty;
  
  n++;
  
  // ********** remove tail **********
  int lastn = n-length;
  if(lastn<0){
    lastn = length+lastn;
  }
  lastx = posx[lastn];
  lasty = posy[lastn];
  
  display.fillRect(lastx, lasty, W, W, WHITE); 
  
  
  display.refresh();
  
} 
  
void loop(void) 
{
  // ********** buttons LEFT+RIGHT **********

  int buttonState = digitalRead(butLEFT);
  int buttonState2 = digitalRead(butRIGHT);

  if (buttonState == LOW) {
      changeDirection(LEFT);
  }
  
   if (buttonState2 == LOW) {     
      changeDirection(RIGHT);
  }
  
  delay(50);

  refreshDisplay();
}

// ********** Button click changes direction of Snake *********
void changeDirection(int dir){
   if(dir==LEFT){
      if(direction==LEFT){
        direction = BOTTOM;
      }else if(direction==BOTTOM){
        direction = RIGHT;
      }else if(direction==RIGHT){
        direction = TOP;
      }else if(direction==TOP){
        direction = LEFT;
      }
   }else if(dir==RIGHT){
      if(direction==LEFT){
        direction = TOP;
      }else if(direction==BOTTOM){
        direction = LEFT;
      }else if(direction==RIGHT){
        direction = BOTTOM;
      }else if(direction==TOP){
        direction = RIGHT;
      }         
   }
}

// ********** Food **********

void genFood(void){
   foodx = random(PADDING,SW-PADDING);
   foody = random(PADDING,SW-PADDING);
   if((foodx & 1)){
     foodx+=1;
   }
   if((foody & 1)){
     foody+=1;
   }
}
