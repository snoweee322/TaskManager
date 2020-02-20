#include "tskmngr.h"
#include "ui_tskmngr.h"


tskMngr::tskMngr(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tskMngr)
{
    ui->setupUi(this);
    tableWidget = new QTableWidget;
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,184);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Process ID"));
    state = Qt::AscendingOrder;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotUpdateProcessList()));
    timer->start(250);
}

void tskMngr::slotUpdateProcessList()
{
    QDir *directory1 = new QDir("/proc");
    QStringList folderName;
    directory1->setNameFilters(QStringList("[0-9]*"));
    folderName = directory1->entryList(QDir::Dirs);
    ui->tableWidget->sortItems(0,state);
    if(lastProcessNumber == folderName.length() && !changed)
    {
        ui->tableWidget->selectRow(rowSelect);
        changed = 0;
    }
    if(lastProcessNumber != folderName.length())
    {
        ui->tableWidget->clearSelection();
        lastProcessNumber = folderName.length();
        ui->tableWidget->clear();
        changed = 1;
        ui->label_2->setText(QString::number(folderName.length()));
        ui->tableWidget->setRowCount(folderName.length());
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Process ID"));
        for(int i = 0 ; i < folderName.length(); i++)
        {
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(folderName.at(i)));
            QFile file("/proc/"+folderName.at(i)+"/comm");
            file.open(QIODevice::ReadOnly);
            QTextStream text(&file);
            QString programName = text.readLine();
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(programName));
            file.close();
        }
        ui->tableWidget->sortItems(0,state);
    }
}

tskMngr::~tskMngr()
{
    delete ui;
}

void tskMngr::on_pushButton_2_clicked()
{
    if(state == Qt::AscendingOrder)
    {
        state = Qt::DescendingOrder;
    }
    else
    {
        state = Qt::AscendingOrder;
    }
}

void tskMngr::on_tableWidget_cellClicked(int row, int column)
{
    rowSelect = row;
    QString selectedPName = ui->tableWidget -> item(row, 0)->text();
    selectedPID = ui->tableWidget -> item(row, 1)->text();
    ui->label_3->setText(selectedPName);
    ui->label_5->setText(selectedPID);
}

void tskMngr::on_killButton_clicked()
{
    char *selectedPID_;
    QByteArray temp;
    temp = selectedPID.toLocal8Bit();
    selectedPID_ = temp.data();
    pid_t pidd;
    pidd = fork();
    if(pidd == 0)
    {
        execl("/bin/kill", "kill", selectedPID_, NULL);
        exit(pidd);
    }
}

void tskMngr::on_startButton_clicked()
{
    char *start_;
    QString tempqstr = ui->lineEdit->text();
    QByteArray tempqba;
    tempqba = tempqstr.toLocal8Bit();
    start_ = tempqba.data();
    pid_t pidd;
    pidd = fork();
    if(pidd == 0)
    {
        system(start_);
        exit(pidd);
    }
}
