
#ifndef CONTROLPANELTRIGGERTAB_H
#define CONTROLPANELTRIGGERTAB_H

#include <QtWidgets>
#include "controllerinterface.h"
#include "systemstate.h"

class ControlPanelTriggerTab : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanelTriggerTab(ControllerInterface* controllerInterface_, SystemState* state_, QWidget *parent = nullptr);
    void updateFromState();

private slots:
    void enableTrigger(bool enable);
    void setTriggerSource(int index);
    void setTriggerPolarity(int index);
    void setTriggerPosition(int index);

private:
    SystemState* state;
    ControllerInterface* controllerInterface;

    QCheckBox *triggerEnableCheckBox;

    QComboBox *triggerSourceComboBox;
    QComboBox *triggerPolarityComboBox;
    QComboBox *triggerPositionComboBox;
};

#endif // CONTROLPANELTRIGGERTAB_H
