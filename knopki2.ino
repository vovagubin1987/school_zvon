


void f_knopki()
{
pinMode(buttonPin2, INPUT_PULLUP);
pinMode(buttonPin1, INPUT);
Serial.println(ESP.getFreeHeap());
//HTTP.handleClient();
Serial.println(WiFi.localIP());
int button1State = digitalRead(buttonPin1);
//
int button2State = digitalRead(buttonPin2);
  Serial.println("button");
  Serial.println(button1State);
  Serial.println(button2State);
  
if (button1State==0 && button2State ==1 && b1i==false){
  b1s=true;
  bp=true;
    Serial.println("b1");
  }
  if (button2State==0 && button1State ==1 && b2i==false){
    //podzvonka(5);
    b2s=true;
    bp=true;
    Serial.println("b2");
  }
   if (button2State==0 && button1State ==0 && b3i==false){
    //podzvonka(6);
    b3s=true;
    bp=true;
    Serial.println("b2+b1");
  }
  if (b1s){
    b1i=true;
    bp=false;
    b1s=false;
    buttong=4;
    b1i=false;
    
  }
  if (b2s){
    b2i=true;
        Serial.println("b2cpn");

     bp=false;
    b2s=false;
    //podzvonka(5);
    buttong=5;
    b2i=false;
   
  }
  if (b3s){
    b3i=true;
     bp=false;
    b3s=false;
    buttong=6;
    b3i=false;
   // bp=false;
  }
};
