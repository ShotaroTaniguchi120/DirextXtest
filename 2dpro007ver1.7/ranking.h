#ifndef _Ranking_h_	//���̃}�N������`����Ă��Ȃ����
#define _Ranking_h_	//��d�C���N���[�h�h�~�}�N��

#include "main.h"

//�\���̂̒�`
typedef struct
{
	int nScore = 0;
	int aName[10] = {};
	bool bPlayer = false;
}Ranking;


//�v���g�^�C�v�錾
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void SetRanking(int nRanking);
Ranking* GetRanking(void);


#endif // !_Ranking_h_