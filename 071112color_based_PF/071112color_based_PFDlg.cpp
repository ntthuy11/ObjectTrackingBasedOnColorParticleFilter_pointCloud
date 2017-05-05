// 071112color_based_PFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "071112color_based_PF.h"
#include "071112color_based_PFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ----------------------------
bool running = true;
int numParticles;

IplImage *currFrame = 0;

// ----------------------------

CMy071112color_based_PFDlg::CMy071112color_based_PFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy071112color_based_PFDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy071112color_based_PFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy071112color_based_PFDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_IMAGE_SEQUENCE, &CMy071112color_based_PFDlg::OnBnClickedButtonImageSequence)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO, &CMy071112color_based_PFDlg::OnBnClickedButtonVideo)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_MATROX, &CMy071112color_based_PFDlg::OnBnClickedButtonCameraMatrox)
	ON_BN_CLICKED(IDC_BUTTON_WEBCAM, &CMy071112color_based_PFDlg::OnBnClickedButtonWebcam)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CMy071112color_based_PFDlg::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMy071112color_based_PFDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()

// CMy071112color_based_PFDlg message handlers

BOOL CMy071112color_based_PFDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//--------------------- INIT --------------------------
	CWnd *editControl;
	CString s;

	s.Format(L"%4d", NUM_OF_PARTICLES);	editControl = this->GetDlgItem(IDC_EDIT_NUM_OF_PARTICLES);	editControl->SetWindowTextW((LPCTSTR)s); 


	// ----------------------------------------------------

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy071112color_based_PFDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy071112color_based_PFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy071112color_based_PFDlg::OnBnClickedButtonImageSequence() {	
	int numOfImages = 400;
	CString fn;

	getUserInput();
	cvNamedWindow(WIN_NAME_IMAGE_SEQUENCE, CV_WINDOW_AUTOSIZE);
	
	currFrame = cvvLoadImage("F:\\_SKKU\\research\\_project\\100915 Stereo based vehicle detection\\5-captureSeq data\\110208\\2-car in front of med. school\\b60-f25_35m-150m\\left\\0.bmp"); // frame dau tien
	//currFrame = cvvLoadImage("F:\\_Ntt\\_MyDocuments\\left_image_01\\101.bmp"); // frame dau tien
	GenericParticleFilter genericPF(currFrame, numParticles, SIGMA);
	
	for (int i = 1; i < numOfImages, running == true; i++) {
		if (i < 10) fn.Format(L"F:\\_SKKU\\research\\_project\\100915 Stereo based vehicle detection\\5-captureSeq data\\110208\\2-car in front of med. school\\b60-f25_35m-150m\\left\\%1d.bmp", i);
		else if (i < 100) fn.Format(L"F:\\_SKKU\\research\\_project\\100915 Stereo based vehicle detection\\5-captureSeq data\\110208\\2-car in front of med. school\\b60-f25_35m-150m\\left\\%2d.bmp", i);
		else if (i < 1000) fn.Format(L"F:\\_SKKU\\research\\_project\\100915 Stereo based vehicle detection\\5-captureSeq data\\110208\\2-car in front of med. school\\b60-f25_35m-150m\\left\\%3d.bmp", i);
		
		/*if (i < 10) fn.Format(L"F:\\_Ntt\\_MyDocuments\\left_image_01\\%1d.bmp", i);
		else if (i < 100) fn.Format(L"F:\\_Ntt\\_MyDocuments\\left_image_01\\%2d.bmp", i);
		else if (i < 1000) fn.Format(L"F:\\_Ntt\\_MyDocuments\\left_image_01\\%3d.bmp", i);
		else fn.Format(L"F:\\_Ntt\\_MyDocuments\\left_image_01\\%4d.bmp", i);
*/

		CStringA filename (fn); // convert CString to char *
		currFrame = cvvLoadImage(filename);

		genericPF.process(currFrame);	

		cvShowImage(WIN_NAME_IMAGE_SEQUENCE, currFrame);
		cvWaitKey(100); // delay 1 khoang thoi gian moi co the show image len duoc
	}
}

void CMy071112color_based_PFDlg::OnBnClickedButtonVideo() {
	
}

void CMy071112color_based_PFDlg::OnBnClickedButtonCameraMatrox() {
	
}

void CMy071112color_based_PFDlg::OnBnClickedButtonWebcam() {
	CvCapture* capture = cvCaptureFromCAM(0); // capture from video device #0
		
	if(!capture) {
		MessageBox(L"Could not initialize capturing.");
	} else { 	
		getUserInput(); 
		cvNamedWindow(WIN_NAME_WEBCAM, CV_WINDOW_AUTOSIZE);

		currFrame = cvQueryFrame(capture); // frame dau tien
		GenericParticleFilter genericPF(currFrame, numParticles, SIGMA);
	
		while(running) {
			currFrame = cvQueryFrame(capture);
			genericPF.process(currFrame);	
			cvShowImage(WIN_NAME_WEBCAM, currFrame);
			cvWaitKey(5); // delay 1 khoang thoi gian moi co the show image len duoc
		}
		//cvReleaseImage(&currFrame); // ko biet vi sao release lai bi loi			
	}
	cvReleaseCapture(&capture);
}

void CMy071112color_based_PFDlg::OnBnClickedButtonQuit() {
	running = false;
	cvDestroyAllWindows();
	OnOK();
}

void CMy071112color_based_PFDlg::OnBnClickedButtonStop() {
	running = false;
	cvDestroyAllWindows();
}

// ----------------------------------------------------------
void CMy071112color_based_PFDlg::getUserInput() {
	running = true; // <----

	CWnd *editControl;	
	
	CString numOfParticlesString;
	editControl = this->GetDlgItem(IDC_EDIT_NUM_OF_PARTICLES);		editControl->GetWindowTextW(numOfParticlesString);

	numParticles = NUM_OF_PARTICLES;
	if (!numOfParticlesString.IsEmpty()) {
		numParticles = (int)wcstod(numOfParticlesString, NULL);
	}
}
