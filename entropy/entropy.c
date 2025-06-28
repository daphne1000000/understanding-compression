/* This code originated here: https://rosettacode.org/wiki/Entropy#C
 * I've only extended it in minor ways and added more verbose print statements to explain the details
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
 
#define MAXLEN 100 //maximum string length
 
int makehist(unsigned char *S,int *hist,int len){
	int wherechar[256]; // creates a lookup table 
	int i,histlen;
	histlen=0;
	for(i=0;i<256;i++)wherechar[i]=-1; // intializes each index in the lookup to -1
	for(i=0;i<len;i++){
		if(wherechar[(int)S[i]]==-1){
			wherechar[(int)S[i]]=histlen; // if the character has not been seen before, it gets assigned an index in the array
			histlen++; // the amount of unique characters is increased
		}
		hist[wherechar[(int)S[i]]]++; //the index in the histogram of that character is incremented
	}
	return histlen;
}
 
double entropy(int *hist,int histlen,int len){
	int i;
	double H;
	H=0;
	for(i=0;i<histlen;i++){
		H-=(double)hist[i]/len*log2((double)hist[i]/len); // This is just the entropy function
	}
	return H;
}
 
int main(void){
	unsigned char S[MAXLEN];
	int len,*hist,histlen;
	double H; // H comes from the greek letter eta, in reference to Boltzmann's H-theorem
    printf("Please enter in your string: ");
	scanf("%[^\n]",S);
	len=strlen(S);
	hist=(int*)calloc(len,sizeof(int)); // A histogram of all of the characters in the string, i.e. how many times does each character occur
	histlen=makehist(S,hist,len); // histlen is the amount of unique characters in the string
	//hist now has no order (known to the program) but that doesn't matter
	H=entropy(hist,histlen,len);
	printf("The entropy value of %s is %lf\n",S,H);
    int representable = (ceil(H) * len); // The smallest amount of bits necessary to represent a set G is H(G) * |G| 
    printf("This means that %s can be represented using %d total bits\n", S, representable);
	return 0;
}
