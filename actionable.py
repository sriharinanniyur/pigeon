# The Lisp AI program will output data to the file data/RESULTS.
# get_results() - returns a list of two-element lists that contain:
# the flag string ("ACTION-ITEM" or "NOT-ACTION-ITEM") as first element and the sentence itself as the second.
def get_results():
    with open('data/RESULTS', 'r') as fin:
        return [[line.split()[0], ' '.join(line.split()[1:]).upper()] for line in fin.readlines()]

# flag() - appends a string to the POSITIVES file if ident=True and the NEGATIVES file if ident=False.
# This is for the user to be able to give data to the AI for training.
def flag(string, ident):
    with open(('training/POSITIVES' if ident else 'training/NEGATIVES'), 'a+') as fout:
        fout.write(string + '\n')
