#include <iostream>
#include <fstream>

using namespace std;

bool guessInList(string guess, string arr[], int num_words)
{   
    int i;
    for(i = 0; i < num_words; i++)
    {
        if(arr[i] == guess)
        {
            cout << "The word '" << arr[i] << "' exists!" << endl;
            return true;
        }
    }
    return false;
}

void compareWords(char guess_arr[], char answer_arr[], int score[])
{

    for(int i = 0; i < 5; i++)
    {
        bool isScored = false;

        for(int j = 0; j <5; j++)
        
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
    }
}

void cleanChArray(char guess_array[], int score[], char remainingChArray[], char newChArray[], int remaining_count, int& added_counter)
{

    added_counter = 0;
    for(int i = 0; i < remaining_count; i+=5)
    {
        bool keep_word = true;
        for(int j = 0; j < 5; j++)
        {
            char guess_ch = guess_array[j];
            int score_j = score[j];
            if(score_j == 0)
            {
                for(int k = 0; k < 5; k++)
                {
                    if(guess_ch == remainingChArray[i+k])
                    {
                        keep_word = false;
                        break;
                    }
                }
            }
            else if(score_j == 2)
            {
                if(!(guess_ch == remainingChArray[i+j]))
                {
                    keep_word = false;
                    break;
                }
            }
            else if(score_j == 1)
            {
                for(int l = 0; l < 5; l++)
                {
                    if(!(guess_ch == remainingChArray[i+l] && j!=l))
                    {
                        keep_word = false;
                        break;
                    }
                    else if(guess_ch == remainingChArray[i+l])
                    {
                        keep_word = false;
                        break;
                    }
                }
            }
            if(!keep_word)
            {
                break;
            }
        }
        if(keep_word)
        {
            for(int k = i; k < i+5; k++)
            {
                newChArray[added_counter] = remainingChArray[k];
                added_counter++;
            }
        }
    }
    printf("%d\n", added_counter);
}

int main()
{
    const int num_words = 2309;
    string ANSWERLIST[num_words];
    char chArray[11545];
    int count = 0;
    int score_template[5];
    int numberOfWords;
    int addCount = 0;
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
    int ch_count = 11545;
    char * chAnswerList = new char[ch_count];
    for(int i = 0; i < 2309; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            chAnswerList[(5*i)+j] = ANSWERLIST[i][j];
        }
    }
    char guess[] = {'s', 'c', 'o', 'p', 'e'};
    char answer[] = {'s', 'c', 'o', 'p', 'e'};
    
    compareWords(guess, answer, score_template);
    
    cleanChArray(guess, score_template, chAnswerList, chArray, ch_count, addCount);
    

    for(int i = 0; i < addCount; i++)
    {
        printf("%c", chArray[i]);
        printf("\n");
    }
    
    return 0;
}


