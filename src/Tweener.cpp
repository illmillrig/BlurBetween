#include "Tweener.h"

#include <maya/MGlobal.h>
#include <maya/MAnimControl.h>
#include <maya/MAnimUtil.h>
#include <maya/MFnCharacter.h>
#include <maya/MPlug.h>



Tweener::Tweener(){}

Tweener::~Tweener(){}


void Tweener::setCurrentTime(){
	this->currentTime = MAnimControl::currentTime();
}


void Tweener::setDefaults(){
	this->animPlugs.clear();
	this->animValues.clear();
	this->setCurrentTime();
	MGlobal::getActiveSelectionList(this->nodes);
}


void Tweener::tweenAnimPlugs(const double mix, const int &tweenType, const bool &fresh, MAnimCurveChange *animCurveChange){

	const double mixA = 1.0 - mix;

	if (fresh) {
	
		this->setDefaults();

		if (tweenType == 0)
			this->tweenKeyed(mixA, mix, animCurveChange);
		
		else if (tweenType == 1)
			this->tweenMarked(mixA, mix, animCurveChange);

		else if (tweenType == 2)
			this->tweenManipulator(mixA, mix, animCurveChange);

		else if (tweenType == 3)
			this->tweenCharacter(mixA, mix, animCurveChange);

		else if (tweenType == 4)
			this->tweenGraph(mixA, mix, animCurveChange);

		else
			this->tweenKeyed(mixA, mix, animCurveChange);
	}

	else
		tweenStoredPlugs(mixA, mix);
}


void Tweener::tweenKeyed(const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange) {
	MPlugArray attrs;
	MAnimUtil::findAnimatedPlugs(this->nodes, attrs);
	this->collectAndTweenFnCurves(attrs, mixA, mixB, animCurveChange);
}


void Tweener::tweenMarked(const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange) {
	MStringArray attrNames;
	MGlobal::executeCommand("channelBox -query -selectedMainAttributes mainChannelBox;", attrNames);

	if (attrNames.length())
		this->tweenAttrNames(attrNames, mixA, mixB, animCurveChange);
}


void Tweener::tweenManipulator(const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange) {
	MStringArray attrNames;
	attrNames = this->getAttrsFromManip();

	if (attrNames.length())
		tweenAttrNames(attrNames, mixA, mixB, animCurveChange);
}


void Tweener::tweenCharacter(const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange) {
	MString characterName;
	MGlobal::executeCommand("selectionConnection -query -object highlightList;", characterName);

	if (characterName.length()){
		MObject character;
		this->getCharacterNode(characterName);

		MFnCharacter fnCharacter;
		MPlugArray attrs;
		fnCharacter.getMemberPlugs(attrs);

		this->collectAndTweenFnCurves(attrs, mixA, mixB, animCurveChange);
	}
}


void Tweener::tweenGraph(const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange) {
	MStringArray attrNames;
	MGlobal::executeCommand("keyframe -query -name", attrNames);
	
	MSelectionList sel;
	MObject animCurve;
	unsigned int length = attrNames.length();
	
	for (unsigned int i=0; i < length; i++){
		sel.add(attrNames[i]);
		sel.getDependNode(i, animCurve);
		this->tweenPlug(animCurve, mixA, mixB, animCurveChange);
	}
}


MObject Tweener::getCharacterNode(const MString &name){
	MSelectionList sel;
	sel.add(name);

	MObject character;
	sel.getDependNode(0, character);

	return character;
}


void Tweener::tweenAttrNames(const MStringArray &attrNames, const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange) {
	MDagPath dagNode;
	unsigned int length1 = this->nodes.length();
	unsigned int length2 = attrNames.length();
	unsigned int length3 = 0;

	for (unsigned int i=0; i < length1; i++){

		this->nodes.getDagPath(i, dagNode);

		if (!MAnimUtil::isAnimated(dagNode))
			return;
		
		this->fnDepend.setObject(dagNode.node());

		for (unsigned int j=0; j < length2; j++){

			// TODO: This seems like duplicate code

			this->objArray.setLength(0);
			MAnimUtil::findAnimation(this->fnDepend.findPlug(attrNames[j]), this->objArray);

			length3 = this->objArray.length();
			for (unsigned int k = 0; k < length3; k++) {
				this->tweenPlug(this->objArray[k], mixA, mixB, animCurveChange);
			}

		}
	}
}


MStringArray Tweener::getAttrsFromManip(){
	MString ctx;
	MGlobal::executeCommand("currentCtx;", ctx);
	MStringArray attrNames;

	if (!ctx.length())
		return attrNames;

	else if (ctx == "moveSuperContext") {
		attrNames.append("tx");
		attrNames.append("ty");
		attrNames.append("tz");
	}

	else if (ctx == "RotateSuperContext") {
		attrNames.append("rx");
		attrNames.append("ry");
		attrNames.append("rz");
	}

	else if (ctx == "scaleSuperContext") {
		attrNames.append("sx");
		attrNames.append("sy");
		attrNames.append("sz");
	}

	return attrNames;
}


void Tweener::collectAndTweenFnCurves(const MPlugArray &connections, const double &mixA, const double &mixB,
									  MAnimCurveChange *animCurveChange){
	unsigned int length1 = connections.length();
	unsigned int length2 = 0;

	for (unsigned int i=0; i < length1; i++){

		// TODO: This seems like duplicate code

		this->objArray.setLength(0); // is this needed? or does findAnimation() clear it for you?
		MAnimUtil::findAnimation(connections[i], this->objArray);

		length2 = this->objArray.length();
		for (unsigned int j=0; j < length2; j++)
			this->tweenPlug(this->objArray[j], mixA, mixB, animCurveChange);
	}
}


std::array<double, 2> Tweener::collectKeyValues(MFnAnimCurve &fnAnimCurve){
	unsigned int closestKey = fnAnimCurve.findClosest(this->currentTime);
	MTime closestKeyTime = fnAnimCurve.time(closestKey);
	
	std::array<double, 2> keyValues;
	
	// TODO: Need to check that these keys exist first

	if (closestKey == 0){	
		keyValues[0] = fnAnimCurve.value(closestKey);
		keyValues[1] = fnAnimCurve.value(closestKey + 1);
	}

	else if (closestKey == fnAnimCurve.numKeys() - 1){
		keyValues[0] = fnAnimCurve.value(closestKey - 1);
		keyValues[1] = fnAnimCurve.value(closestKey);
	}

	else if (closestKeyTime == this->currentTime){
		keyValues[0] = fnAnimCurve.value(closestKey - 1);
		keyValues[1] = fnAnimCurve.value(closestKey + 1);
	}

	else if (closestKeyTime > this->currentTime){
		keyValues[0] = fnAnimCurve.value(closestKey - 1);
		keyValues[1] = fnAnimCurve.value(closestKey);
	}

	else if (closestKeyTime < this->currentTime){
		keyValues[0] = fnAnimCurve.value(closestKey);
		keyValues[1] = fnAnimCurve.value(closestKey + 1);
	}

	else{
		keyValues[0] = fnAnimCurve.value(closestKey - 1);
		keyValues[1] = fnAnimCurve.value(closestKey + 1);	
	}

	return keyValues;
}


void Tweener::tweenPlug(const MObject &plug, const double &mixA, const double &mixB, MAnimCurveChange *animCurveChange){
	this->fnAnimCurve.setObject(plug);
	this->animPlugs.push_back(plug);
	this->animValues.push_back(this->collectKeyValues(fnAnimCurve));

	// TODO: is Auto tangents fine here?, or should I use the same tangents of the keys being tweened between

	this->fnAnimCurve.addKey(this->currentTime, this->mixValues(this->animValues.back(), mixA, mixB),
							 MFnAnimCurve::kTangentAuto, MFnAnimCurve::kTangentAuto, animCurveChange);
}


void Tweener::tweenStoredPlugs(const double &mixA, const double &mixB) {
	size_t numPlugs = this->animPlugs.size();
	for (size_t i=0; i < numPlugs; i++) {
		this->fnAnimCurve.setObject(this->animPlugs[i]);
		this->fnAnimCurve.addKey(this->currentTime, this->mixValues(this->animValues[i], mixA, mixB),
  								 MFnAnimCurve::kTangentAuto, MFnAnimCurve::kTangentAuto, nullptr);
	}
}


inline double Tweener::mixValues(const std::array<double, 2> &keyValues, const double &mixA, const double &mixB) const {
	return (keyValues[0] * mixA) + (keyValues[1] * mixB);
}









