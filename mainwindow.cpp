#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QInputDialog"
#include "QFile"
#include "QTextStream"
#include "QDir"
#include "QSound"
#include "QTime"
#include "QThread"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //populate lists with defaults (Protoss)
    ui->listWidget_Buildings->addItems(QStringList()<<"Assimilator"<<"Cybernetics core"<<"Dark shrine"
                                       <<"Fleet beacon"<<"Forge"<<"Gateway"<<"Nexus"
                                       <<"Pylon"<<"Robotics bay"<<"Robotics facility"<<"Stargate"
                                       <<"Templar archives"<<"Twilight council");
    ui->listWidget_Buildings->setCurrentRow(0);
    ui->listWidget_Units->addItems(QStringList()<<"Adept"<<"Archon"<<"Carrier"<<"Colossus"<<"Dark templar"
                                   <<"Disruptor"<<"High templar"<<"Immortal"<<"Mothership"<<"Mothership core"
                                   <<"Observer"<<"Oracle"<<"Phoenix"<<"Probe"<<"Sentry"<<"Stalker"<<"Tempest"
                                   <<"Void ray"<<"Warp prism"<<"Zealot");
    ui->listWidget_Units->setCurrentRow(0);
    ui->listWidget_Upgrades->addItems(QStringList()<<"+1 ground weapons"<<"+2 ground weapons"<<"+3 ground weapons"
                                      <<"+1 air weapons"<<"+2 air weapons"<<"+3 air weapons"
                                      <<"+1 ground armor"<<"+2 ground armor"<<"+3 ground armor"
                                      <<"+1 air armor"<<"+2 air armor"<<"+3 air armor"
                                      <<"+1 shields"<<"+2 shields"<<"+3 shields"
                                      <<"Observer speed"<<"Warp prism speed"<<"Interceptor speed"<<"Charge"
                                      <<"Blink"<<"Phoenix range"<<"Psionic storm"<<"Thermal lance"<<"Warp gate");
    ui->listWidget_Upgrades->setCurrentRow(0);

    //load settings
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//change race index
void MainWindow::on_ComboBox_Race_currentIndexChanged(int index)
{
    QStringList protossBuildings = (QStringList()<<"Assimilator"<<"Cybernetics core"<<"Dark shrine"
                           <<"Fleet beacon"<<"Forge"<<"Gateway"<<"Nexus"
                           <<"Pylon"<<"Robotics bay"<<"Robotics facility"<<"Stargate"
                           <<"Templar archives"<<"Twilight council");
    QStringList protossUnits = (QStringList()<<"Adept"<<"Archon"<<"Carrier"<<"Colossus"<<"Dark templar"
                                <<"Disruptor"<<"High templar"<<"Immortal"<<"Mothership"<<"Mothership core"
                                <<"Observer"<<"Oracle"<<"Phoenix"<<"Probe"<<"Sentry"<<"Stalker"<<"Tempest"
                                <<"Void ray"<<"Warp prism"<<"Zealot");
    QStringList protossUpgrades = (QStringList()<<"+1 ground weapons"<<"+2 ground weapons"<<"+3 ground weapons"
                                   <<"+1 air weapons"<<"+2 air weapons"<<"+3 air weapons"
                                   <<"+1 ground armor"<<"+2 ground armor"<<"+3 ground armor"
                                   <<"+1 air armor"<<"+2 air armor"<<"+3 air armor"
                                   <<"+1 shields"<<"+2 shields"<<"+3 shields"
                                   <<"Observer speed"<<"Warp prism speed"<<"Interceptor speed"<<"Charge"
                                   <<"Blink"<<"Phoenix range"<<"Psionic storm"<<"Thermal lance"<<"Warp gate");

    QStringList terranBuildings = (QStringList()<<"Armory"<<"Barracks"<<"Command center"<<"Engineering bay"
                                   <<"Factory"<<"Fusion core"<<"Ghost academy"<<"Orbital"<<"Planetary"
                                   <<"Reactor on barracks"<<"Reactor on factory"<<"Reactor on starport"
                                   <<"Refinery"<<"Sensor tower"<<"Starport"<<"Supply depot"<<"Tech lab on barracks"
                                   <<"Tech lab on factory"<<"Tech lab on starport");
    QStringList terranUnits = (QStringList()<<"Banshee"<<"Battlecruiser"<<"Cyclone"<<"Ghost"<<"Hellbat"<<"Hellion"
                               <<"Liberator"<<"Marauder"<<"Marine"<<"Medivac"<<"Raven"<<"Reaper"<<"SCV"<<"Siege tank"
                               <<"Thor"<<"Viking"<<"Widow mine");
    QStringList terranUpgrades = (QStringList()<<"+1 infantry weapons"<<"+2 infantry weapons"<<"+3 infantry weapons"
                                  <<"+1 vehicle weapons"<<"+2 vehicle weapons"<<"+3 vehicle weapons"
                                  <<"+1 air weapons"<<"+2 air weapons"<<"+3 air weapons"
                                  <<"+1 infantry armor"<<"+2 infantry armor"<<"+3 infantry armor"
                                  <<"+1 vehicle/air armor"<<"+2 vehicle/air armor"<<"+3 vehicle/air armor"
                                  <<"Banshee cloak"<<"Banshee speed"<<"Blue flame"<<"Combat shield"<<"Concussive shells"<<"Ghost cloak"
                                  <<"Stimpack"<<"Yamato cannon"<<"Battlecruiser energy"<<"Medivac energy"<<"Raven energy"
                                  <<"Building armor"<<"Bunker size"<<"Durable materials"<<"Turret range");

    QStringList zergBuildings = (QStringList()<<"Baneling nest"<<"Evolution chamber"<<"Extractor"<<"Greater spire"
                                 <<"Hatchery"<<"Hive"<<"Hydralisk den"<<"Infestation pit"<<"Lair"<<"Lurker den"
                                 <<"Nydus worm"<<"Roach warren"<<"Spawning pool"<<"Spire"
                                 <<"Ultralisk cavern");
    QStringList zergUnits = (QStringList()<<"Baneling"<<"Brood lord"<<"Corruptor"<<"Drone"<<"Hydralisk"<<"Infestor"
                               <<"Lurker"<<"Mutalisk"<<"Overlord"<<"Overseer"<<"Queen"<<"Ravager"<<"Roach"<<"Swarm host"
                               <<"Ultralisk"<<"Viper"<<"Zergling");
    QStringList zergUpgrades = (QStringList()<<"+1 melee attack"<<"+2 melee attack"<<"+3 melee attack"
                                <<"+1 missle attack"<<"+2 missle attack"<<"+3 missle attack"
                                <<"+1 air attack"<<"+2 air attack"<<"+3 air attack"
                                <<"+1 ground armor"<<"+2 ground armor"<<"+3 ground armor"
                                <<"+1 air armor"<<"+2 air armor"<<"+3 air armor"
                                <<"Baneling speed"<<"Roach speed"<<"Zergling speed"<<"Overlord speed"
                                <<"Adrenal glands"<<"Burrow"<<"Chitinous Plating"<<"Hydralisk range"<<"Infestor Energy"
                                <<"Neural Parasite"<<"Tunneling claws"<<"Ventral Sacs");

    ui->listWidget_Buildings->clear();
    ui->listWidget_Units->clear();
    ui->listWidget_Upgrades->clear();
    if (index == 0) { //protoss
        ui->listWidget_Buildings->addItems(protossBuildings);
        ui->listWidget_Buildings->setCurrentRow(0);
        ui->listWidget_Units->addItems(protossUnits);
        ui->listWidget_Units->setCurrentRow(0);
        ui->listWidget_Upgrades->addItems(protossUpgrades);
        ui->listWidget_Upgrades->setCurrentRow(0);
    }
    else if (index == 1) { //terran
        ui->listWidget_Buildings->addItems(terranBuildings);
        ui->listWidget_Buildings->setCurrentRow(0);
        ui->listWidget_Units->addItems(terranUnits);
        ui->listWidget_Units->setCurrentRow(0);
        ui->listWidget_Upgrades->addItems(terranUpgrades);
        ui->listWidget_Upgrades->setCurrentRow(0);
    }
    else if (index == 2) { //zerg
        ui->listWidget_Buildings->addItems(zergBuildings);
        ui->listWidget_Buildings->setCurrentRow(0);
        ui->listWidget_Units->addItems(zergUnits);
        ui->listWidget_Units->setCurrentRow(0);
        ui->listWidget_Upgrades->addItems(zergUpgrades);
        ui->listWidget_Upgrades->setCurrentRow(0);
    }
    else { //error
        ui->listWidget_Buildings->addItem("Unknown error");
        ui->listWidget_Buildings->setCurrentRow(0);
        ui->listWidget_Units->addItem("Unknown error");
        ui->listWidget_Units->setCurrentRow(0);
        ui->listWidget_Upgrades->addItem("Unknown error");
        ui->listWidget_Upgrades->setCurrentRow(0);
    }
}

//Click "Add"
void MainWindow::on_pushButton_Add_clicked()
{
    if (ui->tabWidget_Race_details->currentIndex() == 0) { //buildings
       QString str =ui->timeEdit_Timestamp->text(); //get timestamp
       str += "  " + ui->listWidget_Buildings->currentItem()->text(); //add action
       ui->listWidget_Build_order->addItem(str);
       ui->listWidget_Build_order->sortItems();
       //update log
       str += " added.\n" + ui->plainTextEdit_Log->toPlainText();
       ui->plainTextEdit_Log->clear();
       ui->plainTextEdit_Log->document()->setPlainText(str);
    }
    else if (ui->tabWidget_Race_details->currentIndex() == 1) { //units
        QString str = ui->timeEdit_Timestamp->text(); //get timestamp
        str += "  " + ui->listWidget_Units->currentItem()->text(); //add action
        ui->listWidget_Build_order->addItem(str);
        ui->listWidget_Build_order->sortItems();
        //update log
        str += " added.\n" + ui->plainTextEdit_Log->toPlainText();
        ui->plainTextEdit_Log->clear();
        ui->plainTextEdit_Log->document()->setPlainText(str);
    }
    else if (ui->tabWidget_Race_details->currentIndex() == 2) { //upgrades
        QString str = ui->timeEdit_Timestamp->text(); //get timestamp
        str += "  " + ui->listWidget_Upgrades->currentItem()->text(); //add action
        ui->listWidget_Build_order->addItem(str);
        ui->listWidget_Build_order->sortItems();
        //update log
        str += " added.\n" + ui->plainTextEdit_Log->toPlainText();
        ui->plainTextEdit_Log->clear();
        ui->plainTextEdit_Log->document()->setPlainText(str);
    }
    else { //error
        QString str = "Error. \n" + ui->plainTextEdit_Log->toPlainText();
        ui->plainTextEdit_Log->clear();
        ui->plainTextEdit_Log->document()->setPlainText(str);
    }
    ui->listWidget_Build_order->setCurrentRow(0);
    //enable/disable "Remove" button
    if (ui->listWidget_Build_order->count() > 0)
        ui->pushButton_Remove->setEnabled(true);
    else
        ui->pushButton_Remove->setEnabled(false);
}

//Click "Remove"
void MainWindow::on_pushButton_Remove_clicked()
{
    QString str = ui->listWidget_Build_order->currentItem()->text() + " removed.\n";
    qDeleteAll(ui->listWidget_Build_order->selectedItems());
    //update log
    str += ui->plainTextEdit_Log->toPlainText();
    ui->plainTextEdit_Log->clear();
    ui->plainTextEdit_Log->document()->setPlainText(str);
    //enable/disable "Remove" button
    if (ui->listWidget_Build_order->count() > 0)
        ui->pushButton_Remove->setEnabled(true);
    else
        ui->pushButton_Remove->setEnabled(false);
}

//Click "Save"
void MainWindow::on_pushButton_Save_clicked()
{
    QString content;
    QString filePath = ui->lineEdit_Directory->text() + "\\" + ui->ComboBox_Build->currentText() + ".lotv";
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    for (int i = 0; i < ui->listWidget_Build_order->count(); i++) {
        QListWidgetItem *item = ui->listWidget_Build_order->item(i);
        stream << item->text() << "\n";
    }
    file.close();
    //update log
    QString str = "\"" + ui->ComboBox_Build->currentText() + "\" saved.\n";
    str += ui->plainTextEdit_Log->toPlainText();
    ui->plainTextEdit_Log->clear();
    ui->plainTextEdit_Log->document()->setPlainText(str);
}

//Click "Browse"
void MainWindow::on_pushButton_Browse_clicked()
{
    QString filePath = QFileDialog::getExistingDirectory(0,"Open Folder",QString(),QFileDialog::ShowDirsOnly);
    ui->lineEdit_Directory->setText(filePath);
    saveSettings();
    loadSettings();
}

//Click "New"
void MainWindow::on_pushButton_New_clicked()
{
    bool ok;
    QString fileName = QInputDialog::getText(this, tr("New build"), tr("Build name:"), QLineEdit::Normal, "New build", &ok);
    if (ok && !fileName.isEmpty()) {
        //update log
        QString str = "\"" + fileName + "\" created.\n";
        str += ui->plainTextEdit_Log->toPlainText();
        ui->plainTextEdit_Log->clear();
        ui->plainTextEdit_Log->document()->setPlainText(str);
        //create build
        ui->ComboBox_Build->addItem(fileName);        
        ui->ComboBox_Build->setCurrentIndex(ui->ComboBox_Build->count() - 1);
    }
    //enable/disable "Save" button
    if (ui->ComboBox_Build->count() > 0 && ui->lineEdit_Directory->text() != "")
        ui->pushButton_Save->setEnabled(true);
    else
        ui->pushButton_Save->setEnabled(false);
}

//Click "Play"
void MainWindow::on_pushButton_Play_clicked()
{
    int current = 0;
    QString str, backLog;
    QTime time;
    QStringList buildOrderList, timings, actions;
    //create QStringList from ListWidget and break into time/action lists
    for (int i = 0; i < ui->listWidget_Build_order->count(); i++) {
        QListWidgetItem *item = ui->listWidget_Build_order->item(i);
        buildOrderList.push_back(item->text());
    }
    for (int i = 0; i < buildOrderList.count(); i++) {
        timings.push_back(buildOrderList[i].split("  ")[0]);
        actions.push_back(buildOrderList[i].split("  ")[1]);
    }
    //
    //save the current log
    backLog = ui->plainTextEdit_Log->document()->toPlainText();
    time.start();
    while (current < buildOrderList.count()) {
        qApp->processEvents();
        if (time.elapsed() / 1000 == clockToInt(timings[current])) {
            QSound::play("Sounds\\" + actions[current] + ".wav");
            current++;
        }
        if (current == 0) {
            str = "Upcoming:\n    " + actions[0] + " in " + QString::number(clockToInt(timings[0]) - time.elapsed() / 1000) + " seconds.";
            ui->plainTextEdit_Log->document()->setPlainText(str);
        }
        else if (current > 0 && current < buildOrderList.count()) {
            str = "Current:\n    " + actions[current - 1] + "\nUpcoming:\n    " + actions[current] + " in " + QString::number(clockToInt(timings[current]) - time.elapsed() / 1000) + " seconds.";
            ui->plainTextEdit_Log->document()->setPlainText(str);
        }
        else {
            backLog = "Build finished.\n" + backLog;
            ui->plainTextEdit_Log->document()->setPlainText(backLog);
        }
        QThread::msleep(100);
    }
}

//load settings
void MainWindow::loadSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    QString str = settings.value("directory", "").toString();
    if (ui->lineEdit_Directory)
        ui->lineEdit_Directory->setText(str);
    QDir dir = ui->lineEdit_Directory->text();
    QStringList entries = dir.entryList(QStringList()<<"*.lotv", QDir::Files, QDir::Unsorted);
    for (int i = 0; i < entries.count(); i++)
        entries[i].chop(5);
    ui->ComboBox_Build->addItems(entries);
}

//save settings
void MainWindow::saveSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    QString str = (ui->lineEdit_Directory) ? ui->lineEdit_Directory->text() : "";
    settings.setValue("directory", str);
}

//build changed
void MainWindow::on_ComboBox_Build_currentTextChanged(const QString &arg1)
{
    QString content;
    QString filePath = ui->lineEdit_Directory->text() + "\\" + arg1 + ".lotv";
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    content = stream.readLine();
    ui->listWidget_Build_order->clear();
    while (content != NULL) {
        ui->listWidget_Build_order->addItem(content);
        content = stream.readLine();
    }
    file.close();
    //update log
    QString str = "\"" + arg1 + "\" loaded.\n";
    str += ui->plainTextEdit_Log->toPlainText();
    ui->plainTextEdit_Log->clear();
    ui->plainTextEdit_Log->document()->setPlainText(str);
    ui->listWidget_Build_order->setCurrentRow(0);
    //enable/disable "Remove" button
    if (ui->listWidget_Build_order->count() > 0)
        ui->pushButton_Remove->setEnabled(true);
    else
        ui->pushButton_Remove->setEnabled(false);
    //enable/disable "Save" button
    if (ui->ComboBox_Build->count() > 0 && ui->lineEdit_Directory->text() != "")
        ui->pushButton_Save->setEnabled(true);
    else
        ui->pushButton_Save->setEnabled(false);
}

int MainWindow::clockToInt(const QString& str) {
    int min, sec;
    QString minutes, seconds;
    minutes = str.split(":")[0];
    seconds = str.split(":")[1];
    min = minutes.toInt();
    sec = seconds.toInt();
    return (min * 60) + sec;
}
