#define LATCH_DIO D15   
#define CLK_DIO D14
#define DATA_DIO 2   

byte Row=0, Col=0;

const byte SEGMENT_MAP[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0X7F,0X6F,0X77,0X7C,0X39,0x0};
const byte DP = 0x80;  
const byte SEGMENT_SELECT[] = {0x0E,0x0D,0x0B,0x07};

// 一開始先將 last_num 都預設為 13，也就是 SEGMENT_MAP[13] 的 0x0，為了讓燈號不會亮
byte last_num[4] = {13, 13, 13, 13}; 
// 利用 keypad 陣列來控制對應輸出 row 和 col 的數字
const byte keypad[4][4] = {{1, 2, 3, 0xA},
                           {4, 5, 6, 0xB},
                           {7, 8, 9, 0xC},
                           {0, 0, 0, 0xD}, };

void setup() {

  /* Set DIO pins to outputs */
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
} 

void loop() {

  byte keyindex=0;

  if(keyscan()==true) 
  {
    keyindex=(Row-1)*4+Col;
    
    delay(5);
    
    if ((keyscan()==true) && (keyindex=(Row-1)*4+Col))
    {
      // 在我的設計中，上方 16 個按鈕依序為：
      // 1 2 3 A
      // 4 5 6 B
      // 7 8 9 C
      // x 0 x D
      // 第四排左邊的 x 的 keyindex 為 13；右邊的為 15
      // 兩者分別設定為從右飛到左(13)；與從左飛到右(15)的按鍵
      
      if(keyindex != 13 && keyindex != 15){
        
        // 此處是純跑馬燈位移的設計，每次更新 last_num 往前位移一格，並加入新按下的數字
        for(int i = 0; i < 3; ++i){
          last_num[i] = last_num[i+1];
        }
        last_num[3] = keypad[Row-1][Col-1];
      }
      else{
        
        // 此處為從右飛到左的跑馬燈設計
        if(keyindex == 13){
          // 從最右邊的燈開始
          for(int i = 0; i < 4; ++i){
            // 從第一個按下的數字開始飛入
            for(int j = 3; j >= 0; --j){
              WriteNumberToSegment(j, last_num[i]);
              delay(500);
            }
            // 為了讓數字能夠完整飛出，需在最後將最後一位燈號清零
            WriteNumberToSegment(0, 13);
            delay(500);
          }
        }
        // 此處為從左飛到右的跑馬燈設計
        else{
          // 從最左邊的燈開始
          for(int i = 3; i >= 0; --i){
            // 從最後一個按下的數字開始飛入
            for(int j = 0; j < 4; ++j){
              WriteNumberToSegment(j, last_num[i]);
              delay(500);
            }
            // 為了讓數字能夠完整飛出，需在最後將最後一位燈號清零
            WriteNumberToSegment(0, 13);
            delay(500);
          }
        }

        // 等跑馬燈輸出完後，將四個數字顯示在 7-segment 上靜止不動
        for(int i = 0; i < 4; ++i){
          WriteNumberToSegment(i, last_num[i]); 
        }
      }
      // 藉由 while 迴圈處理 race condition 問題，因為當我按下按鍵的瞬間即被視為讀取數次按下按鈕
      // 所以此處的設計是，當我仍在此次按下按鈕的動作時，更新完前面陣列後會被卡在此處的 while 迴圈，直到我放開按鈕
      // 模仿作業系統解決 busy waiting 的手段
      while(keyscan()==true);
    }
  } 

  // 在更新完前面的 last_num 陣列後，將所有最新的四個數字顯示在 7-segment 上
  for(int i = 0; i < 4; ++i){
    WriteNumberToSegment(i, last_num[i]); 
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
  
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
       digitalWrite(A0, HIGH);
      Col=1;Row=4;
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
  
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=3;
      keypressed = true;
      return(keypressed);
  }
  
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=4;
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
  
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=3;
      keypressed = true;
      return(keypressed);
  }
  
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=4;
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

// 根據所傳入的 segment 位置與 value 資訊，輸出該對應燈號
void WriteNumberToSegment(byte Segment, byte Value)
{
    digitalWrite(LATCH_DIO, LOW);

    // shiftOut 語法：shiftOut(dataPin, clockPin, bitOrder, value)
    // dataPin (DATA_DIO)，用來輸出每個 bit 的 pin
    // clockPin (CLK_DIO)，利用 toggle 使得 dataPin 得以被設成正確的值
    // bitOrder (MSBFIRST)，Most significant Bit First，由位數最大者先讀取
    // value，需要被 shift out 的數據
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);        
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );

    digitalWrite(LATCH_DIO,HIGH);
}
