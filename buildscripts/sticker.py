#!/usr/bin/env python3
##
# Parse out a string array to be compiled into an executable for revision
# history
#
# @author Stuart W. Baker
# @data 28 April 2018

from optparse import OptionParser
import subprocess
import os
import time
import platform
import getpass
import filecmp

f_null = open(os.devnull, "w")

usage = "usage: %prog [options]\n\n" + \
        "  %prog -i $(APP_PATH) -o revisions.cxxout\n"

parser = OptionParser(usage=usage)
parser.add_option("-o", "--output", dest="output", metavar="FILE",
                  default="Sticker.out",
                  help="generated output file")
parser.add_option("-i", "--input", dest="input", metavar="FILE",
                  default=None,
                  help="space seperated list of repository root paths")
parser.add_option("-d", "--dirty", dest="dirty", action="store_true",
                  default=False,
                  help="add the \"dirty\" suffix: -d")
parser.add_option("-u", "--untracked", dest="untracked", action="store_true",
                  default=False,
                  help="add the \"untracked files\" suffix: -u")
parser.add_option("-g", "--gcc", dest="gcc", metavar="`gcc -dumpversion`",
                  default=None,
                  help="add the GNU GCC version")
parser.add_option("-t", "--time", dest="date", action="store_true",
                  default=False,
                  help="add the date/time to the output")
parser.add_option("-b", "--build", dest="buildflags", 
                  default="",
                  help="Build flags")

(options, args) = parser.parse_args()

if (options.input == None) :
    parser.error('missing parameter -i')

print(options.input)

options.input = options.input.replace('  ', ' ')
inputs = options.input.split(" ")

orig_dir = os.path.abspath('./')
output = ""

# add data/time
if options.date :
    now = time.strftime("%a, %d %b %Y %H:%M:%S %Z")
    output += now + '\n'

# add GCC version
if options.gcc != None :
    options.gcc = options.gcc.replace('.', '-')
    gcc = 'gcc-' + options.gcc
    output += gcc + '\n'

main_git_hash = None
    
for x in inputs :
    print(x)
    # go into the root of the repo
    os.chdir(orig_dir)
    os.chdir(x)

    # get the short hash
    git_hash = subprocess.check_output(['git', 'rev-parse', '--short', 'HEAD'])
    git_hash = str(git_hash[:7])

    # get the dirty flag
    dirty = os.system('git diff --quiet')

    # get the untracked flag
    untracked_files = subprocess.check_output(['git', 'status', '-u', '-s'])
    untracked_files = untracked_files.splitlines()
    untracked = False
    for y in untracked_files :
        if y[0] == '?':
            untracked = True
            break

    # format the output
    output += git_hash + ':' + os.path.split(os.path.abspath(x))[1]

    hashopts = ""
    
    if dirty or untracked :
        hashopts += ':'
    if dirty :
        hashopts += '-d'
    if untracked :
        hashopts += '-u'
    output += hashopts + '\n'

    if main_git_hash is None:
        main_git_hash = git_hash + hashopts


os.chdir(orig_dir)

for x in os.listdir("../../../managed_components") :
    comp=os.path.join("../../../managed_components",x)
    if not os.path.isdir(comp): 
        continue
    if not os.path.exists(os.path.join(comp,'.component_hash')) :
        continue
    print(comp)
    f = open(os.path.join(comp,'.component_hash'),'r')
    git_hash = f.readline()
    f.close()
    # format the output
    output += git_hash + ':' + os.path.split(os.path.abspath(comp))[1]
    output +=  '\n' 
        
output += options.buildflags + "\n"
output = output[:-1]

os.chdir(orig_dir)

# generate the *.cxxout style content

# generate the *.hxxout file
output_file = open(options.output, 'w')
output_file.write(output)
output_file.close()

f_null.close()
