import os
import re
import sys

def parse(filepath, keep_spaces=False):


	raw_data = ''
	parsed_data = ''

	parsed_file_path = os.path.splitext(filepath)[0] + '_parsed.txt'


	with open(filepath, 'r', encoding='utf8') as start_file:

		raw_data = start_file.read()
	
	if keep_spaces:
		raw_data = ' '.join(raw_data.split())			# Substitute whitespace characters with spaces

	for symbol in raw_data:

		symbol = symbol.lower()
		if keep_spaces:
			matched = re.match(r'^[а-я ]$', symbol) 	# Only keep russian symbols and spaces
		else:
			matched = re.match(r'^[а-я]$', symbol)		# Only keep russian symblos

		if matched:

			symbol = matched.group(0)

			if symbol == 'ё':
				symbol = 'е'

			#if symbol == 'ъ':
			#	symbol = 'ь'

			parsed_data += symbol

	if keep_spaces:
		parsed_data = ' '.join(parsed_data.split())		# Substitute whitespace characters after filtering


	with open(parsed_file_path, 'w', encoding='utf8') as parsed_file:

		parsed_file.write(parsed_data)


	print('Data parsed to \'' + parsed_file_path + '\'')	




def main():

	filepath = sys.argv[1]
	keep_spaces = False

	
	if len(sys.argv) > 2:
		if sys.argv[2] == '-ks':
			keep_spaces = True
	

	parse(filepath, keep_spaces)


main()