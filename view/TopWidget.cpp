#include <view/TopWidget.h>
#include <ui_TopWidget.h>
#include <Constants.h>
#include <QPixmap>

namespace SSw
{

TopWidget::TopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopWidget),
    m_time(0),
    m_normalFace(QPixmap(NORMAL_FACE)),
    m_fearFace(QPixmap(FEAR_FACE)),
    m_happyFace(QPixmap(HAPPY_FACE)),
    m_sadFace(QPixmap(SAD_FACE))
{
    ui->setupUi(this);
    init();
    //TODO: setDigitCount
}

TopWidget::~TopWidget()
{
    delete ui;
}

void TopWidget::incrementTimer()
{
    m_time++;
    ui->lcdTime->display(m_time);
}

void TopWidget::resetTimer()
{
    m_time = 0;
    ui->lcdTime->display(m_time);
}

void TopWidget::setMinaDisplay(int32_t mineRemained)
{
    ui->lcdMine->display(mineRemained);
}

void TopWidget::onPressed()
{
    ui->pushButton->setIcon(m_fearFace);
}

void TopWidget::onReleased()
{
    ui->pushButton->setIcon(m_normalFace);
}

void TopWidget::onWon()
{
    ui->pushButton->setIcon(m_happyFace);
}

void TopWidget::onLost()
{
    ui->pushButton->setIcon(m_sadFace);
}

void TopWidget::setDefault()
{
    ui->pushButton->setIcon(m_normalFace);
}

void TopWidget::init()
{
    setDefault();
    ui->pushButton->setIconSize(QSize(30,30));

    connect(ui->pushButton, &QPushButton::clicked, this, &TopWidget::buttonClicked);
}

} // namespace SSw
