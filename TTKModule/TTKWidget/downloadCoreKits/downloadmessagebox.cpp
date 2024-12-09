#include "downloadmessagebox.h"
#include "ui_downloadmessagebox.h"
#include "downloaduiobject.h"

#include <QPainter>
#include <QButtonGroup>

DownloadMessageBox::DownloadMessageBox(QWidget *parent)
    : DownloadAbstractMoveDialog(parent),
      m_ui(new Ui::DownloadMessageBox)
{
    m_ui->setupUi(this);
    setBackgroundLabel(m_ui->background);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_close_hover"));
    m_ui->topTitleCloseButton->setStyleSheet(TTK::UI::ToolButtonStyle03);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));

    m_ui->confirmButton->setStyleSheet(TTK::UI::PushButtonStyle03);
    m_ui->cancelButton->setStyleSheet(TTK::UI::PushButtonStyle03);
    m_ui->confirmButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

#ifdef Q_OS_UNIX
    m_ui->confirmButton->setFocusPolicy(Qt::NoFocus);
    m_ui->cancelButton->setFocusPolicy(Qt::NoFocus);
#endif

    QFont ft = font();
    ft.setFamily("Times New Roman");
    setFont(ft);
    m_ui->textLabel->setFont(ft);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(m_ui->topTitleCloseButton, 0);
    buttonGroup->addButton(m_ui->confirmButton, 1);
    buttonGroup->addButton(m_ui->cancelButton, 2);
    QtButtonGroupConnect(buttonGroup, this, buttonClicked, TTK_SLOT);
}

DownloadMessageBox::DownloadMessageBox(const QString &text, QWidget *parent)
    : DownloadMessageBox(parent)
{
    setText(text);
}

DownloadMessageBox::DownloadMessageBox(const QString &title, const QString &text, QWidget *parent)
    : DownloadMessageBox(text, parent)
{
    setTitle(title);
}

DownloadMessageBox::~DownloadMessageBox()
{
    delete m_ui;
}

void DownloadMessageBox::setTitle(const QString &text) const
{
    m_ui->topTitleName->setText(text);
}

QString DownloadMessageBox::title() const
{
    return m_ui->topTitleName->text();
}

void DownloadMessageBox::setText(const QString &text) const
{
    m_ui->textLabel->setText(text);
}

QString DownloadMessageBox::text() const
{
    return m_ui->textLabel->text();
}

void DownloadMessageBox::buttonClicked(int index)
{
    switch(index)
    {
        case 0:
        case 2: reject(); break;
        case 1: accept(); break;
        default: break;
    }
}
