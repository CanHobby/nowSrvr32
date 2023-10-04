// #include "Portfolio.h"

// int wpass = 0;

void WthDsp_Tk( void *pvParameters ) {
  bool show = true;
  int x;
Serial.println("WeathDsp Setup");
//  LCD( "Weather from ", 0,1);  //  (config.disp_cols - 16)/2, 0 );
// lcd.print( weather_info.num_cities );
//lcd.print( " towns" );

  for(;;) {
    vTaskDelay( config.Wdly * 1000 );

//    Serial.printf( "W%d = ", wpass );
//    Serial.printf( "%s %.1fC (%dC)\n", city.town_nick[wpass],
//    city.temp[wpass], city.lows[wpass][0] );

//    sprintf( tmp,  "%s %.1fC (%.0f) %d       ", city.town_nick[wpass],
//    city.temp[wpass], city.chill[wpass], city.lows[wpass][0] );
    tmp[20] = 0;
// Serial.printf( "%s\n", tmp );
//    LCD( "        ", 0, 1 );
//    LCD( tmp, 0, 1 );

if( config.w_on == WMAX ) {
// sprintf( tmp, "%d:%d %d:%d %d:%d %d:%d    ", city.highs[wpass][0],city.lows[wpass][0],
//    city.highs[wpass][1],city.lows[wpass][1],
//    city.highs[wpass][2],city.lows[wpass][2],
//    city.highs[wpass][3],city.lows[wpass][3] 
//    );

Serial.printf("FCast=%s\n", tmp );
  tmp[20] = 0;
//    LCD( "        ", 0, 2 );
//    LCD( tmp, 0, 2 );    
    wpass++;
    if( wpass >= weather_info.num_cities ) wpass = 0;
    }
  }
}
