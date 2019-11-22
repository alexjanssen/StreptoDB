SELECT 
'1. Total count Images:',
Count(IMAGE_ID)
FROM Images
UNION
SELECT 
'2. Count Test-Strains:',
Count('STRAIN_ID')
FROM 'Test_Strains'
UNION
SELECT 
'3. Count Inhibition-Listings:',
Count('STRAIN-INHIBITS_ID')
FROM 'Strain-Inhibits'
UNION
SELECT 
'4. Count Positive-Inhibitions:',
SUM(INHIBITION_BOOL)
FROM 'Strain-Inhibits'
UNION
SELECT 
'5. Count Negative-Inhibitions:',
SUM(NOT INHIBITION_BOOL)
FROM 'Strain-Inhibits';