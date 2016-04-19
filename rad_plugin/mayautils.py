import pymel.core as pmc
import maya.OpenMayaUI as OpenMayaUI
from qtshim import *

class undo_on_error(object):
    def __enter__(self):
        pmc.undoInfo(openChunk=True)

    def __exit__(self, exc_type, exc_val, exc_tb):
        pmc.undoInfo(closeChunk=True)
        if exc_val is not None:
            pmc.undo()

def get_maya_window():
    """Returns the QMainWindow for the main Maya window."""
    winptr = OpenMayaUI.MQtUtil.mainWindow()
    if winptr is None:
        raise RuntimeError('No Maya window found.')
    window = wrapinstance(winptr)
    assert isinstance(window, QtGui.QMainWindow)
    return window


def get_main_window_name():
    """Return the QMainWindow for the main Maya window."""
    return pmc.MelGlobals()['gMainWindow']



def uipath_to_qtobject(pathstr):
    """Return the QtObject for a Maya UI path to a control, layout, or menu item. 
    Return None if no item is found."""
    ptr = OpenMayaUI.MQtUtil.findControl(pathstr)
    if ptr is None:
        ptr = OpenMayaUI.MQtUtil.findLayout(pathstr)
    if ptr is None:
        ptr = OpenMayaUI.MQtUtil.findMenuItem(pathstr)
    if ptr is not None:
        ptr = wrapinstance(ptr)
    return ptr
