object Form1: TForm1
  Left = 192
  Top = 114
  Width = 144
  Height = 167
  Caption = 'Beh'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Edit1: TEdit
    Left = 8
    Top = 16
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'Text to Encrpt/Decrypt'
  end
  object Edit2: TEdit
    Left = 8
    Top = 48
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'Encrypted/Decrypted'
  end
  object Button1: TButton
    Left = 24
    Top = 80
    Width = 89
    Height = 25
    Caption = 'Encrypt/Decrpt'
    TabOrder = 2
    OnClick = Button1Click
  end
end
