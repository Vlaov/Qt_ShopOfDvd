#include "searchdisk.h"
#include "ui_searchdisk.h"

searchdisk::searchdisk(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::searchdisk)
{
    ui->setupUi(this);
}

searchdisk::~searchdisk()
{
    delete ui;
}

QString searchdisk::getType() const {
    return ui->searchType->currentText();
}
QString searchdisk::getName() const {
    return ui->searchName->text();
}
QString searchdisk::getAuthor() const {
    return ui->searchAuthor->text();
}



void searchdisk::on_buttonBox_accepted()
{



}

