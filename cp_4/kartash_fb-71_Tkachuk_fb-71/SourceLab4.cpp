#include<iostream>
#include<string>
#include<cmath>
#include <fstream>
#include<vector>
#include<map>
using namespace std;
/*последовательность коэффициентов заносяться в DataInput 
БОЛЬШЕ НИЧЕГО МЕНЯТЬ НЕ НУЖНО*/
int autokorel(string DataOutput, int period, int step) {
	int korell = 0;
	for (int i = 0; i < period; i++)
	{
		korell += (DataOutput[i] + DataOutput[(i + step) % period]) % 2;
	}
	return korell;
}

void NgrammLink(map<string, int> mymap, string text, int length) {
	for (int i = length; i <= text.size(); i += length) {
		string a = "";
		a = text.substr(i - length, length);
		mymap[a]++;
	}

	///
	map <string, int> ::iterator its = mymap.begin();
	for (int i = 0; its != mymap.end(); its++, i++) {  // выводим их
		std::cout << i << ") N-gramma " << its->first << " link " << its->second << endl;
	}
}

int main() {
	map<string, int> mymap;
	vector<int>DataInput = { 1,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,1 };//P1
	//vector<int>DataInput = { 1,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1 };//P2
	string DataOutput ="";
	vector<int>Buffer(DataInput.size());
	vector<int>ImpulsFunk(DataInput.size()-1);
	ImpulsFunk.push_back(1);
	vector<int> ImpulsFunk2(ImpulsFunk);
	int result[2][2] = {0};
	string bits = "01";
	int k = 0;
	do{
		int sum = 0;
		for (int i = 0; i < DataInput.size(); i++) {
			Buffer[i] = DataInput[i] * ImpulsFunk2[i];
			sum += Buffer[i];
		}
		ImpulsFunk2.push_back(sum % 2);
		DataOutput+=to_string(ImpulsFunk2[0]);
		k++;
		//cout <<k;
		ImpulsFunk2.erase(ImpulsFunk2.begin());
		// вывод импульсной последовательности которая меняется
		/*for (int n : ImpulsFunk2)
		{
			std::cout << n;
		}
		cout << endl;*/
	} while (ImpulsFunk2 != ImpulsFunk);
	cout << k<<endl;
	for (int i = 1; i <=10; i++) {
		cout << "Step"<<i<<": " << autokorel(DataOutput, k, i) << endl;
	}
	
	for (int i = 2; i <= 5; i++)
	{
		cout << "Step: " << i << endl;
		NgrammLink(mymap, DataOutput, i);
	}
	//cout << DataOutput;
	system("pause");
	return 0;
}