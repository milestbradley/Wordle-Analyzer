# Here I will begin to outline various methods that are required in the execution of the logic of this program. I will begin with basic intuitive methods and then use these as puzzle pieces to bring the advanced logic together.

WORDLIST = []
wordfile = open('GUESSWORDS.txt')
readguesses = wordfile.read()
WORDLIST = readguesses.replace('\n', ' ').split()
wordfile.close()


ANSWERLIST = []
wordfile = open('ANSWERS.txt')
readanswers = wordfile.read()
ANSWERLIST = readanswers.replace('\n', ' ').split()
wordfile.close()


#CHECKS IF GUESSWORD IS A VALID GUESS

def guessInList(word):
    for i in range(len(WORDLIST)):
        if word == WORDLIST[i]:
            return True
            break


#COMPARES TWO WORDS

def compareWords(guess, answer):
    score = []
    for i in range(5):
        isScored = False
        for j in range(5):
            if guess[i] == answer[j]:
                if i == j:
                    score.insert(i, 2)
                    isScored = True

                else:
                    if isScored == False:
                        score.insert(i, 1)
                        isScored = True
        if isScored == False:
            score.insert(i, 0)
    while len(score)>5:
        score.pop(5)
    return score


#REMOVES ALL WORDS THAT ARE NO LONGER POSSIBLE

def cleanList(guess, score, remainingWords):

    newList = []

    for i in range(len(remainingWords)):
        keep_word = True
        for j in range(len(score)):
            if score[j] == 0:
                for k in range(len(remainingWords[i])):
                    if guess[j] == remainingWords[i][k]:
                        keep_word = False

            elif score[j] == 2:
                if not guess[j] == remainingWords[i][j]:
                    keep_word = False

            elif score[j] == 1:
                for l in range(len(remainingWords[i])):
                    if  not (guess[j] == remainingWords[i][l] and j != l):
                        keep_word = False
                    elif remainingWords[i][l] == guess[l]:
                        keep_word = False
                    else:
                        keep_word = True
                        break


        if keep_word:
            newList.append(remainingWords[i])
    return newList


#RETURNS THE NUMBER OF WORDS ELIMINATED AFTER A CERTAIN GUESS USING THE ABOVE METHODS

def numberEliminated(guess, keyword):
    score = compareWords(guess, keyword)
    return(len(ANSWERLIST) - len(cleanList(guess, score, ANSWERLIST)))
    
    
#RETURNS THE AVERAGE NUMBER OF WORDS ELIMINATED FOR A SINGLE GUESS ACROSS EVERY POSSIBLE ANSWER

def averageEliminated(guess, remainingWords):
    num_elim = 0
    for i in range(len(remainingWords)):
        num_elim += numberEliminated(guess, remainingWords[i])
        
    return num_elim/len(remainingWords)