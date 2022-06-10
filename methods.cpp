#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Guessdata{
        int average;
        char guess[5];
    };


struct {
        bool operator()(const Guessdata& a, const Guessdata& b) const { return a.average < b.average; }
    } customLess;



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
                        for(int e = 0; e < 5; e++)
                        {
                            if(guess_array[e] == remainingChArray[i+k] && e != k && score[e] != 0)
                            {
                                keep_word = true;
                                break;
                            }
                            else
                            {
                                keep_word = false;
                                break;
                            }
                        }
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
                int found = 0;
                for(int l = 0; l < 5; l++)
                {
                    if(guess_ch == remainingChArray[i+l] && j == l)
                    {
                        keep_word = false;
                        break;
                    }
                    else if(guess_ch == remainingChArray[i+l] && j!=l)
                    {
                        found += 1;

                    }
                }
                keep_word = (found == 1);
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
//                printf("here\n");
                newChArray[added_counter] = remainingChArray[k];
                added_counter++;
            }
        }
    }

}

int numberEliminated(char guess_arr[], char keyword_arr[], int score[], char remainingChArray[], char newChArray[], int remainingCount, int& added_counter)
{
    compareWords(guess_arr, keyword_arr, score);
    cleanChArray(guess_arr, score, remainingChArray, newChArray, remainingCount, added_counter);
    return(2309 - (added_counter)/5);
}

int averageEliminated(char guess_arr[], char remainingChArray[], int score[], char newChArray[], int remainingCount, int& added_counter)
{
    int num_elim = 0;
    for(int i = 0; i < remainingCount; i += 5)
    {
        char * keyword_array = new char[5];
        for(int j = 0; j < 5; j++)
        {
            keyword_array[j] = remainingChArray[i+j];
        }
        num_elim += numberEliminated(guess_arr, keyword_array, score, remainingChArray, newChArray, remainingCount, added_counter);
    }
    return num_elim/2309;
}

void makeGuess(char remainingChArray[], int score[], char newChArray[], int& remainingCount, int& added_counter, char final_guess[], int& num_attempts)
{
    int num_words = 230;
    Guessdata * guess_dict = new Guessdata[num_words];
    for(int i = 0; i < remainingCount; i += 5)
    {
        char guess_arr[5];
        for(int j = 0; j < 5; j++)
        {
            guess_dict[i/5].guess[j] = remainingChArray[i+j];
            //printf("%c", guess_dict[i/5].guess[j]);
        }
        guess_dict[i/5].average = averageEliminated(guess_dict[i/5].guess, remainingChArray, score, newChArray, remainingCount, added_counter);
    }

    std::sort(&guess_dict[0], &guess_dict[num_words], customLess);
    for(int i = 0; i < 230; i++)
    {
        for(int j = 0; j < 5; j++){
        }

    }

    for(int i = 0; i < 5; i++)
    {
        final_guess[i] = guess_dict[num_words-1].guess[i];
        printf("%c", final_guess[i]);
    }
    num_attempts += 1;
}

int main()
{
    const int num_words = 2309;
    string ANSWERLIST[num_words];
    char chArray[11545];
    char * officialGuess = new char[5];
    char * officialAnswer = new char[5];
    int count = 0;
    int attempts = 0;
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
    int smaller_count = 1150;
    char * chAnswerList = new char[ch_count];
    char * smallerList = new char[ch_count/10];
    for(int i = 0; i < 2309; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            chAnswerList[(5*i)+j] = ANSWERLIST[i][j];
        }
    }
    for(int i = 0; i < 230; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            smallerList[(i*5)+j] = ANSWERLIST[i][j];
        }
    }

    char official_answer[] = {'a', 'l', 'o', 'n', 'e'};

    
    
    
    //REAL GAME LOGIC
    //FIRST GUESS
    printf("first guess: ");
    makeGuess(smallerList, score_template, chArray, smaller_count, addCount, officialGuess, attempts);
    printf("herrrr");
    compareWords(officialGuess, officialAnswer, score_template);
    bool match = true;
    for(int i = 0; i < 5; i++)
        
        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
    if(match)
    {
        printf("%i\n", attempts);
        return attempts;
    }
    printf("here");
    cleanChArray(officialGuess, score_template, smallerList, chArray, numberOfWords, addCount);
    char * secondList = new char[addCount/5];
    for(int i = 0; i < addCount; i++)
    {
        secondList[i] = chArray[i];
    }
    ch_count = addCount;
    
    
    printf("second guess: ");
    
    //SECOND GUESS
    makeGuess(secondList, score_template, chArray, ch_count, addCount, officialGuess, attempts);
    match = true;
    for(int i = 0; i < 5; i++)
        
        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
    if(match)
    {
        printf("%i\n", attempts);
        return attempts;
    }

    cleanChArray(officialGuess, score_template, secondList, chArray, numberOfWords, addCount);
    char * thirdList = new char[addCount/5];
    for(int i = 0; i < addCount; i++)
    {
        thirdList[i] = chArray[i];
    }
    ch_count = addCount;
    
    
    
    
    //THIRD GUESS
    makeGuess(thirdList, score_template, chArray, ch_count, addCount, officialGuess, attempts);
    compareWords(officialGuess, officialAnswer, score_template);
    match = true;
    for(int i = 0; i < 5; i++)
        
        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
    if(match)
    {
        printf("%i\n", attempts);
        return attempts;
    }

    cleanChArray(officialGuess, score_template, thirdList, chArray, numberOfWords, addCount);
    char * fourthList = new char[addCount/5];
    for(int i = 0; i < addCount; i++)
    {
        fourthList[i] = chArray[i];
    }
    ch_count = addCount;
    
    
    
    
    //FOURTH GUESS
    makeGuess(fourthList, score_template, chArray, ch_count, addCount, officialGuess, attempts);
    compareWords(officialGuess, officialAnswer, score_template);
    match = true;
    for(int i = 0; i < 5; i++)
        
        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
    if(match)
    {
        printf("%i\n", attempts);
        return attempts;
    }

    cleanChArray(officialGuess, score_template, fourthList, chArray, numberOfWords, addCount);
    char * fifthList = new char[addCount/5];
    for(int i = 0; i < addCount; i++)
    {
        fifthList[i] = chArray[i];
    }
    ch_count = addCount;
    
    
    
    
    //FIFTH GUESS
    makeGuess(fifthList, score_template, chArray, ch_count, addCount, officialGuess, attempts);
    compareWords(officialGuess, officialAnswer, score_template);
    match = true;
    for(int i = 0; i < 5; i++)
        
        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
    if(match)
    {
        printf("%i\n", attempts);
        return attempts;
    }

    cleanChArray(officialGuess, score_template, fifthList, chArray, numberOfWords, addCount);
    char * sixthList = new char[addCount/5];
    for(int i = 0; i < addCount; i++)
    {
        sixthList[i] = chArray[i];
    }
    ch_count = addCount;
    
    
    
    
    //SIXTH GUESS
    makeGuess(sixthList, score_template, chArray, ch_count, addCount, officialGuess, attempts);
    compareWords(officialGuess, officialAnswer, score_template);
    match = true;
    for(int i = 0; i < 5; i++)
        
        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
    if(match)
    {
        printf("%i\n", attempts);
        return attempts;
    }
    else
    {
        printf("FAIL\n");
        return 0;
    }
    
}


