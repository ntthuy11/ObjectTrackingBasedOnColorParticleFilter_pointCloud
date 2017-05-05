// 071112color_based_PFDlg.h : header file
//

#pragma once
#include "cv.h"
#include "highgui.h"
#include "GenericParticleFilter.h"

// -----------------------------------------------

#define WIN_NAME_WEBCAM			"Webcam"
#define WIN_NAME_IMAGE_SEQUENCE "Image Sequence"

#define NUM_OF_PARTICLES	(500)
#define SIGMA				(15)	// for random number generator

// -----------------------------------------------

// CMy071112color_based_PFDlg dialog
class CMy071112color_based_PFDlg : public CDialog
{
// Construction
public:
	CMy071112color_based_PFDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MY071112COLOR_BASED_PF_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	void getUserInput();


public:
	afx_msg void OnBnClickedButtonImageSequence();
public:
	afx_msg void OnBnClickedButtonVideo();
public:
	afx_msg void OnBnClickedButtonCameraMatrox();
public:
	afx_msg void OnBnClickedButtonWebcam();
public:
	afx_msg void OnBnClickedButtonQuit();
public:
	afx_msg void OnBnClickedButtonStop();
};
