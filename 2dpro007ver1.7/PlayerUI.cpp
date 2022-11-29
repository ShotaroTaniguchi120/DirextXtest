#include "main.h"
#include "Player.h"
#include "PlayerUI.h"

//�}�N����`
#define MAX_DATA (3)
#define MAX_TEX (13)

//�\���̂̒�`
typedef enum
{
	TYPE_LIFE = 0,
	TYPE_BOMB,
	TYPE_MANUVER
}Type;

typedef struct
{
	Type type;
	bool bUse;

}UIdata;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTexturePlayerUI[MAX_TEX] = {};	//�e�N�X�`��3�����ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerUI = NULL;	//���_�o�b�t�@�ւ̃|�C���^
UIdata g_aUIdata[MAX_TEX] = {};
float g_aTexV2;	//�e�N�X�`�����W�̊J�n�ʒu(V�l)

//�|���S���̏���������
void InitPlayerUI(void)
{
	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

								//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\lifestar.png",//�e�N�X�`���̃t�@�C����
		&g_apTexturePlayerUI[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bombstar.png",//�e�N�X�`���̃t�@�C����
		&g_apTexturePlayerUI[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",//�e�N�X�`���̃t�@�C����
		&g_apTexturePlayerUI[2]);

	//�G�̏�����
	g_aUIdata[0].type = TYPE_LIFE;

	for (nCnt = 1; nCnt <3 ; nCnt++)
	{
		g_aUIdata[nCnt].type =TYPE_BOMB;
	}
	for (nCnt = 3; nCnt <6; nCnt++)
	{
		g_aUIdata[nCnt].type = TYPE_MANUVER;
	}

	for (nCnt = 0; nCnt < MAX_TEX;nCnt++)
	{
		g_aUIdata[nCnt].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerUI,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffPlayerUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
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

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayerUI->Unlock();
}
//�|���S���̏I������
void UninitPlayerUI(void)
{
	int nCnt;

	//�e�N�X�`���̔j��
	for (nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		if (g_apTexturePlayerUI[nCnt] != NULL)
		{
			g_apTexturePlayerUI[nCnt]->Release();
			g_apTexturePlayerUI[nCnt] = NULL;
		}
	}

	//�o�b�t�@�̔j��
	if (g_pVtxBuffPlayerUI != NULL)
	{
		g_pVtxBuffPlayerUI->Release();
		g_pVtxBuffPlayerUI = NULL;
	}
}
//�|���S���̍X�V����
void UpdatePlayerUI(void)
{
	int nCnt,nCnt2;
	Player PlayerData3 = GetPlayer();

	for (nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		g_aUIdata[nCnt].bUse == false;

	}

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		switch (g_aUIdata[nCnt].type)
		{
		case TYPE_LIFE:
			g_aUIdata[nCnt].bUse = PlayerData3.nLife - 1;
			break;

		case TYPE_BOMB:
			for (nCnt2 = 0; nCnt2 < PlayerData3.nBomb; nCnt2++)
			{
				g_aUIdata[nCnt].bUse = PlayerData3.nBomb;
				break;
			}
			break;

		case TYPE_MANUVER:
			for (nCnt2 = 0; nCnt2 < 3; nCnt2++)
			{
				g_aUIdata[nCnt].bUse = true;
				break;
			}
		
			break;
		}
		
	}

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffPlayerUI->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCnt = 0; nCnt <MAX_TEX ; nCnt++)
	{
			switch (g_aUIdata[nCnt].type)
			{
			case TYPE_LIFE:
				for (nCnt2 = nCnt; nCnt2 < 1; nCnt2++)
				{
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(960.0f, 220.0f, 0.0f);	//�E���Őݒ�
					pVtx[1].pos = D3DXVECTOR3(1000.0f, 220.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(960.0f, 260.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(1000.0f, 260.0f, 0.0f);

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
					
				}

				break;

			case TYPE_BOMB:
				for (nCnt2 = nCnt; nCnt2 <3; nCnt2++)
				{
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(900.0f + nCnt2 * 40, 260.0f, 0.0f);	//�E���Őݒ�
					pVtx[1].pos = D3DXVECTOR3(940.0f + nCnt2 * 40, 260.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(900.0f + nCnt2 * 40, 300.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(940.0f + nCnt2 * 40, 300.0f, 0.0f);

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
					
				}

				break;

			case TYPE_MANUVER:
				for (nCnt2 = nCnt; nCnt2 < 6; nCnt2++)
				{
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(900.0f + nCnt2 * 40, 350.0f, 0.0f);	//�E���Őݒ�
					pVtx[1].pos = D3DXVECTOR3(980.0f + nCnt2 * 40, 350.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(900.0f + nCnt2 * 40, 430.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(980.0f + nCnt2 * 40, 430.0f, 0.0f);

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
					pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(1.0f, 0.1f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 0.1f);

					pVtx += 4;
					
				}

				break;
			}
		
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayerUI->Unlock();
}
//�|���S���̕`�揈��
void DrawPlayerUI(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

								//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_aUIdata[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTexturePlayerUI[g_aUIdata[nCnt].type]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
		
	}
	
}