<%
	' -----------------------------
	' CONFIG.ASP
	' Ranking Server Database Setup	
	' -----------------------------
	Dim strDBHost
	Dim strDBUser
	Dim strDBPass
	
	Dim nUsersPerPage
	Dim nBlockPage
	Dim strWidth
	
	Dim strPrev
	Dim strNext
	Dim strRank
	Dim strChar
	Dim strLevel
	Dim strKillCount
	Dim strFirst
	Dim strLast
	Dim strPage
	
	Dim strSearchID
	Dim strSearchName
	Dim strSearchButton
	Dim strSearchCancel
	
	' -----------------------------
	' MAJOR CONFIGURATION
	' -----------------------------
		
	strDBHost = ""    ' ���ĳ����ÿ�
	strDBUser = ""        ' ���ĳ����ÿ�
	strDBPass = ""    ' ���ĳ����ÿ�
		
	' -----------------------------
	' STYLE CONFIGURATION(Option)
	'    -- NOT IMPORTANT --
	' -----------------------------
	
	nUsersPerPage = 20	' How many users will you show in a page?
	nBlockPage = 10		' How many page numbers will you show in a page?
	strWidth = "90%"	' Table Size

	' -----------------------------
	' LOCALIZATION (Default:Korean)
	' -----------------------------
	strRank = "��ŷ"
	strChar = "ĳ����"
	strLevel = "����"
	strPrev = "����"
	strNext = "����"
	strFirst = "ó��"	
	strLast = "������"
	strKillCount = "�¼�"	
	strPage = "������"
	
	strSearchID = "���̵�"
	strSearchName = "ĳ����"
	strSearchButton = "ã��"
	strSearchCancel = "���"
%>
