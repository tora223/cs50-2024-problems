def main():
    text = input("Text:")
    grade = readability_test(text)
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def readability_test(text: str) -> int:
    sentences = text.count(".") + text.count("!") + text.count("?")
    words = text.count(" ") + 1
    letters = sum([1 for s in text if s.isalpha()])
    
    print(f"letters: {letters}, words: {words}, sentences: {sentences}")
    
    l = (letters / words) * 100
    s = (sentences / words) * 100
    
    index = 0.0588 * l - 0.296 * s - 15.8
    
    return round(index)


main()