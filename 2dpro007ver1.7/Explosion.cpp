#include "main.h"
#include "Explosion.h"
#include "input.h"

//�}�N����`
#define MAX_Explosion (128)	//�����̍ő吔

//�����\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DCOLOR col;	//�F
	int nCounterAnimExplosion;	//�A�j���[�V�����J�E���^�[
	int nPatternAnimExplosion;	//�A�j���[�V�����p�^�[���i���o�[
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Explosion;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_Explosion];

//�|���S���̏���������
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntExplosion;

	pDevice = GetDevice();	//�f�o�C�X�̎擾

							//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureExplosion);

	//�����̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(255, 255, 255,100);
		g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
		g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Explosion,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
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
		pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
//�|���S���̏I������
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//�|���S���̍X�V����
void UpdateExplosion(void)
{
	int nCntExplosion;
	//�e�N�X�`���̍X�V
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//�������g�p����Ă���

		 //���_���W�̐ݒ�
			pVtx[0].pos.x = g_aExplosion[nCntExplosion].pos.x + -33;	//�E���Őݒ�
			pVtx[0].pos.y = g_aExplosion[nCntExplosion].pos.y + -33;
			pVtx[0].pos.z = g_aExplosion[nCntExplosion].pos.z + 0.0f;
			pVtx[1].pos.x = g_aExplosion[nCntExplosion].pos.x + 33;
			pVtx[1].pos.y = g_aExplosion[nCntExplosion].pos.y + -33;
			pVtx[1].pos.z = g_aExplosion[nCntExplosion].pos.z + 0.0f;
			pVtx[2].pos.x = g_aExplosion[nCntExplosion].pos.x + -33;
			pVtx[2].pos.y = g_aExplosion[nCntExplosion].pos.y + 33;
			pVtx[2].pos.z = g_aExplosion[nCntExplosion].pos.z + 0.0f;
			pVtx[3].pos.x = g_aExplosion[nCntExplosion].pos.x + 33;
			pVtx[3].pos.y = g_aExplosion[nCntExplosion].pos.y + 33;
			pVtx[3].pos.z = g_aExplosion[nCntExplosion].pos.z + 0.0f;

			g_aExplosion[nCntExplosion].nCounterAnimExplosion++;
			if ((g_aExplosion[nCntExplosion].nCounterAnimExplosion % 8) == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnimExplosion = (g_aExplosion[nCntExplosion].nPatternAnimExplosion + 1);		//�p�^�[��No.���X�V����
			}

			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 1.0f);

			if (g_aExplosion[nCntExplosion].nPatternAnimExplosion >= 8)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
//�|���S���̕`�揈��
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntExplosion;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//�������g�p����Ă���
		 //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
	//	2,//�v���~�e�B�u�i�|���S���j�̐�
	//	&g_aVertex[0],//���_���̐擪�A�h���X
	//	sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
}
//�����̐ݒ菈��
void SetExplosion(D3DXVECTOR3 pos)
{
	int nCntExplosion;

	//���_���W�̐ݒ�
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntExplosion = 0; nCntExplosion < MAX_Explosion; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//�������g�p����Ă��Ȃ�
			g_aExplosion[nCntExplosion].pos = pos;

			g_aExplosion[nCntExplosion].col = D3DXCOLOR(255, 255, 255, 100);
			g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
			g_aExplosion[nCntExplosion].nPatternAnimExplosion = 0;
			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnimExplosion * 0.125f + 0.125f, 1.0f);

			break;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();

	g_aExplosion[nCntExplosion].bUse = true;	//�g�p���Ă����Ԃɂ���
}