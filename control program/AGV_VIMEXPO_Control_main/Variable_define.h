
///////////////Du lieu cap nhat tu ESP32///////////
String BLE_EN = "";
String Wifi_EN = "";
String Connected ="";
String AdminCommand ="0";
String AdminNext = "0";
String RFIDCommand ="";
String RFIDAction = "" ;
String RFIDRead_sub = "00";

///////////////////Du lieu cap nhat ra man hinh
int LineDetect =0;
int Mode = 0;
String RFIDRead;

bool BeginAuto;
int AGVSpeed =0;
int Cmt;
int RunBit = 0;

///////////////Du lieu cap nhat I2C
String Mess ;
char Mess_char[50];
int MessLen = 0;
String RFIDStatus= "0";
String ErrorCode ="0";
int AGVPacStatus = 0;
int AGVBattery =60;
