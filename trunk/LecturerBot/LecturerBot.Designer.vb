<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class LecturerBot
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(LecturerBot))
        Me.Connection = New System.Windows.Forms.WebBrowser
        Me.Edventure = New System.Windows.Forms.Timer(Me.components)
        Me.sdk = New AxAWSDKLib42.AxAwSdk42
        Me.ActiveWorld = New System.Windows.Forms.Timer(Me.components)
        CType(Me.sdk, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'Connection
        '
        Me.Connection.Dock = System.Windows.Forms.DockStyle.Fill
        Me.Connection.Location = New System.Drawing.Point(0, 0)
        Me.Connection.MinimumSize = New System.Drawing.Size(20, 20)
        Me.Connection.Name = "Connection"
        Me.Connection.Size = New System.Drawing.Size(784, 564)
        Me.Connection.TabIndex = 0
        '
        'Edventure
        '
        Me.Edventure.Interval = 3000
        '
        'sdk
        '
        Me.sdk.Enabled = True
        Me.sdk.Location = New System.Drawing.Point(0, 0)
        Me.sdk.Name = "sdk"
        Me.sdk.OcxState = CType(resources.GetObject("sdk.OcxState"), System.Windows.Forms.AxHost.State)
        Me.sdk.Size = New System.Drawing.Size(113, 90)
        Me.sdk.TabIndex = 8
        '
        'ActiveWorld
        '
        '
        'LecturerBot
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(784, 564)
        Me.Controls.Add(Me.Connection)
        Me.Controls.Add(Me.sdk)
        Me.Name = "LecturerBot"
        Me.Text = "LecturerBot"
        CType(Me.sdk, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents Connection As System.Windows.Forms.WebBrowser
    Friend WithEvents Edventure As System.Windows.Forms.Timer
    Friend WithEvents sdk As AxAWSDKLib42.AxAwSdk42
    Friend WithEvents ActiveWorld As System.Windows.Forms.Timer

End Class
