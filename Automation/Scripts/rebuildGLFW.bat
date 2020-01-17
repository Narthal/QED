cd ../../Build
mkdir GLFW
cmake ../External\Dependencies\GLFW\

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
cd ../External\Dependencies\GLFW\src
msbuild glfw.vcxproj /p:OutDir=C:\Users\balas\source\GitHubRepos\QED\Build\GLFW\ /p:IntDir=C:\Users\balas\source\GitHubRepos\QED\Build\GLFW\Intermediate\ /p:Configuration=Release /p:Platform=x64

pause