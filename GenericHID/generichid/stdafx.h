#ifndef _STDAFX_H_
#define _STDAFX_H_

#ifdef _WIN32
#include <atlbase.h>
#pragma warning(push, 1)
#endif

#include <QtGui>
#include <QTimer>
#include <QDomDocument>
#include <QDomElement>
#include <QMimeData>
#include <QVariant>
#include <QToolButton>
#include <QtGui/QMainWindow>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QSettings>

#include <QtLineEditFactory>
#include <QtDoubleSpinBoxFactory>
#include "qtpropertymanager.h"
#include "qtvariantproperty.h"
#include "qtpropertymanager.h"
#include "qtpropertybrowser.h"
#include "qtvariantproperty.h"
#include <QtTreePropertyBrowser>
#include <QtAbstractPropertyManager>
#include "usagepropertymanager.h"
#include <QtProperty>

#ifdef _WIN32
#pragma warning(pop)
#endif

#include "common.h"
#include "datatypes.h"
#include "log.h"
#include "xmlutility.h"
#include <assert.h>


namespace UserTypes
{
    enum UserTypes
    {
	PinItemType = 1,
	ShapeItemType
    };
}

#endif

