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
	
	void tweenAnimPlugs(const double mix, const int &tweenType, const bool &fresh, MAnimCurveChange *animCurveChange);
	void tweenKeyed(const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange);
	void tweenMarked(const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange);
	void tweenManipulator(const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange);
	void tweenCharacter(const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange);
	void tweenGraph(const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange);

public:
	std::vector <MObject> animPlugs;
	std::vector <std::array<double, 2> > animValues;
	MObjectArray objArray;
	MSelectionList nodes;

private:
	MFnAnimCurve fnAnimCurve;
	MFnDependencyNode fnDepend;
	MTime currentTime;
	MAnimCurveChange animCurveChange;

private:
	void setCurrentTime();
	void setDefaults();
	MObject getCharacterNode(const MString &name);
	void tweenAttrNames(const MStringArray &attrs, const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange);
	MStringArray getAttrsFromManip();
	void tweenPlug(const MObject &plug, const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange);
	void collectAndTweenFnCurves(const MPlugArray &connections, const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange);
	std::array<double, 2> collectKeyValues(MFnAnimCurve &fnAnimCurve);
	void tweenStoredPlugs(const double &mixA, const double &mixB);
	double mixValues(const std::array<double, 2> &keyValues, const double &mixA, const double &mixB) const;
};
