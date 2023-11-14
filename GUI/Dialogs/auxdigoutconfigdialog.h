
#ifndef AUXDIGOUTCONFIGDIALOG_H
#define AUXDIGOUTCONFIGDIALOG_H

#include <vector>
#include <QDialog>

using namespace std;

class QCheckBox;
class QComboBox;
class QDialogButtonBox;

class AuxDigOutConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AuxDigOutConfigDialog(vector<bool> &auxOutEnabledIn, vector<int> &auxOutChannelIn, int numPorts,
                                   QWidget *parent = nullptr);

    bool enabled(int port);
    int channel(int port);

private slots:
    void enablePortAChanged(bool enable);
    void enablePortBChanged(bool enable);
    void enablePortCChanged(bool enable);
    void enablePortDChanged(bool enable);
    void enablePortEChanged(bool enable);
    void enablePortFChanged(bool enable);
    void enablePortGChanged(bool enable);
    void enablePortHChanged(bool enable);
    void channelPortAChanged(int channel);
    void channelPortBChanged(int channel);
    void channelPortCChanged(int channel);
    void channelPortDChanged(int channel);
    void channelPortEChanged(int channel);
    void channelPortFChanged(int channel);
    void channelPortGChanged(int channel);
    void channelPortHChanged(int channel);

private:
    vector<bool> auxOutEnabled;
    vector<int> auxOutChannel;

    QCheckBox *enablePortACheckBox;
    QCheckBox *enablePortBCheckBox;
    QCheckBox *enablePortCCheckBox;
    QCheckBox *enablePortDCheckBox;
    QCheckBox *enablePortECheckBox;
    QCheckBox *enablePortFCheckBox;
    QCheckBox *enablePortGCheckBox;
    QCheckBox *enablePortHCheckBox;

    QComboBox *channelPortAComboBox;
    QComboBox *channelPortBComboBox;
    QComboBox *channelPortCComboBox;
    QComboBox *channelPortDComboBox;
    QComboBox *channelPortEComboBox;
    QComboBox *channelPortFComboBox;
    QComboBox *channelPortGComboBox;
    QComboBox *channelPortHComboBox;

    QDialogButtonBox *buttonBox;

    void populatePortComboBox(QComboBox* channelPortComboBox);
};

#endif // AUXDIGOUTCONFIGDIALOG_H
