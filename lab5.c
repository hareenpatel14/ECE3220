#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// creating new variables
double datanew[2000];
int data[2000];
char new[100];
int size;
double mean;
int filenumber;
int centerflag = 0;
int normflag = 0;
	
//delcaring function prototypes
void load_data(int);
int size;
void offset_scale(int);
double calculatemean(int data[], int size);
int max(int data[],int size);



int main(int argc , char **argv)
{
	// initilizing the flags for each arguement
   int fileflag = 0;
    int offsetflag = 0;
    int scaleflag = 0;
    int statflag = 0;
   
    int renameflag = 0;
    int helpflag = 0;
    
    int i=1;
    double offset;
    double scaler;
    int choice;
   char newName[100];
    
    
    // for loop to keep checking each arguement in command line and storing it in respective variable
    for (i = 1; i < argc;)
    {
        if (strcmp(argv[i], "-n") == 0)
        {	// command line input file number
            if (argc - i <= 1 || atoi(argv[i + 1]) == 0)
            {	// checks number after -n
                printf("\n%s needs a modifier after it\n", argv[i]);
                i++;
                continue;
            }
            
            filenumber = atoi(argv[i + 1]);
            fileflag = 1;
            i += 2;
        }
        else if (strcmp(argv[i], "-o") == 0)
        {		// command line offset input
            if (argc - i <= 1 || atoi(argv[i + 1]) == 0)
            { // checks for an offset value after -o
                printf("\n%s needs a modifier after it\n", argv[i]);
                i++;
                continue;
            }
            offset = strtod(argv[i + 1], NULL);
            offsetflag = 1;
            i += 2;
        }
        else if (strcmp(argv[i], "-s") == 0)
        {		// command line scale factor input
            if (argc - i <= 1 || atoi(argv[i + 1]) == 0)
            { // check for a scaler factor input after -s
                printf("\n%s needs a modifier after it\n", argv[i]);
                i++;
                continue;
            }
            scaler = strtod(argv[i + 1], NULL);
            scaleflag = 1;
            i += 2;
        }
        else if (strcmp(argv[i], "-S") == 0)
        {		// get statistics
            statflag = 1;
            i++;
        }


    else if (strcmp(argv[i], "-C") == 0)
    {		// center data
        centerflag = 1;
        i++;
    }
    else if (strcmp(argv[i], "-N") == 0)
    {		// normalize signal
        normflag = 1;
        i++;
    }
    else if (strcmp(argv[i], "-r") == 0)
    {		// rename files
        if (argc - i <= 1 || argv[i + 1][0] == '-')
        {	// make sure there is a new filename after -r
            printf("\n%s needs a modifier after it\n", argv[i]);
            i++;
            continue;
        }
        strcpy(newName, argv[i + 1]);
        renameflag = 1;
        i += 2;
    }
    else if (strcmp(argv[i], "-h") == 0)
    {		// display help
        helpflag = 1;
        i++;
    }
    else
    {	// base case to catch misc arguments.
        printf("\n%s is an invalid argument. Use -h to display a list of arguments\n", argv[i]);
        i++;
        continue;
    }
}
    
    
    if (helpflag == 1) {	// show help when -h or an error in the input occors
        printf("\n\nProgram arguments\n");
        printf("-n This will be an integer value that is greater than zero\n");
        printf("-o this is will a double value that will be used to offset that data\n");
        printf("-s This will be used to scale the data, also a double value.\n");
        printf("-S This will be used to show the stats of the input data\n");
        printf("-C This is used to center the signal at 0\n");
        printf("-N This will be used to normalize the signal between 0 and 1\n");
        printf("-r This will be a string that will rename the input file.\n");
        printf("-h This is used to show help menu\n");
        
        return 1;
    }
    
	load_data(filenumber);
	double mean_val = calculatemean(data,size);
	int max1 = max(data,size);
	 sprintf(new,"Statistic_data_%d.txt",filenumber);
	 	FILE* offset1 = fopen(new,"w");
	 	fprintf(offset1, "%.2f %d\n",mean_val, max1);
	
	
}

void  load_data(int filenum) // opens the file and then loads the data into an array/ other variables
{

	char str[80];
	int limit,i=1;
	// setting name of file to load from
	sprintf(str, "A%d.txt",filenum);

	FILE *file;
	file = fopen(str,"r");

	fscanf(file, "%d %d",&size, &limit);
	//printf("this size of the file is %d and the limit is %d\n", size, limit);

	for (i=1;i<size+1;i++)
	{
		fscanf(file,"%d",&data[i]);// scanfing the numbers from file to array
		printf("this is the nubmer %d\n", data[i]);
	}
}

void offset_scale(int size)// adds the raw data with offset/scales selected by user
{
	int option,i;
	double factor;
	printf("Would you like to offset(1), scale(2) or keep original numbers(3)?\n");
	scanf("%d", &option);

// selecting which case that you are doing
	switch(option)
	{
	case 1:
		printf("You chose offset. Choose a number to offset data by: \n");
		scanf("%lf", &factor);
		
		
		sprintf(new,"Offset_data_%d.txt",filenumber);
		FILE* offset1 = fopen(new,"w");
		fprintf(offset1, "%d %.2f\n",size, factor);
		for (i=1; i<size+1; i++)
		{
			datanew[i] = data[i];
			datanew[i] += factor;
			//printf("this is the new number %d\n", data[i]);
			fprintf(offset1,"%.4lf\n",datanew[i]);

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

double calculatemean(int data[],int size) // finds the mean of the data
{
	double answer=0,mean1=0;
	int i=1,j=1;
	double buffer=0;
	printf("this is size %d\n",size);
	for(i=1;i<size+1;i++)// finding the mean of the data
	{
		answer += (double) data[i];
		mean1 = answer/size;
	}
	printf("This is the mean of the raw data: %.2f\n", mean1);
if (centerflag==1)
{
	sprintf(new,"Centered_data_%d.txt",filenumber);
	FILE* centered = fopen(new,"w");
	fprintf(centered,"%d %.2f\n",size, mean1);

	for(j=1;j<size+1;j++)//centralizing the data in the array
	{
		buffer = (double)data[j]-mean1;
		fprintf(centered, "%.2f\n",buffer);
	}
	}
	return mean1;
}

int max(int data[],int size) // finds max of the data
{
	int i=0;
	int max=0;
	double buffer=0;
	int j=0;
	for(i=1;i<size+1;i++)
	{
	if(data[i]>max)// cheing against the number to see if it is the bigger max
		max= data[i];
	}
	printf("this is the max value %d\n",max);
if (normflag==1)
{
	sprintf(new,"Normal_data_%d.txt",filenumber);
	FILE* normal = fopen(new,"w");
	fprintf(normal,"%d %d\n",size, max);

	for(j=1;j<size+1;j++)// normalizing the data in the array
	{
	buffer = (double)data[j]/max;
	fprintf(normal, "%.2f\n",buffer);
	}
}
	return max;
}