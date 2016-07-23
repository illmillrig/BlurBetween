
#include "BlurBetweenCmd.h"
#include <maya/MFnPlugin.h>


MStatus initializePlugin(MObject obj){ 
	MStatus   status;
	MFnPlugin plugin(obj);

	status = plugin.registerCommand("blurTween", BlurBetween::creator, BlurBetween::syntaxCreator);
	
	if (!status){
		status.perror("registerCommand");
		return status;
	}

	return status;
}

MStatus uninitializePlugin(MObject obj){
	MStatus   status;
	MFnPlugin plugin(obj);

	status = plugin.deregisterCommand("blurTween");
	
	if (!status){
		status.perror("deregisterCommand");
		return status;
	}

	return status;
}
