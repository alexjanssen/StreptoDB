SELECT 
TS.STRAIN_NAME || ' ',
TS.STRAIN_ID,
COUNT(SI.IMAGE_ID),
CASE WHEN SUM(SI.INHIBITION_BOOL) IS NULL THEN '0' ELSE SUM(SI.INHIBITION_BOOL) END,
CASE WHEN SUM(NOT SI.INHIBITION_BOOL) IS NULL THEN '0' ELSE SUM(NOT SI.INHIBITION_BOOL) END
FROM Test_Strains TS
LEFT JOIN 'Strain-Inhibits' SI
ON TS.STRAIN_ID = SI.STRAIN_ID
GROUP BY TS.STRAIN_ID 
UNION
SELECT
'Name:',
'        ID:',
'Count:',
'Pos-:',
'Neg-Inhibitions:'
FROM Test_Strains
ORDER BY TS.STRAIN_ID DESC;