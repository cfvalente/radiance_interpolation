import sys
import maya.OpenMaya as OpenMaya
import maya.OpenMayaMPx as OpenMayaMPx
from maya import cmds
import interpolation

kPluginCmdName = "HDRInterpolation"


# Command
class scriptedCommand(OpenMayaMPx.MPxCommand):
    def __init__(self):
        OpenMayaMPx.MPxCommand.__init__(self)
        

    # Invoked when the command is run.
    def doIt(self,argList):
        interpolation.show()



# function that returns a node object given a name
def nameToNode( name ):
    selectionList = OpenMaya.MSelectionList()
    selectionList.add( name )
    node = OpenMaya.MObject()
    selectionList.getDependNode( 0, node )
    return node

# Creator
def cmdCreator():
    return OpenMayaMPx.asMPxPtr( scriptedCommand() )
    
# Initialize the script plug-in
def initializePlugin(mobject):
    mplugin = OpenMayaMPx.MFnPlugin(mobject)
    def register():
        try:
            mplugin.registerCommand( kPluginCmdName, cmdCreator )
            interpolation.addmenu()
        except:
            sys.stderr.write( "Failed to register command: %s\n" % kPluginCmdName )
            raise
    cmds.evalDeferred(register)

# Uninitialize the script plug-in
def uninitializePlugin(mobject):
    mplugin = OpenMayaMPx.MFnPlugin(mobject)
    try:
        mplugin.deregisterCommand( kPluginCmdName )
        interpolation.clean()
    except:
        sys.stderr.write( "Failed to unregister command: %s\n" % kPluginCmdName )
