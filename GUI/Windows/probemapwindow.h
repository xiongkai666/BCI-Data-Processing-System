
#ifndef PROBEMAPWINDOW_H
#define PROBEMAPWINDOW_H

#include <QtWidgets>

#include "rhxglobals.h"
#include "impedancegradient.h"
#include "pageview.h"
#include "systemstate.h"
#include "xmlinterface.h"
#include "controllerinterface.h"

typedef map<string, double> ChannelList;

class ProbeMapWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ProbeMapWindow(SystemState* state_, ControllerInterface* controllerInterface_, QMainWindow *parent = nullptr);
    ~ProbeMapWindow();

    QSize sizeHint() const override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void updateForRun();
    void updateForLoad();
    void updateForStop();

    QVector<ElectrodeSite*> getSitesWithName(const QString& nativeName); // Return references to all sites with the given nativeName

signals:
    // The mouse's role has been changed to a new MouseMode
    void modeChanged(MouseMode mode);

public slots:
    void updateFromState();
    void updateMouseStatus(float x, float y, bool mousePresent, QString hoveredSiteName);

    void enableChannel(QString nativeName, bool enabled);
    void changeChannelColor(QString nativeName, QString color);
    void changeChannelImpedance(QString nativeName, float impedanceMag, float impedancePhase);
    void linkAndUpdateSites();

private slots:
    void load();
    void pageChanged(int index);
    void mouseLeft();
    void changeMode();
    void endOfResize();
    void highlightSiteFromMap(QString nativeName, bool highlighted);
    void deselectAllSitesFromMap();
    void toggleView();
    void catchSpikeReport(QString names);
    void catchSpikeTimerTick();
    void changeSpikeDecay();

private:
    SystemState* state;
    ControllerInterface* controllerInterface;

    ChannelList activeChannels;
    QElapsedTimer spikeTimer;

    XMLInterface *probeMapSettingsInterface;

    QMenu *fileMenu;

    QToolBar *toolBar;
    QAction *loadAction;
    QActionGroup *mouseActions;

    QAction *bestFitAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;

    QAction *selectAction;
    QAction *scrollAction;
    QAction *resizeAction;

    QAction *scrollUpAction;
    QAction *scrollDownAction;
    QAction *scrollLeftAction;
    QAction *scrollRightAction;

    QAction *defaultViewAction;
    QAction *impedanceViewAction;
    QAction *spikeViewAction;

    QActionGroup *viewActions;

    QTabWidget *pageTabWidget;
    QLabel *statusCoords;
    QLabel *statusSiteInfo;

    ImpedanceGradient *impedanceGradient;
    SpikeGradient *spikeGradient;

    QLabel *spikeDecayLabel;
    QComboBox *spikeDecayComboBox;

    int currentPage;

    void populateTabWidget(); // Create new PageViews and populate the tab widget with them
    void clearTabWidget(); // Delete PageViews and clear the tab widget

    void enableActions(bool enable);

    void updateSpikeTimerSites();

    map<int, double> decayOptions;
};

#endif // PROBEMAPWINDOW_H
