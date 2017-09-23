#include "downloadrunobject.h"
#include "downloadinitobject.h"

#include <QProcess>
#include <QApplication>

class DownloadRunObjectPrivate : public DownloadPrivate<DownloadRunObject>
{
public:
    DownloadRunObjectPrivate();
    ~DownloadRunObjectPrivate();

    QProcess *m_process;

};

DownloadRunObjectPrivate::DownloadRunObjectPrivate()
{
    m_process = nullptr;
}

DownloadRunObjectPrivate::~DownloadRunObjectPrivate()
{
    delete m_process;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
///
///
DownloadRunObject::DownloadRunObject(QObject *parent)
    : QObject(parent)
{
    DOWNLOAD_INIT_PRIVATE;
    DOWNLOAD_D(DownloadRunObject);

    d->m_process = new QProcess(this);
    connect(d->m_process, SIGNAL(finished(int)), SLOT(finished(int)));
}

void DownloadRunObject::checkValid()
{
    DownloadInitObject object;
    object.checkValid();
}

void DownloadRunObject::run(int argc, char **argv)
{
    DOWNLOAD_D(DownloadRunObject);
    QStringList list(APPNAME);
    if(argc == 3)
    {
        list << argv[1] << argv[2];
    }

    d->m_process->start(S_TTKSERVICE_FULL, list);
}

void DownloadRunObject::finished(int code)
{
     if(code == 0)
     {
         qDebug() << "Application exit success!";
     }
     else
     {
         qDebug() << "Application run error, please run TTKService instead!";
     }

     qApp->quit();
}
