#include "downloadmessageaboutdialog.h"
#include "ui_downloadmessageaboutdialog.h"
#include "downloaduiobject.h"
#include "ttkversion.h"

DownloadMessageAboutDialog::DownloadMessageAboutDialog(QWidget *parent)
    : DownloadAbstractMoveDialog(parent),
      m_ui(new Ui::DownloadMessageAboutDialog)
{
    m_ui->setupUi(this);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_delete_normal"));
    m_ui->topTitleCloseButton->setStyleSheet(DownloadUIObject::MToolButtonStyle04);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));

    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));

}

DownloadMessageAboutDialog::~DownloadMessageAboutDialog()
{
    delete m_ui;
}

int DownloadMessageAboutDialog::exec()
{
    m_ui->iconLabel->setPixmap(QPixmap(":/image/lb_logo"));
    m_ui->textLabel->setText(QString("TTKDownloader Version: %1\n").arg(DOWNLOAD_VERSION_STR) +
                             m_ui->textLabel->text());
    setBackgroundPixmap(m_ui->background, size());
    return DownloadAbstractMoveDialog::exec();
}
