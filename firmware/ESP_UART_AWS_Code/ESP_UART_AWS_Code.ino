#define RXD2 16  // GPIO16 for RX
#define TXD2 17  // GPIO17 for TX

#include <WiFiClientSecure.h>
#include <PubSubClient.h> 
#include <esp_wifi.h>
#include <WiFi.h>

// Wi-Fi Credentials
const char* ssid = "O_ROR";
const char* password = "ojii@0911";

// AWS IoT Endpoint
const char* awsEndpoint = "a2frcjikuz45wt-ats.iot.ap-south-1.amazonaws.com";

// Device Certificate
static const char certificatePemCrt[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAMQ8Vnst9SRyrSQAXH7Z6ETgovssMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNTAyMDcxMDMw
NTRaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC09cFRnHoQJS1JXPZh
W32RHBR5SR/d9ICK7gw7oaqfzGpIuRcdJMRx/14vcfyQr2CDvEv0yVz1YPsceORB
IJ8dgauy0C22opfMxMzNXicwhHJttIKXQn5nQruv+TlwkKBzMj/O3wQJmS4CLVD8
09W0eMq63eL5kOobv/KIRO1MzmiAahGKcmeIhjF7w3haKAwTAAaSsk95k9ddFKDr
R6ZeyyvhBddlo2E+T9Ul8ytpTHoWR2CBVFfU6M8gTdFterdlRJuZZyJXII0pjM8r
wWNiSnvsesKxoKwZULvuM1cnyVq1GXGJUdt0xc0LY5lvN/3gQS43tvl0eIFVVHgV
9JTXAgMBAAGjYDBeMB8GA1UdIwQYMBaAFF+bAFvczw1K15gcX8d9Z211rYCsMB0G
A1UdDgQWBBRSp1mit2xJDAGbbs7U/6eRpIhXoTAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAPhmDQ74UwtZDJiZFL8oz4sel
43bPmzDxwvsOjk1khWy4DhnBrYrQvEJKlAevwgJ5DMxA/nPZMKtjR5hW7me9NKhq
EVaDl76nh8xUEg2KalBehifZ13375lt0g/K0yP1wDKF/HVi850QJXdB+yEG0c1ke
OtB2m+P+TotbZlX1Hzo1IWuXbwKh6fe8RANtm7sxmDUCQXRadQ5tap2TnhUtLas5
kxRSnwd9XpVN71ueuQDQlGtLEDQZWoccIP/mRi2Fkr+FkDXW0v2OSeYiulXaMKfO
2Fe0Ai6HnBMi4Veb680nkThMtw634Snj08J+v4XLRg1Di3YvNYqdt7zcQev1ng==
-----END CERTIFICATE-----

)KEY";

// Device Private Key
static const char privatePemKey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAtPXBUZx6ECUtSVz2YVt9kRwUeUkf3fSAiu4MO6Gqn8xqSLkX
HSTEcf9eL3H8kK9gg7xL9Mlc9WD7HHjkQSCfHYGrstAttqKXzMTMzV4nMIRybbSC
l0J+Z0K7r/k5cJCgczI/zt8ECZkuAi1Q/NPVtHjKut3i+ZDqG7/yiETtTM5ogGoR
inJniIYxe8N4WigMEwAGkrJPeZPXXRSg60emXssr4QXXZaNhPk/VJfMraUx6Fkdg
gVRX1OjPIE3RbXq3ZUSbmWciVyCNKYzPK8FjYkp77HrCsaCsGVC77jNXJ8latRlx
iVHbdMXNC2OZbzf94EEuN7b5dHiBVVR4FfSU1wIDAQABAoIBAHEn/9PdqkJwTOpE
NFja0iEsUu0oucGcQ8kcZA/h3wT/2TJSc06pECJM0oOOnqWG1S5rT3/pbrSOCVhb
jDfhgz37OPee0AcVkyDbq0l8Z7siBz/skYCudsZxZ1X53V4zQfHm6RmeQTMTUz7P
QYZnnIm2wuapG2Z9pLbnh2yI1W6h0Wv1msHG70kIdzEEp4nlG0dMaShp/ZjJ1oFh
rVyH69MfqNdJzIQ2G6TJCAPbj+vaC81Cz6yPMgBoHqrTliYPYYEs8LFl49vJ6m2i
HeawN00uIMR5bi9/hJCDObLTOPgt9Dq/o/MCV7Nzwd1KL9kCI6CduiQI5zZH7I9p
kJhINrkCgYEA6rbA8UIgbCJMIEzreOiCzrgGbjbKwz4xH/ieNEX6TyGqU69rN8Hu
C51vyysyGRGaDJ4J96JgduFVUN3U1rHMuqfAa81F+9SzxXmEZfCXSM2q6zbNhw/f
SWqOa1UUpBNksd9lSMplDGT8n5R1WMDAHi1zJExm/Z9G4K86acskU80CgYEAxV8F
ewPNEYtfMMBTjLyfKqzHWwXVzosJKqz7A6eMl/fCxjJzFr2o7eN2ODARJpX6TjCn
bKkP9ffavMpZ8HJlKJh4VlztNoQJur2nWepJVOXvZ+oRPXM7KplFeKViBCxOcX8K
8Qn/SeZkRwBNvYdeoGUa3p/GoKp3BJhyDFTqbzMCgYApriZ5MVr8mOKX4dD2+aMw
/nD15XkATuz+VnIRqlOW9c1/aulJT4DsQxr1I0iUNxH6J55xgT5MHhu+boY7Ufuf
MebzvdIttEnwSXH/gEf9P7iYaHT7BRCLwwZjfQpbUK5S/+7GjFqBZvWNiRmFl0UG
lt+ZlI+9filiAPwIiXB8CQKBgQCpdnKwMo1KeQ4cP6X8+p729y6cGqB/HKWcPLWx
Z5SxjotvvTVP2zxGNLz2dV7kcHVf2SqHg4kuucbXvi4G41Gzz2XTUSpjWm84JUqh
SyX3fQ1XfYOb7WppovwhIG7OAnS/wkLUvq6w9t42kC4vgyFeOjEd4LWckYBrM7EI
oYhAPQKBgClBHJcyFp0M++Wx5Oii4xwAhOQdGXyaFVj3nLdlKYMFzHZ7qRJeohqr
WeOhKYSQ6i+SJwG1YQJkAwRTF7qGZea6uBWKtuAndU95sZ5P+jhYnnl7Gos3aOs+
a+JEYK62dSDg7OxRuboesl0G1+6O2jLXtle+wqdH4471hOWB/bkL
-----END RSA PRIVATE KEY-----

)KEY";

// Amazon Root CA 1
static const char rootCA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

WiFiClientSecure wiFiClient;
PubSubClient pubSubClient(awsEndpoint, 8883, wiFiClient);

unsigned long lastPublish = 0;
int msgCount = 0;
String AlertStatus,detected,CollisionStatus;
int x,distance;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);  // UART2 for receiving data from STM32
  Serial.println("ESP32 AWS IoT & UART Integration");

  // WiFi setup
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi, IP: " + WiFi.localIP().toString());

  // AWS IoT setup
  wiFiClient.setCACert(rootCA);
  wiFiClient.setCertificate(certificatePemCrt);
  wiFiClient.setPrivateKey(privatePemKey);
}

void loop() {
  pubSubCheckConnect();
  
  // Check for data from STM32
  if (Serial2.available()) {
    String receivedData = Serial2.readStringUntil('\n');
    receivedData.trim(); // Remove unwanted spaces/newline
    Serial.println("Received from STM32: " + receivedData);

    // Convert received data to integer (assuming it's a distance value)
    int data = receivedData.toInt();
    if(data == -1)
    {
      x = 1;  // Set x to 1 when collision is detected
    }
    else
    {
      distance = data; 
    }
    Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");

    // Check for collision (threshold: 10 cm)
    if (x == 1)
    {
       detected = "Collision detected";  // Set collision status
       Serial.println("Collision Detected");
    }
    else
    {
      AlertStatus = (distance < 50) ? "Alert Detected" : "No Alert";
      detected = "No Collision";  // If no collision, set this to "No Collision"
      Serial.print("Alert Status: "); Serial.println(AlertStatus);
    }

    // Publish to AWS IoT
    publishToAWS(distance, AlertStatus, detected);
  }
}

void publishToAWS(int distance, String AlertStatus, String detected) {
  if (millis() - lastPublish > 5000) { // Publish every 5 seconds
    String msg = String("{\"distance\": ") + distance + 
                 ", \"status\": \"" + AlertStatus + "\", \"collision\": \"" + detected + "\" }";
    boolean rc = pubSubClient.publish("outTopic", msg.c_str());
    Serial.print("Published to AWS, rc="); Serial.println(rc ? "OK" : "FAILED");
    lastPublish = millis();
  }
}

void pubSubCheckConnect()
 {
  if (!pubSubClient.connected()) {
    Serial.print("Connecting to AWS IoT...");
    while (!pubSubClient.connected()) {
      Serial.print(".");
      pubSubClient.connect("ESP_Thing");
      delay(1000);
    }
    Serial.println(" Connected to AWS IoT");
    pubSubClient.subscribe("inTopic"); // Subscribe if needed
  }
  pubSubClient.loop();
}

