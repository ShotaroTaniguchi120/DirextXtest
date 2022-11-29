#include "main.h"
#include "LifeUI.h"
#include "Player.h"

//�}�N����`
#define NUM_PLACE (5)	//�X�R�A�̍ő包��
#define TEX_SIZE (70)	//�e�N�X�`���̕\���T�C�Y

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureLifeUI = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLifeUI = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posLifeUI;	//�X�R�A�̈ʒu
int g_nLifeUI;	//�X�R�A�̒l

//�|���S���̏���������
void InitLifeUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntLifeUI;

	pDevice = GetDevice();	//�f�o�C�X�̎擾

							//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\lifestar.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureLifeUI);

	//�X�R�A�̏�����
	g_nLifeUI = 2;

	//�ʒu�̏�����
	g_posLifeUI = D3DXVECTOR3(980.0f, 240.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLifeUI,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffLifeUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntLifeUI = 0; nCntLifeUI < NUM_PLACE; nCntLifeUI++)
	{
		pVtx[0].pos.x = g_posLifeUI.x - 20;	//�E���Őݒ�
		pVtx[0].pos.y = g_posLifeUI.y - 20;
		pVtx[0].pos.z = g_posLifeUI.z;
		pVtx[1].pos.x = g_posLifeUI.x + 20;
		pVtx[1].pos.y = g_posLifeUI.y - 20;
		pVtx[1].pos.z = g_posLifeUI.z;
		pVtx[2].pos.x = g_posLifeUI.x - 20;
		pVtx[2].pos.y = g_posLifeUI.y + 20;
		pVtx[2].pos.z = g_posLifeUI.z;
		pVtx[3].pos.x = g_posLifeUI.x + 20;
		pVtx[3].pos.y = g_posLifeUI.y + 20;
		pVtx[3].pos.z = g_posLifeUI.z;

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
	g_pVtxBuffLifeUI->Unlock();
}
//�|���S���̏I������
void UninitLifeUI(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureLifeUI != NULL)
	{
		g_pTextureLifeUI->Release();
		g_pTextureLifeUI = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtxBuffLifeUI != NULL)
	{
		g_pVtxBuffLifeUI->Release();
		g_pVtxBuffLifeUI = NULL;
	}
}
//�|���S���̍X�V����
void UpdateLifeUI(void)
{
	int nCntLifeUI, nNum1, nNum2;
	
	//�e�N�X�`���̍X�V
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffLifeUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);


	for (nCntLifeUI = 0; nCntLifeUI <NUM_PLACE ; nCntLifeUI++)
	{
		pVtx[0].pos.x = g_posLifeUI.x-20+nCntLifeUI*40;	//�E���Őݒ�
		pVtx[0].pos.y = g_posLifeUI.y - 20;
		pVtx[0].pos.z = g_posLifeUI.z;
		pVtx[1].pos.x = g_posLifeUI.x+20+nCntLifeUI*40;
		pVtx[1].pos.y = g_posLifeUI.y - 20;
		pVtx[1].pos.z = g_posLifeUI.z;
		pVtx[2].pos.x = g_posLifeUI.x-20+nCntLifeUI*40;
		pVtx[2].pos.y = g_posLifeUI.y + 20;
		pVtx[2].pos.z = g_posLifeUI.z;
		pVtx[3].pos.x = g_posLifeUI.x+20+nCntLifeUI*40;
		pVtx[3].pos.y = g_posLifeUI.y + 20;
		pVtx[3].pos.z = g_posLifeUI.z;

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
	g_pVtxBuffLifeUI->Unlock();
}
//�|���S���̕`�揈��
void DrawLifeUI(void)
{
	int nCntLifeUI;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	Player PlayerLife = GetPlayer();

								//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLifeUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLifeUI);

	for (nCntLifeUI = 0; nCntLifeUI <  PlayerLife.nLife - 1; nCntLifeUI++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLifeUI * 4, 2);
	}

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
	//	2,//�v���~�e�B�u�i�|���S���j�̐�
	//	&g_aVertex[0],//���_���̐擪�A�h���X
	//	sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
}