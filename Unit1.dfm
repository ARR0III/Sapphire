object Form1: TForm1
  Left = 337
  Top = 207
  BorderStyle = bsDialog
  Caption = 'Sapphire [cipher vigenere modification]'
  ClientHeight = 361
  ClientWidth = 593
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 105
    Height = 14
    Caption = #1050#1083#1102#1095' '#1096#1080#1092#1088#1086#1074#1072#1085#1080#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Consolas'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 120
    Width = 28
    Height = 14
    Caption = #1042#1074#1086#1076
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Consolas'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 8
    Top = 240
    Width = 35
    Height = 14
    Caption = #1042#1099#1074#1086#1076
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Consolas'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 488
    Top = 24
    Width = 49
    Height = 13
    Caption = 'Tumbler G'
  end
  object Label5: TLabel
    Left = 488
    Top = 72
    Width = 48
    Height = 13
    Caption = 'Tumbler T'
  end
  object Memo1: TMemo
    Left = 8
    Top = 24
    Width = 465
    Height = 89
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Consolas'
    Font.Style = []
    MaxLength = 2048
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Memo2: TMemo
    Left = 8
    Top = 136
    Width = 465
    Height = 89
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Consolas'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object Memo3: TMemo
    Left = 8
    Top = 256
    Width = 465
    Height = 89
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Consolas'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object Button1: TButton
    Left = 488
    Top = 288
    Width = 89
    Height = 25
    Caption = #1047#1072#1096#1080#1092#1088#1086#1074#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Consolas'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 488
    Top = 320
    Width = 89
    Height = 25
    Caption = #1056#1072#1089#1096#1080#1092#1088#1086#1074#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Consolas'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 488
    Top = 136
    Width = 89
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 5
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 488
    Top = 256
    Width = 89
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 6
    OnClick = Button4Click
  end
  object XOR: TRadioButton
    Left = 488
    Top = 180
    Width = 49
    Height = 17
    Caption = 'XOR'
    TabOrder = 7
  end
  object Sapphire: TRadioButton
    Left = 488
    Top = 204
    Width = 65
    Height = 17
    Caption = 'Sapphire'
    Checked = True
    TabOrder = 8
    TabStop = True
  end
  object Edit1: TEdit
    Left = 488
    Top = 40
    Width = 89
    Height = 21
    MaxLength = 10
    TabOrder = 9
  end
  object Edit2: TEdit
    Left = 488
    Top = 90
    Width = 89
    Height = 21
    MaxLength = 10
    TabOrder = 10
  end
end
