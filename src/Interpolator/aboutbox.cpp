#include "aboutbox.h"
#include "ui_aboutbox.h"

AboutBox::AboutBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutBox)
{
    ui->setupUi(this);
}

AboutBox::~AboutBox()
{
    delete ui;
}

void AboutBox::on_pushButton_clicked()
{
    close();
}

void AboutBox::on_pushButton_2_clicked()
{
    QDesktopServices::openUrl(QUrl("https://gitlab.com/infante.paolo/interpolator/blob/master/LICENSE"));
}

void AboutBox::on_pushButton_3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://gitlab.com/infante.paolo/interpolator"));
}
