'''
====== Legal notices

Copyright 2017 Jacques de Hooge, GEATEC engineering, www.geatec.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
'''

import os
import shutil

fileNames = []
for name in os.listdir ():
    if os.path.isfile (name):
        fileNames.append (name)

dirNames = []
for name in os.listdir ('simulations'):
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
    if fileName == 'build.py':
        continue
        
    for dirName in dirNames:        
        if fileName == 'rename.ino':
            targetFileName = dirName + '.ino'
        else:
            targetFileName = fileName
              
        targetPath = os.path.join ('simulations', dirName, targetFileName)
              
        print ('Copying', fileName, 'to', targetPath)
        shutil.copyfile (fileName, targetPath)
        
for dirName in dirNames:
    os.chdir (os.path.join ('simulations', dirName))
    os.system ('compile')
    os.chdir (os.path.join ('..', '..'))