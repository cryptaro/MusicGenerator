#ifndef GAMME_H
#define GAMME_H

#include <core/note.h>

enum GAMME_RELATIVITY{
    MAJEUR, MINEUR
};

class Gamme
{
    Note m_fondamentale;
    GAMME_RELATIVITY m_relativity;

    unsigned tonalityM[6];
    unsigned tonalitym[6];

public:
    Gamme(Note _fondamentale=Note(), GAMME_RELATIVITY _relativity=MAJEUR);
    Gamme(const Gamme& g);
    Gamme& operator=(const Gamme& g);

    Note fondamentale(double octave=0);
    Note seconde(double octave=0);
    Note tierse(double octave=0);
    Note quarte(double octave=0);
    Note quinte(double octave=0);
    Note sixte(double octave=0);
    Note septieme(double octave=0);

};

#endif // GAMME_H
