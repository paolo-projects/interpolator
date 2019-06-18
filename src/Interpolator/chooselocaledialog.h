#ifndef CHOOSELOCALEDIALOG_H
#define CHOOSELOCALEDIALOG_H

#include <QDialog>
#include <QDesktopServices>
#include <QSettings>

#define LOCALE_PREF "preference.locale_setting"

namespace Ui {
class ChooseLocaleDialog;
}

class ChooseLocaleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseLocaleDialog(QWidget *parent = nullptr);
    ~ChooseLocaleDialog();

    const QString getChoosenLocale() const;
private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_localeComboBox_currentIndexChanged(int index);

private:
    Ui::ChooseLocaleDialog *ui;
    static std::vector<std::pair<QString, QString>> localelist;
    QString choosenLocale = "C";
    QSettings settings;
    bool isLoaded = false;
};

#endif // CHOOSELOCALEDIALOG_H
