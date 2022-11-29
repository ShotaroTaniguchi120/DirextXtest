#include "main.h"
#include "game.h"
#include "input.h"
#include "Player.h"
#include "Bg.h"
#include "gameUI.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"
#include "fade.h"
#include "effect.h"
#include "Score.h"
#include "LifeUI.h"
#include "sound.h"
#include "lifeUI.h"
#include "bombUI.h"
#include "manuverUI.h"

//�}�N����`
#define NUM_PLACE (8)	//�X�R�A�̍ő包��
#define TEX_SIZE (70)	//�e�N�X�`���̕\���T�C�Y

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureGame = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGame = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posGame;							//�X�R�A�̈ʒu
int g_EndDelay = 0;								//�I���O�x���J�E���g
bool g_bPoseFrag = false;						//�|�[�Y�t���O
bool g_BossFrag = false;						//�{�X��t���O

//�|���S���̏���������
void InitGame(void)
{
	g_BossFrag = false;

	//�w�i�̏���������
	InitBg();

	//�v���C���[�̏���������
	InitPlayer();

	//�e�̏���������
	InitBullet();
	
	//�G�t�F�N�g�̏���������
	InitEffect();

	//�����̏���������
	InitExplosion();

	//�G�l�~�[�̏���������
	InitEnemy();

	//�Q�[��UI�̏���������
	InitGameUI();

	//�v���C���[UI�̏���������
	InitLifeUI();
	InitBombUI();
	InitManuverUI();

	PlaySound(SOUND_LABEL_BGM001);
	SetEnemy(D3DXVECTOR3(420.0f, 120.0f, 0.0f), 4);

	g_BossFrag = true;
	g_EndDelay = 0;

	//�X�R�A�̏���������
	InitScore();

	srand(time(NULL));

}
//�|���S���̏I������
void UninitGame(void)
{
	//�Q�[��UI�̏I������
	UninitGameUI();
	//�v���C���[�I������
	UninitLifeUI();
	UninitBombUI();
	UninitManuverUI();
	//�w�i�̏I������
	UninitBg();
	//�v���C���[�̏I������
	UninitPlayer();
	//�G�t�F�N�g�̏I������
	UninitEffect();
	//�e�̏I������
	UninitBullet();
	//�G�l�~�[�̏I������
	UninitEnemy();
	//�����̏I������
	UninitExplosion();
	////�X�R�A�̏I������
	//UninitScore();
}
//�|���S���̍X�V����
void UpdateGame(void)
{
	int nCntEnemy, nEnemyNumCnt;

	//�|�[�Y�`�F�b�N
	if (g_bPoseFrag == false)
	{

		//�w�i�̍X�V����
		UpdateBg();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�e�̍X�V����
		UpdateBullet();

		//�G�l�~�[�̍X�V����
		UpdateEnemy();

		//�����̍X�V����
		UpdateExplosion();

		//�Q�[��UI�̍X�V����
		UpdateGameUI();

		//�v���C���[UI�̍X�V����
		UpdateLifeUI();
		UpdateBombUI();
		UpdateManuverUI();

		//�X�R�A�̍X�V����
		UpdateScore();

		Player PlayerData3 = GetPlayer();
		Enemy *pEnemy = GetEnemy();

		nEnemyNumCnt = 0;

		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pEnemy++)
		{
			if (pEnemy->bUse == true)
			{
				nEnemyNumCnt++;
			}
		}

		if (nEnemyNumCnt == 0&&g_BossFrag==false)
		{
			
		}

		if (g_BossFrag == true)
		{
			if (nEnemyNumCnt==0)
			{
				g_EndDelay++;

				if (g_EndDelay == 180)
				{
					SetFade(MODE_RESULT);
				}
				
			}
		}

		if (PlayerData3.bUse == false)
		{
			g_EndDelay++;

			if (g_EndDelay == 30)
			{
				SetFade(MODE_RESULT);
			}
			
		}
	}

	if (GetKeyboardTrigger(DIK_P) == true)
	{//P�L�[�������ꂽ
		g_bPoseFrag = g_bPoseFrag ^ 1;
	}
}

//�|���S���̕`�揈��
void DrawGame(void)
{

	//�w�i�̕`�揈��
	DrawBg();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�e�̕`�揈��
	DrawBullet();

	//�G�l�~�[�̕`�揈��
	DrawEnemy();

	//�����̕`�揈��
	DrawExplosion();

	//�Q�[��UI�̕`�揈��
	DrawGameUI();

	//�v���C���[UI�̕`�揈��
	DrawLifeUI();
	DrawBombUI();
	DrawManuverUI();

	//�X�R�A�̕`�揈��
	DrawScore();
}