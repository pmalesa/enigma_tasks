#ifndef COMPANYDATABASE_H
#define COMPANYDATABASE_H

#include <QMainWindow>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class CompanyDatabase;
}
QT_END_NAMESPACE

class CompanyDatabase : public QMainWindow
{
    Q_OBJECT

public:
    CompanyDatabase(QWidget *parent = nullptr);
    ~CompanyDatabase();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_exitButton_clicked();
    void on_dataTable_itemChanged(QTableWidgetItem* item);
    void on_dataTable_itemClicked(QTableWidgetItem* item);
    void on_dataTable_itemSelectionChanged();
    void on_switchLanguageButton_clicked();

private:
    void loadData();
    void updateDataFile();
    void switchLanguages(const QString& languageCode);

    Ui::CompanyDatabase* ui;
    QString _currentLanguage;
};
#endif // COMPANYDATABASE_H
