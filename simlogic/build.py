import os
import shutil

fileNames = []
dirNames = []
for name in os.listdir (os.getcwd  ()):
    if os.path.isfile (name):
        dirNames.append (name)
    else:
        fileNames.append (name)
        
for fileName in fileNames:
    for dirName in dirNames:
        if fileName.endswith ('*.ino'):
            shutil.copyfile (fileName, dirName + '\\' + 'ino')
        else:
            shutil.copyfile (fileName, dirName)
        
      
    
    