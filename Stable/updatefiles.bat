@rem -----------------------------
@rem �ҽ� �޾ƿ���
@rem -----------------------------
@CALL Utils\bin\setenv

svn update 

@rem -----------------------------
@rem ���ҽ� ��������
@rem -----------------------------

SET SSDIR=\\Builder\ArtWorks

@cd "Gunz\XML"
%SourceSafe% CP $/XML
%SourceSafe% GET * -R -I- 
@cd "..\.."

@cd "Gunz\Runtime"
%SourceSafe% CP $/Runtime
%SourceSafe% GET * -R -I-

@cd "..\.."
