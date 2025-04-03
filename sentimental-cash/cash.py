from cs50 import get_float


def main():
    while True:
        change = get_float("Change: ")
        if (change >= 0):
            break
    change = change * 100

    print(comparison(change))


def comparison(change_owed):
    quarters = 0
    dimes = 0
    nickels = 0
    pennies = 0
    while True:

        if (change_owed >= 25):
            change_owed -= 25
            quarters += 1

        elif (change_owed >= 10):
            change_owed -= 10
            dimes += 1

        elif (change_owed >= 5):
            change_owed -= 5
            nickels += 1

        elif (change_owed >= 1):
            change_owed -= 1
            pennies += 1

        if (change_owed == 0):
            break

    return quarters + dimes + nickels + pennies


main()
