#ifndef Switch_h
#define Switch_h

#include <Arduino.h>
#include <Bounce2.h>

typedef enum Cause { PowerOn, LocalSwitch, Remote };

class Switch
{
public:
  Switch(int _lightNo, int _relayPin, int _switchPin = -1, int _switchInterval = 50, int _turnOnValue = 0);

  void Setup();
  void TurnOn(Cause _cause);
  void TurnOff(Cause _cause);
  void CheckSwitch();
  void SetState(bool newState, Cause _cause);
  String GetStatus();

protected:
  int switchPin;
  int switchInterval;
  int relayPin;
  int turnOnValue;
  int turnOffValue;
  int previousSwitchValue;
  Bounce switchBouncer;
  bool state;
  Cause cause;
  int lightNo;
  void PrintStatus(String methodName);
};

#endif
