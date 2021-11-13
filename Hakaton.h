#pragma once

std::vector<double> Number(std::ifstream& input);
bool Compare(std::vector<double>& plant, std::vector<double>& reg);
std::vector< std::vector<std::string> > GetResultStreet();
std::vector<std::string> GetResultParnik(std::string plant);
bool CompareSoil(std::vector<std::string>& plantSoil, std::vector<std::string>& regSoil);
bool CompareTemp(std::vector<double>& regTemp, std::vector<double>& plantTemp, std::vector<std::string>& month);
std::vector<std::string> soilString(std::ifstream& input);
std::vector<double> tempDouble(std::ifstream& input);

