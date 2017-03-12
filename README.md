# Switch
Arduino managed switch that allows local and remote control and can report on the status

## ESP8266 Example

```Arduino
int httpPort = 80;
ESP8266WebServer httpServer = ESP8266WebServer(httpPort);

int switchNo = 1;
int buttonId = 5;
int relayId = 12;
Switch lightSwitch1 = Switch(1, 5, 12);

void setup(void){
    httpServer.begin();

    lightSwitch1.Setup();

    httpServer.on("/1/On", [&] (){ 
        lightSwitch1.TurnOn(Remote);
        httpServer.send(200, "text/html", "TurnOnSuccess");
    });

    httpServer.on("/1/Off", [&] (){
        lightSwitch1.TurnOff(Remote);
        httpServer.send(200, "text/html", "TurnOffSuccess");
    });

    httpServer.on("/1/Status", [&] (){
        String light1Status = lightSwitch1.GetStatus();
        httpServer.send(200, "text/html", light1Status);
    });
}

void loop(void){
  lightSwitch1.CheckSwitch();
  
  httpServer.handleClient();
}
```