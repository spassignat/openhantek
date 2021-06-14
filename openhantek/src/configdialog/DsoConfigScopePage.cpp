// SPDX-License-Identifier: GPL-2.0+

#include "DsoConfigScopePage.h"
#include <QLineEdit>

DsoConfigScopePage::DsoConfigScopePage(DsoSettings *settings, QWidget *parent) : QWidget(parent), settings(settings) {
    // Initialize lists for comboboxes
    QStringList interpolationStrings;
    interpolationStrings << tr("Off") << tr("Linear");

    // Initialize elements
    interpolationLabel = new QLabel(tr("Interpolation"));
    interpolationComboBox = new QComboBox();
    interpolationComboBox->addItems(interpolationStrings);
    interpolationComboBox->setCurrentIndex(settings->view.interpolation);
    digitalPhosphorDepthLabel = new QLabel(tr("Digital phosphor depth"));
    digitalPhosphorDepthSpinBox = new QSpinBox();
    digitalPhosphorDepthSpinBox->setMinimum(2);
    digitalPhosphorDepthSpinBox->setMaximum(99);
    digitalPhosphorDepthSpinBox->setValue(settings->view.digitalPhosphorDepth);

    graphLayout = new QGridLayout();
    graphLayout->addWidget(interpolationLabel, 1, 0);
    graphLayout->addWidget(interpolationComboBox, 1, 1);
    graphLayout->addWidget(digitalPhosphorDepthLabel, 2, 0);
    graphLayout->addWidget(digitalPhosphorDepthSpinBox, 2, 1);

    graphGroup = new QGroupBox(tr("Graph"));
    graphGroup->setLayout(graphLayout);

	linesLabel	= new QLabel(tr("Line Width"));
    lineEdit=new QLineEdit(this);
    lineEdit->setText(settings->view.lineWidth );

	gridAsLineLabel	= new QLabel(tr("Display grid as Line"));
	gridAsLineCheckBox=new QCheckBox(this);
	gridAsLineCheckBox->setCheckState( settings->view.gridAsLine?Qt::CheckState::Checked:Qt::CheckState::Unchecked );

    cursorsLabel = new QLabel(tr("Position"));
    cursorsComboBox = new QComboBox();
    cursorsComboBox->addItem("Left", Qt::LeftToolBarArea);
    cursorsComboBox->addItem("Right", Qt::RightToolBarArea);
    cursorsComboBox->setCurrentIndex(settings->view.cursorGridPosition == Qt::LeftToolBarArea ? 0 : 1);

    cursorsLayout = new QGridLayout();
    cursorsLayout->addWidget(cursorsLabel, 0, 0);
    cursorsLayout->addWidget(cursorsComboBox, 0, 1);
cursorsLayout->addWidget(linesLabel, 1, 0);
    cursorsLayout->addWidget(lineEdit, 1, 1);
cursorsLayout->addWidget(gridAsLineLabel, 2, 0);
    cursorsLayout->addWidget(gridAsLineCheckBox, 2, 1);

    cursorsGroup = new QGroupBox(tr("Cursors"));
    cursorsGroup->setLayout(cursorsLayout);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(graphGroup);
    mainLayout->addWidget(cursorsGroup);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

/// \brief Saves the new settings.
void DsoConfigScopePage::saveSettings() {
    settings->view.interpolation = (Dso::InterpolationMode)interpolationComboBox->currentIndex();
    settings->view.digitalPhosphorDepth = digitalPhosphorDepthSpinBox->value();
    settings->view.cursorGridPosition = (Qt::ToolBarArea)cursorsComboBox->currentData().toUInt();
    settings->view.lineWidth = lineEdit->text();
    settings->view.gridAsLine = gridAsLineCheckBox->isChecked();
}
