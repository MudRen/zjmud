// xiakedao ʯ��

int do_study(string arg)
{
	object me;
	int lvl;

	if (arg != "wall")
		return notify_fail("�����о�ʲô��\n");

	me = this_player();

	if (me->query("combat_exp") < 500000)
	{
		write("�㿴�˰��죬ֻ���Լ�ʵս����̫ǳ�����޷���������ĸ���֪ʶ��\n");
		return 1;
	}

	if (me->is_busy())
	{
		write("��������æ��û���о������ʫ�䡣\n");
		return 1;
	}

	if ((me->query("potential") - me->query("learned_points")) < 10)
		return notify_fail("��Ŀǰ��Ǳ�ܲ��㣬�޷���ʯ���ϸ��򵽸������ݡ�\n");

	if ( me->query("qi")<101 || me->query("jing") < 101)
		return notify_fail("��Ŀǰ�ľ��񲻼ѣ����ǵȻ��ٹ�Ħ�ɡ�\n");

	me->receive_damage("qi", 100);
	me->receive_damage("jing", 100);
	me->start_busy(1);

	lvl = me->query_skill("literate", 1);
	if (lvl >= 200)
		write("�㿴�˰��죬��������ʫд�ĺܺã������ƺ�ûʲô�ر�֮����\n");
	else
	if (lvl >= 100)
		write("������������ʫ����Ԣ�⣬���ɵľ��Ŀ�˼��\n");
	else
	if (lvl >= 1)
		write("�����а��룺�ⶨ��ǰ���������µ��ؼ�����Щ�ʾ��Ҫ�ú÷�����\n");
	else
	if (random(10)>2 && SKILL_D("taixuan-gong")->valid_learn(me))
	{
		write("����������ıʻ����𽥽���һ������ľ��磬ȫ����֮�趯���ԡ�̫��������ʼ��������\n");

	            me->add("learned_points", 10);
	            me->improve_skill("taixuan-gong", 10 + random(me->query("int")*5));
/*
		if (me->query("experience") < me->query_experience_limit())
			//me->add("experience", 1);
			me->add("combat_exp", 1);
*/
	} else
		write("��Ǳ����ĥ����ıʻ�����������ƫƫ��ץ��סҪ�졣\n");

	return 1;
}

void init()
{
	add_action("do_study", "think");
	add_action("do_study", "study");
}
