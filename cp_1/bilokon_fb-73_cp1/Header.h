#pragma once
#include <iostream>
#include <unordered_set>
#include <array>

struct Bigram
{
	wchar_t x;
	wchar_t y;
};

class Bigram_info
{

public:
	double H2 = 0;
	Bigram_info(const std::wstring& input, bool readFromFile = false);

	double getCount(Bigram bigram);

	double getFrequency(Bigram bigram);

	void printDetailedInfo();

private:

	class Bigram_stat
	{
	public:
		Bigram self = { '\0', '\0' };
		mutable double frequancy = 0;
		mutable unsigned int count = 0;
		
		bool operator==(const Bigram_stat& other) const;
	};

	struct KeyHasher
	{
		std::size_t operator()(const Bigram_stat& k) const;
	};

	void calculateFrequancy();

	std::wstring readData(const std::wstring& path);

	std::unordered_set<Bigram_stat, KeyHasher> data;
	static constexpr int rus_lang_symbols_size = 33;
};