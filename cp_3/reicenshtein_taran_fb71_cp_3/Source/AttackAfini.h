#pragma once
int64_t find_pair(std::string pair_data, std::string pair)
{
	for (int i = 0; i < pair_data.length(); i += 2)
	{
		std::string pair_to_cmp = pair_data.substr(i, 2);
		if (pair_to_cmp == pair)
		{
			return i;
		}
	}
	return std::string::npos;
}

int get_occurrences(std::string data, std::string keyword)
{
	int counter = 0;
	int64_t position = 0;

	while ((position = data.find(keyword, position)) != std::string::npos)
	{
		counter++;
		position += keyword.length();
	}

	return counter;
}

void CheckKeys(std::string encrypted_data, int* a_ptr, int* b_ptr, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
	{
		if (a_ptr[i] != 0 && b_ptr[i] != 0)
		{
			std::string decrypted_data = EncryptDecryptAfini(encrypted_data, a_ptr[i], b_ptr[i], false);

			double data_size = decrypted_data.length();
			double a_occur = get_occurrences(decrypted_data, "а") / data_size;
			double e_occur = get_occurrences(decrypted_data, "е") / data_size;
			double o_occur = get_occurrences(decrypted_data, "о") / data_size;

			// 0.055 0.06 0.085 - found during deeeeeep tests
			if (a_occur >= 0.055 && e_occur >= 0.06 && o_occur >= 0.085)
			{
				std::cout << "Возможная пара ключей (a,b): " << a_ptr[i] << " " << b_ptr[i] << std::endl;
			}
		}
	}
}

void FindKeys(std::string pair, std::string pair2, int open_pair, int open_pair2, int** a_ptr, int** b_ptr, int* arr_size)
{
	int encrypted_number = mod((rus_alpha.find(pair[0]) * alpha_size + rus_alpha.find(pair[1])) - (rus_alpha.find(pair2[0]) * alpha_size + rus_alpha.find(pair2[1])), m);
	int decrypted_number = mod(open_pair - open_pair2, m);

	int array_size = 0;
	int* a_array = new int[m];
	int gcd = euclidean(decrypted_number, m, false);

	if (gcd == 1)
	{
		a_array[array_size++] = mod(encrypted_number * euclidean(decrypted_number, m, true), m);
	}
	else if (decrypted_number % gcd == 0)
	{
		int encrypted_gcd = encrypted_number / gcd;
		int decrypted_gcd = decrypted_number / gcd;
		int m_gcd = m / gcd;
		int x_0 = mod(encrypted_gcd * euclidean(decrypted_gcd, m_gcd, true), m_gcd);
		a_array[array_size++] = x_0;
		
		for (int i = 1; i < gcd; i++)
		{
			a_array[array_size++] = x_0 + (i * m_gcd);
		}
	}

	int* b_array = new int[array_size];
	int one_encrypted_pair = rus_alpha.find(pair[0]) * alpha_size + rus_alpha.find(pair[1]);

	for (int i = 0; i < array_size; i++)
	{
		b_array[i] = mod(one_encrypted_pair - a_array[i] * open_pair, m);
	}

	*a_ptr = a_array;
	*b_ptr = b_array;
	*arr_size = array_size;
}

std::string* find_max_bigramms(std::string data, int bigramms_count)
{
	// variables initialization
	std::string bigramms_data;
	int* occurrence_ptr = new int[data.length() / 2];
	//

	// getting all bigramms and its occurrences value
	for (int i = 0, j = 0; i < data.length(); i += 2)
	{
		std::string pair = data.substr(i, 2);

		if (pair.length() < 2)
		{
			break;
		}

		if (find_pair(bigramms_data, pair) == std::string::npos)
		{
			bigramms_data += pair;
			occurrence_ptr[j++] = get_occurrences(data, pair);
		}
	}
	//

	// getting max bigramms
	std::string* max_bigramms = new std::string[bigramms_count];
	std::string max_birgamm;

	for (int i = 0; i < bigramms_count; i++)
	{
		for (int j = 0, max_value = 0; j < bigramms_data.length() / 2; j++)
		{
			if (occurrence_ptr[j] > max_value)
			{
				max_value = occurrence_ptr[j];
				max_birgamm = bigramms_data.substr(j * 2, 2);
			}
		}
		max_bigramms[i] = max_birgamm;
		int pos = find_pair(bigramms_data, max_birgamm);
		occurrence_ptr[pos / 2] = 0;
	}
	//

	return max_bigramms;
}

void AttackAfini(std::string encrypted_data)
{
	// first stage, getting n max bigramms
	std::cout << "Атакуем Афины..." << std::endl;
	std::cout << "Ищем 5 самых повторяемых биграмм в зашифрованном тексте..." << std::endl;

	std::string* max_bigramms = find_max_bigramms(encrypted_data, 5);
	for (int i = 0; i < 5; i++)
	{
		std::cout << i+1 << " повторяющаяся биграмма: " << max_bigramms[i] << std::endl;
	}
	//

	// second stage, find all possible keys and trying to find the best keys xD (10 is the best for the magic_pairs, was found during the tests)
	std::cout << "Ищем всевозможные ключи используя статистику русского алфавита и немного магии..." << std::endl;
	std::cout << "Если выпадает много пар, в большинстве случаев нужно выбрать ту, которая повторилась больше всех, но так же не забывайте проверить и другие пары..." << std::endl;
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == j)
			{
				continue;
			}
			for (int k = 0; k < 21; k++)
			{
				for (int l = 0; l < 21; l++)
				{
					if (k == l)
					{
						continue;
					}
					int array_size = 0;
					int* a_array = NULL;
					int* b_array = NULL;
					FindKeys(max_bigramms[i], max_bigramms[j], magic_pairs[k], magic_pairs[l], &a_array, &b_array, &array_size);
 
					// Checking our keys and showing them if found
					CheckKeys(encrypted_data, a_array, b_array, array_size);
					//
				}
			}
		}
	}
	//

	std::cout << "Атака на Афины завершена, надеюсь вы нашли ключ :)" << std::endl;
}