#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <fstream>

// Russian alphabet
wchar_t walpha[32]
{
  L'а',L'б',L'в',L'г',L'д',L'е',L'ж',L'з',L'и',L'й',L'к',L'л',L'м',L'н',L'о',L'п',L'р',L'с',L'т',L'у',L'ф',L'х',L'ц',L'ч',L'ш',L'щ',L'ы',L'ь',L'э',L'ю',L'я',L' ',
};
wchar_t wbigAlpha[32]
{
  L'А',L'Б',L'В',L'Г',L'Д',L'Е',L'Ж',L'З',L'И',L'Й',L'К',L'Л',L'М',L'Н',L'О',L'П',L'Р',L'С',L'Т',L'У',L'Ф',L'Х',L'Ц',L'Ч',L'Ш',L'Щ',L'Ы',L'Ь',L'Э',L'Ю',L'Я',L' ',
};

const char alpha [] = u8"абвгдежзийклмнопрстуфхцчшщыьэюя ";
double biSpaceAmount[32][32] = {0};
double biAmount[31][31] = {0};

std::string sAlpha[32]
{
  u8"а",u8"б",u8"в",u8"г",u8"д",u8"е",u8"ж",u8"з",u8"и",u8"й",u8"к",u8"л",u8"м",u8"н",u8"о",u8"п",u8"р",u8"с",u8"т",u8"у",u8"ф",u8"х",u8"ц",u8"ч",u8"ш",u8"щ",u8"ы",u8"ь",u8"э",u8"ю",u8"я",u8" ",
};

std::string readText();
std::string cleanText(std::string &text);

std::wstring toUnicode(const char* text, int textSize);
std::wstring leaveRussianText(std::wstring wtext);
std::wstring replaceUnnecessary(std::wstring wbuffer);
std::string toUTF8(int textSize, std::wstring wbuffer);

void mono(std::string &text);
void biCrossed(std::string &text);
void bi(std::string &text);

int main()
{
    std::ofstream out("cleanText.txt");
    std::string text;

    text = readText();
    text = cleanText(text);

    out << text;
    out.close();

    mono(text);
    biCrossed(text);
    bi(text);

    return 0;
}

void bi(std::string &text)
{
    std::ofstream output("biStatistics.txt");

    std::wstring wtext = toUnicode(text.c_str(), text.length());

    double sum, spaceSum = 0;
    std::wstring bigram, mono1, mono2, wstrChar;
    int m, n = -1;
    double biSpaceAmoumt[32][32] = {0};
    double biAmoumt[31][31] = {0};

    for (int i = 0; wtext[i] != '\0'; i += 3)
    {
        mono1 = wtext.substr(i, 1);
        if (i + 2 > wtext.length())
        {
            break;
        }
        mono2 = wtext.substr(i + 2, 1);

        for (int j = 0; j < 32; j++)
        {
            wstrChar = walpha[j];

            if (wstrChar.compare(mono1) == 0)
            {
                m = j;
            }

            if (wstrChar.compare(mono2) == 0)
            {
                m = j;
            }

            if (m != -1 && n != -1)
            {
                break;
            }
        }
        biSpaceAmoumt[m][n]++;
        m = n = -1;
    }

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            spaceSum += biSpaceAmount[i][j];
        }
    }

    std::cout << "Amount of uncrossed bigrams with spaces counted" << std::endl;

    text.erase(std::remove_if(text.begin(), text.end(), &isspace), text.end());
    wtext = toUnicode(text.c_str(), text.length());

    for (int i = 0; wtext[i] != '\0'; i += 3)
    {
        mono1 = wtext.substr(i, 1);
        if (i + 2 > wtext.length())
        {
            break;
        }
        mono2 = wtext.substr(i + 2, 1);

        for (int j = 0; j < 31; j++)
        {
            wstrChar = walpha[j];

            if (wstrChar.compare(mono1) == 0)
            {
                m = j;
            }

            if (wstrChar.compare(mono2) == 0)
            {
                m = j;
            }

            if (m != -1 && n != -1)
            {
                break;
            }
        }
        biAmoumt[m][n]++;
        m = n = -1;
    }

    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 31; j++)
        {
            sum += biAmount[i][j];
        }
    }

    std::cout << "Amount of uncrossed bigrams without spaces counted" << std::endl;

    double prob[31][31], spaceProb[32][32]; //probability
    spaceSum /= 1.04;
    double entr, spaceEntr = 0; //entropy

    output << "probability:\n\t\t";
    for (int i = 0; i < 31; i ++)
    {
        output << sAlpha[i] << "\t\t\t";
    }

    for (int i = 0; i < 31; i ++)
    {
        output << '\n'<< sAlpha[i];

        for (int j = 0; j <= 30; j ++)
        {
            prob[i][j] = biAmount[i][j] / sum;
            if (prob[i][j] != 0)
            {
            entr += prob[i][j] * log(prob[i][j])/log(2);
            }
            output << "\t\t" << std::fixed << prob[i][j];
        }
        output << std::endl;
    }

    output << "\n\nspace probability:\n\t\t";
    for (int i = 0; i < 32; i ++)
    {
        output << sAlpha[i] << "\t\t\t";
    }

    for (int i = 0; i < 32; i ++)
    {
        output << '\n'<< sAlpha[i];

        for (int j = 0; j < 32; j ++)
        {
            spaceProb[i][j] = biSpaceAmount[i][j] / spaceSum;
            if (spaceProb[i][j] != 0)
            {
                spaceEntr += spaceProb[i][j] * log(spaceProb[i][j])/log(2);
            }
            output << "\t\t" << std::fixed << spaceProb[i][j];
        }
        output << std::endl;
    }

    std::cout << "Probability of uncrossed bigrams estimated" << std::endl;

    entr *= -1;
    entr /= 2;
    spaceEntr *= -1;
    spaceEntr /= 2;

    output << std::endl << "\nentropy of uncrossed bigrams without spaces:  " << entr;
    output << std::endl << "entropy of uncrossed bigrams with spaces:\t" << spaceEntr;

    std::cout << "Entropy of uncrossed bigrams estimated" << std::endl;

    std::cout << "Uncrossed bigram statistics recorded" << std::endl;

    output.close();
}

void biCrossed(std::string &text)
{
    std::ofstream output("biCrossedStatistics.txt");

    double sum, spaceSum = 0;
    int pos = -1;
    std::string bigram;
    double biCrossedAmount[32][32] = {0};

    for (int i = 0; i < 32; i ++)
    {

        for (int j = 0; j < 32 ; j ++)
        {
            bigram = sAlpha[i] + sAlpha[j];

            while ((pos = text.find(bigram, pos + 1)) != std::string::npos)
            {
                biCrossedAmount[i][j]++;

                if (text[pos + 1] == '\0')
                {
                    break;
                }
            }
            spaceSum += biCrossedAmount[i][j];
            biSpaceAmount[i][j] = biCrossedAmount[i][j];
            if (i < 31 && j < 31)
            {
                sum += biCrossedAmount[i][j];
                biAmount[i][j] = biCrossedAmount[i][j];
            }
            pos = -1;
        }
    }

    std::cout << "\nAmount of crossed bigrams counted" << std::endl;

    double prob[31][31], spaceProb[32][32]; //probability
    spaceSum /= 1.04;
    double entr, spaceEntr = 0; //entropy

    output << "probability:\n\t\t";
    for (int i = 0; i < 31; i ++)
    {
        output << sAlpha[i] << "\t\t\t";
    }

    for (int i = 0; i < 31; i ++)
    {
        output << '\n'<< sAlpha[i];

        for (int j = 0; j <= 30; j ++)
        {
            prob[i][j] = biCrossedAmount[i][j] / sum;
            if (prob[i][j] != 0)
            {
            entr += prob[i][j] * log(prob[i][j])/log(2);
            }
            output << "\t\t" << std::fixed << prob[i][j];
        }
        output << std::endl;
    }

    output << "\n\nspace probability:\n\t\t";
    for (int i = 0; i < 32; i ++)
    {
        output << sAlpha[i] << "\t\t\t";
    }

    for (int i = 0; i < 32; i ++)
    {
        output << '\n'<< sAlpha[i];

        for (int j = 0; j < 32; j ++)
        {
            spaceProb[i][j] = biCrossedAmount[i][j] / spaceSum;
            if (spaceProb[i][j] != 0)
            {
                spaceEntr += spaceProb[i][j] * log(spaceProb[i][j])/log(2);
            }
            output << "\t\t" << std::fixed << spaceProb[i][j];
        }
        output << std::endl;
    }

    std::cout << "Probability of crossed bigrams estimated" << std::endl;

    entr *= -1;
    entr /= 2;
    spaceEntr *= -1;
    spaceEntr /= 2;

    output << std::endl << "\nentropy of crossed bigrams without spaces:  " << entr;
    output << std::endl << "entropy of crossed bigrams with spaces:\t" << spaceEntr;

    std::cout << "Entropy of crossed bigrams estimated" << std::endl;

    std::cout << "Crossed bigram statistics recorded" << std::endl;

    output.close();
}

void mono(std::string &text)
{
    std::ofstream output("monoStatistics.txt");

    double monoAmount[32];
    double sum, spaceSum = 0;

    int j = 1;
    for (int i = 0; i < 31; i++)
    {
        monoAmount[i] = std::count (text.begin(), text.end(), alpha[j]);
        sum += monoAmount[i];
        j+=2;
    }

    monoAmount[31] = std::count (text.begin(), text.end(), ' ');
    spaceSum = sum + monoAmount[31];

    std::cout << "Amount of letters counted" << std::endl;


    double prob[31], spaceProb[32]; //probability

    for (int i = 0; i < 31; i++)
    {
        prob[i] = monoAmount[i] / sum;
        spaceProb[i] = monoAmount[i] / spaceSum;
    }
    spaceProb[31] = monoAmount[31] / spaceSum;

    std::cout << "Probability of letters estimated" << std::endl;


    double entr, spaceEntr = 0; //entropy

    for (int i = 0; i < 31; i++)
    {
        entr += prob[i] * log2(prob[i]);
        spaceEntr += spaceProb[i] * log2(spaceProb[i]);
    }
    spaceEntr += spaceProb[31] * log2(spaceProb[31]);
    entr *= -1;
    spaceEntr *= -1;

    std::cout << "Entropy estimated" << std::endl;


    output << std::endl << "char:\tprobability:\tspace probability:";
    for (int i = 0; i < 31; i++)
    {
        output << std::endl << sAlpha[i] << ":\t" << prob[i] << "\t" << spaceProb[i];
    }
    output << std::endl << sAlpha[31] << ":\t\t\t" << spaceProb[31];

    output << std::endl << "\nentropy of chars without spaces:  " << entr;
    output << std::endl << "entropy of chars with spaces:\t" << spaceEntr;

    std::cout << "Monogram statistics recorded" << std::endl;

    output.close();
}

std::string cleanText(std::string &text)
{
    std::wstring wtext = toUnicode(text.c_str(), text.length());
    std::wstring wtextFull = leaveRussianText(wtext);
    std::wstring wtextClean = replaceUnnecessary(wtextFull);
    std::string textClean = toUTF8(text.length(), wtextClean);

    return textClean;
}

std::wstring toUnicode(const char* text, int textSize)
{
    int wtextSize = MultiByteToWideChar(CP_UTF8, 0, text, textSize, 0, 0);
    wchar_t* wbuffer = (wchar_t*)malloc(sizeof(wchar_t) * wtextSize + 2);
    memset(wbuffer, 0, sizeof(wchar_t) * wtextSize + 2);
    MultiByteToWideChar(CP_UTF8, 0, text, textSize, wbuffer, sizeof(wchar_t) * wtextSize + 2);

    std::wstring wtext(wbuffer);
    std::cout << "Converted to Unicode\n" << std::endl;

    return wtext;
}

std::wstring leaveRussianText(std::wstring wtext)
{
    wchar_t* wbuffer = (wchar_t*)malloc(sizeof(wchar_t) * wtext.length() + 2);
    memset(wbuffer, 0, sizeof(wchar_t) * wtext.length() + 2);

    for (int i = 0; i < wtext.length(); i++)
    {
        if (wtext[i] >= L'а' && wtext[i] <= L'я' || wtext[i] >= L'А' && wtext[i] <= L'Я' || wtext[i] == L' ')
        {
            wbuffer[i] = wtext[i];
        }
        else
        {
            wbuffer[i] = L' ';
        }
    }

    std::wstring wtextFull(wbuffer);
    std::cout << "Everything exept russian letters and spaces removed\n" << std::endl;
    return wtextFull;
}

std::wstring replaceUnnecessary(std::wstring wtextFull)
{
    for (int i = 0; i < 32; i++)
    {
        std::replace( wtextFull.begin(), wtextFull.end(), wbigAlpha[i], walpha[i]);
    }

    std::cout << "Capital letters removed" << std::endl;

    std::replace( wtextFull.begin(), wtextFull.end(), L'ё', L'е');
    std::replace( wtextFull.begin(), wtextFull.end(), L'ъ', L'ь');
    std::cout << "Odd letters removed" << std::endl;

    wtextFull.erase(std::unique_copy(wtextFull.begin(), wtextFull.end(), wtextFull.begin(), [](char c1, char c2){ return c1 == ' ' && c2 == ' '; }), wtextFull.end());
    std::cout << "Odd spaces removed\n" << std::endl;

    return wtextFull;
}

std::string toUTF8(int textSize, std::wstring wtextFull)
{
    char* text = (char*)malloc(textSize);

    memset(text, 0, textSize);

    WideCharToMultiByte(CP_UTF8, 0, wtextFull.c_str(), wtextFull.length(), text, textSize, 0, 0);

    std::string textFull(text);
    std::cout << "Converted to UTF-8\n" << std::endl;

    return textFull;
}

std::string readText()
{
    std::ifstream input("input.txt");
    std::string full, part;

    std::getline(input, full);
    while (!input.std::ios::eof())
    {
        std::getline(input, part);
        if (!part.empty())
        {
            full += " " + part;
        }
    }

    input.close();
    std::cout << "Text gathered\n" << std::endl;

    return full;
}
