
#ifndef WAVEFORMSELECTDIALOG_H
#define WAVEFORMSELECTDIALOG_H

#include <QDialog>
#include "signalsources.h"

class WaveformSelectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WaveformSelectDialog(SignalSources* signalSources_, QWidget* parent = nullptr);

    QString selectedNativeName();

signals:
    void addPinnedWaveform(QString waveName);

private slots:
    void portChanged(int index);
    void channelChanged(const QString& name);
    void channelSelected();

private:
    SignalSources* signalSources;
    vector<QStringList> channelNameLists;

    QTabWidget* tabWidget;

    QComboBox* portComboBox;
    QComboBox* channelComboBox;
    QComboBox* filterComboBox;
    QComboBox* controllerSignalComboBox;

    QDialogButtonBox* buttonBox;

    QString getNativeName(const QString& completeName) const;
    bool isAmplifierName(const QString& name) const;
};

#endif // WAVEFORMSELECTDIALOG_H
