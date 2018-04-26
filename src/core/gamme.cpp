#include "core/gamme.h"

Gamme::Gamme(Note _fondamentale, GAMME_RELATIVITY _relativity):
tonalityM{2,4,5,7,9,11},tonalitym{2,3,5,7,8,11}{
    m_fondamentale = _fondamentale;
    m_relativity = _relativity;
}
Gamme::Gamme(const Gamme& g){
    m_fondamentale = g.m_fondamentale;
    m_relativity = g.m_relativity;
    memcpy(tonalitym,g.tonalitym,6*sizeof(unsigned));
    memcpy(tonalityM,g.tonalityM,6*sizeof(unsigned));
}
Gamme& Gamme::operator=(const Gamme& g){
    m_fondamentale = g.m_fondamentale;
    m_relativity = g.m_relativity;
    memcpy(tonalitym,g.tonalitym,6*sizeof(unsigned));
    memcpy(tonalityM,g.tonalityM,6*sizeof(unsigned));
    return *this;
}

Note Gamme::fondamentale(double octave){
    return Note::getNextNoteFreq(m_fondamentale.freq(),octave);
}
Note Gamme::seconde(double octave){
    return Note(Note::getNextNoteFreq(m_fondamentale.freq(),octave,
                                      m_relativity==MAJEUR?tonalityM[0]:tonalitym[0]));
}
Note Gamme::tierse(double octave){
    return Note(Note::getNextNoteFreq(m_fondamentale.freq(),octave,
                                      m_relativity==MAJEUR?tonalityM[1]:tonalitym[1]));
}
Note Gamme::quarte(double octave){
    return Note(Note::getNextNoteFreq(m_fondamentale.freq(),octave,
                                      m_relativity==MAJEUR?tonalityM[2]:tonalitym[2]));
}
Note Gamme::quinte(double octave){
    return Note(Note::getNextNoteFreq(m_fondamentale.freq(),octave,
                                      m_relativity==MAJEUR?tonalityM[3]:tonalitym[3]));
}
Note Gamme::sixte(double octave){
    return Note(Note::getNextNoteFreq(m_fondamentale.freq(),octave,
                                      m_relativity==MAJEUR?tonalityM[4]:tonalitym[4]));
}
Note Gamme::septieme(double octave){
    return Note(Note::getNextNoteFreq(m_fondamentale.freq(),octave,
                                      m_relativity==MAJEUR?tonalityM[5]:tonalitym[5]));
}
