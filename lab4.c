/*
 ============================================================================
 Name        : lab4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int data[2000];
int filenumber;
double datanew[2000];
int load_data();
void offset();
char new[80];

double mean(int data[],int size);
int max(int data[],int size);

int main(void) // main function to call all of the other functions
{
	//int filearray[];
	 int size = load_data();
	 offset(size);
	 double mean1 = mean(data,size);
	 int max1 = max(data,size);
	 sprintf(new,"Statistic_data_%d.txt",filenumber);
	 	FILE* offset = fopen(new,"w");
	 	fprintf(offset, "%.2f %d\n",mean1, max1);

	return 0;
}

int  load_data() // opens the file and then loads the data into an array/ other variables
{

	char str[80];
	int size, limit,i=1;

	//User selects file and it is put in to str
	printf("please select a file number from 1-14\n");
	scanf("%d", &filenumber);
	sprintf(str, "A%d.txt",filenumber);

	FILE *file;
	file = fopen(str,"r");

	fscanf(file, "%d %d",&size, &limit);
	//printf("this size of the file is %d and the limit is %d\n", size, limit);

	for (i=1;i<size+1;i++)
	{
		fscanf(file,"%d",&data[i]);
		//printf("this is the nubmer %d\n", data[i]);
	}
	return size;
}

void offset(int size)// adds the raw data with offset/scales selected by user
{
	int option,i;
	double factor;
	printf("Would you like to offset(1), scale(2) or keep original numbers(3)?\n");
	scanf("%d", &option);


	switch(option)
	{
	case 1:
		printf("You chose offset. Choose a number to offset data by: \n");
		scanf("%lf", &factor);
		sprintf(new,"Offset_data_%d.txt",filenumber);
		FILE* offset = fopen(new,"w");
		fprintf(offset, "%d %.2f\n",size, factor);
		for (i=1; i<size+1; i++)
		{
			datanew[i] = data[i];
			datanew[i] += factor;
			//printf("this is the new number %d\n", data[i]);
			fprintf(offset,"%.4lf\n",datanew[i]);

		}
		break;


	case 2:

		printf("You chose scale. Choose a number to scale data by: \n");
		scanf("%lf", &factor);
		sprintf(new,"Scaled_data_%d.txt",filenumber);
		FILE* scaled = fopen(new,"w");
		fprintf(scaled,"%d %.2lf\n", size, factor);
		for (i=1; i<size+1; i++)
			{

				datanew[i] = data[i];
				datanew[i] *= factor;
				//printf("this is the new number %d\n", data[i]);
				fprintf(scaled,"%.4lf\n",datanew[i]);


			}
		break;

	case 3:
		printf("You decided to keep the same numbers!\n");
		break;
	}
}

double mean(int data[],int size) // finds the mean of the data
{
	double answer=0,mean=0;
	int i=1,j=1;
	double buffer=0;
	printf("this is size %d\n",size);
	for(i=1;i<size+1;i++)
	{
		answer += (double) data[i];
		mean = answer/size;
	}
	printf("This is the mean of the raw data: %.2f\n", mean);

	sprintf(new,"Centered_data_%d.txt",filenumber);
	FILE* centered = fopen(new,"w");
	fprintf(centered,"%d %.2f\n",size, mean);

	for(j=1;j<size+1;j++)
	{
		buffer = (double)data[j]-mean;
		fprintf(centered, "%.2f\n",buffer);
	}
	return mean;
}

int max(int data[],int size) // finds max of the data
{
	int i=0;
	int max=0;
	double buffer=0;
	int j=0;
	for(i=1;i<size+1;i++)
	{
	if(data[i]>max)
		max= data[i];
	}
	printf("this is the max value %d\n",max);

	sprintf(new,"Normal_data_%d.txt",filenumber);
	FILE* normal = fopen(new,"w");
	fprintf(normal,"%d %d\n",size, max);

	for(j=1;j<size+1;j++)
	{
	buffer = (double)data[j]/max;
	fprintf(normal, "%.2f\n",buffer);
	}

	return max;
}
