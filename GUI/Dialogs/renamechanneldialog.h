
#ifndef RENAMECHANNELDIALOG_H
#define RENAMECHANNELDIALOG_H

#include <QtWidgets>
#include <QDialog>

class QDialogButtonBox;
class QLineEdit;
class QLabel;

class RenameChannelDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RenameChannelDialog(const QString& nativeName, const QString& oldName, QWidget* parent);

    QString name() const { return nameLineEdit->text(); }

private slots:
    void onLineEditTextChanged();

private:
    QLineEdit *nameLineEdit;
    QDialogButtonBox *buttonBox;
};

#endif // RENAMECHANNELDIALOG_H
