
#include <QtWidgets>
#include <QStringList>
#include "abstractrhxcontroller.h"
#include "waveformselectdialog.h"

WaveformSelectDialog::WaveformSelectDialog(SignalSources* signalSources_, QWidget* parent) :
    QDialog(parent),
    signalSources(signalSources_)
{
    QStringList portNameList;
    for (int port = 0; port < AbstractRHXController::maxNumSPIPorts(signalSources->getControllerType()); ++port) {
        QString portName = "PORT " + QString(QChar('A' + port));
        QStringList nameList = signalSources->headstageSignalNameList(portName);
        if (!nameList.isEmpty()) {
            portNameList.append(portName);
            nameList.sort();
            channelNameLists.push_back(nameList);
        }
    }

    portComboBox = new QComboBox(this);
    portComboBox->addItems(portNameList);
    connect(portComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(portChanged(int)));

    channelComboBox = new QComboBox(this);
    if (channelNameLists.size() > 0) {
        channelComboBox->addItems(channelNameLists[0]);
    }
    connect(channelComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(channelChanged(QString)));

    filterComboBox = new QComboBox(this);
    filterComboBox->addItem("WIDE");
    filterComboBox->addItem("LOW");
    filterComboBox->addItem("HIGH");
    filterComboBox->addItem("SPK");
    if (signalSources->getControllerType() == ControllerStimRecord) {
        filterComboBox->addItem("DC");
    }
    filterComboBox->setEnabled(isAmplifierName(channelComboBox->currentText()));

    controllerSignalComboBox = new QComboBox(this);
    controllerSignalComboBox->addItems(signalSources->controllerIOSignalNameList());

    setWindowTitle(tr("Select Waveform"));

    QHBoxLayout* channelRow = new QHBoxLayout;
    channelRow->addWidget(portComboBox);
    channelRow->addWidget(channelComboBox);
    channelRow->addWidget(filterComboBox);
    channelRow->addStretch(1);

    QHBoxLayout* signalRow = new QHBoxLayout;
    signalRow->addWidget(controllerSignalComboBox);
    signalRow->addStretch(1);

    QFrame* headstageFrame = new QFrame(this);
    headstageFrame->setLayout(channelRow);
    QFrame* controllerFrame = new QFrame(this);
    controllerFrame->setLayout(signalRow);

    tabWidget = new QTabWidget(this);
    tabWidget->addTab(headstageFrame, tr("Headstage Signals"));
    tabWidget->addTab(controllerFrame, tr("Controller I/O"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(channelSelected()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(addPinnedWaveform(QString)), parent, SLOT(addPinnedWaveform(QString)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

void WaveformSelectDialog::portChanged(int index)
{
    for (int i = channelComboBox->count(); i >= 0; --i) {
        channelComboBox->removeItem(i);
    }
    channelComboBox->addItems(channelNameLists[index]);
    filterComboBox->setEnabled(isAmplifierName(channelComboBox->currentText()));
}

void WaveformSelectDialog::channelChanged(const QString& name)
{
    filterComboBox->setEnabled(isAmplifierName(name));
}

void WaveformSelectDialog::channelSelected()
{
    emit addPinnedWaveform(selectedNativeName());
    accept();
}

QString WaveformSelectDialog::selectedNativeName()
{
    QString name;
    if (tabWidget->currentIndex() == 0) {
        name = getNativeName(channelComboBox->currentText());
        if (filterComboBox->isEnabled()) {
            name += "|" + filterComboBox->currentText();
        }
    } else {
        name = getNativeName(controllerSignalComboBox->currentText());
    }
    return name;
}

QString WaveformSelectDialog::getNativeName(const QString& completeName) const
{
    if (!completeName.contains(" (")) return completeName;
    else return completeName.section(" (", 1, 1).chopped(1);
}

bool WaveformSelectDialog::isAmplifierName(const QString& name) const
{
    QString nativeName = getNativeName(name);
    QString second = nativeName.section('-', 1, 1);
    if (second.size() != 3) return false;
    if (second.left(1) == "0" || second.left(1) == "1") {
        return true;
    } else {
        return false;
    }
}
