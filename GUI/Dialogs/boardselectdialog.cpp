
#include <QSettings>
#include "datafilereader.h"
#include "boardselectdialog.h"
#include "scrollablemessageboxdialog.h"
#include "advancedstartupdialog.h"

// Check if Pionway DLL is loaded, and create an instance of CPionway.
BoardIdentifier::BoardIdentifier(QWidget *parent_) :
    parent(parent_)
{
    dev = new CPionway;
}

// Delete the controllers object.
BoardIdentifier::~BoardIdentifier()
{
    while (controllers.size() > 0) {
        delete controllers.first();
        controllers.remove(0);
    }
}

// Return a QString description of the specified board.
QString BoardIdentifier::getBoardTypeString(BoardMode mode, int numSpiPorts)
{
    switch (mode) {
    case RHDUSBInterfaceBoard:
        return RHDBoardString;
    case RHSController:
        return RHS128chString;
    case RHDController:
        if (numSpiPorts == 4) return RHD512chString;
        else return RHD1024chString;
    case CLAMPController:
        if (numSpiPorts == 2) return CLAMP2chString;
        else return CLAMP8chString;
    case UnknownUSB2Device:
        return UnknownUSB2String;
    case UnknownUSB3Device:
        return UnknownUSB3String;
    case RHSController_7310:
        return RHS128ch_7310String;
    case RHDController_7310:
        if (numSpiPorts == 4) return RHD512ch_7310String;
        else return RHD1024ch_7310String;
    case UnknownUSB3_7310Device:
        return UnknownUSB3String;
    default:
        return UnknownString;
    }
}

// Return a QIcon with a picture of the specified board.
QIcon BoardIdentifier::getIcon(const QString& boardType, QStyle *style, int size)
{
    if (boardType == RHDBoardString)
        return QIcon(":/images/usb_interface_board.png");
    else if (boardType == RHS128chString || boardType == RHS128ch_7310String)
        return QIcon(":/images/stim_controller_board.png");
    else if (boardType == RHD512chString || boardType == RHD512ch_7310String)
        return QIcon(":/images/rhd512_controller_board.png");
    else if (boardType == RHD1024chString || boardType == RHD1024ch_7310String)
        return QIcon(":/images/rhd1024_controller_board.png");
    else if (boardType == CLAMP2chString)
        return QIcon(":/images/clamp2_controller_board.png");
    else if (boardType == CLAMP8chString)
        return QIcon(":/images/clamp8_controller_board.png");
    else
        return QIcon(style->standardIcon(QStyle::SP_MessageBoxQuestion).pixmap(size));
}

// Return a QVector of ControllerInfo structures containing information about each controller, after uploading bit files
// to each controller and determining its characteristics.
QVector<ControllerInfo*> BoardIdentifier::getConnectedControllersInfo()
{
    int i, nDevices;
    qDebug() << "Scanning USB for Pionway devices...";
    dev->GetDeviceCount(&nDevices);
    qDebug() << "Found" << nDevices << "Pionway" << ((nDevices == 1) ? "device" : "devices") << "connected.";

    for (i = 0; i < nDevices; ++i) {
        // Create Controller data structure
        ControllerInfo *controller = new ControllerInfo;

        // Fill Controller data structure with characteristics relating to this controller.
        // This function uploads a bit file to the controller, writes some WireIns, and reads some WireOuts.
        identifyController(controller, i);

        // Add this Controller to the 'controllers' QVector.
        controllers.append(controller);
    }
    delete dev;

    return controllers;
}

// Populate variables in 'controller'. Upload a bit file, writes some WireIns, and reads some WireOuts.
void BoardIdentifier::identifyController(ControllerInfo *controller, int index)
{
    // Populate serialNumber field.
    controller->serialNumber = dev->GetDeviceListSerial(index).c_str();

    // Populate usbVersion field.
    QString modelName = opalKellyModelName(dev->GetDeviceListModel(index));
    if (modelName == "XEM6010LX45") {
        controller->usbVersion = USB2;
    } else if (modelName == "XEM6310LX45") {
        controller->usbVersion = USB3;
    } else if (modelName == "XEM7310A75") {
        controller->usbVersion = USB3_7310;
    } else {
        controller->usbVersion = USB3_7310;
        qDebug() << "Pionway model name not recognized, assuming XEM7310";
    }

    // Upload bitfile to determine boardMode, expConnected, and numSPIPorts.
    // Initialize expConnected, numSPIPorts, and boardMode to correspond to an unsuccessful mat.
    controller->expConnected = false;
    controller->numSPIPorts = 0;
    controller->boardMode = UnknownUSB2Device;

    // Open device.
    if (dev->OpenBySerial(dev->GetDeviceListSerial(index).c_str()) != CPionway::NO_ERR) {
        qDebug() << "Device could not be opened. Is one connected?";
        return;
    }

    // Set up default PLL.
    //dev->LoadDefaultPLLConfiguration();

    // Determine proper bitfile to load to FPGA (depending on if USB 2 or 3).
    //QString bitfilename = (controller->usbVersion == USB2) ? ConfigFileXEM6010Tester : ConfigFileRHDController;
    QString bitfilename;
    if (controller->usbVersion == USB2) {
        bitfilename = ConfigFileXEM6010Tester;
    } else if (controller->usbVersion == USB3) {
        bitfilename = ConfigFileRHDController;
    } else {
        bitfilename = ConfigFileRHDController_7310;
        //bitfilename = ConfigFileRHSController_7310;
    }

    // Upload bit file.
    if (!uploadFpgaBitfileQMessageBox(QCoreApplication::applicationDirPath() + "/" + bitfilename)) {
        QMessageBox::critical(nullptr, QObject::tr("Configuration File Error: Software Aborting"),
                              QObject::tr("Cannot upload configuration file: ") + bitfilename +
                              QObject::tr(".  Make sure file is in the same directory as the executable file."));
        exit(EXIT_FAILURE);
    }
    RHXController::resetBoard(dev);

    // Read mode from board.
    int boardMode = RHXController::getBoardMode(dev);

    if (controller->usbVersion == USB2) {
        // Populate boardMode field for USB2 boards.
        switch (boardMode) {
        case RHDUSBInterfaceBoardMode:
            controller->boardMode = RHDUSBInterfaceBoard;
            controller->numSPIPorts = 4;
            controller->expConnected = false;
            break;
        case RHSControllerBoardMode:
            controller->boardMode = RHSController;
            break;
        case CLAMPControllerBoardMode:
            controller->boardMode = CLAMPController;
            break;
        default:
            controller->boardMode = UnknownUSB2Device;
            return;
        }
    } else if (controller->usbVersion == USB3) {
        // Populate boardMode field for USB3 boards.
        switch (boardMode) {
        case RHDControllerBoardMode:
            controller->boardMode = RHDController;
            break;
        default:
            controller->boardMode = UnknownUSB3Device;
            return;
        }
    } else {
        // Populate boardMode field for USB3_7310 boards.
        switch (boardMode) {
        case RHSControllerBoardMode:
            controller->boardMode = RHSController_7310;
            break;
        case RHDControllerBoardMode:
            controller->boardMode = RHDController_7310;
            break;
        default:
            controller->boardMode = UnknownUSB3_7310Device;
            return;
        }
    }

    // For all boards other than the RHD USB Interface Board, determine the number of SPI ports and whether an expander board
    // is connected.
    if (controller->boardMode != RHDUSBInterfaceBoard) {
        dev->UpdateWireOuts();
        controller->numSPIPorts = RHXController::getNumSPIPorts(dev, (controller->usbVersion == USB3 || controller->usbVersion == USB3_7310),
                                                                controller->expConnected, controller->boardMode == RHSController_7310);
    }
}

// Return name of Pionway board based on model code.
QString BoardIdentifier::opalKellyModelName(int model) const
{
    switch (model) {
    case PW_PRODUCT_XMS6301_LX45:
        return "XMS6301_LX45";
    case PW_PRODUCT_XMS6301_LX75:
        return "XMS6301_LX75";
    case PW_PRODUCT_XMS6301_LX100:
        return "XMS6301_LX100";
    case PW_PRODUCT_XMS6301_LX150:
        return "XMS6301_LX150";
    case PW_PRODUCT_XMS6302_LX45:
        return "XMS6302_LX45";
    case PW_PRODUCT_XMS6302_LX75:
        return "XMS6302_LX75";
    case PW_PRODUCT_XMS6302_LX100:
        return "XMS6302_LX100";
    case PW_PRODUCT_XMS6302_LX150:
        return "XMS6302_LX150";
    default:
        return "UNKNOWN";
    }
}

// Upload bitfile specified by 'filename' to the FPGA, reporting any errors that occur as a QMessageBox.
bool BoardIdentifier::uploadFpgaBitfileQMessageBox(const QString& filename)
{
    CPionway::ErrorCode errorCode = dev->ConfigureFPGA(filename.toStdString());

    switch (errorCode) {
    case CPionway::NO_ERR:
        break;
    case CPionway::DEVICE_NOT_OPEN:
        QMessageBox::critical(parent, "FPGA configuration failed", "Device not open.");
        return false;
    case CPionway::FILE_ERROR:
        QMessageBox::critical(parent, "FPGA configuration failed", "Cannot find configuration file.");
        return false;
    case CPionway::INVALID_BITSTREAM:
        QMessageBox::critical(parent, "FPGA configuration failed", "Bitstream is not properly formatted.");
        return false;
    case CPionway::DONE_NOT_HIGH:
        QMessageBox::critical(parent, "FPGA configuration failed", "FPGA DONE signal did not assert after configuration. Make sure switch on Pionway board is set to 'USB' not 'PROM'.");
        return false;
    case CPionway::TRANSFER_ERROR:
        QMessageBox::critical(parent, "FPGA configuration failed", "USB error occurred during download.");
        return false;
    case CPionway::COMMUNICATION_ERROR:
        QMessageBox::critical(parent, "FPGA configuration failed", "Communication error with firmware.");
        return false;
    case CPionway::UNSUPPORTED_FEATURE:
        QMessageBox::critical(parent, "FPGA configuration failed", "Unsupported feature.");
        return false;
    default:
        QMessageBox::critical(parent, "FPGA configuration failed", "Unknown error.");
        return false;
    }

    // Check for Pionway Pionway support in the FPGA configuration.
    if (dev->IsPionwayEnabled() == false) {
        QMessageBox::critical(parent, "FPGA configuration failed",
                              "Pionway Pionway support is not enabled in this FPGA configuration.");
        return false;
    }

    return true;
}

// Create a dialog window for user to select which board's software to initialize.
BoardSelectDialog::BoardSelectDialog(QWidget *parent) :
    QDialog(parent),
    boardTable(nullptr),
    openButton(nullptr),
    playbackButton(nullptr),
    advancedButton(nullptr),
    useOpenCL(true),
    playbackPorts(255),
    defaultSampleRateCheckBox(nullptr),
    defaultSettingsFileCheckBox(nullptr),
    splash(nullptr),
    boardIdentifier(nullptr),
    dataFileReader(nullptr),
    rhxController(nullptr),
    state(nullptr),
    controllerInterface(nullptr),
    parser(nullptr),
    controlWindow(nullptr)
{
    // Information used by QSettings to save basic settings across sessions.
    QCoreApplication::setOrganizationName(OrganizationName);
    QCoreApplication::setOrganizationDomain(OrganizationDomain);
    QCoreApplication::setApplicationName(ApplicationName);

    // Globally disable unused Context Help buttons from windows/dialogs
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

    // Initialize Board Identifier.
    boardIdentifier = new BoardIdentifier(this);

    // Determine how many and what type of controllers are connected to this machine.
    controllersInfo = boardIdentifier->getConnectedControllersInfo();

    // Create a table containing information about connected controllers.
    boardTable = new QTableWidget(controllersInfo.size(), 3, this);
    populateTable();

    // Allow the user to open the selected board by clicking the open button
    // (can also be done by double-clicking the row in the table).
    openButton = new QPushButton(tr("Open"), this);
    openButton->setEnabled(false);
    connect(openButton, SIGNAL(clicked()), this, SLOT(openSelectedBoard()));

    // Allow the user to open a data file for playback.
    playbackButton = new QPushButton(tr("Data File Playback"), this);
    connect(playbackButton, SIGNAL(clicked()), this, SLOT(playbackDataFile()));

    // Allow the user to open 'Advanced' dialog to allow opting out of OpenCL
    advancedButton = new QPushButton(tr("Advanced"), this);
    connect(advancedButton, SIGNAL(clicked()), this, SLOT(advanced()));
    int advancedButtonSize = advancedButton->sizeHint().width() + 10;
    advancedButton->setFixedWidth(advancedButtonSize);

    defaultSampleRateCheckBox = new QCheckBox(this);
    defaultSettingsFileCheckBox = new QCheckBox(this);

    QHBoxLayout *firstRowLayout = new QHBoxLayout;
    firstRowLayout->addWidget(defaultSettingsFileCheckBox);
    firstRowLayout->addStretch(1);
    firstRowLayout->addWidget(playbackButton);

    QHBoxLayout *secondRowLayout = new QHBoxLayout;
    secondRowLayout->addWidget(defaultSampleRateCheckBox);
    secondRowLayout->addStretch(1);
    secondRowLayout->addWidget(openButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(boardTable);
    mainLayout->addLayout(firstRowLayout);
    mainLayout->addLayout(secondRowLayout);
    mainLayout->addWidget(advancedButton);

    setWindowTitle("Select Intan Controller");

    setLayout(mainLayout);

    resize(minimumSize());

    splash = new QSplashScreen(QPixmap(":images/RHX_splash.png"));
    splashMessage = "Copyright " + CopyrightSymbol + " " + ApplicationCopyrightYear + " Intan Technologies.  RHX version " +
            SoftwareVersion + ".  Opening Intan Controller...";
    splashMessageAlign = Qt::AlignCenter | Qt::AlignBottom;
    splashMessageColor = Qt::white;

    if (!validControllersPresent(controllersInfo)) {
        showDemoMessageBox();
    } else {
        show();
    }

    // Highlight first enabled row.
    for (int row = 0; row < boardTable->rowCount(); row++) {
        // Get this row's text.
        QString thisText = boardTable->itemAt(row, 0)->text();
        // If this type of board is recognized and enabled, give it focus. Otherwise, move to the next row.
        if (thisText == RHDBoardString || thisText == RHS128chString ||
                thisText == RHD512chString || thisText == RHD1024chString ||
                thisText == RHS128ch_7310String || thisText == RHD512ch_7310String ||
                thisText == RHD1024ch_7310String) {
            boardTable->setRangeSelected(QTableWidgetSelectionRange(row, 0, row, 2), true);
            boardTable->setFocus();
            break;
        }
    }
}

BoardSelectDialog::~BoardSelectDialog()
{
    if (boardIdentifier) delete boardIdentifier;
    if (dataFileReader) delete dataFileReader;
    if (controllerInterface) delete controllerInterface;
    if (rhxController) delete rhxController;
    if (parser) delete parser;
//    if (state) delete state;  // This causes "The program has unexpectedly finished" upon quitting for some unknown reason.
}

// Determine whether or not the given QVector of type ControllerInfo contains any valid controllers that can be opened
// by this software (RHD USB interface board, RHD Recording Controller, or RHS Stim/Record Controller).
bool BoardSelectDialog::validControllersPresent(QVector<ControllerInfo*> cInfo)
{
    for (int i = 0; i < cInfo.size(); i++) {
        if (cInfo[i]->boardMode == RHDUSBInterfaceBoard || cInfo[i]->boardMode == RHDController ||
                cInfo[i]->boardMode == RHSController || cInfo[i]->boardMode == RHSController_7310 ||
                cInfo[i]->boardMode == RHDController_7310)
            return true;
    }
    return false;
}

void BoardSelectDialog::showDemoMessageBox()
{
    AmplifierSampleRate sampleRate = SampleRate20000Hz;
    StimStepSize stimStepSize = StimStepSize500nA;
    bool rememberSettings = false;

    DemoSelections demoSelection;
    DemoDialog demoDialog(&demoSelection, useOpenCL, playbackPorts, this);
    demoDialog.exec();

    if (demoSelection == DemoPlayback) {
        playbackDataFile();
    } else {
        ControllerType controllerType;
        if (demoSelection == DemoUSBInterfaceBoard) {
            controllerType = ControllerRecordUSB2;
        } else if (demoSelection == DemoRecordingController) {
            controllerType = ControllerRecordUSB3;
        } else {
            controllerType = ControllerStimRecord;
        }

        StartupDialog startupDialog(controllerType, &sampleRate, &stimStepSize, &rememberSettings, false, false, this);
        startupDialog.exec();

        splash->show();
        splash->showMessage(splashMessage, splashMessageAlign, splashMessageColor);

        startSoftware(controllerType, sampleRate, stimStepSize, (controllerType == ControllerRecordUSB3) ? 8 : 4, true, "N/A",
                      SyntheticMode, false);

        splash->finish(controlWindow);
        this->accept();
    }
}

// Fill the table with information corresponding to all connected Pionway devices.
void BoardSelectDialog::populateTable()
{
    // Set up header.
    boardTable->setHorizontalHeaderLabels(QStringList() << "Intan Controller" << "I/O Expander" << "Serial Number");
    boardTable->horizontalHeader()->setSectionsClickable(false);
    boardTable->verticalHeader()->setSectionsClickable(false);
    boardTable->setFocusPolicy(Qt::ClickFocus);

    // Populate each row with information corresponding to a single controller.
    Qt::ItemFlags itemFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    for (int row = 0; row < controllersInfo.size(); row++) {

        // Report the type of board.
        QString boardType = BoardIdentifier::getBoardTypeString(controllersInfo[row]->boardMode, controllersInfo[row]->numSPIPorts);
        QTableWidgetItem *intanBoardType = new QTableWidgetItem(BoardIdentifier::getIcon(boardType, style(), 100), boardType);
        // If this type is clamp, add a description to the boardType string.
        if (controllersInfo[row]->boardMode == CLAMPController) {
            intanBoardType->setText(intanBoardType->text().append(tr(" (run Clamp software to use)")));
        }
        intanBoardType->setFlags(itemFlags);
        boardTable->setItem(row, 0, intanBoardType);

        // Report if an io expander is connected.
        QTableWidgetItem *ioExpanderStatus = nullptr;
        if (boardType == RHDBoardString || boardType == UnknownUSB2String ||
                boardType == UnknownUSB3String || boardType == UnknownString) {
            ioExpanderStatus = new QTableWidgetItem(tr("N/A"));
        } else {
            QIcon icon((controllersInfo[row]->expConnected) ?
                           style()->standardIcon(QStyle::SP_DialogYesButton).pixmap(20) :
                           style()->standardIcon(QStyle::SP_DialogNoButton).pixmap(20));
            ioExpanderStatus = new QTableWidgetItem(icon, (controllersInfo[row]->expConnected ?
                                                               tr("I/O Expander Connected") :
                                                               tr("No I/O Expander Connected")));
        }
        ioExpanderStatus->setFlags(itemFlags);
        boardTable->setItem(row, 1, ioExpanderStatus);

        // Report the serial number of this board.
        QTableWidgetItem *serialNumber = new QTableWidgetItem(controllersInfo[row]->serialNumber);
        serialNumber->setFlags(itemFlags);
        boardTable->setItem(row, 2, serialNumber);

        // If the type of board is unrecognized, disable the row (greyed-out and unclickable).
        if (!(boardType == RHDBoardString || boardType == RHS128chString ||
              boardType == RHD512chString || boardType == RHD1024chString ||
              boardType == RHS128ch_7310String || boardType == RHD512ch_7310String ||
              boardType == RHD1024ch_7310String)) {
            intanBoardType->setFlags(Qt::NoItemFlags);
            ioExpanderStatus->setFlags(Qt::NoItemFlags);
            serialNumber->setFlags(Qt::NoItemFlags);
        }
    }

    // Make table visible in full (for up to 5 rows... then allow a scroll bar to be used).
    boardTable->setIconSize(QSize(283, 100));
    boardTable->resizeColumnsToContents();
    boardTable->resizeRowsToContents();
    boardTable->setMinimumSize(calculateTableSize());
    boardTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    boardTable->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(boardTable, SIGNAL(cellDoubleClicked(int, int)),
            this, SLOT(startBoard(int)));  // When the user double clicks a row, trigger that board's software.
    connect(boardTable, SIGNAL(currentCellChanged(int, int, int, int)),
            this, SLOT(newRowSelected(int)));  // When the user selects a valid row, enable 'open' button.
}

// Return a QSize (that should be the minimum size of the table) which allows all columns to be visible, and up to 5 rows
// to be visible before a scroll bar is added.
QSize BoardSelectDialog::calculateTableSize()
{
    int width = boardTable->verticalHeader()->width();
    for (int column = 0; column < boardTable->columnCount(); column++) {
        width += boardTable->columnWidth(column);
    }
    width += 4;

    // Make the minimum height to be 5 rows.
    int numRows = 5;
    if (boardTable->rowCount() <= 5)
        numRows = boardTable->rowCount();
    int height = boardTable->horizontalHeader()->height();
    for (int row = 0; row < numRows; row++) {
        height += boardTable->rowHeight(row);
    }
    height += 4;

    return QSize(width, height);
}

void BoardSelectDialog::startSoftware(ControllerType controllerType, AmplifierSampleRate sampleRate, StimStepSize stimStepSize,
                                      int numSPIPorts, bool expanderConnected, const QString& boardSerialNumber, AcquisitionMode mode, bool is7310, DataFileReader* dataFileReader)
{
    if (mode == LiveMode) {
        rhxController = new RHXController(controllerType, sampleRate, is7310);
    } else if (mode == SyntheticMode) {
        rhxController = new SyntheticRHXController(controllerType, sampleRate);
    } else if (mode == PlaybackMode) {
        rhxController = new PlaybackRHXController(controllerType, sampleRate, dataFileReader);
    } else {
        return;
    }

    QSettings settings;
    bool testMode = settings.value("testMode", false).toBool() && mode == LiveMode;

    state = new SystemState(rhxController, stimStepSize, numSPIPorts, expanderConnected, testMode, dataFileReader);
    state->highDPIScaleFactor = this->devicePixelRatio();  // Use this to adjust graphics for high-DPI monitors.
    state->availableScreenResolution = QGuiApplication::primaryScreen()->geometry();
    controllerInterface = new ControllerInterface(state, rhxController, boardSerialNumber, useOpenCL, dataFileReader, this, is7310);
    state->setupGlobalSettingsLoadSave(controllerInterface);
    parser = new CommandParser(state, controllerInterface, this);
    controlWindow = new ControlWindow(state, parser, controllerInterface, rhxController);

    connect(controlWindow, SIGNAL(sendExecuteCommand(QString)), parser, SLOT(executeCommandSlot(QString)));
    connect(controlWindow, SIGNAL(sendExecuteCommandWithParameter(QString,QString)), parser, SLOT(executeCommandWithParameterSlot(QString, QString)));
    connect(controlWindow, SIGNAL(sendGetCommand(QString)), parser, SLOT(getCommandSlot(QString)));
    connect(controlWindow, SIGNAL(sendSetCommand(QString, QString)), parser, SLOT(setCommandSlot(QString, QString)));

    connect(parser, SIGNAL(stimTriggerOn(QString)), controllerInterface, SLOT(manualStimTriggerOn(QString)));
    connect(parser, SIGNAL(stimTriggerOff(QString)), controllerInterface, SLOT(manualStimTriggerOff(QString)));
    connect(parser, SIGNAL(stimTriggerPulse(QString)), controllerInterface, SLOT(manualStimTriggerPulse(QString)));

    connect(parser, SIGNAL(updateGUIFromState()), controlWindow, SLOT(updateFromState()));
    connect(parser, SIGNAL(sendLiveNote(QString)), controllerInterface->saveThread(), SLOT(saveLiveNote(QString)));

    connect(controllerInterface, SIGNAL(TCPErrorMessage(QString)), parser, SLOT(TCPErrorSlot(QString)));

    if (dataFileReader) {
        connect(controlWindow, SIGNAL(setDataFileReaderSpeed(double)), dataFileReader, SLOT(setPlaybackSpeed(double)));
        connect(controlWindow, SIGNAL(setDataFileReaderLive(bool)), dataFileReader, SLOT(setLive(bool)));
        connect(controlWindow, SIGNAL(jumpToEnd()), dataFileReader, SLOT(jumpToEnd()));
        connect(controlWindow, SIGNAL(jumpToStart()), dataFileReader, SLOT(jumpToStart()));
        connect(controlWindow, SIGNAL(jumpToPosition(QString)), dataFileReader, SLOT(jumpToPosition(QString)));
        connect(controlWindow, SIGNAL(jumpRelative(double)), dataFileReader, SLOT(jumpRelative(double)));
        connect(controlWindow, SIGNAL(setStatusBarReadyPlayback()), dataFileReader, SLOT(setStatusBarReady()));
        connect(dataFileReader, SIGNAL(setStatusBar(QString)), controlWindow, SLOT(updateStatusBar(QString)));
        connect(dataFileReader, SIGNAL(setTimeLabel(QString)), controlWindow, SLOT(updateTimeLabel(QString)));
        connect(dataFileReader, SIGNAL(sendSetCommand(QString,QString)), parser, SLOT(setCommandSlot(QString,QString)));
    }

    connect(controllerInterface, SIGNAL(haveStopped()), controlWindow, SLOT(stopAndReportAnyErrors()));
    connect(controllerInterface, SIGNAL(setTimeLabel(QString)), controlWindow, SLOT(updateTimeLabel(QString)));
    connect(controllerInterface, SIGNAL(setTopStatusLabel(QString)), controlWindow, SLOT(updateTopStatusLabel(QString)));
    connect(controllerInterface, SIGNAL(setHardwareFifoStatus(double)), controlWindow, SLOT(updateHardwareFifoStatus(double)));
    connect(controllerInterface, SIGNAL(cpuLoadPercent(double)), controlWindow, SLOT(updateMainCpuLoad(double)));

    connect(controllerInterface->saveThread(), SIGNAL(setStatusBar(QString)), controlWindow, SLOT(updateStatusBar(QString)));
    connect(controllerInterface->saveThread(), SIGNAL(setTimeLabel(QString)), controlWindow, SLOT(updateTimeLabel(QString)));
    connect(controllerInterface->saveThread(), SIGNAL(sendSetCommand(QString, QString)),
            parser, SLOT(setCommandSlot(QString, QString)));
    connect(controllerInterface->saveThread(), SIGNAL(error(QString)), controlWindow, SLOT(queueErrorMessage(QString)));

    controlWindow->show();

    settings.beginGroup(ControllerTypeSettingsGroup[(int)state->getControllerTypeEnum()]);
    if (defaultSettingsFileCheckBox->isChecked()) {
        settings.setValue("loadDefaultSettingsFile", true);
        QString defaultSettingsFile = QString(settings.value("defaultSettingsFile", "").toString());
        if (controlWindow->loadSettingsFile(defaultSettingsFile)) {
            emit controlWindow->setStatusBar("Loaded default settings file " + defaultSettingsFile);
        } else {
            emit controlWindow->setStatusBar("Error loading default settings file " + defaultSettingsFile);
        }
    } else {
        settings.setValue("loadDefaultSettingsFile", false);
    }
    settings.endGroup();

    if (state->testMode->getValue()) {
        state->plottingMode->setValue("Original");
    }
}

// Trigger the currently selected board's software.
void BoardSelectDialog::openSelectedBoard()
{
    QTableWidgetItem *selectedItem = boardTable->selectedItems().first();
    startBoard(selectedItem->row());
}

// Enable the 'Open' button when a valid controller's row is selected.
void BoardSelectDialog::newRowSelected(int row)
{
    openButton->setEnabled(true);

    ControllerType controllerType = ControllerRecordUSB3;
    if (boardTable->item(row, 0)->text() == RHDBoardString) controllerType = ControllerRecordUSB2;
    if (boardTable->item(row, 0)->text() == RHS128chString || boardTable->item(row, 0)->text() == RHS128ch_7310String) controllerType = ControllerStimRecord;

    QSettings settings;
    settings.beginGroup(ControllerTypeSettingsGroup[(int)controllerType]);
    bool useDefaultSettings = settings.value("useDefaultSettings", false).toBool();
    bool loadDefaultSettingsFile = settings.value("loadDefaultSettingsFile", false).toBool();

    if (useDefaultSettings) {
        defaultSampleRateCheckBox->setChecked(true);
        defaultSampleRateCheckBox->setVisible(true);
        int defaultSampleRateIndex = settings.value("defaultSampleRate", 14).toInt();
        int defaultStimStepSizeIndex = settings.value("defaultStimStepSize", 6).toInt();
        if (controllerType == ControllerStimRecord) {
            defaultSampleRateCheckBox->setText(tr("Start software with ") + SampleRateString[defaultSampleRateIndex] +
                                               tr(" sample rate and ") +
                                               StimStepSizeString[defaultStimStepSizeIndex]);
        } else {
            defaultSampleRateCheckBox->setText(tr("Start software with ") + SampleRateString[defaultSampleRateIndex] +
                                               tr(" sample rate"));
        }
    } else {
        defaultSampleRateCheckBox->setChecked(false);
        defaultSampleRateCheckBox->setVisible(false);
    }

    if (loadDefaultSettingsFile) {
        defaultSettingsFileCheckBox->setChecked(true);
        defaultSettingsFileCheckBox->setVisible(true);
        QString defaultSettingsFile = QString(settings.value("defaultSettingsFile", "").toString());
        defaultSettingsFileCheckBox->setText(tr("Load default settings file: ") + defaultSettingsFile);
    } else {
        defaultSettingsFileCheckBox->setChecked(false);
        defaultSettingsFileCheckBox->setVisible(false);
    }

    settings.endGroup();
}

// Trigger the given row's board's software.
void BoardSelectDialog::startBoard(int row)
{
    openButton->setEnabled(false);
    playbackButton->setEnabled(false);
    boardTable->setEnabled(false);

    AmplifierSampleRate sampleRate = SampleRate20000Hz;
    StimStepSize stimStepSize = StimStepSize500nA;
    bool rememberSettings = false;

    ControllerType controllerType = ControllerRecordUSB3;
    if (boardTable->item(row, 0)->text() == RHDBoardString) controllerType = ControllerRecordUSB2;
    if (boardTable->item(row, 0)->text() == RHS128chString || boardTable->item(row, 0)->text() == RHS128ch_7310String) controllerType = ControllerStimRecord;

    QSettings settings;
    bool testMode = settings.value("testMode", false).toBool();
    settings.beginGroup(ControllerTypeSettingsGroup[(int)controllerType]);
    if (defaultSampleRateCheckBox->isChecked()) {
        sampleRate = (AmplifierSampleRate) settings.value("defaultSampleRate", 14).toInt();
        stimStepSize = (StimStepSize) settings.value("defaultStimStepSize", 6).toInt();
    } else {
        StartupDialog *startupDialog = new StartupDialog(controllerType, &sampleRate, &stimStepSize, &rememberSettings, true, testMode, this);
        startupDialog->exec();

        if (rememberSettings) {
            settings.setValue("useDefaultSettings", true);
            settings.setValue("defaultSampleRate", (int) sampleRate);
            settings.setValue("defaultStimStepSize", (int) stimStepSize);
        } else {
            settings.setValue("useDefaultSettings", false);
        }
    }
    settings.endGroup();

    splash->show();
    splash->showMessage(splashMessage, splashMessageAlign, splashMessageColor);

    startSoftware(controllerType, sampleRate, stimStepSize, controllersInfo.at(row)->numSPIPorts,
                  controllersInfo.at(row)->expConnected, boardTable->item(row, 2)->text(), LiveMode, controllersInfo.at(row)->usbVersion == USB3_7310);

    splash->finish(controlWindow);
    this->accept();
}

// Allow user to load an Intan data file for playback.
void BoardSelectDialog::playbackDataFile()
{
    QSettings settings;
    QString defaultDirectory = settings.value("playbackDirectory", ".").toString();
    QString playbackFileName;
    playbackFileName = QFileDialog::getOpenFileName(this, tr("Select Intan Data File"), defaultDirectory, tr("Intan Data Files (*.rhd *.rhs)"));

    if (playbackFileName.isEmpty()) {
        exit(EXIT_FAILURE);
    }

    bool canReadFile = false;
    QString report;
    dataFileReader = new DataFileReader(playbackFileName, canReadFile, report, playbackPorts);
    if (!canReadFile) {
        ScrollableMessageBoxDialog msgBox(this, "Unable to Load Data File", report);
        msgBox.exec();
        delete dataFileReader;
        dataFileReader = nullptr;
        exit(EXIT_FAILURE);
    } else if (!report.isEmpty()) {
        ScrollableMessageBoxDialog msgBox(this, "Data File Loaded", report);
        msgBox.exec();
        QFileInfo fileInfo(playbackFileName);
        settings.setValue("playbackDirectory", fileInfo.absolutePath());
    }

    splash->show();
    splash->showMessage(splashMessage, splashMessageAlign, splashMessageColor);

    startSoftware(dataFileReader->controllerType(), dataFileReader->sampleRate(), dataFileReader->stimStepSize(),
                  dataFileReader->numSPIPorts(), dataFileReader->expanderConnected(), "N/A", PlaybackMode, false, dataFileReader);

    splash->finish(controlWindow);
    this->accept();
}

void BoardSelectDialog::advanced()
{
    AdvancedStartupDialog advancedStartupDialog(useOpenCL, playbackPorts, false, this);
    advancedStartupDialog.exec();
}
