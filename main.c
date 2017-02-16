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
	char* post;	//output postfix string
	//declared and initialized stack
	struct node* stack;
	init(stack);

	for(int i=0; i<max; i++) {
		//check if is operand
		if(isdigit(str[i])) {
			chAppend(post,str[i]);
		}
		//check if is operator
		else if(strchr(matchesOp,str[i]) != NULL) {
			if(isEmpty(stack)) { push(stack,str[i]); } //push op if empty stack
			else {
				while(!isEmpty(stack) && getPrec(peek(stack)) > getPrec(str[i])) {
					//checking precedence of chars in input string w/t the stack and append popped char to output string when condition is met
					if(getPrec(str[i]) < getPrec(peek(stack))) {
						chAppend(post,pop(stack));
					 }
					else { push(stack,str[i]);
					}
				}
			}
		}
	}
	while(!isEmpty(stack)) {
		chAppend(post,pop(stack));
	 } //append all remaining elements in the stack to the postfix string

	return post;
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

void chAppend(char* str, char ch){
	int len = strlen(str);
	str[len] = ch;
	str[len+1] = '\0';
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
		printf("error: incorrect number of arguments\n");
		return -1;
	}

	//file validation

	// Checks if input file has extension .in
	char* ret = strstr(argv[1],".IN");
	if (ret == NULL){
		inFile = strAppend(argv[1],".IN");
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
	long size;
	if(!fp) {
		perror("Error opening file: File DNE!");
		return -1;
	}
	else{
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

	// Open file to output stream fp
	FILE *fo = fopen(outFile, "w");

	//file input stream, saves expression as char* to exp
	// ch = fgetc(fp);
	// while (ch != EOF) {
	// 	chAppend(exp,ch);
	// 	ch = fgetc(fp);
	// }
	//
	// fclose(fp);

	// convert string with roman nums to string with only integers

	if (strstr(exp,matchesRoman) != NULL){
		bool isOp = false;
		for (int i = 0; i < strlen(exp)+1; i++){

			if (isdigit(exp[i])){				// Append Digit -> finalExp
				chAppend(finalExp,exp[i]);
			}

			else if (strchr(matchesSpace,exp[i])){	// Append ' ' -> finalExp
				if (strlen(roman_str) > 0){

				}
				else {
					chAppend(finalExp,exp[i]);
				}
			}

			else if (strchr(matchesRoman,exp[i]) != NULL) {  // Append roman num -> roman_str

				isOp = false;
				chAppend(roman_str,exp[i]);
			}
			else if (strchr(matchesOp,exp[i]) != NULL) {
				if (!isOp && strlen(roman_str) > 0) {
					temp = finalConvert(roman_to_arabic(roman_str),roman_str);
					sprintf(tempStr,"%d", temp);
					strAppend(finalExp,tempStr);

					roman_str = "";
				}
				isOp = true;
				chAppend(finalExp,exp[i]);
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
	chAppend(tempStr,calc(finalExp));
	fputs(tempStr, fo);
	fclose(fo);
	return 0;

}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

char calc(char* str){
	const char* matchesCalc = "+-*/";
	char* finalExp = "";
	struct node* stack;
	init(stack);

	struct node* opStack;
	init(opStack);

	for(int i=0; i<strlen(finalExp); i++) {
		if(isdigit(finalExp[i])) {
			push(stack,finalExp[i]);
		}

		else if (finalExp[i] == '(') {
			push(opStack,finalExp[i]);
		}

		else if (finalExp[i] == ')') {
			while (peek(opStack) != '('){
				char op = pop(opStack);
				int val2 = pop(stack);
				int val1 = pop(stack);

				if (op == '+'){
					val1 = val1 + val2;
					push(stack,val1 + '0');
				}
				else if (op == '-'){
					val1 = val1 - val2;
					push(stack,val1 + '0');
				}
				else if (op == '*'){
					val1 = val1 * val2;
					push(stack,val1 + '0');
				}
				else if (op == '/'){
					val1 = val1 / val2;
					push(stack,val1 + '0');
				}
			}
			pop(opStack);
		}

		else if (strchr(matchesCalc,finalExp[i])){
			while (!isEmpty(opStack) && getPrec(peek(opStack)) >= getPrec(finalExp[i])){
				char op = pop(opStack);
				int val2 = pop(stack);
				int val1 = pop(stack);
				if (op == '+'){
					val1 = val1 + val2;
					push(stack,val1 + '0');
				}
				else if (op == '-'){
					val1 = val1 - val2;
					push(stack,val1 + '0');
				}
				else if (op == '*'){
					val1 = val1 * val2;
					push(stack,val1 + '0');
				}
				else if (op == '/'){
					val1 = val1 / val2;
					push(stack,val1 + '0');
				}

				push(opStack,finalExp[i]);
			}
		}

	}

	while(!isEmpty(opStack)) {
		char op = pop(opStack);
		int val2 = pop(stack);
		int val1 = pop(stack);
		if (op == '+'){
			val1 = val1 + val2;
			push(stack,val1 + '0');
		}
		else if (op == '-'){
			val1 = val1 - val2;
			push(stack,val1 + '0');
		}
		else if (op == '*'){
			val1 = val1 * val2;
			push(stack,val1 + '0');
		}
		else if (op == '/'){
			val1 = val1 / val2;
			push(stack,val1 + '0');
		}

	}
	return pop(stack);

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
