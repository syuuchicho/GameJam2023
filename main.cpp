#include "DxLib.h"
#include "solider.h"
#include "Boss.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LE3D_09_サクライヒロト: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 720;

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

	//---------シーン---------------//
	int scene = 0;

	//--------ボス--------------//
	Boss* boss = nullptr;
	boss = new Boss();

	boss->Initialize();

	int bossX = 0,
		bossY = 0,
		bossR = 0,
		bossHp = 0;


	// 画像などのリソースデータ変数宣言
	//ボス画像
	
	
	//-------------兵士-----------------------//
	std::list<std::unique_ptr<Solider>>soliders;
	Solider* solider = nullptr;
	const int solBornTime = 5;
	int solBorn = solBornTime;
	int solNo = 100;

	int playerX = 0,
		playerY = 0,
		playerR = 0;

	int playerDead = 0;

	// 画像などのリソースデータ変数宣言
	//兵士
	int soliderGH = 0;
	int soliderWalkGH[4] = {};
	int soliderAtkGH[4] = {};

	// 画像などのリソースデータ読み込み
	//背景
	int backGroundGH = LoadGraph("Resource/backGround.png");
	
	//兵士
	soliderGH = LoadGraph("Resource/solider.png");
	//兵士歩行
	LoadDivGraph("Resource/soliderWalk.png", 4, 4, 1, 160, 160, soliderWalkGH);
	//兵士攻撃
	LoadDivGraph("Resource/soliderAttack.png", 4, 4, 1, 160, 160, soliderAtkGH);


	// 最新のキーボード情報用
	char keys[256] = {0};

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = {0};

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

#pragma region 更新処理

		int meteorX = boss->GetMeteorX(),
			meteorY = boss->GetMeteorY(),
			meteorR = boss->GetMeteorR(),
			meteorX1 = boss->GetMeteorX1(),
			meteorY1 = boss->GetMeteorY1(),
			meteorR1 = boss->GetMeteorR1();
		

		//--------シーン-----------------------//
		switch (scene)
		{
		case 0: //タイトル

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) && scene == 0)
			{
				scene = 1;
			}
			break;

		case 1: //操作説明

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) && scene == 1)
			{
				scene = 2;
			}
			break;

		case 2: //プレイ画面

			
			//-------------------------兵士---------------------//

			//死んだ兵士を削除
			soliders.remove_if([](std::unique_ptr<Solider>& solider) {
				return solider->IsDead();
				});
			//左クリックで兵士が生まれる
			if (MouseInput & MOUSE_INPUT_LEFT)
			{
				solBorn--;
			}
			if (solBorn <= 0 && solNo > 0)
			{
				//兵を初期化,登録する
				std::unique_ptr<Solider>newSolider = std::make_unique<Solider>();
				newSolider->initialize(MouseX, MouseY, soliderGH, soliderWalkGH, soliderAtkGH);
				soliders.push_back(std::move(newSolider));
				solNo--;
				//カウントダウンリセット
				solBorn = solBornTime;
			}

			bossX = boss->GetPosX(),
			bossY = boss->GetPosY(),
			bossR = boss->GetPosR(),
			bossHp = boss->GetHp();

			
			//兵士毎フレーム処理
			for (std::unique_ptr<Solider>& solider : soliders)
			{
				solider->Update(bossX, bossY, bossR);
				solider->Attack(bossX, bossY, bossR, bossHp);
				//右クリックで兵士を消す・solNo+1
				if (MouseInput & MOUSE_INPUT_RIGHT)
				{
					solider->Eraser(MouseX, MouseY, MouseR, solNo);
				}
				playerX = solider->GetPosX(),
				playerY = solider->GetPosY(),
				playerR = solider->GetPosR();
			}
			//-----------ボス-----------------------//

			
			boss->Update();
			boss->SetHp(bossHp);

			//メテオが予兆の時は当たらない判定
			if (boss->attackflag == 1)
			{
				for (std::unique_ptr<Solider>& solider : soliders)
				{
					//メテオ1(円)とプレイヤーの当たり判定
					if ((meteorR + playerR) * (meteorR + playerR)
						>= (playerX - meteorX) * (playerX - meteorX) + (playerY - meteorY) * (playerY - meteorY))
					{
						solider->Dead();
					}
					//メテオ2(円)とプレイヤーの当たり判定
					if ((playerR + meteorR1) * (playerR + meteorR1)
						>= (playerX - meteorX1) * (playerX - meteorX1) + (playerY - meteorY1) * (playerY - meteorY1))
					{
						//当たったら消える
						solider->Dead();
					}
				}
			}

			break;

		case 3: //ゲームクリア

			break;

		case 4: //ゲームオーバー

			break;

		}

		

		

#pragma endregion


#pragma region 描画処理

		switch (scene)
		{
		case 0: //タイトル

			break;

		case 1: //操作説明

			break;

		case 2: //プレイ画面

			//背景描画
			DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, backGroundGH, true);


			//----ボス------------//
			boss->Draw();

			//----------------------兵士--------------------//
			for (std::unique_ptr<Solider>& solider : soliders)
			{
				solider->Draw(soliderGH);
			}

			//----真ん中の線------//
			DrawLine(440, 0, 440, 720, GetColor(255, 255, 255), true);

			break;

		case 3 ://ゲームクリア

				break;

		case 4: //ゲームオーバー

				break;

		}

		//----マウス----------//
		if (MouseInput & MOUSE_INPUT_LEFT)
		{
			DrawCircle(MouseX, MouseY, MouseR, GetColor(255, 0, 0), false);
		}
		else
		{
			DrawCircle(MouseX, MouseY, MouseR, GetColor(255, 255, 255), false);
		}

		DrawFormatString(0, 240, GetColor(255, 255, 255), "プレイヤー/%d:%d:%d", playerX, playerY, playerR);
		DrawFormatString(0, 260, GetColor(255, 255, 255), "%d", scene);

#pragma endregion
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
	delete boss;

	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
