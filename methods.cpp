#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

//This struct stores the specific guess and its corresponding total number of words eliminated as determined by the totalEliminated function

struct Guessdata{
        int total;
        char guess[5];
    };
    



//This is the comparison used to sort the array of structs by their total eliminated values
struct {
        bool operator()(const Guessdata& a, const Guessdata& b) const { return a.total < b.total; }
    } customLess;

//This method determines whether a guess is a valid guess in the word list
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


/*This method compares two words according to Wordle logic, 
and returns an integer array of length 5, where a 0 corresponds to a grey letter, 
ie a letter that is not found in the true answer, a 1 corresponds to a yellow letter, 
or one that is found but in the wrong location, and a 2 corresponds to a green letter, 
which signifies the correct location and letter.*/
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

/*This method takes a guess word, and a score, and eliminates all words that are rendered impossible by that guess/score combination. 
It then updates an integer value which stores the number of words that are still possible answers and are added to the new list of remaining words.*/
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
                        break;
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
//This method uses the previous methods to return the number of words that are eliminated given a certain guess and answer combination
int numberEliminated(char guess_arr[], char keyword_arr[], int score[], char remainingChArray[], char newChArray[], int remainingCount, int& added_counter)
{
    compareWords(guess_arr, keyword_arr, score);
    cleanChArray(guess_arr, score, remainingChArray, newChArray, remainingCount, added_counter);
    return((remainingCount/5) - (added_counter)/5);
}

/*This method iterates through the above numberEliminated method, 
using the same guess word against every possible answer word, and sums the total number of words eliminated across all iterations. 
This is used to determine the optimal guess word*/
int totalEliminated(char guess_arr[], char remainingChArray[], int score[], char newChArray[], int remainingCount, int& added_counter)
{
    /*for(int i = 0; i < 5; i++)
    {
        printf("%c", guess_arr[i]);
    }*/
    //printf("\n");
    int num_elim = 0;
    for(int i = 0; i < remainingCount; i += 5)
    {

        char keyword_array[5];
        for(int j = 0; j < 5; j++)
        {
            keyword_array[j] = remainingChArray[i+j];
        }
        num_elim += numberEliminated(guess_arr, keyword_array, score, remainingChArray, newChArray, remainingCount, added_counter);
    }
    return num_elim;
}


/*This final method takes an array of structs and populates it with every possible guess word and then its corresponding total eliminated integer. 
It then sorts based on total eliminated, and the word with the highest total eliminated value will be used in the main function as the official guess*/
void makeGuess(char remainingChArray[], int score[], char newChArray[], int& remainingCount, int& added_counter, char final_guess[], int& num_attempts, Guessdata guess_dict[])
{
    //printf("%i, %i, %i\n", remainingCount, added_counter, num_attempts);
    //printf("coool\n");
    for(int i = 0; i < remainingCount/5; i ++)
    {
        //printf("\n");
        for(int j = 0; j < 5; j++)
        {
            guess_dict[i].guess[j] = remainingChArray[(5*i)+j];
            //printf("%c", guess_dict[i].guess[j]);
        }
        guess_dict[i].total = totalEliminated(guess_dict[i].guess, remainingChArray, score, newChArray, remainingCount, added_counter);
        //printf("%i  ", guess_dict[i].average);
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
//    printf("yee\n");

    std::sort(&guess_dict[0], &guess_dict[remainingCount/5], customLess);
    

    for(int i = 0; i < 5; i++)
    {
        final_guess[i] = guess_dict[(remainingCount/5)-1].guess[i];
        printf("%c", final_guess[i]);
    }
    printf("\n");
    num_attempts += 1;
}

/*TO  USE THIS PROGRAM:
This program is run using command line arguments, and the results will be printed in the terminal. 
To use, first compile, and then run using "./a.out Guess Answer"
Guess and Answer must be all lowercase 5 letter words, or the program will not work.
EXAMPLE: 
./a.out raise chief
Would print:
Guess 1: raise
Guess 2: edict
Guess 3: chief
Solved in 3 attempts!

For massive speed improvements, I have allowed the user to choose the first word manually, and then have the bot solve the remainder of the wordle. 
However, if you would like to use the algorithmically determined optimal guess, use "raise", and it will function as if the program solved from beginning to end.

*/
int main(int argc, char * argv[])
{
    int numberOfWords = 2309;
    string * ANSWERLIST = new string[numberOfWords];
    char * chArray = new char[numberOfWords*5];
    char officialGuess[5];
    char officialAnswer[5];
    int count = 0;
    int attempts = 0;
    int score_template[5];
    int addCount = 0;
    ifstream inputFile;

//This populates the main array of strings from the ANSWERS.txt file, which is the list of words released by Wordle as the possible answer words. 
//For speed purposes, I am only using possible answers as guess words, and not every possible 5 letter word. 

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
    int ch_count = numberOfWords*5;
//    int smaller_count = 5750;
    char * chAnswerList = new char[ch_count];
//    char * smallerList = new char[smaller_count];
    for(int i = 0; i < numberOfWords; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            chAnswerList[(5*i)+j] = ANSWERLIST[i][j];
        }
    }

/*    for(int i = 0; i < 1150; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            smallerList[(i*5)+j] = ANSWERLIST[i][j];
        }
    }
*/

    for(int i = 0; i < 5; i++)
    {
        officialGuess[i] = argv[1][i];
    }
    for(int i = 0; i < 5; i++)
    {
        officialAnswer[i] = argv[2][i];
    }

/* This is the main logic of the program. 
It iterates through a maximum of 6 guesses, using makeguess to sort the remaining words, 
and cleanlist to update the list for the next iteration. 
The program is sometimes unsuccessful with certain patterns of words, 
such as break, creak, wreak, and freak, not for any algorithmic flaw, 
but simply because each of these words is equally probable after _reak has been determined. 
I believe this is unavoidable. For all other words I have tested, it succeeds in determining the correct keyword.

*/

    for(int i = 0; i < 6; i++)
    {
        Guessdata * guess_dict = new Guessdata[ch_count/5];
        if(i == 0)
        {
            printf("Guess %i: ", i+1);
            for(int j = 0; j < 5; j++)
            {
                printf("%c", officialGuess[j]);
            }
            printf("\n");
            compareWords(officialGuess, officialAnswer, score_template);
            attempts++;
            
        }
        else
        {
            printf("Guess %i: ", i+1);
            makeGuess(chAnswerList, score_template, chArray, ch_count, addCount, officialGuess, attempts, guess_dict);
            compareWords(officialGuess, officialAnswer, score_template);
        }
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
            printf("Solved in %i attempts!\n", attempts);
            return 0;
        }
        //USE SMALLER COUNT
        cleanChArray(officialGuess, score_template, chAnswerList, chArray, ch_count, addCount);
        if(addCount == 0)
        {
            printf("fail\n");
            return 1;
        }
        //char * newList = new char[addCount];
        for(int i = 0; i < addCount; i++)
        {
            chAnswerList[i] = chArray[i];
            //printf("%c", secondList[i]);
        }
        ch_count = addCount;
        delete[] guess_dict;
        if(i == 5)
        {
            printf("FAIL\n");
            return 1;
        }
    }
    
    
}