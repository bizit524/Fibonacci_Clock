

#ifndef _STRUCTURES_H
#define _STRUCTURES_H

typedef struct {
  struct {
    uint32_t flashLightColor;
    uint32_t rainbowDelay;
    uint32_t pulseColor;
    uint8_t pulseDelay;
    uint32_t randomDelay;
    uint8_t randomEase;
    uint8_t mode;
    uint8_t brightness;
    uint8_t palette;
  };
} Settings;

typedef struct {
  union {
    uint32_t at[4];
    struct {
      uint32_t off;
      uint32_t hours;
      uint32_t minutes;
      uint32_t both;
    };
  };
  String name;
} Palette;

#endif  //_STRUCTURES_H
