#include "Switch.h"

Switch::Switch(int _lightNo, int _relayPin, int _switchPin, int _switchInterval, int _turnOnValue)
{
  switchPin = _switchPin;
  switchInterval = _switchInterval;
  
  relayPin = _relayPin;
  lightNo = _lightNo;
  
  state = false;
  cause = PowerOn;
  
  turnOnValue = _turnOnValue;
  
  if(turnOnValue == 1)
    turnOffValue = 0;
  else
    turnOffValue = 1;
}

void Switch::TurnOn(Cause _cause)
{
  state = true;
  PrintStatus("TurnOn");
  cause = _cause;
  digitalWrite(relayPin, turnOnValue);
}

void Switch::TurnOff(Cause _cause)
{
  state = false;
  PrintStatus("TurnOff");
  cause = _cause;
  digitalWrite(relayPin, turnOffValue);
}

void Switch::SetState(bool newState, Cause _cause)
{
  state = newState;

  PrintStatus("SetState");
   
  if(state)
    TurnOn(_cause);
  else
    TurnOff(_cause);
}

String Switch::GetStatus()
{
  PrintStatus("GetStatus");
  char response[400];
  snprintf(response, 400,

"{\
  \"State\": \"\"\
}", state);
  
  return response;
}

void Switch::CheckSwitch()
{
  if(switchPin == -1)
    return;

  switchBouncer.update();

  int switchValue = switchBouncer.read();
  
  if(switchValue != previousSwitchValue)
  {
    previousSwitchValue = switchValue;
    SetState(!state, LocalSwitch);
  }
}

void Switch::Setup()
{
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  
  if(switchPin > -1)
  {
    switchBouncer = Bounce();
    switchBouncer.attach(switchPin);
    switchBouncer.interval(switchInterval);
  }
}

void Switch::PrintStatus(String methodName)
{
  Serial.println("Switch::" + methodName);
  Serial.println("  Light: " + String(lightNo));
  Serial.println("  State: " + String(state));
  Serial.println("  Cause: " + String(cause));
}