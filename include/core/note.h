#ifndef NOTE_H
#define NOTE_H

#include <cmath>
#include <string>
#include <vector>

#define doBase 32.70

#define PI2 6.283185307179586476925286766559

enum NoteName{
    Do=0,Re=2,Mi=4,Fa=5,Sol=7,La=9,Si=10
};

class Playable{
public:
    virtual ~Playable(){}
    virtual double sinFrequence(int x, double hz)const=0;
//    virtual Playable clone()const=0;
    virtual double duration()const=0;
    virtual std::string toString()const=0;
};



class Note: public Playable
{
protected:
    double m_freq;
    double m_duration_sec;
    double m_amplitude;
public:
    Note(double _freq = doBase, double _duration_sec=0.5, double _amplitude=8000.);
    Note(const Note &n);
    Note& operator=(const Note &n);
    virtual ~Note(){}


    double freq()const{return m_freq;}
    double amplitude()const{return m_amplitude;}
    Note getNextNote(unsigned octave=1, unsigned nbHalfTone=0);

    void setFreq(double freq);
    void setDuration_sec(double duration_sec);
    void setAmplitude(double amplitude);

    static double getFrequence(NoteName n, unsigned octave=3, bool sharp=false);
    static double getNextNoteFreq(double freqBase, unsigned octave=1, unsigned nbHalfTone=0);

    // Inherit
public:
    virtual double sinFrequence(int x, double hz)const;
    virtual std::string toString()const;
//    Playable clone()const;
    virtual double duration()const{return m_duration_sec;}
};


#endif // NOTE_H
