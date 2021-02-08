#!/bin/bash
ScriptPath=tools/GENie
if ! [ -f ./$ScriptPath/genie.exe ];
then wget https://github.com/bkaradzic/bx/raw/master/tools/bin/windows/genie.exe --directory-prefix=$ScriptPath
fi
chmod +x ./$ScriptPath/genie.exe
./$ScriptPath/genie.exe $1


