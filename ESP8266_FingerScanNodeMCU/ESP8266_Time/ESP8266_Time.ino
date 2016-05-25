#include <ESP8266WiFi.h>
#include <time.h>
#include "LedControl.h"
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "FS.h"

// vvvv setup Wifi vvvv
const char* ssid = "ON_Home";
const char* password = "044349220";
// ^^^^ setup Wifi ^^^^

void setupSerial();
void setupLED();
void setupTime();
void setupWifi();
void setupSD_card();
void setupFingerprint();
void setupButton();
void setupJson();

void Serial_print(String text);
void Serial_println(String text);
void Serial_print(int text);
void Serial_println(int text);
void Serial_print(char text);
void Serial_println(char text);

void getTime(); // ดึงเวลาจากอินเทอร์เน็ตมา

void showTimeLED(); //สั่งให้แสดงเวลา
void showLED(int address, int number); //ให้เลือกตำแหน่ง ที่ให้แสดงตัวเลข และแสดงเลขอะไร
void clearLED(); // เคลียร์หน้าจอ LED

void SD_write_to(String Flie_name , String Text_to_write); //เขียนไฟล์
void SD_read(String Flie_name); //อ่านไฟล์
void SD_remove(String Flie_name); //ลบไฟล์

int check_puse_button(); //ตรวจสอบการกดปุ่ม
void Puse_2_button(); //ถ้ากดสองปุ่มพร้อมกัน
void Puse_bt1(); //ถ้ากดปุ่ม 1
void Puse_bt2(); //ถ้ากดปุ่ม 2

int get_ID_Card(); //ตรวจสอบรายนิ้วมือ
void Add_finger(int ID_add) ; //เพิ่มลายนิ้วมือใหม่

String load_name_by_position(String Find_position_is); //ค้นหาชื่อจากตำแหน่ง
bool Add_New_Name(String AddName); // เพิ่มชื่อใหม่ ต่อท้ายรายชื่อเดิมรายชื่อเดิม
bool Add_New_Name_insert(String address , String addName); //แทรกชื่อ เข้าไปในรายชื่อเดิม

void Beepshort(); //ส่งเสียงปิ๊บสั้น
void BeepTime(int Time); //ส่งเสียงปิ๊บ แบบกำหนดเวลาเอง

int T_hour;
int T_min;
int T_sec;
int T_day;
int T_mon;

int ID_Card;

int Page = 1;

bool serial = false;

int All_member_num;

void setup() {

  //setupSerial();   // <<<< Debug Mode ถ้าเปิดฟังค์ชั่นนี้ ตัวLEDจะไม่แสดงผล


  setupLED();
  setupWifi();
  setupTime();
  setupSD_card();
  setupFingerprint();
  setupButton();
  setupJson();
  Serial_println("Setup Ready");
}

void loop() {
  getTime();
  showTimeLED();


  if (check_puse_button() == 3) {
    Page = 2;
  }
  while (Page == 2) {
    int Add_member_number = All_member_num;
    clearLED();
    showLED(7, Add_member_number / 10);
    showLED(6, Add_member_number % 10);

    switch (check_puse_button()) {
      case 1:
        Add_member_number--;
        showLED(7, Add_member_number / 10);
        showLED(6, Add_member_number % 10);

        showLED(0, 9);
        showLED(1, 6);
        //        showLED(3, load_name_by_position(Add_member_number).substring(0, 1) );
        //        showLED(2, load_name_by_position(Add_member_number).substring(1, 2) );
        //        showLED(1, load_name_by_position(Add_member_number).substring(2, 3) );
        //        showLED(0, load_name_by_position(Add_member_number).substring(3, 4) );
        break;
      case 2:
        break;
      case 3:
        break;
      default:
        break;
    }

  }

  //SD_write_to("test","New one");
  //SD_read("test");


  //    Add_finger(0);

  //  if (get_ID_Card() != -1) {
  //    Beepshort();
  //    showLED(2, ID_Card);
  //  }




  delay(100);
}