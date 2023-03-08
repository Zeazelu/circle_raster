#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <model/Model.h>

namespace SSw
{

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    explicit TableModel(QObject *parent = 0);
    ~TableModel() = default;

    QVariant data(const QModelIndex &index, int role) const override;
    int      rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int      columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void     resetModel(int32_t width, int32_t height, int32_t mine);

signals:
    void     gameStarted();
    void     gameLost();
    void     gameWon();
    void     mineDisplay(int32_t mineCount);

public slots:
    void     onTableClicked(const QModelIndex &index);
    void     onRightClicked(const QModelIndex &index);
    void     onBothClicked(const QModelIndex &index);

private:
    void     init(const QModelIndex &index);
    void     discover(const QModelIndex &index);

    Model   m_model;
    int32_t  m_mineDisplay;
    bool     m_initialized;
};

} // namespace SSw

#endif // TableModel_H
