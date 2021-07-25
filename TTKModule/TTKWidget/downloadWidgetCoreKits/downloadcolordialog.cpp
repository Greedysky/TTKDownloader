#include "downloadcolordialog.h"
#include "ui_downloadcolordialog.h"
#include "downloaduiobject.h"

#include <QPainter>
#include <QToolTip>
#include <QMouseEvent>
#include <QPainterPath>
#include <QButtonGroup>

DownloadHlPalette::DownloadHlPalette(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(QSize(360, 120));
    setMouseTracking(true);

    m_dblSaturation = 1.0;
}

QColor DownloadHlPalette::color() const
{
    return m_color;
}

void DownloadHlPalette::init()
{
    m_ptVernierPos = rect().center();
    calculateColor();
    update();
}

void DownloadHlPalette::setSaturation(double dblsaturation)
{
    m_dblSaturation = dblsaturation;
    update();
    calculateColor();
}

void DownloadHlPalette::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::NoBrush);

    int ntRight = rect().right();
    int ntBottm = rect().bottom();
    QColor colorStart, colorDatum, colorFinal;
    for(int it=0; it< ntRight + 1; it++)
    {
        colorStart.setHslF(it/double(ntRight), m_dblSaturation, 1);
        colorDatum.setHslF(it/double(ntRight), m_dblSaturation, 0.5);
        colorFinal.setHslF(it/double(ntRight), m_dblSaturation, 0);

        QLinearGradient linearGradient;
        linearGradient.setStart(QPointF(it, 0));
        linearGradient.setFinalStop(QPointF(it, ntBottm));
        linearGradient.setColorAt(0.0, colorStart);
        linearGradient.setColorAt(0.5, colorDatum);
        linearGradient.setColorAt(1.0, colorFinal);

        QBrush brush(linearGradient);
        painter.setPen(QPen(brush, 1));
        painter.drawLine(QPointF(it, 0), QPointF(it, ntBottm));
    }

    painter.setPen(QPen(Qt::black, 2));
    painter.drawEllipse(m_ptVernierPos, 5, 5);

    painter.setPen(QPen(Qt::white, 2));
    painter.drawEllipse(m_ptVernierPos, 7, 7);
}

void DownloadHlPalette::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    m_ptVernierPos.setX(rect().right() * m_ptfVernierPercentPos.rx());
    m_ptVernierPos.setY(rect().bottom() * m_ptfVernierPercentPos.ry());

    update();
}

void DownloadHlPalette::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_ptVernierPos = event->pos();
        calculateColor();
        update();
    }
}

void DownloadHlPalette::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton && !(event->buttons() & Qt::RightButton))
    {
        m_ptVernierPos = event->pos();
        if(rect().contains(m_ptVernierPos))
        {
            calculateColor();
            update();
        }
    }
    else
    {
        QPainterPath path;
        path.addEllipse(m_ptVernierPos, 7, 7);
        if(path.contains(event->pos()))
        {
            QToolTip::showText(mapToGlobal(event->pos()) + QPoint(0, 5), tr("Adjust Hue And Brightness"), this,
                               QRect(m_ptVernierPos - QPoint(8, 8), QSize(16, 16)));
        }
    }
}

void DownloadHlPalette::calculateColor()
{
    m_ptfVernierPercentPos.setX(m_ptVernierPos.x()/double(rect().right()));
    m_ptfVernierPercentPos.setY(m_ptVernierPos.y()/double(rect().bottom()));
    m_color.setHslF(m_ptfVernierPercentPos.rx(), m_dblSaturation, 1 - m_ptfVernierPercentPos.ry());
    emit colorChanged(m_color);
}



DownloadHlSaturationPalette::DownloadHlSaturationPalette(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    setMinimumWidth(360);
    setMinimumHeight(16);
    setMaximumHeight(24);

    m_color = Qt::red;
    m_dblVernierX = 0;
    m_dblVernierPercentX = 0;
    m_dblSaturation = 0;
}

double DownloadHlSaturationPalette::saturation() const
{
    return m_dblSaturation;
}

void DownloadHlSaturationPalette::setBaseColor(const QColor &color)
{
    m_color = color;
    update();
}

void DownloadHlSaturationPalette::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::NoBrush);

    const int ntRight = rect().right();
    const int ntBottm = rect().bottom();

#if TTK_QT_VERSION_CHECK(6,0,0)
    float dblVH, dblVS, dblVL = -100.0f;
#else
    qreal dblVH, dblVS, dblVL = -100.0f;
#endif
    m_color.getHslF(&dblVH, &dblVS, &dblVL);
    QColor colorCenter, colorStart, colorFinal;
    colorCenter.setHslF(dblVH, 0.5, dblVL);
    colorStart.setHslF(dblVH, 1, dblVL);
    colorFinal.setHslF(dblVH, 0, dblVL);

    QLinearGradient linearGradient;
    linearGradient.setStart(QPointF(0, 0));
    linearGradient.setFinalStop(QPointF(ntRight, 0));
    linearGradient.setColorAt(0.0, colorStart);
    linearGradient.setColorAt(1.0, colorFinal);

    QBrush brush(linearGradient);
    painter.fillRect(rect(), brush);

    QPointF ptfCenter(m_dblVernierX, ntBottm / 2.0);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawEllipse(ptfCenter, 5, 5);

    painter.setPen(QPen(Qt::white, 2));
    painter.drawEllipse(ptfCenter, 7, 7);
}

void DownloadHlSaturationPalette::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    m_dblVernierX = rect().right() * m_dblVernierPercentX;
    update();
}

void DownloadHlSaturationPalette::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_dblVernierX = event->pos().x();
        calculateSuration();
        update();
    }
}

void DownloadHlSaturationPalette::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton && !(event->buttons() & Qt::RightButton))
    {
        m_dblVernierX = event->pos().x();
        if(rect().contains(event->pos()))
        {
            calculateSuration();
            update();
        }
    }
    else
    {
        QPointF ptfCenter(m_dblVernierX, rect().bottom() / 2.0);
        QPainterPath path;
        path.addEllipse(ptfCenter, 7, 7);
        if(path.contains(event->pos()))
        {
            QToolTip::showText(mapToGlobal(event->pos()) + QPoint(0, 5), tr("Adjust Hue And Brightness"), this,
                               QRect(event->pos() - QPoint(8, 8), QSize(16, 16)));
        }
    }
}

void DownloadHlSaturationPalette::calculateSuration()
{
    m_dblVernierPercentX = m_dblVernierX/rect().right();
    m_dblSaturation = 1- m_dblVernierPercentX;
    m_color.setHslF(m_color.hslHueF(), m_dblSaturation, m_color.lightnessF());

    emit saturationChanged(m_dblSaturation);
}



DownloadColorDialog::DownloadColorDialog(QWidget *parent)
    : DownloadAbstractMoveDialog(parent),
      m_ui(new Ui::DownloadColorDialog)
{
    m_ui->setupUi(this);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_close_hover"));
    m_ui->topTitleCloseButton->setStyleSheet(DownloadUIObject::MToolButtonStyle04);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));
    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));

    m_ui->confirmButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
    m_ui->cancelButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
    m_ui->confirmButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

#ifdef Q_OS_UNIX
    m_ui->confirmButton->setFocusPolicy(Qt::NoFocus);
    m_ui->cancelButton->setFocusPolicy(Qt::NoFocus);
#endif
    connect(m_ui->wgtPalette, SIGNAL(colorChanged(QColor)), m_ui->wgtSaturationIndicator, SLOT(setBaseColor(QColor)));
    connect(m_ui->wgtPalette, SIGNAL(colorChanged(QColor)), SLOT(colorChanged(QColor)));
    connect(m_ui->wgtSaturationIndicator, SIGNAL(saturationChanged(double)), m_ui->wgtPalette, SLOT(setSaturation(double)));

    m_status = 0;
    m_ui->wgtPalette->init();

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(m_ui->topTitleCloseButton, 0);
    buttonGroup->addButton(m_ui->confirmButton, 1);
    buttonGroup->addButton(m_ui->cancelButton, 2);
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(buttonGroup, SIGNAL(idClicked(int)), SLOT(buttonClicked(int)));
#else
    connect(buttonGroup, SIGNAL(buttonClicked(int)), SLOT(buttonClicked(int)));
#endif
}

DownloadColorDialog::~DownloadColorDialog()
{
    delete m_ui;
}

QColor DownloadColorDialog::getColor(QWidget *parent)
{
    DownloadColorDialog dialog(parent);
    return dialog.exec() ? dialog.color() : QColor();
}

QColor DownloadColorDialog::color() const
{
    return m_color;
}

void DownloadColorDialog::buttonClicked(int index)
{
    switch(index)
    {
        case 0:
        case 2: m_status = 0; break;
        case 1: m_status = 1; break;
    }
    close();
}

void DownloadColorDialog::colorChanged(const QColor &color)
{
    m_color = color;
}

int DownloadColorDialog::exec()
{
    setBackgroundPixmap(m_ui->background, size());
    DownloadAbstractMoveDialog::exec();
    return m_status;
}
