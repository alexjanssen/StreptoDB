SELECT 
'1. Total count Groups:',
Count(ID_GROUP)
FROM Streptomyceten
UNION
SELECT 
'2. Count Siderophore:',
SUM(SIDEROPHORE_BOOL)
FROM Streptomyceten;