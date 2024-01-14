ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer HTTP(80);
ESP8266WebServer HTTPWAN(8080);
// Для файловой системы
File fsUploadFile;
// Для работы символьных имен в режиме AP
DNSServer dnsServer;
WiFiClient wclient;

uint8_t times=0;

//String configSetup = "{}"; // данные для config.setup.json
//String configJson = "{}";  // данные для config.live.json
uint8_t g_jasj;
uint8_t g_minytj;
uint16_t g_god;
uint8_t g_mecjj;
uint8_t g_jiclo;
bool g_nowap;
bool g_teppop;
bool g_cojpanie;
uint8_t gData=10;
uint8_t  gMecjj=10;
uint8_t gGod=0;
uint8_t gHours=0;
uint8_t gMinutes=0;
uint8_t gSec=0;
uint8_t gDays=1;
int gflag1=0;
const byte DS1307 = 0x68; // I2C адрес таймера DS3231

//как часто опрашивать модуль реального времени
uint16_t g_vremjRtc=1;
//g_vremjRtc=333;
//enum { tNTP, tSSDP, tIP, tA0, tDS, tDHT, tSI, tIR, tRC, tPOW, tRSSI, tMQTT, tDDNS, tCRIB };

int ms1h[36];
int ms1m[36];
int ms1type[36];
int ms2h[36];
int ms2m[36];
int ms2type[36];
int ms3h[36];
int ms3m[36];
int ms3type[36];
int mst[6];
int zad[3];//0-часы 1-минуты 3-статус
uint8_t gTimeZvonokNextHours;
uint8_t gTimeZvonokNextMinutes;




StringCommand sCmd;  




String Lang;                    // файлы языка web интерфейса
String chipID;
String pulsList = "{}";
uint8_t pulsNum =1;
String configJson = "{}";            // Здесь все статусы /config.live.json
String configOptions = "{}";         // Здесь данные для всех страниц /config.options.json
String configSetup = "{}";           // Здесь данные для setup /config.setup.json
String configSetupS1 = "{}";  
String configSetupS11 = "{}";         // Здесь данные для setup /config.setup.json
String configSetupS2 = "{}"; 
String configSetupS22 = "{}";          // Здесь данные для setup /config.setup.json
String configSetupS3 = "{}";
String configSetupS33 = "{}";            // Здесь данные для setup /config.setup.json
String configSetupT = "{}";           // Здесь данные для setup /config.setup.json
String configwidgets;            // Здесь список виджетов для загрузки
String ssdpList = "{}";              // SSDP имя ip всех модулей в сети /ssdp.list.json
String regCommands = "{\"command\":[]}";           // список доступных комманд для различных модулей /command.json
//String previousSetup;                // !!! Предыдущий Setup временная мера будет удалена.
String Scenary;                      // Строка обработки сценариев
String modules = "{\"module\":[]}";
String prefix   = "/IoTmanager";
String statusS   = "{}";
String minTime;
String comTime;
String runTime;
String idTime;
//String pTime;
//String comTimeP;
/*
  ------------------------------------------------------------------------------------------------
  Здесь будут храниться все текстовые константы для сокращения кода
*/
const String fileConfigS   = "config.save.json"; // Имя файла конфигурайии
const String fileConfigS1   = "s1.json"; // Имя файла конфигурайии
const String fileConfigS11   = "s11.json"; // Имя файла конфигурайии
const String fileConfigS22   = "s22.json"; // Имя файла конфигурайии
const String fileConfigS33   = "s33.json"; // Имя файла конфигурайии
const String fileConfigS2   = "s2.json"; // Имя файла конфигурайии
const String fileConfigS3   = "s3.json"; // Имя файла конфигурайии
const String fileConfigT   = "t.json"; // Имя файла конфигурайии
const String ScenaryS   = "scenary.save.txt";    // Имя файла сценарии
//const String configSensorS   = "config.sensor.json";
const String configTimerS   = "timer.save.json"; // Имя файла таймеры
// общие
const String texthtmlS   = "text/html";
const String emptyS   = emptyS;
const String titleS   = "title";
const String classS   = "class";
const String btnS   = "btn btn-block btn-lg btn-";
const String infoS   = "info";
const String primaryS   = "primary";
const String onS   = "on";
const String offS   = "off";
const String notS   = "not";
const String langOffS = "{{LangOff}}";
const String langOnS = "{{LangOn}}";
const String wifiS   = "wifi";
const String messageS   = "message";
const String voiceS   = "voice";

// конфигурация
const String langS   = "lang";
const String setIndexS   = "setIndex";
const String ssdpS   = "SSDP";
const String spaceS   = "space";
const String ssidS   = "ssid";
const String ssidPassS   = "ssidPass";
const String wifiConnectS   = "wifiConnect";
const String wifiBlinkS   = "wifiBlink";
const String checkboxIPS   = "checkboxIP";
const String ipS   = "ip";
const String subnetS   = "subnet";
const String getwayS   = "getway";
const String dnsS   = "dns";
const String timeZoneS   = "timeZone";
const String ssidAPS   = "ssidAP";
const String ssidApPassS   = "ssidApPass";
const String configsS   = "configs";
const String ddnsS   = "ddns";
const String ddnsNameS   = "ddnsName";
const String ddnsPortS   = "ddnsPort";
const String mqttS   = "mqtt";
const String mqttServerS   = "mqttServer";
const String mqttPortS   = "mqttPort";
const String mqttUserS   = "mqttUser";
const String mqttPassS   = "mqttPass";
const String timeS   = "time";
const String macS   = "mac";
const String spiffsDataS   = "spiffsData";
const String buildDataS   = "buildData";
const String spiffsS   = "spiffs";
const String buildS   = "build";
const String ntp1S   = "NTP1";
const String ntp2S   = "NTP2";
const String weekdayS   = "weekday";
const String webSocketS   = "webSocket";
// пульс
const String pulseS   = "pulse";
const String pulseComS ="pulseCom";
const String pulseTimeS ="pulseTime";
// Реле
const String relayS   = "relay"; //"stateRelay"; // Состояние реле
const String PinS   = "Pin"; // Для хранения ножек реле
const String NotS   = "Not"; // Для хранения признака инверсии
// PinOut
const String pinOutS   = "pinout"; //"stateRelay"; // Состояние реле
boolean flag = false;

bool bp = false;
bool b1i=false;
bool b2i=false;
bool b3i=false;
bool b1s=false;
bool b2s=false;
bool b3s=false;

//String weekDays[7]={"0", "1", "2", "3", "4", "5", "6"};
//String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
