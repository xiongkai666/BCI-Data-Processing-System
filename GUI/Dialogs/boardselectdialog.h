
#ifndef BOARDSELECTDIALOG_H
#define BOARDSELECTDIALOG_H

#include <QDialog>

#include "demodialog.h"
#include "startupdialog.h"
#include "rhxcontroller.h"
#include "syntheticrhxcontroller.h"
#include "playbackrhxcontroller.h"
#include "rhxglobals.h"
#include "controlwindow.h"
#include "controllerinterface.h"
#include "systemstate.h"
#include "commandparser.h"

const QString RHDBoardString = "RHD USB Interface Board";
const QString RHD512chString = "RHD 512ch Recording Controller";
const QString RHD1024chString = "RHD 1024ch Recording Controller";
const QString RHS128chString = "RHS 128ch Stim/Recording Controller";
const QString CLAMP2chString = "2ch CLAMP Controller";
const QString CLAMP8chString = "8ch CLAMP Controller";
const QString UnknownUSB2String = "Unknown USB2 Device";
const QString UnknownUSB3String = "Unknown USB3 Device";
const QString UnknownString = "Unknown Device";
const QString RHS128ch_7310String = "RHS 128ch Stim/Recording Controller (7310)";
const QString RHD512ch_7310String = "RHD 512ch Recording Controller (7310)";
const QString RHD1024ch_7310String = "RHD 1024ch Recording Controller (7310)";

enum UsbVersion {
    USB2,
    USB3,
    USB3_7310
};

struct ControllerInfo {
    QString serialNumber;
    UsbVersion usbVersion;
    bool expConnected;
    int numSPIPorts;
    BoardMode boardMode;
};

class BoardIdentifier
{
public:
    BoardIdentifier(QWidget* parent_);
    ~BoardIdentifier();

    static QString getBoardTypeString(BoardMode mode, int numSpiPorts);
    static QIcon getIcon(const QString& boardType, QStyle *style, int size);

    QVector<ControllerInfo*> getConnectedControllersInfo();

private:
    void identifyController(ControllerInfo* controller, int index);
    QString opalKellyModelName(int model) const;
    bool uploadFpgaBitfileQMessageBox(const QString& filename);

    QVector<ControllerInfo*> controllers;
    QWidget *parent;

    CPionway *dev;
};

class QPushButton;
class QTableWidget;

class BoardSelectDialog : public QDialog
{
    Q_OBJECT
public:
    BoardSelectDialog(QWidget *parent = nullptr);
    ~BoardSelectDialog();

    static bool validControllersPresent(QVector<ControllerInfo*> cInfo);

private slots:
    void openSelectedBoard();
    void newRowSelected(int row);
    void startBoard(int row);
    void playbackDataFile();
    void advanced();

private:
    void populateTable();
    QSize calculateTableSize();

    void showDemoMessageBox();
    void startSoftware(ControllerType controllerType, AmplifierSampleRate sampleRate, StimStepSize stimStepSize,
                       int numSPIPorts, bool expanderConnected, const QString& boardSerialNumber, AcquisitionMode mode, bool is7310, DataFileReader* dataFileReader=nullptr);

    QTableWidget *boardTable;
    QPushButton *openButton;
    QPushButton *playbackButton;
    QPushButton *advancedButton;

    QCheckBox *defaultSampleRateCheckBox;
    QCheckBox *defaultSettingsFileCheckBox;

    QSplashScreen* splash;
    QString splashMessage;
    int splashMessageAlign;
    QColor splashMessageColor;

    BoardIdentifier *boardIdentifier;
    QVector<ControllerInfo*> controllersInfo;
    DataFileReader *dataFileReader;

    AbstractRHXController *rhxController;
    SystemState *state;
    ControllerInterface *controllerInterface;
    CommandParser *parser;
    ControlWindow *controlWindow;

    bool useOpenCL;
    uint8_t playbackPorts;
};

#endif // BOARDSELECTDIALOG_H
