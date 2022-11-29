
#include "main.h"
#include "Bg.h"

//�}�N����`
#define NUM_BG (3)		//�w�i�̐�

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureBg =NULL;	//�e�N�X�`��3�����ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;	//���_�o�b�t�@�ւ̃|�C���^
float g_aTexV[NUM_BG];	//�e�N�X�`�����W�̊J�n�ʒu(V�l)

//�|���S���̏���������
void InitBg(void)
{
	int nCntBg;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
								
	//�e�N�X�`���̓ǂݍ���
	//for (nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	//{
	//	D3DXCreateTextureFromFile(pDevice,
	//		"data\\TEXTURE\\bg.png",//�e�N�X�`���̃t�@�C����
	//		&g_apTextureBg);
	//}

		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg02.png",//�e�N�X�`���̃t�@�C����
			&g_apTextureBg);
	

	

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(
		0,
		0,
		(void**)&pVtx,
		0
		);
	
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(20.0f, 20.0f, 0.0f);	//�E���Őݒ�
		pVtx[1].pos = D3DXVECTOR3(820.0f, 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(20.0f, 940.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(820.0f, 940.0f, 0.0f);

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

		

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();
}
//�|���S���̏I������
void UninitBg(void)
{
	int nCntBg;

	//�e�N�X�`���̔j��
	
	if (g_apTextureBg != NULL)
	{
		g_apTextureBg->Release();
		g_apTextureBg = NULL;
	}
	
	//�o�b�t�@�̔j��
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}
//�|���S���̍X�V����
void UpdateBg(void)
{


}
//�|���S���̕`�揈��
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntBg;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBg);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
	//	2,//�v���~�e�B�u�i�|���S���j�̐�
	//	&g_aVertex[0],//���_���̐擪�A�h���X
	//	sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
}