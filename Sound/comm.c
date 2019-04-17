#include "comm.h"
#include <math.h>
#include <stdio.h>
#include <curl/curl.h>

/*	function definition
	This function takes in 80 pieces of rms value each is calculated by 200 samples
	This function should use this value to recalculate 8 pieces of  fast decibel value
	We need to put every 10 pieces of rms value square each of them and multiply by 200,
	accumulate to a sum, and then divide by 2000 then square root the result.
*/
void sendToServer(double rms[]){
	double fast[8], sum;
	int i, j;
	CURL *curl;
	CURLcode res;
	char post[1000];

	for(i=0; i<8; i++){
		 for(j=0, sum=0; j<10; j++){
		 	sum += (rms[j+i*10]*rms[j+i*10])*200;
		 }//end of for j
		 fast[i] = sqrt(sum/2000);
	}// end of for i
	sprintf(post, "data=%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f",
			fast[0], fast[1], fast[2], fast[3], fast[4], fast[5], fast[6], fast[7]);

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl){
		/*
		First set the URL that is about to receive our POST. This URL can just
		as well be a http://URL if that is what should receive the data.
		*/
		curl_easy_setopt(curl, CURLOPT_URL, URL);
	  	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);	//Specify the POST data
	  	res = curl_easy_perform(curl);						//Perform the request, res will get the return code
		if(res != CURLE_OK)									//Check for error
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		curl_easy_cleanup(curl);		//clean up
	}
	curl_global_cleanup();
}
