// EEPROM module
// Read and write settings struct to EEPROM 
// Validates existence of settings on build date and time or a set id
// This module will be available in a separate library
// In this example to avoid depencency

// Includes
#include <EEPROM.h> // 

struct EEPROMadmindata
{
  uint32_t BuildTimeStamp = 0;
  uint16_t StructSize = 0;
};

const uint32_t currentBuild = jenkins_one_at_a_time_hash(__DATE__ __TIME__);

//-----------------------------------------------------------------------------------------------
// Write the settings struct to the EEPROM using buid time/date
template<typename T>
void WriteStructEEPROM(const T& t)
{
  WriteStructEEPROM(t, currentBuild);
}

//-----------------------------------------------------------------------------------------------
// Write the settings struct to the EEPROM
template<typename T>
void WriteStructEEPROM(const T& t, uint32_t id)
{
  EEPROMadmindata AdminData{};
  
  AdminData.BuildTimeStamp =id;
  AdminData.StructSize = sizeof(T);

  const byte* ad = (const byte*)&AdminData;
  for (uint16_t i = 0; i < sizeof(EEPROMadmindata); i++)
    EEPROM.write(i, *ad++);

  const byte* p = (const byte*)&t;
  for (size_t i = 0; i < sizeof(T); i++)
    EEPROM.write(i+sizeof(EEPROMadmindata), *p++);
}

//-----------------------------------------------------------------------------------------------
// Read the settings struct from the EEPROM using buid time/date
template<typename T>
bool ReadStructEEPROM(T& t)
{
  return ReadStructEEPROM(t, currentBuild);
}

//-----------------------------------------------------------------------------------------------
// Read the settings struct from the EEPROM
template<typename T>
bool ReadStructEEPROM(T& t, uint32_t id)
{
  EEPROMadmindata AdminData{};

  byte* ad = (byte*)&AdminData;
  for (uint16_t i = 0; i < sizeof(EEPROMadmindata); i++)
    *ad++ = EEPROM.read(i);

  if ( AdminData.BuildTimeStamp == id &&
       AdminData.StructSize == sizeof(T))
  {
    byte* p = (byte*) &t;
    for (size_t i = 0; i < sizeof(T); i++)
      *p++ = EEPROM.read(i+sizeof(EEPROMadmindata));
    return true;
  }
  return false;
}

//-----------------------------------------------------------------------------------------------
uint32_t jenkins_one_at_a_time_hash(const char *key)
{
    size_t len = strlen(key);
    uint32_t hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}
