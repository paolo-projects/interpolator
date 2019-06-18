#include "chooselocaledialog.h"
#include "ui_chooselocaledialog.h"

#ifdef Q_OS_WIN
std::vector<std::pair<QString, QString>> ChooseLocaleDialog::localelist = {
    { "<default>", "C" },
    { "<system>", ""},
    { "US English", "en-US"},
    { "Italian", "it-IT"},
    { "German", "de-DE"},
    { "French", "fr-FR"},
    { "Spanish", "es-ES"},
};
#elif defined(Q_OS_LINUX)
std::vector<std::pair<QString, QString>> ChooseLocaleDialog::localelist = {
    std::pair<QString, QString> ( "<default>", "C" ),
    std::pair<QString, QString> ( "<system>", ""),
    std::pair<QString, QString> ( "US English", "en_US.UTF-8"),
    std::pair<QString, QString> ( "Italian", "it_IT.UTF-8"),
    std::pair<QString, QString> ( "German", "de_DE.UTF-8"),
    std::pair<QString, QString> ( "French", "fr_FR.UTF-8"),
    std::pair<QString, QString> ( "Spanish", "es_ES.UTF-8"),
};
#else
std::vector<std::pair<QString, QString>> ChooseLocaleDialog::localelist = {
    { "<default>", "C" },
    { "<system>", ""}
};
#endif

ChooseLocaleDialog::ChooseLocaleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseLocaleDialog)
{
    ui->setupUi(this);
    layout()->setSizeConstraint( QLayout::SetFixedSize );

    for(auto locale : localelist)
    {
        ui->localeComboBox->addItem(locale.first);
    }

    int localeIndex = settings.value(LOCALE_PREF, 0).toInt();
    ui->localeComboBox->setCurrentIndex(localeIndex);
    ui->customLocaleEditText->setText(localelist.at(ui->localeComboBox->currentIndex()).second);
    choosenLocale = localelist.at(ui->localeComboBox->currentIndex()).second;

    isLoaded = true;
}

ChooseLocaleDialog::~ChooseLocaleDialog()
{
    //settings.sync();
    delete ui;
}

void ChooseLocaleDialog::on_buttonBox_accepted()    // OK Button
{

}

void ChooseLocaleDialog::on_buttonBox_rejected()    // Cancel Button
{

}

void ChooseLocaleDialog::on_localeComboBox_currentIndexChanged(int index)
{
    if(isLoaded)
    {
        ui->customLocaleEditText->setText(localelist.at(index).second);
        choosenLocale = localelist.at(index).second;
        settings.setValue(LOCALE_PREF, index);
    }
}

const QString ChooseLocaleDialog::getChoosenLocale() const
{
    return choosenLocale;
}
