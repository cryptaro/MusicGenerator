#ifndef ACCORD_H
#define ACCORD_H

#include <core/note.h>
#include <core/gamme.h>

#include <vector>
#include <utility>

typedef std::pair<double,double> NoteBeginDuration;


class Accord: public Playable
{
private:
    std::vector<Note> m_playables;
    std::vector<NoteBeginDuration> m_playablesDuration; // TODO: ARPEGES !
public:
    Accord();
    Accord(Gamme g, double duration=0.5, unsigned octave=0);
    Accord(const std::vector<Note> notes);
    Accord(const Accord& a);
    Accord& operator=(const Accord& a);

    static Accord getAccordWithHarmonic(Gamme g, double duration=0.5, unsigned octave=0);

    // Inherit
public:
    double sinFrequence(int x, double hz)const;
//    Playable clone()const;
    double duration()const;
    std::string toString()const;
};


#endif // ACCORD_H
