#include "addstudent.h"
#include "ui_addstudent.h"

AddStudent::AddStudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddStudent)
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


    ui->radioButton->setChecked(true);
    ui->groupBox_2->setEnabled(false);
}

AddStudent::~AddStudent()
{
    delete ui;
}

void AddStudent::createNewClass()
{

    if(ui->lineEdit->text().size()==0)
    {
        QMessageBox::information(this,"Error","Please Enter Class Name");

    }
    if(ui->lineEdit_3->text().size()==0)
    {
        QMessageBox::information(this,"Error","Please Enter Students");

    }


    // create class.txt and enter new class name to class.txt file
    QFile allclassesfile("D:/dk work/Motarola/project/class.txt");
    if(allclassesfile.open(QFile::Append| QFile::Text))
    {
        if(allclassesfile.size()==0)
        {


            //create specific txt file for each class
            QString classfilepath="D:/dk work/Motarola/project/";
            classfilepath.append(ui->lineEdit->text());
            classfilepath.append(".txt");
            QFile classfile(classfilepath);
            if(classfile.exists())
            {
                QMessageBox::information(this,"Error","Already have this class plase enter another name");

            }
            else
            {
                if(classfile.open(QFile::Append| QFile::Text))
                {
                    QTextStream out2(&classfile);
                    out2 <<ui->lineEdit_3->text();
                    classfile.close();

                    QTextStream out(&allclassesfile);
                    out <<ui->lineEdit->text();
                    ui->comboBox->addItem(ui->lineEdit->text());
                    allclassesfile.close();
                    QMessageBox::information(this,"Success","New Class Created");
                    ui->lineEdit_3->clear();
                    ui->lineEdit->clear();

                }

            }



        }
        else
        {


            QString classfilepath="D:/dk work/Motarola/project/";
            classfilepath.append(ui->lineEdit->text());
            classfilepath.append(".txt");
            QFile classfile(classfilepath);
            if(classfile.exists())
            {
                QMessageBox::information(this,"Error","Already have this class plase enter another name");

            }
            else {

                if(classfile.open(QFile::Append| QFile::Text))
                {
                    QTextStream out2(&classfile);
                    out2 <<ui->lineEdit_3->text();
                    classfile.close();

                    QTextStream out(&allclassesfile);
                    out << ",";
                    out <<ui->lineEdit->text();
                     ui->comboBox->addItem(ui->lineEdit->text());
                    allclassesfile.close();
                    QMessageBox::information(this,"Success","New Class Created");
                    ui->lineEdit_3->clear();
                    ui->lineEdit->clear();

                }
            }



        }



    }
    else
    {
        //QDebug <<"cant open file";

    }



}

void AddStudent::addNewStudent()
{
    if(ui->lineEdit_2->text().size()==0)
    {
        QMessageBox::information(this,"Error","Please Enter Student name");

    }


    QString classfilepath="D:/dk work/Motarola/project/";
    classfilepath.append(ui->comboBox->currentText());
    classfilepath.append(".txt");
    QFile classfile(classfilepath);
    if(classfile.open(QFile::Append| QFile::Text))
    {
        QTextStream out(&classfile);
        out <<",";
        out <<ui->lineEdit_2->text();
         QMessageBox::information(this,"Success","New Studen Added");
         ui->lineEdit_2->clear();

    }

}

void AddStudent::existingClassRadio()
{


    ui->groupBox->setEnabled(false);
    ui->groupBox_2->setEnabled(true);




}

void AddStudent::newClassRadio()
{


     ui->groupBox_2->setEnabled(false);
     ui->groupBox->setEnabled(true);

}
