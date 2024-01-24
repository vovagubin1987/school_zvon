


// --------------------- Загрузка переменных -------------------------------------------------------





void setupToInit() {
  sendStatus(timeS, "00:00:00");
  setupToOptions(langS);
  setupToOptions(ssdpS);
  setupToOptions(spaceS);
  setupToOptions(timeZoneS);
  setupToOptions(ddnsNameS);
  setupToOptions(ddnsPortS);
  setupToOptions(spiffsDataS);
  setupToOptions(buildDataS);
  setupToOptions(langS);
  sendOptions("flashChip", String(ESP.getFlashChipId(), HEX));
  sendOptions("ideFlashSize", ESP.getFlashChipSize());
  sendOptions("realFlashSize", ESP.getFlashChipRealSize());
  sendOptions("flashChipSpeed", ESP.getFlashChipSpeed() / 1000000);
  sendOptions("cpuFreqMHz", ESP.getCpuFreqMHz());
  FlashMode_t ideMode = ESP.getFlashChipMode();
  sendOptions("FreeSketchSpace", ESP.getFreeSketchSpace());
  sendOptions("flashChipMode", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" : ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));
  String configs = getSetup(configsS);
  configs.toLowerCase();
  //String test = readFile("configs/" + configs + ".txt", 4096);
  //test.replace("\r\n", "\n");
  //test += "\n";
  //goCommands(test);
  String test = emptyS;
  sendOptions(macS, WiFi.macAddress().c_str());
  sendOptions(ipS, WiFi.localIP().toString());
  sendOptions(macS, WiFi.macAddress().c_str());
  sendOptions("voice", emptyS);
  jsonWrite(modules, ipS, getOptions(ipS));
  jsonWrite(modules, spaceS, getSetup(spaceS));
  jsonWrite(modules, langS, getSetup(langS));
  jsonWrite(modules, ssdpS, getSetup(ssdpS));

  initPuls();

}
/*
// --------------------Выделяем строку до маркера --------------------------------------------------
String selectToMarker (String str, String found) {
  int p = str.indexOf(found);
  return str.substring(0, p);
}

// -------------------Выделяем строку от конца строки до маркера ---------------------
String selectToMarkerLast (String str, String found) {
  int p = str.lastIndexOf(found);
  return str.substring(p + found.length());
}

//----------------------Удаляем все до символа разделителя -----------------
String deleteBeforeDelimiter(String str, String found) {
  int p = str.indexOf(found) + found.length();
  return str.substring(p);
}
//----------------------Удаляем все до символа разделителя -----------------
String deleteBeforeDelimiterTo(String str, String found) {
  int p = str.indexOf(found);
  return str.substring(p);
}
// -------------------Удаляем строку от конца строки до маркера ---------------------
String deleteToMarkerLast (String str, String found) {
  int p = str.lastIndexOf(found);
  return str.substring(0, p);
}
*/

// ------------- Данные статистики -----------------------------------------------------------
void statistics() {
  /*String urls = "http://backup.privet.lv/visitors/?";
  urls += WiFi.macAddress().c_str();
  urls += "&";
  urls += getSetup(configsS);
  urls += "&";
  urls += ESP.getResetReason();
  urls += "&";
  urls += getSetup(spiffsDataS);
  String stat = getURL(urls);
  sendOptions(messageS, jsonRead(stat, messageS));
  */
}


// ------------- Запрос на удаленный URL -----------------------------------------
String getURL(String urls) {
  String answer;
  HTTPClient http;
  //http.begin(urls); //HTTP
  http.begin(client, urls); //HTTP

  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    answer = http.getString();
  }
  http.end();
  return answer;
}
//------------------Выполнить все команды по порядку из строки разделитель \r\n  \n
String goCommands(String inits) {
  //Serial.println(inits);
  String temp;
  String rn = "\n";
  inits += rn;
  //  Serial.println(writeFile("inits.txt", inits));
  do {
    temp = selectToMarker (inits, rn);

    //    Serial.println(temp);
    sCmd.readStr(temp);
    inits = deleteBeforeDelimiter(inits, rn);
  } while (inits.indexOf(rn) != 0);
  return "OK";
}

/*
// ------------- Чтение файла в строку --------------------------------------
String readFile(String fileName, size_t len ) {
  File configFile = LittleFS.open("/" + fileName, "r");
  if (!configFile) {
    return "Failed";
  }
  size_t size = configFile.size();
  if (size > len) {
    configFile.close();
    return "Large";
  }
  String temp = configFile.readString();
  configFile.close();
  return temp;
}
// ------------- Запись строки в файл --------------------------
String writeFile(String fileName, String strings ) {
  File configFile = LittleFS.open("/" + fileName, "w");
  if (!configFile) {
    return "Failed to open file";
  }
  configFile.print(strings);
  configFile.close();
  return "Write sucsses";
}

*/
// ------------- Запись файла конфигурации ----------------------------------
void saveConfigSetup () {
  writeFile(fileConfigS, configSetup );
}
void saveConfigSetupS1 () {
  writeFile(fileConfigS1, configSetupS1 );
}
void saveConfigSetupS11 () {
  writeFile(fileConfigS11, configSetupS11 );
}
void saveConfigSetupS22 () {
  writeFile(fileConfigS22, configSetupS22 );
}
void saveConfigSetupS33 () {
  writeFile(fileConfigS33, configSetupS33 );
}
void saveConfigSetupS2 () {
  writeFile(fileConfigS2, configSetupS2 );
}
void saveConfigSetupS3 () {
  writeFile(fileConfigS3, configSetupS3 );
}
void saveConfigSetupT () {
  writeFile(fileConfigT, configSetupT );
}
// ------------- Проверка занятости пина --------------------------
/*
   Алгоритм
   Провнряем свободен ли пин если нет вернем 17
   Если свободен то займем pins[pin] = true;

*/
uint8_t pinTest(uint8_t pin) {
  //Serial.print("pin");
  //Serial.print("=");
  /*
  if (pin > 20) {
    pin = 17;
  } else {
    if (pins[pin]) {
      pin = 17 ;
    }
    else {
      pins[pin] = true;
      if (getOptions("flashChipMode") != "DOUT") {
        if (pin > 5 && pin < 12) pin = 17 ;
        if (pin == 1 || pin == 3)  Serial.end();
      } else {
        if ( (pin > 5 && pin < 9) ||  pin == 11) pin = 17 ;
      }
    }
  }
  //Serial.println(pin);
  return pin;
  */
  return 1;
}
uint8_t pinTest(uint8_t pin, boolean multi) {
  //Serial.print("multiPin");
  //Serial.print("=");
  /*
  if (pin > 20) {
    pin = 17;
  } else {
    pins[pin] = !multi;
    if (pins[pin]) {
      pin = 17 ;
    }
    else {
      pins[pin] = true;
      if (getOptions("flashChipMode") != "DOUT") {
        if (pin > 5 && pin < 12) pin = 17 ;
        if (pin == 1 || pin == 3)  Serial.end();
      } else {
        if ( (pin > 5 && pin < 9) ||  pin == 11) pin = 17 ;
      }
    }
  }
  //Serial.println(pin);
  return pin;
  */
  return 1;
}

// -------------- Регистрация модуля
void modulesReg(String modName) {
  ///*
  //DynamicJsonBuffer jsonBuffer;
  DynamicJsonDocument doc(1024);
  //JsonObject& json = jsonBuffer.parseObject(modules);
  deserializeJson(doc, modules);
  //json[ssdpS] = jsonRead(configJson, ssdpS);
  doc[ssdpS] = jsonRead(configJson, ssdpS);
  //hak
   //doc[configsS] = "config";
  //json[spaceS] = jsonRead(configJson, spaceS);
  doc[spaceS] = jsonRead(configJson, spaceS);
  //JsonArray& data = json["module"].asArray();
  JsonArray data = doc.createNestedArray("module");
  //data.add(modName);
  data.add("ntp");
  data.add("upgrade");
  modules = emptyS;
  serializeJson(doc, modules);
  //json.printTo(modules);
  //*/
}

// -------------- Регистрация команд
void commandsReg(String comName) {
  if (regCommands.indexOf(comName) == -1) {
    //DynamicJsonBuffer jsonBuffer;
    DynamicJsonDocument doc(1024);

    //JsonObject& json = jsonBuffer.parseObject(regCommands);
    
    //JsonArray& data = json["command"].asArray();
    JsonArray data = doc.to<JsonArray>();
    data.add(comName);
    regCommands = emptyS;
    //json.printTo(regCommands);
    deserializeJson(doc, regCommands);
  }
  }
// -------------- Регистрация actions
void actionsReg(String actionsName) {
   jsonWrite(pulsList, actionsName, pulsNum);
  pulsNum++;
}


// ------------------- Инициализация Импульс
void initPuls() {
  sCmd.addCommand(pulseS.c_str(), startPuls);
  commandsReg(pulseS);
  //modulesReg(pulseS);
}

void startPuls() {
  String com = readArgsString(); // on off
  /*
  if (com != "") { // если комманда есть
    String pulseCom = readArgsString(); // Команда relay3 или rgb
    String tacks = jsonRead(pulsList, pulseCom);  //Получим номер задачи для устройства
    sendOptions(pulseS + "State" + tacks, false);
    pulseCom = topicToCom(pulseCom);   // Пробел между командой и номером
    pulseCom.replace(" ", " not ");    // Модефицируем командув not
    sendOptions(pulseComS + tacks, pulseCom); // Сохраним команду
    if (com == onS || com == "1") {         // Если комманда есть
      int freq = stringToMilis (readArgsString(), 1); // Как долго включен
      sendOptions(pulseS + tacks + "0", freq);
      if (freq != 0) {
        String temp = readArgsString(); // Как долго выключен
        int freq1 = temp.toInt();
        if (temp == "-")freq1 = freq;
        if (temp == "")freq1 = 0;
        sendOptions(pulseS + tacks + "1", freq1);
        int period = freq + freq1;
        String pulseTime = readArgsString(); // Время работы
        int pulseTimeInt = stringToMilis(pulseTime, period);
        int remainder = pulseTimeInt % (period);
        if (remainder > period / 2) {
          pulseTimeInt += period - remainder;
        } else  pulseTimeInt -= remainder;
        if (getStatusInt(pulseCom)) {
        pulseCom.replace(notS, offS);          // Модефицируем командув off
        sCmd.readStr(pulseCom);
        }
        sendOptions(pulseTimeS + tacks, pulseTimeInt);
        imPuls(tacks.toInt());
      }
    }
    if (com == "off" || com == "0") {
      pulseCom.replace(notS, offS);
      sCmd.readStr(pulseCom);
      flipper[tacks.toInt()].detach();
    }
  }
  */
}
int stringToMilis(String times, int period) {
  int p = times.length();
  String unit = times.substring(p - 1, p);
  int timei = times.toInt();
  if (unit == "s") timei *= 1000;
  if (unit == "m") timei *= 60000;
  if (unit == "h") timei *= 3600000;
  if (unit == "i") timei *= period;
  return timei;
}
void imPuls(int tacks) {
  /*
  String pulseStateN = "pulseState" + (String)tacks;
  boolean stopF = true;
  String pulseCom = getOptions(pulseComS + tacks);           // Получить каким устройством управляем
  String pulseTime = getOptions(pulseTimeS + tacks);         // Получим текстовое значние времени работы
  int pulseTimeInt = pulseTime.toInt();                 // Получим int значние времени работы
  uint8_t low = getOptionsInt(pulseStateN);
  int timeOn = getOptionsInt(pulseS + tacks + low); // Время включено
  int timeOff = getOptionsInt(pulseS + tacks + !low); // Время выключено
  if (timeOn > 0) {                                     // Если время включено >0 сразу закончить

    if (!low) {
      pulseCom.replace(notS, onS);
      //Serial.println(pulseCom);
    }
    else {
      pulseCom.replace(notS, offS);
      //Serial.println(pulseCom);
    }

    sCmd.readStr(pulseCom);                             // Выполнить команду
    if (pulseTime != "null" && pulseTimeInt != 0 ) {
      sendOptions(pulseTimeS + tacks, (String)(pulseTimeInt - timeOn));
      if (getOptionsInt(pulseTimeS + tacks) <= 0) {
        flipper[tacks].detach();
        stopF = false;
      }
    }
    low = !low;
    sendOptions(pulseStateN, low);
    if (stopF) {
      flipper[tacks].attach_ms(timeOn, imPuls, tacks);               // Задать время через которое процедура будет вывана повторно
    }
  } else {
    sCmd.readStr(pulseCom);                            // Выключить
    flipper[tacks].detach();                               // Остановим таймер
    //low = false;                                      // Сбросить флаг ???
    sendOptions(pulseStateN, false);
  }
  */
}
void podzvonka(int tmp){//дёргалка реле
//erial.println("podzvonka");
//Serial.println(tmp);
  switch (tmp){
    case 1:
    Serial.println("zvon1");
      digitalWrite(relePin, HIGH);
      Serial.println("zvon1");
      //delay(3500);
      f_d(45);
      digitalWrite(relePin, LOW);
      //zad[2]=3;
      times=0;
      zad[2]=3;

      break;
    case 2:
    
    Serial.println("zvon2");
      digitalWrite(relePin, HIGH);
      //delay(1000);
      f_d(45);
       //delay(500);
       //delay(1000);
       //delay(1000);
      Serial.println("zvon2");
      digitalWrite(relePin, LOW);
      f_d(1200);
      //delay(60000);
      //
      //digitalWrite(relePin, LOW);
      digitalWrite(relePin, HIGH);
      //delay(1500);
      f_d(30);
      digitalWrite(relePin, LOW);
      //delay(1000);
       //delay(500);
       //delay(1000);
      // delay(1000);
      f_d(35);
      //digitalWrite(relePin, LOW);
      digitalWrite(relePin, HIGH);
      //delay(1500);
      f_d(30);
      digitalWrite(relePin, LOW);
      //zad[2]=3;
      times=0;
      zad[2]=3;
      break;
    case 3:
    Serial.println("zvon3");
      digitalWrite(relePin, HIGH);
      //delay(1500);
      f_d(15);
      Serial.println("zvon3");
      digitalWrite(relePin, LOW);
      //delay(1000);
       //delay(500);
       //delay(1000);
       f_d(25);
      digitalWrite(relePin, HIGH);
      //delay(1500);
      f_d(15);
      digitalWrite(relePin, LOW);
      //delay(1000);
      // delay(500);
      // delay(1000);
      f_d(25);
      digitalWrite(relePin, HIGH);
      //delay(1500);
      f_d(15);
      digitalWrite(relePin, LOW);
      //zad[2]=3;
      //delay(2500);
      times=0;
      zad[2]=3;
      break;
    case 4:
      b1i=true;
      tM="n";
      buttong=0;
      t_knopki.detach();
      pinMode(relePin, OUTPUT);
      
      digitalWrite(relePin, HIGH);
      Serial.println("zvon4");
      
      f_d(35);
     
      digitalWrite(relePin, LOW);
       if (bp==true){
         b1i=false;
        break;
      }
      f_d(35);
      digitalWrite(relePin, HIGH);
      f_d(35);
      digitalWrite(relePin, LOW);
       if (bp==true){
         b1i=false;
         t_knopki.attach_ms(500,f_knopki);
        break;
      }
      f_d(35);
      
      digitalWrite(relePin, HIGH);
      f_d(35);
      digitalWrite(relePin, LOW);
      //zad[2]=3;
      //delay(2500);
      f_d(35);
      b1i=false;
    t_knopki.attach_ms(500,f_knopki);
    digitalWrite(relePin, HIGH);
      f_d(35);
      digitalWrite(relePin, LOW);
       if (bp==true){
         b1i=false;
         t_knopki.attach_ms(500,f_knopki);
        break;
      }
      f_d(35);
      
     buttong=0;
      break;
    case 5:
      b2i=true;
      buttong=0;
      tM="C";
            t_knopki.detach();

      pinMode(relePin, OUTPUT);
      //
      digitalWrite(relePin, HIGH);
      f_d(20);
      Serial.println("zvon5");
      digitalWrite(relePin, LOW);
      f_d(15);
      Serial.println("zvon5-4");
       if (bp==true){
         Serial.println("zvon5_5");
         b2i=false;
         t_knopki.attach_ms(500,f_knopki);
        break;
      }
      digitalWrite(relePin, HIGH);
      f_d(20);
      Serial.println("zvon5__4_1");
      digitalWrite(relePin, LOW);
       f_d(15);
      //digitalWrite(relePin, HIGH);
      Serial.println("zvon5-5");
      f_d(15);
      //digitalWrite(relePin, LOW);
       if (bp==true){
         b2i=false;
        break;
      }
      digitalWrite(relePin, HIGH);
      f_d(20);
      digitalWrite(relePin, LOW);
      
      //digitalWrite(relePin, HIGH);
      
      //digitalWrite(relePin, LOW);
      //zad[2]=3;
      //delay(2500);
      b2i=false;
      t_knopki.attach_ms(500,f_knopki);
      buttong=0;

      break;
    case 6:
      b3i=true;
      tM="t";
      buttong=0;
                  t_knopki.detach();

      digitalWrite(relePin, HIGH);
      f_d(200);
      Serial.println("zvon6");
      digitalWrite(relePin, LOW);
       if (bp==true){
         b3i=false;
         t_knopki.attach_ms(500,f_knopki);
        break;
      }
      f_d(100);
      digitalWrite(relePin, HIGH);
      f_d(300);
      digitalWrite(relePin, LOW);
        if (bp==true){
        b3i=false;
                  t_knopki.attach_ms(500,f_knopki);
         buttong=0;

        break;
    

      }
      t_knopki.attach_ms(500,f_knopki);
      break;
    
    default:
      delay(0);
      break;

  }

}

void proced1(int days1){
  int tmp111=mst[days1-1];//день в индексе с нуля
  Serial.println("---------");
  Serial.println(times);
  Serial.println(tmp111);
  switch (tmp111){
    case 1 :
      for (int i = 0; i < 31; i++){
        if (ms1h[i]==gHours && ms1m[i]==gMinutes && ms1type[i] !=33){
          //zad[2]=33;
          //zad[0]=gHours;
         // zad[1]=gMinutes;
          //
           if (zad[0]==gHours && zad[1]==gMinutes)
          {
            delay(0);
            tM=String(i);
          } else{
          //podzvonka(ms1type[i]);
          //times=ms1type[i];
          zad[2]=33;
          times=ms1type[i];
          //zad[2]=3;
          gTimeZvonokNextHours=ms1h[i+1];
          gTimeZvonokNextMinutes=ms1m[i+1];
          zad[0]=gHours;
          zad[1]=gMinutes;
        }
        zad[2]=3;
        }
      };
      break;
    case 2 :
      for (int i = 0; i < 31; i++){
        if ( ms2h[i]==gHours && ms2m[i]==gMinutes && ms2type[i] !=33){
          //zad[2]=33;
         // zad[0]=gHours;
          //zad[1]=gMinutes;
          //podzvonka(ms2type[i]);
          if (zad[0]==gHours && zad[1]==gMinutes)
          {
            delay(0);
            tM=String(i);
          } else{
          times=ms2type[i];

          ///zad[2]=3;
          gTimeZvonokNextHours=ms2h[i+1];
          gTimeZvonokNextMinutes=ms2m[i+1];
          zad[0]=gHours;
          zad[1]=gMinutes;
          }
          zad[2]=3;
        }

      };
      break;
    case 3 :
      for (int i = 0; i < 31; i++){
        if (ms3h[i]==gHours && ms3m[i]==gMinutes && ms3type[i] !=33){
          //zad[2]=33;
          
         // podzvonka(ms3type[i]);
          if (zad[0]==gHours && zad[1]==gMinutes)
          {
            delay(0);
            tM=String(i);
          } else{
         times=ms3type[i];
          //zad[2]=3;
          gTimeZvonokNextHours=ms3h[i+1];
          gTimeZvonokNextMinutes=ms3m[i+1];
          zad[0]=gHours;
          zad[1]=gMinutes;
          }
        zad[2]=3;
        }
      };
      break;
    default:
      delay(0);
      times=0;
      break;

  }
}


//функция сравнения времени для заданий для звонка и вызова подачи звонков
void f_zvonok(){
  //
  int tmp=gDays;
  Serial.println(tmp);
  //int zadz[3];//0-часы 1-минуты 3-статус это массив заданий текущий для звонка
//смотрим статус ззаданий если 33 то пропускаем
    /*String timeNow = GetTime();
    jsonWrite(configSetup, timeS,  timeNow);
    sendStatus(timeS, timeNow);
    String timeNow2 = GetWeekday();
    sendStatus(weekdayS, timeNow2);
*/
  //if (zad[2]==33){

  //} else
  //{
    //тут остальной код
    //получаем время часы и минуты gHours gMinutes gDays
    //получаем из планировщика звонков по дню недели тип сценария звонков
    
    Serial.println("--befin-");

    switch (tmp){
      
      case 1 ://воскресенье
        proced1(1);
        break;

      case 2 :
        proced1(2);
        break;

      case 3 :
        proced1(3);
        break;
      case 4 :
        proced1(4);
        break;
      case 5 :
        proced1(5);
        Serial.println("----5-----");
        break;
      case 6 :
        proced1(6);
        break;
      case 0 :
        proced1(7);
        break;
      default :
        Serial.println("--default-");
        break;
    //}




    //далее проходим по масиву и смотрим совпадающие часы а затем минуты а затем тип звонка


  }

}



String topicToCom (String topicS) {
  uint8_t   p = 0;
  boolean f = true;
  uint8_t   u = topicS.length();
  while (p != u) {
    if  (isDigit(topicS.charAt(p))) {
      String kay = topicS.substring(0, p);
      //Serial.println(topicS.charAt(p));
      //Serial.println(kay);
      topicS.replace(kay, kay + " ");
      yield();
      f = false;
    }
    p++;
  }
  if (f) topicS += " ";
  return topicS;
}

#ifdef safeData
// Запись данных в файл с частотой 1 секунда и более. Максимальное количество данных в суточном файле 1440 значений
void safeDataToFile(int inter, String par, uint16_t data) {
  yield();
  // Формируем зоголовок (префикс) Интервал, Параметр, размер_параметра
  uint16_t dataSize = sizeof(data);
  String prifexFile;
  prifexFile += inter;
  prifexFile += "," + par;
  prifexFile += ",";
  prifexFile += dataSize;
  prifexFile += ":";
  uint16_t prifexLen = prifexFile.length(); //Размер префикса

  // Сделаем имя файла
  String fileName = GetDate();
  fileName = deleteBeforeDelimiter(fileName, " "); // удалим день недели
  fileName.replace(" ", ".");
  fileName.replace("..", "."); // Заменяем пробелы точками
  fileName = par + "/" + fileName + ".txt"; // Имя файла параметр в виде директории и дата
  fileName.toLowerCase(); //fileName = "san aug 31 2018"; Имя файла строчными буквами
  File configFile = SPIFFS.open("/" + fileName, "a"); // Открываем файл на добавление
  size_t size = configFile.size();
  yield();
  if (size == 0) {
    configFile.print(prifexFile);
  }
  size = configFile.size();
  // Получим время и определим позицию в файле
  String time = GetTime();
  //time = "00:15:00";
  int timeM = timeToMin(time); // Здесь количество минут с начала суток
  timeM = timeM / inter;
  int poz = timeM * dataSize + prifexLen + 1; // позиция в которую нужно записать.
  int endF = (size - prifexLen) * dataSize + prifexLen + 1; // позиция конца файла
  if (poz >= endF) { // если файл имел пропуски в записи данных
    int i = (poz - endF) / dataSize;
    for (int j = 0; j < i; j++) { // Заполним недостающие данные
      for (int d = 0; d < dataSize; d++) {
        yield();
        configFile.write(0);    // нулями
      }
    }
  }
  yield();
  configFile.write(data >> 8); // добавим текущие
  configFile.write(data);      // данные
  configFile.close();
}
#endif
void f_1(){
  Serial.println("data");
  Serial.println(gData);
  Serial.println("god");
    Serial.println(gGod);
Serial.println("gMecjj");
  Serial.println(gMecjj);
  Serial.println("gHours");

  Serial.println(gHours);
  Serial.println("gMinutes");

  Serial.println(gMinutes);
  Serial.println("gSec");

  Serial.println(gSec);
  Serial.println("gDays");

  Serial.println(gDays);
  Serial.println("ip");

  //Serial.println(WiFi.localIP().toString());

}
void f_d(int i)
{
  int ii;
for (ii=1;ii<i;ii++){
  delay(100);
}

}