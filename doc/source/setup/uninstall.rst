Uninstall
=========

To remove Mango from your system, follow the steps appropriate to your
platform.


Linux
-----

To remove a particular version of Mango, delete the folder

  */opt/mango/<version>/*

You should also make sure that */usr/local/bin/mango* does not point
to a binary in that version.

If you wish to remove all versions of Mango, delete the following
folder and symbolic link:

  |  */opt/mango*
  |  */usr/local/bin/mango*


OSX
---

If you wish to remove a particular version of Mango, delete the folder

  */Library/Frameworks/Mango.framework/Versions/<version>/*

In this case you may wish to make sure symbolic link *Current* that
resides in the same folder does not point to the version removed.

If you wish to remove all versions of Mango, delete the following
folder and symbolic link:

  | */Library/Frameworks/Mango.framework/*
  | */usr/bin/mango*

Admin permissions may be required to remove these files.


Windows
-------

Before removing a particular version of Mango, backup any files not
originally belonging to the installation such as extra scripts or
modules places in the *script* directory:

  *C:\\Program Files\\Mango\\<version>\\script\\*

Next, run the uninstaller for that version which can found in the
"Mango-<version>" entry in the Start menu.

The uninstaller will remove all installation files, the start-menu
entry, and the association with *.py* files. It is designed to leave
files not belonging to the installation alone, so the folder
*C:\\Program Files\\Mango\\<version>* might not be completely removed. It
is safe to manually remove this folder.