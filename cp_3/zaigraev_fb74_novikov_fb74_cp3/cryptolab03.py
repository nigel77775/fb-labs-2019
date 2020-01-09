import math, re
from operator import itemgetter      #  For dict reversing,
from itertools import groupby        #  without losing n-gramms
from pprint import pprint

snd = itemgetter(1)
__count=0
__entropy=0
__unique=0



rus_dict=['а', 'б', 'в', 'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м',
          'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ',
          'ь', 'ы', 'э', 'ю', 'я']

__lenOfRing=pow(len(rus_dict), 2)

__alphabet_dict={'о':0.10983, 'е':0.08483, 'а':0.07998, 'и':0.07367, 'н':0.067,
                'т':0.06318, 'с':0.05473, 'р':0.04746, 'в':0.04533, 'л':0.04343,
                'к':0.03486, 'м':0.03203, 'д':0.02977, 'п':0.02804, 'у':0.02615,
                'я':0.02001, 'ы':0.01898, 'ь':0.01735, 'г':0.01687, 'з':0.01641,
                'б':0.01592, 'ч':0.0145, 'й':0.01208, 'х':0.00966, 'ж':0.0094,
                'ш':0.00718, 'ю':0.00639, 'ц':0.00486, 'щ':0.00361, 'э':0.00331,
                'ф':0.00267, 'ъ':0.00037}#, 'ё':0.00013}

__standart_dict={}

def polygramms_freq(filename, fileEncoding, num, step=1, specCharAsSpace=True, countSpace=True):
    global __count, __unique
    res_dict={}
    polygramm_count=0
    polygramm_str=''
    with open(filename, encoding=fileEncoding) as file:
        for line in file:
            line=line.strip()
            line=re.sub(' +', ' ', line)
            line=line.replace('Ъ', 'Ь')
            line=line.replace('ъ', 'ь')

   #         print("Ptint COUNT BM: ",line.count('вм'))
            
            for i in range(len(line)):
             
                if ( ((line[i] in rus_dict) ==False and line[i]!=' ') or (line[i]==' ' and countSpace==False )):
                    if specCharAsSpace==False or countSpace==False:
                        continue
                    polygramm_str+=' '
                else:
                    polygramm_str+=line[i].lower()

                #polygramm_str=re.sub(' +', ' ', polygramm_str)

                if len(polygramm_str)==num:
                    try:
                        res_dict[polygramm_str]+=1
                    except:
                        __unique+=1
                        res_dict[polygramm_str]=1
                    polygramm_str=polygramm_str[step:]
                    polygramm_count+=1
                

    __count=polygramm_count

    #print(__count)
    for key in res_dict.keys():
    #    print(key, '\t', res_dict[key], '\t', polygramm_count, '\t', ((float)(res_dict[key]))/((float)(polygramm_count)))
        res_dict[key]=((float)(res_dict[key]))/((float)(polygramm_count))
    return res_dict

def find_entropy(freq_dict, n):
    res=0
    for elem in freq_dict:
        res+=(elem*math.log(elem,2))*len(freq_dict[elem])
    res*=(-1/n)
    
    return res

def getMostPopularNgrams(_dict, maxIter):
    it=0
    resDict={}
    arr=[]
    for a in sorted(_dict, reverse=True):
        for elem in sorted(_dict[a]):
            if it==maxIter:
                return arr
            resDict[elem]=a
            arr.append(elem)
            it+=1
        
def getBigramNum(bigram):
    return (rus_dict.index(bigram[0])*len(rus_dict))+rus_dict.index(bigram[1])

def getBigramStr(bigram):
    return rus_dict[bigram//len(rus_dict)]+rus_dict[bigram%len(rus_dict)]

def find_keys(x_list, y_list):
    res=[]
    lenOfRing=pow(len(rus_dict), 2)
    deltaY=(getBigramNum(y_list[0])-getBigramNum(y_list[1]))
    deltaX=(getBigramNum(x_list[0])-getBigramNum(x_list[1]))%lenOfRing
    if (math.gcd(deltaY, lenOfRing)>=1 and deltaX % math.gcd(deltaY, lenOfRing) == 0):
        d=math.gcd(deltaY, lenOfRing)
        a1=deltaY/d
        b1=deltaX/d
        n1=lenOfRing/d
        x0=(b1*inverse(a1, n1))%n1
        for i in range(d):
            aInversed=x0+i*n1
            a=inverse(aInversed, lenOfRing)
            if a==None or math.gcd(int(a), lenOfRing)!=1:
                continue
            res.append([int(a), (getBigramNum(y_list[0])-int(a)*getBigramNum(x_list[0]))%lenOfRing])
    return res

def find_all_keys(standart_popular, encrypted_popular):
    res=[]
    st_pairs=[]
    enc_pairs=[]
    count=0
    for i in range(len(standart_popular)):
        for j in range(len(standart_popular)):
            if i==j:
                continue
            st_pairs.append([standart_popular[i], standart_popular[j]])
    for i in range(len(encrypted_popular)):
        for j in range(len(encrypted_popular)):
            if i==j:
                continue
            enc_pairs.append([encrypted_popular[i], encrypted_popular[j]])
    for i in range(len(st_pairs)):
        for j in range(len(enc_pairs)):
            res_temp=find_keys(st_pairs[i], enc_pairs[j])
            res+=res_temp
            count+=1
  
    return set(map(tuple,res))
            
def inverse(a, m):
    a%=m;
    if a == 1:
        return 1;
    try:
        return ((1 - m * inverse(m % a, a)) // a)%m;
    except:
        return;

def decrypt(filename, fileEncoding, keys):
    lenOfRing=pow(len(rus_dict), 2)
    aInv=inverse(keys[0], lenOfRing)
    b=keys[1]
    res=''
    res_dict={}
    res_alphabet_dict={}
    polygramm_count=0
    alphabet_count=0
    polygramm_str=''
    countSpace=False
    specCharAsSpace=False
    with open(filename, encoding=fileEncoding) as file:
        for line in file:
            line=line.strip()
            line=re.sub(' +', ' ', line)
            line=line.replace('Ъ', 'Ь')
            line=line.replace('ъ', 'ь')
            for i in range(len(line)):
             
                if ( ((line[i] in rus_dict) ==False and line[i]!=' ') or (line[i]==' ' and countSpace==False )):
                    if specCharAsSpace==False or countSpace==False:
                        print("test")
                        continue
                    print("test!")
                    polygramm_str+=' '
                else:
                    polygramm_str+=line[i].lower()

                #polygramm_str=re.sub(' +', ' ', polygramm_str)

                if len(polygramm_str)==2:
                    xNum=(aInv*(getBigramNum(polygramm_str)-b))%lenOfRing
                    res+=getBigramStr(xNum)
                    try:
                        res_dict[res[-2:]]+=1
                    except:
                        res_dict[res[-2:]]=1
                    try:    
                        res_alphabet_dict[res[-2]]+=1
                    except:
                        res_alphabet_dict[res[-2]]=1
                    try:
                        res_alphabet_dict[res[-1]]+=1
                    except:                        
                        res_alphabet_dict[res[-1]]=1
                    polygramm_str=''
                    polygramm_count+=1
                    alphabet_count+=2
                    
    for key in res_dict.keys():
        res_dict[key]=((float)(res_dict[key]))/((float)(polygramm_count))

    for key in res_alphabet_dict:
        res_alphabet_dict[key]=((float)(res_alphabet_dict[key]))/((float)(alphabet_count))

    '''
    max_alphabet_info = (res_dict.get('cт', 0)+res_dict.get('но', 0)+res_dict.get('то', 0))/3
    max_standart_alphabet_info = (__standart_dict.get('cт', 0)+__standart_dict.get('но', 0)+__standart_dict.get('то', 0))/3
    max_res=max_alphabet_info/max_standart_alphabet_info
    '''
    max_alphabet_info = (res_alphabet_dict.get('о', 0)+res_alphabet_dict.get('а', 0)+res_alphabet_dict.get('е', 0))/3
    max_standart_alphabet_info = (__alphabet_dict.get('о', 0)+__alphabet_dict.get('а', 0)+__alphabet_dict.get('е', 0))/3
    max_res=max_alphabet_info/max_standart_alphabet_info
    
    min_alphabet_info = (res_alphabet_dict['ф']+res_alphabet_dict['щ']+res_alphabet_dict['ь'])/3
    min_standart_alphabet_info = (__alphabet_dict['ф']+__alphabet_dict['щ']+__alphabet_dict['ь'])/3
    min_res=min_alphabet_info/min_standart_alphabet_info

    summ=False

    if max_res >0.9 and max_res < 1.5 and min_res >0.8 and min_res < 1.5:
        summ=True
    
    return [summ, res]

def find_text(keys_list):
    sums={}
    sumslist=[]
    print(keys_list)
    count=0
    for elem in keys_list:
        a=decrypt(filename='test.txt', fileEncoding='utf-8', keys=elem)
        sums[elem]=a[0]
        sumslist.append(a[0])
        count+=1
        if count%10000==0:
            print(count)

    #pprint(sorted(sumslist, reverse=True))

    inv_map = {number: [char for char,_ in v] 
                 for number, v in groupby(sorted(sums.items(), key=snd), snd)}

    
    it=0
    #needList=inv_map[True]
    #print(needList)
    
    for elem in sorted(inv_map, reverse=True):
        print(elem, inv_map[elem])
        for elem_ in inv_map[elem]:
            if (it==2):
                return
            print(elem_)
            print(decrypt(filename='test.txt', fileEncoding='utf-8', keys=elem_)[1])
            print("----------------------------")
            it+=1
        return
           
    

def main():
    global __entropy, __standart_dict
    
    __standart_dict=polygramms_freq(filename='1.txt', fileEncoding='ansi',
                            num=2, step=1, specCharAsSpace=False, countSpace=False)
    
    inv_map = {number: [char for char,_ in v] 
                 for number, v in groupby(sorted(__standart_dict.items(), key=snd), snd)}

    #__entropy=find_entropy(inv_map, 2)

        
    res=polygramms_freq(filename='test.txt', fileEncoding='utf-8',
                        num=2, step=2, specCharAsSpace=False, countSpace=False)

    inv_map2 = {number: [char for char,_ in v] 
                 for number, v in groupby(sorted(res.items(), key=snd), snd)}


    standart_popular = getMostPopularNgrams(inv_map, 5)
    #standart_popular = ['ст', 'но', 'то', 'на', 'ен']

    encrypted_popular = getMostPopularNgrams(inv_map2, 5)
    print(encrypted_popular)
    #print(inv_map2)

    keys_list=find_all_keys(standart_popular, encrypted_popular)

#    print(keys_list)

    find_text(keys_list)

    print("Done!")


if __name__ == "__main__":
    main()
