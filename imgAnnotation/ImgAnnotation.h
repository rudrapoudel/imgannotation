/**
 * Image Annotation Tool for image annotations with pixelwise masks
 *
 * Author: Rudra Poudel
 */
#ifndef ImgAnnotation_H
#define ImgAnnotation_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QHash>
#include <QPointF>
#include <QRectF>

#define NEW_OBJ_TYPE "<none>"

class ImgAnnotation;

class IAObj {
public:
	QString type;
	QString tmp;
	QStringList tags;
	QList<QPointF> fixPoints;
	QRectF box;
	uint id;
	double score;
	double comboScore;

public:
	IAObj();
	bool isEmpty();
};


class IAFile {
public:
	QList<IAObj> objects;
};


class IADir {
public:
	QHash<QString, IAFile> files;
};


class ImgAnnotation : public QObject {
	Q_OBJECT

public:
	// hash that stores the directories
	QHash<QString, IADir> dirs;

public:
	ImgAnnotation();
	void addFiles(const QStringList&);
	void removeFiles(const QStringList&);
	void loadFromFile(const QString&);
	void saveToFile(const QString&);
	QStringList getAllTags() const;
	QStringList getAllObjTypes() const;

	QList<QString> getDirs() const;
	QList<QString> getDirFiles(const QString dir) const;
	QList<IAObj> *getObj(const QString dir, const QString file);
	IAObj *getObj(const QString dir, const QString file, const int objIndex);
	IAFile *getFile(const QString dir, const QString file);
	void newObj(const QString, const QString, const QString = NEW_OBJ_TYPE);
	void newObj(const QString, const QString, const IAObj &);
	void removeObj(const QString, const QString, const QList<int>);
	void clear();

signals:
	void filesChanged();
	void objectsChanged();
};


#endif
