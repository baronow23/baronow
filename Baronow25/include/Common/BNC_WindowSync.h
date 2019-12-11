#pragma once

class BNC_BaseDialog;
class BN25_TYPE BNC_WindowSync
{
public:
	BNC_WindowSync(BNC_BaseDialog *pTarget);
	~BNC_WindowSync();

private :
	BNC_BaseDialog *m_pTarget;
};

