#include "BigDevice.h"

BigDevice::BigDevice(int type, int deviceId, bool status, int value)
{
	this->type = type;
	this->deviceId = deviceId;
	this->status = status;
	switch (type)
	{
	case BigDevice::MEDICAL:
		this->heartRate = value;
		break;
	case BigDevice::AGRI:
		this->soilQuality = value;
		break;
	case BigDevice::REFINARY:
		this->temperature = value;
		break;
	default:
		throw std::invalid_argument("Invalid value for argument value");
	}
}

void BigDevice::toggleStatus()
{
	status = !status;
}

std::string BigDevice::getStatus(BigDevice *device, int language)
{
	std::string onOrOff;
	std::string statusMessage;

	// If not English, then Dutch
	if (language == EN)
	{
		statusMessage = "OnOff";
		onOrOff = device->status ? "ON" : "OFF";
	}
	else
	{
		statusMessage = "Toestand";
		onOrOff = device->status ? "OP" : "UIT";
	}

	switch (device->type)
	{
		case BigDevice::MEDICAL:
			return statusMessage + onOrOff + std::to_string(device->heartRate);
		case BigDevice::AGRI:
			return statusMessage + onOrOff + std::to_string(device->soilQuality);
		case BigDevice::REFINARY:
			return statusMessage + onOrOff + std::to_string(device->temperature);
	}
	return "";
}

std::string BigDevice::printStatus(std::vector<BigDevice*> &devices, int userLanguage)
{
	 std::string returnString = "";

	 // test list is empty
	 if (devices.empty())
	 {
		 returnString = userLanguage == EN ? "<h1>Empty list of devices!</h1>" : "<h1>Lege lijst met apparaten!</h1>";
	 }
	 else
	 {
		 // we have devices
		 // let's create a header
		 if (userLanguage == EN)
		 {
			 returnString += std::string("<h1>Devices report</h1><br/>");
		 }
		 else
		 {
			 // default is Dutch
			 returnString += std::string("<h1>apparaten Report</h1><br/>");
		 }

		 int numberMedical = 0;
		 int numberAgricultural = 0;
		 int numberRefinaries = 0;
		 {
			 // Get status of the devices 
			 for (auto device : devices)
			 {
				 if (device->type == BigDevice::MEDICAL)
				 {
					 numberMedical++;
					 returnString += (boost::format("<BR/> Device ID: %d;%s <BR>") % device->deviceId % BigDevice::getStatus(device, userLanguage)).str();
				 }
				 else if (device->type == BigDevice::AGRI)
				 {
					 numberAgricultural++;
					 returnString += (boost::format("<BR/> Device ID: %d;%s <BR>") % device->deviceId % BigDevice::getStatus(device, userLanguage)).str();
				 }
				 else if (device->type == BigDevice::REFINARY)
				 {
					 numberRefinaries++;
					 returnString += (boost::format("<BR/> Device ID: %d;%s <BR>") % device->deviceId % BigDevice::getStatus(device, userLanguage)).str();
				 }
			 }
		 }

		 // let's print this
		 returnString += getLine(BigDevice::MEDICAL, userLanguage, numberMedical);
		 returnString += getLine(BigDevice::AGRI, userLanguage, numberAgricultural);
		 returnString += getLine(BigDevice::REFINARY, userLanguage, numberRefinaries);

		 // finally, lets print the footer
		 returnString += std::string("TOTAL: ");
		 returnString += std::to_string(numberAgricultural + numberMedical + numberRefinaries) + std::string(" ") + (userLanguage == EN ? "devices" : "apparaten");
	 }
	 return returnString;
}

std::string BigDevice::getLine(int deviceType, int userLanguage, int numberOfDevices)
{
	if (numberOfDevices > 0)
	{
		if (userLanguage == EN)
		{
			return std::to_string(numberOfDevices) + std::string(" ") + translateDevice(deviceType, userLanguage) + std::string(" devices") + std::string("<br/>");
		}
		return std::to_string(numberOfDevices) + std::string(" ") + translateDevice(deviceType, userLanguage) + std::string(" apparaten") + std::string("<br/>");
	}
	return "";
}

std::string BigDevice::translateDevice(int type, int userLanguage)
{
	switch (type)
	{
		 case 0:
			 return userLanguage == EN ? "Medica" : "Medisch";
		 case 1:
			 return userLanguage == EN ? "Agricultura" : "Agrarisch";
		 case 2:
			 return userLanguage == EN ? "Refinary" : "Raffinaderij";
	}
	return "";
}

void BigDevice::main(std::vector<std::string> *args, int userLanguage)
{
	BigDevice *d1 = new BigDevice(BigDevice::MEDICAL, 1, false, 75);
	BigDevice *d2 = new BigDevice(BigDevice::AGRI, 2, true, 32);
	BigDevice *d3 = new BigDevice(BigDevice::REFINARY, 3, false, 60);

	std::vector<BigDevice*> devices;
	devices.push_back(d1);
	devices.push_back(d2);
	devices.push_back(d3);

	std::string printStatus = BigDevice::printStatus(devices, userLanguage); 
	std::cout << printStatus << std::endl;
}

int main(int argc, const char** argv)
{
    BigDevice::main(nullptr, BigDevice::EN);
    
    return 0;
}
