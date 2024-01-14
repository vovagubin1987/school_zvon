  

          //Содержится в пакете


void delTimer(){}

void initNTP() {
  if (getStatusInt(wifiS) == 3) { //Если есть подключение к роутеру
    String ntpTemp = readArgsString();
    sendOptions(ntp1S, ntpTemp);
    ntpTemp = readArgsString();
    sendOptions(ntp2S, ntpTemp);
        Serial.println("metka48");

    //
    Serial.println(getOptions(messageS));
    if ( getOptions(messageS) == emptyS) { // Если нет связи с интернет пробуем получить время с роутера
      sendOptions(ntp1S, WiFi.gatewayIP().toString()); // Для этого заменяем адрес NTP сервера на адрес роутера
          Serial.println("48---");

    }
    sCmd.addCommand("time", handle_time);
        Serial.println("47----");

    timeSynch();
    //
        Serial.println("metka 49");

    Serial.println(GetTime());
    if (GetTime() != "00:00:00") { // Проверка на получение времени
      // задача проверять таймеры каждую секунду обновлять текущее время.
      //ts.add(tNTP, 1000, [&](void*) {
        String timeNow = GetTime();
        if (timeNow == "00:00:00") { // в это время синхронизируем с внешним сервером
          String timeNow = GetWeekday(); // Новая дата
          sendStatus(weekdayS, timeNow);
          timeSynch();
          //loadTimer();

        //}
        }

      if (timeNow == getOptions("timersT")) {
      sCmd.readStr(getOptions("timersC"));
      //
      
      if (getOptions("timersR")=="1") delTimer();
      //if (getOptions("timersR")=="1");
        sendOptions("timersT", " ");
        sendOptions("timersC", " ");
        //loadTimer();
    }
        sendStatus(timeS, timeNow);
        sendOptions(timeS, timeNow);
        jsonWrite(configSetup, timeS,  timeNow);
      //}, nullptr, true);
      sCmd.addCommand("zone", handle_timeZone);
      //modulesReg("ntp");
    }
  }
}

// ------------------------------ Установка времянной зоны
void handle_timeZone() {
  int timezone = readArgsInt();
  sendSetup(timeZoneS,  timezone);
  sendOptions(timeZoneS, timezone);
  timeSynch();
  saveConfigSetup ();
}

// ------------------------------ Комманда синхронизации времени
void handle_time() {
  timeSynch();
  statusS = "{}";
  jsonWrite(statusS, "title",   "{{LangTime1}} <strong id=time>" + GetTime() + "</strong>");
}

void timeSynch() {
  uint8_t zone = getOptionsInt(timeZoneS);
  Serial.println(WiFi.dnsIP());
  String ntp1 = getOptions(ntp1S);
  String ntp2 = getOptions(ntp2S);
  if (ntp1 == emptyS) ntp1 = "ntp1.vniiftri.ru";
  if (ntp2 == emptyS) ntp2 = "ru.pool.ntp.org";
  //hak
  ntp1 = "ntp1.vniiftri.ru";
  ntp2 = "ru.pool.ntp.org";
  zone = 3;
  //end hak
          Serial.println("metka timesync1");

  if (WiFi.status() == WL_CONNECTED) {
    // Инициализация UDP соединения с NTP сервером
    //configTime(zone * 3600, 0, ntp1.c_str(), ntp2.c_str());
    configTime(zone * 3600, 0, ntp1, ntp2);
     ///timeClient.update();
    
    Serial.println("metka timesync1.1");
    //
    uint8_t i = 0;
    //while (!time(nullptr) && i < 7) {
     // while ( i < 7) {
     // i++;
     // delay(1000);
   //}
    Serial.println("metka timesync2");

    String timeNow = GetTime();
    jsonWrite(configSetup, timeS,  timeNow);
    sendStatus(timeS, timeNow);
    String timeNow2 = GetWeekday();
    sendStatus(weekdayS, timeNow2);
    Serial.println("metka timesync3");
    time_t now1=time(nullptr); // получаем время с помощью библиотеки time.h
    while (now1<1000000000){
      now1=time(nullptr);
      i++;
      if (i>120){
        break;

      }
      delay(500);
    }
  String Time; // Строка для результатов времени
  Time += ctime(&now1); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
  uint8_t ii = Time.indexOf(":"); //Ишем позицию первого символа :
  Serial.println("metka timesync4");
  Serial.println(Time);
  /*gHours=(Time.substring(ii - 2,2)).toInt();
  gMinutes=(Time.substring(ii +1, 2)).toInt();
  gSec=(Time.substring(ii +4, 2)).toInt();
  gGod=(Time.substring(ii +7, 4)).toInt();
  if (gGod>2000){
    gGod=gGod-2000;
  } else{
    gGod=gGod-1900;
  }
  */
  Serial.println("metka timesync5");
  struct tm tm1;
  localtime_r(&now1, &tm1);
  Serial.println("metka timesync6");
  gGod=(tm1.tm_year)-100;
  gMinutes=(tm1.tm_min);
  gSec=(tm1.tm_sec);
  gDays=(tm1.tm_wday);
  Serial.println("metka timesync7");
  gMecjj=(tm1.tm_mon)+1;
  Serial.println("metka timesync8");
  gData=(tm1.tm_mday);
  gHours=(tm1.tm_hour);
  Serial.println("metka timesync9");
  while (gflag1==1){
//Serial.println("metka timesync9");
    }
  Serial.println("metka timesync5");
  if (now1>1000000000){
    Serial.println("metka timesync9_7");
    setDateDs1307(gSec,gMinutes,gHours,gDays,gData,gMecjj,gGod);
}

  //int timei = times.toInt();


  }
}
// Получение текущего времени
String GetTime() {
  
  //time_t now = time(&now); // получаем время с помощью библиотеки time.h
  time_t now1=time(nullptr);
  struct tm tm1;
  // получаем время с помощью библиотеки time.h
  String Time; // Строка для результатов времени
  Time += ctime(&now1); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
  uint8_t i = Time.indexOf(":"); //Ишем позицию первого символа :
  Time = Time.substring(i - 2, i + 6); // Выделяем из строки 2 символа перед символом : и 6 символов после
  return Time; // Возврашаем полученное время
  
  
}
String GetTimeH() {
  /*time_t now = time(nullptr); // получаем время с помощью библиотеки time.h
  String Time; // Строка для результатов времени
  Time += ctime(&now); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
  uint8_t i = Time.indexOf(":"); //Ишем позицию первого символа :
  Time = Time.substring(i - 2,2); // Выделяем из строки 2 символа перед символом : и 6 символов после
  return Time; // Возврашаем полученное время*/
  time_t now1;
  time(&now1);
  struct tm tm1;
  localtime_r(&now1,&tm1);
  int p=(tm1.tm_hour);
  return String(p);
}
String GetTimeM() {
  /*time_t now = time(nullptr); // получаем время с помощью библиотеки time.h
  String Time; // Строка для результатов времени
  Time += ctime(&now); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
  uint8_t i = Time.indexOf(":"); //Ишем позицию первого символа :
  Time = Time.substring(i +1, 2); // Выделяем из строки 2 символа перед символом : и 6 символов после
  return Time; // Возврашаем полученное время*/
  time_t now1;
  time(&now1);
  struct tm tm1;
  localtime_r(&now1,&tm1);
  int p=(tm1.tm_min);
  return String(p);
}
String GetTimeS() {
  /*time_t now = time(nullptr); // получаем время с помощью библиотеки time.h
  String Time; // Строка для результатов времени
  Time += ctime(&now); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
  uint8_t i = Time.indexOf(":"); //Ишем позицию первого символа :
  Time = Time.substring(i +4, 2); // Выделяем из строки 2 символа перед символом : и 6 символов после
  return Time; // Возврашаем полученное время
  */
  time_t now1;
  time(&now1);
  struct tm tm1;
  localtime_r(&now1,&tm1);
  int p=(tm1.tm_sec);
  return String(p);
}

// Получение даты
String GetDate() {
  time_t now1;
  time(&now1);
  struct tm tm1;
  //localtime_r(&now,tm); // получаем время с помощью библиотеки time.h
  String Data; // Строка для результатов времени
  Data += ctime(&now1); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
  Data.replace("\n", emptyS);
  uint8_t i = Data.lastIndexOf(" "); //Ишем позицию последнего символа пробел
  String Time = Data.substring(i - 8, i + 1); // Выделяем время и пробел
  Data.replace(Time, emptyS); // Удаляем из строки 8 символов времени и пробел
  return Data; // Возврашаем полученную дату
}
// Получение дня недели
int GetWeekdayNumber() {
  /*String Data = GetDate();
  uint8_t i = Data.indexOf(" "); //Ишем позицию первого символа пробел
  String weekday = Data.substring(i - 3, i); // Выделяем время и пробел
  return weekday;
  localtime
  
  time_t now = time(nullptr); // получаем время с помощью библиотеки time.h
  char Time; // Строка для результатов времени
  //Time += ctime(&now); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
    //timeinfo = 
    strftime (Time,5,"%w",localtime (&now));
  return Time;*/
  time_t now1;
  time(&now1);
  struct tm tm1;
  localtime_r(&now1,&tm1);
  int p=(tm1.tm_wday);
  return p;
}
String GetWeekday() {
  String Data = GetDate();
  uint8_t i = Data.indexOf(" "); //Ишем позицию первого символа пробел
  String weekday = Data.substring(i - 3, i); // Выделяем время и пробел
  return weekday;
}
void f_ntp()
{
  timeSynch();
  f_1();
};
