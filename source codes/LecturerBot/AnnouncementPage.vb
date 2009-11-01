Public Class AnnouncementPage

    Dim SourceCode As String
    Shared IconPos As Integer

    Public Sub New(ByVal Code As String)
        SourceCode = Code
        IconPos = 1
    End Sub

    Public Function GetNextAnnouncement() As Announcement
        Dim Temp As String
        Dim News As New Announcement
        Dim EMPos1 As Integer
        Dim EMPos2 As Integer
        'Dim SizePos As Integer
        Dim FontPos As Integer
        IconPos = SourceCode.IndexOf("/images/ci/icons/announcement_ia.gif", IconPos + 1)
        EMPos1 = SourceCode.IndexOf("<EM>", IconPos)
        EMPos2 = SourceCode.IndexOf("</EM>", EMPos1)
        Temp = SourceCode.Substring(EMPos1 + Len("<EM>"), EMPos2 - EMPos1 - Len("<EM>"))
        News.SetHeading(ParseData(Temp))
        'SizePos = SourceCode.IndexOf(" size=2>", EMPos2)
        'FontPos = SourceCode.IndexOf("</FONT></TD>", SizePos)
        'Temp = SourceCode.Substring(SizePos + Len(" size=2>"), FontPos - SizePos - Len(" size=2>"))
        FontPos = SourceCode.IndexOf("</FONT></TD>", EMPos2)
        Temp = SourceCode.Substring(EMPos2, FontPos - EMPos2)
        News.SetDetail(ParseData(Temp))
        Return News
    End Function

    Public Function ParseData(ByVal InputText As String) As String
        Dim StartPos As Integer
        Dim EndPos As Integer
        Dim ExtractText As String
        InputText = Replace(InputText, "&nbsp;", " ")
        InputText = Replace(InputText, "<br />", " ")
        InputText = Replace(InputText, "<br>", " ")
        InputText = Replace(InputText, "</p>", ", ")
        InputText = Replace(InputText, "&lt;", "<")
        InputText = Replace(InputText, "&gt;", ">")
        InputText = Replace(InputText, vbNewLine, " ")
        While InStr(InputText, "<") <> 0
            StartPos = InStr(InputText, "<")
            EndPos = InStr(InputText, ">")
            If StartPos > 1 Then
                ExtractText = Mid(InputText, 1, StartPos - 1) & Mid(InputText, EndPos + 1, Len(InputText) - EndPos)
            Else
                ExtractText = Mid(InputText, EndPos + 1, Len(InputText) - EndPos)
            End If
            InputText = ExtractText
        End While

        While InStr(InputText, "  ") <> 0
            InputText = Replace(InputText, "  ", " ")
        End While

        Return InputText
    End Function
End Class
