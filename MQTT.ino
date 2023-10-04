#include "nowSrvr32.h"

#ifdef use_MQTT

#include <PubSubClient.h>

const char* mqtt_server = "192.168.0.30";

// WiFiClient client;
PubSubClient MQTTclient( client );
char *msg;  //  [MSG_BUFFER_SIZE];

/*****

  randomSeed(micros());

****/
// void callback(char* topic, byte* payload, unsigned int length) {
void callback(char* topic, uint8_t *payload, unsigned int length) {
//  Serial.print("Message arrived [");
//  Serial.print( topic );
//  Serial.print("] ");
//  payload[length] = 0;
//  Serial.println( (char *)payload );
//  Sofa = String( (char *)payload ); 
/****

  if ( !(strcmp( topic, "Fan/POWER" ) ) ) {
    printf("top = Fan Power\n");
    FanST = "";
    for (int i = 0; i < length; i++) {
      Serial.print( (char)payload[i] );
      FanST += (char)payload[i];
    }
    Serial.println();
  }

  if ( !(strcmp( topic, "Dummy/SENSOR" ) ) ) {
    Serial.printf("Dum SENSOR\n");
    String TP = "";
//    payload[ length ] = 0;
    for (int i = 0; i < length; i++) {
      Serial.print( (char)payload[i] );
      TP += (char)payload[i];
    }

    TEMP = TP.substring( 53, 57 );
    int TrueTemp = TP.substring( 53, 55 ).toInt() * 10;
//    int TTemp = TP.substring( 56,57 ).toInt();
//    TrueTemp += TP.substring( 56, 57 ).toInt() - 240;
  printf("\nTEMP = %s\n", TEMP.c_str() );
//  TimeFromTasmota( TIME );
    if ( TrueTemp > config.Therm.toInt() ) {
      printf("Turn Fan ON at: %d\n", TrueTemp );
//      PendMsg = "ON"; PendTopic = "Fan/cmnd/POWER";
    }
    if ( TrueTemp < config.Therm.toInt() ) {
      printf("Turn Fan OFF at: %d\n", TrueTemp );

//      PendMsg = "OFF"; PendTopic = "Fan/cmnd/POWER";
    }
  }
 
  if ( !(strcmp( topic, "Sofa/POWER" ) ) ) {
    printf("topic = %s  --  ", topic);
    printf("payload = %s\n", payload );
  String PLtmp = "";
//    payload[ 5 ] = 0;
    //   SofaST = "";
    for (int i = 0; i < length; i++) {
        Serial.print( (char)payload[i] );
    PLtmp += (char)payload[i];
      }
//      PLtmp += "";
      Serial.print( "\nPLt = " );
      Serial.println( PLtmp );
      Serial.printf( "Index of ON = %d\n", PLtmp.indexOf( "ON" ) );
      Serial.println( Sofa );

 if( PLtmp.indexOf( "ON" ) > 5 ) {
    PendTim = PLtmp.substring( 0,5 );
//    PendTimTopic = "Sofa/cmnd/Timer1";
                                }
  }
*****/ 
  if ( !(strcmp( topic, "Sofa/POWER" ) ) ) {
//    Serial.printf("topic = %s == ", topic );
    payload[ length ] = 0;
//    Serial.printf("payload = %s\n", payload );
String SofaTmp = "0Sofa";     
//    Sofa = String(  (char)payload[1] + SofaTmp );  //   + "000";
//    Serial.printf( "Sofa = %s\n", Sofa );
  }

 /****
  if ( !(strcmp( topic, "BedSide/POWER" ) ) ) {
    Serial.printf("top = BedSide Power\n");
    payload[ length ] = 0;
    //   BedST = "";
    //  for (int i = 0; i < length; i++) {
    //    Serial.print( (char)payload[i] );
    BedSide = (char *)payload;
    //  }
    Serial.println( (char *)payload );
//    Serial.println( BedST );
  }
  
  if ( !(strcmp( topic, "Dummy/POWER" ) ) ) {
    Serial.printf("top = Dum Power\n");
    payload[ length ] = 0;
    //   BedST = "";
    //  for (int i = 0; i < length; i++) {
    //    Serial.print( (char)payload[i] );
    DummyST = (char *)payload;
    //  }
    Serial.print( "DState = " );
    Serial.println( DummyST );
  }

  if ( !(strcmp( topic, "Temp/LOGGING" ) ) ) {
    printf("top = Temp/LOGGING\n");

    for (int i = 0; i < length; i++) {
        Serial.print( (char)payload[i] );
//    TempLOG += (char *)payload[i];
      }
   }
*****/
}

void reconnect() {
  if (!MQTTclient.connected()) {
    Serial.print("Attempting MQTT connection... ");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (MQTTclient.connect(clientId.c_str())) {
//      Serial.println("MQTTconnected");
      // Once connected, publish an announcement...
//      MQTTclient.publish("Table/cmnd/POWER", TableST.c_str(), true );
//      MQTTclient.publish("Fan/cmnd/POWER", FanST.c_str(), true );
      // ... and resubscribe
//      MQTTclient.subscribe("Sofa/#");
//      MQTTclient.subscribe("Table/POWER");
      MQTTclient.subscribe("Sofa/POWER");

/***      MQTTclient.subscribe("Temp/SENSOR");


      MQTTclient.subscribe("Dummy/POWER");
      MQTTclient.subscribe("Sofa/LOGGING");
****/      
    } else {
      Serial.print("failed, rc=");
      Serial.print(MQTTclient.state());
#ifdef use_LCD
      LCD( "MQTT Err", 0, 1, true );
#endif      
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void MQTTsetup() {
  randomSeed(micros()); 
  MQTTclient.setServer(mqtt_server, 1883);
  MQTTclient.setCallback(callback);
  MQTTclient.subscribe("Sofa/#");
      reconnect();
 
  printf("MQTT set up with %s\n\n", mqtt_server );
//  digitalWrite( BUILTIN_LED, LOW );

}

void MQTTloop() {

  if (!MQTTclient.connected()) {
    Serial.println("MQTTloop: re-connecting");
//    delay( 30000 );
    reconnect();
  }

//  if ( PendTopic.length() ) {
//    printf("doing Pendings\n");
//    Pub( PendTopic, PendMsg );
//    PendTopic = "";
//  }
/***
  if ( PendTimTopic.length() ) {
 Serial.print( PendTimTopic );
 Serial.printf(" -->  PendTim = %s\n", PendTim );
 char c = PendTim.charAt(4);
Serial.printf("charAt( 3 ) = %c\n", c  );
if( c < '9' ) { PendTim.setCharAt( 4, c+2 ); }
else { PendTim.setCharAt( 1, PendTim.charAt(1)+1 ); PendTim.setCharAt( 3, '0' ); }


/****  Set TimerX Dum/cmnd/Timer1  ---- > **** /
String TStg0 = "{\"Arm\":1,\"Mode\":0,\"Time\":\"";
// 09:06
String TStg1 = "\",\"Window\":1,\"Days\":\"1111111\",\"Repeat\":0,\"Output\":1,\"Action\":1}";
 
    printf("doing Pend Timings\n");
    Pub( PendTimTopic, TStg0+PendTim+TStg1 );
    PendTimTopic = "";
    }
****/
    MQTTclient.publish( "Sofa/cmnd/POWER", " " );
  MQTTclient.loop();


}

void Pub( String Topic, String Msg ) {
//  MQTTclient.publish( "Sofa/cmnd/POWER", "" );
    MQTTclient.publish( Topic.c_str(), Msg.c_str() );
  Serial.printf("Pub..ed %s to %s\n", Msg.c_str(), Topic.c_str() );
}

#endif  //  use_MQTT
