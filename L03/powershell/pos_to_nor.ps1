### If required call as Administrator:
# Set-ExecutionPolicy -ExecutionPolicy RemoteSigned

$InputLogisimFile = '../logisim/pos_task_1.circ'  
$OutputLogisimFile = '../logisim/nor_task_1.circ' 

$CircFileHeaderSize = 53 # lines

$LogisimFileData = Get-Content $InputLogisimFile | Select-Object -Skip $CircFileHeaderSize
$LogisimFileHeader = Get-Content $InputLogisimFile -Head $CircFileHeaderSize

$LogisimFileData = $LogisimFileData.Replace('OR',  'NOR')     
$LogisimFileData = $LogisimFileData.Replace('NOT', 'NOR')    
$LogisimFileData = $LogisimFileData.Replace('AND', 'NOR')    
$LogisimFileHeader | Out-File -encoding ASCII $OutputLogisimFile  
$LogisimFileData | Out-File -encoding ASCII -Append $OutputLogisimFile  
