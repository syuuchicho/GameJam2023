#include "DxLib.h"
#include "solider.h"
// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "xx2x_xx_ナマエ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 800;

// ウィンドウ縦幅
const int WIN_HEIGHT = 800;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	//--------マウス用変数---------//
	int MouseX = 0;
	int MouseY = 0;
	int MouseR = 16;
	int MouseInput = 0;
	//テスト用エネミー変数
	int enemyX = 600;
	int enemyY = 400;
	int enemyR = 10;

	//----------------------------インスタンス-----------------------------//
	std::list<std::unique_ptr<Solider>>soliders;
	Solider* solider = nullptr;
	const int solBornTime = 5;
	int solBorn = solBornTime;
	int solNo = 5;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//マウス座標
		GetMousePoint(&MouseX, &MouseY);
		//マウス入力
		MouseInput = GetMouseInput();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
#pragma region 兵士
		//死んだ兵士を削除
		soliders.remove_if([](std::unique_ptr<Solider>& solider) {
			return solider->IsDead();
			});
		//左クリックで兵士が生まれる
		if (MouseInput & MOUSE_INPUT_LEFT)
		{
			solBorn--;
		}
		if (solBorn <= 0&&solNo>0)
		{
			//兵を初期化,登録する
			std::unique_ptr<Solider>newSolider = std::make_unique<Solider>();
			newSolider->initialize(MouseX, MouseY);

			soliders.push_back(std::move(newSolider));
			solNo--;
			//カウントダウンリセット
			solBorn = solBornTime;
		}
		
		for (std::unique_ptr<Solider>& solider : soliders)
		{
			solider->Update(enemyX, enemyY, enemyR);
			//右クリックで兵士を消す・solNo+1
			if (MouseInput & MOUSE_INPUT_RIGHT)
			{
				solider->Eraser(MouseX, MouseY, MouseR,solNo);
			}
		}
#pragma endregion

		// 描画処理
		//マウス
		if (MouseInput & MOUSE_INPUT_LEFT)
		{
			DrawCircle(MouseX, MouseY, MouseR, GetColor(255, 0, 0), false);
		}
		else if (MouseInput & MOUSE_INPUT_RIGHT)
		{
			DrawCircle(MouseX, MouseY, MouseR, GetColor(0, 0, 255), false);
		}
		else
		{
			DrawCircle(MouseX, MouseY, MouseR, GetColor(255, 255, 255), false);
		}
		//兵士
		for (std::unique_ptr<Solider>& solider : soliders)
		{
			solider->Draw();
		}
		//敵
		DrawCircle(enemyX, enemyY, enemyR, GetColor(255, 0, 0), true);

		DrawFormatString(20, 20, GetColor(255, 255, 255), "solNo:%d", solNo);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	delete solider;
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
