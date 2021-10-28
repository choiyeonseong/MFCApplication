cd /d "D:\repository\MFCApplication\NewCom" &msbuild "NewCom.vcxproj" /t:sdvViewer /p:configuration="Debug" /p:platform=Win32
exit %errorlevel% 