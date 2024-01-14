byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
}
byte decToBcd(byte val){
  return( (val/10*16) + (val%10) );
}
void setDateDs1307(byte second,        // 0-59
                   byte minute,        // 0-59
                   byte hour,          // 1-23
                   byte dayOfWeek,     // 1-7
                   byte dayOfMonth,    // 1-28/29/30/31
                   byte month,         // 1-12
                   byte year)          // 0-99
{
   Wire.beginTransmission(DS1307);
   //Wire.send(0);
   Wire.write(byte(0x00));
   //Wire.send(decToBcd(second));    // 0 to bit 7 starts the clock
   Wire.write(decToBcd(second)); 
   Wire.write(decToBcd(minute));
   Wire.write(decToBcd(hour));      // If you want 12 hour am/pm you need to set
                                   // bit 6 (also need to change readDateDs1307)
   Wire.write(decToBcd(dayOfWeek));
   Wire.write(decToBcd(dayOfMonth));
   Wire.write(decToBcd(month));
   Wire.write(decToBcd(year));
  Wire.write(decToBcd(0));//start clock

   Wire.endTransmission();
}
void f_time(){
  
    gflag1=1;
  Wire.beginTransmission(DS1307); // начинаем обмен с DS3231
  Wire.write(byte(0x00)); // записываем адрес регистра, с которого начинаем чтение!!!
  Wire.endTransmission(); // завершаем передачу

  byte t[7]; // массив для хранения даты и времени
  int i = 0; // индекс текущего элемента массива
  Wire.beginTransmission(DS1307); // начинаем обмен с DS3231
  Wire.requestFrom(DS1307, 7); // запрашиваем 7 байтов у DS3231
  while(Wire.available()) { // пока есть данные от DS3231
    t[i] = Wire.read(); // читаем 1 байт и сохраняем в массив t
    i++; // инкрементируем индекс элемента массива
  }
  Wire.endTransmission(); // завершаем обмен

  gData=bcdToDec(t[4]);
  gMecjj=bcdToDec(t[5]);
  gGod=bcdToDec(t[6]);
  gHours=bcdToDec(t[2]);
  gMinutes=bcdToDec(t[1]);
  gDays=bcdToDec(t[3]);
  gflag1=0;
    
  //f_1();
 Serial.println(gData);
    Serial.println(gGod);

  Serial.println(gMecjj);
  Serial.println(gHours);
  Serial.println(gMinutes);
  Serial.println(gSec);
  Serial.println(gDays);

};
