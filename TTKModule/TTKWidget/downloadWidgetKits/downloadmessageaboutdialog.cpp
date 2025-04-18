#include "downloadmessageaboutdialog.h"
#include "ui_downloadmessageaboutdialog.h"
#include "downloaduiobject.h"
#include "ttkversion.h"

DownloadMessageAboutDialog::DownloadMessageAboutDialog(QWidget *parent)
    : DownloadAbstractMoveDialog(parent),
      m_ui(new Ui::DownloadMessageAboutDialog)
{
    m_ui->setupUi(this);
    setBackgroundLabel(m_ui->background);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_delete_normal"));
    m_ui->topTitleCloseButton->setStyleSheet(TTK::UI::ToolButtonStyle03);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));

    m_ui->iconLabel->setPixmap(QPixmap(":/image/lb_logo"));
    m_ui->textLabel->setText(QString("Version: %1\n").arg(TTK_VERSION_STR) + m_ui->textLabel->text());

    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));
}

DownloadMessageAboutDialog::~DownloadMessageAboutDialog()
{
    delete m_ui;
}
