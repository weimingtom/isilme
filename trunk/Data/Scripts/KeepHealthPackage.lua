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