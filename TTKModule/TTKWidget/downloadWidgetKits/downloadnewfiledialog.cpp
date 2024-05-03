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
    setBackgroundLabel(m_ui->background);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_delete_normal"));
    m_ui->topTitleCloseButton->setStyleSheet(TTK::UI::ToolButtonStyle03);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));

    m_ui->urlTextEdit->setStyleSheet(QString("QTextEdit{ border:1px solid %1; }").arg(G_BACKGROUND_PTR->backgroundColor().name()));

    m_ui->confirmButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->confirmButton->setStyleSheet(TTK::UI::PushButtonStyle03);
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

void DownloadNewFileDialog::confirmButtonPressed()
{
    Q_EMIT setDownloadPath(m_ui->urlTextEdit->toPlainText().split(';'));
    close();
}
