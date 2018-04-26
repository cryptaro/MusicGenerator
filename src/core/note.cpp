#include "core/note.h"
#include <sstream>
#include <cmath>
#include <iostream>


double Note::getFrequence(NoteName n, unsigned octave, bool sharp){
    return (doBase)*pow(2,(n+(sharp?1.:0.)+octave*12.)/12.);
}
double Note::getNextNoteFreq(double freqBase, unsigned octave, unsigned nbHalfTone){
    return (freqBase)*pow(2,(nbHalfTone+octave*12.)/12.);
}


void Note::setFreq(double freq)
{
    m_freq = freq;
}

void Note::setDuration_sec(double duration_sec)
{
    m_duration_sec = duration_sec;
}

void Note::setAmplitude(double amplitude)
{
    m_amplitude = amplitude;
}

Note::Note(double _freq,double _duration_sec, double _amplitude){
    m_freq = _freq;
    m_duration_sec = _duration_sec;
    m_amplitude = _amplitude;
}

Note::Note(const Note &n){
    m_freq = n.m_freq;
    m_duration_sec = n.m_duration_sec;
    m_amplitude = n.m_amplitude;
}

Note& Note::operator=(const Note &n){
    m_freq = n.m_freq;
    m_duration_sec = n.m_duration_sec;
    m_amplitude = n.m_amplitude;
    return *this;
}

Note Note::getNextNote(unsigned octave, unsigned nbHalfTone){
    return Note(getNextNoteFreq(m_freq,octave,nbHalfTone));
}

std::string Note::toString()const{
    std::ostringstream oss;
    oss << "(" << m_freq << " " << m_duration_sec <<" " << m_amplitude << ")";
    return oss.str();
}


double Note::sinFrequence(int x, double hz)const{
//    if(x%100==0)
//    std::cout << 1/(1+1/(m_duration_sec*hz-x)) <<std::endl;
    return m_amplitude*sin(PI2*x*(m_freq)/ hz);
}
//Playable Note::clone()const{
//    return Note(*this);
//}
