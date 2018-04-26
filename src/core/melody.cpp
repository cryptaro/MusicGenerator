#include "include/core/melody.h"

NoteMelodic::NoteMelodic(double _freq, double _duration_sec, double _amplitude,
                         NoteMelodic* prev, NoteMelodic* next, bool related,
                         double (*_transorm)(double, double) ):
    Note(_freq, _duration_sec, _amplitude),
    m_related(related)
{
    m_prev = prev;
    m_next = next;
    transorm = _transorm;
}
NoteMelodic::NoteMelodic(const NoteMelodic& nm):Note(nm),m_related(nm.m_related){
    m_prev = nm.m_prev;
    m_next = nm.m_next;
}
NoteMelodic& NoteMelodic::operator=(const NoteMelodic& nm){
    m_freq = nm.m_freq;
    m_duration_sec = nm.m_duration_sec;
    m_amplitude = nm.m_amplitude;
    m_prev = nm.m_prev;
    m_next = nm.m_next;
    m_related = nm.m_related;
    return *this;
}
NoteMelodic::~NoteMelodic(){
    m_prev = NULL;
    if(m_next){
        delete m_next;
    }
    m_next = NULL;
    transorm = NULL;
}


double NoteMelodic::sinFrequence(int x, double hz)const{
    return (*transorm)(x/(m_duration_sec*hz),m_amplitude)* sin(PI2*x*(m_freq)/ hz);
}


Melody::Melody()
{

}
