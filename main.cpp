#include "DxLib.h"
#include "solider.h"
#include "Boss.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "3064_兵隊SIDE";

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


	//------------BGM--------------
	int titleBGM = LoadSoundMem("BGM/title.mp3"); //タイトルBGM
	int playBGM = LoadSoundMem("BGM/playing.mp3");   //プレイBGM
	int clearBGM = LoadSoundMem("BGM/gameClear.mp3"); //クリアBGM
	int overBGM = LoadSoundMem("BGM/gameOver.mp3");   //オーバーBGM

	///////BGM音量//////////
	ChangeVolumeSoundMem(100, titleBGM);
	ChangeVolumeSoundMem(100, playBGM);
	ChangeVolumeSoundMem(100, clearBGM);
	ChangeVolumeSoundMem(100, overBGM);

	//----------SE--------
	int soliderBornSound = LoadSoundMem("BGM/soliderBorn.mp3"); //プレイヤーを出す
	int soliderHitSound = LoadSoundMem("BGM/punch.mp3");        //攻撃音
	
	///////SE音量//////////
	ChangeVolumeSoundMem(100, soliderBornSound);
	ChangeVolumeSoundMem(150, soliderHitSound);

	//--------マウス用変数---------//
	int MouseX = 0;
	int MouseY = 0;
	int MouseR = 16;
	int MouseInput = 0;
	int oldMouseInput = 0;

	//---------シーン---------------//
	int scene = 0;

	//--------ボス--------------//
	Boss* boss = nullptr;
	boss = new Boss();

	//初期化
	boss->Initialize();

	int bossX = 0,
		bossY = 0,
		bossR = 0,
		bossHp = 0;

	bool bossIsHit = false;


	// 画像などのリソースデータ変数宣言
	
	//-------------兵士-----------------------//
	std::list<std::unique_ptr<Solider>>soliders;
	Solider* solider = nullptr;
	const int solBornTime = 5;
	int solBorn = solBornTime;
	int solNo = 50;
	//生きてる兵士の数
	int solAlive = 0;

	int playerX = 0,
		playerY = 0,
		playerR = 0;

	// 画像などのリソースデータ変数宣言
	//兵士
	int soliderWalkGH[4] = {};
	int soliderAtkGH[4] = {};
	//兵士UI
	int soliderUI[10] = {};
	int solNum = 0;
	const int Digit = 2;
	char eachNumber[Digit] = {};

	// 画像などのリソースデータ読み込み
	

	//-----------------画像一覧------------------//
	int soliderGH = LoadGraph("Resource/solider.png");
	//タイトル
	int titleGH = LoadGraph("Resource/title_2.png");
	//チュートリアル
	int tutorial_2GH = LoadGraph("Resource/tutorial_2.png");
	//背景
	int backGroundGH = LoadGraph("Resource/backGround.png");
	//ゲームクリア
	int gameClearGH = LoadGraph("Resource/gameClear.png");
	//ゲームオーバー
	int gameOver = LoadGraph("Resource/gameOver.png");

	//兵士の数
	int soliderNum = LoadGraph("Resource/soliderNum.png");

	//兵士
	soliderGH = LoadGraph("Resource/solider.png");
	//兵士歩行
	LoadDivGraph("Resource/soliderWalk.png", 4, 4, 1, 160, 160, soliderWalkGH);
	//兵士攻撃
	LoadDivGraph("Resource/soliderAttack.png", 4, 4, 1, 160, 160, soliderAtkGH);
	//兵士UI
	LoadDivGraph("Resource/bitmapfont.png", 10, 10, 1, 40, 40, soliderUI);


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
		//1フレーム前のマウス情報
		oldMouseInput = MouseInput;
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

			soliders.remove_if([](std::unique_ptr<Solider>& solider) {
				return solider->IsDead();
				});

			//BGM停止
			StopSoundMem(clearBGM); //クリア
			StopSoundMem(overBGM);  //オーバー

			//タイトルBGMを最初からリスタート
			if (CheckSoundMem(titleBGM) == 0)
			{
				PlaySoundMem(titleBGM, DX_PLAYTYPE_BACK, true);
			}

			//クリックで次のシーン
			if ((MouseInput & MOUSE_INPUT_LEFT) && (oldMouseInput & MOUSE_INPUT_LEFT) == 0)
			{
				scene = 1;
			}
			break;

		case 1: //操作説明

			if ((MouseInput & MOUSE_INPUT_LEFT) && (oldMouseInput & MOUSE_INPUT_LEFT) == 0)
			{
				scene = 2;
			}
			break;

		case 2: //プレイ画面

			//BGM停止
			StopSoundMem(titleBGM); //タイトル
			StopSoundMem(overBGM);  //オーバー(ゲームオーバーからプレイシーンでリトライできるように)
			
			//プレイBGM再生
			if (CheckSoundMem(playBGM) == 0)
			{
				PlaySoundMem(playBGM, DX_PLAYTYPE_LOOP, true);
			}

			//-------------------------兵士---------------------//

			//死んだ兵士を削除
			soliders.remove_if([](std::unique_ptr<Solider>& solider) {
				return solider->IsDead();
				});
			if (MouseX < 440)
			{
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

					//兵士が生まれる効果音
					PlaySoundMem(soliderBornSound, DX_PLAYTYPE_BACK, true);

					soliders.push_back(std::move(newSolider));
					solNo--;
					//生きてる兵士の数
					solAlive++;
					//カウントダウンリセット
					solBorn = solBornTime;
				}
			}

			bossX = boss->GetPosX(),
			bossY = boss->GetPosY(),
			bossR = boss->GetPosR(),
			bossHp = boss->GetHp();

			
			//兵士毎フレーム処理
			for (std::unique_ptr<Solider>& solider : soliders)
			{
				solider->Update(bossX, bossY, bossR);
				solider->Attack(bossX, bossY, bossR, bossHp, soliderHitSound, bossIsHit);

				//右クリックで兵士を消す・solNo+1
				if (MouseInput & MOUSE_INPUT_RIGHT)
				{
					solider->Eraser(MouseX, MouseY, MouseR, solNo,solAlive);
				}
				playerX = solider->GetPosX(),
				playerY = solider->GetPosY(),
				playerR = solider->GetPosR();

			}
			//-----------ボス-----------------------//
			boss->SetIsHit(bossIsHit);
			boss->Update();
			boss->SetHp(bossHp);

			//メテオが予兆の時は当たらない判定
			if (boss->attackflag == 1)
			{
				for (std::unique_ptr<Solider>& solider : soliders)
				{
					playerX = solider->GetPosX(),
					playerY = solider->GetPosY(),
					playerR = solider->GetPosR();
					//メテオ1(円)とプレイヤーの当たり判定・メテオ2(円)とプレイヤーの当たり判定
					if ((meteorR + playerR) * (meteorR + playerR)
						>= (playerX - meteorX) * (playerX - meteorX) + (playerY - meteorY) * (playerY - meteorY)
						||
						((playerR + meteorR1) * (playerR + meteorR1)
							>= (playerX - meteorX1) * (playerX - meteorX1) + (playerY - meteorY1) * (playerY - meteorY1)))
					{
						//当たったら消える
						solider->Dead();
						solAlive--;
					}
				}
			}
			bossIsHit = false;

			//ゲームクリア
			if (bossHp <= 0)
			{
				scene = 3;
			}

			//ゲームオーバー
			if (solAlive == 0 && solNo == 0)
			{
				scene = 4;
			}

			break;

		case 3: //ゲームクリア

			//初期化
			boss->Reset();
			for (std::unique_ptr<Solider>& solider : soliders)
			{
				solider->Dead();
				solider->Reset();
			}

			solNo = 50;
			solAlive = 0;

			//プレイBGM停止
			StopSoundMem(playBGM);

			//クリアBGM再生
			if (CheckSoundMem(clearBGM) == 0)
			{
				PlaySoundMem(clearBGM, DX_PLAYTYPE_LOOP, true);
			}

			if ((MouseInput & MOUSE_INPUT_LEFT) && (oldMouseInput & MOUSE_INPUT_LEFT) == 0)
			{
				scene = 0;
			}

			break;

		case 4: //ゲームオーバー

			//初期化
			boss->Reset();
			for (std::unique_ptr<Solider>& solider : soliders)
			{
				solider->Dead();
				solider->Reset();
			}
			solNo = 50;
			solAlive = 0;

			//プレイBGM停止
			StopSoundMem(playBGM);

			//オーバーBGM再生
			if (CheckSoundMem(overBGM) == 0)
			{
				PlaySoundMem(overBGM, DX_PLAYTYPE_LOOP, true);
			}

			if ((MouseInput & MOUSE_INPUT_LEFT) && (oldMouseInput & MOUSE_INPUT_LEFT) == 0)
			{
				scene = 0;
			}

			break;

		}

		

		

#pragma endregion


#pragma region 描画処理

		switch (scene)
		{
		case 0: //タイトル

			//タイトル画像
			DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, titleGH, true);

			break;

		case 1: //操作説明

			DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, tutorial_2GH, true);

			break;

		case 2: //プレイ画面

			//背景描画
			DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, backGroundGH, true);

			//兵士の数
			DrawExtendGraph(0, 0, 700,400,soliderNum, true);

			//----ボス------------//
			boss->Draw();
			
			//----------------------兵士--------------------//
			for (std::unique_ptr<Solider>& solider : soliders)
			{
				solider->Draw(soliderGH);
			}

			//兵士UI描画
			for (int i = 0; i < Digit; i++)
			{
				solNum = solNo;

				int CalcDigit = 10;
				for (int i = 0; i < Digit; i++)
				{
					eachNumber[i] = solNum / CalcDigit;
					solNum = solNum % CalcDigit;
					CalcDigit = CalcDigit / 10;
				}

				DrawGraph(10 + i * 40, 20, soliderUI[eachNumber[i]], true);
			}

			//----真ん中の線------//
			DrawLine(440, 0, 440, 720, GetColor(255, 255, 255), true);

			break;

		case 3 ://ゲームクリア

			//ゲームクリア画像
			DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, gameClearGH, true);

				break;

		case 4: //ゲームオーバー

			//ゲームオーバー画像
			DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, gameOver, true);

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

		/*DrawFormatString(0, 240, GetColor(255, 255, 255), "プレイヤー/%d:%d:%d", playerX, playerY, playerR);
		DrawFormatString(0, 260, GetColor(255, 255, 255), "%d", scene);*/
		DrawFormatString(0, 280, GetColor(255, 255, 255), "%d", solAlive);

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

	// 全グラフィックを初期化
	InitGraph();

	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
