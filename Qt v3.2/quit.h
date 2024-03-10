#ifndef QUIT_H
#define QUIT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Quit;
}
QT_END_NAMESPACE

class Quit : public QMainWindow
{
    Q_OBJECT

public:
    QString s;
    Quit(QWidget *parent = nullptr);
    ~Quit();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Quit *ui;
signals:
    void closeMainWindow();
};
#endif // QUIT_H
