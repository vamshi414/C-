@echo off
for /d %%i in ("C:\RVK\VAMSHI\DN\*") do (
   if exist "%%i\x64Debug\" (
       echo Deleting folder %%i\x64Debug
	   rmdir /s /q "%%i\x64Debug"
   ) else (
       echo Folder %%i\x64Debug\ doest not exist.
 )
 echo all specified fodlers have been deleted.
 pause