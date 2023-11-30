#include <iostream>
#include <random>
#include <string>
#include <array>
#include <map>

namespace TEST {
	bool isHere(char& letter, std::string& targetList) { return (std::find(targetList.begin(), targetList.end(), letter) != targetList.end()); }
};

std::string generatePassword(int& nbrChars) {
	std::random_device rd;
	std::mt19937 g(rd());

	std::array<int, 4> choice {1, 2, 3, 4};
	std::map<int, std::string> pattern{{0, "abcdefghijklmnopqrstuvwxyz"}, { 1, "ABCDEFGHIJKLMNOPQRSTUVWXYZ" }, { 2, "0123456789" }, { 3, "!@#$%^&*()_+" }};
	std::string password = "";

	while (password.size() < nbrChars) {
		std::shuffle(choice.begin(), choice.end(), rd);
		switch (choice[0])
		{
		case 1:
			std::shuffle(pattern[0].begin(), pattern[0].end(), rd);
			password += pattern[0][0];
			break;
		case 2:
			std::shuffle(pattern[1].begin(), pattern[1].end(), rd);
			password += pattern[1][0];
			break;
		case 3:
			std::shuffle(pattern[2].begin(), pattern[2].end(), rd);
			password += pattern[2][0];
			break;
		case 4:
			std::shuffle(pattern[3].begin(), pattern[3].end(), rd);
			password += pattern[3][0];
			break;
		}

	}

	std::array<int, 4> count {0, 0, 0, 0};



	for (auto& letter : password) {
		if (TEST::isHere(letter, pattern[0])) { count[0]++; }
		else if (TEST::isHere(letter, pattern[1])) { count[1]++; }
		else if (TEST::isHere(letter, pattern[2])) { count[2]++; }
		else { count[3]++; }
	}

	int checkmax = -1; int checkmin = -1;
	for (int position = 0; position < count.size(); position++ ) { if (count[position] > checkmax) { checkmax = position; } else if (count[position] == 0) { checkmin = position; } }

	if (checkmin != -1) {
		for (int i = password.size() - 1; i >= 0; --i) {
			for (const auto& letter : pattern[checkmax]) {
				if (password[i] == letter) {
					password[i] = pattern[checkmin][2];
					break;
				}
			}
		}
	}
	return password;
}

int main() {

	int nbrChars = 0;

	std::cout << "Combien de carateres ? [12-16]: ";
	std::cin >> nbrChars;

	if (nbrChars < 12) { nbrChars = 12; std::cout << "Nombre caracteres choisi: 12" << std::endl; }
	if (nbrChars > 16) { nbrChars = 16; std::cout << "Nombre caracteres choisi: 16" << std::endl; }

	std::string newPassword = "";
	newPassword += generatePassword(nbrChars);

	std::cout << "Voici le mot de passe genere : " << newPassword << std::endl;

	return 0;
}