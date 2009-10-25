Imports AIMLbot

Public Class StudentBot
    Dim MyAIML As Bot
    Dim Myself As User
    Dim BotX As Integer
    Dim BotY As Integer
    Dim BotZ As Integer
    Dim BotYaw As Integer
    Dim BotName As String
    Dim BotGesture As Integer
    Dim WalkChance As Integer
    Dim GestureChance As Integer
    Dim ChatChance As Integer

    Private Sub Initialize(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        'initialization for student bot to use AIML
        MyAIML = New Bot
        Myself = New User("Myself", MyAIML)
        MyAIML.loadSettings()
        Dim Loader As New AIMLbot.Utils.AIMLLoader(MyAIML)
        Loader.loadAIML("student aiml")
        sdk.aw_init(76)
        'give student some meaningful behavior
        sdk.aw_event_set(AWSDKLib42.AW_EVENT_ATTRIBUTE.AW_EVENT_CHAT)
        sdk.aw_event_set(AWSDKLib42.AW_EVENT_ATTRIBUTE.AW_EVENT_AVATAR_CLICK)
        'student bot login to our active world
        sdk.aw_create("155.69.101.53", 5552)
        sdk.aw_int_set(2, 2)
        sdk.aw_string_set(0, "StudentBot")
        sdk.aw_string_set(3, "12345")
        sdk.aw_string_set(6, "Sample 1")
        sdk.aw_login()
        sdk.aw_enter("A_Pookas")
        'this student is on level 2, carpet area
        sdk.aw_int_set(198, 5000)
        sdk.aw_int_set(199, 805)
        sdk.aw_int_set(200, 0)
        sdk.aw_int_set(201, 60)
        sdk.aw_state_change()
        sdk.aw_say("Hi, i am a student bot")
        'activate the timer
        ActiveWorld.Enabled = True
        Walker.Enabled = True
    End Sub

    Private Sub RandomWalk(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Walker.Tick
        Dim Dice As New Random

        'get the latest variables
        BotX = sdk.aw_int(198)
        BotY = sdk.aw_int(199)
        BotZ = sdk.aw_int(200)
        BotYaw = sdk.aw_int(201)
        BotName = sdk.aw_string(30)
        BotGesture = sdk.aw_int(204)

        'a chance to begin walking in a direction randomly 20% chance
        WalkChance = Dice.Next(1, 100)
        If WalkChance <= 20 Then 'walk north and face north
            BotZ = BotZ + 300
            BotYaw = 60
        ElseIf WalkChance <= 40 Then 'walk west and face west
            BotX = BotX + 300
            BotYaw = 960
        ElseIf WalkChance <= 60 Then 'walk south and face south
            BotZ = BotZ - 300
            BotYaw = 1860
        ElseIf WalkChance <= 80 Then 'walk east and face east
            BotX = BotX - 300
            BotYaw = 2760
        Else
            'stay at the same place
        End If

        'a chance to make some gestures randomly 30%
        GestureChance = Dice.Next(1, 100)
        If GestureChance <= 30 Then
            BotGesture = 1
        ElseIf GestureChance <= 60 Then
            BotGesture = 2
        Else
            'no gesture made
        End If

        'BUG FIX: must walk within the perimeters so that the bot doesnt go through walls or objects
        If BotX > 4450 And BotX < 5550 Then
            sdk.aw_int_set(198, BotX)
        End If
        If BotZ > -1268 And BotZ < 1382 Then
            sdk.aw_int_set(200, BotZ)
        End If
        sdk.aw_int_set(201, BotYaw)
        sdk.aw_int_set(204, BotGesture)
        sdk.aw_state_change() 'update the bot state changes
    End Sub

    Private Sub sdk_EventChat(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles sdk.EventChat
        Dim ChatMessage As String
        Dim ChatResponse As String
        Dim Dice As New Random

        'get the chat message
        ChatMessage = sdk.aw_string(223)
        ChatResponse = ""

        'give this bot a 70% chance to talk
        ChatChance = Dice.Next(1, 100)
        If ChatChance < 70 Then
            Dim MyRequest As New Request(ChatMessage, Myself, MyAIML)
            Dim MyResult = MyAIML.Chat(MyRequest)
            ChatResponse = MyResult.Output
        End If

        'only respond if the bot aiml have something to respond
        If Len(ChatResponse) > 0 Then
            sdk.aw_say(ChatResponse)
        End If

    End Sub

    Private Sub sdk_EventAvatarClick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles sdk.EventAvatarClick
        'the bot will report its own name and its current coordinates when clicked
        BotX = sdk.aw_int(198)
        BotY = sdk.aw_int(199)
        BotZ = sdk.aw_int(200)
        BotYaw = sdk.aw_int(201)
        BotName = sdk.aw_string(30)
        sdk.aw_say(BotName & " (X: " & BotX & ", Y: " & BotY & ", Z: " & BotZ & ", Yaw: " & BotYaw & ")")
    End Sub

    'continue waiting for activeworld events
    Private Sub ActiveWorldEvent(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ActiveWorld.Tick
        sdk.aw_wait(0)
    End Sub

    'destroy the instance of this bot
    Private Sub Destroy(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Leave
        sdk.aw_destroy()
        sdk.aw_term()
    End Sub
End Class
