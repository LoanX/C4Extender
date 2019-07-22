USE [lin2world]
GO
/****** Object:  StoredProcedure [dbo].[lin_GetContributionWinnerPledge]    Script Date: 09/22/2010 16:24:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER PROCEDURE [dbo].[lin_GetContributionWinnerPledge]
(
	@agit_id		int,
	@register_only	int
)
AS
SET NOCOUNT ON

IF @register_only = 0	-- not siege agit
BEGIN
SELECT 
	p.pledge_id 
FROM 
	pledge p (nolock) , 
	pledge_contribution pc (nolock)  
WHERE 
	p.pledge_id = pc.pledge_id 
	AND (p.agit_id = @agit_id OR p.agit_id = 0)
	AND p.skill_level >= 4 
	AND pc.residence_id = @agit_id
ORDER BY 
	pc.contribution DESC
END
ELSE			-- siege agit
BEGIN
SELECT 
	p.pledge_id 
FROM 
	pledge p (nolock) , 
	pledge_contribution pc (nolock)  
WHERE 
	p.pledge_id = pc.pledge_id 
	AND (p.agit_id = @agit_id OR p.agit_id = 0 OR @agit_id = 34 OR @agit_id = 20)	--34 devastated castle, 20 - Fortress of the dead
	AND p.skill_level >= 4 
	AND pc.residence_id = @agit_id
	AND p.pledge_id IN (SELECT pledge_id FROM siege_agit_pledge WHERE agit_id = @agit_id)
ORDER BY 
	pc.contribution DESC
END
