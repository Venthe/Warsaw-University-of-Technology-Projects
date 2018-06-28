#pragma once

#include <QWidget>

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

	std::string mousePosition();

private:
	int canvasMinX, canvasMinY, canvasMaxX, canvasMaxY;
	void drawBackgroundBox(QPainter &painter);
	void DrawingArea::drawPath(QPainter &painter, std::vector<QPoint> points);
	int mouseX, mouseY;
};
