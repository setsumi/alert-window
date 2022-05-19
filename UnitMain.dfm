object FormMain: TFormMain
  Left = 230
  Top = 233
  Caption = 'Alert Window'
  ClientHeight = 410
  ClientWidth = 604
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010002002020100000000000E80200002600000010101000000000002801
    00000E0300002800000020000000400000000100040000000000800200000000
    0000000000000000000000000000000000000000800000800000008080008000
    0000800080008080000080808000C0C0C0000000FF0000FF000000FFFF00FF00
    0000FF00FF00FFFF0000FFFFFF00000000000000000000000000000000000000
    0000000044444444000000000000000000000444444444444440000000000000
    000444444444444444444000000000000044444FFFFFFFFFFFF4440000000000
    0444444FFFFFFFFFFFF44440000000004444444FFFFFFFFFFFF4444400000004
    4444444444FFFFFF44444444400000044444444444FFFFFF4444444440000044
    4444444444FFFFFF44444444440000444444444444FFFFFF4444444444000044
    4444444444FFFFFF44444444440004444444444444FFFFFF4444444444400444
    4444444444FFFFFF44444444444004444444444444FFFFFF4444444444400444
    4444444444FFFFFF44444444444004444444444444FFFFFF4444444444400444
    4444444444FFFFFF44444444444004444444444444FFFFFF4444444444400444
    4444444FFFFFFFFF44444444444000444444444FFFFFFFFF4444444444000044
    4444444444444444444444444400004444444444444444444444444444000004
    4444444444FFFF444444444440000004444444444FFFFFF44444444440000000
    44444444FFFFFFFF444444440000000004444444FFFFFFFF4444444000000000
    00444444FFFFFFFF4444440000000000000444444FFFFFF44444400000000000
    0000044444FFFF44444000000000000000000000444444440000000000000000
    0000000000000000000000000000FFF00FFFFF8001FFFE00007FFC00003FF800
    001FF000000FE0000007C0000003C00000038000000180000001800000010000
    0000000000000000000000000000000000000000000000000000000000008000
    00018000000180000001C0000003C0000003E0000007F000000FF800001FFC00
    003FFE00007FFF8001FFFFF00FFF280000001000000020000000010004000000
    0000C00000000000000000000000000000000000000000000000000080000080
    00000080800080000000800080008080000080808000C0C0C0000000FF0000FF
    000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0000000000000000000000
    0444444000000004444444444000004444FFFFF444000044444FFF4444000444
    444FFF4444400444444FFF4444400444444FFF444440044444FFFF4444400444
    44444444444004444444444444400044444FF4444400004444FFFF4444000004
    444FF444400000000444444000000000000000000000F81F0000E0070000C003
    0000800100008001000000000000000000000000000000000000000000000000
    00008001000080010000C0030000E0070000F81F0000}
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    604
    410)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 8
    Width = 59
    Height = 13
    Caption = 'Event Name'
  end
  object Label2: TLabel
    Left = 16
    Top = 58
    Width = 84
    Height = 13
    Caption = 'Event Description'
  end
  object Label3: TLabel
    Left = 16
    Top = 184
    Width = 69
    Height = 13
    Caption = 'Event Preview'
  end
  object Label4: TLabel
    Left = 395
    Top = 7
    Width = 52
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'Events List'
    ExplicitLeft = 406
  end
  object RichEditPreview: TRichEdit
    Left = 16
    Top = 200
    Width = 273
    Height = 185
    Anchors = [akLeft, akTop, akRight, akBottom]
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      'RichEditPreview')
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 2
    Zoom = 100
  end
  object EditName: TEdit
    Left = 16
    Top = 24
    Width = 273
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    AutoSelect = False
    TabOrder = 0
    Text = 'EditName'
    OnChange = EditNameChange
  end
  object ButtonAdd: TButton
    Left = 301
    Top = 22
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Add =>'
    TabOrder = 3
    OnClick = ButtonAddClick
  end
  object ButtonApply: TButton
    Left = 301
    Top = 53
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Apply =>'
    TabOrder = 4
    OnClick = ButtonApplyClick
  end
  object ButtonDelete: TButton
    Left = 301
    Top = 85
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Delete <='
    TabOrder = 5
    OnClick = ButtonDeleteClick
  end
  object ListBoxEvents: TListBox
    Left = 395
    Top = 24
    Width = 195
    Height = 361
    Anchors = [akTop, akRight, akBottom]
    ItemHeight = 13
    TabOrder = 6
    OnKeyUp = ListBoxEventsKeyUp
    OnMouseUp = ListBoxEventsMouseUp
  end
  object MemoDescr: TRichEdit
    Left = 16
    Top = 75
    Width = 273
    Height = 103
    Anchors = [akLeft, akTop, akRight]
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      'MemoDescr')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 1
    Zoom = 100
    OnChange = MemoDescrChange
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 391
    Width = 604
    Height = 19
    Panels = <
      item
        Text = 
          'Usage: AlertWindow 0 // alert by number; AlertWindow "Name" // a' +
          'lert by name; AlertWindow "Name" "Descr" // specified text'
        Width = 50
      end>
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Left = 312
    Top = 136
  end
end
