#include "settings.hpp"

#include "constants.hpp"
#include "logger.hpp"

namespace {

const int startAddressAdminSettings = sizeof(folderSettings::folder) * 100;

}

void Settings::writeByteToFlash(uint16_t address, uint8_t value) {
  EEPROM_put(address, value);
}

uint8_t Settings::readByteFromFlash(uint16_t address) {
  return EEPROM.read(address);
}

void Settings::clearEEPROM() {
  LOG(settings_log, s_info, F("clearEEPROM"));
  for (uint16_t i = 0; i < sizeof(folderSettings::folder) * 100 + sizeof(this); i++) {
    writeByteToFlash(i, 0);
  }
}

void Settings::writeSettingsToFlash() {
  LOG(settings_log, s_debug, F("writeSettingsToFlash"));
  EEPROM_put(startAddressAdminSettings, *this);
}

void Settings::resetSettings() {
  LOG(settings_log, s_debug, F("resetSettings"));
  cookie               = cardCookie;
  version              =  2;
  maxVolume            = 25;
  minVolume            =  5;
  initVolume           = 15;
  eq                   =  1;
  locked               = false;
  standbyTimer         =  0;
#ifdef FIVEBUTTONS
  invertVolumeButtons  = false;
#else
  invertVolumeButtons  = true;
#endif
  shortCuts[0].folder  =  0;
  shortCuts[1].folder  =  0;
  shortCuts[2].folder  =  0;
  shortCuts[3].folder  =  0;
  adminMenuLocked      =  0;
  adminMenuPin[0]      =  1;
  adminMenuPin[1]      =  1;
  adminMenuPin[2]      =  1;
  adminMenuPin[3]      =  1;
  pauseWhenCardRemoved = false;

#ifdef BUTTONS3X3
  for (uint8_t i = 0; i < buttonExtSC_buttons; ++i)
    extShortCuts[i].folder = 0;
#endif // BUTTONS3X3

  writeSettingsToFlash();
}

void Settings::migrateSettings(int oldVersion) {
  if (oldVersion == 1) {
    LOG(settings_log, s_info, F("migradeSettings 1 -> 2"));
    version              = 2;
    adminMenuLocked      = 0;
    adminMenuPin[0]      = 1;
    adminMenuPin[1]      = 1;
    adminMenuPin[2]      = 1;
    adminMenuPin[3]      = 1;
    pauseWhenCardRemoved = false;
    writeSettingsToFlash();
  }
}

void Settings::loadSettingsFromFlash() {
  LOG(settings_log, s_debug, F("loadSettingsFromFlash"));
  EEPROM_get(startAddressAdminSettings, *this);
  if (cookie != cardCookie)
    resetSettings();
  migrateSettings(version);

  LOG(settings_log, s_info, F("Version: "                ), version);
  LOG(settings_log, s_info, F("Max Vol: "                ), maxVolume);
  LOG(settings_log, s_info, F("Min Vol: "                ), minVolume);
  LOG(settings_log, s_info, F("Init Vol: "               ), initVolume);
  LOG(settings_log, s_info, F("EQ: "                     ), eq);
  LOG(settings_log, s_info, F("Locked: "                 ), locked);
  LOG(settings_log, s_info, F("Sleep Timer: "            ), standbyTimer);
  LOG(settings_log, s_info, F("Inverted Vol Buttons: "   ), invertVolumeButtons);
  LOG(settings_log, s_info, F("Admin Menu locked: "      ), adminMenuLocked);
  LOG(settings_log, s_info, F("Admin Menu Pin: "         ), adminMenuPin[0], adminMenuPin[1], adminMenuPin[2], adminMenuPin[3]);
  LOG(settings_log, s_info, F("Pause when card removed: "), pauseWhenCardRemoved);
}

void Settings::writeFolderSettingToFlash(uint8_t folder, uint16_t track) {
  writeByteToFlash(folder, min(track, 0xffu));
}

uint16_t Settings::readFolderSettingFromFlash(uint8_t folder) {
  return readByteFromFlash(folder);
}

folderSettings& Settings::getShortCut(uint8_t shortCut) {
  if (shortCut > 0 && shortCut <= 4)
    return shortCuts[shortCut];
#ifdef BUTTONS3X3
  else if (shortCut >= buttonExtSC_begin && shortCut < buttonExtSC_begin + buttonExtSC_buttons)
    return extShortCuts[shortCut-buttonExtSC_begin];
#endif

  return shortCuts[0];
}


