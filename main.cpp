#include "DxLib.h"
#include "solider.h"
#include "Boss.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "GameJam2023";

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 720;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//�}�E�X�p�ϐ�
	int MouseX = 0;
	int MouseY = 0;
	int MouseR = 16;
	int MouseInput = 0;

	//�V�[��
	int scene = 0;

	//�{�X
	Boss* boss = nullptr;
	boss = new Boss();

	boss->Initialize();

	int bossX = boss->GetPosX(),
		bossY = boss->GetPosY(),
		bossR = boss->GetPosR(),
		bossHp = 0;

	//���m
	std::list<std::unique_ptr<Solider>>soliders;
	Solider* solider = nullptr;
	const int solBornTime = 5;
	int solBorn = solBornTime;
	int solNo = 100;

	int playerX = 0,
		playerY = 0,
		playerR = 0;
	
	//���\�[�X�ϐ�
	int soliderWalkGH[4] = {};
	int soliderAtkGH[4] = {};
	int soliderBornSound = 0;
	int soliderHitSound = 0;
	//-----------------�摜�ꗗ------------------//
	

	int soliderGH = LoadGraph("Resource/solider.png");
	//�w�i
	int backGroundGH = LoadGraph("Resource/backGround.png");
	//���m���s
	LoadDivGraph("Resource/soliderWalk.png", 4, 4, 1, 160, 160, soliderWalkGH);
	//���m�U��
	LoadDivGraph("Resource/soliderAttack.png", 4, 4, 1, 160, 160, soliderAtkGH);

	//-----------------BGM�ꗗ----------------------//
	soliderBornSound= LoadSoundMem("BGM/soliderBorn.mp3");
	soliderHitSound = LoadSoundMem("BGM/punch.mp3");


	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//�}�E�X���W
		GetMousePoint(&MouseX, &MouseY);
		//�}�E�X����
		MouseInput = GetMouseInput();
		//---------  ��������v���O�������L�q  ----------//

#pragma region �X�V����

		int meteorX = boss->GetMeteorX(),
			meteorY = boss->GetMeteorY(),
			meteorR = boss->GetMeteorR(),
			meteorX1 = boss->GetMeteorX1(),
			meteorY1 = boss->GetMeteorY1(),
			meteorR1 = boss->GetMeteorR1();

		//-------------------------���m---------------------//
		//���񂾕��m���폜
		soliders.remove_if([](std::unique_ptr<Solider>& solider) {
			return solider->IsDead();
			});
		//���N���b�N�ŕ��m�����܂��
		if (MouseInput & MOUSE_INPUT_LEFT)
		{
			solBorn--;
		}
		if (solBorn <= 0 && solNo > 0)
		{
			//����������,�o�^����
			std::unique_ptr<Solider>newSolider = std::make_unique<Solider>();
			newSolider->initialize(MouseX, MouseY,soliderGH,soliderWalkGH, soliderAtkGH);
			//���m�����܂����ʉ�
			PlaySoundMem(soliderBornSound, DX_PLAYTYPE_BACK, true);
			soliders.push_back(std::move(newSolider));
			solNo--;
			//�J�E���g�_�E�����Z�b�g
			solBorn = solBornTime;
		}

		int bossX = boss->GetPosX(),
			bossY = boss->GetPosY(),
			bossR = boss->GetPosR(),
			bossHp = boss->GetHp();

		//���m���t���[������
		for (std::unique_ptr<Solider>& solider : soliders)
		{
			solider->Update(bossX, bossY, bossR);
			solider->Attack(bossX, bossY, bossR, bossHp, soliderHitSound);
			//�E�N���b�N�ŕ��m�������EsolNo+1
			if (MouseInput & MOUSE_INPUT_RIGHT)
			{
				solider->Eraser(MouseX, MouseY, MouseR, solNo);
			}
		}

		//-------------------�V�[���Ǘ�-----------------------//
		switch (scene)
		{
		case 0: //�^�C�g��

			break;

		case 1: //�������

			break;

		case 2: //�v���C���

			break;

		case 3: //�Q�[���N���A

			break;

		case 4: //�Q�[���I�[�o�[

			break;

		}
		//-------------------�{�X---------------//
		boss->SetHp(bossHp);
		boss->Update();
		//���e�I���\���̎��͓�����Ȃ�����
		if (boss->attackflag == 1)
		{
			for (std::unique_ptr<Solider>& solider : soliders)
			{
					playerX = solider->GetPosX(),
					playerY = solider->GetPosY(),
					playerR = solider->GetPosR();
				//���e�I1(�~)�ƃv���C���[�̓����蔻��E���e�I2(�~)�ƃv���C���[�̓����蔻��
				if ((meteorR + playerR) * (meteorR + playerR)
					>= (playerX - meteorX) * (playerX - meteorX) + (playerY - meteorY) * (playerY - meteorY)
					||
					((playerR + meteorR1) * (playerR + meteorR1)
					>= (playerX - meteorX1) * (playerX - meteorX1) + (playerY - meteorY1) * (playerY - meteorY1)))
				{
					//���������������
					solider->Dead();
				}
			}
		}
		boss->SetHp(bossHp);
#pragma endregion

#pragma region �`�揈��
		//�w�i�`��
		DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, backGroundGH, true);

		//----�{�X------------//
		boss->Draw();

		//----------------------���m--------------------//
		for (std::unique_ptr<Solider>& solider : soliders)
		{
			solider->Draw(soliderGH);
		}

		//----�}�E�X----------//
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

		//----�^�񒆂̐�------//
		DrawLine(440, 0, 440, 720, GetColor(255, 255, 255), true);

#pragma endregion
		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	delete solider;
	delete boss;

	// �S�O���t�B�b�N��������
	InitGraph();

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}