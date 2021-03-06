

bool readPalettes(void) {
  bool succeeded = true;
  Dir dir = SPIFFS.openDir(PALETTES_PATH);
  while (dir.next()) {
    File palette = dir.openFile("r");
    if (!readFile(palette, loadPaletteJson)) succeeded = false;
    palette.close();
    yield();
  }
  return succeeded;
}

bool writePalette(String fileName, String json) {
  return writeTxtFile((String)PALETTES_PATH + '/' + fileName, json);
}

void deletePalette(uint8_t index) {
  if (deleteFile((String)PALETTES_PATH + '/' + _palettesV.at(index).name + ".json")) {
    _settings.palette = 0;
    _palettesV.erase(_palettesV.begin() + index);
    refreshIfModeIs(CLOCK_MODE);
  }
}

bool readSettings(void) {
  bool succeeded = false;
#if DEBUG
    Serial.print(F("Opening: "));Serial.println(SETTINGS_FILE_PATH);
#endif
  File settings = SPIFFS.open(SETTINGS_FILE_PATH, "r");
  succeeded = readFile(settings, loadSettingsJson);
  settings.close();
  return succeeded;
}

void writeSettings(String json) {
  writeTxtFile(SETTINGS_FILE_PATH, json);
}

bool readFile(File file, std::function<bool (char* json, String fileName)> callback) {
  if (file) {
    String fileName = file.name();
    size_t fileSize = file.size();
#if DEBUG
    Serial.print(F("Reading "));Serial.print(fileSize);Serial.print(F(" bytes from "));Serial.println(fileName);
#endif
    if (fileSize <= 1024) {
      String content = file.readStringUntil('\n');
      return callback((char*)content.c_str(), getBaseName(fileName));
#if DEBUG
    } else {
      Serial.println(F("file size is too large"));
#endif
    }
#if DEBUG
  } else {
    Serial.println(F("file open failed"));
#endif
  }
  return false;
}

bool writeTxtFile(String path, String content) {
  File file = SPIFFS.open(path, "w");
  if (file) {
#if DEBUG
    Serial.print(F("Writing content: "));Serial.print(content);Serial.print(F(" to: "));Serial.println(path);
#endif  //DEBUG
    file.print(content);
    file.close();
    return true;
#if DEBUG
  } else {
    Serial.print(F("file open failed: "));Serial.println(path);
#endif  //DEBUG
  }
  return false;
}

bool deleteFile(String path) {
  if (SPIFFS.remove(path)) {
    return true;
#if DEBUG
    Serial.print(path); Serial.println(F(" deleted"));
  } else {
    Serial.print(F("file delete failed: "));Serial.println(path);
#endif  //DEBUG
  }
  return false;
}

bool format() {
#if DEBUG
  Serial.println("Formatting");
#endif
  return SPIFFS.format();
}

String getBaseName(String fileName) {
  return fileName.substring(fileName.lastIndexOf('/') + 1, fileName.lastIndexOf('.'));
}
