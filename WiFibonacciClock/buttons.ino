
bool debounce(int pin) {
  bool ret = false, reading = digitalRead(pin);
  reading = !reading;
  if (reading != _lastButtonState[pin]) _lastDebounceTime = millis();

  if ((millis() - _lastDebounceTime) > DEBOUNCE_DELAY_MS) {
    if (reading != _currentButtonState[pin]) {
      _currentButtonState[pin] = reading;
      ret = reading;
      if (canChangeBrightness(pin) && !reading) {
        switchLedStripStatus();
        sendSettings(-1); //Sync all clients
      }
#if DEBUG
      Serial.print(F("Button ")); Serial.print(pin); Serial.print(F(" changed to ")); Serial.println(reading); 
#endif
    } else if (canChangeBrightness(pin) && reading && _timer1 < millis()) {
      fadeLedStrip();
      _timer1 = FADING_DELAY_MS + millis();
    }
  }

  _lastButtonState[pin] = reading;
  return ret;
}

void handleButtons(void) {
  if(debounce(BRIGHTNESS_BUTTON)) {
#if DEBUG
    Serial.print(F("Brightness: ")); Serial.println(_ledStripOn);
#endif
  } else
  if (debounce(MODE_BUTTON)) {
    loadMode(_settings.mode + 1);
    sendSettings(-1); //Sync all clients
  }
}

bool canChangeBrightness(int pin) {
  return !noBrightnessMode(_settings.mode) && pin == BRIGHTNESS_BUTTON;
}
