
uint32_t hexToDec(char* hex) {
  return strtol(hex, NULL, 16);
}

void decToHex(uint32_t dec, char* buffer, size_t bufferSize) {
  String hexString = String(dec, HEX);
  while (hexString.length() < bufferSize - 1) hexString = "0" + hexString;
  hexString.toCharArray(buffer, bufferSize);
}

void formatAndReset(void) {
  format();
#if DEBUG
  Serial.println("Resetting");
#endif
  ESP.reset();
}
