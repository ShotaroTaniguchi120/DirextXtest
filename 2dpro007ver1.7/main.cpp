//==========================================================================================
//
//2DSTG
//Author:���������Y
//
//==========================================================================================
#include "main.h"
#include "input.h"
#include "Player.h"
#include "block.h"

//�}�N����`
#define CLASS_NAME "WindowClass" //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME	"�e���]��" //�E�B���h�E�̖��O

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

//�O���[�o���ϐ��錾
LPDIRECT3D9 g_pD3D = NULL;	//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;	//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;		//FPS�J�E���^
MODE g_mode = MODE_TITLE;	//���݂̃��[�h


//==========================================================================================
//���C���֐�
//==========================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstanceprev, LPSTR IpCmdLine, int nCmdshow)
{
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwExecLastTime;	//�Ō�ɏ�����������
	DWORD dwFrameCount;	//�t���[���J�E���g
	DWORD dwFPSLastTime;	//�Ō��FPS���v����������
	
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;
	MSG msg;
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	RegisterClassEx(&wcex);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindowEx(0,	//�g���E�B���h�E�X�^�C��
		CLASS_NAME,				//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,			//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,			//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,			//�V����Y���W
		SCREEN_WIDTH,			//�V��
		SCREEN_HEIGHT,			//�V����
		NULL,					//�e�E�B���h�E�̃n���h��
		NULL,					//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,				//�C���X�^���X�n���h��
		NULL
	);	//�E�B���h�E�쐬�f�[�^

	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//�����������s�����ꍇ
		return -1;
	}
	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;	//������
	dwExecLastTime = timeGetTime();	//���݂̎������擾
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	ShowWindow(hWnd, nCmdshow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE != 0))
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���

			dwCurrentTime = timeGetTime();	//���ݎ������擾

			if((dwCurrentTime-dwFPSLastTime)>=500)
			{//0.5�b�o��
			//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	//FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;	//�t���[���J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;	//�����J�n�̎���[���ݎ���]��ۑ�
				dwFrameCount++;

				//�X�V����
				Update();
				//�`�揈��
				Draw();
			}
		}
	}
	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}
//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	int nID;

	
	switch (uMsg)
	{
	case WM_DESTROY: //�E�B���h�E�j���̃��b�Z�[�W
					 //WM�QQUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_COMMAND:	//�R�}���h���s�̃��b�Z�[�W
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{ //�I���{�^���������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E��j������iWM�QDESTROY���b�Z�[�W�𑗂�j
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
		}
	case WM_KEYDOWN:
		

		switch (wParam)
		{
		case VK_ESCAPE: //[ESC]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E��j������iWM�QDESTROY���b�Z�[�W�𑗂�j
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
			break;
		}



	case WM_LBUTTONDOWN:	//�}�E�X���N���b�N�̃��b�Z�[�W
							//�ΏۃE�B���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);
		break;
	case WM_CLOSE:	//����{�^�������̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			//�E�B���h�E��j������iWM�QDESTROY���b�Z�[�W�𑗂�j
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}
//����������
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm; //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));	//�p�����[�^�̂O�N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//�Q�[����ʃT�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//�Q�[����ʃT�C�Y�i�c�j
	d3dpp.BackBufferFormat = d3ddm.Format;	//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;	//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;	//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;	//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//�C���^�[�o��

																//Direct3D�f�o�C�X�̍쐬
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_REF,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			return E_FAIL;
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�A���t�@�u�����h�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�e�N�X�`���̊g�k�ۊǂ̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//�e�N�X�`���̃A���t�@�u�����h�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	//�e��I�u�W�F�N�g�̏���������

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�v���C���[�̏���������
	InitPlayer();

	//�u���b�N�̏�����
	InitBlock();

	////�p�b�h�̏���������
	//if (FAILED(InitPad(hInstance, hWnd)))
	//{
	//	return E_FAIL;
	//}

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);


	return S_OK;
}
//�I������
void Uninit(void)
{
	//�e��I�u�W�F�N�g�̏I������

	//�v���C���[�̏I������
	UninitPlayer();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�p�b�h�̏I������
	/*UninitPad();*/

	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//����\��߂�
	timeEndPeriod(1);
}
//�X�V����
void Update(void)
{
	//�e��I�u�W�F�N�g�̍X�V����

	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();
	
	////�p�b�h�̍X�V����
	//UpdatePad();

	//�v���C���[�̍X�V����
	UpdatePlayer();

}
//�`�揈��
void Draw(void)
{
	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
	 //�e��I�u�W�F�N�g�̕`�揈��

		//�v���C���[�̕`�揈��
		DrawPlayer();

#ifdef _DEBUG
	//FPS�̕\��
		DrawFPS();
#endif

		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n�㉺���E�L�[�F�ړ�\nZ�L�[:�V���b�g(�A��)\nshift�L�[:�ᑬ�ړ����[�h", g_nCountFPS);

	//�e�L�X�g��`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
//���[�h�̐ݒ�
void SetMode(MODE mode)
{
	

	g_mode = mode;	//���[�h��ݒ肷��
}
//���[�h�̎擾
MODE GetMode(void)
{
	return g_mode;
}
