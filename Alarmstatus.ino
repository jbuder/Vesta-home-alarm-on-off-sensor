//*************************************************************************************************
// Publishing with MQTT the status of D3 on a WEMOS D1 mini, To trigger connect D3 to G
//    Home Assistant conf file =
//    binary_sensor:
//      - platform: mqtt
//        name: Alarm
//        state_topic: "alarm/home"
//        payload_on: "1_alarm_on"
//        payload_off: "0_alarm_off"
//**************************************************************************************************
//  picked bits and pices from diffrent files mainly from ElectronHacks/MQTT_ESP8266_Garage_Door
//  http://www.electronhacks.com/
//


#include <ESP8266WiFi.h>
#include <PubSubClient.h>


//WIFI
const char* wifi_ssid = "XXXXXXXXXX";
const char* wifi_password = "XXXXXXXXXX";

//MQTT
const char* mqtt_server = "XXXXXXXXXX";
const char* mqtt_topic = "alarm/home";
const char* mqtt_user = "XXXXXXXXXX";
const char* mqtt_password = "XXXXXXXXXX";

//VAR
char vInpD3 = 0;
String rx;
int LEDpinred = D0;
int LEDpingreen = D5;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(D3, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(D5, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {\
  Serial.print("RX: ");

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LEDpinred, HIGH);
    digitalWrite(LEDpingreen, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LEDpinred, LOW);
    digitalWrite(LEDpingreen, HIGH);
  }

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_topic,mqtt_user,mqtt_password)) {
      Serial.println("connected");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }

  ///// Evaluate input D3 and send a message if the value changes 
  if (digitalRead(D3) != vInpD3)
  {
   vInpD3 = digitalRead(D3);
   if (vInpD3 == LOW)
   {    
     client.publish(mqtt_topic, "1_alarm_on");
     Serial.println("TX: Alarm ON");
   }
   else
   {
     client.publish(mqtt_topic, "0_alarm_off");
     Serial.println("TX: Alarm OFF");
   }
  }
 
  client.loop();
  delay(10);  
}

