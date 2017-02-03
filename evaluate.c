#include<iostream.h>
#include<stdio.h>
#include<math.h>


int main(int argc, char *argv[]){
	if (argc != 2){
		std::cout << "error: no input file" << std::endl;
		return -1;
	}
	FILE *fp = fopen(argv[1], "r");
	int ch = getc(fp);
	while (ch != EOF) // BEGIN FILE READ
	{
		
	}	
}