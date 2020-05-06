
    vtchid  -- 鉄騎コントローラ用デバイスドライバ


Introduction
 「vtchid」は、鉄騎コントローラ用デバイスドライバです。このドライバは、
HID (Human Interface Device) miniriver として作成動作し、最大8軸32ボタ
ン2Hatデバイスとして見えます。
このソフトウェアは、無償、無保証、無制限にて公開します。
(つまり、パブリックドメインソフトウェア (PDS) と同等ということ。)


Requirements
 OS    : Windows XP/2000
 Device: 鉄騎コントローラ
         XBox コントローラ型と USB コネクタとの変換ケーブル


Install
 - 圧縮ファイルを展開します。
 - 鉄騎コントローラを USB ポートに接続します。
 - デバイスドライバウィザードが表示されたら、`vtchid.inf' を選択し、ド
   ライバをインストールします。
 - 必要に応じて、プログラム vtchidldr.exe を任意の場所に置き、ショート
   カットをスタートアップに登録して下さい。
   詳細については、Profile Loader の項を参照。


Upgrade
 - 圧縮ファイルを展開します。
 - デバイスマネージャから `鉄騎コントローラ' を選択し、プロパティーの
   ドライバタブにある「ドライバの更新」 ボタンを押します。
 - デバイスドライバのアップグレードウィザードが開始されるので、「この
   デバイスの既知のドライバを表示して、その一覧から選択する」-> 「ディ
   スク使用」 -> 「参照」で `vtchid.inf' を選択し、ドライバをインストー
   ルしなおします。


Profile Loader
 同梱のプログラム vtchidldr.exe は、デバイスドライバに現在の設定を読み
 込むよう指示するものです。
 デバイスを PC に接続した状態で OS を起動すると、設定をデフォルト状態
 から変更してあっても、それが反映されずにデフォルト設定となってしまい
 ます。その場合でも、このプログラムを OS 起動後に実行することで設定の
 読み込みをドライバに指示することができます。
 スタートアップに登録する等しておくとよいかもしれません。

 また、以下のオプションを指定することもできます。

 - vtchidldr    FILENAME
   vtchidldr -l FILENAME : 指定されたファイルをプロファイルとして読み込
			   み、ドライバへ適用します。
			   "-l" オプションは省略することができます。
 - vtchidldr -s FILENAME : 指定されたファイルへ現在のプロファイルを保存
			   します。

 オプションを指定しない場合は、現在の設定の読み込み指示のみ行ないます。


Axes and Buttons
 デフォルト設定での軸/ボタンの割り当て。

 - Axes: AIMING LEVER   => X, Y
         GEAR LEVER     => Z
         SIGHT STICK    => Rx, Ry
         ROTATION LEVER => Rz
         TUNER DIAL     => Slider
 - Buttons:
   - Button  1: MAIN WEAPON
   - Button  2: SUB WEAPON
   - Button  3: LOCK ON
   - Button  4: EJECT CMD
   - Button  5: COCKPIT HATCH
   - Button  6: IGNITION
   - Button  7: START
   - Button  8: MULTI MONITOR - OPEN/CLOSE
   - Button  9: MULTI MONITOR - MAP ZOOM IN/OUT
   - Button 10: MULTI MONITOR - MODE SELECT
   - Button 11: SUB MONITOR MODE SELECT
   - Button 12: MAIN MONITOR ZOOM - IN
   - Button 13: MAIN MONITOR ZOOM - OUT
   - Button 14: F.S.S
   - Button 15: MANIPULATOR
   - Button 16: LINE COLOR CHANGE
   - Button 17: WASHING
   - Button 18: EXTINGUISHER
   - Button 19: CHAFF
   - Button 20: TANK DETACH
   - Button 21: OVERRIDE
   - Button 22: NIGHT SCOPE
   - Button 23: F1
   - Button 24: F2
   - Button 25: F3
   - Button 26: WEAPON CONTROLS - MAIN
   - Button 27: WEAPON CONTROLS - SUB
   - Button 28: WEAPON CONTROLS - MAGAZINE CHANGE
   - Button 29: SIGHT CHANGE - PUSH
   - Button 30: FOOT PEDAL - LEFT
   - Button 31: FOOT PEDAL - CENTER
   - Button 32: FOOT PEDAL - RIGHT
 - Modifiers:
   - Modifier  1: COMMUNICATION TUNER - 1
   - Modifier  2: COMMUNICATION TUNER - 2
   - Modifier  3: COMMUNICATION TUNER - 3
   - Modifier  4: COMMUNICATION TUNER - 4
   - Modifier  5: COMMUNICATION TUNER - 5
   - Modifier  6: FILT CONTROL SYSTEM
   - Modifier  7: OXYGEN SUPPLY SYSTEM
   - Modifier  8: FUEL FLOW RATE
   - Modifier  9: BUFFER MATERIAL
   - Modifier 10: VT-LOCATION MEASUREMENT

 * Axis Throttle はデフォルトでは未割り当て。
 * POV 1、2 はデフォルトでは未割り当て。


Modifiers
 ON/OFF 状態を持つモディファイアが16個あり、それぞれの状態に合わせて、
 軸/ボタン等の設定を変更可能です。

 設定例については Samples の項を参照。


Samples
 samples/ 以下に設定サンプルとしてプロファイルを同梱しています。カスタ
 マイズ方法の参考に多少はなるかもしれません。

 以下はそれぞれのファイルの簡単な説明です。

 - axis.sdp             軸設定の例です。
                        AIMING LEVER にデフォルトと同じ X, Y 軸を、
                        SIGHT CHANGE にデフォルトとは向きが逆の Rx, Ry 軸を、
                        ROTATION LEVER に範囲を中央付近に限定した Rz 軸を、
                        FOOT PEDAL LEFT と RIGHT に RZ 軸を割り当て。

 - buttons.sdp          ボタン設定の例です。
                        MAIN WEAPON にボタン 1 を、
                        SUB WEAPON に on/off が逆のボタン 2 を、
                        F1 ボタンを押したときにボタン 3 の on を、
                        F2 ボタンを押したときにボタン 3 の off を、
                        ROTATION LEVER の左側にボタン 4 を、
                        ROTATION LEVER の右側にボタン 5 を割り当て。

 - modifiers.sdp        モディファイア設定の例です。
                        トグルスイッチ右列3つがそれぞれ mod 1 から 3
                        に対応しており、それぞれの ON/OFF 状態の組合せ
                        によって MAIN WEAPON を押したときに有効となる
                        ボタンが変化します。
                        また、F1 ボタンを押すごとに mod 8 の on/off を
                        切り替え、F2 ボタンを押すごとに mod 9/10 の
                        on/off を切り替えます。

 - delay.sdp            遅延実行 (delay) の例です。
                        MAIN WEAPON を押すと、
                        ボタン 1 on -> 1秒ウェイト -> ボタン 1 off
                        を実行します。

 - apply.sdp            Action list から他の Action list を実行する例
                        です。
                        MAIN WEAPON を押すと、
                        ボタン 9 on -> 1秒ウェイト -> ボタン 9 off ->
                        ボタン 10 on -> 1秒ウェイト -> ボタン 10 off
                        を実行します (前半と後半で別の Action list)。
                        また、SUB WEAPON を押すと、ボタン 1 から 8 ま
                        でを順に on/off し、これを繰り返します。実行中
                        に LOCK ON を押すと mod 1 が on となり、繰り返
                        しが中断されます。

 - mouse.sdp            マウス設定の例です。
                        SIGHT CHANGE にカーソル移動を、MAIN WEAPON と
                        SUB WEAPON にそれぞれボタン 1、2 (左右クリック)
                        を割り当て。

 - keyboard.sdp         キーボード設定の例です。
                        MAIN WEAPON にキー A を、
                        SUB WEAPON にキー A、B、C の連続入力を割り当て。


How to connect XBox controller connector to USB port
  (USB Type A Male <-> USB Type A Female) + (XBox Male <-> XBox Female)
= (USB Type A Male <- ) + ( -> USB Type A Female) +
                              (XBox Male <- ) + ( -> Xbox Female)
= (USB Type A Male <-> Xbox Female) + (XBox Male <-> USB Type A Female)


How to build driver from source
 - Cygwin 及び開発パッケージをインストール (binutils, fileutils, gcc,
   make, w32api)。
 - Cygwin 用 DirectX ヘッダのインストール。
   <http://www.libsdl.org/extras/win32/cygwin/>
 - Borland C++ Compiler 5.5 をインストール (日本語リソースを利用する場
   合のみ)。 <http://www.borland.co.jp/cppbuilder/freecompiler/>
 - ソースファイルを展開。
 - 展開されたディレクトリへ移動し、`make'。
   (日本語リソースを利用しない場合は `make USE_BRCC=no')


TODO (or want to do ...)
 - ボタンを光らせる。
   - タイミングは? (押したとき?、Force Feedback 相当?)
     -> とりあえず、ボタンを押してから離すまでとギアに対応するランプを
        光らせるようにした。
        write report でも光らせることができる。(controller_output_state)
        (Ver 0.1.2)

   - 出力テストタブのテストパターン

 - カスタマイズ
   - ボタン順序
   - 軸とレバーの対応
   - ギア、ダイアルをボタンとして
   - ゲームコントローラのプロパティーから?
     -> 対応 (Ver 0.2.1)

   - キャリブレーション

 - ドキュメント
   - カスタマイズについて

 - ボタン数の制限はなんとかできないのか?
   -> report descriptor として複数の top level collection を返せば複数
      のデバイスに見せられるはずだが、そうすると OS ごと固まってしまう。
      何故? (http://msdn.microsoft.com/library/en-us/intinput/hh/intinput/hidclass_2w13.asp?frame=true)
      -> 非ポーリング (DevicesArePolled = FALSE) なら大丈夫らしい
   -> 割り当てのカスタマイズをできるようにしたのでボタン数は 32 に。
      (Ver 0.2.1)


Link
 - USB.org - HID Tools: <http://www.usb.org/developers/hidpage/>
 - Microsoft Windows Driver Development Kits:
   <http://www.microsoft.com/whdc/ddk/winddk.mspx>
 - HID Game Controllers and DirectInput:
   <http://www.microsoft.com/whdc/hwdev/tech/input/hidgame.mspx>
 - Xbox コントローラ用デバイスドライバ:
   <http://www.katch.ne.jp/~morii/xgc/>
 - XID: <http://www.grooveyardfunk.com/projects/xid/>
 - Dhauzimmer's X36/X45 USB filter driver:
   <http://vega.dyndns.org/x36/>
 - hfsd: <http://www.tamanegi.org/prog/hfsd/>
 - vtchid: <http://www.tamanegi.org/prog/vtchid/>


$Id: README.ja.txt,v 1.12 2004/06/14 14:01:31 hos Exp $
