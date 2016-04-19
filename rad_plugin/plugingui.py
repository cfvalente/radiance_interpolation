from qtshim import *

_files = []
_NINTERP = 11
_TIMES = []

timeinput = None

class interpolationController(QtCore.QObject):
    filesChanged = Signal(list)
    interpolationResult = Signal(str)


class interpolationWindow(QtGui.QMainWindow):
    fbrowseClicked = Signal()
    interpolateClicked = Signal(list, list, str, int, bool)
    closeClicked = Signal()
    resize = Signal()

    def resizeEvent(self, _):
        self.resize.emit()




def indexToInterpolationType(ind):
    if ind == 0:
        return 'linear', 2, 'Linear Interpolation'
    elif ind == 1:
        return 'quadratic', 3, 'Quadratic Interpolation'
    elif ind == 2:
        return 'lagrange', 2, 'Lagrange Interpolation'
    elif ind == 3:
        return 'ncspline', 3, 'Natural Cubic Spline Interpolation'
    elif ind == 4:
        return 'stirling', 2, 'Stirling Interpolation'
    elif ind == 5:
        return 'gaussforward', 2, 'Gauss Forward Interpolation'
    elif ind == 6:
        return 'gaussbackward', 2, 'Gauss Backward Interpolation'
    elif ind == 7:
        return 'bsplinecub', 4, 'Cubic B-Spline Approximation'
    elif ind == 8:
        return 'bezier', 2, 'Bézier Approximation'
    elif ind == 9:
        return 'bezierquad', 3, 'Quadratic Bézier Approximation'
    elif ind == 10:
        return 'beziercub', 4, 'Cubic Bézier Approximation'


def setTimes(infoinput, useInt):
    global _TIMES
    rows = infoinput.rowCount()
    _TIMES = []
    if useInt:
        for i in range(rows):
            qline = QtGui.QLineEdit()
            qline = infoinput.cellWidget(i, 1)
            _TIMES.append(intInputToNum(qline))
    else:
        for i in range(rows):
            qtime = QtGui.QTimeEdit()
            qtime = infoinput.cellWidget(i, 1)
            total = 60*qtime.time().hour()+qtime.time().minute()
            _TIMES.append(total)


def sortInput():
    """Returns two sorted lists based on the _files and _TIMES vars. Note that sorting is NOT stable. """
    global _files
    global _TIMES
    times_files = zip(_TIMES, _files)
    times_files.sort()
    newFiles = [x for y, x in times_files]
    newTimes = [y for y, x in times_files]
    return newFiles, newTimes

def intInputToNum(timeinput):
    interptime = timeinput.text()
    if interptime == '':
        interptime = '0'
    interptime = interptime.replace(',', '')
    time = int(interptime)
    return time


def intToTime(total):
    hour = int(total/60)
    minute = total%60
    return hour, minute

def timeToInt(qtimeedit):
    return (60*qtimeedit.time().hour()+qtimeedit.time().minute())

def create_window(controller, parent=None):
    global timeinput
    QtCore.QTextCodec.setCodecForCStrings(QtCore.QTextCodec.codecForName('utf8'))
    win = interpolationWindow(parent)
    win.setWindowTitle("HDR Interpolation")
    win.setMinimumWidth(900)
    win.setMinimumHeight(600)

    statusbar = QtGui.QStatusBar()
    container = QtGui.QWidget(win)

    timelabel = QtGui.QLabel('Interpolation Time', container)
    timeinput = QtGui.QTimeEdit(container)
    timeinput.setDisplayFormat('hh:mm')
    timelabel.setMaximumWidth(100)


    infolabel = QtGui.QLabel('Files Selected', container)
    infoinput = QtGui.QTableWidget(container)
    infoinput.setColumnCount(2)
    infoinput.setRowCount(0)
    infolabel.setMaximumWidth(100)

    infoinput.setHorizontalHeaderLabels(['File', 'Time'])
    infolabel.setBuddy(infoinput)
    infoinput.setSelectionMode(QtGui.QAbstractItemView.SelectionMode.SingleSelection)

    substexture = QtGui.QCheckBox('Automatically replace IBL\'s texture', container)
    timeinputoption = QtGui.QCheckBox('Use Integers for time input', container)

    fbrowsebutton  = QtGui.QPushButton('Browse Files', container)
    interpolatebutton  = QtGui.QPushButton('Interpolate HDR Images', container)
    closebutton  = QtGui.QPushButton('Close', container)

    interpolatebutton.setMaximumWidth(200)

    dropdownlabel = QtGui.QLabel('Interpolation Type', container)
    dropdownlabel.setMaximumWidth(100)
    dropdown = QtGui.QComboBox(container)
    for i in range(_NINTERP):
        dropdown.addItem(indexToInterpolationType(i)[2])
    dropdown.setMaxVisibleItems(_NINTERP)
    dropdownlabel.setBuddy(dropdown)

    layout = QtGui.QGridLayout(container)
    layout.setSpacing(10)

    container.setLayout(layout)

    layout.addWidget(timelabel, 2, 0)
    layout.addWidget(timeinput, 2, 1, 1, 4, 0)

    layout.addWidget(infolabel, 0, 0)
    layout.addWidget(infoinput, 0, 1, 1, 4, 0)

    layout.addWidget(substexture, 4, 1)
    layout.addWidget(fbrowsebutton, 1, 1, 1, 4, 0)
    layout.addWidget(timeinputoption, 4, 2)

    layout.addWidget(dropdownlabel, 3, 0)
    layout.addWidget(dropdown, 3, 1, 1, 4, 0)

    closebutton.setMaximumWidth(200)
    layout.addWidget(closebutton, 4, 4)
    layout.addWidget(interpolatebutton, 4, 3)

    win.setCentralWidget(container)
    win.setStatusBar(statusbar)


    def getInputTime():
        if timeinputoption.isChecked():
            return intInputToNum(timeinput)
        else:
            return (60*timeinput.time().hour()+timeinput.time().minute())



    def onTimeFormatChange():
        global timeinput
        rows = infoinput.rowCount()
        if not timeinputoption.isChecked():
            total = intInputToNum(timeinput)
        else:
            total = (60*timeinput.time().hour()+timeinput.time().minute())
        layout.removeWidget(timeinput)
        timeinput.close()
        timeinput = None
        if timeinputoption.isChecked():
            timeinput = QtGui.QLineEdit(container)
            timeinput.setValidator(QtGui.QIntValidator())
            timeinput.setText(repr(total))

            for i in range(rows):
                qtime = QtGui.QTimeEdit()
                qtime = infoinput.cellWidget(i, 1)
                total = timeToInt(qtime)
                qline = QtGui.QLineEdit()
                qline.setValidator(QtGui.QIntValidator())
                qline.setText(repr(total))
                infoinput.removeCellWidget(i, 1)
                qtime.close()
                infoinput.setCellWidget(i, 1, qline)
        else:
            timeinput = QtGui.QTimeEdit(container)
            timeinput.setDisplayFormat('hh:mm')
            hour, minute = intToTime(total)
            timeinput.setTime(QtCore.QTime(hour, minute, 0, 0))

            for i in range(rows):
                qline = QtGui.QLineEdit()
                qline = infoinput.cellWidget(i, 1)
                total = intInputToNum(qline)
                qtime = QtGui.QTimeEdit()
                qtime.setDisplayFormat('hh:mm')
                hour, minute = intToTime(total)
                qtime.setTime(QtCore.QTime(hour, minute, 0, 0))
                infoinput.removeCellWidget(i, 1)
                qline.close()
                infoinput.setCellWidget(i, 1, qtime)


        layout.addWidget(timeinput, 2, 1, 1, 4, 0)
        return
    timeinputoption.stateChanged.connect(onTimeFormatChange)


    def resizeFunc(): 
        total = win.width()-200
        infoinput.setColumnWidth(0, total-50)
        infoinput.horizontalHeader().setStretchLastSection(True);
    win.resize.connect(resizeFunc)


    
    def onbrowseClick():
        win.fbrowseClicked.emit()
    fbrowsebutton.clicked.connect(onbrowseClick)

    

    def oncancelClick():
        win.hide()
        win.closeClicked.emit()
    closebutton.clicked.connect(oncancelClick)


    
    def oninterpolateClick():
        setTimes(infoinput, timeinputoption.isChecked())
        newFiles, newTimes = sortInput()
        time = getInputTime()
        if time >= newTimes[0] and time <= newTimes[len(newTimes)-1]:
            statusbar.showMessage('')
            win.interpolateClicked.emit(newFiles, newTimes, indexToInterpolationType(dropdown.currentIndex())[0], time, substexture.isChecked())
        else:
            if timeinputoption.isChecked():
               statusbar.showMessage('Interpolation Time should be greater than or equal to '+repr(newTimes[0])+' and lesser than or equal to '+repr(newTimes[len(newTimes)-1]))
            else:
                hour_0 = '%02d' %int(newTimes[0]/60)
                minute_0 = '%02d' %(newTimes[0]%60)
                hour_n = '%02d' %int(newTimes[len(newTimes)-1]/60)
                minute_n = '%02d' %(newTimes[len(newTimes)-1]%60)
                statusbar.showMessage('Interpolation Time should be greater than or equal to '+hour_0+':'+minute_0+' and lesser than or equal to '+hour_n+':'+minute_n)
    interpolatebutton.clicked.connect(oninterpolateClick)



    def updateFilesList(flist):
        global _files
        _files = flist
        ondropdownChange()
        infoinput.clear()
        infoinput.setRowCount(len(flist))
        infoinput.setHorizontalHeaderLabels(['File', 'Time'])

        for i in range(len(_files)):
            file = QtGui.QTableWidgetItem()
            file.setFlags(QtCore.Qt.ItemIsEditable)
            file.setText(_files[i])

            if timeinputoption.isChecked():
                time = QtGui.QLineEdit()
                time.setValidator(QtGui.QIntValidator())
                time.setText('0')
            else:
                time = QtGui.QTimeEdit()
                time.setDisplayFormat('hh:mm')

            infoinput.setItem(i, 0, file)
            infoinput.setCellWidget(i, 1, time)
    controller.filesChanged.connect(updateFilesList)

    def interpolationResult(res):
        statusbar.showMessage(res)
    controller.interpolationResult.connect(interpolationResult)



    def ondropdownChange():
        global _files
        minimages, interpname = indexToInterpolationType(dropdown.currentIndex())[1:3]
        if _files is None:
            interpolatebutton.setDisabled(True)
            statusbar.showMessage(interpname+' requires at least '+repr(minimages)+' HDR images.')
        elif len(_files) < minimages:
            interpolatebutton.setDisabled(True)
            statusbar.showMessage(interpname+' requires at least '+repr(minimages)+' HDR images.')
        else:
            interpolatebutton.setDisabled(False)
            statusbar.showMessage('')
    dropdown.currentIndexChanged.connect(ondropdownChange)
    ondropdownChange()



    return win



def _py_test():
    import random
    controller = interpolationController()

    app = QtGui.QApplication([])
    win = create_window(controller)
    win.show()
    app.exit(app.exec_())


if __name__ == '__main__':
    _py_test()

