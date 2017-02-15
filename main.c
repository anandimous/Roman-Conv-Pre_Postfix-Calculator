#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "cstack.h"
#include "romanConv.h"
#include "main.h"

// Returns precedence value of corresponding operator
int getPrec(char c){
	if (c == '(') { return 3; }
	else if (c == ')') { return 3; }
	else if (c == "*") { return 2; }
	else if (c == "/") { return 2; }
	else if (c == "+") { return 1; }
	else if (c == "-") { return 1; }
	else {
		//error
		std::cout << "error: argument is not an operator" << std::endl;
		return -1;
	}
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//IMP INFO: THIS METHOD CANNOT PROCESS ANY ROMAN NUMERALS IN THE INPUT STRING, SO CONVERSION IS REQD BEFORE PASSING AS PARAM
char* postfix(char* str) {
	int max = strlen(str);	//size of input string
	char* post[max];	//output postfix string
	//declared and initialized stack
	struct node* stack;
	stack.init();

	for(int i=0; i<max; i++) {
		//check if is operand
		if(isdigit(str[i])) {
			strncat (post, str, 1);
		}
		//check if is operator
		else if(str[i] == '+' || str[i] == '*' || str[i] == '-' || str[i] == '/' || str[i] == '(' || str[i] == ')') {
			if(stack.isEmpty()) { stack.push(str[i]); } //push op if empty stack
			else {
				while(!stack.isEmpty() && stack.peek().getPrec() > str[i].getPrec()) {
					//checking precedence of chars in input string w/t the stack and append popped char to output string when condition is met
					if(str[i].getPrec() < stack.peek().getPrec()) { strncat(post, stack.pop(), 1); }
					else { stack.push(str[i]); }
				}
			}
		}
	}
	while(!stack.isEmpty()) { strcat(post, stack.pop()); } //append all remaining elements in the stack to the postfix string

	return post;
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

char* prefix(char* str) {
	//TBD, but it's really easy

	char* preStr = strReverse(str);
	size_t len = strlen(preStr);
	for (int i = 0; i < len; i++){
		if (preStr[i] == '('){
			preStr[i] = ')';
		}
		else if (preStr[i] == ')'){
			preStr[i] = '(';
		}
	}
	preStr = postfix(preStr);
	preStr = strReverse(str);
	return preStr;

}

/*--------------------------------------------------------------------------------------------------------------------------------------*/
char* strReverse(char* str) { 
	char temp, *finalStr;
	size_t len,j;
	if (str != NULL)
	{
		len = strlen(str);	
		finalStr = str;
		if (len > 1) {
			j = len - 1;
			for (int i = 0; i < len; i++){
				finalStr[i] = str[j];
				j--;
			}
		}
		return finalStr;
	}
	return str;
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

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
	const char* matchesOp = "+-*/()";

	//check cmd line args
	if (argc != 2){
		std::cout << "error: incorrect number of arguments" << std::endl;
		return -1;
	}

	//file validation

	// Checks if input file has extension .in
	ret = strstr(argv[1],".in");
	if (ret == NULL){
		inFile = strAppend(argv[1],".in");
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

/*--------------------------------------------------------------------------------------------------------------------------------------*/

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

/*--------------------------------------------------------------------------------------------------------------------------------------*/
