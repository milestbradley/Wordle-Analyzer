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

    score_len = len(score)
    remaining_cnt = len(remainingWords)
    for i in range(remaining_cnt):
        keep_word = True
        remaining = remainingWords[i]
        remaining_len = len(remaining)
        for j in range(score_len):
            guess_ch = guess[j]
            score_j = score[j]
            if score_j == 0:
                for k in range(remaining_len):
                    if guess_ch == remaining[k]:
                        keep_word = False
                        break

            elif score_j == 2:
                if not guess_ch == remaining[j]:
                    keep_word = False
                    break

            elif score_j == 1:
                for l in range(remaining_len):
                    rem_ch = remaining[l]
                    if  not (guess_ch == rem_ch and j != l):
                        keep_word = False
                        break
                    elif rem_ch == guess_ch:
                        keep_word = False
                        break
#                   else:
#                       keep_word = True
            if not keep_word: break

        if keep_word:
            newList.append(remaining)
    return newList
    
    


#RETURNS THE NUMBER OF WORDS ELIMINATED AFTER A CERTAIN GUESS USING THE ABOVE METHODS

def numberEliminated(guess, keyword):
    score = compareWords(guess, keyword)
    return(len(ANSWERLIST) - len(cleanList(guess, score, ANSWERLIST))) 
    return(len(ANSWERLIST) - len(cleanList(guess, score, ANSWERLIST)))


#RETURNS THE AVERAGE NUMBER OF WORDS ELIMINATED FOR A SINGLE GUESS ACROSS EVERY POSSIBLE ANSWER

def averageEliminated(guess, remainingWords):
    num_elim = 0
    for i in range(len(remainingWords)):
        num_elim += numberEliminated(guess, remainingWords[i])

    return num_elim/len(remainingWords) 