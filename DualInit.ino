#define I_DBG

 esp_now_peer_info_t peerInfo = {};
 
 void DualInit( ) {
  int i, role = 1;
#ifdef I_DBG  
    Serial.printf( "\nESPnow %s DualInit\n\n", role ? "Master" : "Slave" );
#endif
// Set device as a Wi-Fi AP + Station
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA );
//  WiFi.softAP( "PortFolio", "31burr0", 11 );
/***
  WiFi.begin( "VMedia", "arturoelburro" );
 delay( 800 );  
  if( role ) Serial.println("Init Master");
****/  

#ifdef ESP8266
 wifi_set_macaddr( STATION_IF, SRVs_mac );
 wifi_set_macaddr( SOFTAP_IF,  SRVa_mac );
#endif
#ifdef ESP32 
    esp_wifi_set_mac( WIFI_IF_AP,  SRVa_mac );
    esp_wifi_set_mac( WIFI_IF_STA, SRVs_mac );
#endif    

//  WiFi.disconnect();

#ifdef I_DBG
  Serial.print( "STA MAC: ");
  Serial.println( WiFi.macAddress() );
  Serial.print( "AP  MAC: ");
  Serial.println( WiFi.softAPmacAddress() );
//  WiFi.printDiag(Serial);
#endif

  int LCnt;
/**/
/***/
  WiFi.begin( config.ssid, config.pword );
 delay( 800 );  
  if( role ) Serial.println("Init Master");
//****/   
 while (WiFi.status() != WL_CONNECTED) {
    delay(200);   LCnt++; // LCDspin();
    Serial.print(".");
//    if( LCnt > 99 ) { / * strcpy( BADpword, config.pword ); * / return -1; }
  }
  Serial.printf("\n\nWiFi connected in %d \nIP address: ", LCnt );
//*****/ 
  Serial.println(WiFi.localIP());
  #ifdef use_LCD
    lcd.setCursor( 0, 3 );
    lcd.print( WiFi.localIP()[3] );
  #endif   
  Serial.println(WiFi.channel());
  WiFi.printDiag(Serial);
  Serial.println();

// Init ESP-NOW
 
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  esp_now_register_send_cb( OnDataSent );
  esp_now_register_recv_cb( OnDataRecv );
  
  // Register peer
  Serial.print("Adding Peers : ");
  memcpy( peerInfo.peer_addr, SLVa_mac, 6 );
  peerInfo.channel = 11;  //  CHANNEL; // pick a channel
  peerInfo.encrypt = 0;   //  no encryption 
  for ( i = 1; i < 0x20; i+=2 ) {
     peerInfo.peer_addr[5] = i;
     ESP_ERROR_CHECK( esp_now_add_peer( &peerInfo ) );
Serial.printf("%02X:", peerInfo.peer_addr[5] );
      }
Serial.println();
   
// peerInfo.peer_addr[5] = 3;
// ESP_ERROR_CHECK( esp_now_add_peer( &peerInfo ) );
Serial.printf("Peer %X added\n", peerInfo.peer_addr[5] );
 
 }  //  End DualInit()
