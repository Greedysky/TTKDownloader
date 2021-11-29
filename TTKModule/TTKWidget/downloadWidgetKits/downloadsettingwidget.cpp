#include "downloadsettingwidget.h"
#include "ui_downloadsettingwidget.h"
#include "downloadsettingmanager.h"

#include <QButtonGroup>
#include <QFontDatabase>
#include <QFileDialog>
#include <QStyledItemDelegate>

DownloadFunctionTableWidget::DownloadFunctionTableWidget(QWidget *parent)
    : DownloadAbstractTableWidget(parent)
{
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 20);
    headerview->resizeSection(1, 20);
    headerview->resizeSection(2, 85);

    setRowCount(3);
    m_listIndex = 0;
}

void DownloadFunctionTableWidget::addFunctionItems(int index, const DownloadFunctionItems &items)
{
    m_listIndex = index;
    for(int i=0; i<items.count(); ++i)
    {
        const DownloadFunctionItem &&fItem = std::move(items[i]);
        QTableWidgetItem *item = nullptr;
        setItem(i, 0, item = new QTableWidgetItem());

                      item = new QTableWidgetItem(QIcon(fItem.m_icon), QString());
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i, 1, item);

                      item = new QTableWidgetItem(fItem.m_name);
#if TTK_QT_VERSION_CHECK(5,13,0)
        item->setForeground(QColor(80, 80, 80));
#else
        item->setTextColor(QColor(80, 80, 80));
#endif
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 2, item);
    }
}

void DownloadFunctionTableWidget::listCellClicked(int row, int column)
{
    Q_UNUSED(column);
    emit currentIndexChanged(row + m_listIndex);
    selectRow(currentRow());
}

void DownloadFunctionTableWidget::leaveEvent(QEvent *event)
{
    QTableWidget::leaveEvent(event);
    listCellEntered(-1, -1);
}


DownloadSettingWidget::DownloadSettingWidget(QWidget *parent)
    : DownloadAbstractMoveDialog(parent),
      m_ui(new Ui::DownloadSettingWidget)
{
    m_ui->setupUi(this);

    ////////////////////////////////////////////////
    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_delete_normal"));
    m_ui->topTitleCloseButton->setStyleSheet(DownloadUIObject::MToolButtonStyle04);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));
    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));

    ////////////////////////////////////////////////
    DownloadFunctionItems items;
    items << DownloadFunctionItem(QString(), tr("Normal"))
          << DownloadFunctionItem(QString(), tr("Dwonload"))
          << DownloadFunctionItem(QString(), tr("Outlook"));
    m_ui->normalFunTableWidget->setRowCount(items.count());
    m_ui->normalFunTableWidget->addFunctionItems(0, items);

    m_ui->confirmButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
    m_ui->cancelButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
    m_ui->confirmButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->cancelButton->setCursor(QCursor(Qt::PointingHandCursor));
#ifdef Q_OS_UNIX
    m_ui->confirmButton->setFocusPolicy(Qt::NoFocus);
    m_ui->cancelButton->setFocusPolicy(Qt::NoFocus);
#endif
    connect(m_ui->normalFunTableWidget, SIGNAL(currentIndexChanged(int)), m_ui->stackedWidget, SLOT(setCurrentIndex(int)));
    connect(m_ui->normalFunTableWidget, SIGNAL(currentIndexChanged(int)), SLOT(clearFunctionTableSelection()));
    connect(m_ui->confirmButton, SIGNAL(clicked()), SLOT(commitTheResults()));
    connect(m_ui->cancelButton, SIGNAL(clicked()), SLOT(close()));

    ////////////////////////////////////////////////
    initNormalSettingWidget();
    initDownloadSettingWidget();
    initSkinSettingWidget();
    ////////////////////////////////////////////////
    selectFunctionTableIndex(0, 0);

}

DownloadSettingWidget::~DownloadSettingWidget()
{
    delete m_ui;
}

void DownloadSettingWidget::initControllerParameter()
{
    m_ui->downloadDirEdit->setText(G_SETTING_PTR->value(DownloadSettingManager::DownloadPathDirChoiced).toString());

    if(!G_SETTING_PTR->value(DownloadSettingManager::CloseEventChoiced).toBool())
    {
        m_ui->minimumRadioBox->setChecked(true);
    }
    else
    {
        m_ui->quitRadioBox->setChecked(true);
    }

    m_ui->startupCheckBox->setChecked(G_SETTING_PTR->value(DownloadSettingManager::StartUpModeChoiced).toBool());
    m_ui->startupRunCheckBox->setChecked(G_SETTING_PTR->value(DownloadSettingManager::StartUpRunModeChoiced).toBool());
    m_ui->slienceRunCheckBox->setChecked(G_SETTING_PTR->value(DownloadSettingManager::SlienceRunModeChoiced).toBool());

    ///////////////////////////////////////////////////////////////////////////
    G_SETTING_PTR->value(DownloadSettingManager::DownloadLimitChoiced).toInt() == 1 ?
                         m_ui->downloadFullRadioBox->click() : m_ui->downloadLimitRadioBox->click();
    m_ui->defaultDownloadModeBox->setCurrentIndex(G_SETTING_PTR->value(DownloadSettingManager::DownloadModeChoiced).toInt());
    m_ui->downloadMaxCountBox->setCurrentIndex(G_SETTING_PTR->value(DownloadSettingManager::DownloadMaxCountChoiced).toInt());

    ///////////////////////////////////////////////////////////////////////////
    m_ui->effectLevelBox->setCurrentIndex(G_SETTING_PTR->value(DownloadSettingManager::SkinEffectLevelChoiced).toInt());
    m_ui->fontBox->setCurrentIndex(G_SETTING_PTR->value(DownloadSettingManager::SkinFontChoiced).toInt());

    m_ui->suspensionVisiableBox->setChecked(G_SETTING_PTR->value(DownloadSettingManager::SkinSuspensionChoiced).toBool());
    m_ui->suspensionShowPerBox->setChecked(G_SETTING_PTR->value(DownloadSettingManager::SkinSuspensionPerChoiced).toBool());

}

void DownloadSettingWidget::clearFunctionTableSelection()
{
    m_ui->normalFunTableWidget->clearSelection();
}

void DownloadSettingWidget::downloadDirSelected()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setViewMode(QFileDialog::Detail);
    if(dialog.exec())
    {
        QString path = dialog.directory().absolutePath();
        if(!path.isEmpty())
        {
            m_ui->downloadDirEdit->setText(path + TTK_SEPARATOR);
        }
    }
}

void DownloadSettingWidget::downloadGroupSpeedLimit(int index)
{
    m_ui->downloadLimitSpeedComboBox->setEnabled(index);
    m_ui->uploadLimitSpeedComboBox->setEnabled(index);
}

void DownloadSettingWidget::commitTheResults()
{
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadPathDirChoiced, m_ui->downloadDirEdit->text());
    G_SETTING_PTR->setValue(DownloadSettingManager::CloseEventChoiced, m_ui->quitRadioBox->isChecked());
    G_SETTING_PTR->setValue(DownloadSettingManager::StartUpModeChoiced, m_ui->startupCheckBox->isChecked());
    G_SETTING_PTR->setValue(DownloadSettingManager::StartUpRunModeChoiced, m_ui->startupRunCheckBox->isChecked());
    G_SETTING_PTR->setValue(DownloadSettingManager::SlienceRunModeChoiced, m_ui->slienceRunCheckBox->isChecked());

    ///////////////////////////////////////////////////////////////////////////
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadLimitChoiced, m_ui->downloadFullRadioBox->isChecked());
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadModeChoiced, m_ui->defaultDownloadModeBox->currentIndex());
    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadMaxCountChoiced, m_ui->downloadMaxCountBox->currentIndex());

    ///////////////////////////////////////////////////////////////////////////
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinEffectLevelChoiced, m_ui->effectLevelBox->currentIndex());
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinFontChoiced, m_ui->fontBox->currentIndex());
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspensionChoiced, m_ui->suspensionVisiableBox->isChecked());
    G_SETTING_PTR->setValue(DownloadSettingManager::SkinSuspensionPerChoiced, m_ui->suspensionShowPerBox->isChecked());


    emit parameterSettingChanged();
    close();
}

int DownloadSettingWidget::exec()
{
    setBackgroundPixmap(m_ui->background, size());
    return DownloadAbstractMoveDialog::exec();
}

void DownloadSettingWidget::selectFunctionTableIndex(int row, int col)
{
    clearFunctionTableSelection();
    switch(row)
    {
        case 0:
            m_ui->normalFunTableWidget->selectRow(col); break;
        default: break;
    }
}

void DownloadSettingWidget::initNormalSettingWidget()
{
    m_ui->downloadDirEdit->setStyleSheet(DownloadUIObject::MLineEditStyle01);
    m_ui->downloadDirButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
    m_ui->downloadDirButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->downloadDirEdit->setText(TDDOWNLOAD_DIR_FULL);

    m_ui->quitRadioBox->setStyleSheet(DownloadUIObject::MRadioButtonStyle01);
    m_ui->minimumRadioBox->setStyleSheet(DownloadUIObject::MRadioButtonStyle01);

    m_ui->startupCheckBox->setStyleSheet(DownloadUIObject::MCheckBoxStyle01);
    m_ui->startupRunCheckBox->setStyleSheet(DownloadUIObject::MCheckBoxStyle01);

    m_ui->slienceRunCheckBox->setStyleSheet(DownloadUIObject::MCheckBoxStyle01);

#ifdef Q_OS_UNIX
    m_ui->downloadDirButton->setFocusPolicy(Qt::NoFocus);
    m_ui->quitRadioBox->setFocusPolicy(Qt::NoFocus);
    m_ui->minimumRadioBox->setFocusPolicy(Qt::NoFocus);
    m_ui->startupCheckBox->setFocusPolicy(Qt::NoFocus);
    m_ui->startupRunCheckBox->setFocusPolicy(Qt::NoFocus);
    m_ui->slienceRunCheckBox->setFocusPolicy(Qt::NoFocus);
#endif
    connect(m_ui->downloadDirButton, SIGNAL(clicked()), SLOT(downloadDirSelected()));
}

void DownloadSettingWidget::initDownloadSettingWidget()
{
    m_ui->downloadFullRadioBox->setStyleSheet(DownloadUIObject::MRadioButtonStyle01);
    m_ui->downloadLimitRadioBox->setStyleSheet(DownloadUIObject::MRadioButtonStyle01);
#ifdef Q_OS_UNIX
    m_ui->downloadFullRadioBox->setFocusPolicy(Qt::NoFocus);
    m_ui->downloadLimitRadioBox->setFocusPolicy(Qt::NoFocus);
#endif
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(m_ui->downloadFullRadioBox, 0);
    buttonGroup->addButton(m_ui->downloadLimitRadioBox, 1);
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(buttonGroup, SIGNAL(idClicked(int)), SLOT(downloadGroupSpeedLimit(int)));
#else
    connect(buttonGroup, SIGNAL(buttonClicked(int)), SLOT(downloadGroupSpeedLimit(int)));
#endif

    m_ui->defaultDownloadModeBox->setItemDelegate(new QStyledItemDelegate(m_ui->defaultDownloadModeBox));
    m_ui->defaultDownloadModeBox->setStyleSheet(DownloadUIObject::MComboBoxStyle01 + DownloadUIObject::MItemView01);
    m_ui->defaultDownloadModeBox->view()->setStyleSheet(DownloadUIObject::MScrollBarStyle01);
    m_ui->downloadMaxCountBox->setItemDelegate(new QStyledItemDelegate(m_ui->downloadMaxCountBox));
    m_ui->downloadMaxCountBox->setStyleSheet(DownloadUIObject::MComboBoxStyle01 + DownloadUIObject::MItemView01);
    m_ui->downloadMaxCountBox->view()->setStyleSheet(DownloadUIObject::MScrollBarStyle01);
    m_ui->downloadLimitSpeedComboBox->setItemDelegate(new QStyledItemDelegate(m_ui->downloadLimitSpeedComboBox));
    m_ui->downloadLimitSpeedComboBox->setStyleSheet(DownloadUIObject::MComboBoxStyle01 + DownloadUIObject::MItemView01);
    m_ui->downloadLimitSpeedComboBox->view()->setStyleSheet(DownloadUIObject::MScrollBarStyle01);
    m_ui->uploadLimitSpeedComboBox->setItemDelegate(new QStyledItemDelegate(m_ui->uploadLimitSpeedComboBox));
    m_ui->uploadLimitSpeedComboBox->setStyleSheet(DownloadUIObject::MComboBoxStyle01 + DownloadUIObject::MItemView01);
    m_ui->uploadLimitSpeedComboBox->view()->setStyleSheet(DownloadUIObject::MScrollBarStyle01);

    m_ui->defaultDownloadModeBox->addItems(QStringList() << tr("Auto") << tr("Manual"));
    for(int i=1; i<=50; ++i)
    {
        m_ui->downloadMaxCountBox->addItem(QString::number(i));
    }

    QStringList downloadSpeed;
    downloadSpeed << "100" << "200" << "300" << "400" << "500" << "600"
                  << "700" << "800" << "900" << "1000" << "1100" << "1200";
    m_ui->downloadLimitSpeedComboBox->addItems(downloadSpeed);
    m_ui->uploadLimitSpeedComboBox->addItems(downloadSpeed);

}

void DownloadSettingWidget::initSkinSettingWidget()
{
    m_ui->suspensionVisiableBox->setStyleSheet(DownloadUIObject::MCheckBoxStyle01);
    m_ui->suspensionShowPerBox->setStyleSheet(DownloadUIObject::MCheckBoxStyle01);
#ifdef Q_OS_UNIX
    m_ui->suspensionVisiableBox->setFocusPolicy(Qt::NoFocus);
    m_ui->suspensionShowPerBox->setFocusPolicy(Qt::NoFocus);
#endif

    m_ui->effectLevelBox->setItemDelegate(new QStyledItemDelegate(m_ui->effectLevelBox));
    m_ui->effectLevelBox->setStyleSheet(DownloadUIObject::MComboBoxStyle01 + DownloadUIObject::MItemView01);
    m_ui->effectLevelBox->view()->setStyleSheet(DownloadUIObject::MScrollBarStyle01);
    m_ui->fontBox->setItemDelegate(new QStyledItemDelegate(m_ui->fontBox));
    m_ui->fontBox->setStyleSheet(DownloadUIObject::MComboBoxStyle01 + DownloadUIObject::MItemView01);
    m_ui->fontBox->view()->setStyleSheet(DownloadUIObject::MScrollBarStyle01);

    m_ui->effectLevelBox->addItems(QStringList() << tr("Heigh") << tr("Low") << tr("Close"));
    m_ui->fontBox->addItems(QFontDatabase().families(QFontDatabase::Any));
}
