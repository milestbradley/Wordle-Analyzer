#include <iostream>
#include <fstream>

using namespace std;

bool guessInList(string guess, string arr[], int num_words)
{   
    int i;
    for(i = 0; i < num_words; i++)
        if(arr[i] == guess)
        {
            cout << "The word '" << arr[i] << "' exists!" << endl;
            return true;
        }
    return false;
}

int * compareWords(char guess_arr[], char answer_arr[])
{
    int score [] = {0, 0, 0, 0, 0};
    int i;
    for(i = 0; i < 5; i++)
        bool isScored = false;
        int j;
        for(j = 0; j <5; j++)
        
            if(guess_arr[i] == answer_arr[j])
            {
                if(i == j)
                {
                    score[i] = 2;
                    isScored = true;
                }
                else
                {
                    if(!isScored)
                    {
                        score[i] = 1;
                        isScored = true;
                    }
                }
            }
        if(isScored == false)
        {
            score[i] = 0;
        }
    return score;
}

int main()
{
    const int num_words = 2309;
    string ANSWERLIST[num_words];
    int count = 0;
    int numberOfWords;
    
    ifstream inputFile;
    inputFile.open("ANSWERS.txt");
    if(!inputFile)
    {
        cout << "Error finding input file" << endl;
        system("pause");
        exit(-1);
    }
    while(!inputFile.eof())
    {
        inputFile >> ANSWERLIST[count];
        count++;
    }
    numberOfWords = count;
    
    guessInList("trust", ANSWERLIST, numberOfWords);

    return 0;
}


