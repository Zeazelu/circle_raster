#include <view/UstawieniaDialog.h>
#include <ui_UstawieniaDialog.h>
#include <Constants.h>
#include<QDebug>
int wysokosc;
int szerokosc;
int miny;
namespace SSw
{

UstawieniaDialog::UstawieniaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UstawieniaDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &UstawieniaDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &UstawieniaDialog::reject);
    connect(ui->heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateRange()));
    connect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateRange()));
    connect(ui->pushButton_poziom_T,SIGNAL(released()),this,SLOT(on_pushButton_poziom_T_clicked()));
     connect(ui->pushButton_poziom_L,SIGNAL(released()),this,SLOT(on_pushButton_poziom_L_clicked()));
     connect(ui->pushButton_poziom_S,SIGNAL(released()),this,SLOT(on_pushButton_poziom_S_clicked()));
    ui->heightSpinBox->setMinimum(3);
    ui->widthSpinBox->setMinimum(3);

    setWindowTitle(tr("Preferences"));
}

UstawieniaDialog::~UstawieniaDialog()
{
    delete ui;
}

bool UstawieniaDialog::getPreferences(SPreferences &prefs, QWidget *parent)
{
    bool retValue = false;

    UstawieniaDialog dialog(parent);

    dialog.ui->heightSpinBox->setValue(prefs.width);
    dialog.ui->widthSpinBox->setValue(prefs.height);
    dialog.ui->mineSpinBox->setValue(prefs.mine);

    if (dialog.exec() == QDialog::Accepted)
    {
       // prefs.width   = dialog.ui->heightSpinBox->value();
              //  prefs.height  = dialog.ui->widthSpinBox->value();
             //   prefs.mine   = dialog.ui->mineSpinBox->value();
        prefs.width =szerokosc;
        prefs.height= wysokosc;
        prefs.mine= miny;
        retValue = true;
    }

    return retValue;
}

void UstawieniaDialog::updateRange()
{
    int32_t min = MIN_DENSITY * ui->heightSpinBox->value() * ui->widthSpinBox->value();
    int32_t max = MAX_DENSITY * ui->heightSpinBox->value() * ui->widthSpinBox->value();
    ui->mineSpinBox->setRange(min, max);
}
void UstawieniaDialog::on_pushButton_poziom_L_clicked()
{
    wysokosc   = 8;
    szerokosc  = 8;
    miny  = 10;
}
void UstawieniaDialog::on_pushButton_poziom_S_clicked()
{
    wysokosc   = 16;
    szerokosc  = 16;
    miny  = 40;
}
void UstawieniaDialog::on_pushButton_poziom_T_clicked()
{


  wysokosc   = 16;
  szerokosc  = 32;
  miny  = 100;
}

} // namespace SSw
