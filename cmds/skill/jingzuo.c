// jingzuo.c
void wakeup(object me, object where);
void del_jingzuoed(object me);

int main(object me, string arg)
{
	mapping fam;
	object where = environment(me);

	seteuid(getuid());

	if (me->query("family/family_name") != "������")
		return notify_fail("ֻ�ж����ɵ��ӲŻ���ܾ�����\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("����̫���ӣ���û�����ľ�����\n");

	if (me->query("eff_jing") < 50)
		return notify_fail("������̫�أ��޷����ľ�����\n");

	if (me->is_busy())
		return notify_fail("����æ���أ�\n");

	if (me->is_fighting())
		return notify_fail("ս�����뾲�����㲻Ҫ������\n");

	if (time() - me->query("jingzuo_time") < 120)
		return notify_fail("��ղž�����������ͷ��һƬ�հס�\n");

	if (me->query_skill("mahayana", 1) < 40)
		return notify_fail("��Ĵ�˰����͹���̫ǳ���ˣ�û�����ľ�����\n");

	write("����ϥ���£���ʼ�붨��\n");
	write("��һ��������������⣬����������\n");
	me->set_temp("block_msg/all", 1);
	message_vision("$Nһ����������������Ŀ������Ĵ�����\n",me);

	me->set("no_get", 1);
	me->set("no_get_from", 1);
	me->disable_player(" <������>");
	me->start_call_out(bind((: call_other, __FILE__, "wakeup", me, where :), me),random(45) + 1 , me, where);

	return 1;
}

void wakeup(object me, object where)
{
	int skillslvl, addp, addc, exppot, intpot;

	skillslvl = (int) me->query_skill("mahayana", 1);
	exppot = (int) (me->query("combat_exp") / 100000);
	intpot = (int) (me->query_int() / 10);

	if (skillslvl > 100) skillslvl = (skillslvl - 100) / 2 + 100;
	if (exppot > 150) exppot = (exppot - 150) / 4 + 100; else
	if (exppot > 50)  exppot = (exppot - 50) / 2 + 50;

	addp = (int) (random(skillslvl) / 5 + intpot);
	addc = (int) (random(skillslvl) / 3 + exppot);

	if (me->query("combat_exp") >= 1500000)
		addc /= 2;

	if (me->query("combat_exp") >= 3000000)
		addc /= 2;

	if (me->query("combat_exp") >= 5000000)
		addc /= 2;

	me->receive_damage("jing", 15);
	me->receive_wound("jing", 3);
	if (objectp(where) && where->query("no_fight"))
		me->receive_wound("jing", 5);
	me->improve_potential(addp);
	me->add("combat_exp", addc);
	me->enable_player();
	message_vision("$N������ϣ��������ۣ���������һ������\n",me);
	me->set_temp("block_msg/all", 0);
	me->set("jingzuo_time", time());
	write("�㾲����ϣ��о������ۡ�\n");

	me->delete("no_get");
	me->delete("no_get_from");
	me->write_prompt();
	return;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : jingzuo

���ָ���Ƕ����ɵ������Ծ����޵�������.

HELP );
	return 1;
}
