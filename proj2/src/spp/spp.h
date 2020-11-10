#pragma once
#include <vector>
#include <unordered_map>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>

std::list<std::list<std::string>> into_lines(std::istream &fin);
std::list<std::list<std::string>> file_inclusion(std::list<std::list<std::string>> lines);
std::string to_str(std::list<std::list<std::string>> lines);