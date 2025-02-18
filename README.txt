***For main logic, look at methods.cpp file***

The goal of this program is to take a 5 letter wordle solution and the various guesses the user made as inputs, and then output a variety of analyses including the following:
    -The quality of each guess made
    -The optimal guess given the current letter placement information (excluding the initial guess, in which guesses will simply be rated as plausible or not [boobs is a terrible guess due to double letters and is rated as a poor guess, but you don't get extra points for crane vs adieu; among the top good words to begin with, they are all given equal quality]) at each guessing interval (could also output the top x guesses at each interval)
    -The number of turns it took my program to solve that wordle (averaged over 10 attempts in which each of the 10 best initial guesses were used, to eliminate bias ie the initial guess was proud and the answer was pound, the computer doesn't actually get it in 2 because this is essentially luck) 
    -Some algorithmically derived percent accuracy for your guessing performance based on the program’s rating of each of your guesses
    -Some algorithmically derived luck rating for the day (using the proud and pound example, this isn't necessarily low skill, but it is highly lucky. High accuracy + low luck = high skill)

To achieve these results, a variety of data needs to be acquired and algorithms need to be written. Here I will try to outline the steps as I currently see them in solving this problem:

List of 5 letter english words stored in array/list
    -Potentially look through Wordle.com’s source code to see the specific word list they draw from (nerpa and zineb are not used as wordle words, but are 5 letter english words)

Each word assigned value for how much information they will PROBABLY give, given the current set of possible words
    -At first, this is entire word list, but after each guess, will become smaller list
    -This must use word usage statistics

Algorithm to calculate I(w) [information of a word, on average] by finding probability of each letter combination (gray, yellow, green) and the amount that this result would decrease the size of the possible words dataset
    -Multiply “chance of this result” times “factor by which this outcome decreases size of dataset” and sum each of these outcomes for each word
    -Use base 2 (halves the data set, quarters it, 8ths it, etc)

Deliver guess, based on combination of highest probable information and a factor for chance that that word is the actual answer
    -Algorithm for probability each word being answer
    -Similarly common words, with lack of information, should be rated equally in the eyes of being a possible solution
    -“There” and “robin” are equally likely answers, even though “there” is far more common in real life
    -Algorithm for weighting I(w) and P [probability] and making guess

Analyze guess for luck (accuracy is obviously 99th percentile, or my program has failed)
    -Write an algorithm to determine standard deviation from projected information of a certain most accurate guess from the actual information gained (ex. “Alien” is a great initial guess, and is likely to give the user information. However, the word could be “trout”. This isn’t low skill, because given the information the user had, “alien” was likely to be a better guess than trout. However, the user received very little information other than that a, l, i, e, and n, are not used in the answer word. This is an example of low luck)

Repeat until bot has completed the wordle

Return bot guesses, number of guesses, and luck of bot

Use existing algorithms to calculate the accuracy and luck of the user inputted guess
    -All words should already have a rating
    -Algorithm to make a standard distribution of worst to best guesses, and return a percentile ranking of user guess

For each of these guesses, use guessing algorithm to make bot guess given the circumstances on that turn of the user

Return optimal guesses

Repeat user guess analysis for each guess, outputting optimal guesses each time

Algorithm for accuracy of user guesses
    -Using standard deviation guesses as before, but somehow compiling these percentiles for an overall accuracy statistic

Return percentile accuracy

Return percentile luck



From this, it appears that 6 algorithms are needed to make this program work. Here I will try to unpack the math and data required for each one:

Average Information Algorithm:
    Purpose: Return amount of information, in bits, the user gains from using a specific word as a guess, given the guessword and current pool of possible answers.

Word Probability Algorithm:
    Purpose: Return the probability, as a decimal out of 1, of a specific guessword being the actual solution, given the guessword and the current pool of possible answers.

Guess Ranking Algorithm:
    Purpose: Use AIA and WPA to rank optimal guesses in order from best to worst.

Information Received Algorithm:
    Purpose: Return the actual amount of information received from a certain guessword and answerword, in bits derived from the factor by which the current pool of possible words has decreased relative to the previous pool of possible words

Guess Luck (Percentile) Algorithm:
    Purpose: Return the luck percentile rating of a specific guess outcome, given the guessword, WPA rating in bits, actual information received in bits, and all possible actual information received quantities given the current pool of possible words and their WPA ratings.

Guess Accuracy (Percentile) Algorithm:
    Purpose: Return the accuracy percentile rating of a specific guess given the guessword. Derived by finding percentile rank of guessword among all possible guess words based on GRA. 

Total Accuracy (Percentile) Algorithm:
    Purpose: Return overall accuracy of an entire round of wordle, given the GA(P)A of each guess made.


