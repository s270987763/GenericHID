#include "stdafx.h"
#include "shapeselectorswitch.h"

const int MAX_SELECTOR_PINS = 12;

ShapeSelectorSwitch::ShapeSelectorSwitch(QDomElement &node, const QString &sShapeName, ShapeType::ShapeType eShapeType, const QString &sShapeId, bool bSource, const QString &sImageFile, int nImageWidth, int nImageHeight, const QString &sIconFile, int nMaxInstances, const QString &sDescription)
: Shape(node, sShapeName, eShapeType, sShapeId, bSource, sImageFile, nImageWidth, nImageHeight, sIconFile, nMaxInstances, sDescription)
{
}

ShapeSelectorSwitch::~ShapeSelectorSwitch(void)
{
}

bool ShapeSelectorSwitch::Verify( QString &sErrors, const QList<class PinItem *> &pins, const QList<class PropertyValue *> &values ) const
{
    bool bSuccess = true;

    int nOutputs = GetPropertyValueInt( "Outputs", values, 0 );

    QSet<QString> pinsToCheck;
    for ( int i = 0; i < nOutputs; i++ )
	pinsToCheck << QString::number( i+1 );

    QSet<QString> notPinsToCheck;
    for ( int i = nOutputs; i < MAX_SELECTOR_PINS; i++ )
	notPinsToCheck << QString::number( i+1 );

    bSuccess = CheckPins( sErrors, pins, pinsToCheck );
    if ( !CheckNotPins( sErrors, pins, notPinsToCheck ) )
	bSuccess = false;

    return bSuccess;
}
