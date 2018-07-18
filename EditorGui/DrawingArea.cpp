#include "stdafx.h"
#include "DrawingArea.h"

std::vector<QPoint> to_qpoints(std::vector<esl::ControlPoint> list);
QPoint to_qpoint(esl::ControlPoint point);
esl::ControlPoint to_control_point(QPoint point, double weight = 0.0);

QColor black = QColor(0, 0, 0);
QColor white = QColor(255, 255, 255);

DrawingArea::~DrawingArea() = default;

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
	return { canvasMaxX, canvasMaxY };
}

QSize DrawingArea::minimumSizeHint() const
{
	return { canvasMaxX, canvasMaxY };
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event) {
	mouseX = event->pos().x();
	mouseY = event->pos().y();
	emit mousePositionChanged(mousePosition());
}

void DrawingArea::mousePressEvent(QMouseEvent *event) {
	switch (event->button()) {
	case 1: //lmb
		controlPointList.push_back(to_control_point(event->pos()));
		break;
	case 2: //rmb
		if (!controlPointList.empty()) {
			controlPointList.pop_back();
		}
		break;
	default:
		return;
	}

	update();
	emit controlPointListChanged(controlPointList);
}

QString DrawingArea::mousePosition()
{
	return { ("(" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + ")").c_str() };
}

void DrawingArea::controlPointListUpdated(std::vector<esl::ControlPoint> points)
{
	controlPointList = points;
	update();
}

void DrawingArea::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.setWindow(canvasMinX, canvasMinY, canvasMaxX, canvasMaxY);
	painter.setViewport(canvasMinX, canvasMinY, canvasMaxX, canvasMaxY);

	//drawBackgroundBox(painter);
	drawPath(painter, to_qpoints(controlPointList));
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

std::vector<QPoint> to_qpoints(std::vector<esl::ControlPoint> list) {
	std::vector<QPoint> result;

	for (auto controlPoint : list) {
		result.push_back(to_qpoint(controlPoint));
	}

	return result;
}

QPoint to_qpoint(esl::ControlPoint point) {
	return { point.get_x(), point.get_y() };
}

esl::ControlPoint to_control_point(QPoint point, double weight) {
	return { point.x(), point.y(), weight };
}

