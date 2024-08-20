#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>

class QComboBox;
class QLineEdit;
class QLabel;
class QPushButton;
class QGridLayout;
class Item;

class ItemDialog : public QDialog
{
    Q_OBJECT
public:
    ItemDialog(QWidget *parent = nullptr);

signals:
    void dataEntered(Item*);

private slots:
    void addButtonClicked();
    void enableButton();

private:
    QGridLayout *dataGrid;
    QComboBox *itemType;
    QLineEdit *itemName;
    QLabel *message;
    QPushButton *addButton;
};

#endif // ITEMDIALOG_H
