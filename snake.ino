/*********************************************************************/
/* ARDUINO SNAKE by Tom Krcha and Lee Brimelow */

#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Time.h>

Adafruit_SharpMem display(SCK, MOSI, SS);

#define BLACK 0
#define WHITE 1


#define SW 100
#define SH 100
#define W 2

#define TOP 0
#define BOTTOM 1
#define LEFT 2
#define RIGHT 3
#define MAXLEN 50

int direction;
int currentx;
int currenty;
int lastx;
int lasty;

int foodx;
int foody;

int length = 5;

int posx[MAXLEN];
int posy[MAXLEN];// = {0,0,0,0,0,0,0,0,0,0};
int n;

const int butLEFT = 8;     
const int butRIGHT = 7;

int lastDirection;

void setup(void) 
{
  
  Serial.begin(9600);
  // start & clear the display
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
  
   //display.fillRect(50, 50, 40, 40, BLACK); //Solid Fill Rectangle
  
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
  
  display.fillRect(foodx, foody, W, W, BLACK);

  if(currentx == foodx && currenty == foody){
//      display.fillRect(foodx, foody, W, W, WHITE);
      genFood();
      length+=1;
  }
  // n
  if(n==length){
    n = 0;
  }
  
  posx[n] = currentx;
  posy[n] = currenty;
  
  n++;
  
  // remove tail
  
  int lastn = n-length;
  if(lastn<0){
    lastn = length+lastn;
  }
  lastx = posx[lastn];
  lasty = posy[lastn];
  
  display.fillRect(lastx, lasty, W, W, WHITE); //Solid Fill Rectangle
  
  display.refresh();
  
} 
  
void loop(void) 
{
  int buttonState = digitalRead(butLEFT);
  int buttonState2 = digitalRead(butRIGHT);

  if (buttonState == LOW) {
      changeDirection(LEFT);
  }
  
   if (buttonState2 == LOW) {     
      changeDirection(RIGHT);
  }
  
  delay(100);

  refreshDisplay();
}

void changeDirection(int dir){
       if(dir==LEFT){
                  //if(direction!=lastDirection){

          if(direction==LEFT){
            direction = BOTTOM;
                        Serial.println("changeDirection BOTTOM");
                        lastDirection = direction;

          }else if(direction==BOTTOM){
            direction = RIGHT;
                                    Serial.println("changeDirection RIGHT");
                                    lastDirection = direction;

          }else if(direction==RIGHT){
            direction = TOP;
            
                                    Serial.println("changeDirection TOP");
                                    lastDirection = direction;

          }else if(direction==TOP){
            direction = LEFT;
                                    Serial.println("changeDirection LEFT");
                                    lastDirection = direction;

          }
              //    }
       }else if(dir==RIGHT){
         //if(direction!=lastDirection){
          if(direction==LEFT){
            direction = TOP;
                        Serial.println("changeDirection TOP");
                                    lastDirection = direction;


          }else if(direction==BOTTOM){
            direction = LEFT;
          
            Serial.println("changeDirection LEFT");
                                    lastDirection = direction;

          }else if(direction==RIGHT){
            direction = BOTTOM;
            
                                    Serial.println("changeDirection BOTTOM");
                                    lastDirection = direction;

          }else if(direction==TOP){
            direction = RIGHT;
                                    Serial.println("changeDirection RIGHT");
                                    lastDirection = direction;

          }
       //  }
         
       }
       
}

void genFood(void){
     foodx = random(20,80);
   foody = random(20,80);
   if((foodx & 1)){
     foodx+=1;
   }
   if((foody & 1)){
     foody+=1;
   }
}
