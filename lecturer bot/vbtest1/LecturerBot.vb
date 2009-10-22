Imports AIMLbot

Public Class LecturerBot
    Dim MyBot As Bot
    Dim MyUser As User
    Dim Phase As Integer
    Dim Complete As Integer
    Dim Lecture As Integer
    Dim NewsHeader1 As String
    Dim NewsDetail1 As String
    Dim NewsHeader2 As String
    Dim NewsDetail2 As String
    Dim NewsHeader3 As String
    Dim NewsDetail3 As String
    Dim PowerPoint(100) As String
    Dim CurrentPoint As Integer

    Private Sub LecturerBot_Leave(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Leave
        sdk.aw_destroy()
        sdk.aw_term()
    End Sub

    Private Sub LecturerBot_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        HideAll()
        Me.Top = 12
        Panel2.Top = 12
        MyBot = New Bot
        MyUser = New User("myuser", MyBot)
        MyBot.loadSettings()
        Dim Loader As New AIMLbot.Utils.AIMLLoader(MyBot)
        Loader.loadAIML("lecture aiml")
        Phase = 0
        Complete = 0
        WebBrowser1.Navigate("https://edventure.ntu.edu.sg/webapps/login/?new_loc=%2Fntu_post_login.html")
        sdk.aw_init(76)
        sdk.aw_event_set(AWSDKLib42.AW_EVENT_ATTRIBUTE.AW_EVENT_CHAT)
        sdk.aw_event_set(AWSDKLib42.AW_EVENT_ATTRIBUTE.AW_EVENT_AVATAR_CLICK)
        sdk.aw_event_set(AWSDKLib42.AW_EVENT_ATTRIBUTE.AW_EVENT_OBJECT_CLICK)
        sdk.aw_create("155.69.101.53", 5552)
        sdk.aw_int_set(2, 2)
        sdk.aw_string_set(0, "LecturerBot")
        sdk.aw_string_set(3, "12345")
        sdk.aw_string_set(6, "Sample 1")
        sdk.aw_login()
        sdk.aw_enter("A_Pookas")
        sdk.aw_int_set(198, 9846)
        sdk.aw_int_set(199, 805)
        sdk.aw_int_set(200, -2045)
        sdk.aw_int_set(201, 1860)
        sdk.aw_state_change()
        sdk.aw_say("Hello everyone, I'm in LT 1B...")
        Lecture = 0
        CurrentPoint = 0
        PowerPoint(1) = "http://www.mikeswanson.com/blog/images/3D%20PowerPoint%20Large.jpg"
        PowerPoint(2) = "http://www.bytescout.com/images/examples/ppt2swf_example_source_powerpoint_presentation.png"
        PowerPoint(3) = "http://www.baycongroup.com/powerpoint/images/power_point_window.gif"
        Callback.Enabled = True
        'Timer1.Enabled = True
    End Sub

    Private Sub sdk_EventObjectClick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles sdk.EventObjectClick
        Dim ObjectModel As String
        ObjectModel = sdk.aw_string(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_MODEL)

        If ObjectModel = "zpict2" Then
            CurrentPoint = CurrentPoint + 1
            sdk.aw_string_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_ACTION, "create picture " & PowerPoint(CurrentPoint))
            sdk.aw_object_change()
            If CurrentPoint > 3 Then
                CurrentPoint = 0
            End If
        End If
    End Sub

    Private Sub sdk_EventAvatarClick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles sdk.EventAvatarClick
        Dim AvatarName As String
        AvatarName = sdk.aw_string(207)
        sdk.aw_say("Yes, " & AvatarName & "?")
    End Sub

    Private Sub sdk_EventChat(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles sdk.EventChat
        Dim AvatarName As String
        Dim ChatMessage As String
        Dim ChatResponse As String
        Dim Dice As New Random
        AvatarName = sdk.aw_string(207)
        ChatMessage = sdk.aw_string(223)
        ChatResponse = ""
        If InStr(ChatMessage, "announcement") <> 0 Or InStr(ChatMessage, "news") <> 0 Then
            If InStr(ChatMessage, "2nd") <> 0 Or InStr(ChatMessage, "second") <> 0 Then
                ChatResponse = "Hey " & AvatarName & ", " & NewsDetail2
            ElseIf InStr(ChatMessage, "3rd") <> 0 Or InStr(ChatMessage, "third") <> 0 Then
                ChatResponse = "Hey " & AvatarName & ", " & NewsDetail3
            Else
                ChatResponse = "Hey " & AvatarName & ", " & NewsDetail1
            End If
        ElseIf InStr(ChatMessage, "start") <> 0 And InStr(ChatMessage, "lecture") <> 0 And Lecture = 0 Then
            Lecture = 1
            ChatResponse = "Ah yes, the lecture will begin now"
            sdk.aw_int_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_X, 9846)
            sdk.aw_int_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_Y, 805)
            sdk.aw_int_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_Z, -2385)
            sdk.aw_int_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_YAW, 2760)
            sdk.aw_string_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_MODEL, "zpict1")
            sdk.aw_string_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_DESCRIPTION, "Lecture Screen")
            sdk.aw_string_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_ACTION, "create scale 1.5 1.5 1.5; activate media url=http://intune.ntu.edu.sg/sce/courses/wongek/CSC303_OCL%20Intro.wmv")
            sdk.aw_object_add()
        Else
            Dim MyRequest As New Request(ChatMessage, MyUser, MyBot)
            Dim MyResult = MyBot.Chat(MyRequest)
            ChatResponse = MyResult.Output
        End If
        If Len(ChatResponse) > 0 Then
            sdk.aw_say(ChatResponse)
        End If
    End Sub

    Private Sub TextBox2_KeyUp(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyEventArgs) Handles TextBox2.KeyUp
        If e.KeyCode = 13 Then
            TextBox1.Text = TextBox1.Text & vbNewLine & "YOU: " & TextBox2.Text
            TextBox5.Text = TextBox5.Text & vbNewLine & "YOU: " & TextBox2.Text
            Dim ChatResponse As String
            ChatResponse = ""
            If InStr(TextBox2.Text, "announcement") <> 0 Or InStr(TextBox2.Text, "news") <> 0 Then
                ChatResponse = NewsDetail1
            ElseIf InStr(TextBox2.Text, "lecture") <> 0 And Lecture = 0 Then
                Lecture = 1
                ChatResponse = "Ah yes, the lecture will begin now"
                sdk.aw_int_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_X, 9946)
                sdk.aw_int_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_Y, 805)
                sdk.aw_int_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_Z, -2395)
                sdk.aw_int_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_YAW, 1860)
                sdk.aw_string_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_MODEL, "zpict1")
                sdk.aw_string_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_DESCRIPTION, "Lecture Screen")
                sdk.aw_string_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_ACTION, "create scale 2 2 2")
                sdk.aw_object_add()


            Else
                Dim MyRequest As New Request(TextBox2.Text, MyUser, MyBot)
                Dim MyResult = MyBot.Chat(MyRequest)
                ChatResponse = MyResult.Output
            End If
            If Len(ChatResponse) > 0 Then
                TextBox1.Text = TextBox1.Text & vbNewLine & "BOT1: " & ChatResponse
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
        Return InputText
    End Function

    Private Sub Callback_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Callback.Tick
        sdk.aw_wait(0)
    End Sub
End Class
