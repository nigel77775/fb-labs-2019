from collections import Counter

p1 = [1,0,1,0,0,0,0,0,1,0,1,1,0,0,0,1,0,1,0,1,0,1,1,0]
a1 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]
p2 = [1,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,1]
a2 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]
a0 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]
a00 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]
maxperiod1 = 2 ** (len(p1) + 1)
maxperiod2 = 2 ** (len(p2) + 1)

def hz(p1, p2, a0, a1, a2, maxperiod1, maxperiod2):
	l1 = []
	l2 = []
	bigrams = ''
	threegrams = ''
	fourgrams = ''
	fivegrams = ''
	bigrams2 = ''
	threegrams2 = ''
	fourgrams2 = ''
	fivegrams2 = ''
	twgams = dict()
	trgams = dict()
	frgams = dict()
	fvgams = dict()
	twgams2 = dict()
	trgams2 = dict()
	frgams2 = dict()
	fvgams2 = dict()	
	avtoker1 = 0
	avtoker2 = 0
	avtoker3 = 0
	avtoker4 = 0
	avtoker5 = 0
	avtoker6 = 0
	avtoker7 = 0
	avtoker8 = 0
	avtoker9 = 0
	avtoker10 = 0
	avtoker11 = 0
	avtoker12 = 0
	avtoker13 = 0
	avtoker14 = 0
	avtoker15 = 0
	avtoker16 = 0
	avtoker17 = 0
	avtoker18 = 0
	avtoker19 = 0
	avtoker20 = 0

	for i in range(1, maxperiod1):
		hz = 0
		for j in range(len(p1)):
			hz += (p1[j] * a1[j])
			hz %= 2
		l1.append(a1[0])	
		for k in range(len(p1) - 1):
			a1[k] = a1[k + 1]	
		a1[23] = hz	
		if a1 == a0:
			break
	print(i)
	for i in l1:
		if len(bigrams) < 2:
			bigrams += str(i)
		else:
			if twgams.get(bigrams):
				twgams[bigrams] += 1
			else:	
				twgams[bigrams] = 1
			bigrams = str(i)	
	g = Counter(twgams)
	for key in g.keys():
		print('Bigramsp1', key , g[key])

	for i in l1:
		if len(threegrams) < 3:
			threegrams += str(i)
		else:
			if trgams.get(threegrams):
				trgams[threegrams] += 1
			else:	
				trgams[threegrams] = 1
			threegrams = str(i)				
	g = Counter(trgams)
	for key in g.keys():
		print('Threegramsp1', key , g[key])	
			
	for i in l1:
		if len(fourgrams) < 4:
			fourgrams += str(i)
		else:
			if frgams.get(fourgrams):
				frgams[fourgrams] += 1
			else:	
				frgams[fourgrams] = 1
			fourgrams = str(i)
	g = Counter(frgams)
	for key in g.keys():
		print('Fourgramsp1', key , g[key])		

	for i in l1:
		if len(fivegrams) < 5:
			fivegrams += str(i)
		else:
			if fvgams.get(fivegrams):
				fvgams[fivegrams] += 1
			else:	
				fvgams[fivegrams] = 1
			fivegrams = str(i)
	g = Counter(fvgams)
	for key in g.keys():
		print('Fivegramsp1', key , g[key])

	for i in range(len(l1)):
		avtoker1 += (l1[i] + l1[(i + 1)%len(l1)]) % 2
	for i in range(len(l1)):
		avtoker2 += (l1[i] + l1[(i + 2)%len(l1)]) % 2
	for i in range(len(l1)):
		avtoker3 += (l1[i] + l1[(i + 3)%len(l1)]) % 2
	for i in range(len(l1)):
		avtoker4 += (l1[i] + l1[(i + 4)%len(l1)]) % 2
	for i in range(len(l1)):
		avtoker5 += (l1[i] + l1[(i + 5)%len(l1)]) % 2
	for i in range(len(l1)):
		avtoker6 += (l1[i] + l1[(i + 6)%len(l1)]) % 2
	for i in range(len(l1)):
		avtoker7 += (l1[i] + l1[(i + 7)%len(l1)]) % 2
	for i in range(len(l1)):
		avtoker8 += (l1[i] + l1[(i + 8)%len(l1)]) % 2
	for i in range(len(l1)):
		avtoker9 += (l1[i] + l1[(i + 9)%len(l1)]) % 2
	for i in range(len(l1)):
		avtoker10 += (l1[i] + l1[(i + 10)%len(l1)]) % 2
	print("Avtoker1:",avtoker1," Avtoker2:",avtoker2," Avtoker3:",avtoker3," Avtoker4:",avtoker4," Avtoker5:",avtoker5," Avtoker6:",avtoker6," Avtoker7:",avtoker7," Avtoker8:",avtoker8," Avtoker9:",avtoker9," Avtoker10:",avtoker10)

	print("//////////////////////////////////////////////P2////////////////////////////////")

	for i in range(1, maxperiod2):
		hz = 0
		for j in range(len(p2)):
			hz += (p2[j] * a2[j])
			hz %= 2
		l2.append(a2[0])	
		for k in range(len(p2) - 1):
			a2[k] = a2[k + 1]	
		a2[19] = hz	
		if a2 == a00:
			break
	print(i)
	for i in l2:
		if len(bigrams2) < 2:
			bigrams2 += str(i)
		else:
			if twgams2.get(bigrams2):
				twgams2[bigrams2] += 1
			else:	
				twgams2[bigrams2] = 1
			bigrams2 = str(i)
	g = Counter(twgams2)
	for key in g.keys():
		print('Bigramsp2', key , g[key])

	for i in l2:
		if len(threegrams2) < 3:
			threegrams2 += str(i)
		else:
			if trgams2.get(threegrams2):
				trgams2[threegrams2] += 1
			else:	
				trgams2[threegrams2] = 1
			threegrams2 = str(i)
	g = Counter(trgams2)
	for key in g.keys():
		print('Threegramsp2', key , g[key])	
			
	for i in l2:
		if len(fourgrams2) < 4:
			fourgrams2 += str(i)
		else:
			if frgams2.get(fourgrams2):
				frgams2[fourgrams2] += 1
			else:	
				frgams2[fourgrams2] = 1
			fourgrams2 = str(i)
	g = Counter(frgams2)
	for key in g.keys():
		print('Fourgramsp2', key , g[key])

	for i in l2:
		if len(fivegrams2) < 5:
			fivegrams2 += str(i)
		else:
			if fvgams2.get(fivegrams2):
				fvgams2[fivegrams2] += 1
			else:	
				fvgams2[fivegrams2] = 1
			fivegrams2 = str(i)
	g = Counter(fvgams2)
	for key in g.keys():
		print('Fivegramsp2', key , g[key])

	for i in range(len(l2)):
		avtoker11 += (l2[i] + l2[(i + 1)%len(l2)]) % 2
	for i in range(len(l2)):
		avtoker12 += (l2[i] + l2[(i + 2)%len(l2)]) % 2
	for i in range(len(l2)):
		avtoker13 += (l2[i] + l2[(i + 3)%len(l2)]) % 2
	for i in range(len(l2)):
		avtoker14 += (l2[i] + l2[(i + 4)%len(l2)]) % 2
	for i in range(len(l2)):
		avtoker15 += (l2[i] + l2[(i + 5)%len(l2)]) % 2
	for i in range(len(l2)):
		avtoker16 += (l2[i] + l2[(i + 6)%len(l2)]) % 2
	for i in range(len(l2)):
		avtoker17 += (l2[i] + l2[(i + 7)%len(l2)]) % 2
	for i in range(len(l2)):
		avtoker18 += (l2[i] + l2[(i + 8)%len(l2)]) % 2
	for i in range(len(l2)):
		avtoker19 += (l2[i] + l2[(i + 9)%len(l2)]) % 2
	for i in range(len(l2)):
		avtoker20 += (l2[i] + l2[(i + 10)%len(l2)]) % 2
	print("Avtoker1:",avtoker11," Avtoker2:",avtoker12," Avtoker3:",avtoker13," Avtoker4:",avtoker14," Avtoker5:",avtoker15," Avtoker6:",avtoker16," Avtoker7:",avtoker17," Avtoker8:",avtoker18," Avtoker9:",avtoker19," Avtoker10:",avtoker20)
hz(p1, p2, a0, a1, a2, maxperiod1, maxperiod2)