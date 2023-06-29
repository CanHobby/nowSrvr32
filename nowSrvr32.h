#ifndef _nowSrvr32_h_
#define _nowSrvr32_h_

#include <Arduino_JSON.h>
#include <FS.h>
#include <SPIFFS.h>

// #include <ESPAsyncTCP.h>

#include <ESPAsyncWebServer.h>

#include <esp_now.h>
#include <esp_wifi.h>
#include <HTTPClient.h>

#include "NowMACs.h"

#define  USE_LCD
// #define USE_ESP01
// #define NTPdebug
//#define Wdebug

AsyncWebServer server(80);
AsyncWebServerRequest *request;
WiFiClient client;

char* convertTime( time_t t );
#define SHORT_TIME 0
#define MYTZ TZ_America_Edmonton
#define configLEN 96
#define mxBUF 3248
#define maxTQ 2

constexpr int WMIN = 2;
constexpr int WMAX = 4;
constexpr int TMAX = 4;
constexpr int TMIN = 2;
constexpr int PMAX = 4;

   char buff[ mxBUF ];
   char BADpword[16], tmp[128];
  float CurVol;
  int   wpass = 0, apipass = 0, fcpass = 0, PPass = 0, LastTime = 69;  

  int Qidx = 0, TQidx = 0;

   String Table = "Kalindra", FanST = "Off", TEMP = "69.7", Sofa = "On",
    BedSide = "Tarawa", PendTopic = "", PendMsg, PendTim, DummyST = "Off",
    TOven = "Tetisa", Coffee = "Carolin", Temp = "Teena",
    vars[16] = { "0", "One", "2", "Tarawa","4","Berta","6","7x", "8", "Nina" },
    QUE[32];

struct time_queue {
  String Device;
  String Command = "OFF";
  uint32_t timeout = 0;
 };

time_queue TimeQ[ maxTQ ]; 
uint8_t InStatus[64];
 
struct configST {
  char ssid[16]  = "theHAT";
  char pword[16] = "arturoelburro";
//  char disptype[8] = "LCD1602";
  uint8_t disp_cols = 16;
  uint8_t disp_rows = 2;
  uint8_t p_on = 0;  // PMAX;
  uint8_t t_on = TMAX;  // TMIN;
  uint8_t w_on = WMIN;
  uint8_t Wdly = 15*60;
  uint8_t Tdly = 58;
  uint8_t Sell = 2;
  uint8_t Buy  = 1;
  bool SofaLog = true;
  String Therm = "22.9";
//  String tdisp = "TX";
//  String wdisp = "WX";
//  String pdisp = "Pm";

  char spacer[8] = "1234567";  
     } config;
      
struct   tickers {
  char   *tick[6];
  char   *nick[6];
  char   updn[6];
  double alarm[6] = { 0, 0, 0, 0, 0, 0 };
  double price[6];
};

struct  place {
  String town[8] = { "Medicine Hat", "Tijuana", "Oliver", "Calgary", "Estevan" };
  String lat[8] = { "50.0501", "32.5227", "49.1831", "51.0453", "49.0821" };
  String lon[8] = { "-110.6883", "-117.1124", "-119.5524", "-114.0580", "-102.5910" };
  String town_nick[8] = { "theHAT", "Playas", "", "CGY", "" };
  String icon[8] = { "02d", "Playas", "", "CGY", "" };
  int    toffset[  8] = { 0, -2, -2, 0, 2 };
  double  temp[8] = { 49, 59, 69, 79, 89, 99, 99, 99 };
  double  temp_min[8] = { -49, 59, 69, 79, 89, 99, 99, 99 };
  double  temp_max[8] = { 69, 59, 69, 79, 89, 99, 99, 99 };
  double  chill[8] = { 39, 49, 59, 69, 79, 89 };
  int     wind[8] = { 11, 22, 333, 40, 50 };
  int     hum[8]  = { 20, 30, 5, 8, 90 };
  int     lows[8][5] = { { -0,-0,-0,-0,-0 } };
  int     highs[8][5]= { { 0,0,0,0,0      } };
  int     wclows[8][5] = { { 0,1,2,3,4 } };
  int     wchighs[8][5] = { { 0,0,0,0,0 } };
  char    sunrise[8][6] = { { 0,0,0,0,0,0 } };
  char    sunset[8][6] = { { 0,0,0,0,0,0 } };
  uint8_t  weath[8] = { 0, 1, 2, 3, 4 };  //  "--", "--", "--","--", "--", "--", "--", "--" };
} city;

/***
struct  portfl {
  int   num_ports = 2;
  char  *port_names[6] = { "CanHobby Gold", "my Real Estate", "my Dividends",
                           "CanHobby Biz", "CanHobby Crypto", "TSX Average" };
  int   num_ticks[6] = { 2, 4, 1, 1, 2, 1 };
  tickers  ticks[6];
} portfls;
***/

struct  weather {
  String ApiKey = "f30874dc72102094ea1f41676997cef2";
//  "3c2a8864d993f920de902786fffe6709";
//  c47393cfc1ae41c5b2e195045221302
  String cCode  = "CA";
//  char  *port_names[6];
  int   num_cities = 5;
  place  cities[8];
} weather_info;


#endif
