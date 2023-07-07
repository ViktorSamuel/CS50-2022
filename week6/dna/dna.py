import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable numbers are strings
    database = []
    with open(sys.argv[1]) as fD:
        reader = csv.DictReader(fD)
        for person in reader:
            database.append(person)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as fC:
        reader = csv.reader(fC)
        chain = next(reader)

    # TODO: Find longest match of each STR in DNA sequence
    if sys.argv[1] == 'databases/large.csv':
        STR = {
            'AGATC': longest_match(chain[0], 'AGATC'),
            'TTTTTTCT': longest_match(chain[0], 'TTTTTTCT'),
            'AATG': longest_match(chain[0], 'AATG'),
            'TCTAG': longest_match(chain[0], 'TCTAG'),
            'GATA': longest_match(chain[0], 'GATA'),
            'TATC': longest_match(chain[0], 'TATC'),
            'GAAA': longest_match(chain[0], 'GAAA'),
            'TCTG': longest_match(chain[0], 'TCTG')
        }
    else:
        STR = {
            'AGATC': longest_match(chain[0], 'AGATC'),
            'AATG': longest_match(chain[0], 'AATG'),
            'TATC': longest_match(chain[0], 'TATC')
        }

    # tracking vars
    match = 0
    count = 0
    num = 0

    # for each in database
    for person in database:
        # chech parameters
        for str in STR:
            num += 1
            if STR[str] == int(person[str]):
                match += 1
        # if parameters are eql
        if match == num:
            print(person['name'])
            return
        match = 0
        num = 0
        count += 1

    # no one
    if count == len(database):
        print('No match')

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()