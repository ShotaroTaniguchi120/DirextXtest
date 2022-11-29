#include "main.h"
#include "Player.h"
#include "input.h"
#include "Bullet.h"
#include "Explosion.h"
#include "sound.h"

//�}�N����`
#define MAX_TEXTURE (4)

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTexturePlayer[MAX_TEXTURE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Player g_Player;
float g_fLengthPlayer;	//�Ίp���̒���
float g_fMoveLengthPlayer;	//�Ίp���̒����̈ړ�
float g_fAnglePlayer;	//�Ίp���̊p�x
int g_BulletRate = 0;

//�|���S���̏���������
void InitPlayer(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Player000.png",//�e�N�X�`���̃t�@�C����
		&g_apTexturePlayer[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\jikihantei.png",//�e�N�X�`���̃t�@�C����
		&g_apTexturePlayer[3]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\option00.png",//�e�N�X�`���̃t�@�C����
		&g_apTexturePlayer[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\option00.png",//�e�N�X�`���̃t�@�C����
		&g_apTexturePlayer[1]);


	g_Player.nCounterAnimPlayer = 0;	//�J�E���^�[������������
	g_Player.nPatternAnimPlayer = 0;	//�p�^�[��No.������������

	g_Player.pos = D3DXVECTOR3(420.0f, 900.0f, 0.0f);	//�ʒu��������
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ�������
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//������������
	g_Player.nLife = 2;
	g_Player.nBomb = 2;
	g_Player.nManuver = 0;
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.bSlowMode = false;
	g_Player.bUse = true;
	//�Ίp���̒������Z�o
	g_fLengthPlayer = sqrtf(120.0f*120.0f + 120.0f*120.0f)*0.5f;
	//�Ίp���̊p�x���Z�o����
	g_fAnglePlayer = atan2f(120.0f, 120.0f);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�E���Őݒ�
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//�e�N�X�`���̏ꍇ�S�Ĕ���
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}
//�|���S���̏I������
void UninitPlayer(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_apTexturePlayer[nCnt] != NULL)
		{
			g_apTexturePlayer[nCnt]->Release();
			g_apTexturePlayer[nCnt] = NULL;
		}
	}

	//�e�N�X�`���̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//�|���S���̍X�V����
void UpdatePlayer(void)
{
	int nCnt;

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_Player.bSlowMode = true;
	}
	else if (GetKeyboardPress(DIK_LSHIFT) == false)
	{
		g_Player.bSlowMode = false;
	}

	if (GetKeyboardPress(DIK_Z) == true&&g_Player.state!=PLAYERSTATE_BOMB)
	{//Z�L�[�������ꂽ
		g_BulletRate++;
		if ((g_BulletRate % 5) == 0)
		{
			//�e�̐ݒ�
			SetBullet(g_Player.pos + D3DXVECTOR3(16.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -20.0f, 0.0f),0.0f, BULLETTYPE_PLAYER,BALLISTICSTYPE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetBullet(g_Player.pos - D3DXVECTOR3(16.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -20.0f, 0.0f),0.0f, BULLETTYPE_PLAYER, BALLISTICSTYPE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

	}

	if (GetKeyboardTrigger(DIK_Z) == true && g_Player.state != PLAYERSTATE_BOMB)
	{//Z�L�[�������ꂽ
		PlaySound(SOUND_LABEL_SE_SHOT);
		SetBullet(g_Player.pos + D3DXVECTOR3(45.0f, -500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, BULLETTYPE_PLAYER_01, BALLISTICSTYPE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetBullet(g_Player.pos - D3DXVECTOR3(45.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, BULLETTYPE_PLAYER_02, BALLISTICSTYPE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}


	if (GetKeyboardTrigger(DIK_X) == true)
	{//X�L�[�������ꂽ

		if (g_Player.state != PLAYERSTATE_BOMB&&g_Player.nBomb > 0)
		{
			//�{��������Ԃɂ���
			PlaySound(SOUND_LABEL_SE_BOMB);
			g_Player.state = PLAYERSTATE_BOMB;
			g_Player.nCounterState = 240;
			g_Player.nBomb -- ;
			SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - 550 , 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, BULLETTYPE_PLAYER_BOMB, BALLISTICSTYPE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		
	}

	if (GetKeyboardPress(DIK_LEFT) == true && g_Player.pos.x >= GAMEAREA_MIN)
	{//���L�[�������ꂽ

		if (GetKeyboardPress(DIK_UP) == true && g_Player.pos.y >= GAMEAREA_MIN)
		{
			g_Player.pos.x += sinf(-D3DX_PI*-0.75f)*-10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
			g_Player.pos.y += cosf(-D3DX_PI *-0.75f)*10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true && g_Player.pos.y <= GAMEAREA_HEIGHT_MAX)
		{
			g_Player.pos.x += sinf(-D3DX_PI *-0.105f)*-10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
			g_Player.pos.y += cosf(-D3DX_PI *-0.105f)*10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
		else
		{
			//�ʒu���X�V
			g_Player.pos.x += -10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);

		}

	}
	else if (GetKeyboardPress(DIK_RIGHT) == true && g_Player.pos.x <= GAMEAREA_WIDTH_MAX)
	{//���L�[�������ꂽ

		if (GetKeyboardPress(DIK_UP) == true && g_Player.pos.y >= GAMEAREA_MIN)
		{
			g_Player.pos.x += sinf(-D3DX_PI *0.75f)*-10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
			g_Player.pos.y += cosf(-D3DX_PI *0.75f)*10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true && g_Player.pos.y <= GAMEAREA_HEIGHT_MAX)
		{
			g_Player.pos.x += sinf(-D3DX_PI *-0.105f)*10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
			g_Player.pos.y += cosf(-D3DX_PI * -0.105f)*10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
		else
		{
			//�ʒu���X�V
			g_Player.pos.x += 10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}

	}
	else if (GetKeyboardPress(DIK_UP) == true && g_Player.pos.y >= GAMEAREA_MIN)
	{//���L�[�������ꂽ

		if (GetKeyboardPress(DIK_RIGHT) == false && GetKeyboardPress(DIK_LEFT) == false)
		{
			//�ʒu���X�V
			g_Player.pos.y += -10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
	}
	else if (GetKeyboardPress(DIK_DOWN) == true && g_Player.pos.y <= GAMEAREA_HEIGHT_MAX)
	{//���L�[�������ꂽ

		if (GetKeyboardPress(DIK_RIGHT) == false && GetKeyboardPress(DIK_LEFT) == false)
		{
			//�ʒu���X�V
			g_Player.pos.y += 10.0f / (1.0f + (float)g_Player.bSlowMode*1.2f);
		}
	}
	//if (GetKeyboardPress(DIK_R) == true)
	//{//��L�[�����͂��ꂽ�Ƃ�
	// //�g��
	//	if (g_fLengthPlayer < 110.0f)
	//	{//�T�C�Y�����E�𒴂��Ă��Ȃ����
	//		g_fMoveLengthPlayer += 0.5f;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_F) == true)
	//{//���L�[�����͂��ꂽ�Ƃ�
	// //�k��
	//	if (g_fLengthPlayer >50.0f)
	//	{//�T�C�Y���ŏ����E�𒴂��Ă��Ȃ����
	//		g_fMoveLengthPlayer -= 0.5f;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_Q) == true)
	//{//���L�[�����͂��ꂽ�Ƃ�
	// //����]
	//	g_Player.moverot.z += (D3DX_PI * 0.002f);
	//	if (g_Player.moverot.z > D3DX_PI || g_Player.moverot.z < -D3DX_PI)
	//	{//�p�x�����𒴂����Ƃ�
	//		g_Player.moverot.z *= -1;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_E) == true)
	//{//�E�L�[�����͂��ꂽ�Ƃ�
	//	g_Player.moverot.z += (-D3DX_PI * 0.002f);
	//	if (g_Player.moverot.z > D3DX_PI || g_Player.moverot.z < -D3DX_PI)
	//	{//�p�x�����𒴂����Ƃ�
	//		g_Player.moverot.z *= -1;
	////	}
	//}

	/*g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;*/
	g_Player.rot.z += g_Player.moverot.z;	//��]
	g_fLengthPlayer += g_fMoveLengthPlayer;	//�g��k��
	//�ړ��ʂ��X�V�i�����j
	/*g_Player.move.x += (0.0f - g_Player.move.x)*0.1;
	g_Player.move.y += (0.0f - g_Player.move.y)*0.1;*/
	g_Player.moverot.z += (0.0f - g_Player.moverot.z) * 0.05;	//��]���x
	g_fMoveLengthPlayer += (0.0f - g_fMoveLengthPlayer) * 0.1;	//�g��k��

	for (nCnt = 0; nCnt < 1 + g_Player.bSlowMode+g_Player.bOption*2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			//=========================================================================================================
			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
			pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
			pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + -g_fAnglePlayer) * g_fLengthPlayer;
			pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + -g_fAnglePlayer) * g_fLengthPlayer;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer;
			pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer;
			pVtx[3].pos.z = 0.0f;
			//=========================================================================================================

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			switch (g_Player.state)
			{
			case PLAYERSTATE_BOMB:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NORMAL;
				}
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;

			case PLAYERSTATE_DAMEGE:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NOEFFECT;
					g_Player.nCounterState = 240;
				}
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 50, 50, 255);

				break;

			case PLAYERSTATE_NOEFFECT:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NORMAL;
				}
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 75);

				break;


			default:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//�e�N�X�`���̏ꍇ�S�Ĕ���
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;
			}

			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;

		case 3:
			//=========================================================================================================
			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_Player.pos.x - 5;
			pVtx[0].pos.y = g_Player.pos.y - 5;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_Player.pos.x + 5;
			pVtx[1].pos.y = g_Player.pos.y - 5;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_Player.pos.x - 5;
			pVtx[2].pos.y = g_Player.pos.y + 5;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_Player.pos.x + 5;
			pVtx[3].pos.y = g_Player.pos.y + 5;
			pVtx[3].pos.z = 0.0f;
			//=========================================================================================================

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			switch (g_Player.state)
			{
			

			case PLAYERSTATE_BOMB:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NORMAL;
				}
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;

			case PLAYERSTATE_DAMEGE:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NOEFFECT;
					g_Player.nCounterState = 240;
				}
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 50, 50, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 50, 50, 255);

				break;

			case PLAYERSTATE_NOEFFECT:
				g_Player.nCounterState--;
				if (g_Player.nCounterState <= 0)
				{
					g_Player.state = PLAYERSTATE_NORMAL;
				}
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 75);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 75);

				break;

			default:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//�e�N�X�`���̏ꍇ�S�Ĕ���
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;
			}

			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;

		case 1:
			//=========================================================================================================
			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_Player.pos.x - 15-45;
			pVtx[0].pos.y = g_Player.pos.y - 15;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_Player.pos.x + 15-45;
			pVtx[1].pos.y = g_Player.pos.y - 15;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_Player.pos.x - 15-45;
			pVtx[2].pos.y = g_Player.pos.y + 15;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_Player.pos.x + 15-45;
			pVtx[3].pos.y = g_Player.pos.y + 15;
			pVtx[3].pos.z = 0.0f;
			//=========================================================================================================

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;


				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//�e�N�X�`���̏ꍇ�S�Ĕ���
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			

			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;


		case 2:
			//=========================================================================================================
			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_Player.pos.x - 15 + 45;
			pVtx[0].pos.y = g_Player.pos.y - 15;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_Player.pos.x + 15 + 45;
			pVtx[1].pos.y = g_Player.pos.y - 15;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_Player.pos.x - 15 + 45;
			pVtx[2].pos.y = g_Player.pos.y + 15;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_Player.pos.x + 15 + 45;
			pVtx[3].pos.y = g_Player.pos.y + 15;
			pVtx[3].pos.z = 0.0f;
			//=========================================================================================================

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;


			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//�e�N�X�`���̏ꍇ�S�Ĕ���
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}
//�|���S���̕`�揈��
void DrawPlayer(void)
{
	int nCntPlayer;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

								//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPlayer = 0; nCntPlayer <1 + g_Player.bSlowMode+g_Player.bOption*2; nCntPlayer++)
	{
		if (g_Player.bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTexturePlayer[nCntPlayer]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlayer * 4, 2);
		}
	}
}
//���@�̃q�b�g����
void HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;


	PlaySound(SOUND_LABEL_SE_HITPLAYER);

	if (g_Player.nLife <= 0)
	{
		SetExplosion(g_Player.pos);
		g_Player.bUse = false;
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMEGE;
		g_Player.nCounterState = 10;	//�_���[�W��Ԃ�ۂ���

									//���_���W�̐ݒ�
		VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(
			0,
			0,
			(void**)&pVtx,
			0
		);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 50, 50, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 50, 50, 255);	//�e�N�X�`���̏ꍇ�S�Ĕ���
		pVtx[2].col = D3DCOLOR_RGBA(255, 50, 50, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 50, 50, 255);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();
	}
}
//���@�̃q�b�g����
void ManuverPlayer(void)
{
	g_Player.nManuver++;


	PlaySound(SOUND_LABEL_SE_CANCEL);

}
Player GetPlayer(void)
{
	return g_Player;
}