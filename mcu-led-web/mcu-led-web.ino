#include <ESP8266WiFi.h>
 
const char* ssid = "CFT";
const char* password = "1018501491";
 
const int roja = 14;
const int amarilla=12;
const int verde=13;

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(roja, OUTPUT);
  pinMode(amarilla,OUTPUT);
  pinMode(verde,OUTPUT);
  digitalWrite(roja, 0);
  digitalWrite(amarilla,0);
  digitalWrite(verde,0);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  digitalWrite(verde, 1);
  delay(100);
  digitalWrite(verde, 0);
  delay(100);
  
  digitalWrite(verde, 1);
  delay(100);
  digitalWrite(verde, 0);
  delay(100);

  digitalWrite(verde, 1);
  delay(100);
  digitalWrite(verde, 0);
  delay(100);
  
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int valor_roja = 0;
  int valor_amarilla=0;
  int valor_verde=0;
  if (request.indexOf("/roja=ON") != -1)  {
    digitalWrite(roja, 1);
    valor_roja = 1;
  }
  if (request.indexOf("/roja=OFF") != -1)  {
    digitalWrite(roja, 0);
    valor_roja = 0;
  }if (request.indexOf("/amarilla=ON") != -1)  {
    digitalWrite(amarilla, 1);
    valor_amarilla = 1;
  }
  if (request.indexOf("/amarilla=OFF") != -1)  {
    digitalWrite(amarilla, 0);
    valor_amarilla = 0;
  }if (request.indexOf("/verde=ON") != -1)  {
    digitalWrite(verde, 1);
    valor_verde = 1;
  }
  if (request.indexOf("/verde=OFF") != -1)  {
    digitalWrite(verde, 0);
    valor_verde = 0;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.println("color que esta prendido: ");

  String leds="";
 
  if(valor_roja ==1) {
    leds += "roja, ";
  }
  
  else if(valor_amarilla ==1) {
    leds += "amarilla, ";
  }
  
  else if(valor_verde ==1) {
    leds += "verde";
  }

  client.print(leds);

  
  client.println("<h1>primera pag andres</h1>");
  client.println("<br><br>");
  client.println("<a href=\"/roja=ON\"\"><button>prender roja </button></a>");
  client.println("<a href=\"/roja=OFF\"\"><button>apagar roja </button></a><br />");
  client.println("<a href=\"/amarilla=ON\"\"><button>prender amarilla </button></a>");
  client.println("<a href=\"/amarilla=OFF\"\"><button>apagar amarilla </button></a><br />");  
  client.println("<a href=\"/verde=ON\"\"><button>prender verde </button></a>");
  client.println("<a href=\"/verde=OFF\"\"><button>apagar verde </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
