#include "communications/MsgService.h"

class CustomPattern : public Pattern {

public:
  boolean match(const Msg &m) override {
    String content = m.getContent();

    // Controlla la lunghezza minima richiesta
    if (content.length() < 8) {
      return false;
    }

    // Verifica che i primi 3 caratteri siano lettere maiuscole
    for (int i = 0; i < 3; i++) {
      if (!isUpperCase(content[i])) {
        return false;
      }
    }

    // Controlla che il quarto carattere sia ':'
    if (content[3] != ':') {
      return false;
    }

    // Controlla che il resto del messaggio sia "true" o "false"
    String value = content.substring(4);
    if (value == "true" || value == "false") {
      return true;
    }

    return false;
  }

private:
  boolean isUpperCase(char c) {
    return c >= 'A' && c <= 'Z';
  }
};
