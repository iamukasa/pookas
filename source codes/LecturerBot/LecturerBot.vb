Imports AIMLbot

Public Class LecturerBot
    Dim MyAIML As Bot
    Dim Myself As User
    Dim Phase As Integer
    Dim Complete As Integer
    Dim Lecture As Integer
    Dim News(3) As Announcement
    Dim Power As Powerpoint
    Dim ObjectNumber As Integer

    Private Sub Destroy(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Leave
        sdk.aw_destroy()
        sdk.aw_term()
    End Sub

    Private Sub Initialize(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Power = New Powerpoint
        MyAIML = New Bot
        Myself = New User("Myself", MyAIML)
        MyAIML.loadSettings()
        Dim Loader As New AIMLbot.Utils.AIMLLoader(MyAIML)
        Loader.loadAIML("lecture aiml")
        Phase = 0
        Complete = 0
        Connection.Navigate("https://edventure.ntu.edu.sg/webapps/login/?new_loc=%2Fntu_post_login.html")
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
        ActiveWorld.Enabled = True
        Edventure.Enabled = True
    End Sub

    Private Sub sdk_EventObjectClick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles sdk.EventObjectClick
        Dim ObjectModel As String
        ObjectModel = sdk.aw_string(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_MODEL)

        If ObjectModel = "zpict1" Then
            ObjectNumber = sdk.aw_int(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_NUMBER)
        ElseIf ObjectModel = "zpict2" Then
            sdk.aw_string_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_ACTION, "create picture " & Power.GetNextPowerpoint)
            sdk.aw_object_change()
        ElseIf ObjectModel = "pp16l" Then
            Power.GetPreviousPowerpoint()
        End If
    End Sub

    Private Sub sdk_EventAvatarClick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles sdk.EventAvatarClick
        Dim AvatarName As String
        'AvatarName = sdk.aw_string(207)
        'sdk.aw_say("Yes, " & AvatarName & "?")
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
                TextBox1.Text = News(1).GetAnnouncement
                ChatResponse = "Hey " & AvatarName & ", " & News(1).GetAnnouncement
            ElseIf InStr(ChatMessage, "3rd") <> 0 Or InStr(ChatMessage, "third") <> 0 Then
                TextBox1.Text = News(2).GetAnnouncement
                ChatResponse = "Hey " & AvatarName & ", " & News(2).GetAnnouncement
            Else
                TextBox1.Text = News(0).GetAnnouncement
                ChatResponse = "Hey " & AvatarName & ", " & News(0).GetAnnouncement
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
            sdk.aw_string_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_ACTION, "create scale 1.5 1.5 1.5; activate media url=http://intune.ntu.edu.sg/sce/courses/wongek/CSC303_OCL%20Intro.wmv; bump warp +0 -1.2 +0.2a")
            sdk.aw_object_add()
        ElseIf InStr(ChatMessage, "end") <> 0 And InStr(ChatMessage, "lecture") <> 0 And Lecture = 1 Then
            Lecture = 0
            sdk.aw_int_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_NUMBER, ObjectNumber)
            sdk.aw_int_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_X, 9846)
            sdk.aw_int_set(AWSDKLib42.AW_ATTRIBUTE.AW_OBJECT_Y, 805)
            sdk.aw_object_delete()
        Else
            Dim MyRequest As New Request(ChatMessage, Myself, MyAIML)
            Dim MyResult = MyAIML.Chat(MyRequest)
            ChatResponse = MyResult.Output
        End If
        If Len(ChatResponse) > 0 Then
            sdk.aw_say(ChatResponse)
        End If
    End Sub

    Private Sub RefreshEdventure(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Edventure.Tick
        If Phase = 1 And Complete = 0 Then
            Complete = 1
            Connection.Document.GetElementById("user_id").InnerText = "lu0001fu"
            Connection.Document.GetElementById("password").InnerText = "technical"
            Application.DoEvents()
            Connection.Document.Forms(0).All("Login").InvokeMember("click")
        ElseIf Phase = 4 And Complete = 0 Then
            Complete = 1
            Connection.Navigate("http://edventure.ntu.edu.sg/bin/common/announcement.pl?action=LIST&render_type=DEFAULT&time=all&context=course_entry&course_id=_319894_1")
        ElseIf Phase >= 5 Then
            Edventure.Interval = 30000
            Dim Page As New AnnouncementPage(Connection.Document.Body.InnerHtml)
            News(0) = Page.GetNextAnnouncement
            News(1) = Page.GetNextAnnouncement
            News(2) = Page.GetNextAnnouncement
            Connection.Refresh()
        End If
    End Sub

    Private Sub DocumentCompleted(ByVal sender As System.Object, ByVal e As System.Windows.Forms.WebBrowserDocumentCompletedEventArgs) Handles Connection.DocumentCompleted
        Phase = Phase + 1
        Complete = 0
    End Sub

    Private Sub ActiveWorldCall(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ActiveWorld.Tick
        sdk.aw_wait(0)
    End Sub
End Class
