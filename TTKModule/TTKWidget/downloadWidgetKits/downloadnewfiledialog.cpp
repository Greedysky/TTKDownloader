#include "downloadnewfiledialog.h"
#include "ui_downloadnewfiledialog.h"
#include "downloadbackgroundmanager.h"
#include "downloadobject.h"
#include "downloaduiobject.h"

DownloadNewFileDialog::DownloadNewFileDialog(QWidget *parent)
    : DownloadAbstractMoveDialog(parent),
    m_ui(new Ui::DownloadNewFileDialog)
{
    m_ui->setupUi(this);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_delete_normal"));
    m_ui->topTitleCloseButton->setStyleSheet(DownloadUIObject::MToolButtonStyle04);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));

    m_ui->urlTextEdit->setStyleSheet(QString("QTextEdit{ border:1px solid %1;}").arg(
                                     M_BACKGROUND_PTR->getMBackgroundColor().name()));

    m_ui->confirmButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->confirmButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
#ifdef Q_OS_UNIX
    m_ui->confirmButton->setFocusPolicy(Qt::NoFocus);
#endif

    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));
    connect(m_ui->confirmButton, SIGNAL(clicked()), SLOT(confirmButtonPressed()));
}

DownloadNewFileDialog::~DownloadNewFileDialog()
{
    delete m_ui;
}

QString DownloadNewFileDialog::getClassName()
{
    return staticMetaObject.className();
}

void DownloadNewFileDialog::confirmButtonPressed()
{
    QStringList urls = m_ui->urlTextEdit->toPlainText().split(';');

    emit setDownloadPath(urls);
    close();
}

int DownloadNewFileDialog::exec()
{
    setBackgroundPixmap(m_ui->background, size());
    return DownloadAbstractMoveDialog::exec();
}
