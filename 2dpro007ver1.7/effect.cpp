#include "main.h"
#include "Effect.h"
#include "input.h"

//�}�N����`
#define MAX_Effect (4096)	//�����̍ő吔

//�����\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DCOLOR col;		//�F
	float fRadius;		//���a
	int nLife;			//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Effect;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_Effect];

//�|���S���̏���������
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntEffect;

	pDevice = GetDevice();	//�f�o�C�X�̎擾

							//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",//�e�N�X�`���̃t�@�C����
		&g_pTextureEffect);

	//�����̏�����
	for (nCntEffect = 0; nCntEffect < MAX_Effect; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(255, 255, 0, 100);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = 30;
		g_aEffect[nCntEffect].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Effect,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntEffect = 0; nCntEffect < MAX_Effect; nCntEffect++)
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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�e�N�X�`���̏ꍇ�S�Ĕ���
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
//�|���S���̏I������
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//�|���S���̍X�V����
void UpdateEffect(void)
{
	int nCntEffect;
	//�e�N�X�`���̍X�V
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntEffect = 0; nCntEffect < MAX_Effect; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���
			g_aEffect[nCntEffect].col -= D3DXCOLOR(0, 0, 0, 0.1f);
		 //���_���W�̐ݒ�
			pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x + -g_aEffect[nCntEffect].fRadius;	//�E���Őݒ�
			pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y + -g_aEffect[nCntEffect].fRadius;
			pVtx[0].pos.z = g_aEffect[nCntEffect].pos.z + 0.0f;
			pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
			pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y + -g_aEffect[nCntEffect].fRadius;
			pVtx[1].pos.z = g_aEffect[nCntEffect].pos.z + 0.0f;
			pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x + -g_aEffect[nCntEffect].fRadius;
			pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
			pVtx[2].pos.z = g_aEffect[nCntEffect].pos.z + 0.0f;
			pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
			pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
			pVtx[3].pos.z = g_aEffect[nCntEffect].pos.z + 0.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col);
			pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col);	//�e�N�X�`���̏ꍇ�S�Ĕ���
			pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col);
			pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col);

			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_aEffect[nCntEffect].nLife--;	//�����̃J�E���g�_�E��
			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
//�|���S���̕`�揈��
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntEffect;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEffect);
	
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_Effect; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�������g�p����Ă���
		 //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}
	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//�G�t�F�N�g�̐ݒ菈��
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;

	//���_���W�̐ݒ�
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_Effect; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//�������g�p����Ă��Ȃ�
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;	//�g�p���Ă����Ԃɂ���
			break;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
	
}