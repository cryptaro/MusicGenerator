#include "core/accord.h"

#include <sstream>

Accord::Accord(){

}

Accord::Accord(Gamme g, double duration, unsigned octave){
    m_playables.push_back(g.fondamentale(octave));
    m_playables.push_back(g.tierse(octave));
    m_playables.push_back(g.quinte(octave));
//    m_playables.push_back(g.septieme(octave));
}

Accord::Accord(const std::vector<Note> notes){
    for(Note n: notes){
        m_playables.push_back(Note(n));
    }
}
Accord::Accord(const Accord& a){
    for(Note n: a.m_playables){
        m_playables.push_back(Note(n));
    }
}
Accord& Accord::operator=(const Accord& a){
    for(Note n: a.m_playables){
        m_playables.push_back(Note(n));
    }
    return *this;
}


Accord Accord::getAccordWithHarmonic(Gamme g, double duration, unsigned octave){
    Accord acc(g,duration,octave);
    Note harm = g.fondamentale(octave+2);
    harm.setAmplitude(g.fondamentale().amplitude()*0.4);
    acc.m_playables.push_back(harm);
    return acc;
}

/// ======================================

double Accord::sinFrequence(int x, double hz)const{
    double val = 0;
    for(Note p : m_playables){
        if(hz*p.duration()>x){
            val+=p.sinFrequence(x,hz);
        }
    }
    return val;
}

std::string Accord::toString()const{
    std::ostringstream oss;
    oss << "{";
    for(Note n : m_playables){
        oss << n.toString() << " ";
    }
    oss<< "}";
    return oss.str();
}

//Playable Accord::clone()const{
//    return Accord(*this);
//}


double Accord::duration()const{
    double sumDur = 0;
    for(Note p : m_playables){
        sumDur=std::max(p.duration(),sumDur);
    }
    return sumDur;
}
