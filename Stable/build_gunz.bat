@rem -----------------------------
@rem ȯ�� ���� ����
@rem -----------------------------
@CALL Utils\bin\setenv

@cd Utils\bin
@call _getdatetime.bat datetime
@cd ..\..
if "%datetime%" == "" GOTO ERROR


@rem -----------------------------
@rem Clear
@rem -----------------------------
del "Gunz\Runtime\Gunz.exe"
del "Gunz\Runtime\Gunz.pdb"


@rem -----------------------------
@rem �ҽ�, ���ҽ��� �޾ƿ´�.
@rem -----------------------------
CALL updatefiles

@rem -----------------------------
@rem ������
@rem -----------------------------

%DEVENV% "Gunz\Gunz.sln" /rebuild Release_publish /out "Gunz\Runtime\build.log"


@rem -----------------------------
@rem ddsgen ����
@rem ------------------------------

@cd "Gunz\Runtime"

CALL Delete_DDS
CALL ddsgen

CALL copy_share


@rem -----------------------------
@rem publish ����
@rem ------------------------------

if "%1" == "" goto :no_target
if "%datetime%" == "" goto :no_target
SET build_target=\\Databank\TeamWorks\Gunz\BuildClient\!Daily\Gunz_%datetime%\


:no_target


CALL publish kor %build_target%

@cd "..\.."


GOTO END


:ERROR
echo ���� ����
pause
exit

:END
