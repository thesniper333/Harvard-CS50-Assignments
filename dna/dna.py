import csv
from sys import argv, exit


def main():

    if (len(argv) != 3):
        print(f"Usage: python dna.py database_name file_name")
        exit(1)

    # Read database file into a variable

    rows = []
    with open(argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)

    # Read DNA sequence file into a variable

    with open(argv[2], 'r') as file:
        sequence = file.read()

    subsequences = list(rows[0].keys())[1:]
    # TODO: Find longest match of each STR in DNA sequence

    result = {}
    for i in subsequences:
        result[i] = longest_match(sequence, i)

    # TODO: Check database for matching profiles
    for person in rows:
        counter = 0
        for i in subsequences:
            if int(person[i]) == result[i]:
                counter += 1

        if counter == len(subsequences):
            print(person["name"])
            return
    print("No Match")
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
