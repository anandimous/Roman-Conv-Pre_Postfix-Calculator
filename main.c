#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include "arrayStack.h"
#include "romanConv.h"
#include "main.h"

// Returns precedence value of corresponding operator
int getPrec(char c){
	if (c == '(' || c == ')') { return 3; }
	else if (c == '*' || c == '/') { return 2; }
	else if (c == '+' || c == '-') { return 1; }
	else {
		//error
		return -1;
	}
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//IMP INFO: THIS METHOD CANNOT PROCESS ANY ROMAN NUMERALS IN THE INPUT STRING, SO CONVERSION IS REQD BEFORE PASSING AS PARAM
char* postfix(char* str) {

	const char* matchesOp = "+-*/()";
	char* post = "";	//output postfix string
	bool needOp = false;
	bool secondCheck = false;

	//declared and initialized stack
	const int SIZE = strlen(str);
	int stTop=0;
	char stack[SIZE];
	init(&stTop);

	for(int i=0; i<strlen(str); i++) {
		//check if is operand
		if(isdigit(str[i])) {
			if (secondCheck){
				return "ERROR";
			}
			needOp = true;
			post = chAppend(post,str[i]);
		}
		//check if is operator
		else if(strchr(matchesOp,str[i]) != NULL) {
			post = chAppend(post,' ');
			secondCheck = false;
			needOp = false;
			// stack empty? push operator
			if(empty(&stTop)) {
				push(stack,&stTop,str[i]);
			}
			else if (str[i] == '('){
				push(stack,&stTop,str[i]);
			}
			else if (str[i] == ')'){ // append all chars from stack until '(' found
				while(!empty(&stTop) && peek(stack,&stTop) != '('){
					post = chAppend(post,pop(stack,&stTop));
				}
				pop(stack,&stTop);
			}
			// char is operator other than ( or )
			else {
				// if Stack empty --> push
				if(empty(&stTop) || peek(stack,&stTop) == '('){
					push(stack,&stTop,str[i]);
				}
				// if char has higher precedence than top of stack, push it
				else if (getPrec(str[i]) >= getPrec(peek(stack,&stTop))){
					push(stack,&stTop,str[i]);
				}

				else { // append top of stack until operator has higher precedence
					while (!empty(&stTop) &&
								(getPrec(str[i]) < getPrec(peek(stack,&stTop)))){
						post = chAppend(post,pop(stack,&stTop));
					}
					push(stack,&stTop,str[i]);
				}
			}
		}

		else if(str[i] == '\n'){

		}
		else { // string is unknown
			if (str[i] == ' ' && needOp){
				secondCheck = true;

			}
			if (str[i] == ' '){
				post = chAppend(post,' ');
			}
			else if (needOp){
				post = chAppend(post,' ');
			}
		}
	}
	while(!empty(&stTop)) {
		post = chAppend(post,pop(stack,&stTop));
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
	char* tempStr = "";
	char* inFile = argv[1];
	char* outFile;
	// char* ret;
	char* bfr = "";
	char* finalExp = "";
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

	finalExp = ridRoman(bfr);
	if (strcmp(finalExp,"ERROR!") == 0){
		fprintf(fo,"Error!");
		fclose(fo);
		return 0;
	}

	// Used to get Infix as prefix and as postfix in prep for file write

	char* prefStr = finalExp;
	char* postStr = finalExp;
	postStr = postfix(postStr);
	if (strcmp(postStr,"ERROR") == 0){
		fprintf(fo,"Error!");
		fclose(fo);
		return 0;
	}
	prefStr = prefix(prefStr);


	// BEGIN FILE WRITING

	fputs("Prefix: ", fo);
	fputs(prefStr, fo);
	fputs("\n", fo);
	fputs("Postfix: ", fo);
	fputs(postStr, fo);
	fputs("\n", fo);
	fputs("Value: ", fo);
	tempStr = calc(postStr); // < 12
	if (!isdigit(tempStr[0]) && (strcmp(tempStr,"ERROR!") != 0)){
		char fixed = tempStr[0];  // <
		int fixedNum = fixed - '0';  // 12
		char* final = (char*)malloc(sizeof(tempStr));
		sprintf(final,"%d", fixedNum);
		tempStr = final;

	}
	fputs(tempStr, fo);
	fclose(fo);
	return 0;

}

/*--------------------------------------------------------------------------------------------------------------------------------------*/
// convert string with roman nums to string with only integers  2 + IV --> 2 + 4
char* ridRoman(char* bfr){
	char* finalExp = "";
	char* matchesRoman = "IiVvXxLlCcDdMm";
	char* matchesOp = "+-*/()";
	char* roman_str = "";
	int temp;
	int* tempArr;
	bool isOp = false;

	for (int i=0; i<strlen(bfr); i++){
		if (strchr(matchesRoman,bfr[i]) != NULL){
			isOp = true;
		}
	}

	if (isOp){
		isOp = false;
		for (int i = 0; i < strlen(bfr); i++){

			if (isdigit(bfr[i])){				// Append Digit -> finalExp
				finalExp = chAppend(finalExp,bfr[i]);
			}

			else if (bfr[i] == ' '){	// Append ' ' -> finalExp
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
					tempArr = roman_to_arabic(roman_str);
					temp = finalConvert(tempArr,roman_str);	// tempStr = (char)(temp + '0');
					if(!temp) {
						return "ERROR!";
					}
					if(temp == -1) { return "ERROR!";	}
					// strAppend(finalExp,tempStr);
					sprintf(finalExp,"%s%d",finalExp,temp);
					roman_str = "";
				}
				isOp = true;
				finalExp = chAppend(finalExp,bfr[i]);
			}
			else if ((bfr[i] == '\0' || bfr[i] == '\n') && strlen(roman_str) > 0){
				tempArr = roman_to_arabic(roman_str);
				temp = finalConvert(tempArr,roman_str);	// tempStr = (char)(temp + '0');
				if(!temp) {
					return "ERROR!";
				}
				if(temp == -1) { return "ERROR!";	}
				// strAppend(finalExp,tempStr);
				sprintf(finalExp,"%s%d",finalExp,temp);
				roman_str = "";
			}
		}
		if (strlen(roman_str) > 0){
			tempArr = roman_to_arabic(roman_str);
			temp = finalConvert(tempArr,roman_str);	// tempStr = (char)(temp + '0');
			if(!temp) {
				return "ERROR!";
			}
			if(temp == -1) { return "ERROR!";	}
			// strAppend(finalExp,tempStr);
			sprintf(finalExp,"%s%d",finalExp,temp);
			roman_str = "";
		}
		return finalExp;
	}
	else {
		return bfr;
	}
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/
// Calculates value of infix expression
char* calc(char* pfStr){
	char* matchesOp = "+-*/";
	const int SIZE = 3 * (strlen(pfStr));
	char* tempStr = "";
	char* intStr;
	char* intStr2;
	int stTop=0;
	int val1;
	int val2;
	char stack[SIZE];
	init(&stTop);

	for (int i=0; i < strlen(pfStr); i++){
		if (isdigit(pfStr[i])){
			tempStr = "";
			while (isdigit(pfStr[i])){
				tempStr = chAppend(tempStr,pfStr[i]);
				i++;
			}
			i--;
			push(stack,&stTop,':');
			for(int j = strlen(tempStr)-1; j >= 0; j--){
				push(stack,&stTop,tempStr[j]);
			}
			push(stack,&stTop,':');
		}
		else if (strchr(matchesOp,pfStr[i]) != NULL){
			char temp = pop(stack,&stTop);
			if (temp == ':'){
				intStr = "";
				while (peek(stack,&stTop) != ':'){
					intStr = chAppend(intStr,pop(stack,&stTop));
				} // remove ':'
				pop(stack,&stTop);
				val2 = atoi(intStr);
			}
			else {
				// Operating on non-number!!!!!!
			}
			temp = pop(stack,&stTop);
			if (temp == ':'){
				intStr2 = "";
				while (peek(stack,&stTop) != ':'){
					intStr2 = chAppend(intStr2,pop(stack,&stTop));
				} // remove ':'
				pop(stack,&stTop);
				val1 = atoi(intStr2);
			}
			else {
				// Operating on non-number!!!
			}

			if (pfStr[i] == '+'){
				val1 = val1 + val2;
				char* final = (char*)malloc(sizeof(tempStr));
				sprintf(final,"%d",val1);
				// pop(stack,&stTop);
				push(stack,&stTop,':');
				for (int k = strlen(final)-1; k >= 0; k--){
					push(stack,&stTop,final[k]);
				}
				push(stack,&stTop,':');
			}
			else if (pfStr[i] == '-'){
				val1 = val1 - val2;
				char* final = (char*)malloc(sizeof(tempStr));
				sprintf(final,"%d",val1);
				// pop(stack,&stTop);
				push(stack,&stTop,':');
				for (int k = strlen(final)-1; k >= 0; k--){
					push(stack,&stTop,final[k]);
				}
				push(stack,&stTop,':');
			}
			else if (pfStr[i] == '*'){
				val1 = val1 * val2;
				char* final = (char*)malloc(sizeof(tempStr));
				sprintf(final,"%d",val1);
				// pop(stack,&stTop);
				push(stack,&stTop,':');
				for (int k = strlen(final)-1; k >= 0; k--){
					push(stack,&stTop,final[k]);
				}
				push(stack,&stTop,':');
			}
			else if (pfStr[i] == '/'){
				if (val2 == 0){
					return "ERROR!";
				}
				else {
					val1 = val1 / val2;
					char* final = (char*)malloc(sizeof(tempStr));
					sprintf(final,"%d",val1);
					// pop(stack,&stTop);
					push(stack,&stTop,':');
					for (int k = strlen(final)-1; k >= 0; k--){
						push(stack,&stTop,final[k]);
					}
					push(stack,&stTop,':');
				}
			}
			else {
				// never reached
			}
		}
	}
	tempStr = "";
	pop(stack,&stTop);
	while(peek(stack,&stTop) != ':'){
		tempStr = chAppend(tempStr,pop(stack,&stTop));
	}
	pop(stack,&stTop);
	return tempStr;
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
