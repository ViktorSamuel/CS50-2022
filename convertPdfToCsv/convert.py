# require pdf file as input from consol
# as output print all PIE competitors in finals



# importing required modules
import pdfplumber
import re
import sys

# array of lines
lines = []

# check consol input
if len(sys.argv) != 2:
    sys.exit("Usage: python convert.py file.pdf")

# open pdf and rewrite it into lines line by line
with pdfplumber.open(sys.argv[1]) as pdf:
    # load pages
    pages = pdf.pages
    # take each page
    for page in pages:
        # extract text form page
        text = page.extract_text()
        # rewrite text line by line
        for row in text.split('\n'):
            lines.append(row)

# open file for output
with open(sys.argv[1][:-4] + '.txt', 'w') as output:
    # take each line
    for line in lines:
        # variable for K1 = 0, K2 K4
        holes = 0
        # final race of category
        if re.search('^\d{4} (K|C)\d .+ (F|FA) .*', line):
            # line index
            index = lines.index(line)
            # counting holes
            holes = ''.join(filter(lambda i: i.isdigit(), line))
            holes = int(holes[4])
            if holes != 1: holes = 2

            # competitors in ceratin race
            competitors = 1
            PIE = False

            while True:
                # in this race category
                if re.search('^\d{4} (K|C)\d .*', lines[index + competitors]) or (index + competitors) == len(lines) - 1:
                    break
                # is pie here
                if lines[index + competitors].find('PIE') != -1: PIE = True
                # number of competitors in this race
                competitors += 1

            # is here pie
            if PIE == True:
                # print(line)
                output.write('\n' + line + '\n')
                for i in range(competitors - 1):
                    # hackuje piestanec
                    if lines[index + i + 1].find('PIE') != -1 and re.search('^\d(.) *', lines[index + i + 1]):
                        for j in range(holes):
                            # print(4*' ' + lines[index + i + j + 1])
                            output.write(4*' ' + lines[index + i + j + 1] + '\n')
                    # nehackuje
                    elif lines[index + i + 1].find('PIE') != -1 and lines[index + i].find('PIE') == -1 and not re.search('^\d(.) *', lines[index + i + 1]):
                        for j in range(holes, 0, -1):
                            # print(4*' ' + lines[index + i + 2 - j])
                            output.write(4*' ' + lines[index + i + 2 - j] + '\n')

