


void f_tablo()
{
Serial.println("tablo");
String to;
String gH;
String gM;
if (gHours<10) {
  gH="0"+String(gHours);
} else {gH=String(gHours);}
if (gMinutes<10) {
  gM="0"+String(gMinutes);
} else{
gM=String(gMinutes);
}
String gD="-";
if (gSec % 2 == 0)
{
    gD="-";
}
else
{
    gD=" ";
}
to=String(gDays)+tM+gH+gD+gM;
Serial.println(to);
//
My_Display.String_To_Buffer(to, Default_Brightness);
if (gHours==23 && gMinutes==57){
  Serial.println("Reset..");
    ESP.restart();
}
};