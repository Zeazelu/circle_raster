#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QMouseEvent>
#include <view/ActiveDelegate.h>
#include <view/InactiveDelegate.h>

namespace SSw
{

class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(QWidget *parent = 0);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void adjustSizeToContents();

public slots:
    void activate();
    void deactivate();

signals:
    void rightClicked(const QModelIndex& index);
    void bothClicked(const QModelIndex& index);

private:
    ActiveDelegate     m_activeDelegate;
    InactiveDelegate   m_inactiveDelegate;
};

} // namespace SSw

#endif // TABLEVIEW_H
