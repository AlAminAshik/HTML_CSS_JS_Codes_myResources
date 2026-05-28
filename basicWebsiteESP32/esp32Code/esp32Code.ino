#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Drishti Tech";
const char* password = "dtl@2023";

const int buttonPin = 1;   // GPIO to read the switch

/* 80 is the deafult TCP port number on which ESP32's HTTP server listens http://192.168.0.106/mystatus
if we want to use another port "8080, 3000, 5000" we need to explicitely mention it: http://192.168.0.106:8080/mystatus
*/
WebServer server(80); 

// this function is called when browser opens /status
void handleStatus() {
  int state = digitalRead(buttonPin);

  //this is important otherwire the browser will block fetching and no response
  //this is needed otherwise fetch() will fail
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");

  //we send simple raw text, no formatting, no JSON parsing and lightweight data using text/plain and js uses response.text()
  //other types of content are, image/png, application/json(structured data)
  // return plain text: "pressed" or "not pressed"
  if (state == LOW) {
    server.send(200, "text/plain", "pressed"); // 200 is the status code for success, text/plain is the content type, "pressed" is the response body.
    Serial.println("pressed");
  } else {
    server.send(200, "text/plain", "not pressed");
    Serial.println("not pressed");
  }

  /*what status codes mean
  code    Meaning       for generic use
  200       ok              yes
  201      created          maybe
  204     No content        no
  400     Bad request       no
  404     Not found         no
  500     server error      no
  210..   not standard      no
  */
}

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP); // internal pull-up

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected. ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // create URL/API endpoint
  server.on("/mystatus", handleStatus);   //url is: http://192.168.0.106/mystatus
  //server.on("/led/on", handleLedOn);    //url is: http://192.168.0.106/led/on
  //server.on("/temperature", handleTemp);//url is: http://192.168.0.106/temperature

  server.begin();
}

void loop() {
  //server.handleclient checks if a client is requesting something, if so it processes immediately
  //handles incoming requests
  //the refresh rate is set by the javasript code setInterval(fetchSwitchStatus, 500); (polling speed)
  server.handleClient();
}
