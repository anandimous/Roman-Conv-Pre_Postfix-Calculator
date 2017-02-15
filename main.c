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
		else if(strchr(matchesOp,str[i]) != NULL) {
			if(stack.isEmpty()) { stack.push(str[i]); } //push op if empty stack
			else {
				while(!stack.isEmpty() && getPrec(stack.peek()) > getPrec(str[i])) {
					//checking precedence of chars in input string w/t the stack and append popped char to output string when condition is met
					if(getPrec(str[i]) < getPrec(stack.peek())) { strncat(post, stack.pop(), 1); }
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
	int ch;
	int temp;
	char* tempStr;
	char* inFile;
	char* outFile;
	FILE* fp;
	FILE* fo;
	char* exp = "";
	char* finalExp = "";
	char* roman_str = "";
	const char* matchesRoman = "IiVvXxLlCcDdMm";
	const char* matchesSpace = " ";
	const char* matchesOp = "+-*/()";
	const char* matchesCalc = "+-*/";

	//check cmd line args
	if (argc != 2){
		std::cout << "error: incorrect number of arguments" << std::endl;
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
			break;
		}
	}
	
	// Open file to input stream fp
	fp = fopen(inFile, "r");
	if(fp == NULL) {
		perror("Error opening file: File DNE!");
		return -1;
	}
	
	// Open file to output stream fp
	fo = fopen(outFile, "w");

	//file input stream, saves expression as char* to exp
	ch = getc(fp);
	while (ch != EOF) // BEGIN FILE READ
	{
		exp = strAppend(exp,(char*) ch);
		ch = getc(fp);
	}

	fp.close();

	// convert string with roman nums to string with only integers

	if (strstr(exp,matchesRoman) != NULL){
		bool isOp = false;
		for (int i = 0; i < strlen(exp)+1; i++){

			if (isdigit(exp[i])){				// Append Digit -> finalExp
				strcat(finalExp,exp[i]);
			}

			else if (strchr(matchesSpace,exp[i])){	// Append ' ' -> finalExp
				if (strlen(roman_str) > 0){

				}
				else {
					strcat(finalExp,exp[i]);
				}
			}

			else if (strchr(matchesRoman,exp[i]) != NULL) {  // Append roman num -> roman_str
				
				isOp = false;
				strcat(roman_str,exp[i]);
			}
			else if (strchr(matchesOp,exp[i]) != NULL) {
				if (!isOp && strlen(roman_str) > 0) {
					temp = finalConvert(roman_to_arabic(roman_str));
					strAppend(finalExp,itoa(temp,tempStr,10));
					roman_str = "";
				}
				isOp = true;
				strcat(finalExp,exp[i]);
			}
			else if (exp[i] == '\0' && strlen(roman_str) > 0){
				temp = finalConvert(roman_to_arabic(roman_str));
				strAppend(finalExp,itoa(temp,tempStr,10));
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
	//fputs("", fp);                   For value int & \n
	
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

char* calc(char* str){
	struct node* stack;
	stack.init();

	struct node* opStack;
	opStack.init();

	for(int i=0; i<strlen(finalExp); i++) {
		if(isdigit(finalExp[i])) {
			stack.push(finalExp[i]);
		}

		else if (finalExp[i] == '(') {		
			opStack.push(finalExp[i]);
		}

		else if (finalExp[i] == ')') {
			while (opStack.peek() != '('){
				char op = opStack.pop();
				int val2 = stack.pop();
				int val1 = stack.pop();	

				if (op == '+'){
					val1 = val1 + val2;
					stack.push(val1 + '0');
				}
				else if (op == '-'){
					val1 = val1 - val2;
					stack.push(val1 + '0');
				} 
				else if (op == '*'){
					val1 = val1 * val2;
					stack.push(val1 + '0');
				} 
				else if (op == '/'){
					val1 = val1 / val2;
					stack.push(val1 + '0');
				} 		
			}
			opStack.pop();
		}

		else if (strchr(matchesCalc,finalExp[i])){
			while (!opStack.isEmpty() && getPrec(opStack.peek()) >= getPrec(finalExp[i])){
				char op = opStack.pop();
				int val2 = stack.pop();
				int val1 = stack.pop();
				if (op == '+'){
					val1 = val1 + val2;
					stack.push(val1 + '0');
				}
				else if (op == '-'){
					val1 = val1 - val2;
					stack.push(val1 + '0');
				} 
				else if (op == '*'){
					val1 = val1 * val2;
					stack.push(val1 + '0');
				} 
				else if (op == '/'){
					val1 = val1 / val2;
					stack.push(val1 + '0');
				} 

				opStack.push(finalExp[i]);	
			}
		}

	}

	while(!opStack.isEmpty()) {
		char op = opStack.pop();
		int val2 = stack.pop();
		int val1 = stack.pop();
		if (op == '+'){
			val1 = val1 + val2;
			stack.push(val1 + '0');
		}
		else if (op == '-'){
			val1 = val1 - val2;
			stack.push(val1 + '0');
		} 
		else if (op == '*'){
			val1 = val1 * val2;
			stack.push(val1 + '0');
		} 
		else if (op == '/'){
			val1 = val1 / val2;
			stack.push(val1 + '0');
		} 

	}
	return stack.pop();

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
