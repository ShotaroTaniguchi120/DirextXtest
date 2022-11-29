#include "main.h"
#include "Rankingname.h"
#include "ranking.h"
#include "result.h"
#include "input.h"
#include "sound.h"

//�}�N����`
#define MAX_NAME (10)	//���O�̍ő包��
#define MAX_TEX (3)		//�e�N�X�`���̍ő吔
#define NUM_RANKING (10)//�����L���O�̐�


//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureRankingname[MAX_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingname = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posRankingname;	//�X�R�A�̈ʒu
D3DXVECTOR3 g_posRankingNum;	//���ʂ̈ʒu
int g_aName[10]={};
int g_aPosNum = 0;
int g_Cnt = 0;
int g_Rate = 0;
bool g_bInputend = false;

				//�|���S���̏���������
void InitRankingname(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntRankingname, nCntRankingname2;

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\logo01.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureRankingname[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\input00.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureRankingname[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\input01.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureRankingname[2]);

	g_Cnt = 0;
	g_bInputend = true;
	for (nCntRankingname = 0; nCntRankingname < MAX_NAME; nCntRankingname++)
	{
		g_aName[nCntRankingname] = 78;
	}

	//�ʒu�̏�����
	g_posRankingname = D3DXVECTOR3(320.0f, 120.0f, 0.0f);
	g_posRankingNum = D3DXVECTOR3(260.0f, 120.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_NAME*NUM_RANKING+2+11+1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingname,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffRankingname->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//�}�[�J�[�̏�����
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(300.0f, 650.0f, 0.0f);	//�E���Őݒ�
	pVtx[1].pos = D3DXVECTOR3(360.0f, 650.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300.0f, 681.25f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(360.0f, 681.25f, 0.0f);

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

	pVtx += 4;

	//���x���̏�����
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(500.0f, 560.0f, 0.0f);	//�E���Őݒ�
	pVtx[1].pos = D3DXVECTOR3(680.0f, 560.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(500.0f, 640.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(680.0f, 640.0f, 0.0f);

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

	pVtx += 4;

	//���͉�ʂ̏�����
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(300.0f, 650.0f, 0.0f);	//�E���Őݒ�
	pVtx[1].pos = D3DXVECTOR3(900.0f, 650.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300.0f, 900.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(900.0f, 900.0f, 0.0f);

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

	pVtx += 4;

//�����L���O���ʂ̏�����
	//���_���W�̐ݒ�
	for (nCntRankingname2 = 1; nCntRankingname2 < NUM_RANKING; nCntRankingname2++)
	{
		
			pVtx[0].pos.x = g_posRankingNum.x - 28;	//�E���Őݒ�
			pVtx[0].pos.y = g_posRankingNum.y - 28;
			pVtx[0].pos.z = g_posRankingNum.z;
			pVtx[1].pos.x = g_posRankingNum.x + 28;
			pVtx[1].pos.y = g_posRankingNum.y - 28;
			pVtx[1].pos.z = g_posRankingNum.z;
			pVtx[2].pos.x = g_posRankingNum.x - 28;
			pVtx[2].pos.y = g_posRankingNum.y + 28;
			pVtx[2].pos.z = g_posRankingNum.z;
			pVtx[3].pos.x = g_posRankingNum.x + 28;
			pVtx[3].pos.y = g_posRankingNum.y + 28;
			pVtx[3].pos.z = g_posRankingNum.z;

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�e�N�X�`���̏ꍇ�S�Ĕ���
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(nCntRankingname2 * 0.1f,6 * 0.125f);
			pVtx[1].tex = D3DXVECTOR2(nCntRankingname2 * 0.1f + 0.1f,6* 0.125f);
			pVtx[2].tex = D3DXVECTOR2(nCntRankingname2 * 0.1f,6 * 0.125f + 0.125f);
			pVtx[3].tex = D3DXVECTOR2(nCntRankingname2 * 0.1f + 0.1f,6 * 0.125f + 0.125f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
			
		
		g_posRankingNum.y += 45;
	}

	for (nCntRankingname2 = 0; nCntRankingname2 < 2; nCntRankingname2++)
	{
		pVtx[0].pos.x = g_posRankingNum.x - 28;	//�E���Őݒ�
		pVtx[0].pos.y = g_posRankingNum.y - 28;
		pVtx[0].pos.z = g_posRankingNum.z;
		pVtx[1].pos.x = g_posRankingNum.x + 28;
		pVtx[1].pos.y = g_posRankingNum.y - 28;
		pVtx[1].pos.z = g_posRankingNum.z;
		pVtx[2].pos.x = g_posRankingNum.x - 28;
		pVtx[2].pos.y = g_posRankingNum.y + 28;
		pVtx[2].pos.z = g_posRankingNum.z;
		pVtx[3].pos.x = g_posRankingNum.x + 28;
		pVtx[3].pos.y = g_posRankingNum.y + 28;
		pVtx[3].pos.z = g_posRankingNum.z;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�e�N�X�`���̏ꍇ�S�Ĕ���
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(nCntRankingname2 * 0.1f, 6 * 0.125f);
		pVtx[1].tex = D3DXVECTOR2(nCntRankingname2 * 0.1f + 0.1f, 6 * 0.125f);
		pVtx[2].tex = D3DXVECTOR2(nCntRankingname2 * 0.1f, 6 * 0.125f + 0.125f);
		pVtx[3].tex = D3DXVECTOR2(nCntRankingname2 * 0.1f + 0.1f, 6 * 0.125f + 0.125f);

		g_posRankingNum.x -= 25;
		pVtx += 4;
		
	}
	



	
	//���O���̏�����
	for (nCntRankingname2 = 0; nCntRankingname2 < NUM_RANKING; nCntRankingname2++)
	{
		for (nCntRankingname = 0; nCntRankingname < MAX_NAME; nCntRankingname++)
		{
			pVtx[0].pos.x = g_posRankingname.x - 28;	//�E���Őݒ�
			pVtx[0].pos.y = g_posRankingname.y - 28;
			pVtx[0].pos.z = g_posRankingname.z;
			pVtx[1].pos.x = g_posRankingname.x + 28;
			pVtx[1].pos.y = g_posRankingname.y - 28;
			pVtx[1].pos.z = g_posRankingname.z;
			pVtx[2].pos.x = g_posRankingname.x - 28;
			pVtx[2].pos.y = g_posRankingname.y + 28;
			pVtx[2].pos.z = g_posRankingname.z;
			pVtx[3].pos.x = g_posRankingname.x + 28;
			pVtx[3].pos.y = g_posRankingname.y + 28;
			pVtx[3].pos.z = g_posRankingname.z;

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�e�N�X�`���̏ꍇ�S�Ĕ���
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.1f);
			pVtx[3].tex = D3DXVECTOR2(0.0f + 0.1f, 0.1f);

			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
			g_posRankingname.x += 40;
		}
		g_posRankingname.x -= 400;
		g_posRankingname.y += 45;
	}

	

	

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingname->Unlock();
}
//�|���S���̏I������
void UninitRankingname(void)
{
	int nCnt;


	//�e�N�X�`���̔j��
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_pTextureRankingname[nCnt] != NULL)
		{
			g_pTextureRankingname[nCnt]->Release();
			g_pTextureRankingname[nCnt] = NULL;
		}
	}
	
	//�e�N�X�`���̔j��
	if (g_pVtxBuffRankingname != NULL)
	{
		g_pVtxBuffRankingname->Release();
		g_pVtxBuffRankingname = NULL;
	}
}
//�|���S���̍X�V����
void UpdateRankingname(void)
{
	int nCntRankingname, nNum1, nNum2;
	int nCnt, nCnt2;
	int aTexU[MAX_NAME*NUM_RANKING] = {};	//�e���̐������i�[
	int aTexV[MAX_NAME*NUM_RANKING] = {};	//�e���̐������i�[


	Ranking *pRankingData=GetRanking();

	for (nCnt = 0; nCnt < NUM_RANKING; nCnt++)
	{
		if (pRankingData->bPlayer == true)
		{
			g_bInputend = false;
		}
		pRankingData++;
	}

	pRankingData -= NUM_RANKING;

	for (nCnt2 = 0; nCnt2 < NUM_RANKING; nCnt2++)
	{
		for (nCnt = 0; nCnt < MAX_NAME; nCnt++)
		{
			aTexU[nCnt+nCnt2*10] = pRankingData->aName[nCnt] % 10;
			aTexV[nCnt+nCnt2*10] = pRankingData->aName[nCnt] / 10;
		}
		pRankingData++;
	}

	if (GetKeyboardTrigger(DIK_UP) == true)
	{
		g_aPosNum-=10;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}

	if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		g_aPosNum+=10;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}

	if (GetKeyboardTrigger(DIK_LEFT) == true)
	{

		if (g_aPosNum % 10 == 0)
		{
			g_aPosNum += 9;
		}
		else
		{
			g_aPosNum--;
		}
		PlaySound(SOUND_LABEL_SE_SELECT);
	}

	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{
		if (g_aPosNum % 10 == 9)
		{
			g_aPosNum -= 9;
		}
		else
		{
			g_aPosNum++;
		}
		PlaySound(SOUND_LABEL_SE_SELECT);
	}

	if (g_aPosNum < 0)
	{
		g_aPosNum = 80 + g_aPosNum;
	}
	if (g_aPosNum >= 80)
	{
		g_aPosNum -= 80;
	}

		

	

	//�e�N�X�`���̍X�V
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffRankingname->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	
	pVtx[0].pos = D3DXVECTOR3(300.0f +60*(g_aPosNum % 10), 650.0f + 31.25f*(g_aPosNum /10), 0.0f);	//�E���Őݒ�
	pVtx[1].pos = D3DXVECTOR3(360.0f +60*(g_aPosNum % 10), 650.0f + 31.25f*(g_aPosNum /10), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300.0f +60*(g_aPosNum % 10), 681.25f + 31.25f*(g_aPosNum /10), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(360.0f +60*(g_aPosNum % 10), 681.25f + 31.25f*(g_aPosNum /10), 0.0f);

	pVtx += 56;

	for (nCnt2 = 0; nCnt2 < NUM_RANKING; nCnt2++)
	{

		for (nCnt = 0; nCnt < MAX_NAME; nCnt++)
		{
			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(aTexU[nCnt + nCnt2 * 10] * 0.1f, aTexV[nCnt + nCnt2 * 10]*0.125f);
			pVtx[1].tex = D3DXVECTOR2(aTexU[nCnt + nCnt2 * 10] * 0.1f + 0.1f, aTexV[nCnt + nCnt2 * 10]*0.125f);
			pVtx[2].tex = D3DXVECTOR2(aTexU[nCnt + nCnt2 * 10] * 0.1f, aTexV[nCnt + nCnt2 * 10] * 0.125f +0.125f);
			pVtx[3].tex = D3DXVECTOR2(aTexU[nCnt + nCnt2 * 10] * 0.1f + 0.1f, aTexV[nCnt + nCnt2 * 10] * 0.125f +0.125f);

			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingname->Unlock();

	if (GetKeyboardTrigger(DIK_Z) == true && g_bInputend == false)
	{
		

		if (g_aPosNum == 79)
		{
			for (nCnt = g_Cnt; nCnt < MAX_NAME; nCnt++, g_Cnt++)
			{
				g_aName[nCnt] = 78;
			}
			g_bInputend = true;
			
		}
		else if (g_Cnt >= 10)
		{
			g_bInputend = true;
			
		}
		else
		{
			g_aName[g_Cnt] = g_aPosNum;
			g_Cnt++;
		}
		PlaySound(SOUND_LABEL_SE_COLLECT);
	}

	if (GetKeyboardTrigger(DIK_X) == true && g_Cnt != 0)
	{
		g_Cnt--;
		g_aName[g_Cnt] = 78;
		PlaySound(SOUND_LABEL_SE_CANCEL);
	}
	
	pRankingData -= 10;
	for (nCnt2 = 0; nCnt2 < NUM_RANKING; nCnt2++)
	{
		if (pRankingData->bPlayer == true)
		{
			for (nCnt = 0; nCnt < MAX_NAME; nCnt++)
			{
				pRankingData->aName[nCnt] = g_aName[nCnt];
			}
		}
		pRankingData++;
	}
	
}
//�|���S���̕`�揈��
void DrawRankingname(void)
{
	int nCntRankingname;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

								//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankingname, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRankingname = 0+((int)g_bInputend*3); nCntRankingname < 1+2+11+100; nCntRankingname++)
	{
		if (nCntRankingname == 0)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0,NULL);
		}
		else if (nCntRankingname == 1)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRankingname[0]);
		}
		else if(nCntRankingname==2)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRankingname[1]);
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRankingname[2]);
		}

		
			//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRankingname * 4, 2);
		
		
	}
	

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
	//	2,//�v���~�e�B�u�i�|���S���j�̐�
	//	&g_aVertex[0],//���_���̐擪�A�h���X
	//	sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
}
//�X�R�A�̐ݒ菈��
void GetRankingname(int aName[MAX_NAME])
{
	int nCnt;

	for (nCnt = 0; nCnt < MAX_NAME; nCnt++)
	{
		aName[nCnt] = g_aName[nCnt];
	}
	
}
bool GetInputfrag(void)
{
	return g_bInputend;
}
