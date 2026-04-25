#ifndef SORTGROUPDIALOG_H
#define SORTGROUPDIALOG_H

#include <QDialog>

namespace Ui {
class SortGroupDialog;
}

class SortGroupDialog : public QDialog
{
    Q_OBJECT

public:
    enum SortMode {
        NoSort,
        SortByTypeAndName,
        SortByTypeAndAuthor
    };

    enum GroupMode {
        NoGroup,
        GroupByType,
        GroupByAuthor
    };

    explicit SortGroupDialog(QWidget *parent = nullptr);
    ~SortGroupDialog();

    SortMode getSortMode() const;
    GroupMode getGroupMode() const;

private:
    Ui::SortGroupDialog *ui;
};

#endif // SORTGROUPDIALOG_H
