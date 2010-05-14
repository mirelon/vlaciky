#include "metro.h"
#include "ui_metro.h"
#include<QDebug>
#include<QShortcut>

Metro::Metro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Metro)
{
    ui->setupUi(this);

	s = new Settings();
	s->load();
	int n = s->getString("map").length();
	qDebug() << "n=" << n;

	graphics = new Graphics();
	graphics->graphicsView = ui->graphicsView;
	graphics->n = n;
	graphics->s = s;
	graphics->init();

	simulation = new Simulation();
	simulation->s = s;
	simulation->graphics = graphics;
	simulation->init();

	QShortcut* esc = new QShortcut( Qt::Key_Escape, this );
	connect(esc,SIGNAL(activated()),this,SLOT(close()));

	setMouseTracking(true);
}

Metro::~Metro()
{
	delete graphics;
	delete simulation;
	delete s;
    delete ui;
}

void Metro::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Metro::mouseMoveEvent(QMouseEvent *e){
	qDebug() << "move";
}

void Metro::on_actionStart_triggered()
{
	simulation->start();
}

void Metro::on_actionStop_triggered()
{
	simulation->stopped=true;
}
