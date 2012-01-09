class 'TestAction'(Action)

function TestAction:__init()
	Action.__init(self);
	self:SetDuration(0);
end

function TestAction:OnStart()
	local position = self:GetEntity():GetPosition();
	self:GetEntity():SetPosition(position.x + 5, position.y);
	--self:Stop();
end

class 'KeepHealthPackage'(AIPackage)

function KeepHealthPackage:__init()
	AIPackage.__init(self);
end

function KeepHealthPackage:CheckCondition()
--	local e = self:GetEntity();
--	local c = ToCreature(e);
	return false;
	--return c:GetHealth() < c:GetMaxHealth() / 2;
end

function KeepHealthPackage:CreateAction()
	local action = TestAction();
	return action;
end