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
                if(found != 1)
                {
                    keep_word = false;
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
    int current_length = added_counter;
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

void makeGuess(char remainingChArray[], int score[], char newChArray[], int& remainingCount, int& added_counter, char final_guess[], int& num_attempts, Guessdata guess_dict[])
{
    printf("%i, %i, %i\n", remainingCount, added_counter, num_attempts);
    printf("coool\n");
    for(int i = 0; i < remainingCount/5; i ++)
    {
        printf("\n");
        for(int j = 0; j < 5; j++)
        {
            guess_dict[i].guess[j] = remainingChArray[(5*i)+j];
            printf("%c", guess_dict[i].guess[j]);
        }
        guess_dict[i].average = averageEliminated(guess_dict[i].guess, remainingChArray, score, newChArray, remainingCount, added_counter);
        printf("%i  ", guess_dict[i].average);
    }
    /*if(num_attempts > 0)
    {
        for(int i = 0; i < remainingCount; i += 5)
        {
            printf("%i: ", guess_dict[i/5].average);
            for(int j = 0; j < 5; j++)
            {
                printf("%c", guess_dict[i/5].guess[j]);
            }
            printf("\n");
        }
    }*/
    printf("yee\n");
    if(remainingCount>5){

        std::sort(&guess_dict[0], &guess_dict[remainingCount/5], customLess);
    }

    for(int i = 0; i < 5; i++)
    {
        final_guess[i] = guess_dict[(remainingCount/5)-1].guess[i];
        printf("%c", final_guess[i]);
    }
    printf("\n");
    num_attempts += 1;
}

int main()
{
    const int num_words = 2309;
    string * ANSWERLIST = new string[num_words];
    char * chArray = new char[11545*2];
    char * officialGuess = new char[5];
    char * officialAnswer = new char[5];
    int count = 0;
    int attempts = 0;
    int * score_template = new int[5];
    int numberOfWords;
    int addCount = 0;
    ifstream inputFile;
    inputFile.open("ANSWERS.txt");
    if(!inputFile)
    {
        cout << "Error finding input file" << endl;
        exit(-1);
    }
    while(!inputFile.eof())
    {
        inputFile >> ANSWERLIST[count];
        count++;
    }
    numberOfWords = count;
    int ch_count = 11545;
    int smaller_count = 5750;
    char * chAnswerList = new char[ch_count];
    char * smallerList = new char[smaller_count];
    for(int i = 0; i < 2309; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            chAnswerList[(5*i)+j] = ANSWERLIST[i][j];
        }
    }

    for(int i = 0; i < 1150; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            smallerList[(i*5)+j] = ANSWERLIST[i][j];
        }
    }



    officialAnswer[0] = 'b';
    officialAnswer[1] = 'r';
    officialAnswer[2] = 'o';
    officialAnswer[3] = 'o';
    officialAnswer[4] = 'k';



    //REAL GAME LOGIC
    //FIRST GUESS
    printf("first guess: ");
    Guessdata * guess_dict = new Guessdata[smaller_count/5];
    makeGuess(smallerList, score_template, chArray, smaller_count, addCount, officialGuess, attempts, guess_dict);
    compareWords(officialGuess, officialAnswer, score_template);
    bool match = true;
    for(int i = 0; i < 5; i++)
    {

        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
    }
    if(match)
    {
        printf("%i\n", attempts);
        return attempts;
    }
    //USE SMALLER COUNT
    cleanChArray(officialGuess, score_template, smallerList, chArray, smaller_count, addCount);
    if(addCount == 0)
    {
        printf("fail");
        return 0;
    }
    char * secondList = new char[addCount];
    for(int i = 0; i < addCount; i++)
    {
        secondList[i] = chArray[i];
        printf("%c", secondList[i]);
    }
    printf("\n");
    smaller_count = addCount;
    delete[] guess_dict;
    delete[] chAnswerList;
    printf("second guess: ");
    Guessdata * guess_dict2 = new Guessdata[smaller_count/5];
    //SECOND GUESS
    makeGuess(secondList, score_template, chArray, smaller_count, addCount, officialGuess, attempts, guess_dict2);
    compareWords(officialGuess, officialAnswer, score_template);
    match = true;
    for(int i = 0; i < 5; i++)
    {
        printf("%i", score_template[i]);

        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
    }
    if(match)
    {
        printf("%i\n", attempts);
        return attempts;
    }

    cleanChArray(officialGuess, score_template, secondList, chArray, smaller_count, addCount);
    if(addCount == 0)
    {
        printf("fail");
        return 0;
    }
    char * thirdList = new char[addCount];
    for(int i = 0; i < addCount; i++)
    {
        thirdList[i] = chArray[i];
    }
    smaller_count = addCount;

    delete[] secondList;
    delete[] guess_dict2;
    Guessdata * guess_dict3 = new Guessdata[smaller_count/5];
    printf("third guess: ");
    //THIRD GUESS
    makeGuess(thirdList, score_template, chArray, smaller_count, addCount, officialGuess, attempts, guess_dict3);
    compareWords(officialGuess, officialAnswer, score_template);
    match = true;
    for(int i = 0; i < 5; i++)
    {
        
        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
    }
    if(match)
    {
        printf("%i\n", attempts);
        return attempts;
    }

    cleanChArray(officialGuess, score_template, thirdList, chArray, smaller_count, addCount);
    if(addCount == 0)
    {
        printf("fail");
        return 0;
    }
    char * fourthList = new char[addCount];
    for(int i = 0; i < addCount; i++)
    {
        fourthList[i] = chArray[i];
    }
    smaller_count = addCount;

    delete[] thirdList;
    delete[] guess_dict3;
    Guessdata * guess_dict4 = new Guessdata[smaller_count/5];

    //FOURTH GUESS
    makeGuess(fourthList, score_template, chArray, smaller_count, addCount, officialGuess, attempts, guess_dict4);
    compareWords(officialGuess, officialAnswer, score_template);
    match = true;
    for(int i = 0; i < 5; i++)
    {
        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
    }
    if(match)
    {
        printf("%i\n", attempts);
        return attempts;
    }

    cleanChArray(officialGuess, score_template, fourthList, chArray, smaller_count, addCount);
    if(addCount == 0)
    {
        printf("fail");
        return 0;
    }
    char * fifthList = new char[addCount];
    for(int i = 0; i < addCount; i++)
    {
        fifthList[i] = chArray[i];
    }
    smaller_count = addCount;

    delete[] fourthList;
    delete[] guess_dict4;
    Guessdata * guess_dict5 = new Guessdata[smaller_count/5];

    //FIFTH GUESS
    makeGuess(fifthList, score_template, chArray, smaller_count, addCount, officialGuess, attempts, guess_dict5);
    compareWords(officialGuess, officialAnswer, score_template);
    match = true;
    for(int i = 0; i < 5; i++)
    {

        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
    }
    if(match)
    {
        printf("%i\n", attempts);
        return attempts;
    }

    cleanChArray(officialGuess, score_template, fifthList, chArray, smaller_count, addCount);
    if(addCount == 0)
    {
        printf("fail");
        return 0;
    }
    char * sixthList = new char[addCount];
    for(int i = 0; i < addCount; i++)
    {
        sixthList[i] = chArray[i];
    }
    smaller_count = addCount;

    delete[] fifthList;
    delete[] guess_dict5;
    Guessdata * guess_dict6 = new Guessdata[smaller_count/5];

    //SIXTH GUESS
    makeGuess(fifthList, score_template, chArray, smaller_count, addCount, officialGuess, attempts, guess_dict6);
    compareWords(officialGuess, officialAnswer, score_template);
    match = true;
    for(int i = 0; i < 5; i++)
    {
        if(score_template[i] != 2)
        {
            match = false;
            break;
        }
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
    /*for(int i = 0; i < smaller_count; i++)
    {
        printf("%c", chAnswerList[i]);
    }
    char g[5] = {'r', 'a', 'i', 's', 'e'};
    char poop[5] = {'d', 'o', 'w', 'r', 'y'};
    compareWords(g, officialAnswer, score_template);
    for(int i  = 0; i < 5; i++){
        printf("%i", score_template[i]);
    }
    cleanChArray(g, score_template, chAnswerList, chArray, smaller_count, addCount);
    printf("%i", addCount);
    for(int i = 0; i < addCount; i++)
    {
        printf("%c", chArray[i]);
    }*/
}