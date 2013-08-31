#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QFileDialog>
namespace Ui {
class AddStudent;
}

class AddStudent : public QWidget
{
    Q_OBJECT
    
public:
    explicit AddStudent(QWidget *parent = 0);
    ~AddStudent();

private slots:
    void createNewClass();
    void existingClassRadio();
    void newClassRadio();
    void addNewStudent();
    
private:
    Ui::AddStudent *ui;
};

#endif // ADDREMOVESTUDENT_H
