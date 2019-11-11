import sys, argparse, math, re
from operator import itemgetter      #  For dict reversing,
from itertools import groupby        #  without losing n-gramms

__count=0
__num=0
__unique=0
__entropy=0

rus_dict=['а', 'б', 'в', 'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м',
          'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ',
          'ы', 'ь', 'э', 'ю', 'я', 'ё']


def polygramms_freq(filename, fileEncoding, num, step=1, specCharAsSpace=True, countSpace=True):
    global __num, __count, __unique
    res_dict={}
    polygramm_count=0
    polygramm_str=''
    with open(filename, encoding=fileEncoding) as file:
        for line in file:
            line=line.strip()
            line=re.sub(' +', ' ', line)
            for i in range(len(line)):
             
                if ( ((line[i] in rus_dict)==False and line[i]!=' ') or (line[i]==' ' and countSpace==False )):
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
                
    __num=num
    __count=polygramm_count
 
    for key in res_dict.keys():
        res_dict[key]=((float)(res_dict[key]))/((float)(polygramm_count))
    return res_dict


def print_inv_dict(_dict):
    string="=========================================================\n" + "Polygramm ({}) Count: {}\n".format(__num, __count)
    print(string)
    for a in sorted(_dict, reverse=True):
        for elem in sorted(_dict[a]):
            string="'{}' - {}".format(elem, round(a, 6))
            print(string)

def write_inv_dict(_dict, file):
    with open(file, 'a') as out:
        string="=========================================================\n" + "Polygramm ({}) Count: {}\n".format(__num, __count)
        out.write(string)
        for a in sorted(_dict, reverse=True):
            string = str(a)+":\t["
            for elem in sorted(_dict[a]):
                string="'{}' - {}".format(elem, round(a, 6))
                out.write(string+"\n")

def find_entropy(freq_dict):
    res=0
    for elem in freq_dict:
        res+=(elem*math.log(elem,2))*len(freq_dict[elem])
    res*=(-1/__num)
    print(__num)
    
    return res
'''
def find_entropy(freq_dict):
    res=0
    for elem in freq_dict:
        res+=(freq_dict[elem]*math.log(freq_dict[elem],2))
    res*=(-1/__unique)
    print(__unique)
    
    return res
'''
def find_redundancy(alphabet_len):
    return 1-(__entropy/(math.log(alphabet_len,2)))

def main(cmdFilename="TEXT.txt", cmdFileEncoding="cp866", cmdNum=1, cmdNumStep=1,
         cmdSpecCharAsSpace=True, cmdCountSpace=True, cmdOutput="Out"):
    global __entropy

    print(cmdSpecCharAsSpace, cmdCountSpace)
    
    snd = itemgetter(1)
    
    res=polygramms_freq(filename=cmdFilename, fileEncoding=cmdFileEncoding,
                        num=cmdNum, step=cmdNumStep, specCharAsSpace=cmdSpecCharAsSpace, countSpace=cmdCountSpace)
    
    inv_map = {number: [char for char,_ in v] 
                 for number, v in groupby(sorted(res.items(), key=snd), snd)}

    print_inv_dict(inv_map)
    write_inv_dict(inv_map, cmdOutput)

    __entropy=find_entropy(inv_map)
    #__entropy=find_entropy(res)

    redundancy= find_redundancy(len(res) if cmdNum==1 else len(polygramms_freq(filename=cmdFilename, fileEncoding=cmdFileEncoding,
                        num=1, step=1, specCharAsSpace=cmdSpecCharAsSpace, countSpace=cmdCountSpace)))
    
    print("H_{}: {}".format(cmdNum, __entropy))
    print("R by H_{}: {}".format(cmdNum, redundancy))
    data={}
    data["inputFile"]=cmdFilename
    data["n_gram"]=cmdNum
    data["n_gramStep"]=cmdNumStep
    data["specCharAsSpace"]=cmdSpecCharAsSpace
    data["countSpace"]=cmdCountSpace
    data["entropy"]=__entropy
    data["redundancy"]=redundancy
    data["result"]=inv_map


if __name__ == "__main__":
    try:
        parser = argparse.ArgumentParser()
        parser.add_argument("input", help="name of input file", type=str)
        parser.add_argument("inputEncoding", help="encoding of input file", type=str)
        parser.add_argument("n_gram", help="number for n-gram", type=int)
        parser.add_argument("n_gramStep", help="number of step for n-gram", type=int)
        parser.add_argument("countSpace", help="True for counting spaces, False - to not count them in n-grams", type=str)
        parser.add_argument("specCharAsSpace", help="True for counting non-alpha chars as space, False - to not count them at all", type=str)
        parser.add_argument("output", help="name of output file", type=str)
        args = parser.parse_args()
        main(cmdFilename=args.input, cmdFileEncoding=args.inputEncoding,
             cmdNum=args.n_gram, cmdNumStep=args.n_gramStep,  cmdCountSpace= False if args.countSpace.lower()!="true" else True,
             cmdSpecCharAsSpace=False if args.specCharAsSpace.lower()!="true" else True, cmdOutput=args.output)
    except:
        main()
