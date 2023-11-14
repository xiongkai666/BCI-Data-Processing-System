
#include "displayedwaveform.h"

WaveformType DisplayedWaveform::translateSignalTypeToWaveformType(SignalType signalType)
{
    switch (signalType) {
    case AmplifierSignal:
        return AmplifierWaveform;
    case AuxInputSignal:
        return AuxInputWaveform;
    case SupplyVoltageSignal:
        return SupplyVoltageWaveform;
    case BoardAdcSignal:
        return BoardAdcWaveform;
    case BoardDacSignal:
        return BoardDacWaveform;
    case BoardDigitalInSignal:
        return BoardDigInWaveform;
    case BoardDigitalOutSignal:
        return BoardDigOutWaveform;
    default:
        return UnknownWaveform;
    }
}

bool DisplayedWaveform::positiveOnlyType(WaveformType waveformType)
{
    return (waveformType == BoardDigInWaveform ||
            waveformType == BoardDigOutWaveform ||
            waveformType == RasterWaveform);
}
