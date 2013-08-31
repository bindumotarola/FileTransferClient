#ifndef REMOVESTUDENT_H
#define REMOVESTUDENT_H

#include <QWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class RemoveStudent;
}

class RemoveStudent : public QWidget
{
    Q_OBJECT
    
public:
    explicit RemoveStudent(QWidget *parent = 0);
    ~RemoveStudent();
    
private:
    Ui::RemoveStudent *ui;
    QString ClassNameFilePath;

private slots:
    void removeStudentRadio();
    void removeClassRedio();
    void removeStudent();
    void removeClass();
};

#endif // REMOVESTUDENT_H
