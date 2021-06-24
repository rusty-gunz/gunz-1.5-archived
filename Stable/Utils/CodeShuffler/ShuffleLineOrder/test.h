#ifndef ASCOMMANDPARAMETER_H
#define ASCOMMANDPARAMETER_H

#include "MUID.h"
#include "MTypes.h"
#include "mempool.h"

//
//
//
// ���� ���� �� ���������Դϴ�
//
//
//

class MCommandParamCondition;
class MCommandParamConditionMinMax;

/// Ŀ�ǵ� �Ķ���� Ÿ��
enum MCommandParameterType{
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_POS,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_UCHAR,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_BOOL,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_FLOAT,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_UID,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_VECTOR,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_STR,

/*[[SHUFFLE_LINE]] CmdParamType */	MPT_UINT64,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_UINT,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_SVECTOR,

/*[[SHUFFLE_LINE]] CmdParamType */	MPT_CHAR,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_DIR,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_SHORT,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_BLOB,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_INT64,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_USHORT,

/*[[SHUFFLE_LINE]] CmdParamType */	MPT_COLOR,
/*[[SHUFFLE_LINE]] CmdParamType */	MPT_INT,

									MPT_END,			///< �Ķ���� Ÿ�� �� ����
};

#define MAX_BLOB_SIZE		(0x100000)			// 1�ް�����Ʈ




/// Command Parameter Description
class MCommandParameterDesc{
protected:
/*[[SHUFFLE_LINE]] CmdParamDesc */	char								m_szDescription[64];
/*[[SHUFFLE_LINE]] CmdParamDesc */	vector<MCommandParamCondition*>		m_Conditions;
/*[[SHUFFLE_LINE]] CmdParamDesc */	MCommandParameterType				m_nType;

	void								InitializeConditions();
public:
	MCommandParameterDesc(MCommandParameterType nType, char* szDescription);
	virtual ~MCommandParameterDesc(void);

	MCommandParameterType GetType(void){ return m_nType; }
	const char* GetDescription(void){ return m_szDescription; }

	void AddCondition(MCommandParamCondition* pCondition);
	bool HasConditions() { return (!m_Conditions.empty()); }
	int GetConditionCount() { return (int)m_Conditions.size(); }
	MCommandParamCondition* GetCondition(int n) { return m_Conditions[n]; }

};

#endif
