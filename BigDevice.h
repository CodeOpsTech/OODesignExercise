#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <boost/format.hpp>
#include "stringbuilder.h"

/*
* DISCLAIMER
* 
* 1) This source code has been provided as-is for the purpose of learning 
* 2) The code snippet/samples shown here are only meant to highlight concepts provided in the training
*    They may not cover all important, clean coding & best practices like documentation comments or naming conventions (e.g., PC-Lint rules)
* 3) Some part of code/class abstractions may have been intentionally edited
*/

/// <summary>
/// Refactor the BigDevice class to respect SOLID principles and design patterns.
/// Axis of change:
/// 	a) support for new device types
/// b) support more languages
/// 	c) support for new kinds of data formats such as JSON and XML reports
///
/// You can make any change you see fit, in code or tests.
/// </summary>

class BigDevice {
    // named constants for different types of devices
public:
    static constexpr int MEDICAL = 0;
    static constexpr int AGRI = 1;
    static constexpr int REFINARY = 2;

    // properties common to all devices
    int type = 0;
    bool status = true;
    int deviceId = 0;

    // properties for individual types of devices
    int soilQuality = 0; // for Agricultural device
    int heartRate = 0; // for Medical device
    int temperature = 0; // for Refinary device

    // constants for English and Dutch language
    static constexpr int EN = 1;
    static constexpr int DU = 2;

    BigDevice(int type, int deviceId, bool status, int value);

    virtual void toggleStatus();

    static std::string getStatus(BigDevice* device, int language);

    static std::string printStatus(std::vector<BigDevice*>& devices, int userLanguage);

    static std::string getLine(int deviceType, int userLanguage, int numberOfDevices);
    static void main(std::vector<std::string>* args, int userLanguage);

private:
    static std::string translateDevice(int type, int userLanguage);
};
