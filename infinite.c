/* infinite.c */
#include "calculator.h"
#include <string.h>

char* substring(char *des, char a[], int start, int size) {
	strncpy(des, a+start, size);
	*(des+size) = '\0';
	return des;
}

numSet* makeSetL(infinite** inf, char *num) {
	printf("makeSetL: %s\n", num);
	numSet* left = NULL;
	int length = strlen(num);
	int remain = length % 9;
	char a[1000000];
	if (remain != 0) {
		push_backL(&left, atoi(substring(a, num, 0, remain)));
	}
	for(int i = 0; length-remain-9*i > 0; i++) {
		push_backL(&left, atoi(substring(a, num, remain+(9*i), 9)));
	}
	return left;
}

numSet* makeSetR(infinite** inf, char *num) {
	printf("makeSetR: %s\n", num);
	numSet* right = NULL;
	int length = strlen(num);
	char a[1000000];
	int i = 0;
	while(length >= 9) {
		push_backR(&right, atoi(substring(a, num, 9*(i++), 9)));
		length -= 9;
	}
	if(length != 0) {
		int rtn = atoi(substring(a, num, 9*i, length));
		//printf("atoi:%d\n", rtn);
		for(int i = 0; i < 9-length; i++) { // processing under real num.
			rtn *= 10;
		}
		push_backR(&right, rtn);
	}
	return right;
}

infinite* initialize(char* before) {
	infinite* inf = (infinite*)malloc(sizeof(infinite));
	char* pindex;
	if((pindex = strstr(before, ".")) != NULL) {
		int index = pindex - before;
		char a[100000]; 
		char b[100000];
		inf->left = makeSetL(&inf, substring(a, before, 0, index));
		inf->right = makeSetR(&inf, substring(b, before, index+1, strlen(before)-(index+1)));
	} else {
		inf->left = makeSetL(&inf, before);
		inf->right = NULL;
	}
	return inf;
}

// testing function main
int main() {
	infinite *inf;
	char* input = "4321012345678987654321.9876543212345678901234";
	printf("\nInput is %s\n", input);
	inf = initialize(input);
/*	
	numSet* set = inf->right;
	while(isEndR(set) == 0) {
		numSet* temp = set;
		set = set->right;
		free(temp);
	} free(set);

	set = inf->left;
	while(isEndL(set) == 0) {
		numSet* temp = set;
		set = set->left;
		free(temp);
	} free(set);
*/
	printSetL(inf->left);
	printf(".");
	printSetR(inf->right);
	return 0;
}
