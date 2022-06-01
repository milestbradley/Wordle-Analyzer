from methods import*

initial_barray = stringListToByteArray(ANSWERLIST)

c = cleanByteArray("hhhhh", [0, 0, 0, 0, 0], initial_barray)

print(len(c))