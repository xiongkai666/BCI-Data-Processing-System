
#ifndef FILTERDISPLAYSELECTOR_H
#define FILTERDISPLAYSELECTOR_H

#include <QtWidgets>
#include <vector>
#include "systemstate.h"

using namespace std;

class FilterDisplaySelector : public QWidget
{
    Q_OBJECT
public:
    explicit FilterDisplaySelector(SystemState* state_, QWidget* parent = nullptr);

public slots:
    void updateFromState();

private slots:
    void enableOrder1(int checked);
    void enableOrder2(int checked);
    void enableOrder3(int checked);
    void enableOrder4(int checked);
    void filterOrderChanged();
    void arrangeByChanged(int index);
    void displayLabelTextChanged(int index);
    void changeLabelWidth(int index);
    void showDisabledChannels(int checked);

private:
    void boldSelectedFilters();

    SystemState* state;
    bool stimController;
    vector<QLabel*> filterLabels;

    QRadioButton* wide1Button;
    QRadioButton* wide2Button;
    QRadioButton* wide3Button;
    QRadioButton* wide4Button;

    QRadioButton* low1Button;
    QRadioButton* low2Button;
    QRadioButton* low3Button;
    QRadioButton* low4Button;

    QRadioButton* high1Button;
    QRadioButton* high2Button;
    QRadioButton* high3Button;
    QRadioButton* high4Button;

    QRadioButton* spike1Button;
    QRadioButton* spike2Button;
    QRadioButton* spike3Button;
    QRadioButton* spike4Button;

    QRadioButton* dc1Button;
    QRadioButton* dc2Button;
    QRadioButton* dc3Button;
    QRadioButton* dc4Button;

    QComboBox* arrangeByComboBox;
    QComboBox* labelTextComboBox;
    QComboBox* labelWidthComboBox;

    QButtonGroup* order1ButtonGroup;
    QButtonGroup* order2ButtonGroup;
    QButtonGroup* order3ButtonGroup;
    QButtonGroup* order4ButtonGroup;

    QCheckBox* order1CheckBox;
    QCheckBox* order2CheckBox;
    QCheckBox* order3CheckBox;
    QCheckBox* order4CheckBox;
    QCheckBox* clipWaveformsCheckBox;
    QCheckBox* showDisabledCheckBox;

    vector<QString> filterText;
};

#endif // FILTERDISPLAYSELECTOR_H
