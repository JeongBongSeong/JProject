#include<iostream>
#include<stdio.h>

int main()
{
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp,"test.txt","rt");
	char buffer[255];
	int a = 0;
	float b = 0;
	float c = 0;

	fgets(buffer, 255, fp);
	sscanf_s(buffer, "%d %f %f", &a, &b, &c);

}