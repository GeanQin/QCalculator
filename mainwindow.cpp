#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //args
    isList<<"2进制"<<"8进制"<<"10进制"<<"16进制";
    aList<<"+"<<"-"<<"*"<<"/"<<"&"<<"|"<<"^";
    //layout
    m_widget = new QWidget;
    a_hbox = new QHBoxLayout;
    b_hbox = new QHBoxLayout;
    m_hbox = new QHBoxLayout;
    m_vbox = new QVBoxLayout;
    m_widget->setLayout(m_vbox);
    this->setCentralWidget(m_widget);
    //a
    a_line = new QLineEdit;
    a_f_combo = new QComboBox;
    a_f_line = new QLineEdit;
    a_t_combo = new QComboBox;
    a_t_line = new QLineEdit;
    a_trans = new QPushButton;
    a_hbox->addWidget(a_line);
    a_line->setText("A:");
    a_line->setMaximumWidth(45);
    a_line->setReadOnly(true);
    a_hbox->addWidget(a_f_combo);
    a_f_combo->addItems(isList);
    a_hbox->addWidget(a_f_line);
    a_f_line->setPlaceholderText("原本值");
    a_hbox->addWidget(a_t_combo);
    a_t_combo->addItems(isList);
    a_hbox->addWidget(a_t_line);
    a_t_line->setReadOnly(true);
    a_hbox->addWidget(a_trans);
    a_trans->setText("转换");
    m_vbox->addLayout(a_hbox);
    //b
    b_line = new QLineEdit;
    b_f_combo = new QComboBox;
    b_f_line = new QLineEdit;
    b_t_combo = new QComboBox;
    b_t_line = new QLineEdit;
    b_trans = new QPushButton;
    b_hbox->addWidget(b_line);
    b_line->setText("B:");
    b_line->setMaximumWidth(45);
    b_line->setReadOnly(true);
    b_hbox->addWidget(b_f_combo);
    b_f_combo->addItems(isList);
    b_hbox->addWidget(b_f_line);
    b_f_line->setPlaceholderText("原本值");
    b_hbox->addWidget(b_t_combo);
    b_t_combo->addItems(isList);
    b_hbox->addWidget(b_t_line);
    b_t_line->setReadOnly(true);
    b_hbox->addWidget(b_trans);
    b_trans->setText("转换");
    m_vbox->addLayout(b_hbox);
    //ab
    m_t_combo = new QComboBox;
    m_t_combo->addItems(isList);
    m_a_line = new QLineEdit;
    m_a_line->setText("A");
    m_a_line->setMaximumWidth(45);
    m_a_line->setReadOnly(true);
    m_a_combo = new QComboBox;
    m_a_combo->addItems(aList);
    m_b_line = new QLineEdit;
    m_b_line->setText("B");
    m_b_line->setMaximumWidth(45);
    m_b_line->setReadOnly(true);
    m_e_line = new QLineEdit;
    m_e_line->setText("=");
    m_e_line->setMaximumWidth(45);
    m_e_line->setReadOnly(true);
    m_v_line = new QLineEdit;
    m_v_line->setReadOnly(true);
    m_trans = new QPushButton;
    m_trans->setText("运算");
    m_hbox->addWidget(m_t_combo);
    m_hbox->addWidget(m_a_line);
    m_hbox->addWidget(m_a_combo);
    m_hbox->addWidget(m_b_line);
    m_hbox->addWidget(m_e_line);
    m_hbox->addWidget(m_v_line);
    m_hbox->addWidget(m_trans);
    m_vbox->addLayout(m_hbox);
    //connect
    connect(a_trans,&QPushButton::clicked,this, [=](){
        QString str="";
        convert(a_f_combo->currentText(),a_f_line->text(),a_t_combo->currentText(),&str);
        a_t_line->setText(str);
    });
    connect(b_trans,&QPushButton::clicked,this, [=](){
        QString str="";
        convert(b_f_combo->currentText(),b_f_line->text(),b_t_combo->currentText(),&str);
        b_t_line->setText(str);
    });
    connect(m_trans,&QPushButton::clicked,this,&MainWindow::compute);
}

MainWindow::~MainWindow()
{

}

QString MainWindow::eight2two(QString n)
{
    int tmp;
    QString stmp;
    for(int i=0;i<n.length();i++){
        tmp=ten2two(n[i]+"").toInt();
        if(i!=0){
            if(tmp==1||tmp==0){
                stmp=stmp+"00"+QString::number(tmp);
            }else if(tmp==10||tmp==11){
                stmp=stmp+"0"+QString::number(tmp);
            }else{
                stmp=stmp+QString::number(tmp);
            }
        }else{
            stmp=stmp+QString::number(tmp);
        }
    }
    return stmp;
}

QString MainWindow::ten2two(QString n)
{
    int tmp = n.toInt();
    if(tmp<2){
        return n;
    }else{
        return QString::number(ten2two(QString::number(tmp/2)).toInt()*10+tmp%2);
    }
}

QString MainWindow::sixteen2two(QString n)
{
    int tmp;
    QString stmp;
    for(int i=0;i<n.length();i++){
        if(n[i].unicode()>='0'&&n[i].unicode()<='9'){
            tmp=ten2two(n[i]+"").toInt();
        }else if(n[i].unicode()>='A'&&n[i].unicode()<='F'){
            tmp=ten2two(QString::number(n[i].unicode()-'7')).toInt();
        }
        if(i!=0){
            if(tmp==1||tmp==0){
                stmp=stmp+"000"+QString::number(tmp);
            }else if(tmp==10||tmp==11){
                stmp=stmp+"00"+QString::number(tmp);
            }else if(tmp==100||tmp==101||tmp==110||tmp==111){
                stmp=stmp+"0"+QString::number(tmp);
            }else{
                stmp=stmp+QString::number(tmp);
            }
        }else{
            stmp=stmp+QString::number(tmp);
        }
    }
    return stmp;
}

QString MainWindow::two2eight(QString n)
{
    int count=(n.length()+2)/3;
    QString stmp="";
    int tmp;
    for(int i=count-1;i>=0;i--){
        int j=n.length()-1-(count-i-1)*3;
        if(j>1){
            tmp=(n[j].unicode()-'0')*1+(n[j-1].unicode()-'0')*2+(n[j-2].unicode()-'0')*4;
            stmp[i]=(char)(tmp+'0');
        }else if(j==1){
            tmp=(n[j].unicode()-'0')*1+(n[j-1].unicode()-'0')*2;
            stmp[i]=(char)(tmp+'0');
        }else{
            tmp=(n[j].unicode()-'0');
            stmp[i]=(char)(tmp+'0');
        }
    }
    return stmp;
}

QString MainWindow::two2ten(QString n)
{
    int tmp=0;
    for(int i=0;i<n.length();i++){
        int tomul=1;
        for(int j=0;j<n.length()-1-i;j++){
            tomul=tomul*2;
        }
        tmp=tmp+(n[i].unicode()-'0')*tomul;
    }
    return QString::number(tmp);
}

QString MainWindow::two2sixteen(QString n)
{
    int count=(n.length()+3)/4;
    QString stmp="";
    int tmp;
    for(int i=count-1;i>=0;i--){
        int j=n.length()-1-(count-i-1)*4;
        if(j>2){
            tmp=(n[j].unicode()-'0')*1+(n[j-1].unicode()-'0')*2+(n[j-2].unicode()-'0')*4+(n[j-3].unicode()-'0')*8;
            if(tmp>9){
                stmp[i]=(char)(tmp-10+'A');
            }else{
                stmp[i]=(char)(tmp+'0');
            }
        }else if(j==2){
            tmp=(n[j].unicode()-'0')*1+(n[j-1].unicode()-'0')*2+(n[j-2].unicode()-'0')*4;
            stmp[i]=(char)(tmp+'0');
        }else if(j==1){
            tmp=(n[j].unicode()-'0')*1+(n[j-1].unicode()-'0')*2;
            stmp[i]=(char)(tmp+'0');
        }else{
            tmp=(n[j].unicode()-'0');
            stmp[i]=(char)(tmp+'0');
        }
    }
    return stmp;
}

void MainWindow::convert(QString vis,QString v,QString v2is,QString *v2){
    if(!vis.compare("2进制")){
        for(int i=0;i<v.length();i++){
            if(v[i].unicode()>'1'||v[i].unicode()<'0'){
                *v2="输入有误";
                return;
            }
        }
        if(!v2is.compare("2进制")){
            *v2="不用算";
        }else if(!v2is.compare("8进制")){
            *v2=two2eight(v);
        }else if(!v2is.compare("10进制")){
            *v2=two2ten(v);
        }else if(!v2is.compare("16进制")){
            *v2=two2sixteen(v);
        }
    }else if(!vis.compare("8进制")){
        for(int i=0;i<v.length();i++){
            if(v[i].unicode()>'7'||v[i].unicode()<'0'){
                *v2="输入有误";
                return;
            }
        }
        if(!v2is.compare("2进制")){
            *v2=eight2two(v);
        }else if(!v2is.compare("8进制")){
            *v2="不用算";
        }else if(!v2is.compare("10进制")){
            *v2=eight2two(v);
            *v2=two2ten(*v2);
        }else if(!v2is.compare("16进制")){
            *v2=eight2two(v);
            *v2=two2sixteen(*v2);
        }
    }else if(!vis.compare("10进制")){
        for(int i=0;i<v.length();i++){
            if(v[i].unicode()>'9'||v[i].unicode()<'0'){
                *v2="输入有误";
                return;
            }
        }
        if(!v2is.compare("2进制")){
            *v2=ten2two(v);
        }else if(!v2is.compare("8进制")){
            *v2=ten2two(v);
            *v2=two2eight(*v2);
        }else if(!v2is.compare("10进制")){
            *v2="不用算";
        }else if(!v2is.compare("16进制")){
            *v2=ten2two(v);
            *v2=two2sixteen(*v2);
        }
    }else if(!vis.compare("16进制")){
        for(int i=0;i<v.length();i++){
            if(!((v[i].unicode()<='9'&&v[i].unicode()>='0')||(v[i].unicode()<='F'&&v[i].unicode()>='A'))){
                *v2="输入有误";
                return;
            }
        }
        if(!v2is.compare("2进制")){
            *v2=sixteen2two(v);
        }else if(!v2is.compare("8进制")){
            *v2=sixteen2two(v);
            *v2=two2eight(*v2);
        }else if(!v2is.compare("10进制")){
            *v2=sixteen2two(v);
            *v2=two2ten(*v2);
        }else if(!v2is.compare("16进制")){
            *v2="不用算";
        }
    }
}

void MainWindow::compute(){
    int av;
    int bv;
    int v;
    QString stmp;

    if(a_f_combo->currentText().compare("10进制")){
        convert(a_f_combo->currentText(),a_f_line->text(),"10进制",&stmp);
        av=stmp.toInt();
    }else{
        av=a_f_line->text().toInt();
    }

    if(b_f_combo->currentText().compare("10进制")){
        convert(b_f_combo->currentText(),b_f_line->text(),"10进制",&stmp);
        bv=stmp.toInt();
    }else{
        bv=b_f_line->text().toInt();
    }

    if(!m_a_combo->currentText().compare("+")){
        v=av+bv;
    }else if(!m_a_combo->currentText().compare("-")){
        v=av-bv;
    }else if(!m_a_combo->currentText().compare("*")){
        v=av*bv;
    }else if(!m_a_combo->currentText().compare("/")){
        v=av/bv;
    }else if(!m_a_combo->currentText().compare("&")){
        v=av&bv;
    }else if(!m_a_combo->currentText().compare("|")){
        v=av|bv;
    }else if(!m_a_combo->currentText().compare("^")){
        v=av^bv;
    }

    if(m_t_combo->currentText().compare("10进制")){
        convert("10进制",QString::number(v),m_t_combo->currentText(),&stmp);
        m_v_line->setText(stmp);
    }else{
        m_v_line->setText(QString::number(v));
    }
}


