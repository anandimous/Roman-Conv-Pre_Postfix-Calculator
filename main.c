#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include "cstack.h"
#include "romanConv.h"
#include "main.h"

// Returns precedence value of corresponding operator
int getPrec(char c){
	if (c == '(') { return 3; }
	else if (c == ')') { return 3; }
	else if (c == '*') { return 2; }
	else if (c == '/') { return 2; }
	else if (c == '+') { return 1; }
	else if (c == '-') { return 1; }
	else {
		//error
		return -1;
	}
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//IMP INFO: THIS METHOD CANNOT PROCESS ANY ROMAN NUMERALS IN THE INPUT STRING, SO CONVERSION IS REQD BEFORE PASSING AS PARAM
char* postfix(char* str) {

	const char* matchesOp = "+-*/()";
	int max = strlen(str);	//size of input string
	char* post = "";	//output postfix string
	//declared and initialized stack
	struct node* stack = NULL;

	for(int i=0; i<max; i++) {
		//check if is operand
		if(isdigit(str[i])) {
			post = chAppend(post,str[i]);
		}
		//check if is operator
		else if(strchr(matchesOp,str[i]) != NULL) {
			if(isEmpty(stack)) { stack = push(stack,str[i]); } //push op if empty stack
			else {
				while(!isEmpty(stack) && getPrec(peek(stack)) > getPrec(str[i])) {
					//checking precedence of chars in input string w/t the stack and append popped char to output string when condition is met
					if(getPrec(str[i]) < getPrec(peek(stack))) {
						post = chAppend(post,peek(stack));
						stack = pop(stack);
					 }
					else { stack = push(stack,str[i]); }
				}
			}
		}
	}
	while(!isEmpty(stack)) {
		post = chAppend(post,peek(stack));
		stack = pop(stack);
	 } //append all remaining elements in the stack to the postfix string

	return post;
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

char* chAppend(char* str, char ch){
	int len = strlen(str);
	char* str2 = malloc(sizeof(char)*(len+1));
	strcpy(str2, str);
	str2[len] = c;
	str2[len + 1] = '\0';
	return str2;
	free(str2);
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

char* prefix(char* str) {

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
char* strReverse(char* str) {  // returns the reverse of a string
	char *finalStr;
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
	int ch;
	int temp;
	char* tempStr = "";
	char* inFile = argv[1];
	char* outFile;
	char* exp = "";
	char* finalExp = "";
	char* roman_str = "";
	const char* matchesRoman = "IiVvXxLlCcDdMm";
	const char* matchesSpace = " ";
	const char* matchesOp = "+-*/()";

	//check cmd line args
	if (argc != 2){
		printf("error: incorrect number of arguments");
		return -1;
	}

	//file validation

	// Checks if input file has extension .in
	char* ret = strstr(argv[1],".IN");
	if (ret == NULL){
		inFile = strAppend(argv[1],".IN");
	}
	else {
		inFile = argv[1];
	}

	outFile = strAppend(inFile, " ");
	for(int j = 0; j < strlen(outFile); j++) {
		if(outFile[j] == '.') {
			outFile[j+1] = 'O';
			outFile[j+2] = 'U';
			outFile[j+3] = 'T';
			outFile[j+4] = '\0';
			outFile[j+5] = '\0';
			break;
		}
	}

	// Open file to input stream fp
	FILE *fp = fopen(inFile, "r");
	// if(fp == NULL) {
	// 	printf("Error opening file: File DNE!");
	// 	return -1;
	// }

	if(!fp) {
 		perror("Error opening file: File DNE!");
 		return -1;
 	}
	else{
		long size;
		fseek (fp, 0, SEEK_END);
		size = ftell(fp);
		fseek (fp, 0, SEEK_SET);
		exp = malloc (size + 1);

		if (exp){
				fread (exp, 1, size, fp);
		}
		fclose (fp);
		exp[size] = '\0';
	}

	 FILE *fo = fopen(outFile, "w");

	fclose(fp);

	// convert string with roman nums to string with only integers

	if (strstr(exp,matchesRoman) != NULL){
		bool isOp = false;
		for (int i = 0; i < strlen(exp)+1; i++){

			if (isdigit(exp[i])){				// Append Digit -> finalExp
				finalExp = chAppend(finalExp,exp[i]);
			}

			else if (strchr(matchesSpace,exp[i])){	// Append ' ' -> finalExp
				if (strlen(roman_str) > 0){

				}
				else {
					finalExp = chAppend(finalExp,exp[i]);
				}
			}

			else if (strchr(matchesRoman,exp[i]) != NULL) {  // Append roman num -> roman_str

				isOp = false;
				roman_str = chAppend(roman_str,exp[i]);
			}
			else if (strchr(matchesOp,exp[i]) != NULL) {
				if (!isOp && strlen(roman_str) > 0) {
					temp = finalConvert(roman_to_arabic(roman_str),roman_str);
					sprintf(tempStr,"%d", temp);
					strAppend(finalExp,tempStr);

					roman_str = "";
				}
				isOp = true;
				finalExp = chAppend(finalExp,exp[i]);
			}
			else if (exp[i] == '\0' && strlen(roman_str) > 0){
				temp = finalConvert(roman_to_arabic(roman_str),roman_str);
				sprintf(tempStr,"%d",temp);
				strAppend(finalExp,tempStr);
				roman_str = "";
			}

		}
	}


	fputs("Prefix: ", fo);
	fputs(prefix(finalExp), fo);
	fputs("\n", fo);
	fputs("Postfix: ", fo);
	fputs(postfix(finalExp), fo);
	fputs("\n", fo);
	fputs("Value: ", fo);
	tempStr = "";
	tempStr = chAppend(tempStr,calc(finalExp));
	fputs(tempStr, fo);
	fclose(fo);
	return 0;

}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

char calc(char* str){
	const char* matchesCalc = "+-*/";
	char* finalExp = "";
	struct node* stack = NULL;
	struct node* opStack = NULL;

	for(int i=0; i<strlen(finalExp); i++) {
		if(isdigit(finalExp[i])) {
			stack = push(stack,finalExp[i]);
		}

		else if (finalExp[i] == '(') {
			stack = push(opStack,finalExp[i]);
		}

		else if (finalExp[i] == ')') {
			while (peek(opStack) != '('){
				char op = peek(opStack);
				opStack = pop(opStack);
				int val2 = peek(stack);
				stack = pop(stack);
				int val1 = peek(stack);
				stack = pop(stack);

				if (op == '+'){
					val1 = val1 + val2;
					stack = push(stack,val1 + '0');
				}
				else if (op == '-'){
					val1 = val1 - val2;
					stack = push(stack,val1 + '0');
				}
				else if (op == '*'){
					val1 = val1 * val2;
					stack = push(stack,val1 + '0');
				}
				else if (op == '/'){
					val1 = val1 / val2;
					stack = push(stack,val1 + '0');
				}
			}
			peek(opStack);
			opStack = pop(opStack);
		}

		else if (strchr(matchesCalc,finalExp[i])){
			while (!isEmpty(opStack) && getPrec(peek(opStack)) >= getPrec(finalExp[i])){
				char op = peek(opStack);
				opStack = pop(opStack);
				int val2 = peek(stack);
				stack = pop(stack);
				int val1 = peek(stack);
				stack = pop(stack);

				if (op == '+'){
					val1 = val1 + val2;
					stack = push(stack,val1 + '0');
				}
				else if (op == '-'){
					val1 = val1 - val2;
					stack = push(stack,val1 + '0');
				}
				else if (op == '*'){
					val1 = val1 * val2;
					stack = push(stack,val1 + '0');
				}
				else if (op == '/'){
					val1 = val1 / val2;
					stack = push(stack,val1 + '0');
				}

				opStack = push(opStack,finalExp[i]);
			}
		}

	}

	while(!isEmpty(opStack)) {
		char op = peek(opStack);
		opStack = pop(opStack);
		int val2 = peek(stack);
		stack = pop(stack);
		int val1 = peek(stack);
		stack = pop(stack);

		if (op == '+'){
			val1 = val1 + val2;
			stack = push(stack,val1 + '0');
		}
		else if (op == '-'){
			val1 = val1 - val2;
			stack = push(stack,val1 + '0');
		}
		else if (op == '*'){
			val1 = val1 * val2;
			stack = push(stack,val1 + '0');
		}
		else if (op == '/'){
			val1 = val1 / val2;
			stack = push(stack,val1 + '0');
		}

	}
	return peek(stack);
	stack = pop(stack);

}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//Concatenates two strings, returns a new string
char* strAppend(char* str1, char* str2){
	char* newStr;
	int total_len = strlen(str1) + strlen(str2);
	if ((newStr = malloc(sizeof(char)*(total_len+1))) != NULL){
		newStr[0] = '\0';
		strcat(newStr,str1);
		strcat(newStr,str2);
		return newStr;
		free(newStr);
	}
	else {
		printf("malloc failed for strAppend");
		return "";
	}
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/
