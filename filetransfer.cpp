#include "filetransfer.h"
#include "ui_filetransfer.h"

FileTransfer::FileTransfer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileTransfer)
{
    ui->setupUi(this);
}

FileTransfer::~FileTransfer()
{
    delete ui;
}


void FileTransfer::sendFile()
{
    //QMessageBox::information(this,"Its here1","Its here1");
    sendNewFile = new SendFile;
    sendNewFile->show();

}

void FileTransfer::receiveFile()
{
    receiveNewFile = new ReceiveFile;
    receiveNewFile->show();
    //QMessageBox::information(this,"Its here","Its here2");

}

void FileTransfer::addStudent()
{
    student = new AddStudent;
    student->show();
    //QMessageBox::information(this,"Its here1","Its here3");

}

void FileTransfer::removeStudent()
{
    delStudent  = new RemoveStudent;
    delStudent->show();
     //QMessageBox::information(this,"Its here1","Its here3");

}
