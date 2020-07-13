#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString eight2two(QString n);
    QString ten2two(QString n);
    QString sixteen2two(QString n);
    QString two2eight(QString n);
    QString two2ten(QString n);
    QString two2sixteen(QString n);
    void convert(QString vis,QString v,QString v2is,QString *v2);
    void compute();

private:
    //layout
    QWidget *m_widget;
    QHBoxLayout *a_hbox;
    QHBoxLayout *b_hbox;
    QHBoxLayout *m_hbox;
    QVBoxLayout *m_vbox;
    //a
    QLineEdit *a_line;
    QComboBox *a_f_combo;
    QLineEdit *a_f_line;
    QComboBox *a_t_combo;
    QLineEdit *a_t_line;
    QPushButton *a_trans;
    //b
    QLineEdit *b_line;
    QComboBox *b_f_combo;
    QLineEdit *b_f_line;
    QComboBox *b_t_combo;
    QLineEdit *b_t_line;
    QPushButton *b_trans;
    //ab
    QComboBox *m_t_combo;
    QLineEdit *m_a_line;
    QComboBox *m_a_combo;
    QLineEdit *m_b_line;
    QLineEdit *m_e_line;
    QLineEdit *m_v_line;
    QPushButton *m_trans;
    //args
    QStringList isList;
    QStringList aList;
};

#endif // MAINWINDOW_H
