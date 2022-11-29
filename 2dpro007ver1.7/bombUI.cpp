#include "main.h"
#include "BombUI.h"
#include "Player.h"

//�}�N����`
#define NUM_PLACE (5)	//�X�R�A�̍ő包��
#define TEX_SIZE (70)	//�e�N�X�`���̕\���T�C�Y

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBombUI = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBombUI = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posBombUI;	//�X�R�A�̈ʒu
int g_nBombUI;	//�X�R�A�̒l

				//�|���S���̏���������
void InitBombUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntBombUI;

	pDevice = GetDevice();	//�f�o�C�X�̎擾

							//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bombstar.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureBombUI);

	//�X�R�A�̏�����
	g_nBombUI = 2;

	//�ʒu�̏�����
	g_posBombUI = D3DXVECTOR3(980.0f, 315.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBombUI,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBombUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntBombUI = 0; nCntBombUI < NUM_PLACE; nCntBombUI++)
	{
		pVtx[0].pos.x = g_posBombUI.x - 20;	//�E���Őݒ�
		pVtx[0].pos.y = g_posBombUI.y - 20;
		pVtx[0].pos.z = g_posBombUI.z;
		pVtx[1].pos.x = g_posBombUI.x + 20;
		pVtx[1].pos.y = g_posBombUI.y - 20;
		pVtx[1].pos.z = g_posBombUI.z;
		pVtx[2].pos.x = g_posBombUI.x - 20;
		pVtx[2].pos.y = g_posBombUI.y + 20;
		pVtx[2].pos.z = g_posBombUI.z;
		pVtx[3].pos.x = g_posBombUI.x + 20;
		pVtx[3].pos.y = g_posBombUI.y + 20;
		pVtx[3].pos.z = g_posBombUI.z;

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
	g_pVtxBuffBombUI->Unlock();
}
//�|���S���̏I������
void UninitBombUI(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBombUI != NULL)
	{
		g_pTextureBombUI->Release();
		g_pTextureBombUI = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtxBuffBombUI != NULL)
	{
		g_pVtxBuffBombUI->Release();
		g_pVtxBuffBombUI = NULL;
	}
}
//�|���S���̍X�V����
void UpdateBombUI(void)
{
	int nCntBombUI, nNum1, nNum2;

	//�e�N�X�`���̍X�V
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBombUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);


	for (nCntBombUI = 0; nCntBombUI <NUM_PLACE; nCntBombUI++)
	{
		pVtx[0].pos.x = g_posBombUI.x - 20 + nCntBombUI * 40;	//�E���Őݒ�
		pVtx[0].pos.y = g_posBombUI.y - 20;
		pVtx[0].pos.z = g_posBombUI.z;
		pVtx[1].pos.x = g_posBombUI.x + 20 + nCntBombUI * 40;
		pVtx[1].pos.y = g_posBombUI.y - 20;
		pVtx[1].pos.z = g_posBombUI.z;
		pVtx[2].pos.x = g_posBombUI.x - 20 + nCntBombUI * 40;
		pVtx[2].pos.y = g_posBombUI.y + 20;
		pVtx[2].pos.z = g_posBombUI.z;
		pVtx[3].pos.x = g_posBombUI.x + 20 + nCntBombUI * 40;
		pVtx[3].pos.y = g_posBombUI.y + 20;
		pVtx[3].pos.z = g_posBombUI.z;

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
	g_pVtxBuffBombUI->Unlock();
}
//�|���S���̕`�揈��
void DrawBombUI(void)
{
	int nCntBombUI;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	Player PlayerLife = GetPlayer();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBombUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBombUI);

	for (nCntBombUI = 0; nCntBombUI < PlayerLife.nBomb; nCntBombUI++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBombUI * 4, 2);
	}

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
	//	2,//�v���~�e�B�u�i�|���S���j�̐�
	//	&g_aVertex[0],//���_���̐擪�A�h���X
	//	sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
}