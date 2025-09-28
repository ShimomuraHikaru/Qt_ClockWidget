#ifndef _CLOCKWIDGET_H
#define _CLOCKWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QPainter>
#include <QPen>
#include <QtMath>
#include <QTimer>

class ClockWidget : public QWidget
{
	Q_OBJECT
public:
	ClockWidget(QWidget* parent = 0);
	~ClockWidget();
public slots:
	void tick();
protected:
	void paintEvent(QPaintEvent *event) override;
	void drawHands(QPainter& painter, QRect& rect);
	void drawSecondHand(QPainter& painter, QRect& rect);

	QDateTime m_time;
};

#endif
