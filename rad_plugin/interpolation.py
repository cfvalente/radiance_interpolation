import plugingui as gui
import mayautils
import pymel.core as pmc
import sys, string, os, inspect
import maya.cmds as cmds


_window = None
_cont = None
_files = None
_EXECNAME = 'interpolation.exe'
_ARGSFILE = 'argsforhdrinterp.txt'
_menu = None
_menuItems = []


def getmainwindow():
    parent = None
    try:
        parent = mayautils.get_maya_window()
    except RuntimeError as error:
        if (error.message != 'No Maya window found.'):
            raise error
    return parent

def getFiles():
    global _files
    global _cont
    f = pmc.system.fileDialog2(fm=4, cap='HDR File Selection', ff='*.tif', okc='Open')
    if f is not None:
        if _files is not None:
            if set(f) == set(_files):
                return
        f.sort()
        _files = f
        _cont.filesChanged.emit(_files)


def replaceSeparators(str):
    newStr = str.replace('/', os.sep)
    newStr = newStr.replace('\\', os.sep)
    return newStr

def createArgFile(interptype, interptime):
    return

def interpolate(files, times, interptype, interptime, subsTexture):
    global _cont

    currentpath = __file__
    currentpath = currentpath.replace('\\interpolation.pyc', '')
    currentpath = currentpath.replace('/interpolation.pyc', '')
    currentpath = currentpath.replace('\\interpolation.py', '')
    currentpath = currentpath.replace('/interpolation.py', '')
    proj_folder = cmds.workspace(q=True, rd=True)
    hdrfolder = replaceSeparators(proj_folder+'HDR')+os.sep
    args = proj_folder+_ARGSFILE
    args = replaceSeparators(args)
    exe = '"'+currentpath+os.sep+_EXECNAME+'"'
    exe = replaceSeparators(exe)
    exe = '"'+exe+' '+'"'+args+'"'+'"'


    if not os.path.exists(hdrfolder):
        os.makedirs(hdrfolder)
    try:
        fargs = open(args, 'w')
        fargs.write('interpolate '+'"'+hdrfolder+'"'+os.linesep)
        fargs.write('1 '+repr(interptime)+os.linesep)
        fargs.write(interptype+os.linesep)
        for i in range(len(files)):
            fargs.write('"'+replaceSeparators(files[i])+'"'+' '+repr(times[i])+os.linesep)
        fargs.close()
        
        if os.system(exe) != 0:
            _cont.interpolationResult.emit('Error. Unexpected result from: '+exe)
            return
        
        os.remove(args)
        if subsTexture:
            with mayautils.undo_on_error():
                out = hdrfolder+interptype+repr(interptime)+'.tif'

                if os.path.isfile(out) == False:
                    _cont.interpolationResult.emit('Error. Could not find output HDR image: '+out)
                    return

                list = pmc.ls(type='mentalrayIblShape')
                if len(list) > 0:
                    ibl = list[0]
                    name = ibl.name()
                    cmds.setAttr(name+'.type', 0)
                    cmds.setAttr(name+'.tx', out, type="string")
                else:
                    _cont.interpolationResult.emit('No IBL node found. Please create a new IBL node and try again.')
                    return

        _cont.interpolationResult.emit('Done.')

    except IOError as error:
        _cont.interpolationResult.emit('Could not create argument file: '+args+'.')
        print error.message
    return

def show(_):
    global _window
    global _cont
    if _window is None:
        _cont = gui.interpolationController()
        parent = getmainwindow()
        _window = gui.create_window(_cont, parent)
        _window.fbrowseClicked.connect(getFiles)
        _window.interpolateClicked.connect(interpolate)
    _window.show()


def addmenu():
    global _menu
    global _menuItems
    with mayautils.undo_on_error():
        _menu = pmc.menu('HDR Interpolation', parent=mayautils.get_main_window_name())
        item = pmc.menuItem(parent=_menu, label='Show Menu', command=show)
        _menuItems.append(item)


def clean():
    global _menu
    global _menuItems
    global _window
    global _cont
    global _files

    with mayautils.undo_on_error():
        _window.hide()
        for item in _menuItems:
            pmc.deleteUI(item)
        pmc.deleteUI(_menu)

        _window = None
        _cont = None
        _files = None
        _menu = None
        _menuItems = []
