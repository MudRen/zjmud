// feed.c �����

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object *obs;
	object ob;
	int lvl;

	if (me->ban_say(0))
		return 0;

	if (! arg)
		return notify_fail("��Ҫ���ĸ���ҽ���Ȧ��\n");

	lvl = me->query_skill("feed-power", 1);

	if (arg == "all" || arg == "ALL")
	{
		if (lvl < 500)
			return notify_fail("�������ˮƽ��δ������ʦ���磬�޷�ʩչ��������󷨡�\n");

		if (me->query_skill("idle-force", 1) < 500)
			return notify_fail("��ķ�������δ������ʦ���磬�޷�ʩչ��������󷨡�\n");

		if (me->query("potential") < me->query("learned_points") + 50)
			return notify_fail("���Ǳ�ܲ���������ʩչ��������󷨡�\n");

		if (me->query("jing") < 50)
			return notify_fail("��ľ���̫�����ʩչ��һ�����񹦡�\n");

		if (! environment(me)->is_chat_room() ||
		    environment(me) == find_object("/d/city/zhujuan"))
			return notify_fail("������������ʩչ������\n");

		obs = filter_array(all_inventory(environment(me)),
				   (: interactive($1) &&
				      $1 != $(me) &&
				      wiz_level($1) <= wiz_level($(me)) &&
				      query_idle($1) >= 120 :));
		if (sizeof(obs) < 1)
			return notify_fail("���ﲢû�к��ʵĶ�������ʩչ�񹦡�\n");

		me->add("learned_points", 50);
		me->receive_damage("jing", 50);

		message_sort(HIM "$N" HIM "���������дʵ����������飬�����飬��̳ʹ�߿�����飡��"
			       "ֻ�����һ����������������ֱ����£���ʱ��������...."NOR"\n", me);
		tell_object(obs, HIG "��ֻ����ͷһ��..."NOR"\n");
		obs->move("/d/city/zhujuan");
		message_sort("��������ɢȥ���㷢��" + implode(obs->name(), "��") + "��Ȼ�����ˣ�\n", me);
		message("vision", "ֻ��������������ͨ����" + chinese_number(sizeof(obs)) +
				  "���˵�������Ȧ�������������ź��ࡣ\n",
				  environment(obs[0]), obs);
		return 1;
	}

	if (! objectp(ob = find_player(arg)) || ! me->visible(ob))
		return notify_fail("��Ҫ���ĸ���ҽ���Ȧ��\n");

	if (me == ob)
		return notify_fail("�������ˮ��\n");

	if (wiz_level(me) < wiz_level(ob))
		return notify_fail("�������ˮƽ��û����ô�ߡ�\n");

	if (! lvl)
		return notify_fail("�����ѧ�����������˵��\n");

	if (lvl < 50)
		return notify_fail("�������ˮƽ̫��޷�ʩչ������\n");

	if (lvl < 300 && environment(ob) != environment(me))
		return notify_fail("�������ˮƽ���ޣ��޷�ʩչ������ǧ��֮�⣡\n");

	if (environment(ob) == find_object("/d/city/zhujuan"))
		return notify_fail("����������Ȧ�����ء�\n");

	if (! environment(ob)->is_chat_room() && wiz_level(me) < 1)
		return notify_fail("�������ڵĵص���������ʩչ������\n");

	if (! interactive(ob))
		return notify_fail("���˲������ϣ�������֮��\n");

	if (query_idle(ob) < 120)
		return notify_fail("�������ھ������أ��������ɡ�\n");

	if (me->query("jing") < 50)
		return notify_fail("��ľ���̫�����ʩչ��һ�����񹦡�\n");

	if (me->query("learned_points") + 10 > me->query("potential"))
		return notify_fail("���Ǳ�ܲ������޷�ʩչ��һ�����񹦡�\n");

	me->receive_damage("jing", 50);
	me->add("learned_points", 10);

	message_vision(HIM "$N" HIM "���������дʣ�����Ԫ˧������������Ϸ���һͷ��\n", me);
	if (! wizardp(ob) && (random(lvl * lvl) + lvl * lvl < ob->query("combat_exp") ||
	    ob->query("combat_exp") >= 50000))
	{
		write("û���κ�Ч������������������ɣ�\n");
		return 1;
	}

	switch(random(4))
	{
	case 0:
		message_vision(HIM "����ֳ�������ƣ�����Ԫ˧�������£�һ������"
			       HIM "$N" HIM "����Ц����������ȥ�ˡ�"NOR"\n",
			       ob);
		break;
	case 1:
		message_vision(HIM "����Ԫ˧������һ�������У�һ��ץס$N"
			       HIM "���ȵ����ߣ����Ǽ����������������ȥ��"NOR"\n",
			       ob);
		break;
	case 2:
		message_vision(HIM "����Ԫ˧����ææ������������������" +
			       ob->name() + HIM "���϶������ˣ�$N"
			       HIM "һ������æ��������ƨ�ɺ���ߵߵ����ˡ�"NOR"\n",
			       ob);
		break;
	default:
		message_vision(HIM "��ͨһ�£�ֻ������Ԫ˧������ˤ��������$N" +
			       HIM "�̲�ס����һЦ��Ԫ˧��ŭ�����üһ���������\n"
			       "һ���������ֻ���ҽ�������$N" HIM "��������Զȥ��"NOR"\n",
			       ob);
		break;
	}

	ob->move("/d/city/zhujuan");
	message("vision", "ֻ������ͨ��һ����" + ob->name() +
			  "��������Ȧ�������������ź��ࡣ\n",
		environment(ob), ob);
	write(HIC "�������󷨳ɹ��ˣ�" + ob->name(1) +
	      HIC "���ڽ���Ȧ��ȥ��"NOR"\n");

	CHANNEL_D->do_channel(this_object(), "rumor", "��˵" +
			      me->name(1) + HIM "ʩչ����󷨣�" +
			      ob->name(1) + HIM "����Ȧ������������˯���ѡ�");
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : feed <���> | all

���������ڷ����������ó������񹦣���ô����ʹ������ָ��
��������ͽ���Ȧʵϰ��ÿʹ��һ������󷨶���ķ�ʮ��Ǳ��
��һЩ���� ���ʹ�� all ����������Խ��ڳ����з�����ʿ��
����Ȧ����Ȼ���ķѵ�Ǳ�ܻ���ࡣ
 
HELP );
	return 1;
}
