#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QDialog>
#include <QDesktopServices>

namespace Ui {
class AboutBox;
}

class AboutBox : public QDialog
{
    Q_OBJECT

public:
    explicit AboutBox(QWidget *parent = nullptr);
    ~AboutBox();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::AboutBox *ui;
};

#endif // ABOUTBOX_H
