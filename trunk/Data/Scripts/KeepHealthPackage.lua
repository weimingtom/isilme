class 'TestAction'(Action)

function TestAction:__init()
	Action.__init(self);
	self:SetDuration(0);
end

function TestAction:OnStart()
	local position = self:GetEntity():GetPosition();
	self:GetEntity():GetBehaviour():SetHealth(140);
	self:GetEntity():SetPosition(position.x + 1, position.y);
	--self:Stop();
end

indexerTemp = 0;
indexedTable = {};

class 'KeepHealthPackage'(AIPackage)

function KeepHealthPackage:__init()
	AIPackage.__init(self);
end

function KeepHealthPackage:CheckCondition()
	--return false;
	--local e = self:GetEntity();
	--local c = ToCreature(e);
	--return false;
	return self:GetBehaviour():GetHealth() < 100; --c:GetMaxHealth() / 2;
end

function KeepHealthPackage:CreateAction()
	local action = TestAction();
	return action;
end