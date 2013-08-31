#include "servercliant.h"

ServerCliant::ServerCliant(QObject *parent) :
    QObject(parent)
{
}


//Command argument contain wether command is upload or download
//if download also provide filename and if upload porvide path of file
void ServerCliant::test(QString Command,QString ClassFilepath)
{
    DownloadStrted=0;
    downloadFilePath ="D:/dk work/Motarola/project/teacher/";



    int pos = Command.indexOf(" ");
    CCommand = Command.mid(0,pos).trimmed();
    fileNameOrPath = Command.mid(pos + 1).trimmed();

    //full path of the class or if scecific student index
    ClassName =ClassFilepath;



    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(bytesWritten(qint64 )),this,SLOT(bytesWritten(qint64 )));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));


    qDebug()<<"conneting...";

    socket->connectToHost("127.0.0.1",1234);

    if(!socket->waitForConnected(5000))
    {
        qDebug()<<"Error:"<<socket->errorString();
    }

}



void ServerCliant::connected()
{
    qDebug()<<"connected";
    QString init="INIT Start \n";
    socket->write(init.toLatin1());
    socket->waitForBytesWritten(5000);
    qDebug() << "ClientCommand:"<<init.toLatin1();
}

void ServerCliant::disconnected()
{

    qDebug()<<"disconnected";
}

void ServerCliant::readyRead()
{
    if(DownloadStrted==0)
    {
        mCommandBuffer.append(socket->readAll());
        if(mCommandBuffer.endsWith('\n'))
        {
            ProcessCommand(mCommandBuffer);
            mCommandBuffer.clear();
        }
        //qDebug()<<mCommandBuffer;

    }
    else
    {

        DoDownload(socket->readAll());


    }


}

void ServerCliant::bytesWritten(qint64 bytes)
{
    qDebug()<<bytes;

}


void ServerCliant::ProcessCommand(QByteArray ClientCommand)
{
    ExecuteCommand(ClientCommand);


}

void ServerCliant::ExecuteCommand(QByteArray ClientCommand)
{
    try
    {
        QByteArray Command = "";
        QByteArray Arg = "";

        if(ClientCommand.contains(" "))
        {
            //Contains arquments
            int pos = ClientCommand.indexOf(" ");
            Command = ClientCommand.mid(0,pos).trimmed();
            Arg = ClientCommand.mid(pos + 1);
        }
        else
        {
            //No arquments
            Command = ClientCommand.trimmed();
        }

        qDebug() << "ServerReplay: " << Command << " " << Arg<<"\n";


        if(Command=="INIT")
        {
            DoINIT(Arg.trimmed());

        }
        else if(Command=="DOWNSTART")
        {
            DoNewDownload(Arg);
        }





    }
    catch(QString err)
    {
        //SendResponse(550,err);
    }
    catch(...)
    {
        //SendResponse(550,"Unknown error in ExecuteCommand()");
    }
}

void ServerCliant::DoINIT(QByteArray Arg)
{

    QFile studentNames(ClassName);
    if(!studentNames.open(QFile::ReadOnly|QFile::Text))
    {
        qDebug()<< "Error can't open file";
    }
    QTextStream getClassNames(&studentNames);
    QString studentNameList =getClassNames.readAll();
    QStringList StudentList=studentNameList.split(",");


    foreach (QString student, StudentList)
    {
        if(student==Arg)
        {
            qDebug()<<" Success: student match";
            if(CCommand=="Download")
            {
                ToDownload();
                break;


            }
            if(CCommand=="Upload")
            {

                ToUpload();
                break;

            }

        }

    }



}



void ServerCliant::ToDownload()
{

    socket->write("DOWN "+fileNameOrPath.append("\n").toLatin1());
    qDebug()<<"ClientCommand:" <<"DOWN "+fileNameOrPath;

}


void ServerCliant::ToUpload()
{

    QString filename=fileNameOrPath.mid(fileNameOrPath.lastIndexOf("/")+1).trimmed();

    qDebug()<<filename;
    QString startUpload="START ";
    startUpload.append(filename);
    startUpload.append("FNEnd");

    socket->write(startUpload.toLatin1());

    qDebug()<<"ClientCommand:" <<startUpload;

    QFile file(fileNameOrPath);
    file.open(QIODevice::ReadOnly);
    while (!file.atEnd())
    {
        QByteArray buffer = file.read(1024 * 8);
        socket->write(buffer);
        socket->waitForBytesWritten(5000);
    }
    file.close();
    socket->write("End\n");
    socket->waitForBytesWritten(500);
    qDebug()<<"ClientCommand: Finish Upload" ;

}
void ServerCliant::DoNewDownload(QByteArray Arg)
{
    QByteArray fileName = "";
    QByteArray File = "";

    if(Arg.contains("FNEnd"))
    {
        //Contains arquments
        int pos = Arg.indexOf("FNEnd",0);
        fileName = Arg.mid(0,pos).trimmed();
        File = Arg.mid(pos + 5);

    }


    QString filepath=downloadFilePath;
    filepath.append(fileName);

    newfile= new QFile(filepath);
    if(newfile->exists())
    {
        newfile->remove();

    }
    if(!newfile->open(QIODevice::Append))
    {

        qDebug()<<"error";
    }
    else
    {
        if(File.endsWith("End\n"))
        {
            qDebug()<<"Download Started";

            newfile->write(File.mid(0,(File.length()-4)));
            newfile->close();
            DownloadStrted=0;

            qDebug()<<"Download Done";
        }
        else {
            qDebug()<<"Download Started";

            newfile->write(File);
            DownloadStrted=1;
        }




    }


}

void ServerCliant::DoDownload(QByteArray Arg)
{
    if(Arg.endsWith("End\n"))
    {
        qDebug()<<Arg;
        newfile->write(Arg.mid(0,(Arg.length()-4)));
        newfile->close();
        DownloadStrted =0;

        qDebug()<<"Download Done";



    }
    else
    {
        newfile->write(Arg);

    }

}
