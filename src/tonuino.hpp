#ifndef SRC_TONUINO_HPP_
#define SRC_TONUINO_HPP_

#include "settings.hpp"
#include "buttons.hpp"
#include "mp3.hpp"
#include "modifier.hpp"
#include "timer.hpp"

class Tonuino {
public:
  Tonuino() {}
  static Tonuino& getTonuino() { static Tonuino tonuino; return tonuino; }

  void setup          ();
  void loop           ();

  void playFolder     ();
  void playTrackNumber();

  void       nextTrack(bool fromOnPlayFinished = false);
  void   previousTrack();

  void resetActiveModifier   () { activeModifier = &noneModifier; }
  Modifier& getActiveModifier() { return *activeModifier; }

  void setStandbyTimer();
  void disableStandbyTimer();

  void setCard  (const nfcTagObject   &newCard) { myCard = newCard; setFolder(&myCard.nfcFolderSettings); }
  const nfcTagObject& getCard() const           { return myCard; }
  void setFolder(folderSettings *newFolder    ) { myFolder = newFolder; }
  uint8_t getFolder()                           { return myFolder->folder; }

  Mp3&      getMp3      () { return mp3      ; }
  Buttons&  getButtons  () { return buttons  ; }
  Settings& getSettings () { return settings ; }
  Chip_card& getChipCard() { return chip_card; }
  static uint32_t generateRamdomSeed();

private:

  void checkStandby();

  bool specialCard(const nfcTagObject &nfcTag);

  Settings             settings            {};
  Mp3                  mp3                 {settings};
  Buttons              buttons             {settings};
  Chip_card            chip_card           {mp3, buttons};

  friend class Base;

  Modifier             noneModifier        {*this, mp3, settings};
  SleepTimer           sleepTimer          {*this, mp3, settings};
  FreezeDance          freezeDance         {*this, mp3, settings};
  Locked               locked              {*this, mp3, settings};
  ToddlerMode          toddlerMode         {*this, mp3, settings};
  KindergardenMode     kindergardenMode    {*this, mp3, settings};
  RepeatSingleModifier repeatSingleModifier{*this, mp3, settings};
  //FeedbackModifier     feedbackModifier    {*this, mp3, settings};

  Modifier*            activeModifier      {&noneModifier};

  Timer                standbyTimer        {};

  nfcTagObject         myCard              {};
  folderSettings*      myFolder            {&myCard.nfcFolderSettings};
  uint16_t             numTracksInFolder   {};
};

#endif /* SRC_TONUINO_HPP_ */
