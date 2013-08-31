#include "sendfile.h"
#include "ui_sendfile.h"

SendFile::SendFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendFile)
{
    ui->setupUi(this);

    QFile allclassesfile("D:/dk work/Motarola/project/class.txt");
    if(!allclassesfile.open(QFile::ReadOnly|QFile::Text))
    {
        //QDebug()<< "cant open";
    }
    QTextStream getClassNames(&allclassesfile);
    QString classNames =getClassNames.readAll();

    QStringList classList=classNames.split(",");
    ui->comboBox->addItems(classList);
}

SendFile::~SendFile()
{
    delete ui;
}



 void SendFile::selectFile()
{

     QString fileName = QFileDialog::getOpenFileName(this, tr("Open a Movie"),"D:/dk work/Motarola");
     ui->lineEdit_2->setText(fileName);

}

 void SendFile::uploadFile()
 {
     cliant = new ServerCliant;
     QString uploadCommand="Upload ";
     uploadCommand.append(ui->lineEdit_2->text());
     cliant->test(uploadCommand,"D:/dk work/Motarola/project/class1.txt");

 }
