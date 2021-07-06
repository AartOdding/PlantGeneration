After building you need to install the correct dll's from qt:

First go into the folder where the executable is located.

On windows run: 
<qt path>/<qt version>/msvc2019_64/bin/windeployqt.exe .

Where you replace <qt path> and <qt version> with the path where you installed qt, and the exact version of qt that you are using.

On other platforms there should be a similarly named deployment application.
