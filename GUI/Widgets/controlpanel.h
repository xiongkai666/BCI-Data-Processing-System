
#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QtWidgets>
#include "abstractpanel.h"
#include "controllerinterface.h"
#include "systemstate.h"
#include "commandparser.h"
#include "filterdisplayselector.h"

class ControlWindow;
class StimParamDialog;
class AnOutDialog;
class DigOutDialog;
class ControlPanelBandwidthTab;
class ControlPanelImpedanceTab;
class ControlPanelAudioAnalogTab;
class ControlPanelConfigureTab;
class ControlPanelTriggerTab;

class ControlPanel : public AbstractPanel
{
    Q_OBJECT
public:
    explicit ControlPanel(ControllerInterface* controllerInterface_, SystemState* state_, CommandParser* parser_,
                          ControlWindow *parent = nullptr);
    void updateForRun() override final;
    void updateForStop() override final;

    void updateSlidersEnabled(YScaleUsed yScaleUsed) override final;
    YScaleUsed slidersEnabled() const override final;

    void setCurrentTabName(QString tabName) override final;
    QString currentTabName() const override final;

public slots:
    void updateFromState() override final;

private slots:

private:
    QHBoxLayout* createSelectionLayout() override final;
    QHBoxLayout* createSelectionToolsLayout() override final;
    QHBoxLayout* createDisplayLayout() override final;

    void updateYScales() override final;

    QToolButton *hideControlPanelButton;
    QLabel* topLabel;
    ControlPanelBandwidthTab *bandwidthTab;
    ControlPanelImpedanceTab *impedanceTab;
    ControlPanelAudioAnalogTab *audioAnalogTab;
    ControlPanelTriggerTab *triggerTab;

    QSlider *lowSlider;
    QSlider *highSlider;
    QSlider *analogSlider;

    QLabel *lowLabel;
    QLabel *highLabel;
    QLabel *analogLabel;

};

#endif // CONTROLPANEL_H
