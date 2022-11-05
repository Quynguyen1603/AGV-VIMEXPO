#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

uint8_t broadcastAddress[] = {0x24, 0x4C, 0xAB, 0x33, 0x7B, 0xB4};
String success;
String incommess;

//////////////////
int AdminCommand;
int NextCommand;
int StepNum;
String Step1;
String Step2;


/////Send data structure/////////
typedef struct send_message {
char AGVID[5] = "AGV1";
int AGVMode;
int AGVStatus ;
int AGVPacStatus ;
int AGVErrorCode;
int AGVBattery;
int AGVSpeed = 100 ;
char AGVRFIDRead[3];
char AGVNextRFID[3];
int AGVStepStatus;
int AGVCurrentStep;
} send_message;
send_message Sendmess;

///Receive data structure////////////
typedef struct receive_message {
int AGVAdminCommand = 0;
int AGVNextCommand = 0;
int AGVStepNum =0;
char AGVStep1[5] = "  " ;
char AGVStep2[5] = "  " ;
} receive_message;
receive_message Receivemess;


esp_now_peer_info_t peerInfo;


// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // Serial.print("\r\nLast Packet Send Status:\t");
  // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  memcpy(&Receivemess, incomingData, sizeof(Receivemess));
  Serial.print("Bytes received: ");
  Serial.println(len);
  ///////////////////////////////////Thu thap du lieu o day
  NextCommand = Receivemess.AGVNextCommand; 
  // Serial.println ("Next la:"+ (String)NextCommand);
  if (NextCommand ==0 )
  {
    AdminCommand = Receivemess.AGVAdminCommand;  
    StepNum = Receivemess.AGVStepNum;
    Step1 = Receivemess.AGVStep1;
    Step2 = Receivemess.AGVStep2;
  }  
  Serial.println ("Lenh la:"+ (String)AdminCommand);
  Serial.println ("Next la:"+ (String)NextCommand);
  Serial.println ("So buoc:"+ (String)StepNum);
  Serial.println ("Buoc 1:"+ (String)Step1);
  Serial.println ("Buoc 2:"+ (String)Step2);
  Serial.println ("Current Step:"+ (String)CurrentStep);      
  Serial.println ("RunOneBit1:"+ (String)RunOneBit1);    
  Serial.println ("Mode la:"+ (String)AdminCommand_Mode);  
  Serial.println ("********");    
}

void ESP_NOW_define()
{
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);  
}

void Send_to_Center_Control ()
{   
    char AGVID[5];
    char AGVRFIDRead_c[3];
    char AGVNextRFID_c[3];    
    // char RFID1[5] ;
    // char RFID2[5] ;
    strcpy(AGVRFIDRead_c, AGVRFIDRead.c_str());
    strcpy(AGVNextRFID_c, AGVNextRFID.c_str());

    // Sendmess.AGVAdminCommand = AdminCM;
    // Sendmess.AGVStepNum = StepNum;
    // strncpy(Sendmess.AGVStep1,RFID1,sizeof(Sendmess.AGVStep1));
    // strncpy(Sendmess.AGVStep2,RFID2,sizeof(Sendmess.AGVStep2));
    Sendmess.AGVMode  = AGVMode.toInt();
    Sendmess.AGVStatus =  AGVStatus.toInt();
    Sendmess.AGVPacStatus =  AGVPacStatus.toInt(); 
    Sendmess.AGVErrorCode =  AGVErrorCode.toInt();
    Sendmess.AGVBattery =  AGVBattery.toInt();
    Sendmess.AGVSpeed =  AGVSpeed.toInt();
    Sendmess.AGVStepStatus =  AGVStepStatus.toInt();
    Sendmess.AGVCurrentStep =  CurrentStep;
    strncpy(Sendmess.AGVRFIDRead,AGVRFIDRead_c,sizeof(Sendmess.AGVRFIDRead));
    strncpy(Sendmess.AGVNextRFID,AGVNextRFID_c,sizeof(Sendmess.AGVNextRFID));    
      // Serial.println ("Dung luong:" + (String)sizeof(Sendmess));
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&Sendmess, sizeof(Sendmess));         
}
