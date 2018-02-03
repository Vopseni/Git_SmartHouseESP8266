

void setup() {

Serial.begin(115200);     // Открываем работу с COM (Serial) портом Для отладки
                            // помним про контакты GPIO 1 и 3 - они для COM порта 
}

void loop() {
unsigned long Timers_Seconds = millis()/1000;
byte Hour = Timers_Seconds/60/60;
byte Minutes = (Timers_Seconds/60)%60;
byte Seconds =T%60;
Serial.print(Hour);
Serial.print(":");
Serial.print(Minutes);
Serial.print(":");
Serial.println(Seconds);
delay (1001);
}


//Таймер работы модуля
String Timer_ESP_Sketch(){
String Time="";
unsigned long ss;
byte mm,hh;
ss=millis()/1000;
//dd=ss/86400;
hh=ss/3600;
mm=(ss-hh*3600)/60;
ss=(ss-hh*3600)-mm*60;
//if(dd<10)Time+="0";
// Time+=(String)dd+":";
if(hh<10)Time+="0";
Time+=(String)hh+":";
if(mm<10)Time+="0";
Time+=(String)mm+":";
if(ss<10)Time+="0";
Time+=(String)ss;
return Time;
}

//Подпрограмма софтовых часов с переносом данных в XML документ
String Time_Real_Sketch() {  
String Time ="";

// Софтовые часы с использование millis()
if ( (millis()-SoftTime)>1000){
SoftTime=millis();
SoftSeconds ++;
}
if (SoftSeconds>59){
SoftSeconds=0;
SoftMinutes ++;
}
if (SoftMinutes>59){
SoftMinutes=0;
SoftHour ++;
}
if (SoftHour>23){
SoftHour=0;
// Если функция millis() отраженная в переменной SoftTime пришла к своему предельному значению 4294967295 что равняется 50 дней,
// millis() автоматически сбрасывается, а к переменной SoftDate прибавляется 50 дней
if (SoftTime=4294967295){
SoftDate=SoftDate+50;
}
SoftDate++;
}
//Перенос значений в XML документ
if(SoftHour<10){ Time+="0";}    //Добавляем нолик если одна цифра
Time+=String(SoftHour)+":";
if(SoftMinutes<10){ Time+="0";} //Добавляем нолик если одна цифра
Time+=(String)SoftMinutes+":";
if(SoftSeconds<10){Time+="0";}  //Добавляем нолик если одна цифра
Time+=(String)SoftSeconds;
return Time;
}
