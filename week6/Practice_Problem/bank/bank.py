greeting = input("Greeting: ").strip().lower()

if "hello" in greeting:
    print("$0")
elif greeting.find("h") == 0:
    print("$20")
else:
    print("$100")
