number = input("Number: ")


def luhn(number) -> bool:
    sum_val = 0
    sum_val += sum(list(map(lambda x: sum([int(s) for s in str(int(x)*2)]), number[-2::-2])))
    sum_val += sum(list(map(int, number[-1::-2])))
    print("sum: ", sum_val)
    return sum_val % 10 == 0


if luhn(number):
    if len(number) == 15 and number[:2] in ["34", "37"]:
        print("AMEX")
    elif len(number) == 16 and number[:2] in ["51", "52", "53", "54", "55"]:
        print("MASTERCARD")
    elif len(number) in [13, 16] and number[0] == "4":
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
