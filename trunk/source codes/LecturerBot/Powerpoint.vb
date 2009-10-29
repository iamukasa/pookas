Public Class Powerpoint
    Shared URLCount As Long
    Dim Max As Long
    Dim URL(100) As String

    Public Sub New()
        URLCount = 0
        Max = 42
        URL(1) = New String("http://www.worldsearchteam.com/ocl2/ocl2-001.jpg")
        URL(2) = New String("http://www.worldsearchteam.com/ocl2/ocl2-002.jpg")
        URL(3) = New String("http://www.worldsearchteam.com/ocl2/ocl2-003.jpg")
        URL(4) = New String("http://www.worldsearchteam.com/ocl2/ocl2-004.jpg")
        URL(5) = New String("http://www.worldsearchteam.com/ocl2/ocl2-005.jpg")
        URL(6) = New String("http://www.worldsearchteam.com/ocl2/ocl2-006.jpg")
        URL(7) = New String("http://www.worldsearchteam.com/ocl2/ocl2-007.jpg")
        URL(8) = New String("http://www.worldsearchteam.com/ocl2/ocl2-008.jpg")
        URL(9) = New String("http://www.worldsearchteam.com/ocl2/ocl2-009.jpg")
        URL(10) = New String("http://www.worldsearchteam.com/ocl2/ocl2-010.jpg")
        URL(11) = New String("http://www.worldsearchteam.com/ocl2/ocl2-011.jpg")
        URL(12) = New String("http://www.worldsearchteam.com/ocl2/ocl2-012.jpg")
        URL(13) = New String("http://www.worldsearchteam.com/ocl2/ocl2-013.jpg")
        URL(14) = New String("http://www.worldsearchteam.com/ocl2/ocl2-014.jpg")
        URL(15) = New String("http://www.worldsearchteam.com/ocl2/ocl2-015.jpg")
        URL(16) = New String("http://www.worldsearchteam.com/ocl2/ocl2-016.jpg")
        URL(17) = New String("http://www.worldsearchteam.com/ocl2/ocl2-017.jpg")
        URL(18) = New String("http://www.worldsearchteam.com/ocl2/ocl2-018.jpg")
        URL(19) = New String("http://www.worldsearchteam.com/ocl2/ocl2-019.jpg")
        URL(20) = New String("http://www.worldsearchteam.com/ocl2/ocl2-020.jpg")
        URL(21) = New String("http://www.worldsearchteam.com/ocl2/ocl2-021.jpg")
        URL(22) = New String("http://www.worldsearchteam.com/ocl2/ocl2-022.jpg")
        URL(23) = New String("http://www.worldsearchteam.com/ocl2/ocl2-023.jpg")
        URL(24) = New String("http://www.worldsearchteam.com/ocl2/ocl2-024.jpg")
        URL(25) = New String("http://www.worldsearchteam.com/ocl2/ocl2-025.jpg")
        URL(26) = New String("http://www.worldsearchteam.com/ocl2/ocl2-026.jpg")
        URL(27) = New String("http://www.worldsearchteam.com/ocl2/ocl2-027.jpg")
        URL(28) = New String("http://www.worldsearchteam.com/ocl2/ocl2-028.jpg")
        URL(29) = New String("http://www.worldsearchteam.com/ocl2/ocl2-029.jpg")
        URL(30) = New String("http://www.worldsearchteam.com/ocl2/ocl2-030.jpg")
        URL(31) = New String("http://www.worldsearchteam.com/ocl2/ocl2-031.jpg")
        URL(32) = New String("http://www.worldsearchteam.com/ocl2/ocl2-032.jpg")
        URL(33) = New String("http://www.worldsearchteam.com/ocl2/ocl2-033.jpg")
        URL(34) = New String("http://www.worldsearchteam.com/ocl2/ocl2-034.jpg")
        URL(35) = New String("http://www.worldsearchteam.com/ocl2/ocl2-035.jpg")
        URL(36) = New String("http://www.worldsearchteam.com/ocl2/ocl2-036.jpg")
        URL(37) = New String("http://www.worldsearchteam.com/ocl2/ocl2-037.jpg")
        URL(38) = New String("http://www.worldsearchteam.com/ocl2/ocl2-038.jpg")
        URL(39) = New String("http://www.worldsearchteam.com/ocl2/ocl2-039.jpg")
        URL(40) = New String("http://www.worldsearchteam.com/ocl2/ocl2-040.jpg")
        URL(41) = New String("http://www.worldsearchteam.com/ocl2/ocl2-041.jpg")
        URL(42) = New String("http://www.worldsearchteam.com/ocl2/ocl2-042.jpg")
    End Sub

    Public Function GetNextPowerpoint() As String
        URLCount = URLCount + 1
        If URLCount > Max Then
            URLCount = 1
        End If
        Return URL(URLCount)
    End Function

    Public Sub GetPreviousPowerpoint()
        URLCount = URLCount - 2
        If URLCount = -1 Then
            URLCount = Max - 1
        ElseIf URLCount < 1 Then
            URLCount = Max
        End If
    End Sub
End Class
