#pragma once

#include "GPIOConst.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

#define SYSFS_GPIO_DIR "/sys/class/gpio"

class GPIODirection
{
public:
  enum ValueType { INPUT = 0, OUTPUT = 1, INVALID = 99 };

  GPIODirection() : mValue(ValueType::INVALID) { }
  GPIODirection(ValueType aValue) : mValue(aValue) { }
  GPIODirection(std::string aValue) : mValue(to_value_type(aValue)) { }

  ValueType get() const { return mValue; }

  void set(std::string aValue) { mValue = to_value_type(aValue); }
  void set(ValueType   aValue) { mValue = aValue; }

  static ValueType to_value_type(std::string aSzValue)  
  {
    std::string lSzValueUpper = aSzValue;
    std::transform(lSzValueUpper.begin(), lSzValueUpper.end(), lSzValueUpper.begin(), ::toupper); 

    std::cout << "-------" << aSzValue << " - " << lSzValueUpper << std::endl;

    if( 0 == lSzValueUpper.compare("INPUT"))      return ValueType::INPUT;
    else if(0 == lSzValueUpper.compare("OUTPUT")) return ValueType::OUTPUT;
    return ValueType::INVALID;    
  }

  std::string toString() const
  {
    switch(mValue)
    {
      case ValueType::INPUT:   return "INPUT";
      case ValueType::OUTPUT:  return "OUTPUT";
      case ValueType::INVALID: return "INVALID";
    }

    return "???";
  }

protected:

private:
  ValueType mValue;

};


class GPIOMgr
{
public:
  enum PIN_VALUE  { LOW = 0, HIGH = 1 };
  enum EDGE_VALUE { NONE = 0, RISING = 1, FALLING = 2, BOTH = 3 };

  static GPIOMgr *create_instance();
  static GPIOMgr *get_instance();

  int exportPin(unsigned int gpio);
  int unexportPin(unsigned int gpio);
  int setDirection(unsigned int gpio, GPIODirection direction) const;
  int getDirection(unsigned int gpio) const;
  int setValue(unsigned int gpio, PIN_VALUE value) const;
  int getValue(unsigned int gpio) const;
  int setEdge(unsigned int gpio, EDGE_VALUE value) const;
  int getEdge(unsigned int gpio) const;
  std::vector<pins_t> getExportedPins() const;
  int waitForEdge(unsigned int gpio) const;
  void clean();

protected:


private:
  GPIOMgr();
  GPIOMgr(const GPIOMgr&) = delete;
  GPIOMgr(GPIOMgr&& other) = delete;
  virtual ~GPIOMgr();

  std::vector<unsigned int>  mExportedPins;
  static GPIOMgr            *gInstance;
};

template <class T> int writeToSysfs(const char* path, T value) 
{
  std::ofstream stream(path);
  if (!stream) 
  {
    std::cerr << "OPERATION FAILED: Unable to write to sysfs path: " << path
              << std::endl;
    return -1;
  }
  stream << value;
  stream.close();
  return 0;
}

template <class T>
int writeToSysfs(unsigned int gpio, const char* pth, T value) 
{
  char path[50];
  snprintf(path, sizeof(path), SYSFS_GPIO_DIR "/gpio%u%s", gpio, pth);
  return writeToSysfs<T>(path, value);
}

template <class T>
int readFromSysfs(unsigned int gpio, const char* pth, T data) 
{
  char path[50];
  snprintf(path, sizeof(path), SYSFS_GPIO_DIR "/gpio%u%s", gpio, pth);

  std::ifstream stream(path);
  if (!stream) 
  {
    std::cerr << "OPERATION FAILED: Unable to read sysfs path: " << path
              << std::endl;
    return -1;
  }

  stream >> data;
  stream.close();

  return 0;
}