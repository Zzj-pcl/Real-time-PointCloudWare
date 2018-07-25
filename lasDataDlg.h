#ifndef LASDATADLG_H
#define LASDATADLG_H

#include <QDialog>
#include "ui_lasDataDlg.h"

//system
#include <string.h>
#include <vector>

class lasDataDlg : public QDialog, public Ui::lasDataDlg
{
	Q_OBJECT

public:
	lasDataDlg(QWidget *parent = 0);
	~lasDataDlg();


};

#endif // LASDATADLG_H
