#define ID   1
Modbus slave(ID, Serial1);
uint16_t MODBUS_HMI[16];
int8_t state = 0;


void HMI_Data ()
{
  LineDetect = !digitalRead (out_guide_sensor);
  //////////Line detect//////////
  if (LineDetect == 1)
  {
    bitWrite (MODBUS_HMI[0],3,1);
  }
  else
  {
    bitWrite (MODBUS_HMI[0],3,0);
  }
  ////////////Auto/Manual////////////
  //Serial.println ("Auto/Manual:" + (String)bitRead (MODBUS_HMI[0],9));
  if (bitRead (MODBUS_HMI[0],9) == 0)
  {
    Mode = 1;  //Manual
  }
  else
  {
    Mode = 2;    //Auto
  }
  if ( RFIDRead.length() >= 2)  // Nếu đọc được tag thì show ra màn hình
  {
    char A = RFIDRead [0];
    char B = RFIDRead [1];
    MODBUS_HMI[10] = A;
    MODBUS_HMI[11] = B;
  }
  else 
  {
    MODBUS_HMI[10] = '0';
    MODBUS_HMI[11] = '0';
  }
  if ( RFIDCommand.length() >= 2)  // Nếu có RFID tag lệnh được gửi show ra màn hình
  {
    bitWrite (MODBUS_HMI[0],13,1);   // Nút ready sáng
    char A = RFIDCommand [0];
    char B = RFIDCommand [1];
    char C = RFIDAction [0];
    //Serial.println ("RFIDAction" + (String)RFIDAction [0]);
    MODBUS_HMI[12] = A;
    MODBUS_HMI[13] = B;
    MODBUS_HMI[14] = C;
  }
  else 
  {
    bitWrite (MODBUS_HMI[0],13,0);  // Nút ready tắt
    MODBUS_HMI[12] = '0';
    MODBUS_HMI[13] = '0';
    MODBUS_HMI[14] = '0';
  }

  if (TogglePositive_bool(bitRead (MODBUS_HMI[0],14)) ==1 && BeginAuto == 0)
  {
    BeginAuto =1;  
  }
  else if (TogglePositive_bool(bitRead (MODBUS_HMI[0],14)) ==1 && BeginAuto == 1)
  {
    BeginAuto =0;
  }
  
  //////////////Stop/ Runiing////////////
  if (AGVSpeed == 0)
  {
    bitWrite (MODBUS_HMI[0],7,1);  ///Stop
    bitWrite (MODBUS_HMI[0],6,0);  ///Running
    RunBit = 0;
  }
  else 
  {
    bitWrite (MODBUS_HMI[0],7,0);  ///Stop
    bitWrite (MODBUS_HMI[0],6,1);  ///Running
    RunBit = 1;
  }

  ///////////////////Next///////////////
  if (bitRead (MODBUS_HMI[0],12) == 1)
  {
    
    Cmt = 1 ;
  }
  else if (bitRead (MODBUS_HMI[0],12) == 0)
  {
    
    Cmt = 0 ;
  }
  ///////////////Wifi/BLE Connected////////////
  if ( Wifi_EN  == "1")
  {
     bitWrite (MODBUS_HMI[0],1,1);
  }
  else 
  {
    bitWrite (MODBUS_HMI[0],1,0);
  }
  if ( Connected == "1")
  {
    bitWrite (MODBUS_HMI[0],2,1);
  }
  else 
  {
    bitWrite (MODBUS_HMI[0],2,0);
  }
  
}