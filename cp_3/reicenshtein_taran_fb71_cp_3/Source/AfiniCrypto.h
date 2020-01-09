#pragma once
int mod(int a, int b)
{
	return (a % b + b) % b;
}

struct euclidean_data
{
	long x;
	long y;
	long gcd;
};

long extended_euclidean(int a, int b, long* x, long* y)
{
	if (a == 0)
	{
		*x = 0;
		*y = 1;
		return b;
	}

	long x_temp = 0, y_temp = 0;
	long gcd = extended_euclidean(b % a, a, &x_temp, &y_temp);

	*x = y_temp - (b / a) * x_temp;
	*y = x_temp;

	return gcd;
}

euclidean_data* euclidean_struct(int a, int b)
{
	euclidean_data* result = new euclidean_data();

	result->gcd = extended_euclidean(a, b, &result->x, &result->y);

	return result;
}

int euclidean(int a, int b, bool is_obernene)
{
	auto result = euclidean_struct(a, b);

	if (is_obernene)
	{
		return mod(result->x, b);
	}
	else
	{
		return result->gcd;
	}
}

std::string encryptFunction(std::string pair, int a, int b)
{
	std::string encrypted_pair;
	int firstpos = rus_alpha.find(pair[0]);
	int secondpos = rus_alpha.find(pair[1]);
	int decrypted_number = firstpos * alpha_size + secondpos;
	int encrypted_number = mod(a * decrypted_number + b, m);

	for (int i = 0; i < alpha_size; i++)
	{
		for (int j = 0; j < alpha_size; j++)
		{
			if ((i * alpha_size + j) == encrypted_number)
			{
				encrypted_pair += rus_alpha[i];
				encrypted_pair += rus_alpha[j];
				return encrypted_pair;
			}
		}
	}

	return "";
}

std::string decryptFunction(std::string pair, int a, int b)
{
	std::string decrypted_pair;
	int a_reversed = euclidean(a, m, true);
	int firstpos = rus_alpha.find(pair[0]);
	int secondpos = rus_alpha.find(pair[1]);
	int encrypted_number = firstpos * alpha_size + secondpos;
	int decrypted_number = mod(a_reversed * (encrypted_number - b), m);

	for (int i = 0; i < alpha_size; i++)
	{
		for (int j = 0; j < alpha_size; j++)
		{
			if ((i * alpha_size + j) == decrypted_number)
			{
				decrypted_pair += rus_alpha[i];
				decrypted_pair += rus_alpha[j];
				return decrypted_pair;
			}
		}
	}

	return "";
}

std::string EncryptDecryptAfini(std::string data, int a, int b, bool is_encryptmode)
{
	std::string final_data;

	for (int i = 0; i < data.length(); i += 2)
	{
		std::string pair = data.substr(i, 2);

		if (pair.length() < 2)
		{
			final_data += pair;
			break;
		}

		if (is_encryptmode)
		{
			final_data += encryptFunction(pair, a, b);
		}
		else
		{	
			final_data += decryptFunction(pair, a, b);
		}
	}

	return final_data;
}