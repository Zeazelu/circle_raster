#include <view/TableView.h>
#include <view/ActiveDelegate.h>
#include <QHeaderView>

namespace SSw
{

TableView::TableView(QWidget *parent)
    : QTableView(parent),
      m_activeDelegate(),
      m_inactiveDelegate()
{
    setShowGrid(false);
    horizontalHeader()->hide();
    verticalHeader()->hide();
    horizontalHeader()->setMinimumSectionSize(1);
    verticalHeader()->setMinimumSectionSize(1);
    setSelectionMode(QAbstractItemView::NoSelection);
}

void TableView::mouseReleaseEvent(QMouseEvent* event)
{
    QModelIndex index = indexAt(event->pos());

    switch (event->button())
    {
        case Qt::RightButton:
        {
            emit rightClicked(index);
            break;
        }

        case Qt::LeftButton:
        {
            if (event->buttons() & Qt::RightButton)
            {
                emit bothClicked(index);
            }
            else
            {
                QTableView::mouseReleaseEvent(event);
            }

            break;
        }

        default:
        {
            break;
        }
    }
}

void TableView::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::RightButton:
        {
            break;
        }

        case Qt::LeftButton:
        {
            QTableView::mousePressEvent(event);
            break;
        }

        default:
        {
            break;
        }
    }
}

void TableView::adjustSizeToContents()
{
    resizeColumnsToContents();
    resizeRowsToContents();
    int32_t h = rowHeight(1) * model()->rowCount() + 2;
    int32_t w = columnWidth(1) * model()->columnCount() + 2;
    setFixedSize(w, h);
}

void TableView::activate()
{
    reset();
    setEnabled(true);
    setItemDelegate(&m_activeDelegate);
}

void TableView::deactivate()
{
    setItemDelegate(&m_inactiveDelegate);
    setDisabled(true);
}

} // namespace SSw
