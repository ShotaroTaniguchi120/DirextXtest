#ifndef _Player_H_	//���̃}�N������`����Ă��Ȃ����
#define _Player_H_	//��d�C���N���[�h�h�~�}�N��

//���@�̏��
typedef enum
{
	PLAYERSTATE_NORMAL = 0,	//�ʏ�
	PLAYERSTATE_DAMEGE,		//�_���[�W�G�t�F�N�g
	PLAYERSTATE_NOEFFECT,	//���G���
	PLAYERSTATE_BOMB,		//�{�����
	PLAYERSTATE_MAX
}PLAYERSTATE;

//���@�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ʒu
	D3DXVECTOR3 rot;	//�ʒu
	D3DXVECTOR3 moverot;	//�ʒu
	int nCounterAnimPlayer;	//�A�j���[�V�����J�E���^�[
	int nPatternAnimPlayer;	//�A�j���[�V�����p�^�[���i���o�[
	int nLife;			//�̗�
	int nBomb;			//�{����
	int nManuver;		//�}�j���[�o��
	PLAYERSTATE state;	//���
	int nCounterState;	//�X�e�[�g�J�E���^�[
	bool bSlowMode;		//�ᑬ���[�h
	bool bOption = true;		//�I�v�V����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
void ManuverPlayer(void);
Player GetPlayer(void);

#endif // !_Player_H_
