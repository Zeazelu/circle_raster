#ifndef USTAWIENIADIALOG_H
#define USTAWIENIADIALOG_H
#include <SPreferences.h>
#include <QDialog>

namespace Ui {
class UstawieniaDialog;
}

namespace SSw
{

class UstawieniaDialog : public QDialog
{
    Q_OBJECT

public:
    ~UstawieniaDialog();
    static bool getPreferences(SPreferences &prefs, QWidget* parent = 0);

public slots:
    void updateRange();

private slots:
    void on_pushButton_poziom_L_clicked();

void on_pushButton_poziom_S_clicked();

    void on_pushButton_poziom_T_clicked();

private:
    explicit UstawieniaDialog(QWidget *parent = 0);
    Ui::UstawieniaDialog *ui;
};

} // namespace SSw
#endif // USTAWIENIADIALOG_H
