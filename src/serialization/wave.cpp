#include "serialization/wave.h"

#include <cmath>
#include <iostream>

using namespace std;


Wave::Wave(unsigned char _FileTypeBlocID,
           unsigned char _FileSize,
           unsigned char _FileFormatID,
           unsigned char _FormatBlocID,
           unsigned char _BlocSize,
           unsigned char _AudioFormat_NbrCanaux,
           unsigned char _Frequence,
           unsigned char _BytePerSec,
           unsigned char _BytePerBloc_BitsPerSample,
           unsigned char _DataBlocID,
           unsigned char _DataSize){
    FileTypeBlocID=_FileTypeBlocID;
    FileSize=_FileSize;
    FileFormatID=_FileFormatID;
    FormatBlocID=_FormatBlocID;
    BlocSize=_BlocSize;
    AudioFormat_NbrCanaux=_AudioFormat_NbrCanaux;
    Frequence=_Frequence;
    BytePerSec=_BytePerSec;
    BytePerBloc_BitsPerSample=_BytePerBloc_BitsPerSample;
    DataBlocID=_DataBlocID;
    DataSize=_DataSize;
}

Wave::Wave(const Wave& w){
    FileTypeBlocID=w.FileTypeBlocID;
    FileSize=w.FileSize;
    FileFormatID=w.FileFormatID;
    FormatBlocID=w.FormatBlocID;
    BlocSize=w.BlocSize;
    AudioFormat_NbrCanaux=w.AudioFormat_NbrCanaux;
    Frequence=w.Frequence;
    BytePerSec=w.BytePerSec;
    BytePerBloc_BitsPerSample=w.BytePerBloc_BitsPerSample;
    DataBlocID=w.DataBlocID;
    DataSize=w.DataSize;
}

Wave& Wave::operator=(const Wave& w){
    FileTypeBlocID=w.FileTypeBlocID;
    FileSize=w.FileSize;
    FileFormatID=w.FileFormatID;
    FormatBlocID=w.FormatBlocID;
    BlocSize=w.BlocSize;
    AudioFormat_NbrCanaux=w.AudioFormat_NbrCanaux;
    Frequence=w.Frequence;
    BytePerSec=w.BytePerSec;
    BytePerBloc_BitsPerSample=w.BytePerBloc_BitsPerSample;
    DataBlocID=w.DataBlocID;
    DataSize=w.DataSize;
    return *this;
}


void Wave::write(std::string filePath, std::vector<unsigned char> data){
    ofstream out(filePath,ios::binary);
    //if(out.is_open()){
    writeFile(out, data);
    out.close();
    //    }else{
    //        std::cerr << "fail to open file : " << filePath << std::endl;
    //    }
}

void Wave::write(std::string filePath, unsigned char * data, unsigned int size){
    ofstream out(filePath,ios::binary);
    //    if( out.is_open()){
    writeFile(out, data, size);
    out.close();
    //    }else{
    //        std::cerr << "fail to open file : " << filePath << std::endl;
    //    }
}

template <typename Word>
std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
{
    for (; size; --size, value >>= 8)
        outs.put( static_cast <char> (value & 0xFF) );
    return outs;
}


void Wave::writeFile(ofstream& file, std::vector<unsigned char> data){
    writeFile(file,data.data(),data.size());
}

void Wave::writeFile(ofstream& file, unsigned char * data, unsigned int size){
    file << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
    write_word(file,16,4);
    write_word(file,      1, 2 );  // PCM - integer samples
    write_word(file,      2, 2 );  // two channels (stereo file)
    write_word(file,  44100, 4 );  // samples per second (Hz)
    write_word(file, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    write_word(file,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
    write_word(file,     16, 2 );  // number of bits per sample (use a multiple of 8)

    // Write the data chunk header
    size_t data_chunk_pos = file.tellp();
    file << "data----";  // (chunk size to be filled in later)

    constexpr double two_pi = 6.283185307179586476925286766559;
    constexpr double max_amplitude = 32760;  // "volume"

    double hz        = 44100;    // samples per second
    double frequency = 261.626;  // middle C
    double seconds   = 2.5;      // time

    int N = hz * seconds;  // total number of samples
    for (int n = 0; n < N; n++)
    {
        double amplitude = (double)n / N * max_amplitude;
        double value     = sin( (two_pi * n * frequency) / hz );
        write_word(file, (int)(                 amplitude  * value), 2 );
        write_word(file, (int)((max_amplitude - amplitude) * value), 2 );
    }

    // (We'll need the final file size to fix the chunk sizes above)
    size_t file_length = file.tellp();

    // Fix the data chunk header to contain the data size
    file.seekp( data_chunk_pos + 4 );
    write_word( file, file_length - data_chunk_pos + 8 );

    // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
    file.seekp( 0 + 4 );
    write_word(file, file_length - 8, 4 );
}


void Wave::write(std::string filePath, std::vector<Playable*> data){
    std::cout <<"open file " << filePath <<std::endl;
    ofstream out(filePath,ios::binary);
    writeFile(out, data);
    out.close();
}

void Wave::writeFile(std::ofstream& file, std::vector<Playable*> data){
    double hz        = 44100;      // samples per second
    file << "RIFF----WAVEfmt ";    // (chunk size to be filled in later)
    write_word(file,     16, 4 );
    write_word(file,      1, 2 );  // PCM - integer samples
    write_word(file,      2, 2 );  // two channels (stereo file)
    write_word(file,  44100, 4 );  // samples per second (Hz)
    write_word(file, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    write_word(file,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
    write_word(file,     16, 2 );  // number of bits per sample (use a multiple of 8)

    // Write the data chunk header
    size_t data_chunk_pos = file.tellp();
    file << "data----";  // (chunk size to be filled in later)

    constexpr double two_pi = 6.283185307179586476925286766559;

    for(Playable* play : data){
        for(int i=0;i<hz*play->duration();i++){
            write_word(file, (int)(play->sinFrequence(i,hz)), 2 );
            write_word(file, (int)(play->sinFrequence(i,hz)), 2 );
        }
    }

    // (We'll need the final file size to fix the chunk sizes above)
    size_t file_length = file.tellp();

    // Fix the data chunk header to contain the data size
    file.seekp( data_chunk_pos + 4 );
    write_word( file, file_length - data_chunk_pos + 8 );

    // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
    file.seekp( 0 + 4 );
    write_word(file, file_length - 8, 4 );
}
