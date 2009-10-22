Imports AIMLbot

Public Class StudentBot

    Dim MyBot As Bot
    Dim MyUser As User

    Private Sub StudentBot_Leave(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Leave
        sdk.aw_destroy()
        sdk.aw_term()
    End Sub

    Private Sub StudentBot_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        MyBot = New Bot
        MyUser = New User("myuser", MyBot)
        MyBot.loadSettings()
        Dim Loader As New AIMLbot.Utils.AIMLLoader(MyBot)
        Loader.loadAIML("student aiml")
        sdk.aw_init(76)
        sdk.aw_event_set(AWSDKLib42.AW_EVENT_ATTRIBUTE.AW_EVENT_CHAT)
        sdk.aw_event_set(AWSDKLib42.AW_EVENT_ATTRIBUTE.AW_EVENT_AVATAR_CLICK)
        sdk.aw_create("155.69.101.53", 5552)
        sdk.aw_int_set(2, 2)
        sdk.aw_string_set(0, "StudentBot")
        sdk.aw_string_set(3, "12345")
        sdk.aw_string_set(6, "Sample 1")
        sdk.aw_login()
        sdk.aw_enter("A_Pookas")
        sdk.aw_int_set(198, 5000)
        sdk.aw_int_set(199, 805)
        sdk.aw_int_set(200, 0)
        sdk.aw_int_set(201, 60)
        sdk.aw_state_change()
        sdk.aw_say("Hi, i am a bot")
        Timer1.Enabled = True
        Timer2.Enabled = True
    End Sub

    Private Sub sdk_EventChat(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles sdk.EventChat
        Dim ChatMessage As String
        Dim ChatResponse As String
        Dim ChatChance As Integer
        Dim Dice As New Random
        Dim PlayerX As Integer
        Dim PlayerY As Integer
        Dim PlayerZ As Integer
        Dim PlayerYaw As Integer
        Dim PlayerName As String
        PlayerX = sdk.aw_int(208)
        PlayerY = sdk.aw_int(209)
        PlayerZ = sdk.aw_int(210)
        PlayerYaw = sdk.aw_int(211)
        PlayerName = sdk.aw_string(207)
        ChatMessage = sdk.aw_string(223)
        If ChatMessage = "0" Then
            sdk.aw_say(PlayerName & " (X: " & PlayerX & ", Y: " & PlayerY & ", Z: " & PlayerZ & ", Yaw: " & PlayerYaw & ")")
        Else
            ChatResponse = ""
            ChatChance = Dice.Next(1, 100)
            If ChatChance < 70 Then
                Dim MyRequest As New Request(ChatMessage, MyUser, MyBot)
                Dim MyResult = MyBot.Chat(MyRequest)
                ChatResponse = MyResult.Output
            End If
            If Len(ChatResponse) > 0 Then
                sdk.aw_say(ChatResponse)
            End If
        End If
    End Sub

    Private Sub sdk_EventAvatarClick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles sdk.EventAvatarClick
        Dim BotX As Integer
        Dim BotY As Integer
        Dim BotZ As Integer
        Dim BotYaw As Integer
        Dim BotName As String
        BotX = sdk.aw_int(198)
        BotY = sdk.aw_int(199)
        BotZ = sdk.aw_int(200)
        BotYaw = sdk.aw_int(201)
        BotName = sdk.aw_string(30)
        sdk.aw_say(BotName & " (X: " & BotX & ", Y: " & BotY & ", Z: " & BotZ & ", Yaw: " & BotYaw & ")")
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        sdk.aw_wait(0)
    End Sub

    Private Sub Timer2_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer2.Tick
        Dim BotX As Integer
        Dim BotY As Integer
        Dim BotZ As Integer
        Dim BotYaw As Integer
        Dim BotName As String
        Dim BotGesture As String
        Dim Dice As New Random
        Dim WalkChance As Integer
        Dim GestureChance As Integer
        BotX = sdk.aw_int(198)
        BotY = sdk.aw_int(199)
        BotZ = sdk.aw_int(200)
        BotYaw = sdk.aw_int(201)
        BotName = sdk.aw_string(30)
        BotGesture = sdk.aw_int(204)

        WalkChance = Dice.Next(1, 100)
        GestureChance = Dice.Next(1, 100)
        If WalkChance <= 20 Then 'north
            BotZ = BotZ + 300
            BotYaw = 60
        ElseIf WalkChance <= 40 Then 'west
            BotX = BotX + 300
            BotYaw = 960
        ElseIf WalkChance <= 60 Then 'south
            BotZ = BotZ - 300
            BotYaw = 1860
        ElseIf WalkChance <= 80 Then 'east
            BotX = BotX - 300
            BotYaw = 2760
        Else
        End If
        If GestureChance <= 30 Then
            BotGesture = 1
        ElseIf GestureChance <= 60 Then
            BotGesture = 2
        End If

        If BotX > 4450 And BotX < 5550 Then
            sdk.aw_int_set(198, BotX)
        End If
        If BotZ > -1268 And BotZ < 1382 Then
            sdk.aw_int_set(200, BotZ)
        End If
        sdk.aw_int_set(201, BotYaw)
        sdk.aw_int_set(204, BotGesture)
        sdk.aw_state_change()
    End Sub
End Class
