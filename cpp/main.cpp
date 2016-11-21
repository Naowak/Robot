#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memcmp
#include <stdint.h> // for int16_t and int32_t
#include <math.h>
#include <vector>
#include "dtw.h"
#include "WavToMfcc.h"

using namespace std;

void print(int16_t* signal,int length) {
    for(int i=0;i<length;i++) {
        cout<<signal[i]<<endl;
    }
    cout<<"--------------------------------------------------"<<endl;
}

void toMFCC(string s, float** oSignal, int* oLength){
	char* file = (char *)s.c_str();

	FILE* file_wav;
	struct wavfile w;

	if(is_big_endian()){
		cout<<"1.8"<<endl;
	}
	//lit fichier .wav
	wavRead(&file_wav,file,&w);


	//char buffer[sizeof(int16_t)];
	int16_t buffer;
	int16_t signal[w.totallength];
	int i = 0;



	while(! feof(file_wav)){
		//if ( fgets (buffer , sizeof(int16_t) , file_wav) == NULL ) break;
		if ( fread (&buffer , sizeof(int16_t), 1 , file_wav) <= 0 ) break;
		signal[i] = buffer;
		i++;
	}
    cout<<"Avant Silence"<<endl;
    //print(signal,w.totallength);
    cout<<"taille : "<<w.totallength<<endl;

	int16_t* sSignal;
	int newLength;


	removeSilence(signal, w.totallength, &sSignal, &newLength,1/100);

	cout<<"Après RemoveSilence"<<endl;
    //print(sSignal,newLength);
    cout<<"new taille : "<<newLength<<endl;

	float* xMFCC;
	int xLength;


	computeMFCC(&xMFCC, &xLength, sSignal, newLength, w.frequency, 512, 256, 12, 26);

	*oSignal = xMFCC;
	*oLength = xLength;

	cout<<xMFCC<<endl;
	/*cout<<"frequence : "<<w.frequency<<endl;
	cout<<"taille MFC : "<<xLength<<endl;
	for(int i =0; i <xLength; i++){
		cout<<xMFCC[i]<<endl;
	}*/

}

//Compare un nouveau mot à la base de donner pour trouver quel ordre a été donner
float compareMFC(string name_file) {
    float* signal;
	int length;
	toMFCC(name_file, &signal, &length);

    /**
    * Transform the wav extension into mfc extension.
    *
    * @param filename (IN) pointer to the name of the file
    * @param mfcName OUT) pointer to the new name of the file with .mfc ext
    * @return none
    */
    //void nameWavToMfc(char *filename, char * mfcName);
    char mfcName;
    char* char_name_file = (char*)name_file.c_str();
    nameWavToMfc(char_name_file,&mfcName);

}


int main() {

/*float* sequence1 = new float[2];
	sequence1[0] = 1.1;
	sequence1[1] = 1.2;
	float* sequence2 = new float[3];
	sequence2[0] = 2.2;
	sequence2[1] = 2.8;
	sequence2[2] = 2.4;*/


	string s1 = "corpus/corpus/dronevolant_bruite/M01_arretetoi.wav";
	string s2 = "corpus/corpus/dronevolant_bruite/M01_arretetoi.wav";

	float* signal1;
	int length1;

	float* signal2;
	int length2;

	toMFCC(s1, &signal1, &length1);
	toMFCC(s2, &signal2, &length2);

	float result;
	result = dtw(length1,length2,13,signal2,signal1);
	//result = dtw(3,2,13,sequence1,sequence2);


	//cout<<"fin"<<endl;
	cout<<"score : " <<result<<endl;

	/*delete[] sequence1;
	delete[] sequence2;*/
	return 0;
}
