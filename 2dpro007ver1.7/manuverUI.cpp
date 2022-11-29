#include "main.h"
#include "ManuverUI.h"
#include "Player.h"

//�}�N����`
#define NUM_PLACE (3)	//�X�R�A�̍ő包��
#define TEX_SIZE (70)	//�e�N�X�`���̕\���T�C�Y

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureManuver = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffManuver = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posManuver;	//�X�R�A�̈ʒu
int g_nManuver;	//�X�R�A�̒l

				//�|���S���̏���������
void InitManuverUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntManuver;

	pDevice = GetDevice();	//�f�o�C�X�̎擾

							//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureManuver);

	//�X�R�A�̏�����
	g_nManuver = 0;

	//�ʒu�̏�����
	g_posManuver = D3DXVECTOR3(1005.0f, 423.0f, 0.0);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffManuver,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffManuver->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntManuver = 0; nCntManuver < NUM_PLACE; nCntManuver++)
	{
		pVtx[0].pos.x = g_posManuver.x - 35;	//�E���Őݒ�
		pVtx[0].pos.y = g_posManuver.y - 35;
		pVtx[0].pos.z = g_posManuver.z;
		pVtx[1].pos.x = g_posManuver.x + 35;
		pVtx[1].pos.y = g_posManuver.y - 35;
		pVtx[1].pos.z = g_posManuver.z;
		pVtx[2].pos.x = g_posManuver.x - 35;
		pVtx[2].pos.y = g_posManuver.y + 35;
		pVtx[2].pos.z = g_posManuver.z;
		pVtx[3].pos.x = g_posManuver.x + 35;
		pVtx[3].pos.y = g_posManuver.y + 35;
		pVtx[3].pos.z = g_posManuver.z;

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
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f + 0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		g_posManuver.x += 35;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffManuver->Unlock();
}
//�|���S���̏I������
void UninitManuverUI(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureManuver != NULL)
	{
		g_pTextureManuver->Release();
		g_pTextureManuver = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtxBuffManuver != NULL)
	{
		g_pVtxBuffManuver->Release();
		g_pVtxBuffManuver = NULL;
	}
}
//�|���S���̍X�V����
void UpdateManuverUI(void)
{
	int nCntManuver, nNum1, nNum2;
	int aTexU[NUM_PLACE] = {};	//�e���̐������i�[

	Player PlayerData4 = GetPlayer();
	g_nManuver = PlayerData4.nManuver;

	for (nCntManuver = 0; nCntManuver < NUM_PLACE; nCntManuver++)
	{
		nNum1 = pow(10, nCntManuver + 1);
		nNum2 = pow(10, nCntManuver);
		aTexU[nCntManuver] = (g_nManuver % nNum1) / nNum2;
	}

	//�e�N�X�`���̍X�V
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffManuver->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	pVtx += 8;

	for (nCntManuver = 0; nCntManuver < NUM_PLACE; nCntManuver++)
	{
		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aTexU[nCntManuver] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aTexU[nCntManuver] * 0.1f) + 0.1f, 1.0f);

		pVtx -= 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffManuver->Unlock();
}
//�|���S���̕`�揈��
void DrawManuverUI(void)
{
	int nCntManuver;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

								//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffManuver, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureManuver);

	for (nCntManuver = 0; nCntManuver < NUM_PLACE; nCntManuver++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntManuver * 4, 2);
	}

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
	//	2,//�v���~�e�B�u�i�|���S���j�̐�
	//	&g_aVertex[0],//���_���̐擪�A�h���X
	//	sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
}
////�X�R�A�̐ݒ菈��
//void SetManuver(int nManuver)
//{
//	int aTexU[NUM_PLACE];	//�e���̐������i�[
//	int nCntManuver;
//
//	g_nManuver = nManuver;
//	for (nCntManuver = NUM_PLACE; nCntManuver <= 0; nCntManuver--)
//	{
//		aTexU[nCntManuver] = g_nManuver % (10 ^ (nCntManuver + 1)) / (10 ^ nCntManuver);
//	}
//
//	//���_���W�̐ݒ�
//	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^
//
//					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
//	g_pVtxBuffManuver->Lock(
//		0,
//		0,
//		(void**)&pVtx,
//		0
//	);
//
//	for (nCntManuver = 0; nCntManuver < NUM_PLACE; nCntManuver++)
//	{
//		//�e�N�X�`���̍��W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f + 0.1f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(aTexU[nCntManuver] * 0.1f + 0.1f, 1.0f);
//
//		pVtx += 4;
//	}
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffManuver->Unlock();
//
//}
//void AddManuver(int *pValue)
//{
//	g_nManuver += *pValue;
//}