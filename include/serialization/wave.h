#ifndef WAVE_H
#define WAVE_H

#include <vector>
#include <string>

#include <fstream>

#include <core/note.h>

class Wave
{
    /** [Bloc de déclaration d'un fichier au format WAVE] **/
    unsigned char FileTypeBlocID;   // FileTypeBlocID  (4 octets) : Constante «RIFF»  (0x52,0x49,0x46,0x46)
    unsigned char FileSize;         // FileSize        (4 octets) : Taille du fichier moins 8 octets
    unsigned char FileFormatID;     // FileFormatID    (4 octets) : Format = «WAVE»  (0x57,0x41,0x56,0x45)

    /** [Bloc décrivant le format audio] **/
    unsigned char FormatBlocID; // FormatBlocID    (4 octets) : Identifiant «fmt »  (0x66,0x6D, 0x74,0x20)
    unsigned char BlocSize;     // BlocSize        (4 octets) : Nombre d'octets du bloc - 16  (0x10)

    unsigned char AudioFormat_NbrCanaux;
    //AudioFormat     (2 octets) : Format du stockage dans le fichier (1: PCM, ...)
    //NbrCanaux       (2 octets) : Nombre de canaux (de 1 à 6, cf. ci-dessous)

    unsigned char Frequence;    // Frequence       (4 octets) : Fréquence d'échantillonnage (en hertz) [Valeurs standardisées : 11 025, 22 050, 44 100 et éventuellement 48 000 et 96 000]
    unsigned char BytePerSec;   // BytePerSec      (4 octets) : Nombre d'octets à lire par seconde (c.-à-d., Frequence * BytePerBloc).
    unsigned char BytePerBloc_BitsPerSample;
    // BytePerBloc     (2 octets) : Nombre d'octets par bloc d'échantillonnage (c.-à-d., tous canaux confondus : NbrCanaux * BitsPerSample/8).
    // BitsPerSample   (2 octets) : Nombre de bits utilisés pour le codage de chaque échantillon (8, 16, 24)

    /** [Bloc des données] **/
    unsigned char DataBlocID; // DataBlocID      (4 octets) : Constante «data»  (0x64,0x61,0x74,0x61)
    unsigned char DataSize;   // DataSize        (4 octets)

    void writeFile(std::ofstream& file, std::vector<Playable*> data);
    void writeFile(std::ofstream& file, std::vector<unsigned char> data);
    void writeFile(std::ofstream& file, unsigned char * data, unsigned int size);

public:
    Wave(unsigned char _FileTypeBlocID=0,
         unsigned char _FileSize=0,
         unsigned char _FileFormatID=0,
         unsigned char _FormatBlocID=0,
         unsigned char _BlocSize=0,
         unsigned char _AudioFormat_NbrCanaux=0,
         unsigned char _Frequence=0,
         unsigned char _BytePerSec=0,
         unsigned char _BytePerBloc_BitsPerSample=0,
         unsigned char _DataBlocID=0,
         unsigned char _DataSize=0);
    Wave(const Wave& w);
    Wave& operator=(const Wave& w);

    void write(std::string filePath, std::vector<Playable*> data);
    void write(std::string filePath, std::vector<unsigned char> data);
    void write(std::string filePath, unsigned char * data, unsigned int size);
};

#endif // WAVE_H
