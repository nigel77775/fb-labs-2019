#include "Header.h"
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <codecvt>

Bigram_info::Bigram_info(const std::wstring& input, bool readFromFile)
{
	// read from file if user want it, otherwise we interpret this line as input
	const std::wstring& str = !readFromFile ? input : readData(input);
	
	data.reserve(pow(rus_lang_symbols_size, 2));

	for (int i = 0; i < str.length() - 1; i++)
	{
		Bigram entry{ '\0', '\0' };

		// filling our pair of symbols
		int j = i;
		for (; entry.y == '\0' && i < str.length(); i++)
			if (str[i] >= L'à' && str[i] <= L'ÿ')
				if (entry.x == '\0')
					entry.x = str[i];
				else entry.y = str[i];
			else if (str[i] >= L'À' && str[i] <= L'ß')
				// set number to lower case
				if (entry.x == '\0')
					entry.x = str[i] - (L'A' - L'a');
				else entry.y = str[i] - (L'ß' - L'ÿ');
			else
				break;

		// reset i to prev value 
		i = j; //or j for 1 step

		// if pair of symbols invalid
		if (entry.y == '\0')
			continue;

		auto entity = data.find(Bigram_stat({ entry }));

		if (entity == data.end())
			data.insert({ { entry} , 0., 1 }); // create new item
		else
			entity->count++; // update existing one
	}

	// calculation is possible only after filling all pairs
	calculateFrequancy();
}

std::wstring Bigram_info::readData(const std::wstring & path)
{
	std::wifstream wif(path);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstringstream wss;
	wss << wif.rdbuf();
	return wss.str();
}

void Bigram_info::calculateFrequancy()
{
	std::size_t overall_count = 0;

	for (auto& entity : data)
		overall_count += entity.count;

	for (auto& entity : data)
		entity.frequancy = static_cast<double>(entity.count) / overall_count;
	
	for (auto& entity : data)	
		H2 = H2 - log(entity.frequancy) * entity.frequancy / log(2);
	
}

double Bigram_info::getCount(Bigram bigram)
{
	auto entity = data.find({ bigram });

	return (entity == data.end()) ? 0 : entity->count;
}

double Bigram_info::getFrequency(Bigram bigram)
{
	auto entity = data.find({ bigram });

	return (entity == data.end()) ? 0 : entity->frequancy;
}

void Bigram_info::printDetailedInfo()
{
	// this vector will be created only once per program run!!!
	static std::vector<Bigram_stat> sorted_array;
	
	// create vector so we can sort or elements by frequency
	// after second function call this block shall not executed
	if (sorted_array.size() == 0)
	{
		for (auto& el : data)
			sorted_array.push_back(el);

		std::sort(sorted_array.begin(), sorted_array.end(),
			[](const Bigram_stat & a, const Bigram_stat & b) -> bool
			{
				return a.frequancy > b.frequancy;
			});
	}

	for (auto& entity : sorted_array)
	{
		std::wcout << '"' << entity.self.x << entity.self.y << "\" ";
		std::wcout << "f: " << entity.frequancy * 100 << "% ";
		std::wcout << "c : " << entity.count << std::endl;
		
	}
	std::cout << std::setprecision(16);
	std::cout << H2/2 << std::endl;
}

bool Bigram_info::Bigram_stat::operator==(const Bigram_stat & other) const
{
	return self.x == other.self.x
		&& self.y == other.self.y;
}

std::size_t Bigram_info::KeyHasher::operator()(const Bigram_stat & k) const
{
	return k.self.x* k.self.y* k.self.y << k.self.x;
}
