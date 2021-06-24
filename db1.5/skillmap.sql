USE [GunzDB15]
GO

CREATE TABLE [dbo].[SkillMapTimes]
(	
	[MapID][tinyint] NOT NULL,
	[CID][int] NOT NULL,
	[UserName][varchar](24) NOT NULL,
	[BestTime][INT] NOT NULL
) ON [PRIMARY]
GO

CREATE PROCEDURE [dbo].[spInsertSkillMapTime]
@MapID tinyint,
@CID int,
@UserName varchar(24),
@BestTime INT  /*todo*/
	AS BEGIN
		SET NOCOUNT ON;
		
		INSERT INTO dbo.SkillMapTimes(MapID,CID,UserName,BestTime) VALUES(@MapID,@CID,@UserName,@BestTime)
	END
	
GO

CREATE PROCEDURE [dbo].[spGetSkillMapBestTime]
@MapID tinyint,
@CID int

	AS BEGIN
		SET NOCOUNT ON;
		
		SELECT BestTime FROM dbo.SkillMapTimes WHERE CID = @CID AND MapID = @MapID
	END
GO

CREATE PROCEDURE [dbo.[spUpdateSkillMapTime]
@MAPID tinyint,
@CID int,
@UserName varchar(24),
@BestTime int

	AS BEGIN
	
		SET NOCOUNT ON;
		
		UPDATE dbo.SkillMapTimes SET BestTime = @BestTime WHERE MapID = @MAPID AND CID = @CID
	END
GO