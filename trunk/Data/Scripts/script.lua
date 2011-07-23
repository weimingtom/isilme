function lua_test_func()
	a = fa();
	b = fb();
	c = a + b;
	return c;
end

function TestAPI()
	entity = CreateEntity("Monster1", "");
	MoveEntityToLayer(entity, "Layer1");
	MoveEntityToPosition(entity, 5, 1, 0);
end