#ifndef ISILME_AI_SCRIPTAIPACKAGEDEF_H
#define ISILME_AI_SCRIPTAIPACKAGEDEF_H

#include "Definitions.h"
#include "Engine/Core/AIPackageDef.h"

/// �������� ����������� ������ ��
/// �������� ��� ������ ������ ��
class ISILME_API ScriptAIPackageDef : public AIPackageDef
{
public:
	ScriptAIPackageDef();
	virtual ~ScriptAIPackageDef();

	virtual void Parse(TiXmlElement* element);
	virtual AIPackagePtr CreatePackage();
private:
	/// ��� ������ ������ ��
	std::string mClassName;
};

#endif