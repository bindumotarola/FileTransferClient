#include "removestudent.h"
#include "ui_removestudent.h"

RemoveStudent::RemoveStudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoveStudent)
{
    ui->setupUi(this);

    ClassNameFilePath="D:/dk work/Motarola/project/";
    QFile allclassesfile(ClassNameFilePath+"class.txt");
    if(!allclassesfile.open(QFile::ReadOnly|QFile::Text))
    {
        //QDebug()<< "cant open";
    }
    QTextStream getClassNames(&allclassesfile);
    QString classNames =getClassNames.readAll();
    ui->comboBox->addItems(classNames.split(","));
    ui->comboBox_2->addItems(classNames.split(","));

    ui->radioButton->setChecked(true);
    ui->groupBox_2->setEnabled(false);
}

RemoveStudent::~RemoveStudent()
{
    delete ui;
}

void RemoveStudent::removeStudent()

{
    QFile Classfile(ClassNameFilePath+ui->comboBox->currentText().append(".txt"));
    if(!Classfile.open(QFile::ReadWrite|QFile::Text))
    {
        QMessageBox::information(this,"Error","Cant Open Class.txt file");
    }
    else
    {

        QTextStream getStudentNames(&Classfile);
        QString StudentNames =getStudentNames.readAll();
        if(StudentNames.contains(ui->lineEdit->text()))
        {
            if(StudentNames.endsWith(ui->lineEdit->text()))
            {
                StudentNames.remove(","+ui->lineEdit->text());
               // qDebug()<<"file inclue"<<StudentNames;
                Classfile.remove();

            }
            else
            {
                StudentNames.remove(ui->lineEdit->text()+",");
                Classfile.remove();

            }

            QFile newstudentClassFile(ClassNameFilePath+ui->comboBox->currentText().append(".txt"));
             if(!newstudentClassFile.open(QFile::Append|QFile::Text))
             {
                 //QDebug()<< "cant open";
             }
             else {
                 QTextStream out(&newstudentClassFile);
                 out <<StudentNames;
                 newstudentClassFile.close();
                 QMessageBox::information(this,"Success","Studnet Removed");
                 ui->lineEdit->clear();
             }

        }
        else
        {
            QMessageBox::information(this,"Error","there is no Student name like "+ui->lineEdit->text());

        }





    }


}

void RemoveStudent::removeClass()
{

    QFile allclassesfile(ClassNameFilePath+"class.txt");
    if(!allclassesfile.open(QFile::ReadWrite|QFile::Text))
    {
        //QDebug()<< "cant open";
    }
    else
    {

        QTextStream getClassNames(&allclassesfile);
        QString classNames =getClassNames.readAll();
        if(classNames.endsWith(ui->comboBox_2->currentText()))
        {
            classNames.remove(","+ui->comboBox_2->currentText());
            qDebug()<<"file inclue"<<classNames;
            allclassesfile.remove();


        }
        else
        {
            classNames.remove(ui->comboBox_2->currentText().append(","));
            allclassesfile.remove();


        }

        //remove specific class text file
         qDebug()<<ClassNameFilePath+ui->comboBox_2->currentText().append(".txt");
         QFile::remove(ClassNameFilePath+ui->comboBox_2->currentText().append(".txt"));


         //recreate class file with nondeleded classnemes
       QFile newallclassesfile(ClassNameFilePath+"class.txt");
        if(!newallclassesfile.open(QFile::Append|QFile::Text))
        {
            //QDebug()<< "cant open";
        }
        else {
            QTextStream out(&newallclassesfile);
            out <<classNames;
            newallclassesfile.close();
        }


        ui->comboBox->removeItem(ui->comboBox_2->currentIndex());
        ui->comboBox_2->removeItem(ui->comboBox_2->currentIndex());
        QMessageBox::information(this,"Success","Class Removed");

    }


}


void RemoveStudent::removeStudentRadio()
{
    ui->groupBox_2->setEnabled(false);
    ui->groupBox->setEnabled(true);

}

void RemoveStudent::removeClassRedio()
{

    ui->groupBox->setEnabled(false);
    ui->groupBox_2->setEnabled(true);
}
