import csv
from sys import argv


# Check for correct usage

if len(argv) != 3:
    print("Usage: dna.py database sequence")
    exit(1)


# Create list of lists from database rows

database = []

with open(argv[1], 'r') as file:
    csvtable = csv.reader(file)
    for row in csvtable:
        database.append(row)


# Read DNA sequence from text file

with open(argv[2], 'r') as file:
    dna = file.read().rstrip('\n')


# scan sequence and save occurences in list

occ = [0]

numSTR = len(database[0]) - 1

for i in range(numSTR):

    # initialize temporary variables

    STR = database[0][i+1]
    j = 0
    maxrepeats = 0
    repeats = 0

    while j < len(dna) - len(STR):

        if dna[j: j + len(STR)] == STR:
            repeats += 1
            if repeats > maxrepeats:
                maxrepeats = repeats
            j += len(STR)
        else:
            repeats = 0
            j += 1

    occ.append(str(maxrepeats))


# Compare dna occurence list with person's STR list

numPers = len(database) - 1

for i in range(numPers):
    if database[i+1][1:numSTR+1] == occ[1:numSTR+1]:
        print(database[i+1][0])
        exit(0)


# In case there is no match

print("No match")