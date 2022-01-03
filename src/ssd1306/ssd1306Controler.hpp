//
// Created by ralf on 03.01.22.
//

#ifndef AQUAMAT_SSD1306CONTROLER_HPP
#define AQUAMAT_SSD1306CONTROLER_HPP

#include "SSD1306AsciiWire.h"

void screenPreSetup();

void screenPostSetup();

void stopTicker();

void startTicker();

void asciiPostSetup();

void asciiPreSetup();

void asciiLoop();

extern SSD1306AsciiWire displayLineTop;
extern SSD1306AsciiWire displayLineBottom;
extern SSD1306AsciiWire displayFull;

#endif //AQUAMAT_SSD1306CONTROLER_HPP
