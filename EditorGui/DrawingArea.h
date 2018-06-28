#pragma once

#include <QWidget>

#include "ControlPointList.h"

class DrawingArea : public QWidget
{
	Q_OBJECT

public:
	DrawingArea(QWidget *parent = Q_NULLPTR);
	~DrawingArea();

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

	void DrawingArea::paintEvent(QPaintEvent *event);
	void DrawingArea::mouseMoveEvent(QMouseEvent *event);
	void DrawingArea::mousePressEvent(QMouseEvent *event);

	QString mousePosition();
signals:
	void mousePositionChanged(QString position);
	void controlPointListChanged(std::vector<ControlPoint> points);

public slots:
	void controlPointListUpdated(std::vector<ControlPoint> points);

private:
	int canvasMinX, canvasMinY, canvasMaxX, canvasMaxY;
	void drawBackgroundBox(QPainter &painter);
	void DrawingArea::drawPath(QPainter &painter, std::vector<QPoint> points);
	int mouseX, mouseY;
	std::vector<ControlPoint> controlPointList;
};
