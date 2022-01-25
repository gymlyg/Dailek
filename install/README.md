Trying to create installator using the following instructions:
https://doc.qt.io/qtinstallerframework/ifw-tutorial.html
https://doc.qt.io/qtinstallerframework/ifw-component-description.html

Do following steps to get installer under windows:
1) copy releas exe file into the <data dir> (packages\...\data\)
2) run <qt bin path>\windeployqt <data dir>\<binary name>
3) run <QtInstallerFramework bin path>\binarycreator -c config/config.xml -p packages installer