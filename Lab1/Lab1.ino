
#define NUM 16
int leds[NUM] = {
  D0, D1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15
};

#define TEST 4
int input[TEST] = {
  6, 20, 12, 26
}; 
// 預期輸出：2、16、8、30
// 00010、10000、01000、11110

int ans[TEST] = {0};
int total = 0;
int mask = 1 << 4;

void setup() {               
  for(int i = 0; i < NUM; i++){
    pinMode(leds[i], OUTPUT);
  }

  // total 最後會是 4 位 input 全部互相 XOR 的值
  for(int i = 0; i < TEST; ++i){
      total ^= input[i];
  }

  for(int i = 0; i < 32; i++){
      // 如果 total 有這一位元的話
      if(total & (1 << i)){
          for(int j = 0; j < TEST; j++){
              // 如果對於此數 這一位元若是不存在 但是 total 存在 代表其他有奇數個數有此位元
              if(!(input[j] & (1 << i))){
                  ans[j] |= (1 << i);
              }
          }
      }
      else{
          for(int j = 0; j < TEST; j++){
              // 如果對於此數 這一位元若是存在 但 total 不存在 代表總共有偶數個數有此位元
              if(input[j] & (1 << i)){
                  ans[j] |= (1 << i);
              }
          }
      }
  }
}

void light_input(int intputtmp){
    for(int j = 0; j < 5; ++j){
          int tmp = (intputtmp & mask);
          intputtmp <<= 1;

          if(tmp == mask){
            // 輸出 1 (燈亮起來)
            digitalWrite(leds[14 - j], LOW);
          }
          // 否則輸出 0 (不亮燈)
      }
}

void light_ans(int anstmp){
  for(int j = 0; j < 5; ++j){
      int tmp = (anstmp & mask);
      anstmp <<= 1;

      if(tmp == mask){
        // 輸出 1 (燈亮起來)
        digitalWrite(leds[6 - j], LOW);
      }
      // 否則輸出 0 (不亮燈)
  }
}

void loop() {
  // 先讓所有燈熄滅
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
  }

  for(int i = 0; i < TEST; ++i){
      int intputtmp = input[i];
      light_input(intputtmp);
      
      delay(1700);
      
      for(int i = 0; i < NUM; i++){
        digitalWrite(leds[i], HIGH);
      }
  }

  delay(1000);

  for(int i = 0; i < TEST; ++i){
      int anstmp = ans[i];
      light_ans(anstmp);
      
      delay(1700);
          
      for(int i = 0; i < NUM; i++){
        digitalWrite(leds[i], HIGH);
      }
  }

  delay(1000);
}
