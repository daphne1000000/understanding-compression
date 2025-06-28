# Understanding Compression

Lately I've been very interested in digital audio and video technologies, and at the basis of all of the technologies is compression. In order to understand it better I've been reading [Understanding Compression](https://www.amazon.com/Understanding-Compression-Data-Modern-Developers/dp/1491961538). Here are just a collection of my notes on the topic as well as some relevant code that corresponds to different subtopics.

## 1. Entropy 

Entropy is the basis of all subsequent developments in the science of compression. Claude Shannon defined entropy as the minimum number of bits to represent some dataset. You can define Entropy with the following equation:
$$H(s) = - \sum_{i=1}^np_i\log_2(p_i)$$
The science of compression is built around trying to transform a dataset to minimize the entropy value. 

In order to break down this equation further I have [a program](entropy/entropy.c) that implements an algorithm that determines the entropy value of any given string. If we run the program on any arbitrary string its entropy value is computed:
```
./entropy                 
Please enter in your string: ABBCCCDDDD
The entropy value of ABBCCCDDDD is 1.846439
This means that ABBCCCDDDD can be represented using 20 total bits
```
First we calculate the set of unique characters in the string, in this case \[A,B,C,D\]. Next we calculate the probability of each characters occurence which is the amount of times the character occurs divided by the total length of the string.

Then we get the $log_2$ of each probability, and multiply that to the probability of each character, then repeat for each character and sum them together. This is represented in the code as follows:

```
double entropy(int *hist,int histlen,int len){
	int i;
	double H;
	H=0;
	for(i=0;i<histlen;i++){
		H-=(double)hist[i]/len*log2((double)hist[i]/len); // This is just the entropy function
	}
	return H;
}
```

### 1.1 What this entropy stuff is good for

Because the entropy value of ABBCCCDDDD is 1.846439, we can say that it can be represented using 2 bits per value (rounding up to the next integer because binary numbers). This means that we can represent our previous set with only 20 bits since:
$$ G^e=H(G) * |G| $$
And according to Shannon's entropy, that's the smallest size it can be. The point of compression, though, is to make this value smaller.

### 1.2 Breaking entropy

We do this by exploiting two properties about data. Entropy, as defined by Shannon, only cares about probability of occurence, not ordering. But as it turns out, ordering is very important.

#### 1.2.1 Delta Coding

Delta coding is a transform that encodes a series of numbers as the difference from a previous number. If we take the two sets $[0,1,2,3,4,5,6,7]$ and $[1,0,2,4,3,5,7,6]$ we can see why this could be important.

According to Shannon, these two sets have the exact same entropy, $H=3$, when in fact we can encode the first set as $[0,1,1,1,1,1,1,1]$ with $H=1$. The second set we don't get much gain, if any, because it's unordered, and we'd need to encode bits to mean a decrease in value. 

## 2. Variable-Length Codes 