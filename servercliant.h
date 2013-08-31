#ifndef SERVERCLIANT_H
#define SERVERCLIANT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFile>

class ServerCliant : public QObject
{
    Q_OBJECT
public:
    explicit ServerCliant(QObject *parent = 0);
    QTcpSocket *socket;
    void test(QString CArg,QString ClassFilepath);
    int DownloadStrted;
    QString downloadFilePath;


private:
    QByteArray mCommandBuffer;             //! The buffer holding the command
    QString CCommand; //!teacher sent details about download or upload
    QString Path;     //!teacher send command argument if upload filpath if download filename
    QString ClassName;
    void ProcessCommand(QByteArray ClientCommand);
    void ExecuteCommand(QByteArray ClientCommand);


    void ToDownload();
    void DoDownload(QByteArray Arg);
    void DoNewDownload(QByteArray Arg);
    void ToUpload();

    void DoINIT(QByteArray Arg);
    QFile *newfile;
    
signals:
    
public slots:
    void connected();
    void disconnected();
    void readyRead();
    void bytesWritten(qint64 bytes);

    
};

#endif // SERVERCLIANT_H
