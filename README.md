# MindMatrix

# KdMapper
KDMapper is a simple tool that exploits iqvw64e.sys Intel driver to manually map non-signed drivers in memory 

Original creator https://github.com/z175

Updated and improved by https://github.com/TheCruZ

Mdl allocation writed by https://github.com/TygoL

Independent Pages allocation written by https://github.com/Herooyyy/

Tested from Windows 10 1607 to Windows 11 22449.1 ✔️

Update mainly done for UnknownCheats Forum https://www.unknowncheats.me/forum/members/1117395.html

KDMapper is a simple tool that exploits iqvw64e.sys Intel driver to manually map non-signed drivers in memory

Note: Add definition DISABLE_OUTPUT to remove all console outputs

Note: Can be recommended like in the past set a custom entry point like in the HelloWorld example to reduce the generated code in the binary

--- Parameters
Just as reminder, in driver entry, DriverObject and RegistryPath are NULL unless you specify anything! this is a manual mapped driver and not a normal loading procedure
Errors 0xC0000022 and 0xC000009A:

A lot of people ask me about this errors loading the vulnerable driver, both are caused by FACEIT AC since his driver is always running you have to uninstall it
Error 0xC0000603:

The certificate has been blocked as vulnerable and the mapper will return a status of STATUS_IMAGE_CERT_REVOKED. More info at Microsoft

If you want to disable your vulnerable driver list you have to open regedit.exe, go to HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\CI\Config and set 'VulnerableDriverBlocklistEnable' as dword with value 0 and restart to apply the changes

Have Fun!!
TODO just maybe interesting ideas

if anyone interested in create a pull request

Self cleaning of self execution ?

    Registry User Assist
    Prefetch (need to be deleted normally after it's update)
    Recent files and AutomaticDestination
    Registry RecentDocs
    USN journal maybe?
    Self deletion option?
    Loaded driver deletion option?
    SRUM may contain any information?
    Shellbags in kdmapper named folders?

Messages for common loading errors?
