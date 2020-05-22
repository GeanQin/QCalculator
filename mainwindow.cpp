#include "mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(525,100);
    setWindowTitle("多进制计算器");

    a = new QLineEdit();
    a->setParent(this);
    a->setText("A:");
    a->setReadOnly(true);
    a->resize(25,25);

    b = new QLineEdit();
    b->setParent(this);
    b->setText("B:");
    b->setReadOnly(true);
    b->resize(25,25);
    b->move(0,25);

    ais=new QComboBox();
    ais->setParent(this);
    ais->move(25,0);
    ais->resize(75,25);

    bis=new QComboBox();
    bis->setParent(this);
    bis->move(25,25);
    bis->resize(75,25);

    av=new QLineEdit();
    av->setParent(this);
    av->resize(150,25);
    av->move(100,0);
    av->setPlaceholderText("原本值");

    bv=new QLineEdit();
    bv->setParent(this);
    bv->resize(150,25);
    bv->move(100,25);
    bv->setPlaceholderText("原本值");

    a2is=new QComboBox();
    a2is->setParent(this);
    a2is->move(250,0);
    a2is->resize(75,25);

    b2is=new QComboBox();
    b2is->setParent(this);
    b2is->move(250,25);
    b2is->resize(75,25);

    a2v= new QLineEdit();
    a2v->setParent(this);
    a2v->setReadOnly(true);
    a2v->resize(150,25);
    a2v->move(325,0);

    b2v = new QLineEdit();
    b2v->setParent(this);
    b2v->setReadOnly(true);
    b2v->resize(150,25);
    b2v->move(325,25);

    ac=new QPushButton();
    ac->setParent(this);
    ac->setText("转换");
    ac->resize(50,25);
    ac->move(475,0);

    bc=new QPushButton();
    bc->setParent(this);
    bc->setText("转换");
    bc->resize(50,25);
    bc->move(475,25);

    cis=new QComboBox();
    cis->setParent(this);
    cis->move(60,75);
    cis->resize(75,25);

    ca= new QLineEdit();
    ca->setParent(this);
    ca->setText("A");
    ca->setReadOnly(true);
    ca->setAlignment(Qt::AlignCenter);
    ca->resize(25,25);
    ca->move(135,75);

    cal=new QComboBox();
    cal->setParent(this);
    cal->move(160,75);
    cal->resize(50,25);

    cb = new QLineEdit();
    cb->setParent(this);
    cb->setText("B");
    cb->setAlignment(Qt::AlignCenter);
    cb->setReadOnly(true);
    cb->resize(25,25);
    cb->move(210,75);

    ce = new QLineEdit();
    ce->setParent(this);
    ce->setText("=");
    ce->setAlignment(Qt::AlignCenter);
    ce->setReadOnly(true);
    ce->resize(25,25);
    ce->move(235,75);

    ret = new QLineEdit();
    ret->setParent(this);
    ret->setReadOnly(true);
    ret->resize(150,25);
    ret->move(260,75);

    retc=new QPushButton();
    retc->setParent(this);
    retc->setText("运算");
    retc->resize(50,25);
    retc->move(410,75);

    isList<<"2进制"<<"8进制"<<"10进制"<<"16进制";
    ais->addItems(isList);
    bis->addItems(isList);
    a2is->addItems(isList);
    b2is->addItems(isList);
    cis->addItems(isList);

    calList<<"+"<<"-"<<"*"<<"/"<<"&"<<"|"<<"^";
    cal->addItems(calList);

    connect(ac,&QPushButton::clicked,this,&MainWindow::a2vShow);
    connect(bc,&QPushButton::clicked,this,&MainWindow::b2vShow);
    connect(retc,&QPushButton::clicked,this,&MainWindow::retShow);
}

void MainWindow::convert(QString sais,QString sav,QString sa2is,QString *sa2v){
    if(!sais.compare("2进制")){
        for(int i=0;i<sav.length();i++){
            if(sav[i].unicode()>'1'||sav[i].unicode()<'0'){
                *sa2v="输入有误";
                return;
            }
        }
        if(!sa2is.compare("10进制")){
            int tmp=0;
            for(int i=0;i<sav.length();i++){
                int tomul=1;
                for(int j=0;j<sav.length()-1-i;j++){
                    tomul=tomul*2;
                }
                tmp=tmp+(sav[i].unicode()-'0')*tomul;
            }
            *sa2v=QString::number(tmp);
        }else if(!sa2is.compare("8进制")){
            int count=(sav.length()+2)/3;
            QString tmp="";
            int ttmp;
            for(int i=count-1;i>=0;i--){
                int j=sav.length()-1-(count-i-1)*3;
                if(j>1){
                    ttmp=(sav[j].unicode()-'0')*1+(sav[j-1].unicode()-'0')*2+(sav[j-2].unicode()-'0')*4;
                    tmp[i]=(char)(ttmp+'0');
                }else if(j==1){
                    ttmp=(sav[j].unicode()-'0')*1+(sav[j-1].unicode()-'0')*2;
                    tmp[i]=(char)(ttmp+'0');
                }else{
                    ttmp=(sav[j].unicode()-'0');
                    tmp[i]=(char)(ttmp+'0');
                }
            }
            *sa2v=tmp;
        }else if(!sa2is.compare("16进制")){
            int count=(sav.length()+3)/4;
            QString tmp="";
            int ttmp;
            for(int i=count-1;i>=0;i--){
                int j=sav.length()-1-(count-i-1)*4;
                if(j>2){
                    ttmp=(sav[j].unicode()-'0')*1+(sav[j-1].unicode()-'0')*2+(sav[j-2].unicode()-'0')*4+(sav[j-3].unicode()-'0')*8;
                    if(ttmp>9){
                        tmp[i]=(char)(ttmp-10+'A');
                    }else{
                        tmp[i]=(char)(ttmp+'0');
                    }
                }else if(j==2){
                    ttmp=(sav[j].unicode()-'0')*1+(sav[j-1].unicode()-'0')*2+(sav[j-2].unicode()-'0')*4;
                    tmp[i]=(char)(ttmp+'0');
                }else if(j==1){
                    ttmp=(sav[j].unicode()-'0')*1+(sav[j-1].unicode()-'0')*2;
                    tmp[i]=(char)(ttmp+'0');
                }else{
                    ttmp=(sav[j].unicode()-'0');
                    tmp[i]=(char)(ttmp+'0');
                }
            }
            *sa2v=tmp;
        }else{
            *sa2v="不用算";
        }
    }else if(!sais.compare("8进制")){
        int tmp;
        QString stmp="";
        for(int i=0;i<sav.length();i++){
            tmp=ten2two(sav[i].unicode()-'0');
            if(sav[i].unicode()>'7'||sav[i].unicode()<'0'){
                *sa2v="输入有误";
                return;
            }
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
        if(!sa2is.compare("2进制")){
            *sa2v=stmp;
        }else if(!sa2is.compare("10进制")){
            convert("2进制",stmp,"10进制",sa2v);
        }else if(!sa2is.compare("16进制")){
            convert("2进制",stmp,"16进制",sa2v);
        }else{
            *sa2v="不用算";
        }
    }else if(!sais.compare("10进制")){
        for(int i=0;i<sav.length();i++){
            if(sav[i].unicode()>'9'||sav[i].unicode()<'0'){
                *sa2v="输入有误";
                return;
            }
        }
        int tmp=sav.toInt();
        tmp=ten2two(tmp);
        if(!sa2is.compare("2进制")){
            *sa2v=QString::number(tmp);
        }else if(!sa2is.compare("8进制")){
            QString stmp=QString::number(tmp);
            convert("2进制",stmp,"8进制",sa2v);
        }else if(!sa2is.compare("16进制")){
            QString stmp=QString::number(tmp);
            convert("2进制",stmp,"16进制",sa2v);
        }else{
            *sa2v="不用算";
        }
    }else{
        int tmp;
        QString stmp="";
        for(int i=0;i<sav.length();i++){
            if(sav[i].unicode()>='0'&&sav[i].unicode()<='9'){
                tmp=ten2two(sav[i].unicode()-'0');
            }else if(sav[i].unicode()>='A'&&sav[i].unicode()<='F'){
                tmp=ten2two(sav[i].unicode()-'7');
            }else{
                *sa2v="输入有误";
                return;
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
        if(!sa2is.compare("2进制")){
            *sa2v=stmp;
        }else if(!sa2is.compare("8进制")){
            convert("2进制",stmp,"8进制",sa2v);
        }else if(!sa2is.compare("10进制")){
            convert("2进制",stmp,"10进制",sa2v);
        }else{
            *sa2v="不用算";
        }
    }
}

int MainWindow::ten2two(int n)
{
    if(n<2){
        return n;
    }else{
        return ten2two(n/2)*10+n%2;
    }
}

void MainWindow::a2vShow(){
    QString str="";
    convert(ais->currentText(),av->text(),a2is->currentText(),&str);
    a2v->setText(str);
}

void MainWindow::b2vShow(){
    QString str="";
    convert(bis->currentText(),bv->text(),b2is->currentText(),&str);
    b2v->setText(str);
}

void MainWindow::retShow(){
    int iav;
    int ibv;
    int iret;
    QString stmp;

    if(ais->currentText().compare("10进制")){
        convert(ais->currentText(),av->text(),"10进制",&stmp);
        iav=stmp.toInt();
    }else{
        iav=av->text().toInt();
    }
    qDebug()<<iav;

    if(bis->currentText().compare("10进制")){
        convert(bis->currentText(),bv->text(),"10进制",&stmp);
        ibv=stmp.toInt();
    }else{
        ibv=bv->text().toInt();
    }
    qDebug()<<ibv;

    if(!cal->currentText().compare("+")){
        iret=iav+ibv;
    }else if(!cal->currentText().compare("-")){
        iret=iav-ibv;
    }else if(!cal->currentText().compare("*")){
        iret=iav*ibv;
    }else if(!cal->currentText().compare("/")){
        iret=iav/ibv;
    }else if(!cal->currentText().compare("&")){
        iret=iav&ibv;
    }else if(!cal->currentText().compare("|")){
        iret=iav|ibv;
    }else if(!cal->currentText().compare("^")){
        iret=iav^ibv;
    }

    if(cis->currentText().compare("10进制")){
        convert("10进制",QString::number(iret),cis->currentText(),&stmp);
        ret->setText(stmp);
    }else{
        ret->setText(QString::number(iret));
    }
}

MainWindow::~MainWindow()
{

}
