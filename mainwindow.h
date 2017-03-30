#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ComboBox_Race_currentIndexChanged(int index);

    void on_pushButton_Add_clicked();

    void on_pushButton_Remove_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Browse_clicked();

    void on_pushButton_New_clicked();

    void loadSettings();

    void saveSettings();

    void on_ComboBox_Build_currentTextChanged(const QString &arg1);

    void on_pushButton_Play_clicked();

private:
    Ui::MainWindow *ui;
    //settings
    QSettings settings;

    int clockToInt(const QString& str);  
};

#endif // MAINWINDOW_H
