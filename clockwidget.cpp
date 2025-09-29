#include "clockwidget.h"

ClockWidget::ClockWidget(QWidget* parent) : QWidget(parent)
{
	m_time = QDateTime::currentDateTime();
	QTimer* timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer->start(500);
}

ClockWidget::~ClockWidget()
{}

void ClockWidget::tick()
{
	m_time = QDateTime::currentDateTime();
	update();
}

void ClockWidget::drawHands(QPainter& painter, QRect& rect)
{
	int hour, second, minute;
	hour = m_time.time().hour();
	minute = m_time.time().minute();
	second = m_time.time().second();

	float x = qSin((M_PI*2)/43200 * ((hour*3600) + (minute*60) + second));
	float y = -qCos((M_PI*2)/43200 * ((hour*3600) + (minute*60) + second));

	// hour hand
	painter.drawLine(0,0,
				  x*rect.width()/4,
				  y*rect.height()/4);
	
	x = qSin((M_PI*2)/3600 * (minute*60+second));
	y = -qCos((M_PI*2)/3600 * (minute*60+second));

	// minute hand
	painter.drawLine(0,0,
				  x*rect.width()/3,
				  y*rect.height()/3);

}

void ClockWidget::drawSecondHand(QPainter& painter, QRect& rect)
{
	painter.save();
	QPen pen(Qt::red);
	pen.setWidth(2);
	painter.setPen(pen);
	int second = m_time.time().second();
	float x = qSin((M_PI*2)/60*second);
	float y = -qCos((M_PI*2)/60*second);
	painter.drawLine(0,0,
				  x*(rect.width()/2-20),
				  y*(rect.height()/2-20));
	painter.restore();
}

void ClockWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPen pen(Qt::GlobalColor::white);
	pen.setWidth(4);
	painter.setPen(pen);

	// draw frame
	QRect widget_rect = this->rect().adjusted(2, 2, -2, -2);
	painter.drawEllipse(widget_rect);

	// draw face
	painter.setViewport(widget_rect.width()/2,widget_rect.height()/2, widget_rect.width(), widget_rect.height());
	for(int i=0;i < 12;i++)
	{
		float x = qSin((M_PI*2)/12*i);
		float y = -qCos((M_PI*2)/12*i);

		painter.drawLine(x*(widget_rect.width()/2-20), y*(widget_rect.height()/2-20), 
				   x*widget_rect.width()/2, y*widget_rect.height()/2);
	}

	// draw secondary ticks
	pen.setWidth(2);
	painter.save();
	painter.setPen(pen);
	for(int i=0;i < 60;i++)
	{
		if(i%5 == 0)
			continue;

		float x = qSin((M_PI*2)/60*i);
		float y = -qCos((M_PI*2)/60*i);

		painter.drawLine(x*(widget_rect.width()/2-10), y*(widget_rect.height()/2-10), 
				   x*widget_rect.width()/2, y*widget_rect.height()/2);
	}
	painter.restore();

	// draw hands
	drawHands(painter, widget_rect);
	// draw second hand
	drawSecondHand(painter, widget_rect);
}

