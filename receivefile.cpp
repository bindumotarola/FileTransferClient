#include "receivefile.h"
#include "ui_receivefile.h"

ReceiveFile::ReceiveFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReceiveFile)
{
    ui->setupUi(this);
}

ReceiveFile::~ReceiveFile()
{
    delete ui;
}

void ReceiveFile::getStudentFiles()
{
    cliant = new ServerCliant;
    QString uploadCommand="Download ";
    uploadCommand.append(ui->lineEdit->text());
    cliant->test(uploadCommand,"D:/dk work/Motarola/project/class1.txt");

}

void ReceiveFile::getFileFormOneStudent()
{

}
