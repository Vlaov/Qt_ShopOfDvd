#ifndef SEARCHDISK_H
#define SEARCHDISK_H

#include <QDialog>

namespace Ui {
class searchdisk;
}

class searchdisk : public QDialog
{
    Q_OBJECT

public:
    explicit searchdisk(QWidget *parent = nullptr);
    ~searchdisk();

    QString getType() const;
    QString getName() const;
    QString getAuthor() const;


private slots:
    void on_buttonBox_accepted();

private:
    Ui::searchdisk *ui;
};

#endif // SEARCHDISK_H
