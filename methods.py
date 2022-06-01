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
    score = [0, 0, 0, 0, 0]
    for i in range(5):
        isScored = False
        for j in range(5):
            if guess[i] == answer[j]:
                if i == j:
                    score[i] = 2
                    isScored = True

                else:
                    if isScored == False:
                        score[i] = 1
                        isScored = True
        if isScored == False:
            score[i] = 0
    return score


#REMOVES ALL WORDS THAT ARE NO LONGER POSSIBLE
def cleanByteArray(guess, score, remainingByteArray):
    guess_array = bytearray()
    for i in range(5):
        guess_array.extend(map(ord, guess))
        
    newByteArray = ()
    score_len = len(score)
    remaining_count = len(remainingByteArray)
    i = 0
    for i in range(0, remaining_count, 5):
        keep_word = True
        print('rly bro')
        for j in range(score_len):
            guess_char = guess_array[j]
            score_j = score[j]
            print('yuh')
            if score_j == 0:
                print("here")
                for k in range(5):
                    if guess_char == remainingByteArray[i+k]:
                        print("here2")
                        keep_word = False
                        break
                
            elif score_j == 2:
                if not guess_char == remainingByteArray[i+j]:
                    keep_word = False
                    break
                
            elif score_j == 1:
                for l in range(5):
                    if not (guess_char == remainingByteArray[i+l] and j != l):
                        keep_word = False
                        break
                    elif guess_char == remainingByteArray[i+l]:
                        keep_word = False
                        break
            if not keep_word: break 
        

        if keep_word:
            for k in range(i-4, i+1):
                newByteArray.append(remainingByteArray[k])
        return newByteArray

def cleanList(guess, score, remainingWords):

    newList = []
    score_len = len(score)
    remaining_count = len(remainingWords)
    for i in range(remaining_count):
        keep_word = True
        remaining = remainingWords[i]
        remaining_len = len(remaining)
        for j in range(score_len):
            guess_char = guess[j]
            score_j = score[j]
            if score_j == 0:
                for k in range(remaining_len):
                    if guess_char == remaining[k]:
                        keep_word = False
                        break

            elif score_j == 2:
                if not guess_char == remaining[j]:
                    keep_word = False
                    break

            elif score_j == 1:
                for l in range(remaining_len):
                    rem_char = remaining[l]
                    if  not (guess_char == rem_char and j != l):
                        keep_word = False
                        break
                    elif rem_char == guess_char:
                        keep_word = False
                        break

            if not keep_word: break

        if keep_word:
            newList.append(remaining)
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
    
def stringListToByteArray(remainingWords):
    
    remainingByteArray = bytearray()
    for i in range(len(remainingWords)):
        
        remainingByteArray.extend(map(ord, remainingWords[i]))
    return remainingByteArray

def byteArrayToStringList(remainingWords):
    newList = []
    for i in range(len(remainingWords)):
        newList.append(remainingWords.decode(i))
    return newList