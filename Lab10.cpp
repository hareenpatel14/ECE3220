#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

//string letters = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s',
   // 't','u','v','w','x','y','z'};



string morseCode[] = {"._", "_...", "_._.", "_..", ".", ".._.", "__.", "....", "..", ".___",
    "_._", "._..", "__", "_.", "___", ".__.", "__._", "._.", "...", "_",
    ".._", "..._", ".__", "_.._", "_.__", "__.."};







class Message
{
public:

    void printmessage(void);
    Message(); // this is the constructor
    Message(string buffer);
    ~Message();
protected:
    string translatemsg;
};

class MorseCodeMessage:Message
{
public:
    MorseCodeMessage();
    ~MorseCodeMessage();
    void TranslateFunction();
    void printmessage(void);
protected:
    string *FinalTranslate;

};

class Messagestack
{
public:
    Messagestack();
    ~Messagestack();
    void printstack(void);
    void popstack();
    void pushstack(string *stackmessage);
    void askmessage();
protected:
    string *stackmessage;
    int counter;
    //stack <string> mystack;
    string *stack[10];//stack size is 10
};

class lights:MorseCodeMessage
{
public:
    void showlights(char character);
    char parsemorse(string);
    lights();
    ~lights();
protected:
    char character;
};

lights::lights()
{
    character = NULL;
}

lights::~lights()
{

}

char lights::parsemorse(string)
{

/*int i, j;
char character1;

	for(i=0;i<translatemsg.length();i++)
	    {
	        for(j=0;j<FinalTranslate[i].length();j++)
	        {
	            cout<<"this is the character: "<<FinalTranslate[i][j]<<endl;
	            character1 = FinalTranslate[i][j];
	            showlights(character1)

	        }
	    }


*/



    return character;
}

void lights::showlights(char character)
{
    int fd;		// for the file descriptor of the special file we need to open.
    unsigned long *BasePtr;		// base pointer, for the beginning of the memory page (mmap)
    unsigned long *PBDR, *PBDDR;	// pointers for port B DR/DDR

    fd = open("/dev/mem", O_RDWR|O_SYNC);	// open the special file /dem/mem
    if(fd == -1){
        printf("\n error\n");
        return;  // failed open
    }

    // We need to map Address 0x80840000 (beginning of the page)
    BasePtr = (unsigned long*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0x80840000);
    if(BasePtr == MAP_FAILED){
        printf("\n Unable to map memory space \n");
        return;
    }  // failed mmap

    // To access other registers in the page, we need to offset the base pointer to reach the
    // corresponding addresses. Those can be found in the board's manual.
    PBDR = BasePtr + 1;		// Address of port B DR is 0x80840004
    PBDDR = BasePtr + 5;	// Address of port B DDR is 0x80840014

    *PBDDR |= 0xE0;			// configures port B7 as output (Green LED)
    *PBDDR &= 0xFFFFFFFE;	// configures port B0 as input (first push button). You could use: &= ~0x01





    if(character == '_')//yellow find out what number to change 80 to
    {
    	sleep(1);
        *PBDR |= 0x40;	// ON: write a 1 to port B0. Mask all other bits.
        sleep(1);	// How can you sleep for less than a second?
        *PBDR &= ~0x40;	// OFF: write a 0 to port B0. Mask all other bits.

        cout<<"this is yellow"<<endl;
    }

    if (character == '.') //red  find out what number to change 80 to
    {
    	sleep(1);
        *PBDR |= 0x20;	// ON: write a 1 to port B0. Mask all other bits.
        sleep(1);	// How can you sleep for less than a second?
        *PBDR &= ~0x20;	// OFF: write a 0 to port B0. Mask all other bits.

        cout<<"this is red"<<endl;
    }

    if (character == 'z')//green
    {
    	sleep(1);
    	*PBDR |= 0x80;	// ON: write a 1 to port B0. Mask all other bits.
        sleep(1);	// How can you sleep for less than a second?
        *PBDR &= ~0x80;	// OFF: write a 0 to port B0. Mask all other bits.

        cout<<"this is green"<<endl;
    }
}




Messagestack::Messagestack()
{
    stackmessage = new string;

    counter = 0;
    //nothing to allocate
}

Messagestack::~Messagestack()
{
    delete [] stackmessage;
    cout<< "destructing "<<endl;

    //nothing to delete
}

void Messagestack::askmessage()
{
    int choice;
    string input;
    cout<<"Would you like to push(1) a message, pop(2) a message, or print the stack(3)? Press(0) to exit"<<endl;
    cin >> choice;
    while(choice!=0)
    {
        if (choice == 1)
        {
            cout<<"Please give a message to push on to stack"<<endl;
            cin >> input;
           // cout<<"hi"<<endl;
            *stackmessage = input;

         //   cout<<"this is the address of input"<<&input<<endl;
         //   cout<<"this is the value of stackmessage"<<stackmessage<<endl;

          //  cout<<"this is input: "<< input<<endl;
          //  cout<<"This is stack message: "<<*stackmessage<<endl;

            pushstack(stackmessage);
            //cout << "This is the stack: "<<endl<< stack.top()<<endl;
        }

        if (choice == 2)
        {
            cout << "You chose to pop the message!"<< endl;
            popstack();
        }
        if(choice == 3)
            printstack();
        cout<<"Would you like to push(1) a message, pop(2) a message, or print the stack(3)? Press(0) to exit"<<endl;
        cin >> choice;
    }
    exit(EXIT_SUCCESS);
}

void Messagestack::popstack()
{
    if(counter == 0)
        cout<<"There is nothing to pop"<<endl;

    else{
        ;
        counter--;
    }

}

void Messagestack::pushstack(string *stackmessage)
{
    cout<<"hi"<<endl;
    if(counter == 10)
        cout<<"Stack is full (maximum of 10 objects)"<<endl;

    else
    {

        cout<<"this is the message"<<*stackmessage<<endl;
        stack[counter] = new string;

        *stack[counter] = *stackmessage;//set index to message input by user


        counter++;
    }

}
void Messagestack::printstack(void)
{
    cout<<"...Printing stack..."<<endl;

    for (int i=0;i<counter; i++)
    {
        cout<<"this is the counter"<<counter<<endl;
        cout<<"Element "<<(i+1)<<":"<<endl;
        cout<< *stack[i] << endl;

    }
}
MorseCodeMessage::MorseCodeMessage()
{
    cout << "Please give a message to translate:" << endl;
    cin >> translatemsg;

    FinalTranslate = new string[translatemsg.length()];
    TranslateFunction();
}

MorseCodeMessage::~MorseCodeMessage()
{
    //nothing to make go bye bye, jk free finaltranslate
	cout << "MorseCodeMessage destructor"<<endl;
    delete [] FinalTranslate;
}


void MorseCodeMessage::printmessage(void)

{
	lights parse;

    cout<<"This is the original message:"<<translatemsg<<endl;
    cout<<"This is the translated message: ";
    for(int i=0;i<translatemsg.length();i++)
    {
        cout<<""<<FinalTranslate[i]<<"  ";
    }
    cout<<endl;



    cout<<"this is the start of something new"<<endl<<endl<<endl;



    int i,j;
    char character1;
    int buffer=0;
   //cout<<"thisis the length of finaltranslate: "<< FinalTranslate[0].length()<<endl; // finaltranslate is only getting the length of the first one and nothing else
    //cout<<"thisis the length of finaltranslate: "<< FinalTranslate[i].length()<<endl; // prints out the length is 0
    //cout<< "this is the length of the whole thing:"<< FinalTranslate->length()<<endl;

    for(i=0;i<translatemsg.length();i++)
    {

        for(j=0;j<FinalTranslate[i].length();j++)
        {
            cout<<"this is the character: "<<FinalTranslate[i][j]<<endl;
            character1 = FinalTranslate[i][j];
            parse.showlights(character1);

        }
    }

    parse.showlights('z');

}

void MorseCodeMessage::TranslateFunction()
{
	string letters("abcdefghijklmnopqrstuvwxyz");

    int i;
    int j;

    for(i=0;i<translatemsg.length();i++)
    {
        for(j=0;j<24;j++)
        {

            if (translatemsg[i] == letters[j])
            {
                FinalTranslate[i] = morseCode[j];
            }

        }
    }

}

Message::Message()
{
    /*we moved the cout for original message from here to constructor of MorseCodeMessage, if we kept it here the message was being asked two different times, now it will only ask user for 1 word.*/
}

Message::~Message()
{
    // no variables that need memory allocation
}

Message::Message(string buffer)
{
    translatemsg = buffer;
}

void Message::printmessage(void)
{
    //cout<<"this is the original message:"<<translatemsg<<endl;
}

int main(int argc, const char * argv[]) {

    Message message1;
    MorseCodeMessage morse1;
    message1.printmessage();
    morse1.printmessage();
    Messagestack stack;
    stack.askmessage();

    lights parse;


    return 0;
}
