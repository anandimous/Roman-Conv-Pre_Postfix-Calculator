#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include "romanConv.h"

//Roman Char Array to Arabic Int Array
int* roman_to_arabic(char* nums){
	int* converted = (int*)malloc(20 * sizeof(int));
	const char* matchesI = "Ii";
	const char* matchesV = "Vv";
	const char* matchesX = "Xx";
	const char* matchesL = "Ll";
	const char* matchesC = "Cc";
	const char* matchesD = "Dd";
	const char* matchesM = "Mm";
	const char* matchesSp = " ";

	for (int i=0; i < strlen(nums); i++){
		if (strchr(matchesI, nums[i]) != NULL){
			converted[i] = 1;
		}
		else if (strchr(matchesV,nums[i]) != NULL){
			converted[i] = 5;
		}
		else if (strchr(matchesX,nums[i]) != NULL){
			converted[i] = 10;
		}
		else if (strchr(matchesL,nums[i]) != NULL){
			converted[i] = 50;
		}
		else if (strchr(matchesC,nums[i]) != NULL){
			converted[i] = 100;
		}
		else if (strchr(matchesD,nums[i]) != NULL){
			converted[i] = 500;
		}
		else if (strchr(matchesM,nums[i]) != NULL){
			converted[i] = 1000;
		}
		else if (strchr(matchesSp,nums[i]) != NULL){
			// Do Nothing
		}
		else {
			converted[i] = -1;
		}
	}
	return converted;
}

int finalConvert(int* nums, char* roman){
	int max = 0;
	int check = -1;
	int total = 0;
	char* matchesNum = "123456789";

	for(int j = strlen(roman)-1; j >= 0; j--){
		if(nums[j] == check) {
			printf("error\n");
		}

		char temp[5];
		sprintf(temp, "%d", nums[j+2]);

		if(strstr(matchesNum, temp) != NULL) {
			if(nums[j] < nums[j+2]) {
				return -1;
			}
		}
		//1 1 5
	}

	for (int i = strlen(roman)-1; i >= 0; i--){
		if (nums[i] >= max){
			max = nums[i];
			total += max;
		}
		else {
			total -= nums[i];
		}
	}
	return total;
}
