# TODO


def main():
    while True:
        n = input("Number: ")
        count = len(n)
        n = int(n)
        if n > 0:
            break

    if count != 13 and count != 15 and count != 16:
        print("INVALID")
        return 0

    if isValid(n):
        while n >= 100:
            n = int(n / 10)
        if (n == 37 or n == 34) and count == 15:
            print("AMEX")
        elif n >= 51 and n <= 55 and count == 16:
            print("MASTERCARD")
        elif int(n / 10) == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
    return 0


def isValid(n):
    sumMul2 = 0
    sum = 0
    while n != 0:
        sum += int(n % 10)
        n = int(n / 10)
        if n % 10 * 2 >= 10:
            sumMul2 += int((n % 10 * 2) % 10 + (n % 10 * 2) / 10)
        else:
            sumMul2 += int(n % 10 * 2)
        n = int(n / 10)

    res = sum + sumMul2
    if res % 10 == 0:
        return True
    else:
        return False


main()
