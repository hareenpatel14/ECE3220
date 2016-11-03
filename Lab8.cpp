#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
//base class
class Inputmessage {
protected:
    string message;//holds input
    int length;//holds length of input
    
public:
    Inputmessage(void);
    Inputmessage(string);
    ~Inputmessage(void);
    void printInfo(void);
};
//Derived class with base class "Inputmessage"
class morseCodeMessage : public Inputmessage{
public:
    string *translatedmsg;
    string morsecodemsg;
    int index;
    morseCodeMessage(void);
    ~morseCodeMessage(void);
    morseCodeMessage(string);
    void translate(void);
    void printInfo(void);
};
//class used to deal with stack
class messageStack
{
public:
    Inputmessage *StackPtr[10];
    Inputmessage *StackHead;
    messageStack(void);
    //~messageStack(void);
    void push(Inputmessage);
    void push(morseCodeMessage);
    void pop(void);
    void printStack();
    //int stacktop();
    int objectnum;
    int counter;
};

//parametric constructor
Inputmessage::Inputmessage(string input)
{
    message = input; // put the input message into message string
    
}
//default constructor
Inputmessage::Inputmessage(void)
{
    cout<<"Enter a word you would like to be translated:"<<endl; // asking user for input
    cin>>message; // reading input into message string
    length = message.length(); // finding the length
}
//destructor
Inputmessage::~Inputmessage(void)
{
    // nothing to get rid of
}

void Inputmessage::printInfo(void)
{
    cout<<"Input message: "<<message<<endl;
}
/*
-------------------MorseCodeMessage methods----------------
*/
morseCodeMessage::morseCodeMessage(void) : Inputmessage()
{
    translatedmsg = new string[length];
    translate();
}// default constructor, calls the translate method

morseCodeMessage::morseCodeMessage( string input ) : Inputmessage( input )
{
    translatedmsg = new string[ length ];
    translate( );
}// constructs morse code with input, and calls translate

morseCodeMessage::~morseCodeMessage( void )
{
    delete[] translatedmsg;
}// destructor for morse code


void morseCodeMessage::printInfo(void)
{
    cout<<"Before translation: "<<message<<endl;
    cout<<"After translation: "<<morsecodemsg<<endl;
}// prints both normal message and morse code
//this is where the translating happens.
void morseCodeMessage::translate(void)
{
    int i, j, k, upper;
    string space = " ";
    string letters = "abcdefghijklmnopqrstuvwxyz123456789";
    string morse[36] =  {
        ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",
        ".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..",    ".----","..---",
        "...--","....-",".....","-....","--...","---..","----.","-----" };
    
    for( i=0; i < length; i++)
    {
        upper = isupper(message[i]);//checks if letter is uppercase
        if( upper == 1 )//if letter is uppercase, make it lowercase
        {
            message[i] = (char)tolower(message[i]);
        }
    }
    
    for( j=0; j < length; j++)//find correct letter/number
    {
        index = letters.find(message[j]);
        translatedmsg[j] = morse[index];
    }
    
    for( k=0; k < length; k++)
    {
        morsecodemsg.append(translatedmsg[k]);
        morsecodemsg.append(space);
    }
    
}
//default constructor
messageStack::messageStack()
{
	counter=0;
	StackHead = NULL;
}
//push non-translated message on to stack
void messageStack::push(Inputmessage input)
{
	if(StackHead == NULL)
	{
		StackHead = &input;
	}
	if(objectnum >= 10)
		return;
	else
	{
		StackPtr[counter] = new Inputmessage(input);
		counter++;
	}
}
//push Morse Code message on to stack
void messageStack::push(morseCodeMessage input)
{
	if(StackHead == NULL)
	{
		StackHead = &input;
	}
	if(objectnum >= 10)
	{
		return;
	}
	else
	{
		StackPtr[counter] = new morseCodeMessage(input);
		counter++;
	}
}
//popping method
void messageStack::pop()
{
	if(counter == 0)
	{
		cout << "Stack is empty" << endl;
		return;
	}
	delete StackPtr[counter-1];
	counter--;
}
//method to print stack values
void messageStack::printStack()
{
	int i = 0;
	cout << "\nThis is the stack:\n" << endl;
	while (i < counter)
	{
		cout << "Stack position " << i+1 << ":" << endl;
		StackPtr[i]->printInfo();
		i++;
	}
}


int main(int argc, const char * argv[]) {
    // insert code here...
	int buffer =1;
	while (buffer != 0)
	{
    Inputmessage msg;
	morseCodeMessage MCmsg;
	
	msg.printInfo();
	
	MCmsg.printInfo();
	
	cout << "Press 0 to go to stack or 1 to translate" << endl;
	cin >> buffer;
	}
	
	int choice = 5;
	int Stackflg;
	messageStack msg1;
	
	while (choice != 0)
	{
		cout << "\n0: Exit\n1:PUSH message \n2:POP a message\n3: DISPLAY the stack" << endl;
		cin >> choice;
		switch(choice)
		{
			case 0:
				return 0;
				break;
			case 1:
				cout << "1. Normal message \n2. Morse Code" << endl;
				cin >> Stackflg;
				if(Stackflg == 1) 
				{	
					Inputmessage buffer;
					msg1.push(buffer);
				}
				else 
				{
					morseCodeMessage buffer;
					msg1.push(buffer);
				}
				break;
			case 2:
				msg1.pop();
				break;
			case 3: 
				msg1.printStack();
				break;
			default:
				break;
		}
	}
	return 0;
	
}
