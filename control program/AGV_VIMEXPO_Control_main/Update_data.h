void Update_data()  /// Hàm Cap nhat du lieu
{
    /// Nếu thay đổi Tag mới thay đổi Tag gửi
  
  Mess = ",";
  Mess += "AGV1";  ///ID
  Mess += ",";
  Mess += (String)Mode;  ///Status

  Mess += ",";
  ///Status
 Mess += (String)RunBit;

  Mess += ",";
  ///Error code
 Mess += ErrorCode;

  Mess += ",";
  /////Páctatus
 Mess += (String)AGVPacStatus;

  Mess += ",";
  ///Battery
 Mess += (String)AGVBattery;

  Mess += ",";
  ///Speed
  int Speed_Pint = map (AGVSpeed,0,2900,0,100);
 Mess += (String)Speed_Pint ;

  Mess += ",";
  
  ///RFID read code
  if (RFIDRead_sub != RFIDRead && RFIDRead.length() >=2)
  {
    RFIDRead_sub = RFIDRead;                                                        
  }
 Mess += (String)RFIDRead_sub[0];
 Mess += (String)RFIDRead_sub[1];
  // Mess += (String)"AB";
  Mess += ",";
  ///RFID status
  Mess += (String)RFIDStatus;

  Mess += "#";
  //Serial.println (Mess);


  /////////////Convert to char array/////////
  MessLen = Mess.length ();
  Mess_char[MessLen];
  Mess.toCharArray ( Mess_char, MessLen+1);

}
