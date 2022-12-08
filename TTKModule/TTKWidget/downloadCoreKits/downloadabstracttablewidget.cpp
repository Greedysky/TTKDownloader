#include "downloadabstracttablewidget.h"
#include "downloadwidgetutils.h"

DownloadAbstractTableWidget::DownloadAbstractTableWidget(QWidget *parent)
    : QTableWidget(parent),
      m_previousColorRow(-1),
      m_previousClickRow(-1),
      m_backgroundColor(255, 255, 255, 0)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setFont(QtFontInit("Helvetica"));
    setColumnCount(3);
    setRowCount(0);
    setShowGrid(false);//Does not display the grid

    QHeaderView *headerview = horizontalHeader();
    headerview->setVisible(false);
    headerview->resizeSection(0, 20);
    headerview->resizeSection(1, 247);
    headerview->resizeSection(2, 45);
    verticalHeader()->setVisible(false);

    setMouseTracking(true);  //Open the capture mouse function
    setStyleSheet(DownloadUIObject::MTableWidgetStyle01 + DownloadUIObject::MScrollBarStyle03 + DownloadUIObject::MLineEditStyle01);

    QFont font = this->font();
    font.setBold(false);
    setFont(font);

    //Set the color of selected row
    setFrameShape(QFrame::NoFrame);//Set No Border
    setEditTriggers(QAbstractItemView::NoEditTriggers);//No edit
    setSelectionBehavior(QAbstractItemView::SelectRows);
    //Multi-line election
    setSelectionMode(QAbstractItemView::SingleSelection);
    setFocusPolicy(Qt::NoFocus);

    DownloadUtils::Widget::setTransparent(this, 0);
#if defined Q_OS_UNIX && !TTK_QT_VERSION_CHECK(5,7,0) //Fix linux selection-background-color stylesheet bug
    DownloadUtils::Widget::setTransparent(this, QColor(20, 20, 20, 10));
#endif
    connect(this, SIGNAL(cellEntered(int,int)), SLOT(itemCellEntered(int,int)));
    connect(this, SIGNAL(cellClicked(int,int)), SLOT(itemCellClicked(int,int)));
}

DownloadAbstractTableWidget::~DownloadAbstractTableWidget()
{

}

void DownloadAbstractTableWidget::itemCellEntered(int row, int column)
{
    if(item(m_previousColorRow, 0))
    {
       setRowColor(m_previousColorRow, m_backgroundColor);
    }

    if(item(row, column))
    {
       setRowColor(row, QColor(20, 20, 20, 20));
    }

    m_previousColorRow = row;
}

void DownloadAbstractTableWidget::itemCellClicked(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
}

void DownloadAbstractTableWidget::removeItems()
{
    clearContents();
    setRowCount(0);

    m_previousColorRow = -1;
    m_previousClickRow = -1;
    m_backgroundColor = Qt::transparent;
}

void DownloadAbstractTableWidget::setRowColor(int row, const QColor &color) const
{
    for(int i = 0; i < columnCount(); ++i)
    {
        QTableWidgetItem *it = item(row, i);
        if(it)
        {
            QtItemSetBackgroundColor(it, color);
        }
    }
}
