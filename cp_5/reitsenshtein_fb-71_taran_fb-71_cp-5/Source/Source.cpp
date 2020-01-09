#include <iostream>
#include <fstream>
#include "RSA.h"

int main()
{
	RSA* crypto_provider = new RSA();


	std::vector<mp::cpp_int> first_pair = crypto_provider->GenerateKeyPair(mp::pow(mp::cpp_int(2), 255), mp::pow(mp::cpp_int(2), 256));
	std::vector<mp::cpp_int> second_pair = crypto_provider->GenerateKeyPair(mp::pow(mp::cpp_int(2), 255), mp::pow(mp::cpp_int(2), 256));

	for (int i = 0; i < 3; i++)
	{
		std::cout << "Abonent A keys: " << first_pair[i] << std::endl;
	}

	for (int i = 0; i < 3; i++)
	{
		std::cout << "Abonent B keys: " << second_pair[i] << std::endl;
	}

	std::cout << std::endl;

	auto result = crypto_provider->Encrypt(0x1337, first_pair[0], first_pair[2]);
	std::cout << "Encryption with A keys: " << result << std::endl;
	result = crypto_provider->Decrypt(result, first_pair[1], first_pair[2]);
	std::cout << "Decryption with A keys: " << result << std::endl;

	result = crypto_provider->Encrypt(0x1337, second_pair[0], second_pair[2]);
	std::cout << "Encryption with B keys: " << result << std::endl;
	result = crypto_provider->Decrypt(result, second_pair[1], second_pair[2]);
	std::cout << "Decryption with B keys: " << result << std::endl;

	std::cout << std::endl;

	auto sign_result = crypto_provider->Sign(0x1337, first_pair[1], first_pair[2]);
	std::cout << "Sign result with A keys: " << sign_result << std::endl;
	std::cout << "Verify sign returned " << crypto_provider->Verify(sign_result, first_pair[0], first_pair[2]) << std::endl;

	sign_result = crypto_provider->Sign(0x1337, second_pair[1], second_pair[2]);
	std::cout << "Sign result with B keys: " << sign_result << std::endl;
	std::cout << "Verify sign returned " << crypto_provider->Verify(sign_result, second_pair[0], second_pair[2]) << std::endl;

	std::cout << std::endl;

	mp::cpp_int key = 0x16384;
	mp::cpp_int encrypted_sign = 0;
	mp::cpp_int encrypted_key = 0;

	std::cout << "Our secret decrypted key to send: " << key << std::endl;

	if (first_pair[2] <= second_pair[2])
	{
		encrypted_key = crypto_provider->SendKey(key, first_pair[1], first_pair[2], second_pair[0], second_pair[2], &encrypted_sign);
		std::cout << "Encrypted sign: " << encrypted_sign << std::endl << "Encrypted key: "
			<< encrypted_key << std::endl;

		mp::cpp_int decrypted_key = 0;

		auto recieve_result = crypto_provider->ReceiveKey(encrypted_key, encrypted_sign, second_pair[1], second_pair[2], first_pair[0], first_pair[2], &decrypted_key);

		if (recieve_result)
		{
			std::cout << "Receiving the key returned true.\nThe decrypted key is: " << decrypted_key << std::endl;
		}
		else
		{
			std::cout << "Receiving the key returned false.\nThe decrypted key is: " << decrypted_key << std::endl;
		}
	}
	else
	{
		encrypted_key = crypto_provider->SendKey(key, second_pair[1], second_pair[2], first_pair[0], first_pair[2], &encrypted_sign);
		std::cout << "Encrypted sign: " << encrypted_sign << std::endl << "Encrypted key: "
			<< encrypted_key << std::endl;

		mp::cpp_int decrypted_key = 0;

		auto recieve_result = crypto_provider->ReceiveKey(encrypted_key, encrypted_sign, first_pair[1], first_pair[2], second_pair[0], second_pair[2], &decrypted_key);

		if (recieve_result)
		{
			std::cout << "Receiving the key returned true.\nThe decrypted key is: " << decrypted_key << std::endl;
		}
		else
		{
			std::cout << "Receiving the key returned false.\nThe decrypted key is: " << decrypted_key << std::endl;
		}
	}
	
	system("pause");

	return true;
}