#include <stdio.h>
#include <assert.h>

char ErrorTemperature[]= "Temperature out of range!\n";
char ErrorSOC[]="State of Charge out of range!\n";
char ErrorChargingRate[]="Charge Rate out of range!\n";

void ChargingRate(float chargeRate);
void CheckTemperatureRange(float temperature);
void CheckStateOfCharge(float soc);

union
{
  struct
  {
    unsigned char ErrorTemp:1;
    unsigned char ErrorSOC:1;
    unsigned char ErrorChargeRate:1;
    unsigned char DummyBytes:5;
  }structErrors;
  unsigned char AllErrors;
}unionErrors;

static unionErrors unionErrorObj;

int batteryIsOk(float temperature, float soc, float chargeRate)
{
  //Make the Error Variable okay, then catch the error.
  CheckTemperatureRange(temperature);
  CheckStateOfCharge(soc);
  ChargingRate(chargeRate);
  //Check if any bits are overwritten due to Error(s)
  if(0 == unionErrorObj.AllErrors)
    return 0;
  else 
    return 1;
}

void CheckTemperatureRange(float temperature)
{
  if(temperature < 0 || temperature > 45)
  {
    PrintTheError(ErrorTemperature);
    unionErrorObj.structErrors.ErrorTemp = 1;
  }
  else
  {
    unionErrorObj.structErrors.ErrorTemp = 0;
  }
}

void CheckStateOfCharge(float soc)
{
  if(soc < 20 || soc > 80)
  {
    PrintTheError(ErrorSOC);
    unionErrorObj.structErrors.ErrorSOC = 1;
  }
  else
  {
    unionErrorObj.structErrors.ErrorSOC = 0;
  }
}

void ChargingRate(float chargeRate)
{
  if(chargeRate > 0.8)
  {
    PrintTheError(ErrorChargingRate);
    unionErrorObj.structErrors.ErrorChargeRate = 1;
  }
  else
  {
    unionErrorObj.structErrors.ErrorChargeRate = 0;
  }
}

void PrintTheError(char* ErrorString)
{
  printf("%s",ErrorString);
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
