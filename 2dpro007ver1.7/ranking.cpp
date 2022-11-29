#include "main.h"
#include "Ranking.h"
#include "rankingname.h"
#include "Score.h"

//�}�N����`
#define NUM_PLACE (8)	//�X�R�A�̍ő包��
#define TEX_SIZE (70)	//�e�N�X�`���̕\���T�C�Y
#define NUM_RANKING (10)
#define MAX_NAME (10)



//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posRanking;	//�X�R�A�̈ʒu
D3DXVECTOR3 g_posName;	//���O�̈ʒu
Ranking g_aRanking[NUM_RANKING] = {};
bool g_bPlayerSet = false;

//�|���S���̏���������
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntRanking, nCntRanking2;

	g_bPlayerSet = false;

	for (nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		g_aRanking[nCntRanking].bPlayer = false;
	}
	//==============================================================
	//�f�[�^�̓ǂݍ��ݏ���
	//==============================================================

	FILE*pFile;//�t�@�C���|�C���^��錾

			   //�t�@�C�����J��
	pFile = fopen("ranking.txt", "r");

	//���s����
	if (pFile == NULL)
	{
		//�t�@�C�����J��
		pFile = fopen("ranking.txt", "w");
		//�t�@�C���ɓ��͂��ꂽ�\���̂̊e�v�f���o�͂���

		/*fwrite(&g_aRanking[0], sizeof(Ranking), NUM_RANKING, pFile);*/
		for (nCntRanking = 0; nCntRanking <NUM_RANKING; nCntRanking++)
		{
			fprintf(pFile, "%d\n", g_aRanking[nCntRanking].nScore);
			for (nCntRanking2 = 0; nCntRanking2 < 10; nCntRanking2++)
			{
				fprintf(pFile, "%d\n", 78);
			}
			
		}
		

		//�t�@�C�������
		fclose(pFile);

		//�t�@�C�����ēx�J��
		pFile = fopen("ranking.txt", "r");

	}

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�t�@�C���ɓ��͂��ꂽ�\���̗̂v�f���o�͂���

		/*fread(&g_aRanking[0], sizeof(Ranking), NUM_RANKING, pFile);*/
		for (nCntRanking = 0; nCntRanking <NUM_RANKING; nCntRanking++)
		{
			fscanf(pFile, "%d", &g_aRanking[nCntRanking].nScore);
			for (nCntRanking2 = 0; nCntRanking2 < 10; nCntRanking2++)
			{
				fscanf(pFile, "%d", &g_aRanking[nCntRanking].aName[nCntRanking2]);
			}
			
		}

		//�t�@�C�������
		fclose(pFile);
	}
	//else
	//{//�t�@�C�����J���Ȃ������ꍇ
	//	printf("***�G���[:�t�@�C�����J���܂���ł���***\n");
	//}
	pDevice = GetDevice();	//�f�o�C�X�̎擾

							//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number001.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureRanking);

	//�ʒu�̏�����
	g_posRanking = D3DXVECTOR3(720.0f, 120.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 80,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntRanking2 = 0; nCntRanking2 < NUM_RANKING; nCntRanking2++)
	{
		for (nCntRanking = 0; nCntRanking < NUM_PLACE; nCntRanking++)
		{
			pVtx[0].pos.x = g_posRanking.x - 40;	//�E���Őݒ�
			pVtx[0].pos.y = g_posRanking.y - 40;
			pVtx[0].pos.z = g_posRanking.z;
			pVtx[1].pos.x = g_posRanking.x + 40;
			pVtx[1].pos.y = g_posRanking.y - 40;
			pVtx[1].pos.z = g_posRanking.z;
			pVtx[2].pos.x = g_posRanking.x - 40;
			pVtx[2].pos.y = g_posRanking.y + 40;
			pVtx[2].pos.z = g_posRanking.z;
			pVtx[3].pos.x = g_posRanking.x + 40;
			pVtx[3].pos.y = g_posRanking.y + 40;
			pVtx[3].pos.z = g_posRanking.z;

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
			g_posRanking.x += 40;
		}
		g_posRanking.x -= 320;
		g_posRanking.y += 45;
	}




	

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();
}
//�|���S���̏I������
void UninitRanking(void)
{
	int nCnt, nCnt2;
	int aName[MAX_NAME];

	GetRankingname(aName);

	for (nCnt = 0; nCnt < NUM_RANKING; nCnt++)
	{
		if (g_aRanking[nCnt].bPlayer == true)
		{
			for (nCnt2 = 0; nCnt2 < MAX_NAME; nCnt2++)
			{
				g_aRanking[nCnt].aName [nCnt2]= aName[nCnt2];
			}
			

		}
	}

	FILE*pFile;//�t�@�C���|�C���^��錾

			   //�t�@�C�����J��
	pFile = fopen("ranking.txt", "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�t�@�C���ɓ��͂��ꂽ�\���̗̂v�f���o�͂���

	 /*fread(&g_aRanking[0], sizeof(Ranking), NUM_RANKING, pFile);*/

		for (nCnt= 0; nCnt < NUM_RANKING; nCnt++)
		{
			fprintf(pFile, "%d\n", g_aRanking[nCnt].nScore);
			for (nCnt2 = 0; nCnt2 < 10; nCnt2++)
			{
				fprintf(pFile, "%d\n", g_aRanking[nCnt].aName[nCnt2]);
			}
		}
	}
	//�t�@�C�������
	fclose(pFile);

	//�e�N�X�`���̔j��
	if (g_pTextureRanking != NULL)
	{

		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
	//�e�N�X�`���̔j��
	if (g_pVtxBuffRanking != NULL)
	{

		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}
//�|���S���̍X�V����
void UpdateRanking(void)
{
	int nCntRanking, nCntRanking2, nNum1, nNum2;
	int aTexU[NUM_PLACE*NUM_RANKING] = {};	//�e���̐������i�[
	int aTexV[NUM_PLACE*NUM_RANKING] = {};
	int nCount1, nCount2, nData;
	int nScore = GetScore();
	int aName[MAX_NAME];
	int aNameData[MAX_NAME] = {}, aData[MAX_NAME];

	////=====================================================================
	////�\�[�g����
	////=====================================================================
	for (nCount1 = 0; nCount1 < NUM_RANKING; nCount1++)
	{
		if (nScore > g_aRanking[nCount1].nScore)
		{
			nData = nScore;
			nScore = g_aRanking[nCount1].nScore;
			g_aRanking[nCount1].nScore = nData;

			for (nCount2 = 0; nCount2 < MAX_NAME; nCount2++)
			{
				aData[nCount2] = aNameData[nCount2];
				aNameData[nCount2] = g_aRanking[nCount1].aName[nCount2];
				g_aRanking[nCount1].aName[nCount2] = aData[nCount2];
			}

			if (g_bPlayerSet == false)
			{
				
				g_aRanking[nCount1].bPlayer = true;
				g_bPlayerSet = true;
			}
			
		}
	}

	/*for (nCount1 = 0; nCount1 <NUM_RANKING; nCount1++)
	{
		for (nCount2 = nCount1 + 1; nCount2 < NUM_RANKING; nCount2++)
		{
			if (g_aRanking[nCount1].nScore < g_aRanking[nCount2].nScore)
			{
				nData = g_aRanking[nCount1].nScore;
				g_aRanking[nCount1].nScore = g_aRanking[nCount2].nScore;
				g_aRanking[nCount2].nScore = nData;
			}
		}

	}*/
	//=====================================================================

	for (nCntRanking2 = 0; nCntRanking2 < NUM_RANKING; nCntRanking2++)
	{
		for (nCntRanking = 0; nCntRanking < NUM_PLACE; nCntRanking++)
		{

			nNum1 = pow(10, nCntRanking + 1);
			nNum2 = pow(10, nCntRanking);
			aTexU[nCntRanking+(8*nCntRanking2)] = (g_aRanking[nCntRanking2].nScore % nNum1) / nNum2;
		}
	}
	

	//�e�N�X�`���̍X�V
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);
	for (nCntRanking2 = 0; nCntRanking2 < NUM_RANKING; nCntRanking2++)
	{
		/*pVtx += 28;*/
		for (nCntRanking = 7; nCntRanking >= 0; nCntRanking--)
		{
			//�e�N�X�`���̍��W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(aTexU[nCntRanking + (8 * nCntRanking2)] * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((aTexU[nCntRanking + (8 * nCntRanking2)] * 0.1f) + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(aTexU[nCntRanking + (8 * nCntRanking2)] * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((aTexU[nCntRanking + (8 * nCntRanking2)] * 0.1f) + 0.1f, 1.0f);

			pVtx += 4;
		}
		/*pVtx += 32;*/
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();


	
}
//�|���S���̕`�揈��
void DrawRanking(void)
{
	int nCntRanking;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

								//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking);

	for (nCntRanking = 0; nCntRanking < 80; nCntRanking++)
	{
		//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRanking * 4, 2);
	}
	

	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
	//	2,//�v���~�e�B�u�i�|���S���j�̐�
	//	&g_aVertex[0],//���_���̐擪�A�h���X
	//	sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
}
//�X�R�A�̐ݒ菈��
void SetRanking(int nRanking)
{
	int aTexU[NUM_PLACE];	//�e���̐������i�[
	int nCntRanking;


}
Ranking* GetRanking(void)
{
	return &g_aRanking[0];
}