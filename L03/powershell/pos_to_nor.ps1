#
# ******************************************************************************
# * @file    : pos_to_nor.ps
# * @author  : AW           Adrian.Wojcik@put.poznan.pl
# * @author  : ChatGPT      https://chat.openai.com/
# * @version : 1.0
# * @date    : 14-Mar-2022
# * @brief   : Intruction #03: script for converting OR/AND PoS to NOR .circ
# * @note    : If required call as Administrator:
# *            > Set-ExecutionPolicy -ExecutionPolicy RemoteSigned
# *
# ******************************************************************************
#
function Get-SearchStringForGate {
    [CmdletBinding()]
    Param ([Parameter(Mandatory = $true, Position = 0)][string]$GateName)

    return [regex]::Escape('<comp lib="1" loc="(') + '(\d+),(\d+)' + [regex]::Escape(')" name="' + $GateName +' Gate"')
}

# Original input file: 'product of sum' circuit
$InputLogisimFile = '../logisim/pos_task_1.circ'
# Result output file: NOR circuit
$OutputLogisimFile = '../logisim/nor_task_1.circ' 

# Read .circ XML file content
$LogisimFileData = Get-Content $InputLogisimFile 

$ReplaceGateComp = '<comp lib="1" loc="($1,$2)" name="NOR Gate"'

# Replace all 'AND' gates
$SearchGateComp = Get-SearchStringForGate -GateName "AND"
$LogisimFileData = $LogisimFileData -replace $SearchGateComp, $ReplaceGateComp
# Replace all 'OR' gates
$SearchGateComp = Get-SearchStringForGate -GateName "OR"
$LogisimFileData = $LogisimFileData -replace $SearchGateComp, $ReplaceGateComp
# Replace all 'NOT' gates
$SearchGateComp = Get-SearchStringForGate -GateName "NOT"
$LogisimFileData = $LogisimFileData -replace $SearchGateComp, $ReplaceGateComp

# Save result file
$LogisimFileData | Out-File -encoding ASCII $OutputLogisimFile  