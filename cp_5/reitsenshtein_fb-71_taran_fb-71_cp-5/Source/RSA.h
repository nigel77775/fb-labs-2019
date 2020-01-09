#pragma once

#include <boost/random/random_device.hpp>
#include <boost/random.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/integer/extended_euclidean.hpp>

namespace mp = boost::multiprecision;
namespace random = boost::random;
namespace euclidean = boost::integer;

class RSA
{
public:
	RSA() {}
	~RSA() {}

	std::vector<mp::cpp_int> GenerateKeyPair(mp::cpp_int range_min, mp::cpp_int range_max)
	{
		random::uniform_int_distribution<mp::cpp_int> get_number(range_min, range_max);

		mp::cpp_int primes[2];
		int k = 0;

		while (k != 2)
		{
			auto secret_number = get_number(generator);

			if (this->MillerRabin(secret_number))
			{
				primes[k++] = secret_number;
			}
		}
		
		std::cout << std::hex << std::uppercase << "p: " << primes[0] << std::endl << "q: " << primes[1] << std::endl;

		mp::cpp_int n = primes[0] * primes[1];

		mp::cpp_int euler = (primes[0] - 1) * (primes[1] - 1);

		random::uniform_int_distribution<mp::cpp_int> get_number2(2, euler - 1);

		mp::cpp_int e = 0, d = 0;

		while (true)
		{		
			auto e1_temp = get_number2(generator);

			auto euc_result = euclidean::extended_euclidean(e1_temp, euler);

			if (euc_result.gcd == 1)
			{
				e = e1_temp;
				d = mod(mp::cpp_int(euc_result.x), euler);
				break;
			}
		}
		
		std::vector<mp::cpp_int> pair;

		pair.push_back(e);
		pair.push_back(d);
		pair.push_back(n);

		return pair;
	}

	mp::cpp_int Encrypt(mp::cpp_int message, mp::cpp_int e, mp::cpp_int n)
	{
		return mp::powm(message, e, n);
	}

	mp::cpp_int Decrypt(mp::cpp_int encrypted_message, mp::cpp_int d, mp::cpp_int n)
	{
		return mp::powm(encrypted_message, d, n);
	}

	mp::cpp_int Sign(mp::cpp_int message, mp::cpp_int d, mp::cpp_int n)
	{
		return mp::powm(message, d, n);
	}

	mp::cpp_int Verify(mp::cpp_int signed_message, mp::cpp_int e, mp::cpp_int n)
	{
		return mp::powm(signed_message, e, n);
	}

	mp::cpp_int SendKey(mp::cpp_int key, mp::cpp_int d1, mp::cpp_int n1, mp::cpp_int e2, mp::cpp_int n2, mp::cpp_int* encrypted_sign)
	{
		auto signed_result = this->Sign(key, d1, n1);
		auto encrypted_sign_result = this->Encrypt(signed_result, e2, n2);
		auto encrypted_key_result = this->Encrypt(key, e2, n2);

		*encrypted_sign = encrypted_sign_result;

		return encrypted_key_result;
	}

	bool ReceiveKey(mp::cpp_int encrypted_key, mp::cpp_int encrypted_sign, mp::cpp_int d2, mp::cpp_int n2, mp::cpp_int e1, mp::cpp_int n1, mp::cpp_int* decrypted_key)
	{
		auto decrypted_key_result = this->Decrypt(encrypted_key, d2, n2);
		auto decrypted_sign_result = this->Decrypt(encrypted_sign, d2, n2);
		auto key = this->Verify(decrypted_sign_result, e1, n1);

		*decrypted_key = decrypted_key_result;

		if (key == decrypted_key_result)
		{
			return true;
		}
		
		return false;
	}

private:
	mp::cpp_int mod(mp::cpp_int a, mp::cpp_int b)
	{
		return (a % b + b) % b;
	}

	bool MillerRabin(mp::cpp_int secret_number)
	{
		if (secret_number % 2 == 0)
		{
			return false;
		}

		mp::cpp_int d = secret_number - 1;

		while (d % 2 == 0)
		{
			d /= 2;
		}

		// todo, not full number is used
		mp::cpp_int s(log((secret_number.convert_to<double>() - 1) / d.convert_to<double>()));
		//

		random::uniform_int_distribution<mp::cpp_int> get_number(2, secret_number - 2);

		for (int i = 0; i < miller_constant; i++)
		{
			auto a = get_number(generator);

			mp::cpp_int x = mp::powm(a, d, secret_number);

			if (x == 1 || x == secret_number - 1)
			{
				continue;
			}

			for (mp::cpp_int i = 0; i < s - 1; i++)
			{
				x = (x * x) % secret_number;

				if (x == 1)
				{
					return false;
				}
				else if (x == secret_number - 1)
				{
					break;
				}
			}

			if (x != secret_number - 1)
			{
				return false;
			}
		}
		return true;
	}
	
	// number out of my mind
	const int miller_constant = 9;
	//
	random::random_device generator;
};