#pragma once
class BN25_TYPE BNC_ClipboardImageOLE
{
public:
	BNC_ClipboardImageOLE();
	~BNC_ClipboardImageOLE();


private :
	HBITMAP GetBitmapFromDDB(COleDataObject* pDataObject) const;
	HBITMAP GetBitmapFromDIB(COleDataObject* pDataObject) const;
	LPVOID	GetData(COleDataObject* pDataObject, CLIPFORMAT cfFormat, size_t& nSize, LPFORMATETC lpFormatEtc = NULL) const;
	HBITMAP GetBitmapFromImage(COleDataObject* pDataObject) const;
	HBITMAP GetBitmapFromImage(COleDataObject* pDataObject, CLIPFORMAT cfFormat) const;

public :
	HBITMAP GetBitmap(void) const;
};

