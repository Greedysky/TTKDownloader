#include "downloadabstracttablewidget.h"
#include "downloadwidgetutils.h"

DownloadAbstractTableWidget::DownloadAbstractTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
#if TTK_QT_VERSION_CHECK(6,2,0)
    setFont(QFont(QStringList() << "Helvetica"));
#else
    setFont(QFont("Helvetica"));
#endif
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
    setStyleSheet(DownloadUIObject::MTableWidgetStyle01 + \
                  DownloadUIObject::MScrollBarStyle03 + \
                  DownloadUIObject::MLineEditStyle01);

    QFont f = font();
    f.setBold(false);
    setFont(f);

    //Set the color of selected row
    setFrameShape(QFrame::NoFrame);//Set No Border
    setEditTriggers(QTableWidget::NoEditTriggers);//No edit
    setSelectionBehavior(QTableWidget::SelectRows);
    //Multi-line election
    setSelectionMode(QAbstractItemView::SingleSelection);
    setFocusPolicy(Qt::NoFocus);

    DownloadUtils::Widget::setTransparent(this, 0);

    m_previousColorRow = -1;
    m_previousClickRow = -1;
    m_defaultBkColor = QColor(255, 255, 255, 0);

    connect(this, SIGNAL(cellEntered(int,int)), SLOT(listCellEntered(int,int)));
    connect(this, SIGNAL(cellClicked(int,int)), SLOT(listCellClicked(int,int)));
}

DownloadAbstractTableWidget::~DownloadAbstractTableWidget()
{

}

void DownloadAbstractTableWidget::clear()
{
    clearContents();
    setRowCount(0);
}

void DownloadAbstractTableWidget::listCellEntered(int row, int column)
{
    QTableWidgetItem *it = item(m_previousColorRow, 0);
    if(it != nullptr)
    {
       setRowColor(m_previousColorRow, m_defaultBkColor);
    }

    it = item(row, column);
    if(it != nullptr)
    {
       setRowColor(row, QColor(20, 20, 20, 20));
    }

    m_previousColorRow = row;
}

void DownloadAbstractTableWidget::setRowColor(int row, const QColor &color) const
{
    for(int col=0; col<columnCount(); col++)
    {
        QTableWidgetItem *it = item(row, col);
        if(it != nullptr)
        {
#if TTK_QT_VERSION_CHECK(5,13,0)
            it->setBackground(color);
#else
            it->setBackgroundColor(color);
#endif
        }
    }
}
