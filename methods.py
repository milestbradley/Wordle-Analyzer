# Here I will begin to outline various methods that are required in the execution of the logic of this program. I will begin with basic intuitive methods and then use these as puzzle pieces to bring the advanced logic together.
POSSIBLEWORDS = []
BANNEDLETTERS = []
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

def cleanList(guess, score):
    for i in range(len(ANSWERLIST)):
        for j in range(5):
            if score[j] == 0:
                for k in range(5):
                    print(ANSWERLIST[i][k])
                    
                    if guess[j] == ANSWERLIST[i][k]:
                        del ANSWERLIST[i]
                        break
            elif score[j] == 1:
                temp = False
                for k in range(5):
                    if (guess[j] == ANSWERLIST[i][k]) and (j != k):
                        temp = True
                        break
                if temp == False:
                    del ANSWERLIST[i]
            elif score[j] == 2:
                temp = False
                for k in range(5):
                    if (guess[j] == ANSWERLIST[i][k]) and (j == k):
                        temp = True
                        break
                if temp == False:
                    del ANSWERLIST[i]
            else:
                print("ERROR")