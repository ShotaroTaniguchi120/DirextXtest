#ifndef _Score_h_	//���̃}�N������`����Ă��Ȃ����
#define _Score_h_	//��d�C���N���[�h�h�~�}�N��

#include "main.h"

//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(D3DXVECTOR3 pos);
void AddScore(int *pValue);
int GetScore(void);

#endif // !_Score_h_