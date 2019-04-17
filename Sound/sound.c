#include "comm.h"
#include "screen.h"
#include "sound.h"
#include <stdio.h>
#include <math.h>

/*	function definition of printID()
	This function would print ID in char type
	argument: id
	return : no
*/
void printID(char id[]){
	int i;
	for(i=0; i<4; i++)
		printf("%c", id[i]);
	printf("\n");
}

//function definition of dispWAVData()

void dispWAVData(char filename[]){
	int i,j;		//loop counters
	FILE *fp;		//file handler to open the file "test.wav"
	double rms[80],sum;
	short samples[SAMPLERATE];		//totally 16000 samples in 1 sec
	WAVHeader mh;		//just used to skip over the header of wav file
	fp = fopen(filename, "r");
	if(fp == NULL){			// if cannot open the file, print error
		printf("Error when openning the file! \n");
		return;
	}
	fread(&mh, sizeof(mh), 1, fp);		//skip over the header of wave file
	fread(samples, sizeof(short), SAMPLERATE,fp);
	fclose(fp);
	clearScreen();
	for(i=0; i<80; i++){			// run 80 loops, each loop has 200 samples
		for(j=0, sum=0.0; j<SAMPLERATE/80; ++j){		// run 200 samples
			sum += samples[j+i*200]*samples[j+i*200];		//calculate the sum of 200 samples
		}
		rms[i]= sqrt(sum/200);							// calculate the rms value of the sum of sample
#ifdef DEBUG			// if DEBUG is enabled
		printf("rms[%d]: %10.4f, dB= %10.4f\n",i,rms[i], 20*log10(rms[i]));			// print rms value  and dB value
#else					// if DEBUG is disabled
		dispBar(i, 20*log10(rms[i]));		//display dB value in a bar type
#endif
	}
#ifdef COMM				// if COMM is enabled
	sendToServer(rms);						// send to server data
#endif
}

/*	function definition of dispWAVHeader()
	This function print the WAVE file format
	argument : .wav file
*/
void dispWAVHeader(char filename[]){
	FILE *fp;
	WAVHeader mh;	//an instance of WAVHeader struct

	//open the test.wav file for reading
	fp = fopen(filename,"r");
	if(fp == NULL){
		printf("Error when open the file! \n");
		return;		//function stop
	}
	fread(&mh, sizeof(mh), 1, fp);
	fclose(fp);	//close the opened file
	printf("Chunk ID : ");
	printID(mh.chunkID);								//print the chunk ID contains the letter "RIFF" in ASCII form
	printf("  chunk size: %d\n",mh.chunkSize);			// print chunk size
	printf("Format: ");
	printID(mh.format);									// print format contains the letter "WAVE"
	printf("  subchunk 1 ID: ");
	printID(mh.subchunk1ID);							// print subchunk ID  contains letter "fmt"
	printf("  subchunk 1 size: %d\n",mh.subchunk1Size);	// 16 for PCM
	printf("  audioFormat: %d\n",mh.audioFormat);		// PCM = 1
	printf("  numChannels: %d\n",mh.numChannels);
	printf("  sampleRate: %d\n",mh.sampleRate);
	printf("  byteRate: %d\n",mh.byteRate);
	printf("  blockAlign: %d\n",mh.blockAlign);
	printf("  bitsPerSample: %d\n",mh.bitsPerSample);
	printf("  subchunk 2 ID: ");						// contains the letter "data"
	printID(mh.subchunk2ID);
	printf("  subchunk 2 size: %d\n",mh.subchunk2Size);
}
