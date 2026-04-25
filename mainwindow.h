#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "disk.h"
#include "sortgroupdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addDisk_clicked();

    void on_delDisk_clicked();

    void on_saveDisks_clicked();

    void on_disksFromFile_clicked();

    void on_pushButton_clicked();

    void on_sortingButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Disk> disks;

    void showAllProducts() const;
    QVector<Disk> sortDisks(const QVector<Disk>& source, SortGroupDialog::SortMode mode);
    QVector<Disk> sortForGroupingByAuthor(const QVector<Disk>& source);
    QString buildGroupedByTypeText(const QVector<Disk>& source);
    QString buildGroupedByAuthorText(const QVector<Disk>& source);
};
#endif // MAINWINDOW_H
