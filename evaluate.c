#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>



int main(int argc, char *argv[]){
	int inNameSize;
	int ch;
	char* inFile;
	char* outFile;
	FILE* fp;
	char* ret;
	char* exp = "";
	const char* matchesNums = " 1234567890";
	const char* matchesRoman = " IiVvXxLlCcDdMm";
	const char* matchesSpace = " ";
	const char* matchesOp = " +-*/()";

	//check cmd line args
	if (argc != 3){
		std::cout << "error: incorrect number of arguments" << std::endl;
		return -1;
	}

	//file validation
	
	// Checks if input file has extension .in
	ret = strstr(argv[1],".in");
	if (ret == NULL){
		inFile = strAppend(argv[1],".in");
	}

	// Checks if output file has extension .out
	ret = strstr(argv[2],".out");
	if (ret == NULL){
		outFile = strAppend(argv[2],".out");
	}

	// Open file to input stream fp
	fp = fopen(inFile, "r");
	if(fp == NULL) {
		perror("Error opening file: File DNE!");
		return -1;
	}

	//file input stream, saves expression as char* to exp
	ch = getc(fp);
	while (ch != EOF) // BEGIN FILE READ
	{
		exp = strAppend(exp,(char*) ch);
		ch = getc(fp);
	}
}

//Concatenates two strings, returns a new string
char* strAppend(char* str1, char* str2){
	char * newStr;
	if ((newStr = malloc(strlen(str1)+strlen(str2)+1)) != NULL){
		newStr[0] = '\0';
		strcat(newStr,str1);
		strcat(newStr,str2);
		return newStr;
	}
	else {
		perror("malloc failed for strAppend");
		return "";
	}
}

// Returns precedence value of corresponding operator
int getPrec(char c){
	if (c == '('){
		return 3;
	}
	else if (c == ')'){
		return 3;
	}
	else if (c == "*"){
		return 2;
	}
	else if (c == "/"){
		return 2;
	}
	else if (c == "+"){
		return 1;
	}
	else if (c == "-"){
		return 1;
	}
	else {
		//error
		std::cout << "error: argument is not an operator" << std::endl;
		return -1;
	}
}


