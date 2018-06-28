#include "stdafx.h"
#include "DrawingArea.h"
#include "ControlPointList.h"

QColor black = QColor(0, 0, 0);
QColor white = QColor(255, 255, 255);

DrawingArea::~DrawingArea()
{
}

DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
	canvasMinY = canvasMinX = 0;
	canvasMaxX = canvasMaxY = 300;

	mouseX = mouseY = 0;

	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(false);
	setMouseTracking(true);
}

QSize DrawingArea::sizeHint() const
{
	return QSize(canvasMaxX, canvasMaxY);
}

QSize DrawingArea::minimumSizeHint() const
{
	return QSize(canvasMaxX, canvasMaxY);
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event) {
	mouseX = event->pos().x();
	mouseY = event->pos().y();
	emit mousePositionChanged(mousePosition());
}

void DrawingArea::mousePressEvent(QMouseEvent *event) {
	switch (event->button()) {
	case 1: //lmb
		controlPointList.push_back(toControlPoint(event->pos()));
		break;
	case 2: //rmb
		if (controlPointList.size() >= 1) {
			controlPointList.pop_back();
		}
		break;
	}

	update();
	emit controlPointListChanged(controlPointList);
}

QString DrawingArea::mousePosition()
{
	return		QString(("(" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + ")").c_str());
}

void DrawingArea::controlPointListUpdated(std::vector<ControlPoint> points)
{
	controlPointList = points;
	update();
}

void DrawingArea::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.setWindow(canvasMinX, canvasMinY, canvasMaxX, canvasMaxY);
	painter.setViewport(canvasMinX, canvasMinY, canvasMaxX, canvasMaxY);

	//drawBackgroundBox(painter);
	drawPath(painter, toQPoints(controlPointList));
}

void DrawingArea::drawPath(QPainter &painter, std::vector<QPoint> points)
{
	QPainterPath path;

	if (points.size() >= 4) {
		path.moveTo(points.at(0));
		for (int i = 1; i < points.size() && points.size() - i >= 3; i += 3) {
			path.cubicTo(points.at(i), points.at(i + 1), points.at(i + 2));
			//qDebug() << i << " " << points.at(i) << " " << points.at(i + 1) << " " << points.at(i + 2);
		}
	}

	painter.setRenderHint(QPainter::Antialiasing, true);

	QPen pen = Qt::SolidLine;
	pen.setWidth(3);
	painter.setPen(pen);
	painter.setBrush(Qt::BrushStyle::NoBrush);
	painter.drawPath(path);
}

void DrawingArea::drawBackgroundBox(QPainter &painter)
{
	QRect background = QRect(canvasMinX, canvasMinY, canvasMaxX, canvasMaxY);
	painter.setPen(black);
	painter.setBrush(white);
	painter.drawRect(background);
}
