#include <LiquidCrystal.h>
#define BUTTON_RIGHT 0
#define BUTTON_UP 1
#define BUTTON_DOWN 2
#define BUTTON_LEFT 3
#define BUTTON_SELECT 4
#define BUTTON_NONE 5
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int flag=0;
int readButtons();
int previousButton=BUTTON_NONE,currentButton,i=0,currentCursor;
unsigned int D1=-1,D2=-1,D3=-1,D4=-1;
unsigned long timeLeds;
int previousCursor;
uint8_t upArrow[8] = {
    0b00100,
    0b01110,
    0b11111,
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00100};

void setup(){
  lcd.begin(16, 2);
    lcd.createChar(1, upArrow);
}
void loop(){
    delay(500);
    if(flag==0){
      msgInit();
    }
  currentButton=readButtons();
  switch(currentButton){
    case 0:
      if(flag!=0){
          moveCursorRight();
      }
      break;
    case 1:
      setNumber();
      break;
    case 2:
      setNumber();
      break;
    case 3:
      if(flag!=0){
          moveCursorLeft();
      }
      break;
    case 4:
      if(flag==0){
            lcd.clear();
            setValueNone();
            showCurrentCursor(1);
        currentCursor=1;
            flag=1;
      }
        if(D1!=-1&&D2!=-1&&D3!=-1&&D4!=-1){
          prenderBitDatos();
          delay(500);
          prenderBitParidad();
        }
      break;
  }
}

void setNumber(){
  int retorno=0;
  if(readButtons()==BUTTON_UP){
    switch(currentCursor){
      case 1:
        if(D1==0||D1==-1){
          lcd.setCursor(0, 0);
          lcd.print("1");
          D1=1;
          break;
        }
        if(D1==1){
          lcd.setCursor(0, 0);
          lcd.print("0");
          D1=0;
        }
        break;
      case 2:
        if(D2==0||D2==-1){
          lcd.setCursor(1, 0);
          lcd.print("1");
          D2=1;
          break;
        }
        if(D2==1){
          lcd.setCursor(1, 0);
          lcd.print("0");
          D2=0;
        }
        break;
      case 3:
        if(D3==0||D3==-1){
          lcd.setCursor(2, 0);
          lcd.print("1");
          D3=1;
          break;
        }
        if(D3==1){
          lcd.setCursor(2, 0);
          lcd.print("0");
          D3=0;
        }
        break;
      case 4:
        if(D4==0||D4==-1){
          lcd.setCursor(3, 0);
          lcd.print("1");
          D4=1;
          break;
        }
        if(D4==1){
          lcd.setCursor(3, 0);
          lcd.print("0");
          D4=0;
        }
        break;
      }
  }
  if(readButtons()==BUTTON_DOWN){
    switch(currentCursor){
      case 1:
        if(D1==1||D1==-1){
          lcd.setCursor(0, 0);
          lcd.print("0");
          D1=0;
          break;
        }
        if(D1==0){
          lcd.setCursor(0, 0);
          lcd.print("1");
          D1=1;
        }
        break;
      case 2:
        if(D2==1||D2==-1){
          lcd.setCursor(1, 0);
          lcd.print("0");
          D2=0;
          break;
        }
        if(D2==0){
          lcd.setCursor(1, 0);
          lcd.print("1");
          D2=1;
        }
        break;
      case 3:
        if(D3==1||D3==-1){
          lcd.setCursor(2, 0);
          lcd.print("0");
          D3=0;
          break;
        }
        if(D3==0){
          lcd.setCursor(2, 0);
          lcd.print("1");
          D3=1;
        }
        break;
      case 4:
        if(D4==1||D4==-1){
          lcd.setCursor(3, 0);
          lcd.print("0");
          D4=0;
          break;
        }
        if(D4==0){
          lcd.setCursor(3, 0);
          lcd.print("1");
          D4=1;
        }
        break;
      }
  }
}
void prenderBitParidad(){
  if(D1==0&&D2==0&&D4==1||D1==0&&D2==1&&D4==0||D1==1&&D2==1&&D4==1||D1==1&&D2==0&&D4==0){
              pinMode(13,OUTPUT);
    }
    if(D1==0&&D3==0&&D4==1||D1==0&&D3==1&&D4==0||D1==1&&D3==1&&D4==1||D1==1&&D3==0&&D4==0){
      pinMode(12,OUTPUT);
    }
    if(D2==0&&D3==0&&D4==1||D2==0&&D3==1&&D4==0||D2==1&&D3==1&&D4==1||D2==1&&D3==0&&D4==0){
        pinMode(10,OUTPUT);
    }
}
void prenderBitDatos(){
    if(flag==1&&BUTTON_SELECT==readButtons()){
        if(D1==1){
          pinMode(11,OUTPUT);
        }
        if(D2==1){
          analogWrite(A3,0);
        }
        if(D3==1){
          analogWrite(A4,0);
        }
        if(D4==1){
          analogWrite(A5,0);
        }
    }
}
void apagarBitDatos(){
  if(flag==1){
        if(D1==0){
          pinMode(11,INPUT);
        }
        if(D2==0){
          analogWrite(A3,1);
        }
        if(D3==0){
          analogWrite(A4,1);
        }
        if(D4==0){
          analogWrite(A5,1);
        }
    }
}
void showCurrentCursor(int option)
{
    switch(option){
    case 1:
        lcd.setCursor(3, 2);
            lcd.print(" ");
        lcd.setCursor(2, 2);
            lcd.print(" ");
        lcd.setCursor(1, 2);
            lcd.print(" ");
        lcd.setCursor(0, 2);
            lcd.write(1);
        break;
    case 2:
        lcd.setCursor(0, 2);
            lcd.print(" ");
        lcd.setCursor(2, 2);
            lcd.print(" ");
        lcd.setCursor(3, 2);
            lcd.print(" ");
        lcd.setCursor(1, 2);
            lcd.write(1);
        break;
    case 3:
        lcd.setCursor(0, 2);
            lcd.print(" ");
        lcd.setCursor(1, 2);
            lcd.print(" ");
        lcd.setCursor(3, 2);
            lcd.print(" ");
        lcd.setCursor(2, 2);
            lcd.write(1);
        break;
    case 4:
        lcd.setCursor(0, 2);
            lcd.print(" ");
        lcd.setCursor(1, 2);
            lcd.print(" ");
        lcd.setCursor(2, 2);
            lcd.print(" ");
        lcd.setCursor(3, 2);
            lcd.write(1);
        break;
    }
}
void moveCursorRight(){
  if(readButtons()==BUTTON_RIGHT){
      while(i<=5){
        if(i==5){
          i=0;
        }
        i++;
      showCurrentCursor(i);
        currentCursor=i;
        if(i==4){
          i=0;
        }
        
        break;  
      }
    }
}
void moveCursorLeft(){
  if(readButtons()==BUTTON_LEFT){
      while(i>=0&&i<=5){
        if(i==0){
          i=5;
        }
        i--;
      showCurrentCursor(i);
        currentCursor=i;
        if(i==1){
          i=5;
        }
        
        break;
      }
    }
  
}
void setValueNone()
{
    lcd.setCursor(0, 0);
    lcd.write("*");
    D1=-1;
    lcd.setCursor(1, 0);
    lcd.write("*");
    D1=-1;
    lcd.setCursor(2, 0);
    lcd.write("*");
    D1=-1;
    lcd.setCursor(3, 0);
    lcd.write("*");
    D1=-1;
}
void msgInit(){
    lcd.setCursor(0,0);
    lcd.print("Presione SELECT");
    lcd.setCursor(1,2);
    lcd.print("para comenzar");
}
int readButtons()
{
    int value = analogRead(0);
    if (value > 900)
        return BUTTON_NONE;
    if (value < 50)
        return BUTTON_RIGHT;
    if (value < 250)
        return BUTTON_UP;
    if (value < 450)
        return BUTTON_DOWN;
    if (value < 650)
        return BUTTON_LEFT;
    if (value < 850)
        return BUTTON_SELECT;
    return BUTTON_NONE; // Por si todo falla
}
