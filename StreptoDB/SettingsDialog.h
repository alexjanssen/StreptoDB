#pragma once

#include <QtWidgets/qdialog.h>
#include "ui_StreptoGUI.h"
#include <QtWidgets\QLabel>
#include <ui_SettingsDialog.h>

class settingsDialog : public QDialog, public Ui::StreptoGUIClass
{
	Q_OBJECT

public:
	settingsDialog(QDialog* parent = 0);
	Ui::settingsDialog ui;


public slots:
	void selectPath();
	void saveSettings();

};
