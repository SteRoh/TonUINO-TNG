#include "src/tonuino.hpp"

#include "src/settings.hpp"
#include "src/mp3.hpp"
#include "src/buttons.hpp"
#include "src/logger.hpp"
#include "src/constants.hpp"

/*
   _____         _____ _____ _____ _____
  |_   _|___ ___|  |  |     |   | |     |
    | | | . |   |  |  |-   -| | | |  |  |
    |_| |___|_|_|_____|_____|_|___|_____|
    TonUINO Version 3.1 - refactored by Boerge1

    created by Thorsten Voß and licensed under GNU/GPL.
    Information and contribution at https://tonuino.de.
*/

/*
Please select your TonUINO PCB (Classic, AiO or AiO+) in file constants.hpp
Right now you must use an older version of the DFPlayer Mini Mp3 by Makuna library (1.0.7)!

Bitte wählt eure TonUINO-Platine (Classic, AiO oder AiO+) in der Datei constands.hpp
Aktuell wird nur eine ältere Version der DFPlayer Mini Mp3 by Makuna Bibliothek (1.0.7) unterstützt!
*/

void setup()
{
  Serial.begin(115200);

  // Dieser Hinweis darf nicht entfernt werden
  LOG(init_log, s_error, F("\n _____         _____ _____ _____ _____"));
  LOG(init_log, s_error, F("|_   _|___ ___|  |  |     |   | |     |"));
  LOG(init_log, s_error, F("  | | | . |   |  |  |-   -| | | |  |  |"));
  LOG(init_log, s_error, F("  |_| |___|_|_|_____|_____|_|___|_____|"));
  LOG(init_log, s_error, F("TonUINO Version 3.1 - refactored by Boerge1\n"));
  LOG(init_log, s_error, F("created by Thorsten Voß and licensed under GNU/GPL."));
  LOG(init_log, s_error, F("Information and contribution at https://tonuino.de.\n"));

  Tonuino::getTonuino().setup();
}

void loop()
{
  Tonuino::getTonuino().loop();
}
