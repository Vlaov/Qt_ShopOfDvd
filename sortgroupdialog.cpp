#include "sortgroupdialog.h"
#include "ui_sortgroupdialog.h"


SortGroupDialog::SortGroupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SortGroupDialog)
{
    ui->setupUi(this);
}
SortGroupDialog::~SortGroupDialog()
{
    delete ui;
}
 SortGroupDialog::SortMode SortGroupDialog::getSortMode() const {
     switch(ui->sortingByType->currentIndex()) {
     case 1:
        return SortByTypeAndAuthor;
     case 2:
        return SortByTypeAndName;
     case 0:
     default:
        return NoSort;
     }
}

 SortGroupDialog::GroupMode SortGroupDialog::getGroupMode() const
 {
     switch (ui->groupComboBox->currentIndex()) {
     case 2:
         return GroupByType;
     case 1:
         return GroupByAuthor;
     case 0:
     default:
         return NoGroup;
     }
 }
