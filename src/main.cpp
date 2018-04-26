#include <iostream>

using namespace std;

#include <serialization/wave.h>
#include <core/note.h>
#include <core/gamme.h>
#include <core/accord.h>

#include <vector>

int main(int argc, char *argv[])
{
    Wave wave;
    std::string filePath = __FILE__;
#ifdef WIN32
    filePath=filePath.substr(0,filePath.find_last_of("\\")+1);
#else
    filePath=filePath.substr(0,filePath.find_last_of("/")+1);
#endif
    filePath+="../gen/";

    std::vector<Playable*> n;
    //--------------
    //    std::string fileName = "test.wav";
    //    std::string fileName = "pierrot.wav";
    //    n.push_back(Note(Note::getFrequence(Do),0.3));
    //    n.push_back(Note(Note::getFrequence(Do),0.3));
    //    n.push_back(Note(Note::getFrequence(Do),0.3));
    //    n.push_back(Note(Note::getFrequence(Re),0.3));
    //    n.push_back(Note(Note::getFrequence(Mi),0.5));
    //    n.push_back(Note(Note::getFrequence(Re),0.5));
    //    n.push_back(Note(Note::getFrequence(Do),0.3));
    //    n.push_back(Note(Note::getFrequence(Mi),0.3));
    //    n.push_back(Note(Note::getFrequence(Re),0.3));
    //    n.push_back(Note(Note::getFrequence(Re),0.3));
    //    n.push_back(Note(Note::getFrequence(Do),0.3));

    //--------------
    std::string fileName = "gamme.wav";
    Gamme gammeLa(Note(Note::getFrequence(La,3)),MINEUR);
    Gamme gammeSol(Note(Note::getFrequence(Sol,3)),MINEUR);
    Gamme gammeDo(Note(Note::getFrequence(Do,3)),MINEUR);
    Gamme gammeMi(Note(Note::getFrequence(Mi,3)),MINEUR);
    n.push_back(new Accord(Accord::getAccordWithHarmonic(gammeLa,3)));
    n.push_back(new Accord(Accord::getAccordWithHarmonic(gammeSol,2)));
    n.push_back(new Accord(Accord::getAccordWithHarmonic(gammeDo,3)));
    n.push_back(new Accord(Accord::getAccordWithHarmonic(gammeMi,1)));


    //--------------
    for(Playable* p : n){
        std::cout << p->toString() << std::endl;
    }

    wave.write(filePath+fileName, n);

    for(Playable* p : n){
        delete p;
    }
    return 0;
}
