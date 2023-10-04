
#include <time.h>

void FSbegin() {

Serial.printf("FSbegin( )\n");
    if (!SPIFFS.begin( )) {
    Serial.println("FS mount failed");
    return;
  }
}

int getFSize( const String fil ) {
File f;
int  siz;

  f = SPIFFS.open( fil, "r");
  siz = f.size();
  f.close();
//  printf("getFSize fil = %d bytes in ", siz );
//  Serial.println( fil );
  return siz;
                }
                
void FSRead( char *fil, bool dump ) {
//   fs::FS &fs = SPIFFS;
File f;
  f = SPIFFS.open( fil );
  Serial.printf("FSRead: %s %d bytes long\n", fil , f.size() );
  f.read( Buf, f.size() );

if( dump ) {
  Serial.printf("\n--------------------------------------------------------------------\n\n");
  for( int x=0; x<f.size(); x++ ) {
    Serial.printf( "%c", Buf[x] );
            }
  Serial.printf("\n--------------------------------------------------------------------\n\n");
          }    
   f.close(); 
 }

//#ifdef ESP32

 void listDir(const char * dirname ) {  //  , fs::FS &fs, uint8_t levels){

  fs::FS &fs = SPIFFS;
  uint8_t levels = 0;
  
  Serial.printf("ESP32 Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(file.path() );  //  , levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}
/****/

// #endif

#ifdef ESP8266
void listDir(const char * dirname) {
// void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  Serial.printf("Listing directory: %s\n", dirname);

  Dir root = LittleFS.open(dirname);

  while (root.next()) {
    File file = root.openFile("r");
    Serial.print("  FILE: ");
    Serial.print(root.fileName());
    Serial.print("  SIZE: ");
    Serial.print(file.size());
    time_t cr = file.getCreationTime();
    time_t lw = file.getLastWrite();
    file.close();
    struct tm * tmstruct = localtime(&cr);
    Serial.printf("    CREATION: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
//    tmstruct = localtime(&lw);
//    Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
  }
}
#endif
