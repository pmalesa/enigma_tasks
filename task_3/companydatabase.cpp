#include "companydatabase.h"
#include "./ui_companydatabase.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>

CompanyDatabase::CompanyDatabase(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CompanyDatabase)
    , _currentLanguage("en_US")
{
    ui->setupUi(this);
    ui->deleteButton->setEnabled(false);

    /* Initialize columns of the table */
    ui->dataTable->setColumnCount(5);
    ui->dataTable->setHorizontalHeaderLabels({"Company name", "NIP", "Telephone number", "Address", "E-mail"});
    ui->dataTable->setColumnWidth(4, 180);

    /* Enable sorting */
    ui->dataTable->setSortingEnabled(true);

    loadData();
}

CompanyDatabase::~CompanyDatabase()
{
    delete ui;
}

void CompanyDatabase::loadData()
{
    QFile file("../task_3/data.csv");

    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream in(&file);
    int row = 0;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        ui->dataTable->insertRow(row);

        for (int col = 0; col < fields.size(); ++col)
            ui->dataTable->setItem(row, col, new QTableWidgetItem(fields[col]));

        ++row;
    }

    file.close();
}

void CompanyDatabase::updateDataFile()
{
    QFile file("../task_3/data.csv");

    if (!file.open(QIODevice::WriteOnly))
        return;

    QTextStream stream(&file);

    for (int i = 0; i < ui->dataTable->rowCount(); ++i)
    {
        QStringList rowContents;
        for (int j = 0; j < ui->dataTable->columnCount(); ++j)
        {
            QTableWidgetItem* item = ui->dataTable->item(i, j);
            rowContents << (item ? item->text() : "");
        }
        stream << rowContents.join(",") << "\n";
    }

    file.close();
}

void CompanyDatabase::switchLanguages(const QString& languageCode)
{
    _currentLanguage = languageCode;
    if (_currentLanguage == "en_US")
    {
        ui->dataTable->setHorizontalHeaderLabels({"Company name", "NIP", "Telephone number", "Address", "E-mail"});
        ui->addButton->setText(tr("Add"));
        ui->deleteButton->setText(tr("Delete"));
        ui->switchLanguageButton->setText(tr("Switch language"));
        ui->exitButton->setText(tr("Exit"));
    }
    else if (_currentLanguage == "pl_PL")
    {
        ui->dataTable->setHorizontalHeaderLabels({"Nazwa firmy", "NIP", "Numer telefonu", "Adres", "E-mail"});
        ui->addButton->setText(tr("Dodaj"));
        ui->deleteButton->setText(tr("Usuń"));
        ui->switchLanguageButton->setText(tr("Zmień język"));
        ui->exitButton->setText(tr("Wyjście"));
    }
}

void CompanyDatabase::on_addButton_clicked()
{
    int newRow = ui->dataTable->rowCount();
    ui->dataTable->insertRow(newRow);
    for (int col = 0; col < ui->dataTable->columnCount(); ++col)
        ui->dataTable->setItem(newRow, col, new QTableWidgetItem(""));
    ui->dataTable->setCurrentCell(newRow, 0);
    ui->dataTable->editItem(ui->dataTable->item(newRow, 0));
}

void CompanyDatabase::on_deleteButton_clicked()
{
    int selectedRow = ui->dataTable->currentRow();
    if (selectedRow < 0)
        return;

    ui->dataTable->removeRow(selectedRow);
    updateDataFile();
}

void CompanyDatabase::on_exitButton_clicked()
{
    QCoreApplication::quit();
}

void CompanyDatabase::on_dataTable_itemChanged(QTableWidgetItem* item)
{
    updateDataFile();
}

void CompanyDatabase::on_dataTable_itemClicked(QTableWidgetItem* item)
{
    ui->deleteButton->setEnabled(true);
}

void CompanyDatabase::on_dataTable_itemSelectionChanged()
{
    bool hasSelection = !ui->dataTable->selectedItems().isEmpty();
    ui->deleteButton->setEnabled(hasSelection);
}

void CompanyDatabase::on_switchLanguageButton_clicked()
{
    QString newLanguage = _currentLanguage == "en_US" ? "pl_PL" : "en_US";
    switchLanguages(newLanguage);
}

