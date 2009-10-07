Imports System.IO

Public Class Form1
    Inherits System.Windows.Forms.Form


    Dim Phase As Long
    Dim Complete As Long
    Dim Toggle As Long




#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents AxWebBrowser1 As AxSHDocVw.AxWebBrowser
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents TextBox2 As System.Windows.Forms.TextBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(Form1))
        Me.AxWebBrowser1 = New AxSHDocVw.AxWebBrowser
        Me.Button1 = New System.Windows.Forms.Button
        Me.TextBox1 = New System.Windows.Forms.TextBox
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.TextBox2 = New System.Windows.Forms.TextBox
        CType(Me.AxWebBrowser1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'AxWebBrowser1
        '
        Me.AxWebBrowser1.Enabled = True
        Me.AxWebBrowser1.Location = New System.Drawing.Point(0, 0)
        Me.AxWebBrowser1.OcxState = CType(resources.GetObject("AxWebBrowser1.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxWebBrowser1.Size = New System.Drawing.Size(984, 544)
        Me.AxWebBrowser1.TabIndex = 0
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(600, 552)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(80, 32)
        Me.Button1.TabIndex = 1
        Me.Button1.Text = "Button1"
        '
        'TextBox1
        '
        Me.TextBox1.Location = New System.Drawing.Point(160, 560)
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.Size = New System.Drawing.Size(384, 20)
        Me.TextBox1.TabIndex = 2
        Me.TextBox1.Text = "TextBox1"
        '
        'Timer1
        '
        Me.Timer1.Enabled = True
        Me.Timer1.Interval = 1000
        '
        'TextBox2
        '
        Me.TextBox2.Location = New System.Drawing.Point(0, 600)
        Me.TextBox2.Multiline = True
        Me.TextBox2.Name = "TextBox2"
        Me.TextBox2.Size = New System.Drawing.Size(984, 536)
        Me.TextBox2.TabIndex = 3
        Me.TextBox2.Text = "TextBox2"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(992, 606)
        Me.Controls.Add(Me.TextBox2)
        Me.Controls.Add(Me.TextBox1)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.AxWebBrowser1)
        Me.Name = "Form1"
        Me.Text = "Form1"
        CType(Me.AxWebBrowser1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        If Toggle = 1 Then
            Toggle = 0
            AxWebBrowser1.Top = 600
            TextBox2.Top = 0
        Else
            Toggle = 1
            AxWebBrowser1.Top = 0
            TextBox2.Top = 600
        End If


        'MsgBox(AxWebBrowser1.Document)
        'Dim doc As mshtml.HTMLDocumentClass
        'Dim anc As mshtml.HTMLAnchorElementClass
        'doc = DirectCast(AxWebBrowser1.Document, mshtml.HTMLDocumentClass)

        'anc = DirectCast(doc.getElementById("managedLink"), mshtml.HTMLAnchorElementClass)


        'AxWebBrowser1.Document.All("user_id") = "testing"
        'AxWebBrowser1.Document.Forms(0).submit()
        'AxWebBrowser1.Document.Forms(0).Field()
        'AxWebBrowser1.Document.Forms(0).submit()

        'Dim Browser As mshtml.HTMLDocument = AxWebBrowser1.Document
        'MsgBox(Browser.body.innerHTML)
        'Dim EL

        'For Each EL In AxWebBrowser1.Document
        'MsgBox(EL.href)
        'Next

        'Dim Element

        'For Each Element In AxWebBrowser1.Document.All
        'If Element.tagName = "A" Then
        'MsgBox(Element.href)
        'If Element.href = "http://WebSiteName/weater.asp" Then
        '   Element.Click()
        'End If
        '   End If
        'Next
        'Data = AxWebBrowser1.Document.All.Item().innertext
        'MsgBox(Data)

    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Phase = 0
        Complete = 0
        AxWebBrowser1.Navigate("https://edventure.ntu.edu.sg/webapps/login/?new_loc=%2Fntu_post_login.html")
        'AxWebBrowser1.Navigate("http://www.google.com")
    End Sub

    Private Sub AxWebBrowser1_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles AxWebBrowser1.Enter

    End Sub

    Private Sub AxWebBrowser1_DocumentComplete(ByVal sender As Object, ByVal e As AxSHDocVw.DWebBrowserEvents2_DocumentCompleteEvent) Handles AxWebBrowser1.DocumentComplete
        Phase = Phase + 1
        Complete = 0
        TextBox1.Text = "Phase = " & Phase & " | Complete = " & Complete
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        If Phase = 1 And Complete = 0 Then
            Complete = 1
            AxWebBrowser1.Document.getElementById("user_id").value = "lu0001fu"
            Application.DoEvents()
            AxWebBrowser1.Document.getElementById("password").value = "technical"
            Application.DoEvents()
            AxWebBrowser1.Document.Forms(0).All("Login").click()
            Application.DoEvents()
        ElseIf Phase = 4 And Complete = 0 Then
            Complete = 1
            'AxWebBrowser1.Navigate("http://edventure.ntu.edu.sg/webapps/portal/frameset.jsp?tab_id=_2_1&url=%2fwebapps%2fblackboard%2fexecute%2flauncher%3ftype%3dCourse%26id%3d_319894_1%26url%3d")
            'AxWebBrowser1.Navigate("http://edventure.ntu.edu.sg/webapps/blackboard/content/launchLink.jsp?course_id=_319894_1&tool_id=_139_1&tool_type=TOOL&mode=view&mode=reset")
            AxWebBrowser1.Navigate("http://edventure.ntu.edu.sg/bin/common/announcement.pl?action=LIST&render_type=DEFAULT&time=all&context=course_entry&course_id=_319894_1")
        ElseIf Phase >= 5 Then
            Dim Browser As mshtml.HTMLDocument = AxWebBrowser1.Document
            'MsgBox("Total number of frames = " & Browser.frames.length)
            'Dim Frame As mshtml.IHTMLWindow2
            'Frame = Browser.frames.item(1)
            'Dim Inner As mshtml.HTMLDocument = Frame.document
            Dim SourceCode As String
            SourceCode = Browser.body.innerHTML
            'TextBox2.Text = SourceCode
            Timer1.Interval = 10000
            Dim Writer As New System.IO.StreamWriter("C:\Documents and Settings\ms1\Desktop\test1\bin\test1.txt")
            Writer.Write(SourceCode)
            Writer.Close()
            AxWebBrowser1.Refresh()
        End If
    End Sub
End Class
