#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

class hang 
{
    string supersecretword;
    int maxtries;
    const string wordlist="words.txt";
    vector<bool> guessed = getRandomWord();
    public:
        hang()
        {
            maxtries=7;
        }
        vector<bool> getRandomWord();
        void displayWord();
        bool isWordGuessed();
        void guess(char ch);
};

vector<bool> hang::getRandomWord()
{
    ifstream file(wordlist);
    string word;
    srand(time(NULL));
    int wordcount=0;
    while(file>>word)
    {
        if(rand()%(++wordcount)==0)
            supersecretword = word;
    }
    return vector<bool> (supersecretword.length(), false);
    
}

void hang::displayWord()
{
    for(int i=0;i<supersecretword.length();i++)
    {
        if(guessed[i])
            cout<<supersecretword[i]<<" ";
        else
            cout<<"_ ";
    }
    cout<<endl;
    cout<<"Attempts left: "<<maxtries<<endl;
}

bool hang::isWordGuessed()
{
    for(int i=0; i<supersecretword.length();i++)
    {
        if(!guessed[i])
            return false;
    }
    return true;
}

void hang::guess(char ch)
{
    bool found=false;
    for(int i=0; i<supersecretword.length();i++)
    {
        if(ch==supersecretword[i])
        {
            found=true;
            guessed[i]=true;
        }
    }
    if(!found)
    {
        maxtries--;
        cout<<"Incorrect attempt!"<<endl;
    }
    if(isWordGuessed())
    {
        cout<<"Congratulations! The word is "<<supersecretword<<endl;
        exit(0);
    }
    if(maxtries==0)
    {
        cout<<"Sorry, you ran out of tries, the correct word was "<<supersecretword<<endl;
        exit(0);
    }
}

int main()
{
    char ch;
    hang obj;
    cout<<"Welcome to Hangman!"<<endl;
    obj.getRandomWord();
    while(1)
    {
        cout<<"Word: ";
        obj.displayWord();
        cout<<"Enter a character: ";
        cin>>ch;
        obj.guess(ch);
    }
    return 0;
}