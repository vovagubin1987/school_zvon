// ------------- Чтение значения json
String jsonRead(String &json, String name) {
  DynamicJsonDocument doc(1024);
  //JsonObject root = jsonBuffer.parseObject(json);
  //JsonObject& root = jsonBuffer.parseObject(json);
  //Serial.println(doc.capacity());

  DeserializationError error = deserializeJson(doc, json);
  //return root[name].as<String>();
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    
  }
  return doc[name].as<String>();
}

/*String jsonReadFileInt(String &json, String name) {
  String path="/"+json;
  File file = LittleFS.open(path, "r");
  DynamicJsonDocument doc(1024);
  //JsonObject root = jsonBuffer.parseObject(json);
  //JsonObject& root = jsonBuffer.parseObject(json);

  DeserializationError error = deserializeJson(doc, file);
  //return root[name].as<String>();
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    //Serial.println(error.f_str());
    
  }
  tmp = doc[name].as<String>();
  file.close;
  return tmp;

}
int jsonReadToInt2(String &json, String name) {
 return jsonReadFileInt(json, name).toInt();
}*/

int jsonReadToInt(String &json, String name) {
  return jsonRead(json, name).toInt();
}
float jsonReadToFloat(String &json, String name) {
  return jsonRead(json, name).toFloat();
}
// -------------- Чтение configSetup -------------------------------
String getSetup(String Name) {
  return jsonRead(configSetup, Name);
}
int getSetupInt(String Name) {
  return jsonReadToInt(configSetup, Name);
}
float getSetupFloat(String Name) {
  return jsonReadToFloat(configSetup, Name);
}
// -------------- Чтение configOptions --------------------
String getOptions(String Name) {
  return jsonRead(configOptions, Name);
}
int getOptionsInt(String Name) {
  return jsonReadToInt(configOptions, Name);
}
float getOptionsFloat(String Name) {
  return jsonReadToFloat(configOptions, Name);
}
// -------------- Чтение configJson     -----------------------------------------------
String getStatus(String Name) {
  return jsonRead(configJson, Name);
}
int getStatusInt(String Name) {
  return jsonReadToInt(configJson, Name);
}

int gets1StatusInt(String Name) {
  return jsonReadToInt(configJson, Name);
}
int gets2StatusInt(String Name) {
  return jsonReadToInt(configJson, Name);
}
int gets3StatusInt(String Name) {
  return jsonReadToInt(configJson, Name);
}
int getAllStatusInt(String conf, String Name) {
  return jsonReadToInt(conf, Name);
}
float getStatusFloat(String Name) {
  return jsonReadToFloat(configJson, Name);
}


// ------------- Чтение значения json
int jsonReadtoInt(String &json, String name) {
  //DynamicJsonBuffer jsonBuffer(1024);
  DynamicJsonDocument doc(1024);
  //JsonObject& root = jsonBuffer.parseObject(json);
  deserializeJson(doc, json);
  return doc[name];
}

// ------------- Запись значения json String
String jsonWrite(String &json, String name, String volume) {
  //DynamicJsonBuffer jsonBuffer(1024);
  DynamicJsonDocument doc(1024);
  //JsonObject& root = jsonBuffer.parseObject(json);
  deserializeJson(doc, json);
  doc[name] = volume;
  ///json = "";
  //root.printTo(json);
  json = emptyS;
  serializeJson(doc,json);
  return json;
}

// ------------- Запись значения json int
String jsonWrite(String &json, String name, int volume) {
  //DynamicJsonBuffer jsonBuffer(1024);
  DynamicJsonDocument doc(1024);
  //JsonObject& root = jsonBuffer.parseObject(json);
  deserializeJson(doc, json);
  //root[name] = volume;
  doc[name]=volume;
  ///json = "";
  //root.printTo(json);
  json = emptyS;
  serializeJson(doc,json);
  return json;
}

// ------------- Запись значения json float
String jsonWrite(String &json, String name, float volume) {
  //DynamicJsonBuffer jsonBuffer(1024);
  DynamicJsonDocument doc(2048);
  //JsonObject& root = jsonBuffer.parseObject(json);
  deserializeJson(doc, json);
  //root[name] = volume;
  doc[name]=volume;
  ///json = "";
  //root.printTo(json);
  json = emptyS;
  serializeJson(doc,json);
  return json;
}

// ------------- Запись строки в файл
String writeFile(String fileName, String strings ) {
  File configFile = LittleFS.open("/" + fileName, "w");
  if (!configFile) {
    Serial.print("Failed to open config file");
    return "Failed to open config file";
  }
  configFile.print(strings);
  //strings.printTo(configFile);
  configFile.close();
  return "Write sucsses";
}


void saveConfig (){
  writeFile("config.json", configSetup );
}

// ------------- Чтение файла в строку
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

void sendSetupS1(String Name, String volume) {
  jsonWrite(configSetupS1, Name, volume);
}
void sendSetupS11(String Name, String volume) {
  jsonWrite(configSetupS11, Name, volume);
}
void sendSetupS22(String Name, String volume) {
  jsonWrite(configSetupS22, Name, volume);
}
void sendSetupS33(String Name, String volume) {
  jsonWrite(configSetupS33, Name, volume);
}
void sendSetupS2(String Name, String volume) {
  jsonWrite(configSetupS2, Name, volume);
}
void sendSetupS3(String Name, String volume) {
  jsonWrite(configSetupS3, Name, volume);
}
void sendSetupT(String Name, String volume) {
  jsonWrite(configSetupT, Name, volume);
}

void sendSetup(String Name, String volume) {
  jsonWrite(configSetup, Name, volume);
}
// ------------- Отправить данные в Setup int -----------------------
void sendSetup(String Name, int volume) {
  jsonWrite(configSetup, Name, volume);
}
// ------------- Отправить данные в Setup float ------------
void sendSetupF(String Name, float volume) {
  jsonWrite(configSetup, Name, volume);
}
// ------------- Отправить данные в Status String ------------------------------
boolean sendStatus(String Name, String volume) {
  jsonWrite(configJson, Name, volume);
  return true;
}
// ------------- Отправить данные в Status int -----------------------
boolean sendStatus(String Name, int volume) {
  jsonWrite(configJson, Name, volume);
  return true;
}
// ------------- Отправить данные в Status float ----------
boolean sendStatusF(String Name, float volume) {
  jsonWrite(configJson, Name, volume);
  return true;
}
// ------------- Отправить данные в Options String ------------------------------
void sendOptions(String Name, String volume) {
  jsonWrite(configOptions, Name, volume);
}
// ------------- Отправить данные в Options int -----------------------
void sendOptions(String Name, int volume) {
  jsonWrite(configOptions, Name, volume);
}
// ------------- Отправить данные в Options float ----------
void sendOptionsF(String Name, float volume) {
  jsonWrite(configOptions, Name, volume);
}
// ------------- Копируем параметр из Setup Options
void setupToOptions(String Name){
  sendOptions(Name,getSetup(Name));
  }
// ------------- Копируем параметр из Setup Options
void setupToStatus(String Name){
  sendStatus(Name,getSetup(Name));
  }




