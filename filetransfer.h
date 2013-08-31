#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QMainWindow>
#include <QMessageBox>
#include "addstudent.h"
#include "sendfile.h"
#include "removestudent.h"
#include "receivefile.h"

namespace Ui {
class FileTransfer;
}

class FileTransfer : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FileTransfer(QWidget *parent = 0);
    ~FileTransfer();

    AddStudent *student;
    SendFile *sendNewFile;
    RemoveStudent *delStudent;
    ReceiveFile *receiveNewFile;

public slots:
    void sendFile();
    void receiveFile();
    void addStudent();
    void removeStudent();
    
private:
    Ui::FileTransfer *ui;
};

#endif // FILETRANSFER_H
