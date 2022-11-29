#include "main.h"
#include "Score.h"
#include "Enemy.h"

//�}�N����`
#define NUM_PLACE (8)	//�X�R�A�̍ő包��
#define TEX_SIZE (70)	//�e�N�X�`���̕\���T�C�Y

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore;	//�X�R�A�̈ʒu
int g_nScore;	//�X�R�A�̒l
int g_nHighScore;

//�|���S���̏���������
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntScore, nCntScore2;

	pDevice = GetDevice();	//�f�o�C�X�̎擾

							//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureScore);

	//�X�R�A�̏�����
	g_nScore = 0;


	//�����L���O�f�[�^�ǂݍ��ݏ���
	FILE*pFile;//�t�@�C���|�C���^��錾

			   //�t�@�C�����J��
	pFile = fopen("ranking.txt", "r");

	//��������
	if (pFile != NULL)
	{
		
		//�t�@�C���ɓ��͂��ꂽ�\���̂̊e�v�f���o�͂���

		/*fwrite(&g_aRanking[0], sizeof(Ranking), NUM_RANKING, pFile);*/

		fscanf(pFile, "%d", &g_nHighScore);

		
	}
	else if(pFile ==NULL)
	{
		g_nHighScore = 0;
	}
	
	if (pFile != NULL)
	{
		//�t�@�C�������
		fclose(pFile);
	}
	

	//�ʒu�̏�����
	g_posScore = D3DXVECTOR3(980.0f, 160.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE*2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntScore2 = 0; nCntScore2 < 2; nCntScore2++)
	{
		for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
		{
			pVtx[0].pos.x = g_posScore.x - 40;	//�E���Őݒ�
			pVtx[0].pos.y = g_posScore.y - 40;
			pVtx[0].pos.z = g_posScore.z;
			pVtx[1].pos.x = g_posScore.x + 40;
			pVtx[1].pos.y = g_posScore.y - 40;
			pVtx[1].pos.z = g_posScore.z;
			pVtx[2].pos.x = g_posScore.x - 40;
			pVtx[2].pos.y = g_posScore.y + 40;
			pVtx[2].pos.z = g_posScore.z;
			pVtx[3].pos.x = g_posScore.x + 40;
			pVtx[3].pos.y = g_posScore.y + 40;
			pVtx[3].pos.z = g_posScore.z;

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
			g_posScore.x += 40;
		}
		g_posScore.x -= 320;
		g_posScore.y = 90;
	}
	

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//�|���S���̏I������
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
//�|���S���̍X�V����
void UpdateScore(void)
{
	int nCntScore, nCntScore2, nNum1, nNum2;
	int aTexU[NUM_PLACE*2] = {};	//�e���̐������i�[

	if (g_nScore >= g_nHighScore)
	{
		g_nHighScore = g_nScore;
	}

		for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
		{
			nNum1 = pow(10, nCntScore + 1);
			nNum2 = pow(10, nCntScore);
			aTexU[nCntScore] = (g_nScore % nNum1) / nNum2;
		}
	
		for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
		{
			nNum1 = pow(10, nCntScore + 1);
			nNum2 = pow(10, nCntScore);
			aTexU[nCntScore+8] = (g_nHighScore % nNum1) / nNum2;
		}

	//�e�N�X�`���̍X�V
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntScore2 = 0; nCntScore2 < 2; nCntScore2++)
	{

		for (nCntScore = 7; nCntScore >= 0; nCntScore--)
		{
			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(aTexU[nCntScore+nCntScore2*8] * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((aTexU[nCntScore+nCntScore2*8] * 0.1f) + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(aTexU[nCntScore+nCntScore2*8] * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((aTexU[nCntScore+nCntScore2*8] * 0.1f) + 0.1f, 1.0f);

			pVtx += 4;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//�|���S���̕`�揈��
void DrawScore(void)
{
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < 16; nCntScore++)
	{
		 //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
	//	2,//�v���~�e�B�u�i�|���S���j�̐�
	//	&g_aVertex[0],//���_���̐擪�A�h���X
	//	sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
}
//�X�R�A�̐ݒ菈��
void SetScore(D3DXVECTOR3 pos)
{
	int aTexU[NUM_PLACE];	//�e���̐������i�[
	int nCntScore;

	g_posScore = pos;

	//���_���W�̐ݒ�
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		pVtx[0].pos.x = g_posScore.x - 40;	//�E���Őݒ�
		pVtx[0].pos.y = g_posScore.y - 40;
		pVtx[0].pos.z = g_posScore.z;
		pVtx[1].pos.x = g_posScore.x + 40;
		pVtx[1].pos.y = g_posScore.y - 40;
		pVtx[1].pos.z = g_posScore.z;
		pVtx[2].pos.x = g_posScore.x - 40;
		pVtx[2].pos.y = g_posScore.y + 40;
		pVtx[2].pos.z = g_posScore.z;
		pVtx[3].pos.x = g_posScore.x + 40;
		pVtx[3].pos.y = g_posScore.y + 40;
		pVtx[3].pos.z = g_posScore.z;


		g_posScore.x += 40;
		pVtx += 4;
	}

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);	//�e�N�X�`���̏ꍇ�S�Ĕ���
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

		pVtx += 4;
	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

}
void AddScore(int *pValue)
{
	g_nScore += *pValue;
}
//�X�R�A�̎擾
int GetScore(void)
{
	return g_nScore;
}