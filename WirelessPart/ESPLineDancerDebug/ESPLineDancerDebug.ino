#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define wifi_ssid "Robot14"
#define wifi_password "ciscocisco"

#define mqtt_server "192.168.137.1"
#define mqtt_port 1883

#define in_topic "/light/in"
#define in_x "/point/x"
#define in_y "/point/y"
#define in_z "/point/z"
#define out_topic "/light/out" //output

// Replace by 2 if you aren't enable to use Serial Monitor... Don't forget to Rewire R1 to GPIO2!
#define in_led 2

int lastTimeSend;
const int waitTime = 500;

WiFiClient espClient;
PubSubClient client;

void setup() {
  Serial.begin(115200);
  pinMode(in_led, OUTPUT);
  digitalWrite(in_led, HIGH);
  setup_wifi();
  client.setClient(espClient);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(in_led, OUTPUT);
  digitalWrite(in_led, HIGH);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
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

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe(in_x);
      client.subscribe(in_y);
      client.subscribe(in_z);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
 for (int i = 0; i < length; i++) {
  char receivedChar = (char)payload[i];
  Serial.print(receivedChar);
  if (topic == in_x ){
    Serial.print("x");
  }
  else if ( topic == in_y) {
    Serial.print("y");
  }
  else if ( topic == in_z ){
    Serial.print(" pen");
  }
 }
 Serial.println();
}

void loop() {
  if (!client.connected()) {
    digitalWrite(in_led, HIGH);
    reconnect();
  }
  digitalWrite(in_led, LOW);
  client.loop();
  // Publishes a random 0 and 1 like someone switching off and on randomly (random(2))
  if(millis() > lastTimeSend + waitTime){
      client.publish(out_topic, "Online", true);
      lastTimeSend = millis();
  }

  delay(100);
  
  
  //delay(1000);
}
