#ifndef SCANNER_H
#define SCANNER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class scanner; }
QT_END_NAMESPACE

class scanner : public QMainWindow
{
    Q_OBJECT

public:
    scanner(QWidget *parent = nullptr);
    ~scanner();

private slots:
    void on_pushButton_clicked();

private:
    Ui::scanner *ui;
};
#endif // SCANNER_H
