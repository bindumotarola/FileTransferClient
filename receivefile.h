#ifndef RECEIVEFILE_H
#define RECEIVEFILE_H

#include <QWidget>
#include "servercliant.h"

namespace Ui {
class ReceiveFile;
}

class ReceiveFile : public QWidget
{
    Q_OBJECT
    
public:
    explicit ReceiveFile(QWidget *parent = 0);
    ~ReceiveFile();
    
private:
    Ui::ReceiveFile *ui;
    ServerCliant *cliant;

private slots:
    void getStudentFiles();
    void getFileFormOneStudent();
};

#endif // RECEIVEFILE_H
