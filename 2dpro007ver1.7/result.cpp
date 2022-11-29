#include "main.h"
#include "result.h"
#include "fade.h"
#include "input.h"
#include "ranking.h"
#include "rankingname.h"
#include "Score.h"

//�}�N����`
#define MAX_TEX (2)


//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�ւ̃|�C���^
int g_Deley = 0;


//�|���S���̏���������
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntResult;

	g_Deley = 0;
	

	pDevice = GetDevice();	//�f�o�C�X�̎擾

							//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\resultbg.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureResult[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ResultLogo.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureResult[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntResult = 0; nCntResult < MAX_TEX; nCntResult++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�E���Őݒ�
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 960.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 960.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	InitRanking();
	UpdateRanking();

	SetScore(D3DXVECTOR3(720.0f, 600.0f, 0.0f));
	UpdateScore();

	InitRankingname();
}
//�|���S���̏I������
void UninitResult(void)
{
	int nCnt;

	UninitRanking();
	//�X�R�A�̏I������
	UninitScore();

	

	//�e�N�X�`���̔j��

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_pTextureResult != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}
	}
	
	//�e�N�X�`���̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	

	
}
//�|���S���̍X�V����
void UpdateResult(void)
{
	UpdateRankingname();
	bool bEndfrag = GetInputfrag();

	if (bEndfrag == true)
	{
		/*g_Deley++;
		if (g_Deley >= 120)
		{*/
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_SPACE) == true || GetKeyboardTrigger(DIK_Z) == true)
			{//ENTER�L�[�������ꂽ
			 //���[�h�ݒ�i�Q�[����ʂɈڍs�j
				SetFade(MODE_TITLE);
			}
		/*}*/
	}
	
	
}
//�|���S���̕`�揈��
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCnt;
								//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt*4, 2);
	}
	


	DrawRanking();
	DrawScore();
	DrawRankingname();
}