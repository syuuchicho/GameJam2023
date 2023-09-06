#include "DxLib.h"
#include "solider.h"
// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "xx2x_xx_�i�}�G: �^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 800;

// �E�B���h�E�c��
const int WIN_HEIGHT = 800;

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

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//--------�}�E�X�p�ϐ�---------//
	int MouseX = 0;
	int MouseY = 0;
	int MouseR = 16;
	int MouseInput = 0;
	//�e�X�g�p�G�l�~�[�ϐ�
	int enemyX = 600;
	int enemyY = 400;
	int enemyR = 10;

	//----------------------------�C���X�^���X-----------------------------//
	std::list<std::unique_ptr<Solider>>soliders;
	Solider* solider = nullptr;
	const int solBornTime = 5;
	int solBorn = solBornTime;
	int solNo = 5;

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

		// �X�V����
#pragma region ���m
		//���񂾕��m���폜
		soliders.remove_if([](std::unique_ptr<Solider>& solider) {
			return solider->IsDead();
			});
		//���N���b�N�ŕ��m�����܂��
		if (MouseInput & MOUSE_INPUT_LEFT)
		{
			solBorn--;
		}
		if (solBorn <= 0&&solNo>0)
		{
			//����������,�o�^����
			std::unique_ptr<Solider>newSolider = std::make_unique<Solider>();
			newSolider->initialize(MouseX, MouseY);

			soliders.push_back(std::move(newSolider));
			solNo--;
			//�J�E���g�_�E�����Z�b�g
			solBorn = solBornTime;
		}
		
		for (std::unique_ptr<Solider>& solider : soliders)
		{
			solider->Update(enemyX, enemyY, enemyR);
			//�E�N���b�N�ŕ��m�������EsolNo+1
			if (MouseInput & MOUSE_INPUT_RIGHT)
			{
				solider->Eraser(MouseX, MouseY, MouseR,solNo);
			}
		}
#pragma endregion

		// �`�揈��
		//�}�E�X
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
		//���m
		for (std::unique_ptr<Solider>& solider : soliders)
		{
			solider->Draw();
		}
		//�G
		DrawCircle(enemyX, enemyY, enemyR, GetColor(255, 0, 0), true);

		DrawFormatString(20, 20, GetColor(255, 255, 255), "solNo:%d", solNo);

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
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
