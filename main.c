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
		else if(str[i] == '\n'){

		}
		else { // string is unknown

		}
	}
	while(!isEmpty(stack)) {
		post = chAppend(post,peek(stack));
		stack = pop(stack);
	 } //append all remaining elements in the stack to the postfix string

	return post;
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

char* chAppend(char* str, char c){
	int len = strlen(str);
	char* str2 = malloc(len+2);  //accounts for end terminator
	strcpy(str2, str);
	str2[len] = c;
	str2[len + 1] = '\0';
	return str2;
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
	char* postStr = postfix(preStr);
	return strReverse(postStr);

}

/*--------------------------------------------------------------------------------------------------------------------------------------*/
char* strReverse(char* str) {  // returns the reverse of a string
	int length;
	char *start, *end, temp;
	if (str != NULL)
	{
		length = strlen(str);
		start = str;
		end = str;

		// point end to the end of str
		for (int i = 0; i < length-1; i++){
			end++;
		}
		// swap pointers from beginning and end of str, work to middle
		for (int i = 0; i < length/2; i++){
			temp = *end;
			*end = *start;
			*start = temp;

			start++;
			end--;
		}
	}
	return  str;
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]){
	int temp;
	char* tempStr = "";
	char* inFile = argv[1];
	char* outFile;
	// char* ret;
	char* bfr = "";
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

	outFile = strAppend(inFile, " ");
	// outFile -> inFile.OUT
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

	// Get size of file to malloc for our string buffer
	else{
		long size;
		fseek (fp, 0, SEEK_END);
		size = ftell(fp);
		fseek (fp, 0, SEEK_SET);
		bfr = malloc (size + 1);
		finalExp = malloc(size + 1);

		if (bfr){
				fread (bfr, 1, size, fp);
		}
		bfr[size] = '\0';
		fclose(fp);
	}

	FILE *fo = fopen(outFile, "w");
	if (!fo) {
		perror("Error opening outFile: Creation Failed!");
		return -1;
	}
	else{
	// check if bfr contains any illegal characters --> Error!
		for (int i = 0; i < strlen(bfr); i++){
			if ( (strchr(matchesRoman,bfr[i]) != NULL) ||
						(strchr(matchesOp,bfr[i]) != NULL) ||
						(strchr(matchesSpace,bfr[i]) != NULL) ||
						(strchr("\n",bfr[i]) != NULL) ||
						(isdigit(bfr[i])) ){
							// The character is allowed
			}
			else {
				//fputs("Error!", fo);
				fprintf(fo,"Error!");
				fclose(fo);
				return 0;
			}
		}
	}

	// convert string with roman nums to string with only integers

	if (strstr(bfr,matchesRoman) != NULL){
		bool isOp = false;
		for (int i = 0; i < strlen(bfr)+1; i++){

			if (isdigit(bfr[i])){				// Append Digit -> finalExp
				finalExp = chAppend(finalExp,bfr[i]);
			}

			else if (strchr(matchesSpace,bfr[i])){	// Append ' ' -> finalExp
				if (strlen(roman_str) > 0){

				}
				else {
					finalExp = chAppend(finalExp,bfr[i]);
				}
			}

			else if (strchr(matchesRoman,bfr[i]) != NULL) {  // Append roman num -> roman_str

				isOp = false;
				roman_str = chAppend(roman_str,bfr[i]);
			}
			else if (strchr(matchesOp,bfr[i]) != NULL) {
				if (!isOp && strlen(roman_str) > 0) {
					temp = finalConvert(roman_to_arabic(roman_str),roman_str);
					sprintf(tempStr,"%d", temp);
					strAppend(finalExp,tempStr);

					roman_str = "";
				}
				isOp = true;
				finalExp = chAppend(finalExp,bfr[i]);
			}
			else if (bfr[i] == '\0' && strlen(roman_str) > 0){
				temp = finalConvert(roman_to_arabic(roman_str),roman_str);
				sprintf(tempStr,"%d",temp);
				strAppend(finalExp,tempStr);
				roman_str = "";
			}

		}
	}
	else {
		finalExp = bfr;
	}

	// Used to get Infix as prefix and as postfix in prep for file write

	char* prefStr = finalExp;
	char* postStr = finalExp;
	prefStr = prefix(prefStr);
	postStr = postfix(postStr);

	// BEGIN FILE WRITING

	fputs("Prefix: ", fo);
	fputs(prefStr, fo);
	fputs("\n", fo);
	fputs("Postfix: ", fo);
	fputs(postStr, fo);
	fputs("\n", fo);
	fputs("Value: ", fo);
	tempStr = chAppend(tempStr,calc(finalExp));
	fputs(tempStr, fo);
	fclose(fo);
	return 0;

}

/*--------------------------------------------------------------------------------------------------------------------------------------*/
// Calculates value of infix expression
char calc(char* finalExp){
	const char* matchesCalc = "+-*/";
	struct node* stack = NULL;
	struct node* opStack = NULL;
	int length = strlen(finalExp);

	for(int i=0; i<length; i++) {
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
