cd ../../../Build
mkdir SQLite
cd ../
External\Tools\cmake-3.16.2-win64-x64\bin\cmake.exe -S External\Vendor\SQLiteAmalgamation\ -B Build\SQLite\ -DUSE_MSVC_RUNTIME_LIBRARY_DLL=ON  -DCMAKE_BUILD_TYPE=Debug -DSQLITE_THREADSAFE=1

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
cd Build\SQLite
REM msbuild ALL_BUILD.vcxproj /p:OutDir=C:\Users\balas\source\GitHubRepos\QED\Build\GLFW\ /p:IntDir=C:\Users\balas\source\GitHubRepos\QED\Build\GLFW\Intermediate\ /p:Configuration=Debug /p:Platform=x64
REM set _CL_=/MT
msbuild ALL_BUILD.vcxproj
pause