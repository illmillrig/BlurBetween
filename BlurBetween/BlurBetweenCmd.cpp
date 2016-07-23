

#include "BlurBetweenCmd.h"


#include <maya/MGlobal.h>
#include <maya/MArgParser.h>
#include <maya/MSyntax.h>


#define	kMix "-m"
#define	kMixLong "-mixValue"
#define	kTweenType "-t"
#define	kTweenTypeLong "-tweenType"
#define	kFresh "-f"
#define	kFreshLong "-fresh"



Tweener BlurBetween::bTween;


BlurBetween::BlurBetween(){
	this->mix = 0.5;
	this->tweenType = 0;
	this->fresh = true;
}


BlurBetween::~BlurBetween(){ }


MStatus BlurBetween::doIt(const MArgList &argList ){
	this->argParser(argList);
	bTween.tweenAnimPlugs((this->mix/100.0), this->tweenType, this->fresh, &this->animCurveChange);

	return MS::kSuccess;
}


MStatus BlurBetween::redoIt(){
	this->animCurveChange.redoIt();

	return MS::kSuccess;
}


MStatus BlurBetween::undoIt(){
	this->animCurveChange.undoIt();
	
	return MS::kSuccess;
}


MStatus BlurBetween::argParser(MArgList argList){

	this->mix = argList.asDouble(0);
	this->tweenType = argList.asInt(1);
	this->fresh = argList.asBool(2);

	// NOT SURE WHY THIS NEXT LINE CRASHES MAYA
	//MArgParser parsed(this->syntax(), argList);

	/*if (parsed.isFlagSet(kMix)){
		this->mix = parsed.flagArgumentDouble(kMixLong, 0);
	}

	if (parsed.isFlagSet(kTweenType)){
		this->tweenType = parsed.flagArgumentString(kTweenType, 0);
	}

	if (parsed.isFlagSet(kFresh)){
		this->fresh = parsed.flagArgumentBool(kFresh, 0);
	}*/

	return MS::kSuccess;
}



MSyntax BlurBetween::syntaxCreator(){
	MSyntax syntax;
	syntax.addFlag(kMix, kMixLong, MSyntax::kDouble);
	syntax.addFlag(kTweenType, kTweenTypeLong, MSyntax::kString);
	syntax.addFlag(kFresh, kFreshLong, MSyntax::kDouble);
	return syntax;
}


bool BlurBetween::isUndoable() const{
	return true;
}


void* BlurBetween::creator()
{
	return new BlurBetween();
}
