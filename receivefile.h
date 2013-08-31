#ifndef RECEIVEFILE_H
#define RECEIVEFILE_H

#include <QWidget>

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
};

#endif // RECEIVEFILE_H
