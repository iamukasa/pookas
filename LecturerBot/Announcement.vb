Public Class Announcement
    Dim NewsHeading As String
    Dim NewsDetail As String
    Dim NewsDate As String

    Public Function GetAnnouncement() As String
        Return NewsDetail
    End Function

    Sub SetHeading(ByVal Heading As String)
        NewsHeading = Heading
    End Sub

    Sub SetDetail(ByVal Detail As String)
        NewsDetail = Detail
    End Sub
End Class
