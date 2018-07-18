#pragma once

#include <QWidget> // NOLINT
#include "ControlPoint.h"

class DrawingArea : public QWidget
{
	Q_OBJECT

public:
	DrawingArea(QWidget *parent = Q_NULLPTR);
	~DrawingArea() final;

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

	void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;

	QString mousePosition();
signals:
	void mousePositionChanged(QString position);
	void controlPointListChanged(std::vector<esl::ControlPoint> points);

public slots:
	void controlPointListUpdated(std::vector<esl::ControlPoint> points);

private:
	int canvasMinX, canvasMinY, canvasMaxX, canvasMaxY;
	void drawBackgroundBox(QPainter &painter);
	void drawPath(QPainter &painter, std::vector<QPoint> points);
	int mouseX, mouseY;
	std::vector<esl::ControlPoint> controlPointList;
};
