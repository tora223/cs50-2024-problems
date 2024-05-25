import csv
import sys


def main():

    # Check for command-line usage
    argv = sys.argv
    if len(argv) != 3:
        print("Usage: python dna.py databases.csv sequence.txt")
        return

    # Read database file into a variable
    rows = []
    with open(argv[1], mode="r") as database_file:
        reader = csv.DictReader(database_file)
        header = reader.fieldnames
        for row in reader:
            rows.append(row)
    
    # Read DNA sequence file into a variable
    with open(argv[2], mode="r") as sequence_file:
        sequence = sequence_file.read()

    # Find longest match of each STR in DNA sequence
    longest_matches = {}
    for s in header[1:]:
        longest_matches[s] = longest_match(sequence, s)

    # Check database for matching profiles
    for row in rows:
        flag = True
        for k, v in longest_matches.items():
            if int(row[k]) != v:
                flag = False
        
        if flag:
            print(row["name"])
            return
    
    # If no match found
    print("No match")
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
