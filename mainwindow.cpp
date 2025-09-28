#include "mainwindow.h"
#include "clockwidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	setWindowTitle("Clock");
	setFixedSize(500,500);
	QWidget* clock = new ClockWidget(this);
	setCentralWidget(clock);
}

MainWindow::~MainWindow()
{}
