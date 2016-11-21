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

int dim_mfcc = 13;


/* Créer ou remplace un fichier mfc représentent un nouveau mot
 * (IN) file name
 * (OUT) MFC
 * (OUT) MFC Length
*/
void toMFCC(string s, float** oSignal, int* oLength){
	char* file = (char *)s.c_str();

	FILE* file_wav;
	struct wavfile w;

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



	int16_t* sSignal;
	int newLength;


	removeSilence(signal, w.totallength, &sSignal, &newLength, (float)1/100);

	float* xMFCC;
	int xLength;



	computeMFCC(&xMFCC, &xLength, sSignal, newLength, w.frequency, 512, 256, dim_mfcc, 26);

	*oSignal = xMFCC;
	*oLength = xLength;

	//cout<<"frequence : "<<w.frequency<<endl;

	/*
	cout<<"taille MFC : "<<xLength<<endl;
	for(int i =0; i <xLength; i++){
		for(int j = 0;j<dim_mfcc;j++){
			cout<<xMFCC[i*dim_mfcc+j]<<" -- ";
		}
		cout<<endl;
	}*/

}

/* Compare un nouveau mot à la base de donner pour trouver quel ordre a été donner
*/
float compareMFC(string name_file, string compareTo){

	float* signal;
	int length;

	int lengthTo;

	toMFCC(name_file, &signal, &length);

	char* mfcName = (char *)compareTo.c_str();

	FILE* fileTo;
	fileTo = fopen(mfcName, "r");
	fread(&lengthTo,sizeof(int), 1, fileTo);
	float signalTo[lengthTo*dim_mfcc];



	for(int i = 0; i<lengthTo*dim_mfcc;i++){
		fread(&signalTo[i],sizeof(float), 1, fileTo);
	}





	float ret = dtw(length, lengthTo, dim_mfcc, signal, signalTo);
	cout<<"Score: "<<ret<<endl;
	return ret;
}

/**
* Calcul la MFC d'un fichier audio et l'enregistre dans un fichier mfc
*/
void saveMFC(string wavFile){
	float* signal;
	int length;
	toMFCC(wavFile, &signal, &length);
	char mfcName[wavFile.size()];
	nameWavToMfc((char *) wavFile.c_str(), mfcName);

	FILE* mfcFile = fopen(mfcName, "w");

	string cLength = ""+length;

	fwrite(&length,sizeof(int),1,mfcFile);


	fwrite(signal,sizeof(float),length*dim_mfcc,mfcFile);

	fclose(mfcFile);
}


int main(int argc, char *argv[]) {

	/*float* sequence1 = new float[2];
	sequence1[0] = 1.1;
	sequence1[1] = 1.2;
	float* sequence2 = new float[3];
	sequence2[0] = 2.2;
	sequence2[1] = 2.8;
	sequence2[2] = 2.4;
*/


	string s = "M05_arretetoi.wav";

	float* signal;
	int length;

	//toMFCC(s, &signal, &length);

	//saveMFC(s);


	compareMFC("F01_etatdurgence.wav","M01_arretetoi.mfc");



	/*
	float result;
	result = dtw(length,length,13,signal,signal);


	//cout<<"fin"<<endl;
	cout<<result<<endl;*/

	/*delete[] sequence1;
	delete[] sequence2;*/
	return 0;


}
