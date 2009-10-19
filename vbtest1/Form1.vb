Imports AIMLbot

Public Class Form1
    Dim MyBot As Bot
    Dim MyBot2 As Bot
    Dim MyUser As User

    Dim Phase As Integer
    Dim Complete As Integer

    Dim NewsHeader1 As String
    Dim NewsDetail1 As String
    Dim NewsHeader2 As String
    Dim NewsDetail2 As String
    Dim NewsHeader3 As String
    Dim NewsDetail3 As String

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        HideAll()
        Me.Top = 12
        Panel2.Top = 12
        MyBot = New Bot
        MyBot2 = New Bot
        MyUser = New User("myuser", MyBot)
        MyBot.loadSettings()
        MyBot2.loadSettings()
        Dim Loader As New AIMLbot.Utils.AIMLLoader(MyBot)
        Dim Loader2 As New AIMLbot.Utils.AIMLLoader(MyBot2)
        Loader.loadAIML("aiml")
        Loader2.loadAIML("aiml2")
        Phase = 0
        Complete = 0
        WebBrowser1.Navigate("https://edventure.ntu.edu.sg/webapps/login/?new_loc=%2Fntu_post_login.html")
    End Sub

    Private Sub TextBox2_KeyUp(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyEventArgs) Handles TextBox2.KeyUp
        If e.KeyCode = 13 Then
            TextBox1.Text = TextBox1.Text & vbNewLine & "YOU: " & TextBox2.Text
            TextBox5.Text = TextBox5.Text & vbNewLine & "YOU: " & TextBox2.Text

            Dim ChatResponse As String
            Dim ChatChance As Integer
            Dim Dice As New Random

            If InStr(TextBox2.Text, "announcement") <> 0 Or InStr(TextBox2.Text, "news") <> 0 Then
                ChatResponse = NewsDetail1
            Else
                Dim MyRequest As New Request(TextBox2.Text, MyUser, MyBot)
                Dim MyResult = MyBot.Chat(MyRequest)
                ChatResponse = MyResult.Output
                If Len(ChatResponse) > 0 Then
                    TextBox1.Text = TextBox1.Text & vbNewLine & "BOT1: " & ChatResponse
                End If
            End If

            ChatChance = Dice.Next(1, 100)
            If ChatChance < 25 Then
                Dim MyRequest2 As New Request(TextBox2.Text, MyUser, MyBot2)
                Dim MyResult2 = MyBot2.Chat(MyRequest2)
                ChatResponse = MyResult2.Output
                If Len(ChatResponse) > 0 Then
                    TextBox5.Text = TextBox5.Text & vbNewLine & "BOT2: " & ChatResponse
                End If

            End If

            TextBox2.Text = ""
        End If
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        HideAll()
        Panel1.Top = 12
    End Sub

    Sub HideAll()
        Panel1.Top = 1000
        Panel2.Top = 1000
        Panel3.Top = 1000
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        HideAll()
        Panel2.Top = 12
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        If Phase = 1 And Complete = 0 Then
            Complete = 1
            WebBrowser1.Document.GetElementById("user_id").InnerText = "lu0001fu"
            WebBrowser1.Document.GetElementById("password").InnerText = "technical"
            Application.DoEvents()
            WebBrowser1.Document.Forms(0).All("Login").InvokeMember("click")
        ElseIf Phase = 4 And Complete = 0 Then
            Complete = 1
            WebBrowser1.Navigate("http://edventure.ntu.edu.sg/bin/common/announcement.pl?action=LIST&render_type=DEFAULT&time=all&context=course_entry&course_id=_319894_1")
        ElseIf Phase >= 5 Then
            Timer1.Interval = 30000
            Dim SourceCode As String
            SourceCode = WebBrowser1.Document.Body.InnerHtml
            'TextBox3.Text = SourceCode
            Dim IconCode As String
            Dim IconPos As Integer
            Dim EMCode1 As String
            Dim EMPos1 As Integer
            Dim EMCode2 As String
            Dim EMPos2 As Integer
            Dim SizeCode As String
            Dim SizePos As Integer
            Dim FontCode As String
            Dim FontPos As Integer
            IconPos = 1
            IconCode = "/images/ci/icons/announcement_ia.gif"
            EMCode1 = "<EM>"
            EMCode2 = "</EM>"
            SizeCode = " size=2>"
            FontCode = "</FONT></TD>"
            'search for news 1
            IconPos = SourceCode.IndexOf(IconCode, IconPos + 1)
            EMPos1 = SourceCode.IndexOf(EMCode1, IconPos)
            EMPos2 = SourceCode.IndexOf(EMCode2, EMPos1)
            NewsHeader1 = SourceCode.Substring(EMPos1 + Len(EMCode1), EMPos2 - EMPos1 - Len(EMCode1))
            NewsHeader1 = RemoveTag(NewsHeader1)
            SizePos = SourceCode.IndexOf(SizeCode, EMPos2)
            FontPos = SourceCode.IndexOf(FontCode, SizePos)
            NewsDetail1 = SourceCode.Substring(SizePos + Len(SizeCode), FontPos - SizePos - Len(SizeCode))
            NewsDetail1 = RemoveTag(NewsDetail1)
            'search for news 2
            IconPos = SourceCode.IndexOf(IconCode, IconPos + 1)
            EMPos1 = SourceCode.IndexOf(EMCode1, IconPos)
            EMPos2 = SourceCode.IndexOf(EMCode2, EMPos1)
            NewsHeader2 = SourceCode.Substring(EMPos1 + Len(EMCode1), EMPos2 - EMPos1 - Len(EMCode1))
            NewsHeader2 = RemoveTag(NewsHeader2)
            SizePos = SourceCode.IndexOf(SizeCode, EMPos2)
            FontPos = SourceCode.IndexOf(FontCode, SizePos)
            NewsDetail2 = SourceCode.Substring(SizePos + Len(SizeCode), FontPos - SizePos - Len(SizeCode))
            NewsDetail2 = RemoveTag(NewsDetail2)
            'search for news 3
            IconPos = SourceCode.IndexOf(IconCode, IconPos + 1)
            EMPos1 = SourceCode.IndexOf(EMCode1, IconPos)
            EMPos2 = SourceCode.IndexOf(EMCode2, EMPos1)
            NewsHeader3 = SourceCode.Substring(EMPos1 + Len(EMCode1), EMPos2 - EMPos1 - Len(EMCode1))
            NewsHeader3 = RemoveTag(NewsHeader3)
            SizePos = SourceCode.IndexOf(SizeCode, EMPos2)
            FontPos = SourceCode.IndexOf(FontCode, SizePos)
            NewsDetail3 = SourceCode.Substring(SizePos + Len(SizeCode), FontPos - SizePos - Len(SizeCode))
            NewsDetail3 = RemoveTag(NewsDetail3)
            'write to textbox
            TextBox4.Text = NewsHeader1 & vbNewLine & vbNewLine & NewsDetail1
            TextBox3.Text = NewsHeader1 & vbNewLine & vbNewLine & NewsDetail1 & vbNewLine & vbNewLine & NewsHeader2 & vbNewLine & vbNewLine & NewsDetail2 & vbNewLine & vbNewLine & NewsHeader3 & vbNewLine & vbNewLine & NewsDetail3
            WebBrowser1.Refresh()
            TextBox2.Focus()
        End If
    End Sub

    Private Sub WebBrowser1_DocumentCompleted(ByVal sender As System.Object, ByVal e As System.Windows.Forms.WebBrowserDocumentCompletedEventArgs) Handles WebBrowser1.DocumentCompleted
        Phase = Phase + 1
        Label1.Text = "Phase " & Phase
        Complete = 0
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        HideAll()
        Panel3.Top = 12
    End Sub

    Public Function RemoveTag(ByVal InputText As String) As String
        Dim StartPos As Integer
        Dim EndPos As Integer
        Dim ExtractText As String
        InputText = Replace(InputText, "&nbsp;", " ")
        InputText = Replace(InputText, "<br />", " ")
        InputText = Replace(InputText, "<br>", " ")
        InputText = Replace(InputText, "<p>", " ")
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
        Return InputText
    End Function
End Class
