import os
import shutil

curDir= ''
simDir = os.path.join (curDir, 'simulations')

fileNames = []
for name in os.listdir (curDir):
    path = os.path.join (curDir, name)
    if os.path.isfile (path):
        fileNames.append (name)

dirNames = []
for name in os.listdir (simDir):
    if os.path.isdir (os.path.join ('simulations', name)):
        dirNames.append (name)

print ()        
    
print ('fileNames:')
for fileName in fileNames:
    print (fileName)
print ()
    
print ('dirNames:')
for dirName in dirNames:
    print (dirName)
print ()
            
for fileName in fileNames:
    for dirName in dirNames:        
        if fileName == 'rename.ino':
            targetFileName = dirName + '.ino'
        else:
            targetFileName = fileName
              
        targetPath = os.path.join ('simulations', dirName, targetFileName)
              
        print ('copyfile', fileName, targetPath)
        shutil.copyfile (fileName, targetPath)

            
      
    
    