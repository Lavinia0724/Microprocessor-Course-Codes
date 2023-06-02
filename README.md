## LAVI's Microprocessor Course Codes
###### tags: `Course` `Arduino` `LAVI` `2022` 

## Information
- 大三上學期微處理機課程作業程式
- 使用 Arodunino 及 FPGA Andes Corvette-F1-N25

### Details
#### Lab1 LED Matrix Control Design
- 使用 Arduino 設計一個運用 bitwise operator 的程式

#### Lab2 7-Segment Control & Key-Matrix
- 自由選定 10 個 Push Buttons 為不同數字輸入，按下後必須將數字顯示在 7-Segment 上
- 自由選定 2 個 Push Buttons 作跑馬燈控制：
    - 1 個控制由左到右之跑馬燈，最末位數字 (最後按下數字) 先飛入，數字必須完全飛出 7-Segment 後，再將 4 個數字顯示在 7-Segment 後，靜止不動
    - 1 個控制由右到左之跑馬燈，第一位數字 (最先按下數字) 先飛入，數字必須完全飛出 7-Segment 後，再將 4 個數字顯示在 7-Segment 後，靜止不動
        > 跑馬燈效果：數字必須慢慢移入，不能太快

#### Lab3 LCM Control 
- 跑馬燈設計規格：
    - 以 push button 1 控制第一組文字顯示，文字長度 40
    - 以 push button A 控制第二組文字顯示，文字長度 40
    - 以 push button 4 控制文字左移
    - 以 push button D 控制文字右移
    - 以 push button BTN1 控制 Clear Display
    - 以 push button BTN2 控制 Return Home
    - 以 push button BTN4 控制 Cursor on/off

#### Lab4 PWM (Pulse-WidthModulator)
- 錄放音機設計規格：
    - 以 push button 1\~7 控制七個音符發音，LCM 第一列最左邊顯示 Do、Re、Mi、Fa、So、La、Si
    - 以 push button A, B, C 控制高、中、低音輸出，LCM 第一列最右邊分別顯示 `High`、`Middle`、`Low`
    - 以 push button BTN1 控制錄音 (Record)，開始錄音，LCM 第二列顯示顯示 `Recording`
    - 以 push button BTN2 代表結束錄音，LCM 第二列顯示 `NoRecording`
    - 以 push button BTN3 控制錄音播放 (Play)，LCM 第二列顯示 `Playing`
    - 以 push button BTN4 播放事先預錄的一首歌曲，LCM 第一列顯示歌名，LCM 第二列顯示 `Playinga Song`

#### Lab5 RTC (RealTimeClock)
- 時鐘顯示與碼錶控制設計規格：
    - 先設定 RTC 的日期/時間為 `MM/DD` (Demo日期)，`HH:MM:SS`
    - 將日期/時間顯示在 LCM
        - 第一行顯示日期/時間： 月/日與時/分/秒，例：`05/09   05:08:06`
        - 碼錶功能規格：
            1. 按下 BTN1 進入碼錶功能，第二行顯示碼錶計時顯示及狀態，計時顯示在最左邊，格式為 00:00:00 (時:分:秒)，最右邊顯示 StopWatch 狀態
            2. 按下 BTN4 碼錶開始計時，最右邊顯示 Counting 狀態
                - 再按一次 BTN4，暫停碼錶計時，最右邊顯示 Stop 狀態
                - 在 Stop 狀態，再按一次 BTN4，碼錶繼續計時，依此類推
            3. 按 BTN2，碼錶計時重設為 00:00:00，最右邊顯示 StopWatch 狀態
            4. 計時過程中，如按下 BTN3，結束碼錶計時；第二列清空