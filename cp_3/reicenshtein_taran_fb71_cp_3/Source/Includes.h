#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <boost/algorithm/string.hpp>

// constants
//std::string rus_alpha = "אבגדהוזחטיךכלםמןנסעףפץצקרשûü‎‏ÿ";
std::string rus_alpha = "אבגדהוזחטיךכלםמןנסעףפץצקרשüû‎‏ÿ";
const int alpha_size = 31;
const int m = 31 * 31;
const int magic_pairs[21] = { 545,436,417,324,168,76,411,496,403,510,572,107,451,13,438,479,501,537,450,452,481 };
//