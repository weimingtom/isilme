function BonusHealth(trigger, target)
	if target:GetName() == "Player" then
		GiveHP("Player", 10);
		trigger:Remove();
	end
end

function RedOrbBonus(trigger, target)
	AddOrbs(5);
	DestroyEntity(trigger);
end

function TestEngineAPI()
	local e = Factory:GetEntity("House");
	p = e:GetPosition();
	e:SetPosition(p.x, p.y + 3.5);
	--e:RemoveBody();
	--e:Remove();
	e = nil;
	return true;
end;

function TestCondition()
	local e = Factory:GetEntity("Player");
	local p = e:GetPosition();
	if p.y > 6 then
		return true;
	end;
	return false;
end

function TestStory()

	local q = Story:GetQuest("Level1");
	q:SetStage(10);
end


--TestEngineAPI();