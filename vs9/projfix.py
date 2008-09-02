#!/usr/bin/python

import os
import re

print "Mangling project files for older Visual Studio versions"

versions = [ ['8.00', 'vs8'],
             ['7.10', 'vs7'] ]

for version in versions:
  number = version[0]
  subdir = version[1]

  print "  version %s in ..\%s" % (number, subdir)

  projects = [p for p in os.listdir('.') if re.search('vcproj$', p)]
  for project in projects:
    newproject = "..\%s\%s" % (subdir, project)
    print "    %s -> %s " % (project, newproject)

    p = open(project)
    np = open(newproject, 'w')
   
    for l in p.readlines():
      if re.search("TargetFrameworkVersion", l):
        continue
      if re.search("Version=", l):
        l = l.replace('9.00', number)
      np.write(l)
    np.close()
    p.close()
