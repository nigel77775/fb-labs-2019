#include <fstream>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream in("E:\\6.txt");
	ofstream out("E:\\a20.txt");
	string text;
	string key = { "КРАСИВАЯМУЛЬТИВАРКАК" };
	
	int num[20];
	for (int i = 0; i < key.length(); i++)
	{
		num[i] = int(key[i]) + 64;
		
	}
	
	if (in.is_open())
	{
		while (getline(in, text))
		{

		
			for (int i = 0; i < text.length(); i++)
			{
				for (int l = 0; l < key.length(); l++)
				{
					for (int j = l; j < text.length(); j +=key.length())
					{
						if (i == j)
						{
							
							text[i] = char(-32+int(text[i] + 256 + num[l]));// or - num for deshiphrator
								
						}

					}
			
				}
			}
			for (int i = 0; i < text.length(); i++)
			{
				if (char(int(text[i] + 256) <224)) {
					
					text[i] = char(int(text[i] + 256))+32;
				}
			}
			
		}
	}

	out << text;

	return 0;
}
