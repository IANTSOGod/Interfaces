#ifndef RESET_H
#define RESET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class reset;
}
QT_END_NAMESPACE

class reset : public QMainWindow
{
    Q_OBJECT

public:
    reset(QWidget *parent = nullptr);
    ~reset();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::reset *ui;
};
#endif // RESET_H
