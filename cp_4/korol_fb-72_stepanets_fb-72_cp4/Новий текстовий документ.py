import  threading
from time import time
PL1 = [1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1] #x20 has to to be the Sum of others that meens that x20 has to zero
PL2 = [0,0,1,0,0,0,0,0,1,1,0,0,1,0,1,1,0,0,1,1,1,0,0,1]#used to be degree 25 but polinom meens that he coef near to hirest degree if the sum of priviost,so just dont using it

def Linear_shift_register1(moment):
	sum_of_moment = 0
	for i in range(len(PL1)):
		if PL1[i] == 1:
			sum_of_moment += moment[i]
	return  [sum_of_moment % 2] + moment[:-1]

def Linear_shift_register2(moment):
	sum_of_moment = 0
	for i in range(len(PL2)):
		if PL2[i] == 1:
			sum_of_moment += moment[i]
	return [sum_of_moment % 2] + moment[:-1]

def CreateImpulse(lenght):
	impulse = [0] *(lenght - 1)
	impulse.append(1)
	return impulse

def Calculating_period(polinom):
	sequence = "0"
	initial_state = CreateImpulse(len(polinom))
	count = 1
	if len(initial_state) > 20:
	 	new_state = Linear_shift_register2(initial_state)
	 	while  new_state != initial_state:
	 		sequence += str(new_state[0])
	 		new_state = Linear_shift_register2(new_state)
	 		count += 1
	else:
		new_state = Linear_shift_register1(initial_state)
		while new_state != initial_state:
			sequence += str(new_state[0])
			new_state = Linear_shift_register1(new_state)
			count += 1
	print(count)
	return  (polinom ,count,sequence)

def Polinom_description(polinom,count):
	print(f"{polinom},Current period: {count}, MAX- Period:{(2 ** len(polinom)) - 1  }")
	if (2 ** len(polinom)) - 1  == count:
		print("Primary polinom")
	elif ((2 ** len(polinom)) - 1 ) % count == 0:
		print("NEPRIVODIMUY polinom")
	else:
		print("POLINOM IS COULD BE BOTH VARs")


def sum_of_two_shifts(i,j):
	return (sequence[j] + sequence[(j + i) % period]) %2

def Auto(polinom,d,period,sequence):
	print(period,len(sequence))
	Dictionary = {i + 1: 0 for i in range(d)}
	for i in Dictionary.keys():
		for j in range(period):
			Dictionary[i] += (int(sequence[j]) + int(sequence[(i + j) % period])) % 2
	print(Dictionary)

def  Destribute(polinom,k,sequence):
	frequences = {}
	for i in range(0,len(sequence),k):
		if str(sequence[i:i + k]) in frequences:
			frequences[str(sequence[i:i + k])] += 1
		else:
			frequences[str(sequence[i:i + k])] = 1
	print(frequences)

start = time()
tpl = Calculating_period(PL1)
task1 =  threading.Thread(target = Destribute, args = (PL1,1,tpl[2]))
task1.start()
task2 = threading.Thread(target = Auto, args = (PL1,10,tpl[1],tpl[2]))
task2.start()
tpl2 = Calculating_period(PL2)
task3 =  threading.Thread(target = Destribute, args = (PL2,1,tpl2[2]))
task3.start()
task4 = threading.Thread(target = Auto, args = (PL2,10,tpl2[1],tpl2[2]))
task4.start()
task4.join()
end = time()
print(f"ВРЕМЯ РАБОТЫ:{end - start}")
#task5 = threading.Thread(target = Auto, args = (PL2,10,tpl2[1],tpl2[2]))
#task5.start()
