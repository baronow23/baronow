#pragma once

// https://rammichael.com/getting-brighter-colors-in-windows-10
// https://github.com/RaMMicHaeL/Windows-10-Color-Control

class BN25_TYPE BNC_DwmColorControl
{
public:
	BNC_DwmColorControl();
	~BNC_DwmColorControl();

public :
	static bool	GetColorParam(const WCHAR *pParam, COLORREF *pColor);

public :
	void		InitWindowsThemeColorApi();
	COLORREF	GetDwmColorizationColor();
	void		SetDwmColorizationColor(COLORREF color);
	COLORREF	GetAccentColor();
	void		SetAccentColor(COLORREF color, bool newAccentAlgorithmWorkaround = false);
	bool		IsNewAutoColorAccentAlgorithm();
	void		SetAutoColorAccentAlgorithm(bool bNewAlgorithm);
};

