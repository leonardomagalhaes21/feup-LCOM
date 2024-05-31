#include "type.h"

int processScanCode(uint8_t scancode) {
  if (scancode == 0x1E) { 
    name[indexName] = "a";
    indexName++;
  }
  else if (scancode == 0x30) { 
    name[indexName] = "b";
    indexName++;
  }
  else if (scancode == 0x2E) { 
    name[indexName] = "c";
    indexName++;
  }
  else if (scancode == 0x20) { 
    name[indexName] = "d";
    indexName++;
  }
  else if (scancode == 0x12) { 
    name[indexName] = "e";
    indexName++;
  }
  else if (scancode == 0x21) { 
    name[indexName] = "f";
    indexName++;
  }
  else if (scancode == 0x22) { 
    name[indexName] = "g";
    indexName++;
  }
  else if (scancode == 0x23) { 
    name[indexName] = "h";
    indexName++;
  }
  else if (scancode == 0x17) { 
    name[indexName] = "i";
    indexName++;
  }
  else if (scancode == 0x24) {
    name[indexName] = "j";
    indexName++;
  }
  else if (scancode == 0x25) {
    name[indexName] = "k";
    indexName++;
  }
  else if (scancode == 0x26) {
    name[indexName] = "l";
    indexName++;
  }
  else if (scancode == 0x32) {
    name[indexName] = "m";
    indexName++;
  }
  else if (scancode == 0x31) {
    name[indexName] = "n";
    indexName++;
  }
  else if (scancode == 0x18) {
    name[indexName] = "o";
    indexName++;
  }
  else if (scancode == 0x19) {
    name[indexName] = "p";
    indexName++;
  }
  else if (scancode == 0x10) {
    name[indexName] = "q";
    indexName++;
  }
  else if (scancode == 0x13) {
    name[indexName] = "r";
    indexName++;
  }
  else if (scancode == 0x1F) {
    name[indexName] = "s";
    indexName++;
  }
  else if (scancode == 0x14) {
    name[indexName] = "t";
    indexName++;
  }
  else if (scancode == 0x16) {
    name[indexName] = "u";
    indexName++;
  }
  else if (scancode == 0x2F) {
    name[indexName] = "v";
    indexName++;
  }
  else if (scancode == 0x11) {
    name[indexName] = "w";
    indexName++;
  }
  else if (scancode == 0x2D) {
    name[indexName] = "x";
    indexName++;
  }
  else if (scancode == 0x15) {
    name[indexName] = "y";
    indexName++;
  }
  else if (scancode == 0x2C) {
    name[indexName] = "z";
    indexName++;
  }
}
