#include "scanner.h"
#include "ui_scanner.h"
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextBrowser>
scanner::scanner(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::scanner)
{
    ui->setupUi(this);
    ui->plainTextread->setReadOnly(true);
}

scanner::~scanner()
{
    delete ui;
}


void scanner::on_pushButton_clicked()
{
    QFile file ("C:/Users/user/Documents/scanner/code.txt");
    QFile file2 ("C:/Users/user/Documents/scanner/result.txt");
    if(!file.open(QFile::ReadWrite | QFile::Truncate | QFile::Text)){
        QMessageBox::warning(this,"title","file is not opened");
    }
    if(!file2.open(QFile::ReadWrite | QFile::Truncate | QFile::Text)){
        QMessageBox::warning(this,"title","file is not opened");
    }
    file.resize(0);
    file2.resize(0);
    QTextStream out(&file);
    ui->plainTextread->clear();
    ui->plainTextread->setReadOnly(true);
    QString text= ui->plainTextWrite->toPlainText();
    out<<text;
    file.flush();
    file.close();
    int type=0;
    QTextStream output(&file2);
    file.open(QFile :: ReadWrite |QFile::Text);
    output <<"List of TokenValues and TokenTypes"<<endl;
    QString token="";
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line;
        QString s = "";
        bool error = false;
        line=in.readLine();
            int i = 0;
            while(i<line.length()) {

                if (line[i] == ' ') type = 1;
                else if ((line[i]).isLetter()) type = 2;
                else if (line[i].isDigit()) type = 3;
                else if (line[i] == '+' || line[i] == '*' || line[i] == '-' || line[i] == '/' || line[i]=='='|| line[i]=='!') type = 4;
                else if (line[i] == '(' || line[i] == ')' || line[i] == '<' || line[i] == ';' || line[i]==':' ) type = 5;
                else if (line[i] == '{') {
                    while(line[i] !='}'){
                    if(i==line.length()-1 &&line[i] != '}'){
                        line=in.readLine();
                        //error = true;
                        //break;
                    }
                    else{
                    while (i<=line.length()-1 && line[i] != '}') {
                        i++;
                    }
                    if(in.atEnd()){
                        output << line[i]<< ", "<<"Syntax Error:";
                        error = true;
                        break;
                    }
                    else{
                    i++;
                    }
                    }
                    }
                }
                else {
                    output << line[i]<< ", "<<"Syntax Error:";
                    error = true;
                    break;
                }

                switch (type) {
                case 1:
                    i++;
                    break;
                case 2:
                    while ((line[i]).isLetter()) {
                        token += line[i];
                        i++;
                    }
                    if ((line[i]).isDigit()) {
                        while ((line[i]).isDigit()) {
                            if(i<line.length()){
                            token += line[i];
                            i++;
                        }
                        }
                        output << token << ", " << "Syntax ERROR" << endl;
                        error = true;
                        break;
                    }
                    if (token == "if"){
                        output << token << ", " << "IF Token" << endl;
                    }
                    else if (token == "else") {
                        output << token << ", " << "ELSE Token" << endl;
                    }
                    else if (token == "then") {
                        output << token << ", " << "THEN Token" << endl;
                    }
                    else if (token == "end") {
                        output << token << ", " << "END Token" << endl;
                    }
                    else if (token == "repeat") {
                        output << token << ", " << "REPEAT Token" << endl;
                    }
                    else if (token == "until") {
                        output << token << ", " << "UNTIL Token" << endl;
                    }
                    else if (token == "read") {
                        output << token << ", " << "READ Token" << endl;
                    }
                    else if (token == "write") {
                        output << token << ", " << "WRITE Token" << endl;
                    }
                    else if (token == "return") {
                        output << token << ", " << "RETURN Token" << endl;
                    }
                    else if (token == "begin") {
                        output << token << ", " << "BEGIN Token" << endl;
                    }else if (token == "int") {
                        output << token << ", " << "INT Token" << endl;
                    }
                    else if (token == "string") {
                        output << token << ", " << "STRING Token" << endl;
                    }
                    else if (token == "real") {
                        output << token << ", " << "REAL Token" << endl;
                    }
                    else {
                        output << token << ", " << "Identifier" << endl;
                    }
                    token = "";
                    break;
                case 3:
                    while ((line[i]).isDigit()) {
                        token += line[i];
                        i++;
                    }
                    if ((line[i]).isLetter()) {
                        while ((line[i]).isLetter()) {
                            if(i<line.length()){
                            token += line[i];
                            i++;
                        }
                        }
                        output << token << ", " << "Syntax ERROR" << endl;
                        error = true;
                        break;
                    }
                    else{
                        output << token << ", " << "number" << endl;
                    }
                    s = "";
                    token = "";
                    break;
                case 4:
                    if (line[i] == '+' &&(line[i+1] == ' ' || line[i+1].isLetter() || line[i+1].isDigit())) {
                        token += '+';
                        output << token << ", " << "PLUS SIGN" << endl;
                    }
                    else if (line[i] == '-' &&(line[i+1] == ' ' || line[i+1].isLetter() || line[i+1].isDigit())) {
                        token += '-';
                        output << token << ", " << "MINUS SIGN" << endl;
                    }
                    else if (line[i] == '*' &&(line[i+1] == ' ' || line[i+1].isLetter() || line[i+1].isDigit())) {
                        token += '*';
                        output << token << ", " << "MULT SIGN" << endl;
                    }
                    else if (line[i] == '/' &&(line[i+1] == ' ' || line[i+1].isLetter() || line[i+1].isDigit())) {
                        token += '/';
                        output << token << ", " << "DIVIDE SIGN" << endl;
                    }
                    else if (line[i] == '=' &&(line[i+1] == ' ' || line[i+1].isLetter() || line[i+1].isDigit())) {
                        token += "=";
                        output << token << ", " << "ISEQUAL SIGN" << endl;
                    }

                    i++;

                    token = "";
                    break;
                case 5:
                    if (line[i] == '(' &&(line[i+1] == ' ' || line[i+1].isLetter() || line[i+1].isDigit())) {
                        token += '(';
                        output << token << ", " << "LEFT PARENTHESES" << endl;
                    }
                    else if (line[i] == ')' &&(line[i+1] == ' ' || line[i+1].isLetter() || line[i+1].isDigit())) {
                        token += ')';
                        output << token << ", " << "RIGHT PARENTHESES" << endl;
                    }
                    else if (line[i] == '<' &&(line[i+1] == ' ' || line[i+1].isLetter() || line[i+1].isDigit())) {
                        token += '<';
                        output << token << ", " << "LESS THAN OPERATOR" << endl;
                    }
                    else if (line[i] == ';' &&(line[i+1] == ' ' || line[i+1].isLetter() || line[i+1].isDigit())) {
                        token += ';';
                        output << token << ", " << "SEMI COLON" << endl;
                    }
                    else if (line[i] == ':' &&(line[i+1]=='=')) {
                        token += ":=";
                        i++;
                        output << token << ", " << "ASSIGNMENT" << endl;
                    }

                    i++;

                    token = "";
                    break;
                }
                if (error) break;
            }

    }
    file2.flush();
    file2.close();
    file2.open(QFile :: ReadWrite |QFile::Text);
    ui->plainTextread->setPlainText(output.readAll());
    file2.close();
    file.close();

}
