#ifndef MELODY_H
#define MELODY_H

#include <core/note.h>

// TODO: faire les silences

double transformLinear(double p, double amp){
    return amp;
}


class NoteMelodic: public Note{
    NoteMelodic* m_prev;
    NoteMelodic* m_next;
    bool m_related;

    // Fonction de transformation de l'amplitude de la note au cours
    // d'un pourcentage temps de la durée de la note
    // Arg 1 : %age de temps,
    // Arg 2 : amplitude
    double (*transorm)(double, double);
public:
    NoteMelodic(double _freq = doBase, double _duration_sec=0.5, double _amplitude=8000.,
                NoteMelodic* prev=NULL, NoteMelodic* next=NULL, bool related=false,
                double (*_transorm)(double, double)=&transformLinear);
    NoteMelodic(const NoteMelodic& nm);
    NoteMelodic& operator=(const NoteMelodic& nm);
    virtual ~NoteMelodic();

// Inherited
public:
    virtual double sinFrequence(int x, double hz)const;
};


class Melody
{
public:
    Melody();
};

#endif // MELODY_H
