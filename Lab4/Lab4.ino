#define LATCH_DIO D15   
#define CLK_DIO D14
#define DATA_DIO 2   
byte Row=0, Col=0;

#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int buttonState1,buttonState2,buttonState3,buttonState4 = 0;  
const int numRows = 2;
const int numCols = 16;
String str1 = "                ", str2 = "                ";
String str3 = "Happy BD To You.";

int speakerPin = D3;
char notes[] = "eefeageefebaeeecagfddcaba ";
unsigned long beats[] = {1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,2};
int tempo = 300;

char song[100];
int song_HML[100];
int idx = 0;
int HML = 0;
int start_record = 0;
String record_song[100];
bool flag = false;

void setup() {
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
  pinMode(BT3, INPUT);
  pinMode(BT4, INPUT);
  
  pinMode(LATCH_DIO,  OUTPUT);
  pinMode(CLK_DIO,  OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
 
  pinMode(10, INPUT);                                   
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT); 
  pinMode(A2, OUTPUT); 
  pinMode(A3, OUTPUT); 

  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  
  pinMode(speakerPin, OUTPUT);

  lcd.begin(numCols, numRows);
  lcd.clear();
  
  idx = 0;
  HML = 0;
  start_record = 0;
  flag = false;

  str1[10] = ' ';
  str1[11] = ' ';
  str1[12] = ' ';
  str1[13] = 'L';
  str1[14] = 'o';
  str1[15] = 'w';
}

void loop() {
   byte keyindex=0;

  if(keyscan()==true) 
  {
    keyindex=(Row-1)*4+Col;
    
    delay(5);
    
    if ((keyscan()==true) && (keyindex=(Row-1)*4+Col))
    {
      
      if(keyindex >= 1 && keyindex <= 3 || keyindex >= 5 && keyindex <= 7 || keyindex == 9){

          // 若前一個狀態是播完預錄歌曲，則將整個 lcd 清空
          if(flag){
            lcd.clear();
          }

          // 偵測 do~si 的音，並顯示在 lcd 第一排
          char tmp;
          lcd.setCursor(0, 0);
          if(keyindex == 1){
              tmp = 'a'; 
              str1[0] = 'D';
              str1[1] = 'o';
              lcd.print(str1);
          }
          else if(keyindex == 2){
              tmp = 'b';  
              str1[0] = 'R';
              str1[1] = 'e';
              lcd.print(str1);
          }
          else if(keyindex == 3){
              tmp = 'c';  
              str1[0] = 'M';
              str1[1] = 'i';
              lcd.print(str1);
          }
          else if(keyindex == 5){
              tmp = 'd';  
              str1[0] = 'F';
              str1[1] = 'a';
              lcd.print(str1);
          }
          else if(keyindex == 6){
              tmp = 'e';  
              str1[0] = 'S';
              str1[1] = 'o';
              lcd.print(str1);
          }
          else if(keyindex == 7){
              tmp = 'f';  
              str1[0] = 'L';
              str1[1] = 'a';
              lcd.print(str1);
          }
          else if(keyindex == 9){
              tmp = 'g';  
              str1[0] = 'S';
              str1[1] = 'i';
              lcd.print(str1);
          }

          // 偵測高低音 並撥放音
          if(HML == 0){
             playNote(speakerPin, tmp, beats[0] * tempo);
          }
          else if(HML == 1){
              playNote2(speakerPin, tmp, beats[0] * tempo);
          }
          else if(HML == 2){
              playNote3(speakerPin, tmp, beats[0] * tempo);
          }

          // 如果在錄音，則將音符紀錄下來，並同時記錄此音符的高低音字串顯示
          if(start_record = 1){
              song[idx] = tmp;
              song_HML[idx] = HML;
              record_song[idx] = str1;
              idx++;
          }
          
          while(keyscan()==true);
      }
      else if(keyindex == 4 || keyindex == 8 || keyindex == 12){

        // 更新高低音
        lcd.setCursor(0, 0);
        if(keyindex == 4){
              str1[10] = ' ';
              str1[11] = ' ';
              str1[12] = 'H';
              str1[13] = 'i';
              str1[14] = 'g';
              str1[15] = 'h';
              lcd.print(str1);
              HML = 2;
          }
          else if(keyindex == 8){
              str1[10] = 'M';
              str1[11] = 'i';
              str1[12] = 'd';
              str1[13] = 'd';
              str1[14] = 'l';
              str1[15] = 'e';
              lcd.print(str1);
              HML = 1; 
          }
          else if(keyindex == 12){
              str1[10] = ' ';
              str1[11] = ' ';
              str1[12] = ' ';
              str1[13] = 'L';
              str1[14] = 'o';
              str1[15] = 'w';
              lcd.print(str1);
              HML = 0;
          }
      }
      
      while(keyscan()==true);
    }
  } 
 
    buttonState1 = digitalRead(BT1);
    buttonState2 = digitalRead(BT2);
    buttonState3 = digitalRead(BT3);
    buttonState4 = digitalRead(BT4);

    if (buttonState1 == LOW) {
       // 開始錄音，並顯示
       lcd.clear();
       lcd.setCursor(0, 1);
       str2 = "Recording       ";
       lcd.print(str2);
       
       start_record = 1;
       idx = 0;
       flag = false;
       
    }  else if (buttonState2 == LOW) {
        // 停止錄音
        lcd.clear();
        lcd.setCursor(0, 1);
        str2 = "No Recording    ";
        lcd.print(str2);
        start_record = 0;
        flag = false;
       
    }else if (buttonState3 == LOW) {
       // 撥放錄音
       lcd.clear();
       lcd.setCursor(0, 1);
       
       str2 = "Playing         ";
       lcd.print(str2);
       flag = false;
       
      for (int i = 0; i < idx; i++) {
        if (notes[i] == ' ') {
          delay(beats[0] * tempo); 
          
        } else {
            // 撥放錄音的音符同時，顯示此音和此音的高低
            lcd.setCursor(0, 0);
            lcd.print(record_song[i]);
            
            if(song_HML[i] == 0){
               playNote(speakerPin, song[i], beats[0] * tempo);
            }
            else if(song_HML[i] == 1){
                playNote2(speakerPin, song[i], beats[0] * tempo);
            }
            else if(song_HML[i] == 2){
                playNote3(speakerPin, song[i], beats[0] * tempo);
            }
        }
        
        delay(tempo/10);
      }
       
    } else if (buttonState4 == LOW) {
       // 撥放預錄歌曲，並顯示歌曲名
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(str3);
       
       lcd.setCursor(0, 1);
       str2 = "Playing a Song  ";
       lcd.print(str2);
       
        for (int i = 0; i < sizeof(notes); i++) {
          if (notes[i] == ' ') {
              delay(500); // rest
          } else {
              // 配合歌曲設定高低音
              if(i == 4 || (i >= 10 && i <= 11) || (i >= 14 && i <= 16) || i >= 19){
                  playNote3(speakerPin, notes[i], beats[i] * tempo);
               }
               else{
                  playNote2(speakerPin, notes[i], beats[i] * tempo);
               }
          }
          delay(tempo/10);
        }

        flag = true;
        
    }
}

void playNote(int OutputPin, char note, unsigned long duration) {
  char names[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  int tones[] = { 261, 294, 330, 349, 392, 440, 494};

  // 播放音符對應的頻率(低音)
  for (int i = 0; i < 7; i++) {
    if (names[i] == note) {
      tone(OutputPin,tones[i], duration);
      delay(duration);
      noTone(OutputPin);
    }
  }
}

void playNote2(int OutputPin, char note, unsigned long duration) {
  char names[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  int tones[] = { 523, 587, 659, 698, 784, 880, 988};

  // 播放音符對應的頻率(中音)
  for (int i = 0; i < 7; i++) {
    if (names[i] == note) {
      tone(OutputPin,tones[i], duration);
      delay(duration);
      noTone(OutputPin);
    }
  }

}

void playNote3(int OutputPin, char note, unsigned long duration) {
  char names[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  int tones[] = { 1046, 1175, 1318, 1397, 1568, 1760, 1976};

  // 播放音符對應的頻率(高音)
  for (int i = 0; i < 7; i++) {
    if (names[i] == note) {
      tone(OutputPin,tones[i], duration);
      delay(duration);
      noTone(OutputPin);
    }
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
  
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=3;
      keypressed = true;
      return(keypressed);
  }
  
  //scan col 2  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=1;
      keypressed = true;
      return(keypressed);
  }
  
    //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=2;
      keypressed = true;
      return(keypressed);
  }

  //scan col 3  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=1;
      keypressed = true;
      return(keypressed);
  }
  
  //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=2;
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
  
    //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=2;
      keypressed = true;
      return(keypressed);
  }
  
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=3;
      keypressed = true;
      return(keypressed);
  }
  return(false);
}
