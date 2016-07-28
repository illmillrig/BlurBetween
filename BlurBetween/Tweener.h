#pragma once

#include <maya/MTime.h>
#include <maya/MString.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MSelectionList.h>
#include <maya/MFnAnimCurve.h>
#include <maya/MDagPath.h>
#include <maya/MStringArray.h>
#include <maya/MPlugArray.h>
#include <maya/MAnimCurveChange.h>
#include <maya/MObjectArray.h>

#include <vector> 
#include <array> 

#include <memory> 


class Tweener {
public:
	Tweener();
	~Tweener();
	
	MStatus tweenAnimPlugs(double &mix, const int &tweenType, const bool &fresh, MAnimCurveChange *animCurveChange);
	MStatus tweenKeyed(double &mix, MAnimCurveChange *animCurveChange);
	MStatus tweenMarked(double &mix, MAnimCurveChange *animCurveChange);
	MStatus tweenManipulator(double &mix, MAnimCurveChange *animCurveChange);
	MStatus tweenCharacter(double &mix, MAnimCurveChange *animCurveChange);
	MStatus tweenGraph(double &mix, MAnimCurveChange *animCurveChange);

	MObjectArray objArray;
	MFnAnimCurve fnAnimCurve;
	MFnDependencyNode fnDepend;
	MSelectionList nodes;
	MTime currentTime;
	MAnimCurveChange animCurveChange;

	std::vector <MObject> animPlugs;
	std::vector <std::array<double, 2> > animValues;
		
	MStatus setCurrentTime();
	MStatus setDefaults();

	MObject getCharacterNode(MString &name);
	MStatus tweenAttrNames(MStringArray &attrs, double &mix, MAnimCurveChange *animCurveChange);
	MStringArray getAttrsFromManip();
	MStatus tweenPlug(MObject &plug, double &mixA, double &mixB, MAnimCurveChange *animCurveChange);
	MStatus collectAndTweenFnCurves(MPlugArray &connections, double &mixA, double &mixB, MAnimCurveChange *animCurveChange);
	std::array<double, 2> collectKeyValues(MFnAnimCurve &fnAnimCurve);
	MStatus tweenStoredPlugs(double &mixB);
	double mixValues(std::array<double, 2> &keyValues, double &mixA, double &mixB);

};
