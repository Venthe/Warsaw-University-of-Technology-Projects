#include "stdafx.h"
#include "DrawingArea.h"

QColor black = QColor(0, 0, 0);
QColor white = QColor(255, 255, 255);

DrawingArea::~DrawingArea() = default;

DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
	canvasMinY = canvasMinX = 0;
	canvasMaxX = canvasMaxY = 300;

	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(false);
	setMouseTracking(true);
}

QSize DrawingArea::sizeHint() const
{
	return { canvasMaxX, canvasMaxY };
}

QSize DrawingArea::minimumSizeHint() const
{
	return { canvasMaxX, canvasMaxY };
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event) {
	emit mousePositionChanged(event->pos());
}

void DrawingArea::mousePressEvent(QMouseEvent *event) {
	// TODO: Move to service?
	// TODO: Introduce enums
	switch (event->button()) {
	case 1: //lmb
		controlPointList->push_back(toControlPoint(event->pos()));
		break;
	case 2: //rmb
		if (!controlPointList->empty()) {
			controlPointList->pop_back();
		}
		break;
	default:
		return;
	}

	emit controlPointListChanged();
}

void DrawingArea::controlPointListUpdated()
{
	update();
}

void DrawingArea::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.setWindow(canvasMinX, canvasMinY, canvasMaxX, canvasMaxY);
	painter.setViewport(canvasMinX, canvasMinY, canvasMaxX, canvasMaxY);

	drawPath(painter, toQPoints(*controlPointList));
}

void DrawingArea::drawPath(QPainter &painter, std::vector<QPoint> points)
{
	QPainterPath path;

	// TODO: Clean code
	if (points.size() >= 4) {
		path.moveTo(points.at(0));
		for (int i = 1; i < points.size() && points.size() - i >= 3; i += 3) {
			path.cubicTo(points.at(i), points.at(i + 1), points.at(i + 2));
		}
	}

	painter.setRenderHint(QPainter::Antialiasing, true);
	
	// TODO: SetPenWidth in relation to current weight? Ignore weight of control points?
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

std::vector<QPoint> DrawingArea::toQPoints(std::vector<esl::ControlPoint> list) {
	std::vector<QPoint> result;

	for (auto controlPoint : list) {
		result.push_back(toQPoint(controlPoint));
	}

	return result;
}

QPoint DrawingArea::toQPoint(esl::ControlPoint point) {
	return { point.getX(), point.getY() };
}

esl::ControlPoint DrawingArea::toControlPoint(QPoint point) {
	return { static_cast<long>(point.x()), static_cast<long>(point.y()), *controlPointWeight };
}

