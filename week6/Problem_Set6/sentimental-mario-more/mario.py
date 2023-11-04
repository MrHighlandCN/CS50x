# TODO


def main():
    while True:
        try:
            height = int(input("What's height? "))
            if height <= 0 or height > 8:
                continue
            else:
                break
        except ValueError:
            pass

    for i in range(height):
        print(" " * (height - i - 1), "#" * (i + 1), "  ", "#" * (i + 1), sep="")


main()
