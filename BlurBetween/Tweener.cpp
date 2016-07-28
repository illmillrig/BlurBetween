#include "Tweener.h"

#include <maya/MGlobal.h>
#include <maya/MAnimControl.h>
#include <maya/MAnimUtil.h>
#include <maya/MFnCharacter.h>
#include <maya/MPlug.h>



Tweener::Tweener(){}

Tweener::~Tweener(){}


MStatus Tweener::setCurrentTime(){
	this->currentTime = MAnimControl::currentTime();
	return MS::kSuccess;
}


MStatus Tweener::setDefaults(){
	this->animPlugs.clear();
	this->animValues.clear();
	
	MGlobal::getActiveSelectionList(this->nodes);
	
	setCurrentTime();

	return MS::kSuccess;
}


MStatus Tweener::tweenAnimPlugs(double &mix, const int &tweenType, const bool &fresh, MAnimCurveChange *animCurveChange){
	
	if (fresh) {
	
		this->setDefaults();

		if (tweenType == 0)
			this->tweenKeyed(mix, animCurveChange);
		
		else if (tweenType == 1)
			this->tweenMarked(mix, animCurveChange);

		else if (tweenType == 2)
			this->tweenManipulator(mix, animCurveChange);

		else if (tweenType == 3)
			this->tweenCharacter(mix, animCurveChange);

		else if (tweenType == 4)
			this->tweenGraph(mix, animCurveChange);

		else
			this->tweenKeyed(mix, animCurveChange);
	}

	else
		tweenStoredPlugs(mix);

	return MS::kSuccess;
}


MStatus Tweener::tweenKeyed(double &mix, MAnimCurveChange *animCurveChange){
	
	MPlugArray attrs;
		
	MAnimUtil::findAnimatedPlugs(this->nodes, attrs);
	double mixB = 1.0 - mix;
	this->collectAndTweenFnCurves(attrs, mixB, mix, animCurveChange);

	return MS::kSuccess;
}


MStatus Tweener::tweenMarked(double &mix, MAnimCurveChange *animCurveChange){
	MStringArray attrNames;
	MGlobal::executePythonCommand("maya.cmds.channelBox('mainChannelBox', query=True, selectedMainAttributes=True)", attrNames);

	if (attrNames.length() > 0)
		this->tweenAttrNames(attrNames, mix, animCurveChange);
	
	return MS::kSuccess;
}


MStatus Tweener::tweenManipulator(double &mix, MAnimCurveChange *animCurveChange){
	MStringArray attrNames;
	attrNames = this->getAttrsFromManip();

	if (attrNames.length() > 0)
		tweenAttrNames(attrNames, mix, animCurveChange);
	
	return MS::kSuccess;
}


MStatus Tweener::tweenCharacter(double &mix, MAnimCurveChange *animCurveChange){
	MString characterName;
	MGlobal::executePythonCommand("maya.cmds.selectionConnection('highlightList', query=True, object=True)", characterName);

	if (characterName.length() > 0){
		MObject character;
		this->getCharacterNode(characterName);

		MFnCharacter fnCharacter;
		MPlugArray attrs;
		fnCharacter.getMemberPlugs(attrs);

		double mixB = 1.0 - mix;
		this->collectAndTweenFnCurves(attrs, mixB, mix, animCurveChange);
	}

	return MS::kSuccess;
}


MStatus Tweener::tweenGraph(double &mix, MAnimCurveChange *animCurveChange){
	MStringArray attrNames;
	MGlobal::executePythonCommand("maya.cmds.keyframe(query=True, name=True)", attrNames);
	
	MSelectionList sel;
	MObject animCurve;
	double mixA = (1.0 - mix);
	
	for (unsigned int i=0; i < attrNames.length(); i++){
		sel.add(attrNames[i]);
		sel.getDependNode(i, animCurve);
		this->tweenPlug(animCurve, mixA, mix, animCurveChange);
	}

	return MS::kSuccess;
}


MObject Tweener::getCharacterNode(MString &name){
	MSelectionList sel;
	sel.add(name);

	MObject character;
	sel.getDependNode(0, character);

	return character;
}


MStatus Tweener::tweenAttrNames(MStringArray &attrNames, double &mix, MAnimCurveChange *animCurveChange){
	MDagPath dagNode;
	double mixA = (1.0 - mix);

	for (unsigned int i=0; i < this->nodes.length(); i++){

		this->nodes.getDagPath(i, dagNode);

		if (!MAnimUtil::isAnimated(dagNode)){
			return MS::kSuccess;
		}
		
		this->fnDepend.setObject(dagNode.node());
		for (unsigned int j=0; j < attrNames.length(); j++){


			this->objArray.setLength(0);
			MAnimUtil::findAnimation(this->fnDepend.findPlug(attrNames[j]), this->objArray);

			for (unsigned int k = 0; k < this->objArray.length(); k++) {
				this->tweenPlug(this->objArray[k], mixA, mix, animCurveChange);
			}

		}
	}

	return MS::kSuccess;
}


MStringArray Tweener::getAttrsFromManip(){
	MString ctx;
	MGlobal::executePythonCommand("maya.cmds.currentCtx()", ctx);
	MStringArray attrNames;

	if (ctx.length() == 0)
		return attrNames;

	else if (ctx == "moveSuperContext") {
		attrNames.append(MString("tx"));
		attrNames.append(MString("ty"));
		attrNames.append(MString("tz"));
	}

	else if (ctx == "RotateSuperContext") {
		attrNames.append(MString("rx"));
		attrNames.append(MString("ry"));
		attrNames.append(MString("rz"));
	}

	else if (ctx == "scaleSuperContext") {
		attrNames.append(MString("sx"));
		attrNames.append(MString("sy"));
		attrNames.append(MString("sz"));
	}

	return attrNames;
}



MStatus Tweener::collectAndTweenFnCurves(MPlugArray &connections, double &mixA, double &mixB, MAnimCurveChange *animCurveChange){
	for (unsigned int i=0; i < connections.length(); i++){
		
		this->objArray.setLength(0);
		MAnimUtil::findAnimation(connections[i], this->objArray);

		for (unsigned int i=0; i < this->objArray.length(); i++)
			this->tweenPlug(this->objArray[i], mixA, mixB, animCurveChange);

	}

	return MS::kSuccess;
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


MStatus Tweener::tweenPlug(MObject &plug, double &mixA, double &mixB, MAnimCurveChange *animCurveChange){
		
	this->fnAnimCurve.setObject(plug);
	
	this->animPlugs.push_back(plug);
	this->animValues.push_back(this->collectKeyValues(fnAnimCurve));

	this->fnAnimCurve.addKey(this->currentTime, this->mixValues(this->animValues.back(), mixA, mixB),
								MFnAnimCurve::kTangentAuto, MFnAnimCurve::kTangentAuto, animCurveChange);
	
	return MS::kSuccess;
}


MStatus Tweener::tweenStoredPlugs(double &mixB){

	double mixA = (1.0 - mixB);
	for (size_t i=0; i < this->animPlugs.size(); i++) {
		
		this->fnAnimCurve.setObject(this->animPlugs[i]);
		this->fnAnimCurve.addKey(this->currentTime, this->mixValues(this->animValues[i], mixA, mixB),
									MFnAnimCurve::kTangentAuto, MFnAnimCurve::kTangentAuto);
	}

	return MS::kSuccess;
}


double Tweener::mixValues(std::array<double, 2> &keyValues, double &mixA, double &mixB){
	return (keyValues[0] * mixA) + (keyValues[1] * mixB);
}









