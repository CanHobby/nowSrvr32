#include "nowSrvr32.h"
#include <Arduino_JSON.h>
#include <string>
#include <iterator>

// #define WDebug
#define W_upd_DBG
// String openWeatherMapApiKey = "3c2a8864d993f920de902786fffe6709";
// api.openweathermap.org/data/2.5/forecast?lat=50&lon=110&appid=3c2a8864d993f920de902786fffe6709
//   x = 0, ;

const String wths[] = { "partly cloudy", "light snow", "overcast clouds", "scattered clouds",
                        "clear sky", "few clouds", "broken clouds", ""
                      };
// int wthlen = distance( begin(wths), end(wths) );
String serverPath;
// String fcastBuf;
static String jsonBuffer;

// size_t AVsize;
// JSONVar myFcast;

void WthUpd_Tk(  void *pvParameters  ) {
  bool show = false;
  int x;
  Serial.printf("\nWeather UpDater ");
//  Serial.print("Connected to WiFi network at: ");
//  Serial.println(WiFi.localIP());
//  Serial.printf("Monitoring weather in %d cities\n", weather_info.num_cities );

if( show ) { // lcd.clear(); LCD( "Weather ", (config.disp_cols - 16)/2 );
//lcd.print( weather_info.num_cities );
//lcd.print( " cities" );

  for ( x = 0; x < weather_info.num_cities; x++ ) {
//    Serial.print( city.town[x] ); Serial.print( ", " );
//    if( show && ( x < 3) ) {
//      LCD( "                    ", 0, 1 );
//      LCD( city.town[x].c_str(), (config.disp_cols - city.town[x].length())/2, 1 );
//          }
    delay( 2000 );      
  }

 }
  Serial.println("\nEnd Weather Setup");
  
  for(;;) {

    Serial.printf( "\n**** Update for %s, %d, %d\n", city.town[apipass].c_str(), apipass, 69 );

#ifdef use_OPEN_Basic
  WupdaterBasic();
#endif
#ifdef use_OPEN_OneCall
  WupdaterOpenCall();
#endif
    
    apipass++;
    if( apipass >= weather_info.num_cities ) apipass = 0;

    vTaskDelay( config.Wdly * 1000 );
  }
} //    End of WthUpd_Tk

/****
void getFCast_() {
  char *ptr, *tmp;
  int   idxf, idxl, cnt = 0, httpCode, len, c;
  int   fc[42], wc[42], wt[42];

  printf("\nGetting ForeCast for %s -- %d\n", city.town_nick[ fcpass ].c_str(), fcastBuf.length() );
  WiFiClient client;
  HTTPClient http;

  if ( WiFi.status() != WL_CONNECTED ) {
    printf("getFCast:48 Client not connected\n" );
    return;
  }
//Serial.println("FCast 50: http://api.openweathermap.org/data/2.5/forecast?lat=" + city.lat[fcpass] + "&lon=" + city.lon[fcpass] + "&units=metric&appid=3c2a8864d993f920de902786fffe6709");

  if ( !http.begin( client,
                    "http://api.openweathermap.org/data/2.5/forecast?lat=" + city.lat[fcpass] + "&lon=" + city.lon[fcpass] + "&units=metric&appid=3c2a8864d993f920de902786fffe6709") )
  {
    Serial.printf("getFCast:53 begin failed\n");
    return;
  }
  // start connection and send HTTP header
  httpCode = http.GET();
  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  }  else {
    Serial.printf( "FCast:60 httpCODE = %d\n", httpCode );
    return;
  }

  if (httpCode != HTTP_CODE_OK && httpCode != HTTP_CODE_MOVED_PERMANENTLY) {
    Serial.printf("FCast:63 Bad httpCode %d\n", httpCode ); return;
  }
  len = http.getSize(); c = 0;
  // Serial.printf("len = %d\n", len );

  // while (http.connected() && (len > 0 || len == -1) ) {
  while ( AVsize = client.available() ) {

    if ( AVsize > sizeof(buff) ) {
      Serial.printf( "FCast:71 Buff overrun size = %d, buf = %d, len = %d\n", AVsize, sizeof(buff), len );
    }

    c = client.readBytes(buff, (( AVsize > sizeof(buff)) ? mxBUF : AVsize ) );
    len = len - c;
    //  Serial.printf("%d->%d ", c, len );
    fcastBuf.concat( buff );
    delay( 50 );
  }
  // }
  Serial.printf("\nBuf assembled len = %d\n", len );
  Serial.printf("fcBuf length() = %d\n", fcastBuf.length() );
  //   Serial.print("fcBuf = " );
  //   Serial.println( fcastBuf.substring( 0, 200 ) );
  //   Serial.println("\n");

  while ( cnt < 40 ) {

    idxf = fcastBuf.indexOf( "temp\":" );
    //   if( idxf != -1 ) Serial.printf("found temp idxf = %d\n", idxf );
    idxl = fcastBuf.indexOf( ",\"feels" );
    //   if( idxl != 0 ) Serial.printf("found feels idxl = %d\n", idxl );
    //   Serial.print( fcastBuf.substring( idxf+6, idxl ) );
    //   Serial.printf("  -- %d\n", fcastBuf.substring( idxf+6, idxl ).toInt() );
    fc[ cnt ] = fcastBuf.substring( idxf + 6, idxl ).toInt();
    //  Serial.printf("%d \n", fc[ cnt ] );
    idxf = idxl + 14;
    //   if( idxf != -1 ) Serial.printf("found temp idxf = %d\n", idxf );
    idxl = fcastBuf.indexOf( "temp_min" ) - 2;
    //   if( idxl != 0 ) Serial.printf("found feels idxl = %d\n", idxl );
    //   Serial.print( fcastBuf.substring( idxf, idxl ) );
    //   Serial.printf("  -- %d\n", fcastBuf.substring( idxf+6, idxl ).toInt() );
    wc[ cnt ] = fcastBuf.substring( idxf, idxl ).toInt();
    //  Serial.printf("  %d  ", wc[ cnt ] );
    idxf = fcastBuf.indexOf( "ption" ) + 8;
    //   if( idxf != 0 ) Serial.printf("found desc idxf = %d\n", idxf );
    idxl = fcastBuf.indexOf( "icon" ) - 3;
    //   if( idxl != 0 ) Serial.printf("found icon idxl = %d\n", idxl );
    //   Serial.print(  fcastBuf.substring( idxf, idxl ) );
    //   Serial.printf( "    idxf = %d, idxl = %d\n", idxf, idxl );

    idxf = fcastBuf.indexOf( "dt_txt" ) + 20;
    //Serial.print( fcastBuf.substring( idxf, idxf+2 ) );
    fcastBuf.remove( 0, idxf + 10 );
    //Serial.printf("|\ncnt = %d, idxf = %d, len = %d\n", cnt, idxf, fcastBuf.length() );
    cnt++;
  }
  fcastBuf.clear();
  sortFC( fc, wc );
  FCupdate = false;
  fcpass++;
  if ( fcpass > weather_info.num_cities ) {
    fcpass = 0;
  }
}  *****/ //  end getWFCast
/*****
void sortFC( int fc[], int wc[] ) {
  int i, j, k, x, temp, tempwc;
  for ( k = 0; k < 5; k++ ) {
    for (i = 0; i < 7; i++ )
    {
      for (j = 0; j < 8 - i; j++ )
      {
        if ( fc[ j + k * 8 ] > fc[ j + k * 8 + 1 ])
        {
          temp = fc[ j + k * 8 + 1 ];
          fc[ j + k * 8 + 1 ] = fc[ j + k * 8 ];
          fc[ j + k * 8 ] = temp;
        }
        if ( wc[ j + k * 8 ] > wc[ j + k * 8 + 1 ])
        {
          tempwc = wc[ j + k * 8 + 1 ];
          wc[ j + k * 8 + 1 ] = wc[ j + k * 8 ];
          wc[ j + k * 8 ] = tempwc;
        }
      }
    }
    city.lows[fcpass][k] = fc[k * 8];  city.highs[fcpass][k] = fc[k * 8 + 7];
    city.wclows[fcpass][k] = wc[k * 8];  city.wchighs[fcpass][k] = wc[k * 8 + 7];

    for ( x = 0; x < 8; x++ ) {
      //  Serial.printf("f%d ", fc[x+k*8] );
      //  Serial.printf("w%d ", wc[x+k*8] );
    } // Serial.printf(" == %d\n", fcpass );
  }
} //  end sortFC()
*******/
void WupdaterBasic() {  // Get updated Weather data

  serverPath = "http://api.openweathermap.org/data/2.5/weather?lat=" + city.lat[apipass] + "&lon=" + city.lon[ apipass ] + "&units=metric&appid=3c2a8864d993f920de902786fffe6709";

   Serial.printf( "Wupdater %s api = %d\n", city.town_nick[apipass], apipass );

    jsonBuffer = httpGETRequest(serverPath.c_str());
 
    Serial.printf("JBuf len = %d\n", jsonBuffer.length() );

    String stg;

#ifdef W_upd_DBG
    Serial.println(jsonBuffer);
#endif
    JSONVar myObject = JSON.parse(jsonBuffer);
#ifdef W_upd_DBG
  Serial.println(myObject["main"]);
#endif    
   stg = JSON.stringify( myObject["main"]["temp"] );
 Serial.printf( "cur temp = %s\n", stg );    
    double dtmp = stg.toDouble();
    city.temp[ apipass ] = dtmp;
 Serial.printf( "cur temp dtmp = %.2f\n", dtmp );
 Serial.printf( "temp = %.2f\n", city.temp[0] ); 
    stg = JSON.stringify( myObject["main"]["feels_like"] );
    dtmp = stg.toDouble();
    city.chill[ apipass ] = dtmp;
 Serial.printf( "chill = %.2f\n", city.chill[ apipass ] );    

// Serial.printf( "\nSTG = " );
// Serial.println( myObject["daily"][0]["temp"]["min"] );
stg = JSON.stringify( myObject["main"]["temp_min"] );
// int itmp
dtmp = stg.toDouble();
city.temp_min[apipass] = dtmp;
stg = JSON.stringify( myObject["main"]["temp_max"] );
    dtmp = stg.toDouble();
city.temp_max[apipass] = dtmp;
#ifdef WDebug
// Serial.printf("\n%d=%d:%d",apipass,city.highs[apipass][x],city.lows[apipass][x]);
#endif
 
Serial.println();
//    stg = JSON.stringify( myObject["wind"]["speed"] );
    int Wind = stg.toInt();
    city.wind[ apipass ] = Wind;

//    stg = JSON.stringify( myObject["main"]["humidity"] );
    Wind = stg.toInt();
    city.hum[ apipass ] = Wind;
#ifdef Wdebug
  Serial.println("End Weatehr Update");
#endif
  apipass++;
  if ( apipass > weather_info.num_cities ) {
    apipass = 0;
  }
}
/**********   ONE CALL   ************  /
void WupdaterOneCall() {
  
  serverPath = "http://api.openweathermap.org/data/2.5/forecast?lat=" + city.lat[apipass] + "&lon=" + city.lon[ apipass ] + "&units=metric&appid=3c2a8864d993f920de902786fffe6709";

   Serial.printf( "Wupdater %s api = %d\n", city.town_nick[apipass], apipass );

    jsonBuffer = httpGETRequest(serverPath.c_str());
 
    Serial.printf("JBuf len = %d\n", jsonBuffer.length() );

//  Serial.printf( "\nWupdate Reporting apipass = %d\n", apipass );
  // Check WiFi connection status

    String stg;
    char *stg2;
//    String serverPath = "http://api.openweathermap.org/data/3.0/onecall?lat=" + city.lat[apipass] + "&lon=" + city.lon[ apipass ] + "&units=metric&exclude=minutely,hourly,alerts&APPID=" + weather_info.ApiKey;

//   Serial.println( serverPath );
//    jsonBuffer = httpGETRequest(serverPath.c_str());
#ifdef W_upd_DBG
    Serial.println(jsonBuffer);
#endif
    JSONVar myObject = JSON.parse(jsonBuffer);
// Serial.printf( "jsonBuffer len = %d\n", jsonBuffer.length() );
//    if (JSON.typeof(myObject) == "undefined") {
//      Serial.println("Parsing input failed!");
//      return;
//    }

#ifdef W_upd_DBG
//    Serial.println(myObject["current"]);
Serial.println(myObject["list"][0]["main"]);
#endif    
//    stg = JSON.stringify( myObject["current"]["temp"] );
        stg = JSON.stringify( myObject["list"][0]["main"]["temp"] );  //  "main"]["temp"] );
 Serial.printf( "cur temp = %s\n", stg );    
    double dtmp = stg.toDouble();
    city.temp[ apipass ] = dtmp;
 Serial.printf( "cur temp dtmp = %.2f\n", dtmp );
 Serial.printf( "temp = %.2f\n", city.temp[0] ); 
    stg = JSON.stringify( myObject["current"]["feels_like"] );
    dtmp = stg.toDouble();
    city.chill[ apipass ] = dtmp;
 Serial.printf( "chill = %.2f\n", city.chill[ apipass ] );    

for( int x=0; x<5; x++ ) {

// Serial.printf( "\nSTG = " );
// Serial.println( myObject["daily"][0]["temp"]["min"] );
stg = JSON.stringify( myObject["daily"][x]["temp"]["min"] );
int itmp = stg.toInt();
city.lows[apipass][x] = itmp;
stg = JSON.stringify( myObject["daily"][x]["temp"]["max"] );
    itmp = stg.toInt();
// city.highs[apipass][x] = itmp;
#ifdef WDebug
// Serial.printf("\n%d=%d:%d",apipass,city.highs[apipass][x],city.lows[apipass][x]);
#endif
}   
Serial.println();
//    stg = JSON.stringify( myObject["wind"]["speed"] );
    int Wind = stg.toInt();
    city.wind[ apipass ] = Wind;

//    stg = JSON.stringify( myObject["main"]["humidity"] );
    Wind = stg.toInt();
    city.hum[ apipass ] = Wind;
#ifdef Wdebug
  Serial.println("End Weatehr Update");
#endif
  apipass++;
  if ( apipass > weather_info.num_cities ) {
    apipass = 0;
  }
}
********/
void WdisplayerMINI() {
  int x = 0, xx, xc, yy = config.disp_rows - 2;

//  FntWthTim();
  
#ifdef Wdebug
  Serial.printf("\nWMINI - %d, %d cities, wpass = %d, w_on =  %d   ", config.disp_cols, weather_info.num_cities, wpass, config.w_on );
#endif
  if ( (weather_info.num_cities - wpass ) < 2 ) {
    xc = 1;
  }  //  weather_info.num_cities/2 +1; }
  else {
    xc = 2;
  }  // weather_info.num_cities/2; }
#ifdef Wdebug
  Serial.printf("xc == %d\n", xc );
#endif
if( city.temp[x + wpass] == 99 ) { return; }
  for ( xx = 0; xx < config.disp_cols; xx++ ) {
//    LCD(" ", xx, yy);  //  clear
  }
  //  while( x < xc ) {  //  weather_info.num_cities/2  ) {
#ifdef Wdebug
  Serial.printf(" %d  ", x );
#endif
  if ( config.t_on ) {
    xx = 0;
  } // ( config.disp_cols - city.town_nick[x+wpass].length() ) / 2; }
  else {
    xx = 0;
  }
  
  if ( city.town_nick[x + wpass] != "" ) {
    //     printf("x %d wpass %d\n", x, wpass );
//    lcd.setCursor( xx, yy );
//    lcd.print( city.town_nick[ x + wpass ] );
  } else {
    printf("x %d wpass %d\n", x, wpass );
//    lcd.setCursor( xx, yy );
//    lcd.print( city.town[ x + wpass ] );
  }

/**  lcd.setCursor( config.disp_cols - city.weath[wpass].length(), yy );
lcd.print( "  " ); 
lcd.write( city.weath[wpass] );
lcd.setCursor( config.disp_cols - 5, yy );
lcd.printf("%02d:", atoi(ArtTime.Hour) + (city.toffset[ x + wpass ] / 2) + ( 1 * Nfld ) );
  if ( city.toffset[ x + wpass ] % 2 ) {
    if (  Nfld ) lcd.printf( "%02d",  atoi(ArtTime.Min) - 30 );
    if ( !Nfld ) lcd.printf( "%02d",  atoi(ArtTime.Min) + 30 );
  }
  else {
    lcd.printf( "%02d",  atoi(ArtTime.Min) );
  }

  lcd.setCursor( 0, yy + 1 );
  lcd.printf( "% .0fC (%.0f) %2dkm    ", city.temp[x + wpass], city.chill[x + wpass], city.wind[x + wpass] );
  if ( config.disp_cols > 18 ) {
    lcd.setCursor( config.disp_cols - 4 , yy + 1 );
    lcd.printf( "%d%% ", city.hum[x + wpass] );
  }
****/  
// }  //  temp == 99
  if ( wpass >= weather_info.num_cities - 1 ) {
    wpass = 0;
  } else {
    wpass ++;
  }
  delay( config.Wdly * 1000 );
//  W_ON = false;
#ifdef Wdebug
  Serial.println("End WdisplayMINI");
#endif
}  //  End WdisplayerMNI

void WdisplayerMAXxxx() {
  int x = 0;
#ifdef Wdebug
  Serial.printf("\nWMAX - %d cities, wpass = %d ", weather_info.num_cities, wpass );
#endif
//  lcd.clear();
#ifdef Wdebug
  Serial.printf(" %d  ", x );
#endif

  //   if( config.tdisp ) { xx = ( config.disp_cols - city.town_nick[x+wpass].length() ) / 2; }
  //   else { xx = 1; }
//  lcd.setCursor( 1, 0 );
  if ( city.town_nick[x + wpass] != "" ) {
    //    lcd.setCursor( 1, 0 );
//    lcd.print( "\"" ); lcd.print( city.town_nick[ x + wpass ] ); lcd.print( "\"" );
  } else {
    //    lcd.setCursor( 0, 0 );
//    lcd.print( city.town[ x + wpass ] );
  }
  //    lcd.setCursor( config.disp_cols - 5, x*2 );
/**
  if ( (city.toffset[ x + wpass ] % 2 ) && (atoi(ArtTime.Min) > 29 ) ) {
    Nfld = 1;
    //  Serial.printf("\nMAX 323: Nfld = %d\n", Nfld );

  } else {
    Nfld = 0;
    //        Serial.printf("\nNfld MAX:326 %d\n", Nfld );
  }
****/
//  lcd.setCursor( config.disp_cols - 5, x * 2 );
    Serial.printf( "\nLine 336 : %s -- ", city.town_nick[ x+wpass ].c_str() );
//  lcd.printf("%02d:", atoi(ArtTime.Hour) + (city.toffset[ x + wpass ] / 2) + ( 1 * Nfld ) );
//    Serial.printf("%02d: -- %d --  ", atoi(ArtTime.Hour), Nfld );
//    Serial.printf("%02d:\n", atoi(ArtTime.Hour) + (city.toffset[ x+wpass ]/2) + (1*Nfld) );

  if ( city.toffset[ x + wpass ] % 2 ) {
//   if (  Nfld ) lcd.printf( "%02d",  atoi(ArtTime.Min) - 30 );
//    if ( !Nfld ) lcd.printf( "%02d",  atoi(ArtTime.Min) + 30 );
  }
  else {
//    lcd.printf( "%02d",  atoi(ArtTime.Min) );
  }
#ifdef use_LCD
//  lcd.setCursor( 0, x * 2 + 1 );
  lcd.printf( "% .0fC (%.0f) %2dkm", city.temp[x + wpass], city.chill[x + wpass], city.wind[x + wpass] );

  lcd.setCursor( config.disp_cols - 3 , x * 2 + 1 );
  lcd.printf( "%d%%", city.hum[x + wpass] );

  lcd.setCursor( 0, 2 );
  for ( x = 0; x < 5; x++ ) {
    lcd.printf( "% 3d ", city.highs[ wpass ][x] );
  }

  lcd.setCursor( 0, 3 );
  for ( x = 0; x < 5; x++ ) {
    lcd.printf( "% 3d ", city.lows[ wpass ][x] );
  }
#endif  
  wpass++;
  if ( wpass >= weather_info.num_cities ) {
    wpass = 0;
  }
  delay( config.w_on * 1000 - 200 );
//  W_ON = false;
#ifdef Wdebug
  Serial.println("End WdisplayMAX");
#endif
delay( (config.Wdly-1) * 1000 ); 
}

const String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
#ifdef WDebug  
  Serial.printf("httpREQ serverName = %s\n", serverName );
#endif
  http.begin(client, serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload;

  if (httpResponseCode > 0) {
#ifdef WDebug
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
#endif
/****
      int  len = http.getSize();
      Serial.printf("len = %d\n", len );
      int avl = client.available();
      Serial.printf("avl = %d\n", avl );
    *****/
    payload = http.getString();
//    delay( 300 );
//    Serial.print("PLoad = ");
//    Serial.println( payload );
    // Serial.println(" XX");

  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
