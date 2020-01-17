cd ../../Build
mkdir GLFW
cd ../
External\Tools\cmake-3.16.2-win64-x64\bin\cmake.exe -S External\Dependencies\GLFW\ -B Build\GLFW\

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
cd Build\GLFW\src
msbuild glfw.vcxproj /p:OutDir=C:\Users\balas\source\GitHubRepos\QED\Build\GLFW\ /p:IntDir=C:\Users\balas\source\GitHubRepos\QED\Build\GLFW\Intermediate\ /p:Configuration=Release /p:Platform=x64

pause