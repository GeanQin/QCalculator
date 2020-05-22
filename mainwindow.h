#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QStringList>
#include <QDebug>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void convert(QString sais,QString sav,QString sa2is,QString *sa2v);
    void a2vShow();
    void b2vShow();
    void retShow();
    int ten2two(int n);

private:
    QLineEdit *a;
    QLineEdit *b;
    QComboBox *ais;
    QComboBox *bis;
    QLineEdit *av;
    QLineEdit *bv;
    QComboBox *a2is;
    QComboBox *b2is;
    QLineEdit *a2v;
    QLineEdit *b2v;
    QPushButton *ac;
    QPushButton *bc;
    QComboBox *cis;
    QLineEdit *ca;
    QComboBox *cal;
    QLineEdit *cb;
    QLineEdit *ce;
    QLineEdit *ret;
    QPushButton *retc;
    QStringList isList;
    QStringList calList;

};

#endif // MAINWINDOW_H
