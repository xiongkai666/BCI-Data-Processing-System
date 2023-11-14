
#include "demodialog.h"
#include "advancedstartupdialog.h"

DemoDialog::DemoDialog(DemoSelections *demoSelection_, bool &useOpenCL_, uint8_t &playbackPorts_, QWidget *parent) :
    QDialog(parent),
    demoSelection(demoSelection_),
    useOpenCL(&useOpenCL_),
    playbackPorts(&playbackPorts_),
    message(nullptr),
    usbInterfaceButton(nullptr),
    recordControllerButton(nullptr),
    stimControllerButton(nullptr),
    playbackButton(nullptr)
{
    message = new QLabel(tr("No Intan controllers have been detected. Ensure devices are powered on and connected to this machine.\n"
                            "You may also run this software in demonstration mode or play back a saved data file."));

    usbInterfaceButton = new QPushButton(tr("RHD USB Interface Board Demo"), this);
    recordControllerButton = new QPushButton(tr("RHD Recording Controller Demo"), this);
    stimControllerButton = new QPushButton(tr("RHS Stim/Record Controller Demo"), this);
    playbackButton = new QPushButton(tr("Data File Playback"));

    advancedButton = new QPushButton(tr("Advanced"), this);
    advancedButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    int advancedButtonWidth = advancedButton->sizeHint().width() + 10;
    advancedButton->setFixedWidth(advancedButtonWidth);

    stimControllerButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    int buttonWidth = stimControllerButton->sizeHint().width() + 10;
    stimControllerButton->setFixedWidth(buttonWidth);
    usbInterfaceButton->setFixedWidth(buttonWidth);
    recordControllerButton->setFixedWidth(buttonWidth);
    playbackButton->setFixedWidth(buttonWidth);

    connect(usbInterfaceButton, SIGNAL(clicked(bool)), this, SLOT(usbInterface()));
    connect(recordControllerButton, SIGNAL(clicked(bool)), this, SLOT(recordController()));
    connect(stimControllerButton, SIGNAL(clicked(bool)), this, SLOT(stimController()));
    connect(playbackButton, SIGNAL(clicked(bool)), this, SLOT(playback()));
    connect(advancedButton, SIGNAL(clicked(bool)), this, SLOT(advanced()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(message);
    mainLayout->addWidget(usbInterfaceButton);
    mainLayout->addWidget(recordControllerButton);
    mainLayout->addWidget(stimControllerButton);
    mainLayout->addSpacing(8);
    mainLayout->addWidget(playbackButton);
    mainLayout->addSpacing(8);
    mainLayout->addWidget(advancedButton);

    mainLayout->setAlignment(usbInterfaceButton, Qt::AlignHCenter);
    mainLayout->setAlignment(recordControllerButton, Qt::AlignHCenter);
    mainLayout->setAlignment(stimControllerButton, Qt::AlignHCenter);
    mainLayout->setAlignment(playbackButton, Qt::AlignHCenter);

    setWindowTitle(tr("No Intan Controllers Detected"));
    setLayout(mainLayout);
}

void DemoDialog::closeEvent(QCloseEvent *)
{
    exit(EXIT_FAILURE);
}

void DemoDialog::usbInterface()
{
    *demoSelection = DemoUSBInterfaceBoard;
    accept();
}

void DemoDialog::recordController()
{
    *demoSelection = DemoRecordingController;
    accept();
}

void DemoDialog::stimController()
{
    *demoSelection = DemoStimRecordController;
    accept();
}

void DemoDialog::playback()
{
    *demoSelection = DemoPlayback;
    accept();
}

void DemoDialog::advanced()
{
    AdvancedStartupDialog advancedStartupDialog(*useOpenCL, *playbackPorts, true, this);
    advancedStartupDialog.exec();
}
