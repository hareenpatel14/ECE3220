//  Lab7
//  Created by Hareen Patel on 10/26/16.


#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
using namespace std;

class Signal
{
    private:
        int len;
        int max;
        int avg;
        vector<double> data;
    void findavg()
        {
            int i;
            for (i= 0; i<len; i++)
            {
                avg = avg + data[i];
                
            }
			avg = avg/len;
            
        }
    void findmax()
        {
            int i;
            for (i=0;i<len;i++)
            {
                if(data[i]>max)
                {
                    max = data[i];
                    
                }
            }
        }
    
    public:
        void Scale( double scale );
        void Offset( double offset );
        void Stat(void);
        void Center( double mean );
        void Normalize( double max );
        void Sig_Info(void);
        void Save_File( const char* Filename );
        void Operations( Signal );
        Signal (void);
    void operator*(double Scale_factor);
    void operator+(double Offset_factor);
    Signal ( int num );
        Signal ( const char* Filename );
        ~Signal(void);
    
};

Signal::Signal ( int num )
{
    int i;
    char *Filename = new char[60];
    
    sprintf(Filename, "A%d.txt", num);
    FILE *fptr = fopen(Filename, "r");
    
    fscanf( fptr , "%d %d" , &len , &max);
    //////data = new double[len];
    
    vector<double> DataStart = data;
    
    while(i < len)
    {
        int temp;
        fscanf(fptr,"%d\n",&temp);
      //  data[i] = temp;
        data.push_back(temp);
        //data++;
        i++;
    }
    data = DataStart;
    findavg();
    
    fclose(fptr);
    delete[] Filename;
    //Fills out Signal with data from number files	
}
//default constructor
Signal::Signal ()
{
    int i;
    char *Filename = new char[60];
    
    sprintf(Filename, "A1.txt");
    FILE *fptr = fopen(Filename, "r");
    
    fscanf( fptr , "%d %d" , &len , &max);
    avg = 0;
    ////data = new double[len];
    
    vector<double> buffer;
    while(i < len)
    {
        int buf;
        fscanf(fptr,"%d\n",&buf);
       // data[i] = buf;
        data.push_back(buf);
        //data++;
        i++;
    }
    data = buffer;
    findavg();
    
    fclose(fptr);
    delete[] Filename;
    // Fills out Signal with default data 
}
//parametric constructor
Signal::Signal ( const char* Filename)
{
    int i;
    
    char filebuffer[60];
    sprintf(filebuffer,"%s",Filename);
    FILE *fp = fopen(filebuffer, "r");
    
    fscanf( fp , "%d %d" , &len , &max);
    //////data = new double[len];
    
    vector<double> Datastart;
    while(i < len)
    {
        int temp;
        fscanf(fp,"%d\n",&temp);
        //data[i] = temp;
        data.push_back(temp);
       // data++;
        i++;
    }
    data = Datastart;
    findavg();
    
    fclose(fp);
    delete[] Filename;
    //Fills out Signal with data from user inputted file	
}
//destructor, causing seg faults for some reason
Signal::~Signal()
{
    //delete[] data;
}

void Signal::Offset( double offset )
{
    operator+(offset);
}
void Signal::operator+(double Offset_factor)
{
    int i;
    for(i=0;i<len;i++)
    {
        data[i] = data[i] + Offset_factor;
    }
}

void Signal::Scale( double scale )
{
    operator*(scale);
}

void Signal::operator*(double scale)
{
    int i;
    for(i=0;i<len;i++)
    {
        data[i] = data[i] * scale;
    }
}

void Signal::Stat( )
{
    findavg();
    findmax();
    //Finds Average and Max of data
}

void Signal::Normalize( double max )
{
    int i;
    for(i = 0; i < len; i++)
    {
        data[i] = data[i] / max;
    }
    // normalizes the array
}

void Signal::Center( double mean )
{
    int i;
    double buffer;
    findavg();
    for(i = 0; i < len; i++)
    {
        cout << " this is it : "<< data[i]<<endl;
        //buffer = data[i] - mean;
    //   data[i]=buffer;
       // data.push_back();
    }
    // Centers the array
}

void Signal::Sig_Info( )
{
    cout << "Length: " << Signal::len << endl;
    cout << "Max: " << Signal::max << endl;
    cout << "Average: " << Signal::avg << endl;
    // prints some info from the signal
}

void Signal::Save_File( const char* Filename)
{
    int i = 1;
	char fileString[50];
    
    vector<double> start;
    sprintf(fileString,"%s",Filename);
    FILE *fp = fopen(fileString, "w");
    
    fscanf( fp , "%d %d\n" , &len , &max);
    
    while(i <= len)
    {
        fprintf(fp,"%.2lf\n\n",data[i]);
        //data++;
        i++;
    }
    data = start;
    
    fclose(fp);
    //Saves the updated file under a new name
}
//this function handles the user's menu choice and performs correct operation
void Signal::Operations( Signal Sig )
{
    int choice =0;
    double Scale_factor , Offset_factor;
    char new_name[50];
    while( choice != 8 )
	{
        //ask user for operation choice
        cout<<"Select an Option: \n1. Scale \n2. Offset \n3. Statistics \n4. Center \n5. Normalize \n6. Info \n7. Save \n8. Exit \nPlease Choose Operation:  "<<endl;
        cin>>choice;
        
        if( choice < 1 || choice > 8)
        {
			//error check
            cout<<"Invalid choice, please try again. "<<endl;
        }
        // scale, write to file
        if( choice == 1 )
        {
            cout<<"Enter a scaling factor: "<<endl;
            cin>>Scale_factor;
            
            cout<<"Scaling"<<endl;
            Sig.Scale( Scale_factor );
            
        }
		//offset, write to file
        if( choice == 2 )
        {
            cout<<"Enter a number to offset data by: "<<endl;
            cin>>Offset_factor;
            
            cout<<"Offsetting"<<endl;
            Sig.Offset( Offset_factor );
            
        }
		//find mean and max, print to file
        if( choice == 3 )
        {
            cout<<"Printing Stats"<<endl;
            Sig.Stat();
        }
		//center array, print to file
        if( choice == 4)
        {
            cout<<"Centering"<<endl;
            Sig.Center( Sig.avg );
        }
		// normalize, print to file
        if( choice == 5)
        {
            cout<<"Normalizing"<<endl;
            Sig.Normalize( Sig.max );
        }
		//print info
        if( choice == 6)
        {
            cout<<"Printing Info"<<endl;
            Sig.Sig_Info();
        }
		//save file
        if( choice == 7)
        {
            cout<<"Enter new file name:"<<endl;
            cin>>new_name;
            cout<<"Saving"<<endl;
            
            Sig.Save_File(new_name);
        }
		//exit the program
        if( choice == 8)
        {
            cout <<"Exiting"<< endl;
        }
        
    }
}

int main(int argc , char **argv)
{
    int num = 0;
    int def_flag = 0;
    int file_flag = 0;
    int num_flag = 0;
    int i =0;
    int name = 0;
    char *Filename = new char[100];
    
    //handles command line
    if( i < argc )
    {
        
        if( strcmp( "-n" , argv[i]) == 0 )
        {
            i++;
            
            if( i >= (argc-1) )
            {
                num = 0;
            }
            else
            {
                num = atoi(argv[i]);
            }	
            num_flag = 1;
        }
        
        if(strcmp( "-f" , argv[i]) == 0 )
        { 
            file_flag = 1;
            i++;
            Filename = argv[(i)];
        }
        
        i++;
    }
    
    //if there are no command line arguments, do this
    if(num == 0 && file_flag == 0)
    { 
        cout<<"Please enter a filename or choose default: \n1. Enter Filename \n2. Default "<<endl; 
        cin>>name;
        if( name == 1)
        {
            cout<<"Enter name of file: "<<endl;
            cin>>Filename;
            
            file_flag = 1;
        }
        else if( name == 2)
        { 
            def_flag = 1;
        }
        //Gets filename or uses default
    }
    
    if( def_flag == 1 )
    {
        Signal Sig;
        Sig.Operations(Sig);
        // makes default signal	
    }
    else if( num_flag == 1 )
    {
        Signal Sig ( num ); 
        Sig.Operations(Sig);
        //makes num file signal	
    }
    else if( file_flag == 1 )
    { 
        Signal Sig ( Filename ); 
        Sig.Operations(Sig);
        //makes user file signal	
    }
    
    return 0;
}

