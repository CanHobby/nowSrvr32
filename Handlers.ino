// #include <FS.h>
#include "nowSrvr32.h"
#include <iostream>
#include <string.h>
using namespace std;

const char *txthtm = "text/html";
char *buf = "\000\000";

void WebServerSetup() {

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send( SPIFFS, "/index.html", "text/html" );
    printf( "serving %s\n", "index.html" );
  });
  /******/
  server.on("/State.htm", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/State.htm", String(), false, processor);
    printf( "serving %s\n", "State.htm" );
  });

  server.on("/getStatus.htm", HTTP_GET, [](AsyncWebServerRequest * request) {
//        Serial.printf( "serving getStatus.htm\n" );
        request->send( SPIFFS, "/getStatus.htm", String(), false, processor );
  });

  server.on("/getSt.htm", HTTP_GET, [](AsyncWebServerRequest * request) {
        Serial.printf( "serving getSt.htm\n" );
        request->send( SPIFFS, "/getSt.htm", String(), false, processor );
//          request->send( 200, "text/html", "{ \"UpDate\":\"null\" }" ); }                        
  });

  server.on("/faviXXXcon.ico", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send( SPIFFS, "/favicon.ico", "image/gif", false );
    printf( "serving /favicon.ico\n" );
  });
  /***/
  server.on("/IC", HTTP_GET, [](AsyncWebServerRequest * request) {
    handleAll( request );
    //    printf("serving 31 IC\n");
  });

  server.on("/diyStyle.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/diyStyle.css", "text/css"  , false );
    printf("serving diyStyle.css\n");
  });

  server.on("/setup.htm", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/setup.htm", "text/html"  , false );
    printf("serving setup.htm\n");
  });

      server.on("/AHA.htm", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/AHA.htm", "text/html"  , false );
      printf("serving AHA.htm\n");
    });

      server.on("/Boxes.js", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/Boxes.js", "text/javascript"  , false );
      printf("serving Boxes.js\n");
    });

  server.on("/jquery-3.6.0.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "jquery-3.6.0.min.js", "text/javascript"  , false );
    printf("serving jquery-3.6.0.min..js\n");
  });

  server.on("/getParams.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "getParams.js", "text/html"  , false );
    printf("serving getParams.js\n");
  });
    Serial.println( "Web Server has been Set Up");
}

void handleAll( AsyncWebServerRequest *request ) {
  int x, ACnt = request->args( );
  String fff = "";

  //  Serial.printf( "HAll - ACnt = %d\n", ACnt );

  if ( ACnt == 0 ) { // request->send( SPIFFS, "index.html", txthtm, false );
    Serial.printf( "ACnt = %d\n", ACnt );
  }

  if ( ACnt > 0 ) {


    if (request->hasParam( "cSSID" )) {
      Serial.printf( "has Param cSSID = " );
      Serial.println( request->getParam( "cSSID" )->value() );
      strcpy( config.ssid, request->getParam( "cSSID" )->value().c_str() );
    }

    if (request->hasParam( "cpWord" )) {
      Serial.printf( "has Param cpWord = " );
      Serial.println( request->getParam( "cpWord" )->value() );
      strcpy( config.pword, request->getParam( "cpWord" )->value().c_str() );
    }

    if (request->hasParam( "page" )) {
      fff = request->getParam( "page" )->value() + ".htm";
      Serial.printf( "has Param page = " );
      Serial.println( fff );
    }

    if (request->hasParam( "disptype" )) {
      Serial.printf( "has Param disptype = " );
      String disp;
      disp = request->getParam( "disptype" )->value();
      Serial.println( disp );  Serial.println( disp.substring(3, 5).toInt() );
      //    strcpy( config.disptype, disp.c_str() );
      config.disp_cols = disp.substring(3, 5).toInt();
      config.disp_rows = disp.substring(5, 7).toInt();
//      EEPROM.put( 0, config );
//      boolean ok = EEPROM.commit();
//      Serial.println((ok) ? "EEPROM Commit OK" : "EEPROM Commit failed");
    }

    if (request->hasParam( "flash" )) {
      Serial.printf( "has Param flash = " );
      Serial.println( request->getParam( "flash" )->value() );
      updateWrite( &config, configLEN, "config.dat" );
    }

    if (request->hasParam( "UPD" ) ) {
 /***  BroadCast Test   **** /     
        String STG = "Suku";
        Serial.printf( "has Param UPD Now sending %s\n", STG );
        NOWsend( 255, STG );
 / ***  BroadCast Test   ****/ 
    }
    
    if (request->hasParam( "NOW" )) {

      String ADR = request->getParam( "NOW" )->value();
      String MSG = request->getParam( "MSG" )->value();
      String TO  = request->getParam( "TO" )->value();
      String ID  = request->getParam( "ID" )->value();

      Serial.print( "\nhas Param NOW ADR = " );
      Serial.printf( "%s MSG = %s TO = ", ADR, MSG );
      Serial.printf( "%s : ms = %d\n", TO, millis() / 1000 );

      if ( TO.toInt() == 0 ) { Serial.println( "No TO" );
        if ( ADR.toInt() ) {
          NOWsend( ADR.toInt(), MSG );
          vars[ ADR.toInt() ] = MSG;
             }
        else {
#ifdef use_MQTT          
          Pub( ADR + String("/cmnd/POWER"), MSG );
          Sofa = MSG[1] + String("6Sofa"); // = Coffee = MSG[1]; // Sofa = MSG[1];
#endif          
          }
      } else { 
        TimeQ[TQidx].Device  = ADR;
        TimeQ[TQidx].Command = MSG;
        TimeQ[TQidx].timeout = millis() / 1000 + TO.toInt();
        TQidx++;
        Serial.printf( "Processing TO TQidx = %d\n", TQidx );
      }

    }

    if (request->hasParam( "state" )) {

//      pushQue( request->getParam( "state" )->value() ); // , request->getParam( "MSG" )->value() );

      //    PendMsg   = request->getParam( "state" )->value();
      //    PendTopic = request->getParam( "ID" )->value()+"/cmnd/POWER";
      Serial.printf( "has Param state = " );
      Serial.printf( "%s ID = %s\n", PendMsg, request->getParam( "ID" )->value() );
    }

    if (request->hasParam( "config" )) {
      if ( request->getParam( "cfg" )->value() == "Therm" ) {
        config.Therm = request->getParam( "value" )->value();
      }
      Serial.printf( "has Param config = " );
      Serial.printf( "cfg = %s\n", request->getParam( "value" )->value() );
    }

    if ( fff.compareTo( "IC") ) {
      request->send( SPIFFS, fff, "text/html", false, processor );
      //  printf("serving 125 %s\n", fff.c_str() );
    }
  }  //  if ACnt > 0
}  //  end handleAll

void UpDater( int ACnt, String Params[4][2] ) {

  Serial.printf( "Update %s to ", Params[1][0] );
  Serial.printf( "%s\n", Params[1][1] );

  //  if( Params[1][0] == "SSID"  ) strcpy( config.ssid , Params[1][1].c_str() );
  //  if( Params[2][0] == "pWord" ) strcpy( config.pword, Params[2][1].c_str() );

}

////////*
// Replaces placeholder with button section in your web page
String processor(const String& var) {
  char buf[256];
//    Serial.printf( "Processor engaged: var = %s\n", var.c_str() );

  if ( var.toInt() ) {
    return vars[ var.toInt() ];  //  String(InStatus[ TOven_MAC[5] ]);
      }
  if (var == "Sofa") {
    return Sofa;
    }
  if (var == "Coffee") {
    return Coffee;
  }
  if (var == "Temp") {
    sprintf( buf, "%.0f", city.temp[0] );
    return buf;
  }
  if (var == "Temp_min") {
    sprintf( buf, "%.0f", city.temp_min[0] );
    return buf;
  }
  if (var == "Temp_max") {
    sprintf( buf, "%.0f", city.temp_max[0] );
    return buf;
  }
  if (var == "Icon") {
    return city.icon[0];
  }     
  if (var == "Chill") {
    sprintf( buf, "%.0f", city.chill[0] );
    return buf;
  }  
  if (var == "Wind") {
    sprintf( buf, "%d", city.wind[ 0 ] );
//    Serial.printf("H231 wind = %d\n", city.wind[ 0 ] );
  return buf;
  }
/****  
  if (var == "FANSTATUS") {
    return FanST;
  }
  if (var == "SENSOR") {
    return TEMP;
  }
  if (var == "BEDSIDE") {
    return BedST;
  }
  if (var == "Therm") {
    return config.Therm;
  }
  if (var == "DUMMY") {
    return DummyST;
  }
 
  }
****/ 
  return String();
}

void handleConfig( AsyncWebServerRequest *request ) {
  printf("handleConfig: config.ssid = %s config.pword = %s\n", config.ssid, config.pword );
  //printf("arg 0 = %s\n", request->arg( 0 ) );

  int i = 0;
  //  strcpy( config.disptype, request->arg( i ).c_str()  );
  //  i++;
  //  strcpy( config.pword, request->arg( i ).c_str() );

  //    printf("handleConfig: config.disp_rows = %d config.pword = ??\n", config.disp_rows );

  //  updateWrite( &config, configLEN, "config.dat" );

}

String proc_Emp( String var ) {

  String retn = "Tetis Did it!";

  return retn;

}

String proc_Ports( String var ) {

  String retn = "proc_Ports";

  return retn;

}

void handleEMP( AsyncWebServerRequest *request ) {

}

void handlePorts( AsyncWebServerRequest *request ) {

}

void handleWiFi( AsyncWebServerRequest *request ) {
  printf("handleWiFi: config.ssid = %s config.pword = %s\n", config.ssid, config.pword );
  int i = 0;
  //  strcpy( config.ssid, request->arg( i ).c_str() );
  i++;
  //  strcpy( config.pword, request->arg( i ).c_str() );

  printf("handleWiFi: config.ssid = %s config.pword = %s\n", config.ssid, config.pword );

  updateWrite( &config, configLEN, "config.dat" );

}

void updateWrite( void *strct, int len, char *dat ) {
  File f;
  memcpy( Buf, strct, len );
  Serial.printf("UpDate %s with %d bytes\n", dat, len );
  f = SPIFFS.open( dat, "w");
  Serial.printf("Buf = %s\n", Buf );
  f.write( Buf, len );    delay( 100 );
  f.close();
  //  delay( 500 );
}

void updateRead( void *strct, char *dat, int len ) {
  File f;
  f = SPIFFS.open( dat, "r");
  f.read( Buf, len );
  f.close();
  memcpy( strct, Buf, len );
}

String getStatus() {
  return FanST;
}
