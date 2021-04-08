#include <SoftwareSerial.h> 
#include <TinyGPS.h> 
float lat,lon; // create variable for latitude and longitude object  
SoftwareSerial gpsSerial(0,1);//rx,tx 
 
TinyGPS gps; // create gps object 
void setup(){ 
Serial.begin(9600); // connect serial 
Serial.println("The GPS Received Signal:"); 
gpsSerial.begin(9600); // connect gps sensor  
} 
void loop(){ 
  while(gpsSerial.available()){ // check for gps data 
  if(gps.encode(gpsSerial.read()))// encode gps data 
  {  
  gps.f_get_position(&lat,&lon); // get latitude and longitude 
  // display position 
   

  Serial.print("Position: "); 
  Serial.print("Latitude:"); 
  Serial.print(lat,6); 
  Serial.print(";"); 
  Serial.print("Longitude:"); 
  Serial.println(lon,6);  
 } 
 String LatStr= String(lat,6);
 String LongStr= String(lon,6); 
} 
} 
