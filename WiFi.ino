// #include "Portfolio.h"
#include "nowSrvr32.h"

IPAddress local_IP();
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS( 75, 153, 171, 67 );
IPAddress secondaryDNS( 75, 153, 171, 116 );

int WiFiSetup() {
  Serial.println("\nWiFiSetup\n");
  int LCnt = 0;
//  WiFi.persistent(false);
  WiFi.disconnect();
//  WiFi.persistent( true );
  WiFi.mode( WIFI_AP_STA );
//    WiFi.printDiag(Serial); // Uncomment to verify channel number before
//  esp_wifi_set_promiscuous(true);
//  esp_wifi_set_channel(11, WIFI_SECOND_CHAN_NONE);
//  esp_wifi_set_promiscuous(false);
//  esp_wifi_set_mac( WIFI_IF_STA, SRVs_mac );
//  WiFi.printDiag(Serial);
//  WiFi.hostname( "ESP32-S3" );

/**** /
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure Static IP");
  }
/ *****/

  WiFi.begin( config.ssid, config.pword );

 while (WiFi.status() != WL_CONNECTED) {
    delay(200);   LCnt++; // LCDspin();
    Serial.print(".");
    if( LCnt > 99 ) { strcpy( BADpword, config.pword ); return -1; }
  }

  Serial.printf("\n\nWiFi connected in %d \nIP address: ", LCnt );
  Serial.println(WiFi.localIP());
  Serial.printf("WiFi Ch = %d\n", WiFi.channel() );
  Serial.printf( "IP.5 = %X\n", local_IP[3] );
  return 0;
}

void GetCreds() {

  int ccd = 0;
  
  Serial.print("\nConfiguring access point...\n");
  WiFi.softAP( "Info" );
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

//  LCD("Connect to WiFi",true);
//  LCD("\"InfoCentre\"",0,1);

  delay( 200 );
Serial.println(WiFi.softAPgetStationNum());
while( !ccd ) {  
//  Serial.printf("%d ", ccd );
  ccd = WiFi.softAPgetStationNum();
  delay( 1200 );
//  LCDspin();
              }
     printf("\n%d Clients connected\n", WiFi.softAPgetStationNum() );
#ifdef use_LCD                
lcd.setCursor( 4, 3 );
lcd.print("Connected !!");
   delay( 2000 );

    lcd.clear();

    lcd.print("Go to http://");
    lcd.setCursor(2,1);
    lcd.print( myIP );
#endif  //  use_LCD
    server.begin();
    Serial.println("AP server started");
}
