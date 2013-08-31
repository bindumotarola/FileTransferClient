#include "servercliant.h"

ServerCliant::ServerCliant(QObject *parent) :
    QObject(parent)
{
}

void ServerCliant::test(QString CArg,QString ClassFilepath)
{
    DownloadStrted=0;
    downloadFilePath ="D:/dk work/Motarola/project/teacher/";


    //Carg contarin download or upload command with path path means
    //if download path of the file if upload nameof the file
    int pos = CArg.indexOf(" ");
    CCommand = CArg.mid(0,pos).trimmed();
    Path = CArg.mid(pos + 1).trimmed();

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
//    try
//    {
//        //Append to the command buffer
//        mCommandBuffer.append(socket->readAll());

//       qDebug()<<mCommandBuffer;
//        //Check to see if it is the end of line
//        if(mCommandBuffer.endsWith('\n'))
//        {
//            ProcessCommand(mCommandBuffer);
//            mCommandBuffer.clear();
//        }

//    }
//    catch(QString err)
//    {
//        //SendResponse(550,err);
//    }
//    catch(...)
//    {
//        //SendResponse(550,"Unknown error in SocketReadyRead()");
//    }

}

void ServerCliant::bytesWritten(qint64 bytes)
{
    qDebug()<<bytes;

}


void ServerCliant::ProcessCommand(QByteArray ClientCommand)
{
    ExecuteCommand(ClientCommand);

//    try
//    {
//        //Some clients like to put multiple commands on a single packet command1<crlf>command2<crlf>
//        //Bad form yes but we have to deal with it regardless

//        QStringList Commands = ClientCommand.split("\n");

//        foreach(QString Command, Commands)
//        {
//            QString ClientCommand = Command.trimmed();
//            if(ClientCommand != "")
//            {
//                //Execute the command
//                ExecuteCommand(ClientCommand);
//            }
//        }
//    }
//    catch(QString err)
//    {
//        //SendResponse(550,err);
//    }
//    catch(...)
//    {
//        //SendResponse(550,"Unknown error in ProcessCommand()");
//    }
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

        qDebug() << "Client: " << Command << " " << Arg;


        if(Command=="INIT")
        {
            DoINIT(Arg.trimmed());

        }

        else if (Command=="RETR")
        {


            //DoDownload(Arg);

        }
        else if (Command=="DoSTOR")
        {


            //DoUpload(Arg);

        }
        else if(Command=="DOWNSTART")
        {
            DoNewDownload(Arg);
        }


//        QMetaObject metaObject = this->staticMetaObject;
//        QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("RequestCommands"));

//        switch(metaEnum.keysToValue(Command.toUpper().toAscii()))
//        {

//            // RFC 959  --------------------------------------------------
//            case HELP: // Lists all available commands
//            DoHelp();
//            break;

//            case QUIT: // Log out
//            DoQuit();
//            break;

//            case USER: // Username
//            DoUser(Arg);
//            break;


//        }


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
        //QDebug()<< "cant open";
    }
    QTextStream getClassNames(&studentNames);
    QString studentNameList =getClassNames.readAll();
    QStringList StudentList=studentNameList.split(",");


    foreach (QString student, StudentList)
    {
        qDebug()<<student;
        if(student==Arg)
        {
            qDebug()<<"student match";
                    if(CCommand=="Download")
                    {
                         ToDownload();


                    }
                    if(CCommand=="Upload")
                    {

                        ToUpload();

                    }

        }

    }



}



void ServerCliant::ToDownload()
{
    //qDebug()<<"command"<<"DOWN "+Path.append("\n").toLatin1();
    socket->write("DOWN "+Path.append("\n").toLatin1());


}


void ServerCliant::ToUpload()
{
    qDebug() << "LIST SEND FILE";
    QString filename=Path.mid(Path.lastIndexOf("/")+1).trimmed();

    qDebug()<<filename;
    QString startUpload="START ";
    startUpload.append(filename);
    startUpload.append("FNEnd");

    socket->write(startUpload.toLatin1());
    QFile file(Path);
    file.open(QIODevice::ReadOnly);
    while (!file.atEnd())
    {
        QByteArray buffer = file.read(1024 * 8);
        socket->write(buffer);
        socket->waitForBytesWritten(5000);
    }
    file.close();
    socket->write("End\n");

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
        //qDebug()<<"filposition"<<pos;
    }


    QString filepath=downloadFilePath;
    filepath.append(fileName);
    qDebug()<<filepath;

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

            qDebug()<<File.mid(0,(File.length()-4));
             newfile->write(File.mid(0,(File.length()-4)));
             newfile->close();
             DownloadStrted=0;
        }
        else {
            qDebug()<<"its herefdfdfdfdfdffdfdf";
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



      }
      else
      {
          newfile->write(Arg);
         // qDebug()<<Arg;

      }

  }
