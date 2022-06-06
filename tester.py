from methods import*


initial_barray = stringListToByteArray(ANSWERLIST)
broke_guess_array = stringListToByteArray("broke")
print(averageEliminated(broke_guess_array, initial_barray))
