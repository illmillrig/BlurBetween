#pragma once

#include "Tweener.h"


#include <maya/MPxCommand.h>
#include <maya/MArgList.h>
#include <maya/MString.h>
#include <maya/MAnimCurveChange.h>


class MArgList;


class BlurBetween : public MPxCommand {
public:
	BlurBetween();
	virtual ~BlurBetween();

	MStatus	doIt(const MArgList& argList);
	MStatus	redoIt();
	MStatus	undoIt();
	bool isUndoable() const;

	static void* creator();
	static MSyntax syntaxCreator();
	MStatus	argParser(MArgList argList);

	double mix;
	int tweenType;
	bool fresh;
	MAnimCurveChange animCurveChange;

	static Tweener bTween;
};
