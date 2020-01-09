#include "Includes.h"
#include "TextFormatting.h"
#include "AfiniCrypto.h"
#include "AttackAfini.h"

int main()
{
	// setting console output to 1251 (russian ascii)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//

	// gathering info what to do
	std::cout << "Выберите что вы хотите сделать:\n1 - Зашифровать текст (Только UTF-8)\n2 - Расшифровать текст (Только Windows-1251)\n3 - Атака на Аффинный шифр (Только Windows-1251)\nВведите значение: ";
	std::string action;
	std::cin >> action;
	std::string a_string, b_string;
	if (action != "3")
	{
		std::cout << "Введите a: ";
		std::cin >> a_string;
		std::cout << "Введите b: ";
		std::cin >> b_string;
	}
	std::cout << "Введите название файла: ";
	std::string file_name;
	std::cin >> file_name;
	//

	// reading the file
	int64_t file_size = std::filesystem::file_size(file_name);
	char* file_data = (char*)malloc(file_size + 1);
	ZeroMemory(file_data, file_size + 1);
	FILE* file_ptr = NULL;
	fopen_s(&file_ptr, file_name.c_str(), "rb");
	fread(file_data, 1, file_size, file_ptr);
	fclose(file_ptr);
	//

	// doing actions
	if (action == "1")
	{
		// working with data
		std::wstring data_unicode = toUNICODE(file_data, file_size);
		std::string data_string = to1251(data_unicode);
		data_string = clear_the_text(data_string);
		std::ofstream cleared("cleared.txt");
		cleared << data_string;
		cleared.close();
		//

		// encrypting
		int a = atoi(a_string.c_str());
		int b = atoi(b_string.c_str());
		std::string data_encrypted = EncryptDecryptAfini(data_string, a, b, true);
		std::ofstream encrypted("encrypted.txt");
		encrypted << data_encrypted;
		encrypted.close();
		//

		// showing results
		std::cout << data_encrypted << std::endl;
		//
	}
	else if (action == "2")
	{
		// working with data
		std::string data_string(file_data);
		data_string = clear_the_text(data_string);
		std::ofstream cleared("cleared.txt");
		cleared << data_string;
		cleared.close();
		//

		// decrypting
		int a = atoi(a_string.c_str());
		int b = atoi(b_string.c_str());
		std::string data_decrypted = EncryptDecryptAfini(data_string, a, b, false);
		std::ofstream decrypted("decrypted.txt");
		decrypted << data_decrypted;
		decrypted.close();
		//

		// showing results
		std::cout << data_decrypted << std::endl;
		//
	}
	else if (action == "3")
	{
		// working with data
		std::string data_string(file_data);
		data_string = clear_the_text(data_string);
		//

		// attacking
		AttackAfini(data_string);
		//
	}
	//

	system("pause");
	return true;
}