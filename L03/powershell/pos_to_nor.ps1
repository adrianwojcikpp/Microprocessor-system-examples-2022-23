#
# ******************************************************************************
# * @file    : pos_to_nor.ps
# * @author  : AW           Adrian.Wojcik@put.poznan.pl
# * @author  : ChatGPT      https://chat.openai.com/
# * @version : 2.0
# * @date    : 18-Mar-2024
# * @brief   : Intruction #03: script for converting OR/AND PoS to NOR .circ
# * @note    : If required call as Administrator:
# *            > Set-ExecutionPolicy -ExecutionPolicy RemoteSigned
# *
# ******************************************************************************
#

# Original input file: 'product of sum' circuit
$InputLogisimFile = '../logisim/pos_task_1.circ'
# Result output file: NOR circuit
$OutputLogisimFile = '../logisim/nor_task_1.circ'

# Read .circ XML file content
$LogisimFileData = Get-Content $InputLogisimFile 

## AND / OR gates **************************************************************

# Search pattern for gate component
function Get-SearchStringForGate {
    [CmdletBinding()]
    Param ([Parameter(Mandatory = $true, Position = 0)][string]$GateName)

    return [regex]::Escape('<comp lib="1" loc="(') + '(\d+),(\d+)' + [regex]::Escape(')" name="' + $GateName +' Gate">')
}

# Match group logic for gate component
$ReplaceGateComp = {
    param($match)
    # Move gates 10 units rigth because of added negation at output
    $x = [int]$match.Groups[1].Value + 10
    $y = [int]$match.Groups[2].Value
    return '<comp lib="1" loc="(' + $x + ',' + $y + ')" name="NOR Gate">'
}

# Replace all 'AND' gates
$SearchGateComp = Get-SearchStringForGate -GateName "AND"
$LogisimFileData = [regex]::Replace($LogisimFileData, $SearchGateComp, $ReplaceGateComp)

# Replace all 'OR' gates
$SearchGateComp = Get-SearchStringForGate -GateName "OR"
$LogisimFileData = [regex]::Replace($LogisimFileData, $SearchGateComp, $ReplaceGateComp)

## Inverters  ******************************************************************

# Search pattern for inverter component
function Get-SearchStringForInverter {
    return [regex]::Escape('<comp lib="1" loc="(') + '(\d+),(\d+)' + [regex]::Escape(')" name="NOT Gate"/>')
}

# Match group logic for inverter component
$ReplaceGateComp = {
    param($match)
    $x = [int]$match.Groups[1].Value
    $y = [int]$match.Groups[2].Value

    # Additionnal wire
    $from_x = [int]$match.Groups[1].Value - 40
    $from_y = [int]$match.Groups[2].Value
    $to_x = [int]$match.Groups[1].Value - 40
    $to_y = [int]$match.Groups[2].Value + 10

    return '<wire from="(' + $from_x + ','+ $from_y + ')" to="(' + $to_x + ','+ $to_y + ')"/>' + "`r`n" + '<comp lib="1" loc="(' + $x + ','+ $y + ')" name="NOR Gate">' + "`r`n`t" + '<a name="size" val="30"/>' + "`r`n" + '</comp>'
}

# Replace all 'NOT' gates
$SearchGateComp = Get-SearchStringForInverter 
$LogisimFileData = [regex]::Replace($LogisimFileData, $SearchGateComp, $ReplaceGateComp)

# Add newlines 
$LogisimFileData = [regex]::Replace($LogisimFileData, '     ', "`r`n")

# Save result file
$LogisimFileData | Out-File -encoding ASCII $OutputLogisimFile  