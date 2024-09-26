#pragma once
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "sqlite3.h"

using namespace std;

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    cout << endl;
    return 0;
}

int main();