#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte Row=0, Col=0;
const int numRows = 2;
const int numCols = 16;

String str1 = "ThisHomeworkLab3NeedsFortyWordsToPresent";
String str2 = "HowManyWordsShalINeedToWriteThisHomework";
bool flag = false;

int buttonState1,buttonState2,buttonState3,buttonState4 = 0;     

void setup() {
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
  pinMode(BT4, INPUT);
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT); 
  pinMode(A2, OUTPUT); 
  pinMode(A3, OUTPUT); 

  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  
  lcd.begin(numCols, numRows);

  // 預設 cursor on
  flag = true;
  lcd.cursor();
}

void loop() {
    buttonState1 = digitalRead(BT1);
    buttonState2 = digitalRead(BT2);
    buttonState4 = digitalRead(BT4);
    
    if (buttonState1 == LOW) {
       // BT1 清空所有 lcd display
       lcd.clear();
       
    }  else if (buttonState2 == LOW) {
      // BT2 讓 cursor 回到最左上角
       lcd.home();
       
    } else if (buttonState4 == LOW) {
      // 若 flag 為 false，表示現在沒有 cursor，則設定為 cursor on
      // 若 flag 為 true，表示現在有 cursor，則設定 cursor off
       if(flag){
          lcd.noCursor();
          flag = false;
       }
       else{
          lcd.cursor();
          flag = true;
       }
        delay(500);
        
       // 因為按鈕按下去的瞬間的判定會反覆讀取，所以需要卡 busy waiting
       while(!digitalRead(BT4));
    }

    byte keyindex=0;
    if(keyscan()==true) {
        keyindex = (Row - 1) * 4 + Col;
        delay(5);
        
            // 若按下 buttom 1，設定寫出 str1
            if(keyindex == 1){
                lcd.setCursor(0, 0);
                lcd.print(str1);
            }
            // 若按下 buttom A，設定寫出 str2
            if(keyindex == 4){
                lcd.setCursor(0, 1);
                lcd.print(str2);  
            }

            // 若按下 buttom 4，讓 display 向左位移 40 次
            if(keyindex == 5){
                for (int positionCounter = 0; positionCounter < 40; positionCounter++) {
                    lcd.scrollDisplayLeft();
                    delay(200);
                }
            }

            // 若按下 buttom D，讓 display 向右位移 40 次
            if(keyindex == 16){
                for (int positionCounter = 0; positionCounter < 40; positionCounter++) {
                    lcd.scrollDisplayRight();
                    delay(200);
                }
            }
        // 卡 busy waiting
        while((keyscan() == true)) ; 
    } 
}

bool keyscan( )
{
  Row=0;Col=0;
  bool keypressed = false;

  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);

  // 讀取按鈕的數據，根據所按下的按鈕更新其所在位置的 col 和 row，並回傳有"按下"此按鈕的 keypressed 資訊
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=1;
      keypressed = true;
      return(keypressed);
  }
  
  //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=2;
      keypressed = true;
      return(keypressed);
  }
  
  //scan col 4  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  delayMicroseconds(100);
  
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=1;
      keypressed = true;
      return(keypressed);
  }
  
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=4;
      keypressed = true;
      return(keypressed);
  }
  return(false);
}
