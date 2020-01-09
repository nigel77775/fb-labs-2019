#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

std::string biGram[4] = {"00", "01", "10", "11"};
int biCount[4] = {0};
std::string threeGram [8] = {"000", "001", "010", "011", "100", "101", "110", "111"};
int threeCount[8] = {0};
std::string fourGram [16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
int fourCount[16] = {0};
std::string fiveGram [32] = {"00000", "00001", "00010", "00011", "00100", "00101", "00110", "00111", "01000", "01001", "01010", "01011", "01100", "01101", "01110", "01111", "10000", "10001", "10010",  "10011", "10100", "10101", "10110", "10111", "11000", "11001", "11010", "11011", "11100", "11101", "11110", "11111"};
int fiveCount[32] = {0};
std::vector<bool> sequence1 {1,1,1,1,0,0,1,1,1,0,0,1,0,1,1,1,0,1,0,0,0,0};
std::vector<bool> impulse1 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
std::vector<bool> etalon1 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
std::vector<bool> sequence2 {1,1,1,0,0,0,0,1,0,1,1,0,0,1,1,1,1,0,0,0,0};
std::vector<bool> impulse2 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
std::vector<bool> etalon2 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};

int doEverything(std::vector<bool> sequence, std::vector<bool> impulse, std::vector<bool> etalon)
{
    std::vector<bool> order, temp;
    bool sum;

    do
    {
        order.push_back(sequence[1]);

        for (int i = 0; i < sequence.size(); ++i)
        {
            temp.push_back(impulse[i] & sequence[i]);
        }

        sum = 0;
        for (int i = 0; i < sequence.size(); ++i)
        {
            sum ^= temp[i];
        }

        impulse.erase (impulse.begin());
        impulse.push_back(sum);

        for (int i = 0; i < sequence.size(); ++i)
        {
            temp.pop_back();
        }

    } while (!(impulse == etalon));

    std::cout << order.size();

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < order.size(); j += 2)
        {
            std::string buf(sequence[j], sequence[j + 1]);
            if (buf == biGram[i])
            {
                biCount[i]++;
            }
        }
        std::cout << biCount[i];
    }

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < order.size(); j += 3)
        {
            std::string buf(sequence[j], sequence[j + 2]);
            if (buf == threeGram[i])
            {
                threeCount[i]++;
            }
        }
        std::cout << threeCount[i];
    }

    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < order.size(); j += 4)
        {
            std::string buf(sequence[j], sequence[j + 3]);
            if (buf == fourGram[i])
            {
                fourCount[i]++;
            }
        }
        std::cout << fourCount[i];
    }

    for (int i = 0; i < 32; ++i)
    {
        for (int j = 0; j < order.size(); j += 5)
        {
            std::string buf(sequence[j], sequence[j + 4]);
            if (buf == fiveGram[i])
            {
                fiveCount[i]++;
            }
        }
        std::cout << fiveCount[i];
    }

    for (int j = 0; j < 10; j++)
    {
        int autocorrelation = 0;
        for (int i = 0; i < order.size(); i += j)
        {
            autocorrelation += order[i] + order[i + j] % 2;
        }
        std::cout << "\nautocorrelation " << j << ' ' << autocorrelation;
    }
}

int main()
{
    doEverything(sequence1, impulse1, etalon1);
    doEverything(sequence2, impulse2, etalon2);
}
