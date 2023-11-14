
#include "stimparameters.h"

StimParameters::StimParameters(SingleItemList &hList_, SystemState *state_, SignalType signalType_) :
    stimShape(nullptr),
    stimPolarity(nullptr),
    triggerSource(nullptr),
    triggerEdgeOrLevel(nullptr),
    triggerHighOrLow(nullptr),
    pulseOrTrain(nullptr),
    enabled(nullptr),
    maintainAmpSettle(nullptr),
    enableAmpSettle(nullptr),
    enableChargeRecovery(nullptr),
    firstPhaseDuration(nullptr),
    secondPhaseDuration(nullptr),
    interphaseDelay(nullptr),
    firstPhaseAmplitude(nullptr),
    secondPhaseAmplitude(nullptr),
    baselineVoltage(nullptr),
    postTriggerDelay(nullptr),
    pulseTrainPeriod(nullptr),
    refractoryPeriod(nullptr),
    preStimAmpSettle(nullptr),
    postStimAmpSettle(nullptr),
    postStimChargeRecovOn(nullptr),
    postStimChargeRecovOff(nullptr),
    signalType(signalType_)
{
    if (signalType == AmplifierSignal) {

        stimShape = new DiscreteItemList("Shape", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        stimShape->addItem("Biphasic", "Biphasic");
        stimShape->addItem("BiphasicWithInterphaseDelay", "BiphasicWithInterphaseDelay");
        stimShape->addItem("Triphasic", "Triphasic");
        stimShape->setValue("Biphasic");

        stimPolarity = new DiscreteItemList("Polarity", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        stimPolarity->addItem("NegativeFirst", "NegativeFirst");
        stimPolarity->addItem("PositiveFirst", "PositiveFirst");
        stimPolarity->setValue("NegativeFirst");

        triggerSource = new DiscreteItemList("Source", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        for (int i = 0; i < 16; ++i) {
            QString channelName = "DigitalIn" + QString("%1").arg(i + 1, 2, 10, QChar('0'));
            triggerSource->addItem(channelName, channelName);
        }
        for (int i = 0; i < 8; ++i) {
            QString channelName = "AnalogIn" + QString("%1").arg(i + 1, 2, 10, QChar('0'));
            triggerSource->addItem(channelName, channelName);
        }
        for (int i = 0; i < 8; ++i) {
            QString channelName = "KeyPressF" + QString::number(i + 1);
            triggerSource->addItem(channelName, channelName);
        }
        triggerSource->setValue("DigitalIn01");

        triggerEdgeOrLevel = new DiscreteItemList("TriggerEdgeOrLevel", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        triggerEdgeOrLevel->addItem("Edge", "Edge");
        triggerEdgeOrLevel->addItem("Level", "Level");
        triggerEdgeOrLevel->setValue("Edge");

        triggerHighOrLow = new DiscreteItemList("TriggerHighOrLow", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        triggerHighOrLow->addItem("High", "High");
        triggerHighOrLow->addItem("Low", "Low");
        triggerHighOrLow->setValue("High");

        pulseOrTrain = new DiscreteItemList("PulseOrTrain", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        pulseOrTrain->addItem("SinglePulse", "SinglePulse");
        pulseOrTrain->addItem("PulseTrain", "PulseTrain");
        pulseOrTrain->setValue("SinglePulse");

        enabled = new BooleanItem("StimEnabled", hList_, state_, false, XMLGroupStimParameters, TypeDependencyStim);
        maintainAmpSettle = new BooleanItem("MaintainAmpSettle", hList_, state_, false, XMLGroupStimParameters, TypeDependencyStim);
        enableAmpSettle = new BooleanItem("EnableAmpSettle", hList_, state_, true, XMLGroupStimParameters, TypeDependencyStim);
        enableChargeRecovery = new BooleanItem("EnableChargeRecovery", hList_, state_, false, XMLGroupStimParameters, TypeDependencyStim);

        firstPhaseDuration = new DoubleRangeItem("FirstPhaseDurationMicroseconds", hList_, state_, 0.0, 5000.0, 100.0, XMLGroupStimParameters, TypeDependencyStim);
        secondPhaseDuration = new DoubleRangeItem("SecondPhaseDurationMicroseconds", hList_, state_, 0.0, 5000.0, 100.0, XMLGroupStimParameters, TypeDependencyStim);
        interphaseDelay = new DoubleRangeItem("InterphaseDelayMicroseconds", hList_, state_, 0.0, 5000.0, 100.0, XMLGroupStimParameters, TypeDependencyStim);
        firstPhaseAmplitude = new DoubleRangeItem("FirstPhaseAmplitudeMicroAmps", hList_, state_, 0.0, 2550.0, 0.0, XMLGroupStimParameters, TypeDependencyStim);
        secondPhaseAmplitude = new DoubleRangeItem("SecondPhaseAmplitudeMicroAmps", hList_, state_, 0.0, 2550.0, 0.0, XMLGroupStimParameters, TypeDependencyStim);
        postTriggerDelay = new DoubleRangeItem("PostTriggerDelayMicroseconds", hList_, state_, 0.0, 500000.0, 0.0, XMLGroupStimParameters, TypeDependencyStim);
        pulseTrainPeriod = new DoubleRangeItem("PulseTrainPeriodMicroseconds", hList_, state_, 0.0, 1000000.0, 10000.0, XMLGroupStimParameters, TypeDependencyStim);
        refractoryPeriod = new DoubleRangeItem("RefractoryPeriodMicroseconds", hList_, state_, 0.0, 1000000.0, 1000.0, XMLGroupStimParameters, TypeDependencyStim);
        preStimAmpSettle = new DoubleRangeItem("PreStimAmpSettleMicroseconds", hList_, state_, 0.0, 500000.0, 0.0, XMLGroupStimParameters, TypeDependencyStim);
        postStimAmpSettle = new DoubleRangeItem("PostStimAmpSettleMicroseconds", hList_, state_, 0.0, 500000.0, 1000.0, XMLGroupStimParameters, TypeDependencyStim);
        postStimChargeRecovOn = new DoubleRangeItem("PostStimChargeRecovOnMicroseconds", hList_, state_, 0.0, 1000000.0, 0.0, XMLGroupStimParameters, TypeDependencyStim);
        postStimChargeRecovOff = new DoubleRangeItem("PostStimChargeRecovOffMicroseconds", hList_, state_, 0.0, 1000000.0, 0.0, XMLGroupStimParameters, TypeDependencyStim);
        numberOfStimPulses = new IntRangeItem("NumberOfStimPulses", hList_, state_, 0, 256, 2, XMLGroupStimParameters, TypeDependencyStim);

    } else if (signalType == BoardDacSignal) {

        stimShape = new DiscreteItemList("Shape", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        stimShape->addItem("Biphasic", "Biphasic");
        stimShape->addItem("BiphasicWithInterphaseDelay", "BiphasicWithInterphaseDelay");
        stimShape->addItem("Triphasic", "Triphasic");
        stimShape->addItem("Monophasic", "Monophasic");
        stimShape->setValue("Biphasic");

        stimPolarity = new DiscreteItemList("Polarity", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        stimPolarity->addItem("NegativeFirst", "NegativeFirst");
        stimPolarity->addItem("PositiveFirst", "PositiveFirst");
        stimPolarity->setValue("NegativeFirst");

        triggerSource = new DiscreteItemList("Source", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        for (int i = 0; i < 16; ++i) {
            QString channelName = "DigitalIn" + QString("%1").arg(i + 1, 2, 10, QChar('0'));
            triggerSource->addItem(channelName, channelName);
        }
        for (int i = 0; i < 8; ++i) {
            QString channelName = "AnalogIn" + QString("%1").arg(i + 1, 2, 10, QChar('0'));
            triggerSource->addItem(channelName, channelName);
        }
        for (int i = 0; i < 8; ++i) {
            QString channelName = "KeyPressF" + QString::number(i + 1);
            triggerSource->addItem(channelName, channelName);
        }
        triggerSource->setValue("DigitalIn01");

        triggerEdgeOrLevel = new DiscreteItemList("TriggerEdgeOrLevel", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        triggerEdgeOrLevel->addItem("Edge", "Edge");
        triggerEdgeOrLevel->addItem("Level", "Level");
        triggerEdgeOrLevel->setValue("Edge");

        triggerHighOrLow = new DiscreteItemList("TriggerHighOrLow", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        triggerHighOrLow->addItem("High", "High");
        triggerHighOrLow->addItem("Low", "Low");
        triggerHighOrLow->setValue("High");

        pulseOrTrain = new DiscreteItemList("PulseOrTrain", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        pulseOrTrain->addItem("SinglePulse", "SinglePulse");
        pulseOrTrain->addItem("PulseTrain", "PulseTrain");
        pulseOrTrain->setValue("SinglePulse");

        enabled = new BooleanItem("StimEnabled", hList_, state_, false, XMLGroupStimParameters, TypeDependencyStim);

        firstPhaseDuration = new DoubleRangeItem("FirstPhaseDurationMicroseconds", hList_, state_, 0.0, 5000.0, 100.0, XMLGroupStimParameters, TypeDependencyStim);
        secondPhaseDuration = new DoubleRangeItem("SecondPhaseDurationMicroseconds", hList_, state_, 0.0, 5000.0, 100.0, XMLGroupStimParameters, TypeDependencyStim);
        interphaseDelay = new DoubleRangeItem("InterphaseDelayMicroseconds", hList_, state_, 0.0, 5000.0, 100.0, XMLGroupStimParameters, TypeDependencyStim);
        firstPhaseAmplitude = new DoubleRangeItem("FirstPhaseAmplitudeVolts", hList_, state_, 0.0, 10.24, 0.0, XMLGroupStimParameters, TypeDependencyStim);
        secondPhaseAmplitude = new DoubleRangeItem("SecondPhaseAmplitudeVolts", hList_, state_, 0.0, 10.24, 0.0, XMLGroupStimParameters, TypeDependencyStim);
        baselineVoltage = new DoubleRangeItem("BaselineVoltageVolts", hList_, state_, -10.24, 10.24, 0.0, XMLGroupStimParameters, TypeDependencyStim);
        postTriggerDelay = new DoubleRangeItem("PostTriggerDelayMicroseconds", hList_, state_, 0.0, 500000.0, 0.0, XMLGroupStimParameters, TypeDependencyStim);
        pulseTrainPeriod = new DoubleRangeItem("PulseTrainPeriodMicroseconds", hList_, state_, 0.0, 1000000.0, 10000.0, XMLGroupStimParameters, TypeDependencyStim);
        refractoryPeriod = new DoubleRangeItem("RefractoryPeriodMicroseconds", hList_, state_, 0.0, 1000000.0, 1000.0, XMLGroupStimParameters, TypeDependencyStim);

        numberOfStimPulses = new IntRangeItem("NumberOfStimPulses", hList_, state_, 0, 256, 2, XMLGroupStimParameters, TypeDependencyStim);

    } else {

        triggerSource = new DiscreteItemList("Source", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        for (int i = 0; i < 16; ++i) {
            QString channelName = "DigitalIn" + QString("%1").arg(i + 1, 2, 10, QChar('0'));
            triggerSource->addItem(channelName, channelName);
        }
        for (int i = 0; i < 8; ++i) {
            QString channelName = "AnalogIn" + QString("%1").arg(i + 1, 2, 10, QChar('0'));
            triggerSource->addItem(channelName, channelName);
        }
        for (int i = 0; i < 8; ++i) {
            QString channelName = "KeyPressF" + QString::number(i + 1);
            triggerSource->addItem(channelName, channelName);
        }
        triggerSource->setValue("DigitalIn01");

        triggerEdgeOrLevel = new DiscreteItemList("TriggerEdgeOrLevel", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        triggerEdgeOrLevel->addItem("Edge", "Edge");
        triggerEdgeOrLevel->addItem("Level", "Level");
        triggerEdgeOrLevel->setValue("Edge");

        triggerHighOrLow = new DiscreteItemList("TriggerHighOrLow", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        triggerHighOrLow->addItem("High", "High");
        triggerHighOrLow->addItem("Low", "Low");
        triggerHighOrLow->setValue("High");

        pulseOrTrain = new DiscreteItemList("PulseOrTrain", hList_, state_, XMLGroupStimParameters, TypeDependencyStim);
        pulseOrTrain->addItem("SinglePulse", "SinglePulse");
        pulseOrTrain->addItem("PulseTrain", "PulseTrain");
        pulseOrTrain->setValue("SinglePulse");

        enabled = new BooleanItem("StimEnabled", hList_, state_, false, XMLGroupStimParameters, TypeDependencyStim);

        firstPhaseDuration = new DoubleRangeItem("FirstPhaseDurationMicroseconds", hList_, state_, 0.0, 100000, 100.0, XMLGroupStimParameters, TypeDependencyStim);
        postTriggerDelay = new DoubleRangeItem("PostTriggerDelayMicroseconds", hList_, state_, 0.0, 500000.0, 0.0, XMLGroupStimParameters, TypeDependencyStim);
        pulseTrainPeriod = new DoubleRangeItem("PulseTrainPeriodMicroseconds", hList_, state_, 0.0, 1000000.0, 10000.0, XMLGroupStimParameters, TypeDependencyStim);
        refractoryPeriod = new DoubleRangeItem("RefractoryPeriodMicroseconds", hList_, state_, 0.0, 1000000.0, 1000.0, XMLGroupStimParameters, TypeDependencyStim);

        numberOfStimPulses = new IntRangeItem("NumberOfStimPulses", hList_, state_, 0, 256, 2, XMLGroupStimParameters, TypeDependencyStim);
    }
}

void StimParameters::populateParametersFrom(StimParameters *originalStimParameters)
{
    if (stimShape)
        stimShape->setIndex(originalStimParameters->stimShape->getIndex());

    if (stimPolarity)
        stimPolarity->setIndex(originalStimParameters->stimPolarity->getIndex());

    if (triggerSource)
        triggerSource->setIndex(originalStimParameters->triggerSource->getIndex());

    if (triggerEdgeOrLevel)
        triggerEdgeOrLevel->setIndex(originalStimParameters->triggerEdgeOrLevel->getIndex());

    if (triggerHighOrLow)
        triggerHighOrLow->setIndex(originalStimParameters->triggerHighOrLow->getIndex());

    if (pulseOrTrain)
        pulseOrTrain->setIndex(originalStimParameters->pulseOrTrain->getIndex());

    if (enabled)
        enabled->setValue(originalStimParameters->enabled->getValue());

    if (maintainAmpSettle)
        maintainAmpSettle->setValue(originalStimParameters->maintainAmpSettle->getValue());

    if (enableAmpSettle)
        enableAmpSettle->setValue(originalStimParameters->enableAmpSettle->getValue());

    if (enableChargeRecovery)
        enableChargeRecovery->setValue(originalStimParameters->enableChargeRecovery->getValue());


    if (firstPhaseDuration)
        firstPhaseDuration->setValue(originalStimParameters->firstPhaseDuration->getValue());

    if (secondPhaseDuration)
        secondPhaseDuration->setValue(originalStimParameters->secondPhaseDuration->getValue());

    if (interphaseDelay)
        interphaseDelay->setValue(originalStimParameters->interphaseDelay->getValue());

    if (firstPhaseAmplitude)
        firstPhaseAmplitude->setValue(originalStimParameters->firstPhaseAmplitude->getValue());

    if (secondPhaseAmplitude)
        secondPhaseAmplitude->setValue(originalStimParameters->secondPhaseAmplitude->getValue());

    if (baselineVoltage)
        baselineVoltage->setValue(originalStimParameters->baselineVoltage->getValue());

    if (postTriggerDelay)
        postTriggerDelay->setValue(originalStimParameters->postTriggerDelay->getValue());

    if (pulseTrainPeriod)
        pulseTrainPeriod->setValue(originalStimParameters->pulseTrainPeriod->getValue());

    if (refractoryPeriod)
        refractoryPeriod->setValue(originalStimParameters->refractoryPeriod->getValue());

    if (preStimAmpSettle)
        preStimAmpSettle->setValue(originalStimParameters->preStimAmpSettle->getValue());

    if (postStimAmpSettle)
        postStimAmpSettle->setValue(originalStimParameters->postStimAmpSettle->getValue());

    if (postStimChargeRecovOn)
        postStimChargeRecovOn->setValue(originalStimParameters->postStimChargeRecovOn->getValue());

    if (postStimChargeRecovOff)
        postStimChargeRecovOff->setValue(originalStimParameters->postStimChargeRecovOff->getValue());

    if (numberOfStimPulses)
        numberOfStimPulses->setValue(originalStimParameters->numberOfStimPulses->getValue());
}
