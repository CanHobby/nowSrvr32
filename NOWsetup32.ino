///  Set Up ESPNOW
#include "string.h"
// esp_now_peer_info_t peerInfo = {};
 uint8_t Adr_Tpl[6] = { 0, 1, 2, 3, 4, 7 };
// uint8_t Adr_Tpl[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0 };
void NOWsetup() {
  Serial.println("\nNOWsetup\n");
TimeQ[0].Device = "BedSide";
TimeQ[1].Device = "Coffee";
TimeQ[2].Device = "Two";
TimeQ[3].Device = "Three";
TimeQ[1].Command = "OFF";
TimeQ[0].timeout = 0;
TimeQ[1].timeout = 0;  // seconds
TimeQ[2].timeout = 0;
TimeQ[3].timeout = 0;

}

// callback when data is recv from Master
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int len) {
//  data[ len ] = 0;
//  Serial.printf("%s <-- %d\n", reinterpret_cast<const char*>(data), mac_addr[5] );
//  Serial.printf("%s << %X..%X\n", (char*)data, mac_addr[0], mac_addr[5] );

// vars[ mac_addr[5] ] = String( (char *)data );
  }

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status  ) {
  Serial.printf("%s ", status ? "TxFail" : "TxOK" );
  Serial.printf( " >> %X..%X\n",  mac_addr[0], mac_addr[5] );
}

void NowDelay() {
  int x;

  for( x=0; x<maxTQ; x++ ) {
 //   Serial.printf("x = %d, TimeQ[x].timeout = %d, ms = %d\n", x, TimeQ[x].timeout, millis()/1000 );

      if( TimeQ[x].timeout ) {
      Serial.printf( "NowDel Dev = %s",TimeQ[x].Device.c_str() );
      Serial.printf( " : timeout = %d : ", TimeQ[x].timeout );
      Serial.printf( "ms = %lu\n", millis()/1000 );
      }
    if( TimeQ[x].timeout ) {
      if( millis()/1000 >= TimeQ[x].timeout ) {
        printf("%s %s @ %d\n",TimeQ[x].Device.c_str(), TimeQ[x].Command.c_str(), millis()/1000 );
        TimeQ[x].timeout=0;
        if( TimeQ[x].Device.toInt() == 0 ) {
//          Pub( TimeQ[x].Device+"/cmnd/POWER", TimeQ[x].Command );
                             }
        else { NOWsend( TimeQ[x].Device.toInt(), TimeQ[x].Command ); }
        TQidx--;
    }
  }
  
  }

/****/  
//  Serial.printf( "NowDelay TQidx = %d, TO = %d, ms = %d\n", TQidx, TimeQ[TQidx].timeout, millis()/1000  );
  for( x=0; x<TQidx+1; x++ ) { // Serial.printf("x = %d\n", x );
//  if( TQidx ) {
    if( TimeQ[x].timeout ) {
      Serial.printf( "NowDelay --> %s",TimeQ[x].Device.c_str() );
      Serial.printf( " : timeout = %d : ", TimeQ[x].timeout );
      Serial.printf( "ms = %lu\n", millis()/1000 );
      if( millis()/1000 >= TimeQ[x].timeout ) {
        printf("%s %s @ %d\n",TimeQ[x].Device.c_str(), TimeQ[x].Command.c_str(), millis()/1000 );
        TimeQ[x].timeout=0;
        if( TimeQ[x].Device.toInt() == 0 ) {
Serial.printf("Alpha Device\n");          
          Pub( TimeQ[x].Device+"/cmnd/POWER", TimeQ[x].Command );

          
                             }
        else { NOWsend( TimeQ[x].Device.toInt(), TimeQ[x].Command ); }
        TQidx--;
    }
  }
 }
 /******/
}

void NOWsend( int Adr, String MsgS ) {
// Serial.printf( "Nowsend: MsgS = %s, Len = %d\n", MsgS.c_str(), MsgS.length() );

if( Adr != 255 ) { SLVa_mac[5] = Adr; }

uint8_t MsgU[ 32 ];
int x;
for( x = 0; x < MsgS.length(); x++ ) { MsgU[x] = MsgS[x]; }
MsgU[ MsgS.length() ] = 0;

 if( Adr == 255 ) { esp_now_send( BCast_MAC, MsgU, MsgS.length() );
  Serial.printf( "BCast MsgC = %s\n", MsgU );
  }
 else {
// if( esp_now_send( SLVa_mac, MsgU, MsgS.length() ) ) {
if( esp_now_send( SLVa_mac, MsgU, 2 ) ) {  //  MsgS.length() ) ) {
  Serial.printf( "NOWsend error on: %s --> %d..%d\n", MsgS, SLVa_mac[0], SLVa_mac[5] );
    }
 }

}
/***
void NOWloop() {

// popQue( );  //  &String("F2") );


String STG = "Suku";
  NOWsend( 255, STG );
  delay( 35000 );

/ ***
 STG = "Seven";
  NOWsend( STG, 7 );
  delay( 5000 );
  
  STG = "BCast";
  NOWsend( STG, 255 );
  delay( 5000 );
  **** /
}

bool popQue( ) {  //  String *Qdata ) {
  
  if( Qidx ) {
//  QUE[0] = String( "Teena" );
   Serial.printf("QLen = %d\n", QUE[ Qidx ].length() );
   Qidx--;
  *Qdata = QUE[ Qidx ];

//  memcpy( Qdata, &QUE[0][0], QUE[0].length() );
  return true; 
  }
  else { return false; }
  } 

void pushQue( String Qdata ) {
  QUE[Qidx] = Qdata;
//  Serial.print( "pushQ: Qdata = ");
//  Serial.println( Qdata );
//  Serial.printf("Len Q[0] = %d\n", QUE[Qidx].length() );
  Qidx++; 
}
****/
