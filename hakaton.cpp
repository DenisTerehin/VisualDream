#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Hakaton.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	vector< vector<string> > plants = GetResultStreet();

	string ability = "Открытый грунт";
	string plant = "Огурец";
	int district = 3;

	if (ability == "Открытый грунт") {
		if (find(plants[district - 1].begin(), plants[district - 1].end(), plant) != plants[district - 1].end()) {
			cout << "Можно выращивать" << endl;
		} else cout << "Нельзя выращивать" << endl;
	}
	else {
		vector<string> dataPlant = GetResultParnik(plant);
		cout << "Можно посадить, соблюдая следующие условия:\n";
	}
}

vector<string> GetResultParnik(string plant)
{
	vector<string> plantData;

	ifstream plants;
	plants.open("D:/Hakaton/plants.txt");
	string namePlant;
	while (plant != namePlant)
		getline(plants, namePlant);
	for (int i = 0; i < 5; i++) {
		getline(plants, namePlant);
		string data = "";
		for (int j = 0; j < namePlant.length(); j++) {
			if ((namePlant[j] == ' ' && i != 3) || namePlant[j] == '\n') {
				plantData.push_back(data);
				data = "";
				continue;
			}
			if (namePlant[j] == ',' && i == 3) {
				data += ", ";
				continue;
			}
			data += namePlant[j];
		}
	}
	plants.close();
	return plantData;
}

vector< vector<string> > GetResultStreet()
{
	vector< vector<string> > plantsInRegion;

	ifstream regions;
	regions.open("D:/Hakaton/regions.txt");
	string nameRegion;
	while (getline(regions, nameRegion)) {

		vector<double> regTemp = tempDouble(regions);
		vector<double> regHm = Number(regions);
		vector<double> regPres = Number(regions);
		vector<string> regSoil = soilString(regions);
		vector<double> regPH = Number(regions);

		vector<string> plant;

		ifstream plants;
		plants.open("D:/Hakaton/plants.txt");
		string namePlant;
		while (getline(plants, namePlant)) {

			vector<string> month;
			vector<double> plantTemp = Number(plants);
			vector<double> plantHm = Number(plants);
			vector<double> plantPres = Number(plants);
			vector<string> plantSoil = soilString(plants);
			vector<double> plantPH = Number(plants);

			if (CompareTemp(plantTemp, regTemp, month)
				&& CompareSoil(plantSoil, regSoil)
				&& Compare(plantHm, regHm)
				&& Compare(plantPres, regPres)
				&& Compare(plantPH, regPH)) {

				plant.push_back(namePlant);
			}
			month.clear();
			getline(plants, namePlant);
		}
		plants.close();
		getline(regions, nameRegion);

		plantsInRegion.push_back(plant);
	}
	regions.close();

	return plantsInRegion;
}

bool Compare(std::vector<double>& plant, std::vector<double>& reg)
{
	if (reg[1] == 0) {
		if (plant[1] == 0) {
			if (plant[0] > reg[0])
				return false;
		}
		else if (plant[0] > reg[0] || reg[0] > plant[1])
			return false;
	} else if (plant[1] == 0) {
		if (plant[0] > reg[0])
			return false;
	}
	else if (plant[0] > reg[0] || reg[1] > plant[1])
		return false;

	return true;
}

bool CompareSoil(std::vector<std::string>& plantSoil, std::vector<std::string>& regSoil)
{
	int countSoil = 0;
	for (int i = 0; i < plantSoil.size(); i++)
		if (find(regSoil.begin(), regSoil.end(), plantSoil[i]) != regSoil.end())
			countSoil++;
	if (countSoil == 0) return false;
	return true;;
}

bool CompareTemp(std::vector<double>& plantTemp, std::vector<double>& regTemp, std::vector<std::string>& month)
{
	vector<string> nameMonth{ "April", "May", "June", "Jule", "August", "September" };
	for (int i = 0; i < regTemp.size(); i++) {
		vector<double> value(1, regTemp[i]);
		value.push_back(0);
		if (Compare(plantTemp, value)) {
			month.push_back(nameMonth[i]);
		}
	}
	if (month.size() == 0) return false;
	return true;
}

vector<double> Number(ifstream& input)
{
	vector<double> data;
	string dataString, dataOne = "", dataTwo = "";
	getline(input, dataString);
	int flag = 1;
	for (int i = 0; i < dataString.length(); i++) {
		if (dataString[i] == ' ') {
			flag = 0;
			continue;
		}
		if (flag) dataOne += dataString[i];
		else dataTwo += dataString[i];
	}
	data.push_back(atof(dataOne.c_str()));
	data.push_back(atof(dataTwo.c_str()));
	return data;
}

vector<string> soilString(ifstream& input)
{
	vector<string> data;
	string dataString, dataOne = "";
	getline(input, dataString);
	for (int i = 0; i < dataString.length(); i++) {
		if (dataString[i] == ',') {
			data.push_back(dataOne);
			dataOne = "";
			continue;
		}
		dataOne += dataString[i];
	}
	data.push_back(dataOne);
	return data;
}

vector<double> tempDouble(ifstream& input)
{
	vector<double> data;
	string dataString, dataOne = "";
	getline(input, dataString);
	for (int i = 0; i < dataString.length(); i++) {
		if (dataString[i] == ' ') {
			data.push_back(atof(dataOne.c_str()));
			dataOne = "";
			continue;
		}
		dataOne += dataString[i];
	}
	data.push_back(atof(dataOne.c_str()));
	return data;
}