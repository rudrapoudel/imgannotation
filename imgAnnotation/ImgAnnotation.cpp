/**
 * Image Annotation Tool for image annotations with pixelwise masks
 *
 * Author: Rudra Poudel
 */
#include "ImgAnnotation.h"
#include <QStringList>
#include <QFile>
#include <QRegExp>
#include <QTextStream>
#include <QtDebug>


// ========== ImgAnnotation ==========

ImgAnnotation::ImgAnnotation()
{
}

void ImgAnnotation::loadFromFile(const QString &filepath)
{
	// try to open the file
	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	// clear the current content
	dirs.clear();

	// loop over all lines
	IAFile *currentFile = NULL;
	IAObj *currentObj = NULL;
	IAFile emptyFile;
	IAObj emptyObj;

	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		line = line.trimmed();

		// ignore empty lines and comment lines
		if (line.isEmpty() || line.startsWith("#"))
			continue;

		// split the line in its key and value (up to ':' and the value)
		QString key = line.section(':', 0, 0).trimmed().toLower();
		QString value = line.section(':', 1, -1).trimmed();

		//
		// decide what to do based on the key value
		//

		if (key == "file") {
			// we have a new file given .. parse the pathname
			QString filename = value.section('/', -1);
			QString dir = value.section('/', 0, -2);

			// add a new empty file .. if it doesn't exist already
			if (!(dirs.contains(dir) && dirs[dir].files.contains(filename))) {
				dirs[dir].files[filename] = emptyFile;
			}

			// update currentFile and currentObj (to zero, since we added a new file)
			currentFile = &(dirs[dir].files[filename]);
			currentObj = NULL;
		}
		else if (key == "object") {
			// we have a new object given
			if (currentFile == NULL)
				continue;

			// add a new empty object
			emptyObj.type = value;
			currentFile->objects << emptyObj;

			// update currentObj
			currentObj = &(currentFile->objects.last());
		}
		else if (key == "minxymaxxy") {
			// we have new coordinates for min/max x/y value
			if (currentObj == NULL)
				continue;

			// set the min/max values for x/y
			currentObj->box.setLeft(value.section(',', 0, 0).trimmed().toFloat());
			currentObj->box.setTop(value.section(',', 1, 1).trimmed().toFloat());
			currentObj->box.setRight(value.section(',', 2, 2).trimmed().toFloat());
			currentObj->box.setBottom(value.section(',', 3, 3).trimmed().toFloat());
		}
		else if (key == "tags") {
			// we have tags given
			if (currentObj == NULL)
				continue;

			// clean the taggs and add the given ones to the currentObj
			currentObj->tags.clear();
			currentObj->tags << value.split(QRegExp("\\s*,\\s*"), QString::SkipEmptyParts);
		}
		else if (key == "fixpointsxy") {
			// we have a list of fix points given
			if (currentObj == NULL)
				continue;

			// split the list and add the points to the fix point list
			QStringList points = value.split(QRegExp("\\s*,\\s*"), QString::SkipEmptyParts);
			for (int i = 0; i < points.count() - 1; i += 2) {
				QPointF newPoint(points[i].trimmed().toFloat(), points[i + 1].trimmed().toFloat());
				currentObj->fixPoints << newPoint;
			}
		}
		else if (key == "score") {
			// we have a score value
			if (currentObj == NULL)
				continue;

			// update our score value
			currentObj->score = value.toDouble();
		}
	}

	// emit a signal that something has changed
	emit filesChanged();
}

void ImgAnnotation::saveToFile(const QString &filepath)
{
	// try to open the file
	QFile file(filepath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	// loop over all elements in our datastructur and write their data to the file
	QTextStream out(&file);
	QList<QString> dirList = getDirs();
	for (QList<QString>::const_iterator iDir = dirList.constBegin(); iDir != dirList.constEnd(); ++iDir) {
		QList<QString> fileList = getDirFiles(*iDir);
		for (QList<QString>::const_iterator iFile = fileList.constBegin(); iFile != fileList.constEnd(); ++iFile) {
			IAFile *file = getFile(*iDir, *iFile);
			out << "########## NEW FILE ##########\n";
			out << "file: " << *iDir << "/" << *iFile << "\n\n";
			for (QList<IAObj>::const_iterator iObj = file->objects.constBegin(); iObj != file->objects.constEnd(); ++iObj) {
				// output the object type
				out << "object: " << (*iObj).type << "\n";

				// output the bounding box
				if (!(*iObj).box.isEmpty())
					out << "minXYMaxXY: "
							<< (*iObj).box.left() << ", "
							<< (*iObj).box.top() << ", "
							<< (*iObj).box.right() << ", "
							<< (*iObj).box.bottom() << "\n";

				// output the tags
				if (!(*iObj).tags.isEmpty())
					out << "tags: " << (*iObj).tags.join(", ") << "\n";

				// output the fix points
				if (!(*iObj).fixPoints.isEmpty()) {
					out << "fixPointsXY: ";
					for (int iPoint = 0; iPoint < (*iObj).fixPoints.count(); iPoint++) {
						out << (*iObj).fixPoints[iPoint].x() << ", " << (*iObj).fixPoints[iPoint].y();
						if (iPoint < (*iObj).fixPoints.count() - 1)
							out << ", ";
						else
							out << "\n";
					}
				}

				// output the score
				if ((*iObj).score != 0)
					out << "score: " << (*iObj).score << "\n";

				// a additional empty line at the end of an object
				out << "\n";
			}
		}
	}
}

void ImgAnnotation::addFiles(const QStringList& files)
{
	IAFile emptyFile;

	for ( int i = 0; i < files.size(); i++ ) {
		// get the filename and the path
		QString filename = files[i].section('/', -1);
		QString path = files[i].section('/', 0, -2);

		dirs[path].files[filename] = emptyFile;
	}

	// emit a signal that something has changed
	emit filesChanged();
}

void ImgAnnotation::removeFiles(const QStringList& files)
{
	for ( int i = 0; i < files.size(); i++ ) {
		// get the filename and the path
		QString filename = files[i].section('/', -1);
		QString path = files[i].section('/', 0, -2);

		if (filename.isEmpty())
			// delete the whole directory
			dirs.remove(path);
		else
			// remove file
			dirs[path].files.remove(filename);
	}

	// emit a signal that something has changed
	emit filesChanged();
}

QList<QString> ImgAnnotation::getDirs() const
{
	return dirs.keys();
}

QList<QString> ImgAnnotation::getDirFiles(const QString dir) const
{
	if (!dirs.contains(dir))
		return QList<QString>();

	return dirs[dir].files.keys();
}

QList<IAObj> *ImgAnnotation::getObj(const QString dir, const QString file)
{
	if (!dirs.contains(dir) || !dirs[dir].files.contains(file))
		return NULL;

	return &(dirs[dir].files[file].objects);
}

IAObj *ImgAnnotation::getObj(const QString dir, const QString file, const int objIndex)
{
	if (!dirs.contains(dir) || !dirs[dir].files.contains(file)
		|| objIndex < 0 || objIndex >= dirs[dir].files[file].objects.count())
		return NULL;

	return &(dirs[dir].files[file].objects[objIndex]);
}

IAFile *ImgAnnotation::getFile(const QString dir, const QString file)
{
	if (!dirs.contains(dir) || !dirs[dir].files.contains(file))
		return NULL;

	return &(dirs[dir].files[file]);
}

QStringList ImgAnnotation::getAllTags() const
{
	QStringList tags;
	QHash<QString, bool> tagsHash;

	// go through all objects and collect different tags
	for (QHash<QString, IADir>::const_iterator iDir = dirs.constBegin(); iDir != dirs.constEnd(); ++iDir) {
		for (QHash<QString, IAFile>::const_iterator iFile = (*iDir).files.constBegin(); iFile != (*iDir).files.constEnd(); ++iFile) {
			for (QList<IAObj>::const_iterator iObj = (*iFile).objects.constBegin(); iObj != (*iFile).objects.constEnd(); ++iObj) {
				for (QStringList::const_iterator iTag = (*iObj).tags.constBegin(); iTag != (*iObj).tags.constEnd(); ++iTag) {
					// get the next tag, convert it to lower case, and see wether it exists (via our tag hash map)
					QString tagLowerCase = (*iTag).toLower();
					if (!tagsHash.contains(tagLowerCase)) {
						tagsHash[tagLowerCase] = true;
						tags << *iTag;
					}
				}
			}
		}
	}

	return tags;
}

QStringList ImgAnnotation::getAllObjTypes() const
{
	QStringList types;
	QHash<QString, bool> typesHash;

	// add the object type for new objects
	QString newType(NEW_OBJ_TYPE);
	typesHash[newType.toLower()] = true;
	types << newType;

	// go through all objects and collect different tags
	for (QHash<QString, IADir>::const_iterator iDir = dirs.constBegin(); iDir != dirs.constEnd(); ++iDir) {
		for (QHash<QString, IAFile>::const_iterator iFile = (*iDir).files.constBegin(); iFile != (*iDir).files.constEnd(); ++iFile) {
			for (QList<IAObj>::const_iterator iObj = (*iFile).objects.constBegin(); iObj != (*iFile).objects.constEnd(); ++iObj) {
				// get the next object type, convert it to lower case, and see wether it exists (via our type hash map)
				QString typeLowerCase = (*iObj).type.toLower();
				if (!typesHash.contains(typeLowerCase)) {
					typesHash[typeLowerCase] = true;
					types << (*iObj).type;
				}
			}
		}
	}

	return types;
}

void ImgAnnotation::newObj(const QString dir, const QString file, const QString objType)
{
	// make sure that a file entry exists
	if (!dirs.contains(dir) || !dirs[dir].files.contains(file)) {
		IAFile emptyFile;
		dirs[dir].files[file] = emptyFile;
	}

	// add a new object to our database
	IAObj emptyObj;
	emptyObj.type = objType;
	dirs[dir].files[file].objects << emptyObj;

	// send signal that an object has been added
	emit objectsChanged();
}

void ImgAnnotation::newObj(const QString dir, const QString file, const IAObj &newObj)
{
	// make sure that a file entry exists
	if (!dirs.contains(dir) || !dirs[dir].files.contains(file)) {
		IAFile emptyFile;
		dirs[dir].files[file] = emptyFile;
	}

	// add the new object to our database
	dirs[dir].files[file].objects << newObj;

	// send signal that an object has been added
	emit objectsChanged();
}

void ImgAnnotation::removeObj(const QString dir, const QString file, const QList<int> removeObj)
{
	if (!dirs.contains(dir) || !dirs[dir].files.contains(file))
		return;

	QList<IAObj> *objList = &(dirs[dir].files[file].objects);
	int removed = 0;
	for (QList<int>::const_iterator i = removeObj.constBegin(); i != removeObj.constEnd(); ++i) {
		int index = (*i) - removed;

		// check wether this object exists
		if (index < 0 || index >= objList->count())
			continue;

		// remove object from list
		objList->removeAt(index);
		removed++;
	}

	// send signal that an object has been added
	emit objectsChanged();
}


void ImgAnnotation::clear()
{
	dirs.clear();
}


// ========== IAObj ==========

IAObj::IAObj()
{
	// init the parameters
	type = NEW_OBJ_TYPE;
	score = 0.0;
	comboScore = 0.0;
}

bool IAObj::isEmpty()
{
	return (type.isEmpty() || type == NEW_OBJ_TYPE)
			&& tags.isEmpty() && fixPoints.isEmpty() && box.isEmpty();
}
