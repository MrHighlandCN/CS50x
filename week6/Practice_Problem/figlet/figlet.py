import random
import sys
import pyfiglet

figlet = pyfiglet.Figlet()
list = figlet.getFonts()

if len(sys.argv) != 1 and len(sys.argv) != 3:
    sys.exit("Invalid usage")
elif (sys.argv[1] != "-f" and sys.argv[1] != "--font") or sys.argv[2] not in list:
    sys.exit("Invalid usage")

s = input("Input: ")


print(sys.argv[1])
if len(sys.argv) == 1:
    f = random.choice(list)
else:
    f = sys.argv[2]

figlet.setFont(font=f)
print(figlet.renderText(s))
