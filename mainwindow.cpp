#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "disk.h"
#include "searchdisk.h"
#include "sortgroupdialog.h"
#include <QDebug>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <algorithm>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAllProducts() const {
    QString allProducts;
    for (int i = 0; i < disks.size(); i++) {
        allProducts.push_back(disks[i].toDisplayString() + '\n' + '\n');
    }
    ui->showElement->setPlainText(allProducts);
}

void MainWindow::on_addDisk_clicked()
{
    bool ok;

    QString typeFromUi = ui->choosingType->currentText();
    QString nameFromUi = ui->choosingName->text();
    QString authorFromUi = ui->choosingAuthor->text();
    QString priceFromUi = ui->choosingPrice->text();
    QString noteFromUi = ui->choosingNote->text();

    float floatFromUi = priceFromUi.toFloat(&ok);
    if(priceFromUi.isEmpty() || !ok) floatFromUi = 0.0;

    if (nameFromUi.isEmpty()) {
        ui->choosingName->setPlaceholderText("Поле не может быть пустым!");
        return;
    }
    Disk newProduct(typeFromUi, nameFromUi, authorFromUi, floatFromUi, noteFromUi);
    disks.push_back(newProduct);
    showAllProducts();

    ui->choosingName->clear();
    ui->choosingAuthor->clear();
    ui->choosingPrice->clear();
    ui->choosingNote->clear();
    ui->choosingType->setCurrentIndex(0);
}


void MainWindow::on_delDisk_clicked()
{
    if (disks.empty()) {
        QMessageBox::warning(this, "Предупреждение", "Магазин пустой, надо что-то добавить!");
        return;
    }

    bool ok;
    int getDelIndex = QInputDialog::getInt(
        this,
        "Выбор элемента",
        "Введите номер диска для удаления...",
        1,
        1,
        disks.size(),
        1,
        &ok);

    if (ok) {
        disks.remove(getDelIndex - 1);
        showAllProducts();
    }


}


void MainWindow::on_saveDisks_clicked()
{
    QString filename = QFileDialog::getSaveFileName(
        this,
        tr("Сохранить в файл"),
        "",
        tr("Text Files (*.txt);;All Files (*)"));

    if (!filename.isEmpty()) {
        QFile file(filename);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int i = 0; i < disks.size(); i++) {
                out << disks[i].objectToString() << '\n';
            }
            file.close();
            QMessageBox::information(this, "Сообщение", "Сохранение прошло успешно!");
        } else {
            QMessageBox::warning(this, "Предупреждение", "Файл не открылся!");
            return;
        }
    }
}


void MainWindow::on_disksFromFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Text Files (*.txt);;All Files (*)");

    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            disks.clear();
            QTextStream in(&file);
            QString stringToFile;
            while(!in.atEnd()) {
                stringToFile = in.readLine();
                if(stringToFile == "") continue;
                disks.push_back(Disk::stringToObject(stringToFile.trimmed()));
            }
            file.close();
            showAllProducts();
            QMessageBox::information(this, "Сообщение", "Загрузка прошла успешно!");
        } else {
            QMessageBox::warning(this, "Предупреждение", "Файл не открылся!");
            return;
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    searchdisk windowFilters;
    if (windowFilters.exec() == QDialog::Accepted) {
        QString filterType = windowFilters.getType();
        QString filterName = windowFilters.getName();
        QString filterAuthor = windowFilters.getAuthor();
        QString filterResult;
        bool matchType;
        bool matchName;
        bool matchAuthor;

        for (int i = 0; i < disks.size(); i++) {
            if (filterType == "Все") {
                matchType = true;
            } else {
                matchType = (filterType == disks[i].getType());
            }

            if (filterName.isEmpty()) {
                matchName = true;
            } else {
                matchName = (disks[i].getName()).contains(filterName, Qt::CaseInsensitive);
            }

            if (filterAuthor.isEmpty()) {
                matchAuthor = true;
            } else {
                matchAuthor = (disks[i].getAuthor()).contains(filterAuthor, Qt::CaseInsensitive);
            }
            if (matchType && matchName && matchAuthor) {
                filterResult += disks[i].toDisplayString() + '\n' + '\n';
            }
        }
        if (filterResult.isEmpty()) {
            QMessageBox::information(this, "Сообщение", "Совпадений не найдено");
        } else {
            ui->showElement->setPlainText(filterResult);
        }
    }
}





QVector<Disk> MainWindow::sortDisks(const QVector<Disk>& source, SortGroupDialog::SortMode mode)
{
    QVector<Disk> result = source;

    if (mode == SortGroupDialog::NoSort) {
        return result;
    }

    std::sort(result.begin(), result.end(),
              [mode](const Disk& a, const Disk& b)
              {
                  int typeCompare = QString::compare(a.getType(), b.getType(), Qt::CaseInsensitive);

                  if (typeCompare != 0) {
                      return typeCompare < 0;
                  }

                  if (mode == SortGroupDialog::SortByTypeAndName) {
                      return QString::compare(a.getName(), b.getName(), Qt::CaseInsensitive) < 0;
                  }

                  if (mode == SortGroupDialog::SortByTypeAndAuthor) {
                      return QString::compare(a.getAuthor(), b.getAuthor(), Qt::CaseInsensitive) < 0;
                  }

                  return false;
              });

    return result;
}





QString MainWindow::buildGroupedByTypeText(const QVector<Disk>& source)
{
    if (source.isEmpty()) {
        return "Список пуст.";
    }

    QString result;
    QString currentType;

    for (const Disk& disk : source) {
        if (disk.getType() != currentType) {
            currentType = disk.getType();

            if (!result.isEmpty()) {
                result += "\n";
            }

            result += "=== " + currentType + " ===\n";
        }

        result += disk.toDisplayString() + "\n\n";
    }

    return result;
}

QString MainWindow::buildGroupedByAuthorText(const QVector<Disk>& source)
{
    if (source.isEmpty()) {
        return "Список пуст.";
    }

    QString result;
    QString currentAuthor;

    for (const Disk& disk : source) {
        if (disk.getAuthor() != currentAuthor) {
            currentAuthor = disk.getAuthor();

            if (!result.isEmpty()) {
                result += "\n";
            }

            result += "=== " + currentAuthor + " ===\n";
        }

        result += disk.toDisplayString() + "\n\n";
    }

    return result;
}
QVector<Disk> MainWindow::sortForGroupingByAuthor(const QVector<Disk>& source)
{
    QVector<Disk> result = source;

    std::sort(result.begin(), result.end(),
              [](const Disk& a, const Disk& b)
              {
                  int authorCompare = QString::compare(a.getAuthor(), b.getAuthor(), Qt::CaseInsensitive);
                  if (authorCompare != 0) {
                      return authorCompare < 0;
                  }

                  return QString::compare(a.getName(), b.getName(), Qt::CaseInsensitive) < 0;
              });

    return result;
}
void MainWindow::on_sortingButton_clicked()
{
    SortGroupDialog dialog(this);

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    SortGroupDialog::SortMode sortMode = dialog.getSortMode();
    SortGroupDialog::GroupMode groupMode = dialog.getGroupMode();

    QVector<Disk> processed;

    if (groupMode == SortGroupDialog::GroupByAuthor) {
        processed = sortForGroupingByAuthor(disks);
    } else {
        processed = sortDisks(disks, sortMode);
    }

    ui->showElement->clear();

    if (processed.isEmpty()) {
        ui->showElement->setPlainText("Список пуст.");
        return;
    }

    if (groupMode == SortGroupDialog::GroupByType) {
        ui->showElement->setPlainText(buildGroupedByTypeText(processed));
    } else if (groupMode == SortGroupDialog::GroupByAuthor) {
        ui->showElement->setPlainText(buildGroupedByAuthorText(processed));
    } else {
        for (const Disk& disk : processed) {
            ui->showElement->appendPlainText(disk.toDisplayString());
            ui->showElement->appendPlainText("");
        }
    }
}

