#ifndef _Enemy_H_	//���̃}�N������`����Ă��Ȃ����
#define _Enemy_H_	//��d�C���N���[�h�h�~�}�N��

//�}�N����`
#define MAX_ENEMY (128)	//�G�̍ő吔

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL=0,	//�ʏ�
	ENEMYSTATE_DAMEGE,		//�_���[�W�G�t�F�N�g
	ENEMYSTATE_NOEFFECT,	//���G���
	ENEMYSTATE_OPTION,		//�I�v�V����
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�G�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nCounterAnimEnemy;	//�A�j���[�V�����J�E���^�[
	int nPatternAnimEnemy;	//�A�j���[�V�����p�^�[���i���o�[
	int ntype;			//���
	int nLife;			//�̗�
	int nLifeGage;		//�̗̓Q�[�W��
	ENEMYSTATE state;	//���
	int nCounterState;	//�X�e�[�g�J�E���^�[
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void HitEnemy(int nCntEnemy, int Damage);
Enemy *GetEnemy(void);
bool GetBulletDlt(void);

#endif // !_Enemy_H_
