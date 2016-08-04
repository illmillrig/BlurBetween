
#include "BlurBetweenUI.h"
#include "BlurBetweenCmd.h"
#include <maya/MFnPlugin.h>


MStatus initializePlugin(MObject obj){ 
	MStatus stat;
	MFnPlugin plugin(obj);

	stat = plugin.registerCommand("blurTween", BlurBetween::creator, BlurBetween::syntaxCreator);
	if (!stat){
		stat.perror("registerCommand");
		return stat;
	}


	stat = plugin.registerCommand("blurTweenUI", BlurTweenUICmd::creator);
	if (!stat){
		stat.perror("registerCommand");
		return stat;
	}

	return stat;
}


MStatus uninitializePlugin(MObject obj){
	MStatus stat;
	MFnPlugin plugin(obj);


	// get rid of any QT ui's
    BlurTweenUICmd::cleanup();


	stat = plugin.deregisterCommand("blurTween");
	if (!stat){
		stat.perror("deregisterCommand");
		return stat;
	}


	stat = plugin.deregisterCommand("blurTweenUI");
	if (!stat){
		stat.perror("deregisterCommand");
		return stat;
	}

	return stat;
}
