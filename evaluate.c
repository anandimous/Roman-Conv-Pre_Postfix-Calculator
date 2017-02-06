#include<stdio.h>
#include<math.h>

int main(int argc, char *argv[]){
	//check cmd line args
	if (argc != 2){
		std::cout << "error: no input file" << std::endl;
		return -1;
	}

	//file validation
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) {
		perror("Error opening file: File DNE!");
		return(-1);
	}

	//file input stream
	int ch = getc(fp);
	while (ch != EOF) // BEGIN FILE READ
	{

	}
}
