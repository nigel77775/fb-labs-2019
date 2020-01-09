#a = ord('а')
rus_dict=['а', 'б', 'в', 'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м',
          'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ',
          'ы', 'ь', 'э', 'ю', 'я']#, 'ё'][chr(i) for i in range(a,a+6)] + [chr(a+33)] + [chr(i) for i in range(a+6,a+32)]

eng_dict=['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
          'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']


lang_dict=[]


def lang_opt(lang):
    global lang_dict
    if lang=="eng":
        lang_dict=eng_dict
    elif lang=="rus":
        lang_dict=rus_dict

def encrypt(inputFile, outputFile, key):
    encrypted=""
    keyStep=0
    with open(inputFile, "r") as file:
        for line in file:
            for elem in line:
                if elem.lower() not in lang_dict:
                    encrypted+=elem
                else:
                    
                    encrypted+=lang_dict[(lang_dict.index(elem.lower())+lang_dict.index(key[keyStep]))%len(lang_dict)] if elem.islower()==True else lang_dict[(lang_dict.index(elem.lower())+lang_dict.index(key[keyStep]))%len(lang_dict)].upper()
                    keyStep+=1
                    keyStep%=len(key)
    with open(outputFile, "w") as file:
        file.write(encrypted)

def main():
    #print("Enter input File:")
    #inputFile=input()
    #print("Enter output File:")
    #inputFile=input()
    print("Choose language dictionary (eng/rus):")
    lang=input()
    lang_opt(lang)
    #print(lang_dict)
    print("Enter key (use symbols from dictionary):")
    key=input()
    key=key.lower()
    inputFile="TEXT2.txt"
    outputFile="TEXT.txt"
    encrypt(inputFile, outputFile, key)

if __name__ == "__main__":
    main()
