#include "nowSrvr32.h"
//#include <Arduino.h>

uint8_t Buf[2048];  //  , tmp[32];
bool    Wupdate = false, W__ON = false, FCupdate=false, Tupdate=false;
bool    NTPupdate = false, T_ON = false, P_ON = false, TimeSync=true;
// bool    YahoLoop = true;
 
TaskHandle_t NTP_Tk_h = NULL;
TaskHandle_t WthDsp_Tk_h = NULL;
TaskHandle_t Radio_Tk_h = NULL;

void setup() {
  Serial.begin(115200);
  Serial.printf("\n\n %s Reporting...\n", __FILE__ );

  FSbegin( );
  listDir( "/" );
// updateRead( &config, "config.dat", configLEN );
// FSRead( "/index.html", true );

printf("ESP32 WiFi = %s %s\n", config.ssid, config.pword );

// printf("config.disp_rows = %d\n", config.disp_rows );
// printf("config.t_on = %d\n", config.t_on );
// printf("config.w_on = %d\n", config.w_on );
// printf("BADpword = %s\n", BADpword );
// LCDstart();

  while( false ) { //WiFiSetup() == -1 ) {
    sprintf( tmp, "WiFi Error: %s", config.ssid );
    Serial.printf( "\n%s : %s\n", tmp, config.pword );
#ifdef use_LCD    
    lcd.clear( );
    lcd.print( tmp );
    lcd.setCursor( 0,1 );
    lcd.print( "Connect Device");
    lcd.setCursor( 0,2 );
    lcd.print( "to router \"Info\"");
#endif //  use_LCD       
    GetCreds();
delay( 200 );
  WebServerSetup();
  Serial.printf( "BPass = %s, GPass = %s ", BADpword, config.pword );
  while( !strcmp( BADpword, config.pword ) ) {
//    Serial.printf( "BPass = %s, GPass = %s ", BADpword, config.pword );
//    LCDspin();
    delay( 400 );
        }
  }

  DualInit();
  NOWsetup();

#ifdef use_MQTT
  MQTTsetup();
#endif  
//  lcd.clear();    
//  LCD("WiFi Connected",2, 0 );  //  config.disp_rows - 1 );
//  LCD("to configure go to:", 0, 1);
//  LCD("http://", 0, 3);
//  lcd.setCursor( 0, 3 );  //  config.disp_cols - 4, config.disp_rows - 1 );
//  lcd.print( WiFi.localIP() );
//  lcd.print("  ");
OTAsetup();
vTaskDelay( 200 );
  WebServerSetup();
  server.begin( );
  Serial.println("STA server started");
//  pinMode( BUILTIN_LED, OUTPUT );
//  digitalWrite( BUILTIN_LED, HIGH );

// DispTimeMAX( 1 );

for( int x=0; x<weather_info.num_cities; x++ ) {
// Wupdater();  //  do pre-update
}
// lcd.clear();
#ifdef use_NTP 
    xTaskCreate( NTP_Tk,    "NTP",    4096, NULL, 1, &NTP_Tk_h );
#endif
#ifdef use_WEATH     
    xTaskCreate( WthDsp_Tk, "WthDsp", 4096, NULL, 1, &WthDsp_Tk_h );
// #ifdef use_
    xTaskCreate( WthUpd_Tk, "WthUpd", 8096, NULL, 1, NULL );
// #endif
#endif
//  xTaskCreate( Radio_Tk,  "Player", 12096, NULL, 1, &Radio_Tk_h );

}

char *tmpp = "Tmpp\00";

void loop() {
  if( tmpp[0] == 'N' ) { tmpp[0] = 'F'; }
  else { tmpp[0] = 'N'; }
//  NOWsend( 7, tmpp );

//  NOWsend( 3, tmpp );
//  delay( 5000 );
#ifdef use_MQTT
  MQTTloop();
#endif 
// NOWloop();
  NowDelay();  //  For Timed "Boxes"
//time_loop();   
//  vTaskDelay( 5000 );
// Serial.printf("0x%X, 0x%X, 0x%X, 0x%X\n", InStatus[1], InStatus[3], InStatus[5], InStatus[7] ); 
OTAloop();
  delay( 1000 );
}
