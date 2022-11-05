#include "WString.h"
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

uint8_t broadcastAddress[] = {0x78, 0xE3, 0x6D, 0x0E, 0xD8, 0xBC};
String success;
String incommess;

//////////////Data receive/////////
String DATAID;
int DATAMode;
int DATAStatus ;
int DATAPacStatus;
String DATAErrorCode;
int DATASpeed ;
int DATABattery;
String DATARFIDRead;
String DATANextRFID;
int DATAStepStatus;
int DATACurrentStep;

/////Receive data structure/////////
typedef struct receive_message {
char AGVID[5];
int AGVMode;
int AGVStatus ;
int AGVPacStatus ;
int AGVErrorCode;
int AGVBattery;
int AGVSpeed ;
char AGVRFIDRead[3];
char AGVNextRFID[3];
int AGVStepStatus;
int AGVCurrentStep;
} receive_message;
receive_message Receivemess;

///Send data structure////////////
typedef struct send_message {
int AGVAdminCommand = 0;
int AGVNextCommand = 0;
int AGVStepNum =0;
char AGVStep1[5] = "  " ;
char AGVStep2[5] = "  " ;
} send_message;


send_message Sendmess;

esp_now_peer_info_t peerInfo;



// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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

  DATAID = Receivemess.AGVID;
  DATAMode =Receivemess.AGVMode;
  DATAStatus = Receivemess.AGVStatus;
  DATAErrorCode = Receivemess.AGVErrorCode;
  DATAPacStatus = Receivemess.AGVPacStatus;
  DATABattery = Receivemess.AGVBattery;
  DATASpeed = Receivemess.AGVSpeed;
  DATARFIDRead = Receivemess.AGVRFIDRead;
  DATANextRFID = Receivemess.AGVNextRFID;
  DATAStepStatus = Receivemess.AGVStepStatus;
  DATACurrentStep = Receivemess.AGVCurrentStep; 

  Serial.println ("ID:"+ (String)DATAID);
  Serial.println ("Mode:"+ (String)DATAMode);
  Serial.println ("Status:"+ (String)DATAStatus);
  Serial.println ("PacStatus:"+ (String)DATAPacStatus);
  Serial.println ("ERC:"+ (String)DATAErrorCode);
  Serial.println ("Battery:"+ (String)DATABattery);
  Serial.println ("Speed:"+ (String)DATASpeed);
  Serial.println ("RFIDRead:"+ (String)DATARFIDRead);
  Serial.println ("Speed:"+ (String)DATASpeed);
  Serial.println ("NextRFID:"+ (String)DATANextRFID);  
  Serial.println ("StepStatus:"+ (String)DATAStepStatus);
  Serial.println ("C-Step:"+ (String)DATACurrentStep);
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
void Send_to_AGV (int AdminCM,int StepNum,int NextCM, String RFIDCode1, String RFIDCode2)
{
    char RFID1[5] ;
    char RFID2[5] ;
    strcpy(RFID1, RFIDCode1.c_str());
    strcpy(RFID2, RFIDCode2.c_str());

    Sendmess.AGVAdminCommand = AdminCM;
    Sendmess.AGVNextCommand = NextCM;
    Serial.println ("Next:"+ (String)NextCM);
    Sendmess.AGVStepNum = StepNum;
    strncpy(Sendmess.AGVStep1,RFID1,sizeof(Sendmess.AGVStep1));
    strncpy(Sendmess.AGVStep2,RFID2,sizeof(Sendmess.AGVStep2));

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &Sendmess, sizeof(Sendmess));         
}
