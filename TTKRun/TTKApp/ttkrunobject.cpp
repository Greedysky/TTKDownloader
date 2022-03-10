#include "ttkrunobject.h"
#include "downloadinitobject.h"

#include <QProcess>
#include <QApplication>

/*! @brief The class of the ttk run object private.
 * @author Greedysky <greedysky@163.com>
 */
class TTKRunObjectPrivate : public TTKPrivate<TTKRunObject>
{
public:
    TTKRunObjectPrivate();
    ~TTKRunObjectPrivate();

    QProcess *m_process;

};

TTKRunObjectPrivate::TTKRunObjectPrivate()
{
    m_process = nullptr;
}

TTKRunObjectPrivate::~TTKRunObjectPrivate()
{
    delete m_process;
}



TTKRunObject::TTKRunObject(QObject *parent)
    : QObject(parent)
{
    TTK_INIT_PRIVATE(TTKRunObject);
    TTK_D(TTKRunObject);

    d->m_process = new QProcess(this);
    connect(d->m_process, SIGNAL(finished(int)), SLOT(finished(int)));
}

void TTKRunObject::valid() const
{
    DownloadInitObject object;
    object.valid();
}

void TTKRunObject::run(int argc, char **argv) const
{
    TTK_D(TTKRunObject);

    QStringList list(APP_NAME);
    if(argc == 3)
    {
        list << argv[1] << argv[2];
    }

    d->m_process->start(TTK_SERVICE_FULL, list);
}

void TTKRunObject::finished(int code)
{
    if(code == 0)
    {
        TTK_LOGGER_INFO("Application exit success");
    }
    else
    {
        TTK_LOGGER_INFO("Application run error, please run TTKService instead");
    }

    qApp->quit();
}
