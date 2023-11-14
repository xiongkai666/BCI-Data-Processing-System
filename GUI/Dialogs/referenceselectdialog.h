
#ifndef REFERENCESELECTDIALOG_H
#define REFERENCESELECTDIALOG_H

#include <QDialog>
#include "signalsources.h"

class ReferenceSelectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReferenceSelectDialog(QString refString, SignalSources* signalSources_, bool useMedian, QWidget* parent = nullptr);

    QString referenceString() const;
    bool useMedian() const;

private slots:
    void hardwareButtonSelected();
    void portReferenceButtonSelected();
    void customReferenceButtonSelected();
    void selectedChannelsChanged();

private:
    SignalSources* signalSources;

    QButtonGroup *referenceButtonGroup;
    QRadioButton *hardwareReferenceRadioButton;
    QRadioButton *portReferenceRadioButton;
    QRadioButton *customReferenceRadioButton;

    QComboBox* portComboBox;
    QListWidget* channelListWidget;

    QCheckBox* medianCheckBox;
    QPushButton* okButton;
    QPushButton* cancelButton;

    int numSelectedChannels() const;
};

#endif // REFERENCESELECTDIALOG_H
