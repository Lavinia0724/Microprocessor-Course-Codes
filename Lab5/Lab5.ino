// include the library code:
#include <LiquidCrystal.h>
#include <RTC.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const byte seconds = 00;
const byte minutes = 40;
const byte hours = 13;
const byte day = 23;

byte record_seconds = 00;
byte record_minutes = 00;
byte record_hours = 00;

int first_time = 00;
int ori_time = 0, ori_time2 = 0;

bool have_been_bt1 = false;
bool stoping = false;
bool recording = false;
bool start_record = false;
bool recording_continue = false;
String str1 = "                ";
int buttonState1,buttonState2,buttonState3,buttonState4 = 0;  

void setup() {

    pinMode(BT1, INPUT);
    pinMode(BT2, INPUT);
    pinMode(BT3, INPUT);
    pinMode(BT4, INPUT);
     
    lcd.begin(16, 2);
    RTC.settime(day, hours, minutes, seconds);
    RTC.startcounting();
    
    record_seconds = 0;
    record_minutes = 0;
    record_hours = 0;

    first_time = 0;
    ori_time = 0;
    ori_time2 = 0;

    have_been_bt1 = false;
    stoping = false;
    start_record = false;
    recording = false;
    recording_continue = false;
     
}

void output(){
    // 負責控制目前時間的輸出 function
    if(record_hours < 10){
        lcd.print("0");
     }
     lcd.print(record_hours);
     lcd.print(":");
     
     if(record_minutes < 10){
        lcd.print("0");
     }
     lcd.print(record_minutes);
     lcd.print(":");
     
     if(record_seconds < 10){
        lcd.print("0");
     }
     lcd.print(record_seconds);
     lcd.print(" ");
}

void timer(){
     // 用以控制計時器時間的輸出 function
     lcd.setCursor(0, 0);
     lcd.print("11/");
     lcd.print(RTC.getday());
     lcd.print("   ");
     
     if(RTC.gethours() < 10){
        lcd.print("0");
     }
     lcd.print(RTC.gethours());
     lcd.print(":");
     if(RTC.getminutes() < 10){
        lcd.print("0");
     }
     lcd.print(RTC.getminutes());
     lcd.print(":");
     if(RTC.getseconds() < 10){
        lcd.print("0");
     }
     lcd.print(RTC.getseconds());
}

void loop() {
     lcd.setCursor(0, 0);
     lcd.print("11/");
     lcd.print(RTC.getday());
     lcd.print("   ");
     
     if(RTC.gethours() < 10){
        lcd.print("0");
     }
     lcd.print(RTC.gethours());
     lcd.print(":");
     if(RTC.getminutes() < 10){
        lcd.print("0");
     }
     lcd.print(RTC.getminutes());
     lcd.print(":");
     if(RTC.getseconds() < 10){
        lcd.print("0");
     }
     lcd.print(RTC.getseconds());
     
      buttonState1 = digitalRead(BT1);
      buttonState2 = digitalRead(BT2);
      buttonState3 = digitalRead(BT3);
      buttonState4 = digitalRead(BT4);

    if (buttonState1 == LOW) {
         // 若按下 BT1, 將計時器歸零，且可以顯示計時器
         record_hours = 0;
         record_minutes = 0;
         record_seconds = 0;
         
         start_record = recording = false;
         recording_continue = false;

         ori_time = ori_time2 = 0;
         
         // 用此 bool 值控制是否有按過 BT1, 否則如果先按其他按鈕都不反應
         have_been_bt1 = true;
         
         lcd.setCursor(0, 1);
         output();
         lcd.print("StopWatch");
       
    } else if (buttonState2 == LOW && have_been_bt1) {
        // 若按下 BT2, 將所有計時器歸零
        record_hours = 0;
        record_minutes = 0;
        record_seconds = 0;
        
        start_record = recording = false;
        recording_continue = false;
        ori_time = ori_time2 = 0;

        lcd.setCursor(0, 1);
        output();
        lcd.print("StopWatch");
    } else if (buttonState3 == LOW) {
        // 若按下 BT3, 將計時器歸零, 並將第二列計時器的顯示消失
        record_hours = 0;
        record_minutes = 0;
        record_seconds = 0;
        
        start_record = recording = false;
        recording_continue = false;

        have_been_bt1 = false;

        lcd.setCursor(0, 1);
        lcd.print(str1);
    } else if (buttonState4 == LOW && have_been_bt1) {
        // 若按下 BT4, 開始計時

        // 利用 start_record 控制現在是否開始計時
        // 且用 recording_continue 控制現在是否在計時的過程中(可能有按過暫停)
        if(!start_record) {
            start_record = true;
        }
        else {
          start_record = false;
          recording_continue = true;
        }

        int sec = RTC.getseconds();
        int mins = RTC.getminutes();
        int hour = RTC.gethours();
        // first_time 紀錄第一次按下開始計時器的當前時間
        first_time = (sec + mins * 60 + hour * 3600);
        
        recording = true;

        // 卡 busy waiting
        while(!digitalRead(BT4));
    }

    if(start_record && recording){
        int sec = RTC.getseconds();
        int mins = RTC.getminutes();
        int hour = RTC.gethours();

        // now_time 紀錄當前時間 - 第一次按下開始計時器的時間, 也就是累計計時的時間
        // ori_time2 紀錄當前本次開始計時累計計時的時間
        // ori_time 紀錄過去累計計時的時間
        // 將 now_time 更新為目前總共累計計時的時間, 並輸出
        int now_time = (sec + mins * 60 + hour * 3600) - first_time;
        ori_time2 = now_time;
        now_time += ori_time;
        
        record_hours = (now_time/3600);
        record_minutes = (now_time%3600)/60;
        record_seconds = ((now_time%3600)%60);

        lcd.setCursor(0, 1);
        output();
        lcd.print("Counting");

        stoping = true;
    } 
     if(!start_record && recording){
           lcd.setCursor(0, 1);
           output();
           lcd.print("   Stop");

           // 從開始計時(不一定是第一次),並按下暫停時, 紀錄上次 ori_time2 累計的時間更新給 ori_time
           if(stoping){
              ori_time += ori_time2;
              stoping = false;
           }
           recording = false;
      }
      
}
