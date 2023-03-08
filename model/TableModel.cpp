#include <model/TableModel.h>
#include <QPixmap>
#include <QSize>

namespace SSw
{

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent),
      m_model(),
      m_mineDisplay(0),
      m_initialized(false)
{
}

void TableModel::init(const QModelIndex &index)
{
    m_model.populate(index.row(), index.column());
    m_initialized = true;
    emit gameStarted();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model.width();
}
int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model.height();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (Qt::UserRole == role)
    {
        QVariant variant;
        variant.setValue(m_model.field(index.row(), index.column()));
        return variant;
    }

    return QVariant();
}

void TableModel::resetModel(int32_t width, int32_t height, int32_t mine)
{
    m_initialized  = false;
    m_mineDisplay = mine;
    m_model.reset(width, height, mine);
    emit mineDisplay(mine);
    emit layoutChanged();
}

void TableModel::onTableClicked(const QModelIndex &index)
{
    if (m_model.field(index.row(), index.column()).disarmed == 0)
    {
        discover(index);
    }
}

void TableModel::discover(const QModelIndex &index)
{
    if (!m_initialized)
    {
        init(index);
    }

    const int32_t x = index.row();
    const int32_t y = index.column();

    m_model.discover(x, y);

    if (m_model.field(x, y).neighbours == 0 && m_model.field(x, y).mine == 0)
    {
        if (!m_model.getDiscovered(x-1, y-1))   discover(index.sibling(x-1, y-1));
        if (!m_model.getDiscovered(x,   y-1))   discover(index.sibling(x,   y-1));
        if (!m_model.getDiscovered(x+1, y-1))   discover(index.sibling(x+1, y-1));
        if (!m_model.getDiscovered(x-1, y))     discover(index.sibling(x-1, y));
        if (!m_model.getDiscovered(x+1, y))     discover(index.sibling(x+1, y));
        if (!m_model.getDiscovered(x-1, y+1))   discover(index.sibling(x-1, y+1));
        if (!m_model.getDiscovered(x,   y+1))   discover(index.sibling(x,   y+1));
        if (!m_model.getDiscovered(x+1, y+1))   discover(index.sibling(x+1, y+1));
    }

    emit dataChanged(index, index);

    if (m_model.field(x, y).mine && m_model.field(x, y).disarmed == 0)
    {
        emit gameLost();
    }
    else if (m_model.checkWinCondition())
    {
        emit gameWon();
    }
}

void TableModel::onRightClicked(const QModelIndex &index)
{
    const int32_t x = index.row();
    const int32_t y = index.column();

    if (m_model.field(x, y).discovered == 0)
    {
        m_model.disarm(x, y);

        if (m_model.field(x, y).disarmed == 1)
        {
            m_mineDisplay--;
        }
        else if (m_model.field(x, y).disarmed == 0)
        {
            m_mineDisplay++;
        }

        emit mineDisplay(m_mineDisplay);
        emit dataChanged(index, index);
    }
}

void TableModel::onBothClicked(const QModelIndex &index)
{
    const int32_t x = index.row();
    const int32_t y = index.column();

    if (m_model.getDiscovered(x, y)
            && m_model.getNeighbours(x, y) == m_model.countFlagsAround(x, y))
    {
        if (!m_model.getDiscovered(x-1, y-1))   discover(index.sibling(x-1, y-1));
        if (!m_model.getDiscovered(x, y-1))     discover(index.sibling(x,   y-1));
        if (!m_model.getDiscovered(x+1, y-1))   discover(index.sibling(x+1, y-1));
        if (!m_model.getDiscovered(x-1, y))     discover(index.sibling(x-1, y));
        if (!m_model.getDiscovered(x+1, y))     discover(index.sibling(x+1, y));
        if (!m_model.getDiscovered(x-1, y+1))   discover(index.sibling(x-1, y+1));
        if (!m_model.getDiscovered(x, y+1))     discover(index.sibling(x,   y+1));
        if (!m_model.getDiscovered(x+1, y+1))   discover(index.sibling(x+1, y+1));
    }
}

} // namespace SSw
