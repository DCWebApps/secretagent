# SecretAgent

SecretAgent is a launcher for the Windows [JetBrains TeamCity](https://www.jetbrains.com/teamcity/) build agent.

## Installation

Binary distributions can be found under releases on the [github releases](https://github.com/fizzyade/secretagent/releases) page.

- **Windows**.  The application is supplied as an installer executable, download and run the installer to install the application, this will create a shortcut in the start menu which can be used to launch the software.

### General Information

By default, installing the TeamCity build agent on windows you have the option to run it as either:

- as a service
- as a task

When running as a service, there may be issues that require you to run the software as a task.  When running the software as a task, the start script spawns a terminal which remains open while the agent is running.  This means you have a terminal window always appearing in your Task Bar and cluttering up this.

SecretAgent can be used to launch the build agent instead, it requires the build agent be stored in the default location (C:\BuildAgent) and it directly launches the java application and redirects the console to itself, this means that a separate console is not spawned.  SecretAgent provides a Notifcation area icon which can be used to open the console output from the build agent.  When minimising or closing the console window, the window is hidden, the application does not close so remains running.  To quit the application you should right click on the icon in the notification area and select the Quit option from the menu.

### Notes

This may require tweaking from time to time to accomodate changes with the launch script.  In addition, if you are using a different location for the build agent then you will need to rebuild the application from source and make any necessary changes.

# Credits

The following third party libraries/assets/tools/services have been used in the development of SecretAgent.

- [Qt](https://www.qt.io/download) - cross platform framework, licensed under the [GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html).
- [TeamCity](https://www.jetbrains.com/teamcity/) - CI plaform.
- [cmake](www.cmake.org) - cross platform project build system, licensed under [BSD license](https://gitlab.kitware.com/cmake/cmake/raw/master/Copyright.txt).


In addition, the following commercially licensed tools/services have also been used.

- [SmartCard Tools](https://www.mgtek.com/smartcard) - code signing tool, allows automation of signing using a smartcard token.
- [Certum Code Signing Certificate](https://en.sklep.certum.pl/data-safety/code-signing-certificates/open-source-code-signing-1022.html) - open source code signing certificate for signing Windows binaries.
- [AdvancedInstaller](https://www.advancedinstaller.com/) - Installer creator for windows, license kindly provided by them for free.
- [Affinity Designer](https://www.serif.com/designer) - Vector artwork design application.
- [Affinity Photo](https://www.serif.com/photo) - Bitmap artwork design application.

# License

This project is open source and is released under the GPLv3 License

Distributed as-is; no warranty is given.

