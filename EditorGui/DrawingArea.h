#pragma once

#include <QWidget>  // NOLINT
#include "ControlPoint.h"

class DrawingArea : public QWidget {
  Q_OBJECT

 public:
  DrawingArea(QWidget* parent = Q_NULLPTR);
  ~DrawingArea() final;

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

  void paintEvent(QPaintEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
 signals:
  void mousePositionChanged(QPoint point);
  void controlPointListChanged();

 public slots:
  void controlPointListUpdated();

 private:
  std::vector<esl::ControlPoint>* controlPointList;
  double* controlPointWeight;
  int canvasMinX, canvasMinY, canvasMaxX, canvasMaxY;

  void drawBackgroundBox(QPainter& painter);
  void drawPath(QPainter& painter, std::vector<QPoint> points);

  // TODO: Split into helper methods?
  std::vector<QPoint> toQPoints(
      std::vector<esl::ControlPoint> controlPointList);
  QPoint toQPoint(esl::ControlPoint point);
  esl::ControlPoint toControlPoint(QPoint point);

 public:
  void setControlPointListReference(
      std::vector<esl::ControlPoint>* controlPointList);
  void setControlPointWeightReference(double* controlPointWeight);
};
