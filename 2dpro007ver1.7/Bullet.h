#ifndef _Bullet_h_	//���̃}�N������`����Ă��Ȃ����
#define _Bullet_h_	//��d�C���N���[�h�h�~�}�N��

#include "main.h"

//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER=0,	//�v���C���[�̒e
	BULLETTYPE_PLAYER_01,
	BULLETTYPE_PLAYER_02,
	BULLETTYPE_PLAYER_BOMB,
	BULLETTYPE_ENEMY_00,		//�G�̒e
	BULLETTYPE_ENEMY_01,
	BULLETTYPE_ENEMY_02,
	BULLETTYPE_ENEMY_03,
	BULLETTYPE_ENEMY_04,
	BULLETTYPE_ENEMY_05,
	BULLETTYPE_ENEMY_06,
	BULLETTYPE_ENEMY_07,
	BULLETTYPE_ENEMY_08,
	BULLETTYPE_MAX
}BULLETTYPE;

//�e���̎��
typedef enum
{
	BALLISTICSTYPE_NORMAL=0,	//�ʏ�
	BALLISTICSTYPE_FALL,		//����
	BALLISTICSTYPE_REFLECT,		//����
	BALLISTICSTYPE_MAX
}BALLISTICSTYPE;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fTexAngle, BULLETTYPE type,BALLISTICSTYPE ballistics, D3DXCOLOR col);
void SetBarrage(D3DXVECTOR3 BossPos, float fAngle, float fmove, int nWay, int nBarrageType, D3DXCOLOR col);
#endif // !_Bullet_h_
