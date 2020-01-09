f = open('text_original.txt', 'r')
text = f.read()
f.close

trash_mas = [',', '"', '\'', '\n', '\t', '.', '-', '—', ':', ';', '%', '!', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '(', ')', '$', '@', '^', '&', '*', '=', '+', '_', '/', '\\' '~', '#', '|']
for element in trash_mas:
    text = text.replace(element, '')

text = text.lower()
text = text.replace(' ', '')
text = text.replace('  ', '')
text = text.replace('   ', '')
text = text.replace('    ', '')
text = text.replace('     ', '')

print(text)
