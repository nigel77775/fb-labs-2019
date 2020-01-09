#include <Windows.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

// Calculated constants
const int l1_size = 258;
const int l1_criteria = 81;
const int l2_size = 265;
const int l2_criteria = 83;
const int l3_size = 272;
//

struct ThreadData
{
	unsigned long long start;
	unsigned long long end;
	FILE* file_ptr;
};

CRITICAL_SECTION thread_cs;
std::string input_data = "";
std::string final_l1 = "", final_l2 = "", final_l3 = "";

std::vector<std::string> final_data_l1;
std::vector<std::string> final_data_l2;

void ThreadCreator(void* func_addr, int pow_num, int threads_count, const char* file_name);
void l1_calc(ThreadData* struct_ptr);
void l2_calc(ThreadData* struct_ptr);
void l3_calc();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	InitializeCriticalSection(&thread_cs);

	std::string input_filename = "";
	std::cout << "Введите название файла с входящей последовательностью: ";
	std::cin >> input_filename;

	std::string num_of_threads = "";
	std::cout << "Введите количество потоков (будьте осторожны, слишком большое число может сильно нагрузить ваш процессор): ";
	std::cin >> num_of_threads;

	int threads_count = atoi(num_of_threads.c_str());

	std::ifstream input_sequence(input_filename);
	input_sequence >> input_data;
	input_sequence.close();

	std::cout << "1. Посчитать L1\n2. Посчитать L2\n3. Посчитать L3\n4. Посчитать всё\nЧто вы хотите сделать: ";
	std::string action = "";
	std::cin >> action;

	if (action == "1" || action == "4")
	{
		std::cout << "Поиск подходящих L1..." << std::endl;

		ThreadCreator(l1_calc, 30, threads_count, "l1.txt");

		std::cout << "Последовательности L1:" << std::endl;

		for (int i = 0; i < final_data_l1.size(); i++)
		{
			std::cout << final_data_l1[i] << std::endl;
		}
	}

	if (action == "2" || action == "4")
	{
		std::cout << "Поиск подходящих L2..." << std::endl;

		ThreadCreator(l2_calc, 31, threads_count, "l2.txt");

		std::cout << "Последовательности L2:" << std::endl;

		for (int i = 0; i < final_data_l2.size(); i++)
		{
			std::cout << final_data_l2[i] << std::endl;
		}
	}

	if (action == "3" || action == "4")
	{
		if (action != "4")
		{
			std::string file_name_l1 = "", file_name_l2 = "";
			std::cout << "Введите название файла с последовательностями L1: ";
			std::cin >> file_name_l1;
			std::cout << "Введите название файла с последовательностями L2: ";
			std::cin >> file_name_l2;

			std::ifstream l1_data(file_name_l1);
			std::ifstream l2_data(file_name_l2);

			while (!l1_data.eof())
			{
				std::string temp = "";
				l1_data >> temp;
				
				if (temp[0] != '\n')
				{
					final_data_l1.push_back(temp);
				}
			}
			l1_data.close();

			while (!l2_data.eof())
			{
				std::string temp = "";
				l2_data >> temp;

				if (temp[0] != '\n')
				{
					final_data_l2.push_back(temp);
				}
			}
			l2_data.close();
		}

		std::cout << "Генерация L3 относительно L1 и L2..." << std::endl;
		
		l3_calc();
	}

	std::cout << "Финальные последовательности L1,L2,L3:" << std::endl;
	std::cout << "L1: " << final_l1 << std::endl;
	std::cout << "L2: " << final_l2 << std::endl;
	std::cout << "L3: " << final_l3 << std::endl;

	system("pause");

	return true;
}

void ThreadCreator(void* func_addr, int pow_num, int threads_count, const char* file_name)
{
	unsigned long long l_start = pow(2, pow_num);
	unsigned long long l_per_thread = l_start / threads_count;

	DWORD ThreadID = NULL;
	HANDLE* hThreads = new HANDLE[threads_count];

	FILE* file_ptr = NULL;
	fopen_s(&file_ptr, file_name, "wb");

	for (int i = 0; i < threads_count; i++)
	{
		ThreadData* l_data = new ThreadData();
		l_data->start = l_per_thread * i;
		l_data->end = l_per_thread * (i + 1);
		l_data->file_ptr = file_ptr;
		hThreads[i] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)func_addr, l_data, NULL, &ThreadID);
	}

	WaitForMultipleObjects(threads_count, hThreads, TRUE, INFINITE);
	
	fclose(file_ptr);
}

void l1_calc(ThreadData* struct_ptr)
{
	for (unsigned long long i = struct_ptr->start; i < struct_ptr->end; i++)
	{
		std::string bitset_string = std::bitset<30>(i).to_string();

		for (int j = 0; j < l1_size - 30; j++)
		{
			bitset_string += ((bitset_string[j] ^ bitset_string[j + 1] ^ bitset_string[j + 4] ^ bitset_string[j + 6]) + 0x30);
		}

		int R = 0;

		for (int j = 0; j < l1_size; j++)
		{
			R += (bitset_string[j] ^ input_data[j]);
		}

		if (R < l1_criteria)
		{
			EnterCriticalSection(&thread_cs);
			final_data_l1.push_back(bitset_string);
			fputs(bitset_string.c_str(), struct_ptr->file_ptr);
			fputs("\n", struct_ptr->file_ptr);
			LeaveCriticalSection(&thread_cs);
		}
	}

	ExitThread(NULL);
}

void l2_calc(ThreadData* struct_ptr)
{
	for (unsigned long long i = struct_ptr->start; i < struct_ptr->end; i++)
	{
		std::string bitset_string = std::bitset<31>(i).to_string();

		for (int j = 0; j < l2_size - 31; j++)
		{
			bitset_string += ((bitset_string[j] ^ bitset_string[j + 3]) + 0x30);
		}

		int R = 0;

		for (int j = 0; j < l2_size; j++)
		{
			R += (bitset_string[j] ^ input_data[j]);
		}

		if (R < l2_criteria)
		{
			EnterCriticalSection(&thread_cs);
			final_data_l2.push_back(bitset_string);
			fputs(bitset_string.c_str(), struct_ptr->file_ptr);
			fputs("\n", struct_ptr->file_ptr);
			LeaveCriticalSection(&thread_cs);
		}
	}

	ExitThread(NULL);
}

void l3_calc()
{
	final_l1 = final_data_l1[0];

	// finding l2
	for (int j = 0; j < final_data_l2.size(); j++)
	{
		for (int k = 0; k < l1_size; k++)
		{
			if (final_l1[k] != input_data[k] && final_data_l2[j][k] != input_data[k])
			{
				break;
			}

			if (k == l1_size - 1)
			{
				final_l2 = final_data_l2[j];
			}
		}
	}
	//

	// calculating l3
	std::string l3_generated = "";
	for (int i = 0; i < 32; i++)
	{
		if (final_l1[i] == input_data[i] && final_l2[i] == input_data[i])
		{
			l3_generated += "?";
		}
		else if (final_l1[i] == input_data[i])
		{
			l3_generated += "1";
		}
		else if (final_l2[i] == input_data[i])
		{
			l3_generated += "0";
		}
	}
	//

	// l3 brute-force
	// 18 unknown bits found during testing our sequence ?
	unsigned long long l3_start = pow(2, 18);
	//

	for (unsigned long long i = 0; i < l3_start; i++)
	{
		std::string bitset_string = std::bitset<18>(i).to_string();
		
		std::string l3_not_full = l3_generated;

		for (int j = 0, k = 0; j < 32; j++)
		{
			if (l3_not_full[j] == '?')
			{
				l3_not_full[j] = bitset_string[k++];
			}
		}

		for (int l = 0; l < l3_size - 32; l++)
		{
			l3_not_full += ((l3_not_full[l] ^ l3_not_full[l + 1] ^ l3_not_full[l + 2] ^ l3_not_full[l + 3] ^ l3_not_full[l + 5] ^ l3_not_full[l + 7]) + 0x30);
		}

		for (int m = 0; m < l1_size; m++)
		{
			if (l3_not_full[m] == '1' && final_l1[m] == input_data[m] || l3_not_full[m] == '0' && final_l2[m] == input_data[m] || final_l1[m] == final_l2[m])
			{
				if (m == l1_size - 1)
				{
					final_l3 = l3_not_full;
				}
				continue;
			}
			break;
		}
	}
	//
}