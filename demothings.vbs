' this script will move the demothings to their char folders
Set objFS = CreateObject("Scripting.FileSystemObject")
inFolder="U:\AOVanilla1.7.3\AOVanilla1.7.41\client\base\misc\Demothings\" 'demothings
outFolder="U:\AOVanilla1.7.3\AOVanilla1.7.41\client\base\characters\"
Set objFolder = objFS.GetFolder(inFolder)
For Each strFile In objFolder.Files
	strFileName = strFile.Path
	If Right(objFS.GetFileName(strFileName),14) = "_char_icon.png" Then
		If objFS.FolderExists(outFolder & Left(objFS.GetFileName(strFileName),Len(objFS.GetFileName(strFileName))-14)) Then
			strFile.Copy(outFolder & Left(objFS.GetFileName(strFileName),Len(objFS.GetFileName(strFileName))-14) & "\char_icon.png")
		End If
	End If	
Next 