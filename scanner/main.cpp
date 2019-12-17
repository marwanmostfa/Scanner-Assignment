#include "scanner.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    scanner w;
    w.show();
    return a.exec();
}
