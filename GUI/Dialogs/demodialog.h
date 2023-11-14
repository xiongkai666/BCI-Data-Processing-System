
#ifndef DEMODIALOG_H
#define DEMODIALOG_H

#include <QDialog>
#include <QtWidgets>

#include "rhxglobals.h"


class DemoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DemoDialog(DemoSelections *demoSelection_, bool &useOpenCL_, uint8_t &playbackPorts_, QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *) override;

private:
    DemoSelections *demoSelection;

    bool *useOpenCL;
    uint8_t *playbackPorts;
    QLabel *message;
    QPushButton *usbInterfaceButton;
    QPushButton *recordControllerButton;
    QPushButton *stimControllerButton;
    QPushButton *playbackButton;
    QPushButton *advancedButton;

private slots:
    void usbInterface();
    void recordController();
    void stimController();
    void playback();
    void advanced();
};

#endif // DEMODIALOG_H
