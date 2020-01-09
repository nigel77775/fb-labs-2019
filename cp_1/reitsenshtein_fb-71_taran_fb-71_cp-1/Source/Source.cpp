#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

// russian alphabet
std::string alpha[32]
{
	"а","б","в","г","д","е","ж","з","и","й","к","л","м","н","о","п","р","с","т","у","ф","х","ц","ч","ш","щ","ы","ь","э","ю","я"," "
};
//

// functions
size_t find_pair(std::string, std::string);
std::wstring toUNICODE(void*, int64_t);
std::string to1251(std::wstring);
std::string clear_the_text(std::string);
int get_occurrences(std::string, std::string);

void get_monogramms_data(std::string, double**, double**, double*, double*, double*, double*);
void get_crossed_bigramm(std::string, std::string, std::string*, std::string*, double**, double**, double*, double*, double*, double*);
void get_ncrossed_bigramm(std::string, std::string, std::string*, std::string*, double**, double**, double*, double*, double*, double*);
//

int main()
{
	// setting console output to 1251 (russian ascii)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//

	// getting file name to parse
	std::string filename = "";
	std::cout << "Введите имя файла для обработки (Только UTF-8): ";
	std::cin >> filename;
	//

	// reading the file
	FILE* file_ptr = NULL;
	fopen_s(&file_ptr, filename.c_str(), "rb");
	int64_t file_size = std::experimental::filesystem::file_size(filename);
	char* data_ptr = (char*)malloc(file_size + 1);
	ZeroMemory(data_ptr, file_size + 1);
	fread(data_ptr, 1, file_size, file_ptr);
	fclose(file_ptr);
	//
	
	auto counter_start = std::chrono::high_resolution_clock::now();
	// converting to unicode
	std::wstring data_unicode = toUNICODE(data_ptr, file_size);
	//

	// converting to 1251
	std::string data_1251 = to1251(data_unicode);
	//

	// clearing the text
	std::string data = clear_the_text(data_1251);
	std::string data_ns = data;
	boost::replace_all(data_ns, " ", "");
	//
	auto counter_end = std::chrono::high_resolution_clock::now();
	double counter = double(std::chrono::duration_cast<std::chrono::milliseconds>(counter_end - counter_start).count()) / 1000;

	// writing the cleared files
	std::ofstream cleared("cleared.txt");
	cleared << data;
	cleared.close();
	std::ofstream cleared_ns("cleared_ns.txt");
	cleared_ns << data_ns;
	cleared_ns.close();
	//

	// getting monogramms
	double* monogramm_array = NULL, * monogramm_ns_array = NULL;
	double entropy = 0, entropy_ns = 0;
	double nadlishok = 0, nadlishok_ns = 0;
	counter_start = std::chrono::high_resolution_clock::now();
	get_monogramms_data(data, &monogramm_array, &monogramm_ns_array, &entropy, &entropy_ns, &nadlishok, &nadlishok_ns);
	counter_end = std::chrono::high_resolution_clock::now();
	counter += double(std::chrono::duration_cast<std::chrono::milliseconds>(counter_end - counter_start).count()) / 1000;

	std::cout << "Монограммы:\n";
	for (int i = 0; i < 32; i++)
	{
		std::cout << alpha[i] << ": " << std::fixed << std::setprecision(7) << monogramm_array[i] << std::endl;
	}
	std::cout << "H1 = " << std::fixed << std::setprecision(7) << entropy << std::endl;
	std::cout << "R1 = " << std::fixed << std::setprecision(7) << nadlishok << std::endl << std::endl;

	for (int i = 0; i < 31; i++)
	{
		std::cout << alpha[i] << ": " << std::fixed << std::setprecision(7) << monogramm_ns_array[i] << std::endl;
	}
	std::cout << "H1_ns = " << std::fixed << std::setprecision(7) << entropy_ns << std::endl;
	std::cout << "R1_ns = " << std::fixed << std::setprecision(7) << nadlishok_ns << std::endl << std::endl;
	//

	// getting bigramms
	double* bigramm_crossed = NULL, * bigramm_ns_scrossed = NULL;
	double bigramm_crossed_entropy = 0, bigramm_crossed_ns_entropy = 0;
	double bigramm_crossed_nadlishok = 0, bigram_crossed_ns_nadlishok = 0;
	std::string pairs_crossed, ns_pairs_crossed;
	counter_start = std::chrono::high_resolution_clock::now();
	get_crossed_bigramm(data, data_ns, &pairs_crossed, &ns_pairs_crossed, &bigramm_crossed, &bigramm_ns_scrossed, &bigramm_crossed_entropy, &bigramm_crossed_ns_entropy, &bigramm_crossed_nadlishok, &bigram_crossed_ns_nadlishok);
	counter_end = std::chrono::high_resolution_clock::now();
	counter += double(std::chrono::duration_cast<std::chrono::milliseconds>(counter_end - counter_start).count()) / 1000;

	std::cout << "Пересекающиеся биграммы:\n";
	for (int i = 0; i < 32; i++)
	{
		std::cout << "\t\t" << alpha[i];
	}
	std::cout << std::endl << std::endl;

	for (int i = 0; i < 32; i++)
	{
		std::cout << alpha[i] << "\t";
		for (int j = 0; j < 32; j++)
		{
			std::string pair = alpha[i] + alpha[j];
			size_t position = find_pair(pairs_crossed, pair);
			if (position != std::string::npos)
			{
				std::cout << std::fixed << std::setprecision(7) << bigramm_crossed[position / 2] << "\t";
			}
			else
			{
				std::cout << std::fixed << std::setprecision(7) << double(0) << "\t";
			}
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "H2 = " << std::fixed << std::setprecision(7) << bigramm_crossed_entropy << std::endl;
	std::cout << "R2 = " << std::fixed << std::setprecision(7) << bigramm_crossed_nadlishok << std::endl << std::endl;

	for (int i = 0; i < 31; i++)
	{
		std::cout << "\t\t" << alpha[i];
	}
	std::cout << std::endl << std::endl;

	for (int i = 0; i < 31; i++)
	{
		std::cout << alpha[i] << "\t";
		for (int j = 0; j < 31; j++)
		{
			std::string pair = alpha[i] + alpha[j];
			size_t position = find_pair(ns_pairs_crossed, pair);
			if (position != std::string::npos)
			{
				std::cout << std::fixed << std::setprecision(7) << bigramm_ns_scrossed[position / 2] << "\t";
			}
			else
			{
				std::cout << std::fixed << std::setprecision(7) << double(0) << "\t";
			}
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "H2_ns = " << std::fixed << std::setprecision(7) << bigramm_crossed_ns_entropy << std::endl;
	std::cout << "R2_ns = " << std::fixed << std::setprecision(7) << bigram_crossed_ns_nadlishok << std::endl << std::endl;
	//

	// getting ncrossed bigramms
	double* bigramm_ncrossed = NULL, * bigramm_ns_nscrossed = NULL;
	double bigramm_ncrossed_entropy = 0, bigramm_nscrossed_ns_entropy = 0;
	double bigramm_ncrossed_nadlishok = 0, bigram_ncrossed_ns_nadlishok = 0;
	std::string pairs, ns_pairs;
	counter_start = std::chrono::high_resolution_clock::now();
	get_ncrossed_bigramm(data, data_ns, &pairs, &ns_pairs, &bigramm_ncrossed, &bigramm_ns_nscrossed, &bigramm_ncrossed_entropy, &bigramm_nscrossed_ns_entropy, &bigramm_ncrossed_nadlishok, &bigram_ncrossed_ns_nadlishok);
	counter_end = std::chrono::high_resolution_clock::now();
	counter += double(std::chrono::duration_cast<std::chrono::milliseconds>(counter_end - counter_start).count()) / 1000;

	std::cout << "Не пересекающиеся биграммы:\n";
	for (int i = 0; i < 32; i++)
	{
		std::cout << "\t\t" << alpha[i];
	}
	std::cout << std::endl << std::endl;

	for (int i = 0; i < 32; i++)
	{
		std::cout << alpha[i] << "\t";
		for (int j = 0; j < 32; j++)
		{
			std::string pair = alpha[i] + alpha[j];
			size_t position = find_pair(pairs, pair);
			if (position != std::string::npos)
			{
				std::cout << std::fixed << std::setprecision(7) << bigramm_ncrossed[position / 2] << "\t";
			}
			else
			{
				std::cout << std::fixed << std::setprecision(7) << double(0) << "\t";
			}
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "H3 = " << std::fixed << std::setprecision(7) << bigramm_ncrossed_entropy << std::endl;
	std::cout << "R3 = " << std::fixed << std::setprecision(7) << bigramm_ncrossed_nadlishok << std::endl << std::endl;

	for (int i = 0; i < 31; i++)
	{
		std::cout << "\t\t" << alpha[i];
	}
	std::cout << std::endl << std::endl;

	for (int i = 0; i < 31; i++)
	{
		std::cout << alpha[i] << "\t";
		for (int j = 0; j < 31; j++)
		{
			std::string pair = alpha[i] + alpha[j];
			size_t position = find_pair(ns_pairs, pair);
			if (position != std::string::npos)
			{
				std::cout << std::fixed << std::setprecision(7) << bigramm_ns_nscrossed[position / 2] << "\t";
			}
			else
			{
				std::cout << std::fixed << std::setprecision(7) << double(0) << "\t";
			}
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "H3_ns = " << std::fixed << std::setprecision(7) << bigramm_nscrossed_ns_entropy << std::endl;
	std::cout << "R3_ns = " << std::fixed << std::setprecision(7) << bigram_ncrossed_ns_nadlishok << std::endl << std::endl;
	//

	// overall execution time
	std::cout << "Программа обработала файл за: " << counter << " секунд.\n";
	//

	system("pause");
	return 0;
}

size_t find_pair(std::string pairs_data, std::string pair)
{
	for (int i = 0; i < pairs_data.length(); i += 2)
	{
		std::string pair_to_cmp = pairs_data.substr(i, 2);
		if (pair == pair_to_cmp)
		{
			return i;
		}
	}
	return std::string::npos;
}

std::wstring toUNICODE(void* buffer, int64_t buffer_size)
{
	int64_t unicode_buffer_size = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)buffer, buffer_size, 0, 0) * sizeof(wchar_t) + 2;

	wchar_t* unicode_data_ptr = (wchar_t*)malloc(unicode_buffer_size);
	ZeroMemory(unicode_data_ptr, unicode_buffer_size);

	MultiByteToWideChar(CP_UTF8, 0, (LPCCH)buffer, buffer_size, unicode_data_ptr, unicode_buffer_size);

	std::wstring unicode_wstring(unicode_data_ptr);

	return unicode_wstring;
}

std::string to1251(std::wstring unicode_data)
{
	int64_t mb_buffer_size = WideCharToMultiByte(1251, 0, unicode_data.c_str(), unicode_data.length(), 0, 0, 0, 0) + 1;

	char* mb_data_ptr = (char*)malloc(mb_buffer_size);
	ZeroMemory(mb_data_ptr, mb_buffer_size);

	WideCharToMultiByte(1251, 0, unicode_data.c_str(), unicode_data.length(), mb_data_ptr, mb_buffer_size, 0, 0);

	std::string mb_string(mb_data_ptr);

	return mb_string;
}

std::string clear_the_text(std::string data)
{
	std::string data_ptr;

	for (int i = 0; i < data.length(); i++)
	{
		if (data[i] >= 'а' && data[i] <= 'я' || data[i] >= 'А' && data[i] <= 'Я' || data[i] == ' ')
		{
			data_ptr += data[i];
		}
	}

	boost::to_lower(data_ptr,std::locale(".1251"));
	boost::replace_all(data_ptr, "ё", "е");
	boost::replace_all(data_ptr, "ъ", "ь");
	data_ptr = boost::regex_replace(data_ptr, boost::regex("\\s+"), " ");

	if (data_ptr[0] == ' ')
	{
		data_ptr.erase(0);
	}
	if (data_ptr[data_ptr.length() - 1] == ' ')
	{
		data_ptr.erase(data_ptr.length() - 1);
	}

	return data_ptr;
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

void get_monogramms_data(std::string text, double** array_ptr, double** array_ns_ptr, double* entropy, double* entropy_ns, double* nadlishok, double* nadlishok_ns)
{
	// variables initialization
	double* freq = new double[32];
	double* freq_ns = new double[31];
	double monogramm_entropy = 0, monogramm_entropy_ns = 0;
	double monogramm_nadlishok = 0, monogramm_nadlishok_ns = 0;
	int monogramm_size = 0;
	//

	// getting freq
	for (int i = 0; i < 31; i++)
	{
		freq[i] = get_occurrences(text, alpha[i]);
		freq_ns[i] = freq[i];
		monogramm_size += freq[i];
	}
	freq[31] = get_occurrences(text, alpha[31]);

	for (int i = 0; i < 31; i++)
	{
		freq_ns[i] /= monogramm_size;
	}

	monogramm_size += freq[31];

	for (int i = 0; i < 32; i++)
	{
		freq[i] /= monogramm_size;
	}
	//

	// getting entropy
	for (int i = 0; i < 31; i++)
	{
		if (freq[i] != 0)
		{
			monogramm_entropy += freq[i] * log2(freq[i]);
		}

		if (freq_ns[i] != 0)
		{
			monogramm_entropy_ns += freq_ns[i] * log2(freq_ns[i]);
		}
	}
	if (freq[31] != 0)
	{
		monogramm_entropy += freq[31] * log2(freq[31]);
	}
	monogramm_entropy *= (-1);
	monogramm_entropy_ns *= (-1);
	//

	// getting nadlishok
	monogramm_nadlishok = double(1 - monogramm_entropy / log2(32));
	monogramm_nadlishok_ns = double(1 - monogramm_entropy_ns / log2(31));
	//

	// finalizing
	*array_ptr = freq;
	*array_ns_ptr = freq_ns;
	*entropy = monogramm_entropy;
	*entropy_ns = monogramm_entropy_ns;
	*nadlishok = monogramm_nadlishok;
	*nadlishok_ns = monogramm_nadlishok_ns;
	//
}

void get_crossed_bigramm(std::string text, std::string text_ns, std::string* pairs, std::string* pairs_ns, double** array_ptr, double** array_ns_ptr, double* entropy, double* entropy_ns, double* nadlishok, double* nadlishok_ns)
{
	// variables initialization
	std::string bigram_pairs, bigram_ns_pairs;
	double* freq = new double[32 * 32];
	double* freq_ns = new double[31 * 31];
	double bigram_entropy = 0, bigram_ns_entropy = 0;
	double bigram_nadlishok = 0, bigram_ns_nadlishok = 0;
	int bigram_size = 0, bigram_ns_size = 0;
	//

	// getting freq
	for (int i = 0, j = -1; i < text.length(); i++)
	{
		std::string pair = text.substr(i, 2);

		if (find_pair(bigram_pairs, pair) == std::string::npos)
		{
			bigram_pairs += pair;
			freq[++j] = get_occurrences(text, pair);
			bigram_size += freq[j];
		}
	}
	for (int i = 0, j = -1; i < text_ns.length(); i++)
	{
		std::string pair = text_ns.substr(i, 2);

		if (find_pair(bigram_ns_pairs, pair) == std::string::npos)
		{
			bigram_ns_pairs += pair;
			freq_ns[++j] = get_occurrences(text_ns, pair);
			bigram_ns_size += freq_ns[j];
		}
	}
	for (int i = 0; i < bigram_pairs.length() / 2; i++)
	{
		freq[i] /= bigram_size;
	}
	for (int i = 0; i < bigram_ns_pairs.length() / 2; i++)
	{
		freq_ns[i] /= bigram_ns_size;
	}
	//

	// getting entropy
	for (int i = 0; i < bigram_pairs.length() / 2; i++)
	{
		if (freq[i] != 0)
		{
			bigram_entropy += freq[i] * log2(freq[i]);
		}
	}
	for (int i = 0; i < bigram_ns_pairs.length() / 2; i++)
	{
		if (freq_ns[i] != 0)
		{
			bigram_ns_entropy += freq_ns[i] * log2(freq_ns[i]);
		}
	}
	bigram_entropy *= (-1);
	bigram_ns_entropy *= (-1);
	bigram_entropy /= 2;
	bigram_ns_entropy /= 2;
	//

	// getting nadlishok
	bigram_nadlishok = double(1 - bigram_entropy / log2(32));
	bigram_ns_nadlishok = double(1 - bigram_ns_entropy / log2(31));
	//

	// finalyzing
	*array_ptr = freq;
	*array_ns_ptr = freq_ns;
	*pairs = bigram_pairs;
	*pairs_ns = bigram_ns_pairs;
	*entropy = bigram_entropy;
	*entropy_ns = bigram_ns_entropy;
	*nadlishok = bigram_nadlishok;
	*nadlishok_ns = bigram_ns_nadlishok;
	//
}

void get_ncrossed_bigramm(std::string text, std::string text_ns, std::string* pairs, std::string* pairs_ns, double** array_ptr, double** array_ns_ptr, double* entropy, double* entropy_ns, double* nadlishok, double* nadlishok_ns)
{
	// variables initialization
	std::string bigram_pairs, bigram_ns_pairs;
	double* freq = new double[32 * 32];
	double* freq_ns = new double[31 * 31];
	double bigram_entropy = 0, bigram_ns_entropy = 0;
	double bigram_nadlishok = 0, bigram_ns_nadlishok = 0;
	int bigram_size = 0, bigram_ns_size = 0;
	//

	// getting freq
	for (int i = 0, j = -1; i < text.length(); i+=2)
	{
		std::string pair = text.substr(i, 2);

		if (find_pair(bigram_pairs, pair) == std::string::npos)
		{
			bigram_pairs += pair;
			freq[++j] = get_occurrences(text, pair);
			bigram_size += freq[j];
		}
	}
	for (int i = 0, j = -1; i < text_ns.length(); i+=2)
	{
		std::string pair = text_ns.substr(i, 2);

		if (find_pair(bigram_ns_pairs, pair) == std::string::npos)
		{
			bigram_ns_pairs += pair;
			freq_ns[++j] = get_occurrences(text_ns, pair);
			bigram_ns_size += freq_ns[j];
		}
	}
	for (int i = 0; i < bigram_pairs.length() / 2; i++)
	{
		freq[i] /= bigram_size;
	}
	for (int i = 0; i < bigram_ns_pairs.length() / 2; i++)
	{
		freq_ns[i] /= bigram_ns_size;
	}
	//

	// getting entropy
	for (int i = 0; i < bigram_pairs.length() / 2; i++)
	{
		if (freq[i] != 0)
		{
			bigram_entropy += freq[i] * log2(freq[i]);
		}
	}
	for (int i = 0; i < bigram_ns_pairs.length() / 2; i++)
	{
		if (freq_ns[i] != 0)
		{
			bigram_ns_entropy += freq_ns[i] * log2(freq_ns[i]);
		}
	}
	bigram_entropy *= (-1);
	bigram_ns_entropy *= (-1);
	bigram_entropy /= 2;
	bigram_ns_entropy /= 2;
	//

	// getting nadlishok
	bigram_nadlishok = double(1 - bigram_entropy / log2(32));
	bigram_ns_nadlishok = double(1 - bigram_ns_entropy / log2(31));
	//

	// finalyzing
	*array_ptr = freq;
	*array_ns_ptr = freq_ns;
	*pairs = bigram_pairs;
	*pairs_ns = bigram_ns_pairs;
	*entropy = bigram_entropy;
	*entropy_ns = bigram_ns_entropy;
	*nadlishok = bigram_nadlishok;
	*nadlishok_ns = bigram_ns_nadlishok;
	//
}