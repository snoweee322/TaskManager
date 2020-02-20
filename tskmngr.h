#ifndef TSKMNGR_H
#define TSKMNGR_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableView>
#include <QString>
#include <sys/stat.h>
#include <QDir>
#include <QTimer>
#include <QLabel>
#include <QList>
#include <QFile>
#include <unistd.h>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class tskMngr; }
QT_END_NAMESPACE

class tskMngr : public QMainWindow
{
    Q_OBJECT

public:
    tskMngr(QWidget *parent = nullptr);
    Qt::SortOrder state;
    int rowSelect = 0;
    int lastProcessNumber = 0;
    int changed = 0;
    QString selectedPID;
    QString qwerrty;
    ~tskMngr();

private:
    Ui::tskMngr *ui;
    QTableWidget *tableWidget;
    QDir *directory1;
    QTimer *timer;

private slots:
    void slotUpdateProcessList();
    void on_pushButton_2_clicked();
    void on_tableWidget_cellClicked(int row, int column);
    void on_killButton_clicked();
    void on_startButton_clicked();
};
#endif // TSKMNGR_H
