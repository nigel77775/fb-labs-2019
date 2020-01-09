 #include <fstream>
 #include <iostream>  
 #include <cstring>
 #include <math.h>
 #include <cstdio>

 using namespace std;
 
 struct	s_data
 {
 		int *var25;
 		int	*def25;
 		int	*dif25;
 		int	*var;
 		int	*def;
 		int *dif;
 };

char *get_t(s_data data, int &T, int size)
{
	cout << "Searching T\n";
	int suma = 0;
	char *mas = new char[100000000];
	int i = -1;
	while (++i < size)
		suma+=(data.var[i]*data.def[i]);
	//sdvig
	mas[T]=data.def[0];
	i = -1;
	while (++i < size - 1)
		data.def[i] = data.def[i+1];
	data.def[size - 1]=suma%2;
	T++;
	while(equal(data.def,data.def+size,data.dif) == 0)
	{
		suma = 0;
		i = -1;
		while (++i < size)
			suma+=(data.var[i]*data.def[i]);
		mas[T]=data.def[0];
		for(int i=0;i<size - 1;i++)
		{
			data.def[i]=data.def[i+1];
		}
		data.def[size - 1]=suma%2;
		T++;
   }
   cout<<"T = "<<T<<endl;
   return (mas);
}

void recur(int T, char *mas, int grams, int *num, int cur_num) 
{
	if (cur_num == grams)
	{
		int n[5];
		memcpy(n, num, 5 * sizeof(int));
		for (int l = 0; l < grams; l++)
			cout << n[l] << " ";
		long int counter = 0;
		int i = 0 - grams;
		while ((i = i + grams) < T-T % grams)
						{
							char m[5];
							memcpy(m, mas + i, grams);
							if(equal(n, n + grams, m))
								counter++;
						}
		cout << counter << endl;
		return ;
	}
	num[cur_num] = 0;
	recur(T, mas, grams, num, cur_num + 1);
	num[cur_num] = 1;
	recur(T, mas, grams, num, cur_num + 1);
}

void calc_autocorrelation(int T, char *mas)
{
	cout << "calculating correlation\n"; //
	int k;
	int d = -1;
	int i;
	while (++d < 11 && !(k = 0) && (i = -1))
	{
		while (++i < T)
			k += (mas[i] + mas[(i + d) % T]) % 2;
		printf("%d %d\n", d, k);
	}
}

int main()
{
	s_data kripta;
	int var25[25]={1,0,0,1,0,0,1,1,1,0,1,0,0,1,1,1,0,1,0,1,1,0,0,0,0};
	int def25[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	int dif25[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	int var[20]={1,0,1,0,1,0,1,0,0,1,1,1,0,1,0,1,0,1,0,0};
	int def[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	int dif[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	kripta.var25 = var25;
	kripta.def = def;
	kripta.def25 = def25;
	kripta.var = var;
	kripta.dif = dif;
	kripta.dif25 = dif25;
	cout << "counting polinom 20-size\n";
	int T = 0;
	char *mas = get_t(kripta, T, 20);
	int mas_int[5];
	cout << "2-gram\n";
	recur(T, mas, 2, mas_int, 0);
	cout << "3-gram\n";
	recur(T, mas, 3, mas_int, 0);
	cout << "4-gram\n";
	recur(T, mas, 4, mas_int, 0);
	cout << "5-gram\n";
	recur(T, mas, 5, mas_int, 0);
	calc_autocorrelation(T, mas);
	delete[] mas;
	cout << "counting polinom 25-size\n";
	kripta.def = kripta.def25;
	kripta.dif = kripta.dif25;
	kripta.var = kripta.var25;
  	T = 0;
	mas = get_t(kripta, T, 25);
	mas_int[5];
	cout << "2-gram\n";
	recur(T, mas, 2, mas_int, 0);
	cout << "3-gram\n";
	recur(T, mas, 3, mas_int, 0);
	cout << "4-gram\n";
	recur(T, mas, 4, mas_int, 0);
	cout << "5-gram\n";
	recur(T, mas, 5, mas_int, 0);
	calc_autocorrelation(T, mas);
	delete[] mas;
}
