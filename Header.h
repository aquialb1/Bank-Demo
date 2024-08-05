#pragma once
#include <iostream>
#include <string>

using namespace std;

class Account {
public:
	string name;
	string username;
	string password;

	float checking_value = 0;
};

int main();

void account_entry();