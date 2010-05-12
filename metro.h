#ifndef METRO_H
#define METRO_H

#include <QMainWindow>
#include "graphics.h"
#include "simulation.h"
#include "settings.h"

namespace Ui {
    class Metro;
}

class Metro : public QMainWindow {
    Q_OBJECT
public:
    Metro(QWidget *parent = 0);
    ~Metro();

protected:
    void changeEvent(QEvent *e);
	void mouseMoveEvent(QMouseEvent *e);

private:
    Ui::Metro *ui;
	Graphics* graphics;
	Simulation* simulation;
	Settings* s;

private slots:
	void on_actionStop_triggered();
	void on_actionStart_triggered();
};

#endif // METRO_H
