#ifndef SENDFILE_H
#define SENDFILE_H

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include "servercliant.h"


namespace Ui {
class SendFile;
}

class SendFile : public QWidget
{
    Q_OBJECT
    
public:
    explicit SendFile(QWidget *parent = 0);
    ~SendFile();

private slots:
    void selectFile();
    void uploadFile();
    
private:
    Ui::SendFile *ui;
    ServerCliant *cliant;
};

#endif // SENDFILE_H
