/**
 * Image Annotation Tool for image annotations with pixelwise masks
 *
 * Author: Rudra Poudel
 */
#include "PixmapWidget.h"

#include "defines.h"
#include <QPixmap>
#include <QPainter>
#include <QWheelEvent>
#include <QPointF>
#include <math.h>
#include <QAbstractScrollArea>
#include <QScrollBar>
#include <QColor>
#include <QVector>
#include <QtDebug>
#include <math.h>

PixmapWidget::PixmapWidget( QAbstractScrollArea *parentScrollArea, QWidget *parent )
	: QWidget( parent )
{
	scrollArea = parentScrollArea;
	m_pm = new QPixmap();
	zoomFactor = 1.0;
	iMaskEditColor = 1;
	penWidth = 5;
	maskTransparency = 0.5;
	isDrawing = false;
	isFloodFilling = false;

	setAttribute(Qt::WA_OpaquePaintEvent);
	setFocusPolicy(Qt::NoFocus);
	setMinimumSize( m_pm->width()*zoomFactor, m_pm->height()*zoomFactor );
	setMouseTracking(true);
	setCursor(QCursor(Qt::BlankCursor));
}

PixmapWidget::~PixmapWidget()
{
	delete m_pm;
}

void PixmapWidget::setZoomFactor( double f )
{
	int w, h;

	if( fabs(f - zoomFactor) <= 0.001 )
		return;

	zoomFactor = f;
	emit( zoomFactorChanged( zoomFactor ) );

	w = m_pm->width()*zoomFactor;
	h = m_pm->height()*zoomFactor;
	setMinimumSize( w, h );

	QWidget *p = dynamic_cast<QWidget*>( parent() );
	if( p )
		resize( p->width(), p->height() );

	update();
}

int PixmapWidget::getMaskEditColor()
{
    return MAX(0, MIN(mask.colorCount() - 1, iMaskEditColor));
}

QImage* PixmapWidget::getMask()
{
	updateMask();

	return &mask;
}

void PixmapWidget::setMask(QImage& newMask)
{
	// store the new mask
	mask = newMask.copy();

	// create a partly transparent mask
	QImage tmpMask = newMask.copy();
    for (int i = 0; i < drawMask.colorCount(); i++)
		tmpMask.setColor(i, getColor(i));
	drawMask = tmpMask.convertToFormat(QImage::Format_RGB32);

	// create the temporary draw mask
	tmpDrawMask = QImage(newMask.size(), QImage::Format_RGB32);

	// we have to repaint
	repaint();
}

void PixmapWidget::setPenWidth(int width)
{
	penWidth = width;
	update();
}

void PixmapWidget::setMaskEditColor(int iColor)
{
	iMaskEditColor = iColor;
}

void PixmapWidget::setMaskDrawOnColor(int iColor)
{
	iMaskDrawOnColor = MAX(-1, iColor);
    if (iColor >= mask.colorCount())
		iMaskDrawOnColor = -1;
}

void PixmapWidget::setMaskTransparency(double transparency)
{
	maskTransparency = transparency;
	updateMask();

	// create a partly transparent mask
	QImage tmpMask = mask.copy();
    for (int i = 0; i < drawMask.colorCount(); i++) {
		tmpMask.setColor(i, getColor(i));
	}
	drawMask = tmpMask.convertToFormat(QImage::Format_ARGB32_Premultiplied);


	// we have to repaint
	update();
}

void PixmapWidget::setFloodFill(bool flag)
{
	isFloodFilling = flag;
	if (flag)
		setCursor(QCursor(Qt::CrossCursor));
	else
		setCursor(QCursor(Qt::BlankCursor));

	update();
}

void PixmapWidget::setPixmap( const QPixmap& pixmap)
{
	delete m_pm;
	m_pm = new QPixmap(pixmap);

	emit( pixmapChanged( m_pm ) );

	setMinimumSize( m_pm->width()*zoomFactor, m_pm->height()*zoomFactor );
	repaint();
}

void PixmapWidget::paintEvent( QPaintEvent *event )
{
	bool drawBorder = false;
	int xOffset = 0, yOffset = 0;

	if( width() > m_pm->width()*zoomFactor ) {
		xOffset = (width()-m_pm->width()*zoomFactor)/2;
		drawBorder = true;
	}

	if( height() > m_pm->height()*zoomFactor ) {
		yOffset = (height()-m_pm->height()*zoomFactor)/2;
		drawBorder = true;
	}

	// get the current value of the parent scroll area .. to optimize the painting
	double hValue = 0, hMin = 0, hMax = 0, hPageStep = 0, hLength = 0;
	double vValue = 0, vMin = 0, vMax = 0, vPageStep = 0, vLength = 0;
	if (scrollArea) {
		QScrollBar *scrollBar;
		scrollBar = scrollArea->horizontalScrollBar();
		if (scrollBar) {
			hValue = scrollBar->value();
			hMin = scrollBar->minimum();
			hMax = scrollBar->maximum();
			hPageStep = scrollBar->pageStep();
			hLength = hMax - hMin + hPageStep;
		}
		scrollBar = scrollArea->verticalScrollBar();
		if (scrollBar) {
			vValue = scrollBar->value();
			vMin = scrollBar->minimum();
			vMax = scrollBar->maximum();
			vPageStep = scrollBar->pageStep();
			vLength = vMax - vMin + vPageStep;
		}
	}

	//
	// draw image and the transparent image mask
	//

	QPainter p(this);
	p.setRenderHint(QPainter::SmoothPixmapTransform, false);
	p.setRenderHint(QPainter::Antialiasing, false);

	// adjust the coordinate system
	p.save();
	p.translate(xOffset, yOffset);
	p.scale(zoomFactor, zoomFactor);
	currentMatrixInv = p.matrix().inverted();
	currentMatrix = p.matrix();

	// find out which part of the image we have to draw
	// since we are embedded into a QScrollArea and not all is visible
	QRectF updateRectF = currentMatrixInv.mapRect(event->rect());
	if (lastVScrollValue != vValue || lastHScrollValue != hValue || updateRectF.isEmpty()) {
		updateRectF.setLeft((hValue / hLength) * m_pm->width());
		updateRectF.setWidth((hPageStep / hLength) * m_pm->width());
		updateRectF.setTop((vValue / vLength) * m_pm->height());
		updateRectF.setHeight((vPageStep / vLength) * m_pm->height());
	}
	QRect updateRect;
	updateRect.setLeft(int(updateRectF.left()+0.5) - 1);
	updateRect.setRight(int(updateRectF.right()+0.5) + 1);
	updateRect.setTop(int(updateRectF.top()+0.5) - 1);
	updateRect.setBottom(int(updateRectF.bottom()+0.5) + 1);

	// save the scroll bar values
	lastVScrollValue = vValue;
	lastHScrollValue = hValue;

	// find out what needs to be cleared on the canvas outside the image
	QRectF eraseTop(updateRect.left(), updateRect.top(), updateRect.width(), -updateRect.top());
	QRectF eraseBottom(updateRect.left(), m_pm->height(), updateRect.width(), updateRect.height() - (-updateRect.top() + m_pm->height()));
	QRectF eraseLeft(updateRect.left(), 0, -updateRect.left(), m_pm->height());
	QRectF eraseRight(m_pm->width(), 0, updateRect.height() - (-updateRect.left() + m_pm->width()), m_pm->height());
	if (eraseTop.isValid())
		p.eraseRect(eraseTop);
	if (eraseBottom.isValid())
		p.eraseRect(eraseBottom);
	if (eraseLeft.isValid())
		p.eraseRect(eraseLeft);
	if (eraseRight.isValid())
		p.eraseRect(eraseRight);

	// draw the image
	p.drawPixmap(updateRect.topLeft(), *m_pm, updateRect);

	// draw the object mask
	QImage transparentMask = drawMask.convertToFormat(QImage::Format_ARGB32);
	QImage alphaChannel = transparentMask.alphaChannel();
	for (int y = MAX(0, updateRect.top()); y <= updateRect.bottom() && y < transparentMask.height(); y++)
		for (int x = MAX(0, updateRect.left()); x <= updateRect.right() && x < transparentMask.width(); x++) {
			QRgb rgb = transparentMask.pixel(x, y);
			if (qRed(rgb) == 0 && qGreen(rgb) == 0 && qBlue(rgb) == 0)
				// black is the background color .. 100% transparent
				alphaChannel.setPixel(x, y, 0);
			else
				// all other colors are partly transparent
				alphaChannel.setPixel(x, y, (int)(255 * maskTransparency + 0.5));
		}
	transparentMask.setAlphaChannel(alphaChannel);
	p.drawImage(updateRect.topLeft(), transparentMask, updateRect);

	// draw the brush
	if (!isFloodFilling) {
		QPen penWhite(QColor(255, 255, 255, (int)(255 * maskTransparency + 0.5)));
		penWhite.setWidth(1 / zoomFactor);
		QPen penBlack(QColor(0, 0, 0, (int)(255 * maskTransparency + 0.5)));
		penBlack.setWidth(1 / zoomFactor);
		p.setPen(penWhite);
		p.drawEllipse(QRectF(
				xyMouseFollowed.x() - 0.5 * penWidth - 0.5 / zoomFactor + 0.5,
				xyMouseFollowed.y() - 0.5 * penWidth - 0.5 / zoomFactor + 0.5,
				penWidth + 1 / zoomFactor, penWidth + 1 / zoomFactor));
		p.setPen(penBlack);
		p.drawEllipse(QRectF(
				xyMouseFollowed.x() - 0.5 * penWidth + 0.5 / zoomFactor + 0.5,
				xyMouseFollowed.y() - 0.5 * penWidth + 0.5 / zoomFactor + 0.5,
				penWidth - 1 / zoomFactor, penWidth - 1 / zoomFactor));
	}

	// draw a border around the image
	p.restore();
	if (drawBorder) {
		p.setPen( Qt::black );
		p.drawRect( xOffset-1, yOffset-1, m_pm->width()*zoomFactor+1, m_pm->height()*zoomFactor+1 );
	}
}

void PixmapWidget::mousePressEvent(QMouseEvent * event)
{
	// get the mouse coordinate in the zoomed image
	QPoint xyMouseOrg(event->x(), event->y());
	QPoint xyMouse = currentMatrixInv.map(xyMouseOrg);
//	QPoint lastXyMouse = currentMatrixInv.map(lastXyMouseOrg);
//	QPoint lastXyDrawnMouse = currentMatrixInv.map(lastXyDrawnMouseOrg);

	// floodfill the image with the current color
	if (event->button() == Qt::LeftButton && isFloodFilling) {
		int orgIColor = mask.pixelIndex(xyMouse.x(), xyMouse.y());
		QList<QPoint> pointStack;
		pointStack << xyMouse;
		QList<QPoint> neighborPoints;
		while (!pointStack.isEmpty()) {
			QPoint point = pointStack.first();
			pointStack.removeFirst();

			// check whether the pixel has been processed in the meanwhile
			QRgb tmpRgb = 0x00FFFFFF & tmpDrawMask.pixel(point);
			if (tmpRgb != 0)
				continue;

			// fill the point and mark the point as filled
			drawMask.setPixel(point, getColor(getMaskEditColor()));
			tmpDrawMask.setPixel(point, Qt::white);

			// add the points in a 4-neighborhood
			for (int i = -1; i <= 1; ++i)
				for (int j = -1; j <= 1; ++j) {
					if (i == j)
						continue;

					// the coordinates for the neighbor point
					int x = point.x() + i;
					int y = point.y() + j;

					// check whether point lies in the image
					if (x < 0 || x >= drawMask.width() || y < 0 || y >= drawMask.height())
						continue;

					// get the colors
					int iColor = mask.pixelIndex(x, y);
					QRgb tmpRgb = 0x00FFFFFF & tmpDrawMask.pixel(x, y);

					// check whether the color is the right one and
					// whether it has not been processed so far
					if (iColor != orgIColor || tmpRgb != 0)
						continue;

					// everything ok .. we'll add the point to the list
					pointStack << QPoint(x, y);
				}
		}

		// reset the temporary mask
		tmpDrawMask.fill(0);

		// update
		updateMask();
		update();

		// send the signal that the mask has been changed
		emit( drawEvent( &mask ) );
	}
	// draw a line / point
	else if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
		// get the region of the mouse coursor
		QRect updateRectOrg;
		int penOffset = (int) ceil(zoomFactor * (0.5 * penWidth + 2));
		if (event->button() == Qt::LeftButton) {
			updateRectOrg.setLeft(xyMouseOrg.x() - penOffset);
			updateRectOrg.setRight(xyMouseOrg.x() + penOffset);
			updateRectOrg.setTop(xyMouseOrg.y() - penOffset);
			updateRectOrg.setBottom(xyMouseOrg.y() + penOffset);
		}
		else if (event->button() == Qt::RightButton) {
			QPoint mappedLastXyDrawMouse = currentMatrix.map(lastXyDrawnMouse);
			updateRectOrg.setLeft(MIN(mappedLastXyDrawMouse.x(), xyMouseOrg.x()) - penOffset);
			updateRectOrg.setRight(MAX(mappedLastXyDrawMouse.x(), xyMouseOrg.x()) + penOffset);
			updateRectOrg.setTop(MIN(mappedLastXyDrawMouse.y(), xyMouseOrg.y()) - penOffset);
			updateRectOrg.setBottom(MAX(mappedLastXyDrawMouse.y(), xyMouseOrg.y()) + penOffset);
		}
		QRect updateRect = currentMatrixInv.mapRect(updateRectOrg);

		if (iMaskDrawOnColor < 0) {
			// draw on the full image
			QPainter painter(&drawMask);
			setUpPainter(painter);
			if (event->button() == Qt::LeftButton)
				painter.drawPoint(xyMouse);
			else if (event->button() == Qt::RightButton)
				painter.drawLine(lastXyDrawnMouse, xyMouse);
		}
		else {
			// draw into the temporary mask
			QPainter painter(&tmpDrawMask);
			painter.setRenderHint(QPainter::Antialiasing, false);
			painter.setPen(QPen(QBrush(Qt::white),
					penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
			if (event->button() == Qt::LeftButton)
				painter.drawPoint(xyMouse);
			else if (event->button() == Qt::RightButton)
				painter.drawLine(lastXyDrawnMouse, xyMouse);

			// draw on a specific color
			for (int y = MAX(0, updateRect.top()); y <= updateRect.bottom() && y < drawMask.height(); y++)
				for (int x = MAX(0, updateRect.left()); x <= updateRect.right() && x < drawMask.width(); x++) {
					int iColor = mask.pixelIndex(x, y);
					int tmpColor = 0x00FFFFFF & tmpDrawMask.pixel(x, y);
					if (tmpColor != 0 && iColor == iMaskDrawOnColor)
						drawMask.setPixel(x, y, getColor(getMaskEditColor()));
				}

			// clear the region in the temporary mask that has been drawn to
			painter.fillRect(updateRect, QBrush(Qt::black));
		}

		// update
		if (event->button() == Qt::LeftButton)
			isDrawing = true;

		// save the current position and perform an update in the
		// region of the mouse coursor
		lastXyMouseOrg = xyMouseOrg;
		lastXyMouse = xyMouse;
		lastXyDrawnMouseOrg = xyMouseOrg;
		lastXyDrawnMouse = xyMouse;
		update(updateRectOrg);
	}
}

void PixmapWidget::mouseMoveEvent(QMouseEvent * event)
{
	// save the mouse position in coordinates of the zoomed image
	QPoint xyMouseOrg(event->x(), event->y());
	QPoint xyMouse = currentMatrixInv.map(xyMouseOrg);
//	QPoint lastXyMouse = currentMatrixInv.map(lastXyMouseOrg);
	xyMouseFollowed = xyMouse;

	// determine the region that has been changed
	QRect updateRectOrg;
	updateRectOrg.setLeft(MIN(lastXyMouseOrg.x(), xyMouseOrg.x()) - (int) ceil(zoomFactor * (0.5 * penWidth + 2)));
	updateRectOrg.setRight(MAX(lastXyMouseOrg.x(), xyMouseOrg.x()) + (int) ceil(zoomFactor * (0.5 * penWidth + 2)));
	updateRectOrg.setTop(MIN(lastXyMouseOrg.y(), xyMouseOrg.y()) - (int) ceil(zoomFactor * (0.5 * penWidth + 2)));
	updateRectOrg.setBottom(MAX(lastXyMouseOrg.y(), xyMouseOrg.y()) + (int) ceil(zoomFactor * (0.5 * penWidth + 2)));
	QRect updateRect = currentMatrixInv.mapRect(updateRectOrg);

	if (isDrawing) {
		if (iMaskDrawOnColor < 0) {
			// draw on the full image
			QPainter painter(&drawMask);
			setUpPainter(painter);
			painter.drawLine(lastXyMouse, xyMouse);
		}
		else {
			// draw into the temporary mask
			QPainter painter(&tmpDrawMask);
			painter.setRenderHint(QPainter::Antialiasing, false);
			painter.setPen(QPen(QBrush(Qt::white),
					penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
			painter.drawLine(lastXyMouse, xyMouse);

			// draw on a specific color
			for (int y = MAX(0, updateRect.top()); y <= updateRect.bottom() && y < drawMask.height(); y++)
				for (int x = MAX(0, updateRect.left()); x <= updateRect.right() && x < drawMask.width(); x++) {
					int iColor = mask.pixelIndex(x, y);
					int tmpColor = 0x00FFFFFF & tmpDrawMask.pixel(x, y);
					if (tmpColor != 0 && iColor == iMaskDrawOnColor)
						drawMask.setPixel(x, y, getColor(getMaskEditColor()));
				}

			// clear the region in the temporary mask that has been drawn to
			painter.fillRect(updateRect, QBrush(Qt::black));
		}

	}

	// save the current position and perform an update
	lastXyMouseOrg = xyMouseOrg;
	lastXyMouse = currentMatrixInv.map(xyMouseOrg);
	update(updateRectOrg);
}

void PixmapWidget::mouseReleaseEvent(QMouseEvent * event)
{
	// save the mouse position in coordinates of the zoomed image
	QPoint xyMouseOrg(event->x(), event->y());
	QPoint xyMouse = currentMatrixInv.map(xyMouseOrg);
	QPoint lastXyMouse = currentMatrixInv.map(lastXyMouseOrg);

	// determine the region that has been changed
	QRect updateRectOrg;
	updateRectOrg.setLeft(MIN(lastXyMouseOrg.x(), xyMouseOrg.x()) - (int) ceil(zoomFactor * (0.5 * penWidth + 2)));
	updateRectOrg.setRight(MAX(lastXyMouseOrg.x(), xyMouseOrg.x()) + (int) ceil(zoomFactor * (0.5 * penWidth + 2)));
	updateRectOrg.setTop(MIN(lastXyMouseOrg.y(), xyMouseOrg.y()) - (int) ceil(zoomFactor * (0.5 * penWidth + 2)));
	updateRectOrg.setBottom(MAX(lastXyMouseOrg.y(), xyMouseOrg.y()) + (int) ceil(zoomFactor * (0.5 * penWidth + 2)));
	QRect updateRect = currentMatrixInv.mapRect(updateRectOrg);

	if (event->button() == Qt::LeftButton && isDrawing) {

		if (iMaskDrawOnColor < 0) {
			// draw on the full image
			QPainter painter(&drawMask);
			setUpPainter(painter);
			painter.drawLine(lastXyMouse, xyMouse);
		}
		else {
			// draw into the temporary mask
			QPainter painter(&tmpDrawMask);
			painter.setRenderHint(QPainter::Antialiasing, false);
			painter.setPen(QPen(QBrush(Qt::white),
					penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
			painter.drawLine(lastXyMouse, xyMouse);

			// draw on a specific color
			for (int y = MAX(0, updateRect.top()); y <= updateRect.bottom() && y < drawMask.height(); y++)
				for (int x = MAX(0, updateRect.left()); x <= updateRect.right() && x < drawMask.width(); x++) {
					int iColor = mask.pixelIndex(x, y);
					int tmpColor = 0x00FFFFFF & tmpDrawMask.pixel(x, y);
					if (tmpColor != 0 && iColor == iMaskDrawOnColor)
						drawMask.setPixel(x, y, getColor(getMaskEditColor()));
				}

			// clear the region in the temporary mask that has been drawn to
			painter.fillRect(updateRect, QBrush(Qt::black));
		}

		// update
		isDrawing = false;
	}

	// save the last position
	lastXyMouseOrg = xyMouseOrg;
	lastXyMouse = currentMatrixInv.map(xyMouseOrg);
	lastXyDrawnMouseOrg = xyMouseOrg;
	lastXyDrawnMouse = currentMatrixInv.map(xyMouseOrg);

	// send the signal that the mask has been changed
	updateMask();
	emit( drawEvent( &mask ) );

	// paint update
	update(updateRectOrg);
}

void PixmapWidget::updateMouseCursor()
{
}

void PixmapWidget::updateMask()
{
	// store the original color table and clear the original mask
	QVector<QRgb> orgColorTable = mask.colorTable();
	mask.fill(0);

	// convert the mask to the original format
	QRgb rgb, lastRgb = qRgb(0, 0, 0);
	int i, lastI = 0;
	for (int y = 0; y < drawMask.height(); y++)
		for (int x = 0; x < drawMask.width(); x++) {
			QRgb rgb = drawMask.pixel(x, y);

			// see whether we have to find for the right color index or not
			if (rgb == lastRgb)
				mask.setPixel(x, y, lastI);
			else {
				// find the closest color
				int bestI = -1;
				double tmpDist, bestDist;
				for (int j = 0; j < orgColorTable.size(); j++) {
					tmpDist = pow(double(qRed(rgb) - qRed(orgColorTable[j])), 2)
							+ pow(double(qGreen(rgb) - qGreen(orgColorTable[j])), 2)
							+ pow(double(qBlue(rgb) - qBlue(orgColorTable[j])), 2);
					if (bestI < 0 || tmpDist < bestDist) {
						bestI = j;
						bestDist = tmpDist;
						if (bestDist == 0)
							break;
					}
				}

				// set the color and buffer the values
				mask.setPixel(x, y, bestI);
				lastI = bestI;
				lastRgb = rgb;
			}
		}
}

QRgb PixmapWidget::getColor(int i)
{
	QRgb color = mask.color(i);
// 	if (0 == i)
// 		color = qRgba(0, 0, 0, 0);
// 	else
// 		color = qRgba((int)(maskTransparency * qRed(color) + 0.5),
// 				(int)(maskTransparency * qGreen(color) + 0.5),
// 				(int)(maskTransparency * qBlue(color) + 0.5),
// 				(int)(maskTransparency * 255 + 0.5));
	return color;
}

void PixmapWidget::setUpPainter(QPainter &painter)
{
	painter.setRenderHint(QPainter::Antialiasing, false);
	painter.setPen(QPen(QBrush(getColor(getMaskEditColor())),
			penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}
