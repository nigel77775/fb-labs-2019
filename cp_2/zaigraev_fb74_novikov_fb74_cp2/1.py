import sys, argparse, math, re
from operator import itemgetter      #  For dict reversing,
from itertools import groupby        #  without losing chars

__standart_index=0.0553
__lower_index=0
__count=0
__alphabet={}
snd = itemgetter(1)
__probab_keyLen=[]

lang_freq_dict={}
lang_dict=[]

rus_freq_dict={'о':0.10983, 'е':0.08483, 'а':0.07998, 'и':0.07367, 'н':0.067,
                'т':0.06318, 'с':0.05473, 'р':0.04746, 'в':0.04533, 'л':0.04343,
                'к':0.03486, 'м':0.03203, 'д':0.02977, 'п':0.02804, 'у':0.02615,
                'я':0.02001, 'ы':0.01898, 'ь':0.01735, 'г':0.01687, 'з':0.01641,
                'б':0.01592, 'ч':0.0145, 'й':0.01208, 'х':0.00966, 'ж':0.0094,
                'ш':0.00718, 'ю':0.00639, 'ц':0.00486, 'щ':0.00361, 'э':0.00331,
                'ф':0.00267, 'ъ':0.00037}#, 'ё':0.00013}

eng_freq_dict={'e':0.12702, 't':0.09056, 'a':0.08167, 'o':0.07507, 'i':0.06966,
                'n':0.06749, 's':0.06327, 'h':0.06094, 'r':0.08987, 'd':0.04253,
                'l':0.04025, 'c':0.02782, 'u':0.02758, 'm':0.02406, 'w':0.02360,
                'f':0.02228, 'g':0.02015, 'y':0.01974, 'p':0.01929, 'b':0.01492,
                'v':0.00978, 'k':0.00772, 'j':0.00153, 'x':0.00150, 'q':0.00095,
                'z':0.00074}



#a = ord('а')
rus_dict=['а', 'б', 'в', 'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м',
          'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ',
          'ы', 'ь', 'э', 'ю', 'я']#, 'ё'][chr(i) for i in range(a,a+6)] + [chr(a+33)] + [chr(i) for i in range(a+6,a+32)]

eng_dict=['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
          'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

def first_algo(filename, blockStep, fileEncoding, specCharAsSpace=True, countSpace=True):
    global __lower_index,  __probab_keyLen, __count
    
    polygramm_str=''
    main_arr=[]
    index=0
    sumIndex=0
    
    for start in range(blockStep):
        blockDict={}
        localStep=start+1
        count=0
        with open(filename, encoding=fileEncoding) as file:
            for line in file:
                for i in range(len(line)):
                 
                    #if ( (line[i].isalpha()==False and line[i]!=' ') or (line[i]==' ' and countSpace==False )):
                    if line[i].lower() not in lang_dict:
                        if specCharAsSpace==False or countSpace==False:                                
                            continue
                        _str=' '
                    else:
                        _str=line[i].lower()
                        
                    if localStep==blockStep:
                        localStep=1
                        try:
                            blockDict[_str]+=1
                        except:
                            blockDict[_str]=1
                        count+=1
                    else:
                        localStep+=1
                    
            __count=count
            index=find_index(blockDict)
            sumIndex+=index

            main_arr.append(blockDict)
    if __lower_index==0 and blockStep==1:
        __lower_index=1/len(main_arr[0])
    currIndex=sumIndex/blockStep
    
    temp=__standart_index#-__lower_index
    temp2=currIndex#-__lower_index

    if (temp2/temp)*100>80:
        __probab_keyLen.append(blockStep)

    print("{}:\t{}".format(blockStep, temp2))
            
    return main_arr

def find_index(_dict):
    res=0
    for elem in _dict:
        res+=_dict[elem]*(_dict[elem]-1)
    res*=1/(__count*(__count-1))
    return res

'''
def find_key(arr):
    res1String=""
    res2String=""
    
    for _dict in reversed(arr):
        inv_map = {number: [char for char,_ in v] 
                 for number, v in groupby(sorted(_dict.items(), key=snd), snd)}
        a=0
        for elem in sorted(inv_map, reverse=True):
            number = (ord(inv_map[elem][0]) - ord('о'))%32
            char1=chr(number+ord(lang_dict[0]))
            res1String+=char1

            number = (ord(inv_map[elem][0]) - ord('е'))%32
            char2=chr(number+ord(lang_dict[0]))
            res2String+=char2

            print(char1, char2, sorted(inv_map, reverse=True))
            break
    
    return [res1String, res2String]
'''

def find_key2(arr):
    max1=0
    value1=''
    res=""
    for _dict in reversed(arr):
        max1=0
        for i in range(len(lang_dict)):
            summ=0
            for elem in lang_freq_dict:
                try:
                    summ+=lang_freq_dict[elem]*_dict[lang_dict[(lang_dict.index(elem)+i)%len(lang_dict)]]
                except:
                    continue
            if summ>max1:
                max1=summ
                value1=lang_dict[i]

        res+=value1
    return res


def decrypt(filename, key):
    resString=""
    step=0
    with open(filename) as file:
        for line in file:
            for i in range(len(line)):
                #if line[i].isalpha()==False:
                if line[i].lower() not in lang_dict:
                    resString+=line[i]
                    continue
                if step==len(key):
                    step=0
                resString+=lang_dict[(ord(line[i].lower())-ord(key[step])+len(lang_dict))%len(lang_dict)] if line[i].islower()==True else  lang_dict[(ord(line[i].lower())-ord(key[step])+len(lang_dict))%len(lang_dict)].upper()
                step+=1
    print(resString)
    with open('cracked', 'w') as file:
        file.write("Key: {}\n".format(key))
        file.write(resString)


def lang_index():
    global __standart_index
    summ=0
    for elem in lang_freq_dict:
        summ+=lang_freq_dict[elem]**2
    print("LANG INDEX:", summ)
    __standart_index=summ

def lang_opt(lang):
    global lang_freq_dict, lang_dict
    if lang=="rus":
        lang_freq_dict=rus_freq_dict
        lang_dict=rus_dict
    elif lang=="eng":
        lang_freq_dict=eng_freq_dict
        lang_dict=eng_dict
    
        
def main(cmdFilename="TEXT.txt", cmdFileEncoding="ansi", cmdNum=12,
         cmdSpecCharAsSpace=True, cmdCountSpace=False, cmdOutput="Out"):
    global __alphabet
    #print("Choose File to CRACK:")
    #cmdFilename=input()
    
    print("Choose lang:")
    lang_opt(input())
    
    lang_index()
    
    print("Upper limit:", __standart_index)
    __alphabet=first_algo(filename=cmdFilename, fileEncoding=cmdFileEncoding,
                   blockStep=1, specCharAsSpace=cmdSpecCharAsSpace,
                   countSpace=cmdCountSpace)[0]
    print(__alphabet)
    
    print("Lower limit: ", __lower_index)
    for i in range(1, 30):
        first_algo(filename=cmdFilename, fileEncoding=cmdFileEncoding,
                   blockStep=i+1, specCharAsSpace=cmdSpecCharAsSpace,
                   countSpace=cmdCountSpace)

    print("Probable key lengths: ", __probab_keyLen)
    print("Enter Key Len:")
    keyLen=int(input())
    arr=first_algo(filename=cmdFilename, fileEncoding=cmdFileEncoding,
                   blockStep=keyLen, specCharAsSpace=cmdSpecCharAsSpace,
                   countSpace=cmdCountSpace)
    
    print("Probable key: ", find_key2(arr))
    print("Enter Key:")
    key=input()
    decrypt(cmdFilename, key)

    

if __name__ == "__main__":
    main()
