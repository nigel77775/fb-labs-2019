p2=[1,1,0,0,0,0,1,1,0,0,1,0,1,0,1,0,1,0,0,0]
####0,1,2,3
p1=[1,1,1,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,1,0,0]
####0,1,2,3
a1=[0]*(int(len(p1)-1))+[1]
a2=[0]*(int(len(p2)-1))+[1]

file1 = open("G:/file1.txt", "w", encoding='utf-8')
file2 = open("G:/file2.txt", "w", encoding='utf-8')


buf1=[0]*(int(len(p1)-1))+[1]
buf2=[0]*(int(len(p2)-1))+[1]

str1=""
str2=""

def sdvig(arr,elem):
	a=arr[0]
	for i in range(0,len(arr)):
		if i == len(arr)-1:
			arr[i]=elem
		else:
			arr[i]=arr[i+1]
	return a



def aa(buf1,p1,a1,file):
	por=0
	i=0
	str1=""
	while i>-1:
		file.write(str(buf1[0]))
		por+=1
		nn=0
		for t in range(0,len(buf1)):
			nn+=buf1[t]*p1[t]
			#print(nn)
		q=str(sdvig(buf1,nn%2))
		str1=str1+q
		#print(buf1)
		i+=1
		if buf1==a1:
			print("T="+str(por))
			break
	return por
def bb(buf1,p1,TTTTT,h):
	por=0
	i=0
	while i<TTTTT:
		nn=0
		for t in range(0,len(buf1)):
			nn+=buf1[t]*p1[t]
			#print(nn)
		sdvig(buf1,nn%2)
		#print(buf1)
		por=por+(buf1[0]+buf1[h])%2
		#print(por)
		i+=1

	return por


s=[0]*10

#print(aa(buf2,p2,a2))
print(p2)
T=aa(buf2,p2,a2,file1)
for i in range(1,11):
	print("d["+str(i)+"]="+str(bb(buf2,p2,T,i)))


print(p1)
T=aa(buf1,p1,a1,file2)
for i in range(1,11):
	print("d["+str(i)+"]="+str(bb(buf1,p1,T,i)))
