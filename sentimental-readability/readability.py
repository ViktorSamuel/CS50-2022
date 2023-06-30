from cs50 import get_string

# intest text
text = get_string("Text: ")

# tracking values
sentences = 0
words = 1
letters = 0
grade = 0

# chech each letter
for c in text:
    if c.isalpha():
        letters += 1
    elif c == ' ':
        words += 1
    elif c == '.' or c == '?' or c == '!':
        sentences += 1

# count grade
grade = round(0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8)

# print equal grade
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Before Grade 16+")
else:
    print(f"Grade {grade}")