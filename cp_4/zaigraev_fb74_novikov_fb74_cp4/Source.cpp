#include "compute.cuh"

#include <bitset>//num to bin for answer
#pragma comment (lib, "cudart64_102.dll")


using namespace std;


double getBeta(pPolynom poly, double percent) {
	double Border = double(1) / pow(2, poly->polynom[0]);
	return Border * percent;
}

void getParams(pPolynom poly, pcrackParams params, int *C, int *Ns) {
	boost::math::normal dist(0.0, 1.0);
	double beta = getBeta(poly, params->betaPercent);
	double QuantileAlpha = quantile(dist, 1 - params->alpha);
	double QuantileBeta  = quantile(dist, 1 - beta);
	double NsDouble = pow((QuantileBeta + ((QuantileAlpha * sqrt(params->p1 * (1 - params->p1))) / sqrt(params->p2 * (1 - params->p2)))) * (sqrt(params->p2 * (1 - params->p2)) / (params->p2 - params->p1)), 2);
	*C = (NsDouble * params->p1 + QuantileAlpha * sqrt(NsDouble * params->p1 * (1 - params->p1))) + 1;
	*Ns = NsDouble + 1;
}


double getCuda_optimalSize(pPolynom poly, int Ns, int z_size) {
	int maxBlocks, maxThreads;
	unsigned long long memoryByte, mem_per_thread, mem_shared, mem_total;
	
	mem_per_thread = 2048 * sizeof(unsigned int) + 2 * 64 * sizeof(unsigned int) + sizeof(unsigned char) + 3 * sizeof(unsigned int) + 10 * sizeof(int) + 32 * sizeof(unsigned int);
	mem_shared = 40000 * sizeof(unsigned int) + 64 * sizeof(unsigned int) + poly->size * sizeof(unsigned int) + sizeof(unsigned int) + 100 * sizeof(unsigned int);
	mem_total = mem_per_thread + mem_shared;

	cudaDeviceProp deviceProp;
	cudaGetDeviceProperties(&deviceProp, 0);
	cout << "Found: " << deviceProp.name << endl;
	maxBlocks = deviceProp.maxGridSize[0];
	maxThreads = deviceProp.maxThreadsDim[0];
	memoryByte = deviceProp.totalGlobalMem;
	//memoryByte -= pow(2, 28);
	memoryByte = (double)(memoryByte) * 0.9;
	memoryByte -= mem_shared;


	return ((double)(memoryByte / mem_per_thread)) * 0.95;
}



int main() {
	vector <unsigned int> z;
	//int N = getZ("test_big", &z);
	int N = getZ("test_small", &z);
	pcrackParams params = new crackParams;
	params->alpha = 0.01;
	params->p1 = 0.25;
	params->p2 = 0.5;
	params->betaPercent = 0.99;

	pPolynom poly1 = new Polynom;
	//poly1->polynom = new unsigned int[5]{ 30, 6, 4, 1, 0 };
	//poly1->size = 5;
	poly1->polynom = new unsigned int[3]{ 25, 3, 0 };
	poly1->size = 3;
	pPolynom poly2 = new Polynom;
	//poly2->polynom = new unsigned int[3]{ 31, 3, 0 };
	//poly2->size = 3;
	poly2->polynom = new unsigned int[5]{ 26, 6, 2, 1, 0 };
	poly2->size = 5;
	pPolynom poly3 = new Polynom;
	//poly3->polynom = new unsigned int[7]{ 32, 7, 5, 3, 2, 1, 0 };
	//poly3->size = 7;
	poly3->polynom = new unsigned int[5]{ 27, 5, 2, 1, 0 };
	poly3->size = 5;
	vector<unsigned int> L1_probable, L2_probable, result;
	plfstrHistory lfstr1_init = new lfstrHistory;
	plfstrHistory lfstr2_init = new lfstrHistory;

	int NsInt, C;
	getParams(poly1, params, &C, &NsInt);

	lfstr1_init->parts = unsigned int(getCuda_optimalSize(poly1, NsInt, C));

	unsigned int period;
	
	cout << "LFSTR1" << endl;
	cout << "CPU calculation of init vectors for CUDA parallelism" << endl;
	lfstr(1, poly1, &period, lfstr1_init);

	cuda_lfstrCrack(lfstr1_init, poly1, z, NsInt, C, &L1_probable);
	cout << "Num of probable vectors: " << L1_probable.size() << endl;
	/*
	for (int i = 0; i < L1_probable.size();i++) {
		cout << L1_probable[i] << endl;
	}
	*/
	
	

	


	cout << "LFSTR2" << endl;
	cout << "CPU calculation of init vectors for CUDA parallelism" << endl;
	getParams(poly2, params, &C, &NsInt);
	lfstr2_init->parts = unsigned int(getCuda_optimalSize(poly2, NsInt, C));
	lfstr(1, poly2, &period, lfstr2_init);
	cuda_lfstrCrack(lfstr2_init, poly2, z, NsInt, C, &L2_probable);

	cout << "Num of probable vectors: " << L2_probable.size() << endl;
	/*for (int i = 0; i < L2_probable.size(); i++) {
		//cout << L2_probable[i] << endl;
	}*/


	
	cout << "LFSTR3" << endl;

	
	cout << "CPU preparations for CUDA" << endl;

	cuda_GeffeCrack(poly1, poly2, poly3, z, L1_probable, L2_probable, &result);


	cout << "\n----------------------------------------------------------\nRESULT:" << endl;

	for (int i = 0; i < result.size(); i++) {
		string bits = std::bitset<32>(result[i]).to_string();
		reverse(bits.begin(), bits.end());
		cout << "L" << i+1 << ": " << bits << endl;
	}

	cout << "L1 gamma:" << endl;
	vector<unsigned int> arr = get_lfstr_res(result[0], poly1);
	for (int i = 0; i < arr.size(); i++)
		cout << std::bitset<32>(arr[i]).to_string();
	cout << "\n" << endl;

	cout << "L2 gamma:" << endl;
	arr = get_lfstr_res(result[1], poly2);
	for (int i = 0; i < arr.size(); i++)
		cout << std::bitset<32>(arr[i]).to_string();
	cout << "\n" << endl;

	cout << "L3 gamma:" << endl;
	arr = get_lfstr_res(result[2], poly3);
	for (int i = 0; i < arr.size(); i++)
		cout << std::bitset<32>(arr[i]).to_string();
	cout << "\n" << endl;

	cout << "EO CRACKING!" << endl;


	system("pause");

	return 0;	
}



/*
int main() {
	unsigned int period;

	pPolynom poly1		 = new polynom;
	pPolynom poly2		 = new polynom;
	pPolynom poly3		 = new polynom;
	plfstrHistory lfstr1 = new lfstrHistory;
	plfstrHistory lfstr2 = new lfstrHistory;
	plfstrHistory lfstr3 = new lfstrHistory;

	poly1->polynom = new int[3] {25, 3, 0};
	poly1->size = 3;
	poly2->polynom = new int[5] {26, 6, 2, 1, 0};
	poly2->size = 5;
	poly3->polynom = new int[5] {27, 5, 2, 1, 0};
	poly3->size = 5;

	lfstr(1, poly1, &period);
	cout << 1 << ") Period: " << period << endl;
	lfstr(1, poly2, &period, lfstr2);
	cout << 2 << ") Period: " << period << endl;
	lfstr(1, poly3, &period, lfstr3);
	cout << 3 << ") Period: " << period << endl;

	delete[] poly1->polynom;
	delete[] poly2->polynom;
	delete[] poly3->polynom;
	delete poly1;	
	delete poly2;	
	delete poly3;
	
	lfstr1->history.clear();
	lfstr1->history.shrink_to_fit();
	lfstr2->history.clear();
	lfstr2->history.shrink_to_fit();
	lfstr3->history.clear();
	lfstr3->history.shrink_to_fit();

	delete lfstr1;
	delete lfstr2;
	delete lfstr3;

	return 0;
}
*/



int getZ(string file, vector <unsigned int>* z)
{
	fstream zFile;
	char* read = new char[1];
	zFile.open(file, ios::in | ios::binary | ios::ate);
	streampos fileLen = zFile.tellg();
	zFile.seekg(0, ios::beg);
	for (int i = 0; i < fileLen; i++)
	{
		if (i % 32 == 0)
			z->push_back(0);
		zFile >> read[0];
		(*z)[i / 32] |= (int(read[0]) - 48) << (31 - (i % 32));
	}
	delete[] read;
	zFile.close();
	return fileLen;
}



void lfstr(unsigned int init, pPolynom polynom, unsigned int* period, plfstrHistory history) {
	unsigned char new_bit;
	unsigned int curr = init;
	unsigned int bit_length = polynom->polynom[0];
	*period = 0;
	unsigned int max_iters = (1 << polynom->polynom[0]) - 1;
	if (polynom->polynom[0] == 32)
		max_iters = 4294967295;
	unsigned int modulo;
	//cout << max_iters << endl;

	if (history != nullptr) {
		if (history->parts == 0)
			modulo = 1;
		else
			modulo = max_iters / history->parts;
	}

	while (true) {
		new_bit = 0;

		if (history != nullptr && *period % modulo == 0)
			history->history.push_back(curr);

		*period += 1;

		for (int i = 1; i < polynom->size; i++) {
			new_bit ^= (curr & (1 << polynom->polynom[i])) >> polynom->polynom[i];
		}

		curr >>= 1;
		curr |= new_bit << (bit_length - 1);

		if (curr == init || *period >= max_iters) {
			if (history != nullptr)
				history->size = history->history.size();
			return;
		}
	}
}



void lfstr_Crack_old(unsigned int init, pPolynom polynom, vector <unsigned int> z, int Ns, int C, vector <unsigned int>* probable) {
	unsigned char new_bit, temp_bit, temp_bit2;
	unsigned int curr = init;
	unsigned int bit_length = polynom->polynom[0];
	int* final_Countdown=nullptr;
	
	unsigned int max_iters = (1 << polynom->polynom[0]) - 1;
	cout << max_iters << endl;

	vector<unsigned int> history, x = z;
	int vectorSize = x.size();

	int R;
	for (int iter = 0; iter < max_iters + Ns; iter++) {
		if (iter % 10000000 == 0)
			cout << iter << endl;


		new_bit = 0;
		R = 0;

		for (int i = 1; i < polynom->size; i++) {
			new_bit ^= (curr & (1 << polynom->polynom[i])) >> polynom->polynom[i];
		}


		temp_bit = (x[vectorSize - 1] & (1 << 31)) >> 31;
		x[vectorSize - 1] <<= 1;
		x[vectorSize - 1] |= curr & 1;
		for (int i = vectorSize-2; i >= 0; i--) {
			temp_bit2 = (x[i] & (1 << 31)) >> 31;
			x[i] <<= 1;
			x[i] |= temp_bit;
			temp_bit = temp_bit2;
		}


		if (history.size() == Ns-1) {
			for (int i = 0; i < Ns; i++) {
				R += ((z[i / 32] & (1 << (31 - (i % 32)))) >> (31 - (i % 32))) ^ ((x[(2048 - Ns + i) / 32] & (1 << (31 - ((2048 - Ns + i) % 32)))) >> (31 - ((2048 - Ns + i) % 32)));
			}
			if (R < C) {
				probable->push_back(history[0]);
			}
			history.erase(history.begin());
		}
		history.push_back(curr);


		curr >>= 1;
		curr |= new_bit << (bit_length - 1);

		/*
		if (final_Countdown) {
			*final_Countdown--;
			if (*final_Countdown == 0)
				return;
		}

		if (curr == init) {
			final_Countdown = new int(Ns);
		}
		*/
	}
}


void lfstr_Crack(unsigned int init, pPolynom polynom, vector <unsigned int> z, int Ns, int C, vector <unsigned int>* probable) {
	unsigned char new_bit, temp_bit, temp_bit2;
	unsigned int curr = init;
	unsigned int bit_length = polynom->polynom[0];

	unsigned int max_iters = (1 << polynom->polynom[0]) - 1;
	cout << max_iters << endl;

	vector<unsigned int> history, x = z;
	int vectorSize = x.size();
	for (int i = 0; i < x.size(); i++)
		x[i] = 0;

	int R;
	for (int iter = 0; iter < max_iters + Ns; iter++) {
		if (iter % 10000000 == 0)
			cout << iter << endl;

		

		new_bit = 0;
		R = 0;

		for (int i = 1; i < polynom->size; i++) {
			new_bit ^= (curr & (1 << polynom->polynom[i])) >> polynom->polynom[i];
		}


		temp_bit = (x[vectorSize - 1] & (1 << 31)) >> 31;
		x[vectorSize - 1] <<= 1;
		x[vectorSize - 1] |= curr & 1;
		for (int i = vectorSize - 2; i >= 0; i--) {
			temp_bit2 = (x[i] & (1 << 31)) >> 31;
			x[i] <<= 1;
			x[i] |= temp_bit;
			temp_bit = temp_bit2;
		}

		/*
		if (iter == 1489)
			return;
		printf("%d) %d\n", iter, curr);*/
		
		/*
		if (iter == 15648) {
			for (unsigned int i = 0; i < vectorSize; i++) {
				printf("%d) \t%d\n", i, x[i]);
			}
			return;
		}
		*/

		if (history.size() == Ns - 1) {
			for (int i = 0; i < Ns; i++) {
				R += ((z[i / 32] & (1 << (31 - (i % 32)))) >> (31 - (i % 32))) ^ ((x[(2048 - Ns + i) / 32] & (1 << (31 - ((2048 - Ns + i) % 32)))) >> (31 - ((2048 - Ns + i) % 32)));
			}
			if (R < C) {
				probable->push_back(history[0]);
			}
			history.erase(history.begin());
		}
		history.push_back(curr);


		curr >>= 1;
		curr |= new_bit << (bit_length - 1);

	}
	history.clear();
	history.shrink_to_fit();
	x.clear();
	x.shrink_to_fit();
	z.clear();
	z.shrink_to_fit();
}

void cuda_lfstrCrack(plfstrHistory init_arr, pPolynom polynom, vector <unsigned int> z, int Ns, int C, vector<unsigned int>* probable) {
	vector<unsigned int> polynom_vector;
	for (int i = 0; i < polynom->size; i++)
		polynom_vector.push_back(polynom->polynom[i]);

	kernel_crackLFSTR(init_arr, polynom_vector, z, Ns, C, probable);
	polynom_vector.clear();
	polynom_vector.shrink_to_fit();
	init_arr->history.clear();
	init_arr->history.shrink_to_fit();
	delete init_arr;
	sort(probable->begin(), probable->end());
	probable->erase(unique(probable->begin(), probable->end()), probable->end());
}


vector <unsigned int> get_lfstr_res(unsigned int init, pPolynom polynom, int iterations) {
	unsigned char new_bit, temp_bit, temp_bit2;
	unsigned int curr = init;
	unsigned int bit_length = polynom->polynom[0];
	int vector_size;
	if (iterations % 32 == 0)
		vector_size = iterations / 32;
	else
		vector_size = (iterations / 32) + 1;
	vector<unsigned int> res(vector_size);

	for (int iter = 0; iter < iterations; iter++) {
		new_bit = 0;

		for (int i = 1; i < polynom->size; i++) {
			new_bit ^= (curr & (1 << polynom->polynom[i])) >> polynom->polynom[i];
		}

		temp_bit = (res[vector_size - 1] & (1 << 31)) >> 31;
		res[vector_size - 1] <<= 1;
		res[vector_size - 1] |= curr & 1;
		for (int i = vector_size - 2; i >= 0; i--) {
			temp_bit2 = (res[i] & (1 << 31)) >> 31;
			res[i] <<= 1;
			res[i] |= temp_bit;
			temp_bit = temp_bit2;
		}

		curr >>= 1;
		curr |= new_bit << (bit_length - 1);

	}
	return res;
}



void cuda_GeffeCrack(pPolynom polynom1, pPolynom polynom2, pPolynom polynom3, vector <unsigned int> z, vector <unsigned int> lfstr1, vector <unsigned int> lfstr2, vector<unsigned int>* result) {
	//unsigned int z;
	vector<unsigned int> lfstr1_res, lfstr2_res, polynom_vector, temp, temp2, pairs, cudaRes, arr;
	vector<vector<unsigned int>> polynoms;
	unsigned int known_mask, unknown_mask, known_z, possible = 0;
	for (int i = 0; i < polynom1->size; i++)
		polynom_vector.push_back(polynom1->polynom[i]);
	polynoms.push_back(polynom_vector);
	polynom_vector.clear();
	for (int i = 0; i < polynom2->size; i++)
		polynom_vector.push_back(polynom2->polynom[i]);
	polynoms.push_back(polynom_vector);
	polynom_vector.clear();
	for (int i = 0; i < polynom3->size; i++)
		polynom_vector.push_back(polynom3->polynom[i]);
	polynoms.push_back(polynom_vector);
	polynom_vector.clear();
	/*
	for (int i = 0; i < lfstr1.size(); i++) {
		temp = get_lfstr_res(lfstr1[i], polynom1);
		for (int j = 0; j < temp.size(); j++)
			lfstr1_res.push_back(temp[j]);
	}
	for (int i = 0; i < lfstr2.size(); i++) {
		temp = get_lfstr_res(lfstr2[i], polynom2);
		for (int j = 0; j < temp.size(); j++)
			lfstr2_res.push_back(temp[j]);
		kernel_crackGeffe(init_arr, polynom_vector, z, lfstr1_res, lfstr2_res, &cudaRes);
		lfstr2_res.clear();
		cudaRes.clear();
		cout << i << endl;
		if (cudaRes[2] != 0)
			break;
	}

	known_mask = lfstr1_local[0] ^ lfstr2_local[0];

	if (lfstr1_local[0] & ~known_mask != z_local[0] & ~known_mask)
		return;

	known_z |= (lfstr1_local[0] & known_mask) ^ (~(z_local[0] & known_mask));


	for (int i = 0; i < lfstr1.size(); i++) {
		vector<unsigned int>t1 = get_lfstr_res(lfstr1[i], polynom1, 2048);
		for (int j = 0; j < lfstr2.size(); j++) {
			vector<unsigned int>t2 = get_lfstr_res(lfstr2[i], polynom2, 2048);
			bool tr = true;
			for (int k = 0; k < 2048; k++) {
				known_mask = t1[i] ^ t2[j];

				if ((t1[i] & ~known_mask) != (z[0] & ~known_mask)) {
					tr = false;
					break;
				}
			}
			if (tr == true) {
				cout << "Possible" << possible++ << ": " << lfstr1[i] << " " << lfstr2[j] << endl;
				temp1.push_back(lfstr1[i]);
				temp2.push_back(lfstr2[i]);
				pairs.push_back(i * lfstr2.size() + j);
			}
			//known_z |= (lfstr1_local[0] & known_mask) ^ (~(z_local[0] & known_mask));
		}
	}

	*/
	
	unsigned int z_rev;
	//temp1.empty();
	z_rev = reverseBits(z[0]);//get_lfstr_res(z[0], polynom1, 32);
	unsigned int end_mask = pow(2, min(polynoms[0][0], polynoms[1][0], polynoms[2][0])) - 1;
	
	for (int i = 0; i < lfstr1.size(); i++) {
		for (int j = 0; j < lfstr2.size(); j++) {
			known_mask = lfstr1[i] ^ lfstr2[j];
			unknown_mask = ~known_mask;
			unknown_mask &= end_mask;

			if ((lfstr1[i] & unknown_mask) != (z_rev & unknown_mask))
				continue;
//			cout << "Possible" << possible++ << ": " << lfstr1[i] << " " << lfstr2[j] << endl;
			arr.push_back(lfstr1[i]);
			temp2.push_back(lfstr2[j]);
			pairs.push_back(i * lfstr2.size() + j);
			//known_z |= (lfstr1_local[0] & known_mask) ^ (~(z_local[0] & known_mask));
		}
	}



	sort(arr.begin(), arr.end());
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	temp = arr;
	sort(temp2.begin(), temp2.end());
	temp2.erase(unique(temp2.begin(), temp2.end()), temp2.end());

	for (int i = 0; i < pairs.size(); i++) {
		int index_l1 = pairs[i] / lfstr2.size();
		int index_l2 = pairs[i] % lfstr2.size();
		for (int j = 0; j < temp.size(); j++) {
			if (lfstr1[index_l1] == temp[j]) {
				index_l1 = j;
				break;
			}
		}
		for (int j = 0; j < temp2.size(); j++) {
			if (lfstr2[index_l2] == temp2[j]) {
				index_l2 = j;
				break;
			}
		}
		pairs[i] = index_l1 * temp2.size() + index_l2;
	}
	lfstr1 = temp;
	lfstr2 = temp2;
	temp2.clear();
	temp2.shrink_to_fit();

	for (int i = 0; i < lfstr1.size(); i++) {
		temp = get_lfstr_res(lfstr1[i], polynom1);
		for (int j = 0; j < temp.size(); j++)
			lfstr1_res.push_back(temp[j]);
	}

	for (int i = 0; i < lfstr2.size(); i++) {
		temp = get_lfstr_res(lfstr2[i], polynom2);
		for (int j = 0; j < temp.size(); j++)
			lfstr2_res.push_back(temp[j]);
	}
	temp.clear();
 	temp.shrink_to_fit();
	cout << "Number of probable pairs: "<< pairs.size() << endl;
	unsigned int* cudaPointer = kernel_crackGeffe(polynoms[2], min(polynoms[0][0], polynoms[1][0], polynoms[2][0]), z, lfstr1_res, lfstr2_res, pairs);
	cudaRes.assign(cudaPointer, cudaPointer + 3);
	free(cudaPointer);
	polynom_vector.clear();
	polynom_vector.shrink_to_fit();
	result->push_back(lfstr1[cudaRes[0]]);
	result->push_back(lfstr2[cudaRes[1]]);
	result->push_back(cudaRes[2]);
}


unsigned int reverseBits(unsigned int num)
{
	unsigned int count = sizeof(num) * 8 - 1;
	unsigned int reverse_num = num;

	num >>= 1;
	while (num)
	{
		reverse_num <<= 1;
		reverse_num |= num & 1;
		num >>= 1;
		count--;
	}
	reverse_num <<= count;
	return reverse_num;
}