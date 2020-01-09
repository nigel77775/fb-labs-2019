import math

num = raw_input('Enter the num: ')
alp_sum_str = raw_input('Space or not: ')
if (alp_sum_str == 'yes'):
    alp_sum = 32
if (alp_sum_str == 'no'):
    alp_sum = 31
num = float(num)
result = 1 - (num)/(math.log(32,2))

print(result)
