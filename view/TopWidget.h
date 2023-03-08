#ifndef TOPWIDGET_H
#define TOPWIDGET_H
#include <QWidget>
#include <QIcon>

namespace Ui {
class TopWidget;
}

namespace SSw
{

class TopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TopWidget(QWidget *parent = 0);
    ~TopWidget();

signals:
    void buttonClicked();

public slots:
    void setMinaDisplay(int32_t mineRemained);
    void incrementTimer();
    void resetTimer();
    void onPressed();
    void onReleased();
    void onWon();
    void onLost();
    void setDefault();

private:
    void init();

    Ui::TopWidget *ui;
    int32_t        m_time;
    QIcon          m_normalFace;
    QIcon          m_fearFace;
    QIcon          m_happyFace;
    QIcon          m_sadFace;
};

} // namespace SSw
#endif // TOPWIDGET_H
