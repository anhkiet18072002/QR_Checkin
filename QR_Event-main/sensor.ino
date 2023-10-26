#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Kaicenter_lau5";
const char* password = "Kai.218PXL";

#define MQTT_SERVER "broker.mqttdashboard.com"
#define MQTT_PORT 1883
#define MQTT_USER "LDP"
#define MQTT_LDP_TOPIC "QR_check"

int cambien = 25;
int giatri;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connect_to_broker() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "IoTLab4";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), MQTT_USER, NULL)) {
      Serial.println("connected");
      client.subscribe(MQTT_LDP_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}

void send_data(int data) {
  client.publish(MQTT_LDP_TOPIC, String(data).c_str());
  delay(1000);
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(500);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  connect_to_broker();
  pinMode(cambien, INPUT);
}

void loop() {
  giatri = digitalRead(cambien);
  Serial.print("Gia tri cam bien la: ");
  Serial.println(giatri);
  client.loop();
  if (!client.connected()) {
    connect_to_broker();
  }
  send_data(giatri);
}