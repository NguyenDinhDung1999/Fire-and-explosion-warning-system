// khai bao thu vien
#define BLYNK_PRINT Serial  
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
//Mã template va token cua du an
#define BLYNK_TEMPLATE_ID "TMPL65iykWTlj"
#define BLYNK_TEMPLATE_NAME "Báo cháy"
#define BLYNK_AUTH_TOKEN "VWtR6g3V5MYbT6x3uz7q1xg279ZwlGzi"
// khai báo chân module và tên biến
int Cbkhoi = 16;
int Khoi;
int Cblua = 5;
int Lua;
int Relay_Quat=14;
int Relay_Bom=12;
int Coi=4;
int chedo,button_bom,button_quat;
int a;
int b;
// khai báo wifi
char ssid[] = "DuongDat";
char pass[] = "12345678a";

void setup()
{

  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2500L, notifyOnFire);
  // khai báo thiết bị vào thiết bị ra
  pinMode(Cbkhoi, INPUT);
  pinMode(Cblua, INPUT);
  pinMode(Relay_Quat,OUTPUT);
  digitalWrite(Relay_Quat, LOW);
  pinMode(Relay_Bom,OUTPUT);
  digitalWrite(Relay_Bom, LOW);
  pinMode(Coi, OUTPUT);
  // khởi tạo các chân blynk
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);

}

  BLYNK_WRITE(V1){
    button_bom = param.asInt();
 }
  BLYNK_WRITE(V0){
    chedo = param.asInt();
 }
  BLYNK_WRITE(V2){
    button_quat = param.asInt();
 }
 // khởi tạo hàm con thông báo về điện thoại và gửi email
 void notifyOnFire()
{
 
  if (Lua==1 && a==0) {
    Serial.println("Xuất hiện lửa");
     //Blynk.email("duongdatks90@gmail.com", "Xuất hiện lửa");
     Blynk.logEvent("chay","Xuất hiện lửa");
    a=1;
  }
  else if (Lua==0)
  {
    a=0;
  }
  if (Khoi==0 && b==0) {
    Serial.println("Xuất hiện khói");
     //Blynk.email("duongdatks90@gmail.com", "Phát hiện khói");
     Blynk.logEvent("khoi","Phát hiện khói");
    b=1;
  }
  else if (Khoi==1)
  {
    b=0;
  }
}

void loop()
{
  Blynk.run();
  timer.run();
  Khoi=digitalRead(Cbkhoi);
  Lua=digitalRead(Cblua);
  

// tạo chế độ tự động và thủ công 
if(chedo == 0)
 {
  if (Khoi == 0 || Lua == 1 ){
    digitalWrite(Coi, HIGH); 
  } else {
    digitalWrite(Coi, LOW);
  }
  if (Lua==1 )
{digitalWrite(Relay_Bom,HIGH);

}
else
{digitalWrite(Relay_Bom,LOW);
}
if (Khoi==0)
{digitalWrite(Relay_Quat,HIGH);
}
else
{digitalWrite(Relay_Quat,LOW);
}
 }
 else
 {
  digitalWrite(Coi,LOW);

  
  if (button_quat == 1)
  {
    digitalWrite(Relay_Quat,HIGH); 
  }
  else
  {
    digitalWrite(Relay_Quat,LOW);
  }
  if (button_bom == 1)
  {
    digitalWrite(Relay_Bom,HIGH);
  }
  else
  {
    digitalWrite(Relay_Bom,LOW);
  }
 }

}
